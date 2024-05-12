#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define PIPE "/tmp/my_pipe"
#define BUFFER_SIZE 1024

int main() {
    int pipe_fd;
    char buffer[2];
   
   
    pipe_fd = open(PIPE, O_RDONLY);
    if (pipe_fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    while (1) {
        ssize_t bytes_read = read(pipe_fd, buffer, BUFFER_SIZE - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            if(buffer[0]=='S'){
               printf("Stop\n");}
            else if(buffer[0]=='R'){
                printf("Right\n");}
            else
                printf("Left\n");    
                //printf("%c\n", buffer[0]);    
        }
        else{
            perror("read");
            close(pipe_fd);
            return EXIT_FAILURE;
        }
    }

    close(pipe_fd);
    return EXIT_SUCCESS;
}


