
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define PIPE "/tmp/my_pipe"
#define BUFFER_SIZE 1024

void playMusic() {
    // "omxplayer"나 "mpg321" 등 사용 중인 음악 플레이어 명령어로 변경
    system("mpg321 cocatest.mp3 &");
    printf("Music Playing\n");
}

void stopMusic() {
    // "killall" 명령어로 음악 플레이어 프로세스를 종료
    system("killall mpg321");
    printf("Music Stopped\n");
}

int main(int argc,char*argv[]) {
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
            if(buffer[0]=='S'){//motor stop and buzz on
               printf("Stop\n");
                
               //write(dev1,&buffer[0],1);
               //usleep(100);
            }
            else if(buffer[0]=='R'){
                printf("Right\n");
                if (system("pgrep mpg321")) {
                // omxplayer not play
                playMusic();
                } else {
                // omxplayer when music is played
                stopMusic();
                }
                //write(dev1,&buffer[0],1);
                //usleep(100);
            }
            else if(buffer[0]== 'L'){
                printf("Left\n");
                //write(dev1,&buffer[0],1)
                //usleep(100);
            }
             else if(buffer[0]== 'A'){//for controll audio amp
                printf("audio toggle\n");
              
            }
            else if(buffer[0]== 'L'){//for controll led
                printf("led toggle\n");
                //write(dev2,&buff,sizeof(buff))
            }            
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

Music Playing
High Performance MPEG 1.0/2.0/2.5 Audio Player for Layer 1, 2, and 3.
Version 0.3.2-1 (2012/03/25). Written and copyrights by Joe Drew,
now maintained by Nanakos Chrysostomos and others.
Uses code from various people. See 'README' for more!
THIS SOFTWARE COMES WITH ABSOLUTELY NO WARRANTY! USE AT YOUR OWN RISK!
tcgetattr(): Inappropriate ioctl for device

Playing MPEG stream from cocatest.mp3 ...
                                                                            
[0:00] Decoding of cocatest.mp3 finished.



