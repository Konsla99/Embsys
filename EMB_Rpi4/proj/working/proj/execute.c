#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.h>
#include <tensorflow/lite/c/c_api.h>

#define IMG_WIDTH 224
#define IMG_HEIGHT 224
#define IMG_CHANNELS 3

int main() {
    // TensorFlow Lite 모델 로드
    const char* model_path = "your_model.tflite";
    TfLiteModel* model = TfLiteModelCreateFromFile(model_path);
    TfLiteInterpreterOptions* options = TfLiteInterpreterOptionsCreate();
    TfLiteInterpreter* interpreter = TfLiteInterpreterCreate(model, options);

    // 인터프리터에 메모리 할당
    TfLiteInterpreterAllocateTensors(interpreter);

    // 입력 및 출력 텐서 정보 가져오기
    TfLiteTensor* input_tensor = TfLiteInterpreterGetInputTensor(interpreter, 0);
    const TfLiteTensor* output_tensor = TfLiteInterpreterGetOutputTensor(interpreter, 0);

    // 레이블 파일 로드
    FILE* file = fopen("labels.txt", "r");
    char labels[1000][30]; // 최대 1000개의 레이블, 각 레이블은 최대 30자
    int num_labels = 0;
    while (fgets(labels[num_labels], 30, file)) {
        num_labels++;
    }
    fclose(file);

    // OpenCV로 웹캠 열기
    CvCapture* capture = cvCaptureFromCAM(0);
    IplImage* frame;
    IplImage* resized_frame = cvCreateImage(cvSize(IMG_WIDTH, IMG_HEIGHT), IPL_DEPTH_8U, IMG_CHANNELS);

    while (1) {
        // 웹캠에서 이미지 캡처
        frame = cvQueryFrame(capture);
        if (!frame) break;

        // 이미지 크기 조정
        cvResize(frame, resized_frame, CV_INTER_LINEAR);

        // 이미지 전처리 및 정규화
        unsigned char* frame_data = (unsigned char*)resized_frame->imageData;
        float input_data[IMG_WIDTH * IMG_HEIGHT * IMG_CHANNELS];
        for (int i = 0; i < IMG_WIDTH * IMG_HEIGHT * IMG_CHANNELS; i++) {
            input_data[i] = (frame_data[i] - 127.5) / 127.5;
        }

        // 모델 입력 설정
        TfLiteTensorCopyFromBuffer(input_tensor, input_data, sizeof(input_data));

        // 모델 실행
        TfLiteInterpreterInvoke(interpreter);

        // 예측 결과 읽기
        float* output = TfLiteTensorData(output_tensor);
        int max_index = 0;
        float max_value = output[0];
        for (int i = 1; i < num_labels; i++) {
            if (output[i] > max_value) {
                max_index = i;
                max_value = output[i];
            }
        }

        // 결과 출력
        printf("Predicted: %s, Confidence: %f\n", labels[max_index], max_value);

        // 키보드 입력 확인 (ESC 키로 종료)
        char c = cvWaitKey(1);
        if (c == 27) break; // ESC 키
    }

    // 정리
    cvReleaseImage(&resized_frame);
    cvReleaseCapture(&capture);
    TfLiteInterpreterDelete(interpreter);
    TfLiteInterpreterOptionsDelete(options);
    TfLiteModelDelete(model);

    return 0;
}

