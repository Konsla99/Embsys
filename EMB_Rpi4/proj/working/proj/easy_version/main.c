#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define PIPE "/tmp/my_pipe"
#define BUFFER_SIZE 1024

//void playMusic() {
    // "omxplayer"나 "mpg321" 등 사용 중인 음악 플레이어 명령어로 변경
  //  system("omxplayer your_music_file.mp3 &");
  //  printf("Music Playing\n");
//}

//void stopMusic() {
    // "killall" 명령어로 음악 플레이어 프로세스를 종료
//    system("killall omxplayer");
 //   printf("Music Stopped\n");
//}

int main(int argc,char*argv[]) {
    int pipe_fd;
    char buffer[2];
   
   
    pipe_fd = open(PIPE, O_RDONLY);
    if (pipe_fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }
    int dev1 = open("/dev/motor_driver", O_RDWR);// step motor
    int dev2 = open("/dev/my_LED", O_RDWR);// led device 
    
    if (dev1 == -1) {
        printf("Opening was not possible!\n");
        return -1;
    }

    if (dev2 == -1) {
        printf("Opening was not possible!\n");
        return -1;
    }
    printf("device opening was successful!\n");

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
                //write(dev1,&buffer[0],1);
                //usleep(100);
            }
            else if(buffer[0]== 'L'){
                printf("Left\n");
                //write(dev1,&buffer[0],1)
                //usleep(100);
            }
          //   else if(buffer[0]== 'A'){//for controll audio amp
            //    printf("audio toggle\n");
            //    if (system("pgrep omxplayer")) {
            //    // omxplayer not play
            //    playMusic();
            //    } else {
            //    // omxplayer when music is played
             //   stopMusic();
             //   }
           // }
            else if(buffer[0]== 'B'){//for controll led light bulb
                printf("led toggle\n");
                //write(dev2,&buffer[0],1)
            }            
                //printf("%c\n", buffer[0]);    
        }
        else{
            perror("read");
            close(pipe_fd);
            return EXIT_FAILURE;
        }
    }
   // write(dev2,0,1);
    close(dev1);
    close(dev2);
    close(pipe_fd);
    return EXIT_SUCCESS;
}


