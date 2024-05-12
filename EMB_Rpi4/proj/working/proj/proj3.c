#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define PIPE "/tmp/my_pipe"
#define BUFFER_SIZE 1024

int main() {
    int pipe_fd;
    char buffer[BUFFER_SIZE];
    int count = 0;
    char* state;
    char* score;
    char* saveptr;

    pipe_fd = open(PIPE, O_RDONLY);
    if (pipe_fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    while (1) {
        ssize_t bytes_read = read(pipe_fd, buffer, BUFFER_SIZE - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            char* token = strtok_r(buffer, " ", &saveptr);
            while (token != NULL) {
                printf("%s\n", token);
                if (count % 2 == 0) {
                    score = token;
		    if((score[0] == '7' || score[0] == '8' || score[0] == '9' || score[0] == '1') && score[1] != (NULL || '\n')) {
				    printf("score:%s\n",score);
		    }
                }

		if (count % 2 == 1) {
                    state = token;
		    if((score[0] == '7' || score[0] == '8' || score[0] == '9' || score[0] == '1') && score[1] != (NULL || '\n')) {
				    printf("state:%s\n",state);
				    }
                }
                count++;
                token = strtok_r(NULL, " ", &saveptr);
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


