#include<pthread.h>

#include<stdio.h>

#include<sys/types.h>

#include<errno.h>
#include<error.h>

long money = 1000000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* start_routine(void* arg){
    for(long i=0;i<1000000;i++){
        pthread_mutex_lock(&mutex);
        money = money -1;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(void){
    pthread_t pid1;
    if(pthread_create(&pid1, NULL, start_routine, NULL)){
        error(1, 0, "pthread_create");
    }

    pthread_t pid2;
    if(pthread_create(&pid2, NULL, start_routine, NULL)){
        error(1, 0, "pthread_create");
    }

    if(pthread_join(pid1, NULL)){
        error(1, 0, "pthread_cancel");
    }

    if(pthread_join(pid2, NULL)){
        error(1, 0, "pthread_cancel");
    }

    printf("money=%ld\n", money);
    pthread_mutex_destroy(&mutex);
    return 0;
}