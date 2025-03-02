#include<stdio.h>
// wait
#include <sys/types.h>
#include <sys/wait.h>
// fork
#include <sys/types.h>
#include <unistd.h>
// error errno
#include<errno.h>
#include<error.h>

// exit
#include<stdlib.h>

// open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include<string.h>


int main(void){
    // int fd = open("./_stdin", O_RDWR | O_CREAT | O_TRUNC, 0666);
    // dup2(fd, STDOUT_FILENO);
    // system("pwd");
    // char arr[1024] = {'\0'};
    // fgets(arr, 1024, STDOUT_FILENO);
    // fflush(STDOUT_FILENO);
    char cmd[256] = {'\0'};
    char cwd[256] = {'\0'};
    while(1){
        if(getcwd(cwd, 256)==NULL){
            error(1, errno, "getcwd");
        }
        printf("zyk@zyk:%s$ ", cwd);
        if(fgets(cmd, 256, stdin) == NULL){
            error(1, errno, "fgets");
        }

        if(strcmp(cmd, "quit\n")==0){
            exit(0);
        }
        system(cmd);
    }
    return 0;
}