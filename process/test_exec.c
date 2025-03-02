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


int main(void){
    // execl("./print_env", "1", "2", NULL);
    char* env[] = {"abs=3", "qwwwq=4", NULL};
    // execlp("ls" "-al", ".", NULL);
    execle("./print_env", "./print_env", NULL, env);
    return 0;
}