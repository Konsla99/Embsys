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

int main(){
	playMusic();
	usleep(100000000);
	stopMusic();
	return 0;
}
