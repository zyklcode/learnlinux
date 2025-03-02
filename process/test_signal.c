#include<signal.h>
#include<stdio.h>

void signal_handler(int signum){
    switch (signum)
    {
    case SIGABRT:
        puts("I am SIGABRT");
        break;
    case SIGFPE:
        puts("I am SIGFPE");
        break;
    case SIGQUIT:
        puts("I am SIGQUIT");
        break;
    case SIGTERM:
        puts("I am SIGTERM");
        break;
    default:
        puts("I am SIGOTHER");
        break;
    }
}

int main(void){
    signal(SIGINT, signal_handler);
    
    int i = 1;
    while(1){
        20/(i-1);
    }
    return 0;
}