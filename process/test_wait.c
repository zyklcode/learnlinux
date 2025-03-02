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


void print_wstatus(int wstatus){
    if(WIFEXITED(wstatus)){
        printf("exited, status=%d\n", WEXITSTATUS(wstatus));
    } else if(WIFSIGNALED(wstatus)){
        printf("killed by signal %d\n", WTERMSIG(wstatus));
    } else if(WIFSTOPPED(wstatus)){
        printf("stopped by signal %d\n", WSTOPSIG(wstatus));
    } else{

    }
}

int main(void){
    pid_t pid = fork();
    if(pid == 0){
        // 子进程执行流
        sleep(2);
        printf("pid=%d\n", getpid());
        // exit(10);
        abort();
    }else if(pid == -1){
        // 执行异常时的代码
        error(1, errno, "fork");
    }else{
        // 父进程执行流
        int wstatus = 0;
        if(wait(&wstatus)==-1){
            error(1, 0, "wait");
        }
        print_wstatus(wstatus);
        printf("pid=%d\n", getpid());

    }
    return 0;
}