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

	    char* token = strtok(buffer, " ");
	    while (token !=NULL) {
            printf("%s\n", token);
	    token = strtok(NULL, " ");
	    if(count%2==0){
		    state = token;
	    }
	    else{
		    score = token;
	    }
	    count++;
	    if(count >= 9999){
		 count = 0;
        }
        else {
            perror("read");
            close(pipe_fd);
            return EXIT_FAILURE;
            }
        }
    }

    close(pipe_fd);
    return EXIT_SUCCESS;
    }
}

