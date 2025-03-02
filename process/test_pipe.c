// 测试匿名管道
#include<unistd.h>

#include<errno.h>
#include<error.h>

#include<stdio.h>

#include<string.h>

#include<sys/types.h>
#include<unistd.h>

int main(void){
    // int fd1[2];
    // int status = pipe(fd1);
    // if(status){
    //     error(1, errno, "pipe");
    // }
    // // printf("fd1[0]=%d, fd1[1]=%d\n", fd1[0], fd1[1]);
    // char buf[1024] = {'\0'};
    // while(1){
    //     printf("user:\n");
    //     if(fgets(buf, 1024, stdin)==NULL){
    //         error(1, errno, "fgets");
    //     }
    //     write(fd1[1], buf, strlen(buf) + 1);
    //     printf("system:\n");
    //     read(fd1[0], buf, 1024);
    //     printf("%s", buf);
        
    // }

    // int fd1[2];
    // int status = pipe(fd1);
    // if(status){
    //     error(1, errno, "pipe");
    // }
    // char buf[1024] = {'\0'};
    // pid_t pid = fork();
    // if(pid == -1){
    //     error(1, errno, "fork");
    // }else if(pid == 0){
    //     // 子进程
    //     // 关闭写通道
    //     if(close(fd1[1])){
    //         error(1, errno, "close");
    //     }
    //     while(read(fd1[0], buf, 1024)){
    //         printf("Sub:%s", buf);
    //     }
    // }else{
    //     // 父进程
    //     // 关闭读通道
    //     if(close(fd1[0])){
    //         error(1, errno, "close");
    //     }
    //     while(1){
    //         printf("Main:");
    //         if(fgets(buf, 1024, stdin)==NULL){
    //             error(1, errno, "fgets");
    //         }
    //         write(fd1[1], buf, strlen(buf)+1);
    //     }
    // }
    // return 0;
    int fd1[2];
    int fd2[2];
    if(pipe(fd1) && pipe(fd2)){
        error(1, errno, "pipe");
    }
    
    pid_t pid = fork();

}