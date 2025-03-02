#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include<errno.h>
#include<error.h>

int main(void){
    for(int i=0;i<3;i++){
        fork();
        printf("a\n");
    }
    return 0;
}