#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<error.h>
#include<errno.h>

int main(void){
    char cwd[1024] = {'\0'};
    if(getcwd(cwd, 12)==NULL){
        error(1, errno, "getcwd");
    }
    puts(cwd);
    return 0;    
}
