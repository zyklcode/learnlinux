#include<stdio.h>
#include<stdlib.h>
#include<error.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include <unistd.h>

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

    do{
        printf("1:");
        if(!fgets(send, LINE_MAX_SIZE, stdin)){
            write(fd_wr, "quit\n", 5);
            exit(-1); 
        }
        write(fd_wr, send, strlen(send));
        if(strcmp(send, "quit\n")==0){
            break;
        }
        read(fd_rd, recv, LINE_MAX_SIZE);
        printf("2:%s", recv);
        if(strcmp(recv, "quit\n")==0){
            break;
        }
        memset(recv, '\0', LINE_MAX_SIZE);
    }while(1);
    

    close(fd_rd);
    close(fd_wr);

    return 0;
}