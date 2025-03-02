#include<stdio.h>
#include<error.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void){
    int fd_wr = open("pipe1", O_WRONLY);
    if(fd_wr == -1){
        error(1, errno, "open pipe1");
    }

    int fd_rd = open("pipe2", O_RDONLY);
    if(fd_wr == -1){
        error(1, errno, "open pipe2");
    }

    puts("Established");

    return 0;
}