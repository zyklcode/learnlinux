#include<stdio.h>
#include<stdlib.h>
#include<error.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include <unistd.h>
#include<sys/select.h>

#define LINE_MAX_SIZE 256

int main(void){
    int fd_wr = open("pipe1", O_WRONLY);
    if(fd_wr == -1){
        error(1, errno, "open pipe1");
    }

    int fd_rd = open("pipe2", O_RDONLY);
    if(fd_rd == -1){
        error(1, errno, "open pipe2");
    }

    puts("Established");

    char recv[LINE_MAX_SIZE] = {'\0'};
    char send[LINE_MAX_SIZE] = {'\0'};

    fd_set mainfds;
    FD_ZERO(&mainfds);
    int maxfd = 0;
    FD_SET(STDIN_FILENO, &mainfds);
    maxfd = STDIN_FILENO;
    FD_SET(fd_rd, &mainfds);
    maxfd = maxfd > fd_rd ? maxfd : fd_rd;

    struct timeval timeout = {20, 0};

    while(1){
        fd_set readfds = mainfds;
        int event = select(maxfd+1, &readfds, NULL, NULL, NULL);
        switch(event){
            case -1:
                // 出错
                error(1, errno, "select");
            case 0:
                // 超时
                printf("TIMEOUT\n");
                continue;
            default:
                // 有读事件就绪
                // printf("timeout: tv_sec = %ld tv_usec = %ld\n", timeout.tv_sec, timeout.tv_usec);
                // STDIN_FILENO就绪
                if(FD_ISSET(STDIN_FILENO, &readfds)){
                    fgets(send, LINE_MAX_SIZE, stdin);
                    write(fd_wr, send, strlen(send)+1);
                }

                // read pipe就绪
                if(FD_ISSET(fd_rd, &readfds)){
                    int nbytes = read(fd_rd, recv, LINE_MAX_SIZE);
                    // 对端关闭
                    if(nbytes == 0){
                        goto end;
                    }else if(nbytes == -1){
                        error(1, errno, "read");
                    }else{
                        printf("from p1: %s", recv);
                    }
        }
    }
    }
    
    end:
        close(fd_rd);
        close(fd_wr);

    return 0;
}