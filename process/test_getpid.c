#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>

int main(void){
    printf("pid=%d\n", getpid());
    printf("ppid=%d\n", getppid());
    sleep(20);
    return 0;
}