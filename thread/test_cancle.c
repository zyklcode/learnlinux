#include<pthread.h>
#include<sys/types.h>

#include<errno.h>
#include<error.h>

#include<stdlib.h>

#include<unistd.h>

void* start_routine(void* arg){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    // pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    while(1){
        sleep(2);
    };
    return NULL;
}

int main(void){
    pthread_t pid;
    if(pthread_create(&pid, NULL, start_routine, NULL)){
        error(1, 0, "pthread_create");
    }
    
    sleep(2);

    if(pthread_cancel(pid)){
        error(1, 0, "pthread_cancel");
    }

    if(pthread_join(pid, NULL)){
        error(1, 0, "pthread_join");
    }
    return 0;
}