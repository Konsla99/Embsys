#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define PIPE "/tmp/my_pipe"
#define BUFFER_SIZE 1024
#define MAX_CLASSES 100

typedef struct {
    char class_name[100];
    int confidence;
} Prediction;

int main() {
    int pipe_fd;
    char buffer[BUFFER_SIZE];
    Prediction predictions[MAX_CLASSES];

    // 파이프 파일 열기
    pipe_fd = open(PIPE, O_RDONLY);
    if (pipe_fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    while (1) {
        // 파이프에서 데이터 읽기
        ssize_t bytes_read = read(pipe_fd, buffer, BUFFER_SIZE);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';

            // 첫 번째 토큰 (클래스 이름) 추출
            char* token = strtok(buffer, " ");
            if (token != NULL) {
                strncpy(predictions[prediction_count].class_name, token, sizeof(predictions[prediction_count].class_name));
            }
	    printf("Class: %s\n", predictions[i].class_name);

            // 두 번째 토큰 (신뢰도 점수) 추출 및 변환
            token = strtok(NULL, " ");
            if (token != NULL) {
                predictions[prediction_count].confidence = atoi(token);
            }
	    printf("Confidence: %d\n");

        } else {
            perror("read");
            break;
        }
    }

    close(pipe_fd);
    return EXIT_SUCCESS;
}

