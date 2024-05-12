#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define PIPE "/tmp/my_pipe"

int main() {
    int pipe_fd;
    char buffer;
    int isPlaying = 0;  // 음악 재생 상태 추적

    pipe_fd = open(PIPE, O_RDONLY);
    if (pipe_fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    while (1) {
        ssize_t bytes_read = read(pipe_fd, &buffer, 1);  // 단일 문자 읽기
        if (bytes_read > 0) {
            printf("Received: %c\n", buffer);  // 단일 문자 출력

            if (buffer == 'R') {
                if (isPlaying) {
                    system("pkill aplay");  // 음악 정지
                    isPlaying = 0;
                } else {
                    system("aplay taeyeon.wav &");  // 음악 재생
                    isPlaying = 1;
                }
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

