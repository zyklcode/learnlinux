#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include<errno.h>
#include<error.h>

int main(void){
    int i = 40;
    printf("BEGIN:");
    pid_t pid = fork();
    if(pid==-1){
        error(1, 0, "fork");
    }
    
    while(i>0){
        printf("pid=%d, num=%d\n", getpid(), i);
        i--;
        sleep(1);
    }
    
    return 0;
}