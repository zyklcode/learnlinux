#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include<errno.h>
#include<error.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void){
    int fd = open("text", O_RDWR | O_CREAT | O_TRUNC, 0666);
    pid_t pid = fork();
    if(pid==-1){
        error(1, 0, "fork");
    }else if(pid==0){
        // 子进程代码
        write(fd, "hello\n", 6);
        close(fd);
    }else{
        // 父进程代码
        write(fd, "world\n", 6);
        close(fd);
    }
    
    return 0;
}