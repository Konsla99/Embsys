#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define PIPE "/tmp/my_pipe"
#define BUFFER_SIZE 10

int main() {
    int pipe_fd;
    char buffer[BUFFER_SIZE];
    int isPlaying = 0;  // 음악 재생 상태 추적

    pipe_fd = open(PIPE, O_RDONLY);
    if (pipe_fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    while (1) {
        ssize_t bytes_read = read(pipe_fd, &buffer, BUFFER_SIZE);  // 단일 문자 읽기
        if (bytes_read > 0) {
            printf("Received: %c\n", buffer[0]);  // 단일 문자 출력

            if (buffer[0] == 'L' && !isPlaying) {
                // 'L' 입력 시, 음악이 정지 상태이면 재생 시작
                system("aplay taeyeon.wav &");  // 음악 재생
                isPlaying = 1;
            } else if (buffer[0] == 'R' && isPlaying) {
                // 'R' 입력 시, 음악이 재생 상태이면 정지
                system("pkill aplay");  // 음악 정지
                isPlaying = 0;
            }
        } else {
            perror("read");
            close(pipe_fd);
            return EXIT_FAILURE;
        }
    }

    close(pipe_fd);
    return EXIT_SUCCESS;
}

