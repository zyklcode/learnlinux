// 实现生产者消费者模型

#include "blockq.h"
#include <stdio.h>
#include <stdlib.h>

#include <error.h>

#include <unistd.h>

void* consume(void* arg){
    E data = 0;
    BlockQ* q = (BlockQ*)arg;
    while(1){
        data = blockq_pop(q);
        printf("Thread %ld: consume %d\n", pthread_self(), data);
        sleep(2);
    }
    return NULL;
}

void* produce(void* arg){
    BlockQ* q = (BlockQ*)arg;
    srand(time(NULL));
    E data;
    while(1){
        data = rand() % 1000;
        blockq_push(q, data);
        printf("Thread %ld: produce %d\n", pthread_self(), data);
        sleep(2);
    }
    return NULL;
}

int main(void){
    BlockQ* q = blockq_create();
    pthread_t pid1;
    if(pthread_create(&pid1, NULL, consume, (void*)q)){
        error(1, 0, "pthread_create");
    }

    pthread_t pid2;
    if(pthread_create(&pid2, NULL, produce, (void*)q)){
        error(1, 0, "pthread_create");
    }

    pthread_t pid3;
    if(pthread_create(&pid3, NULL, produce, (void*)q)){
        error(1, 0, "pthread_create");
    }

    if(pthread_join(pid1, NULL)){
        error(1, 0, "pthread_join");
    }

    if(pthread_join(pid2, NULL)){
        error(1, 0, "pthread_join");
    }

    if(pthread_join(pid3, NULL)){
        error(1, 0, "pthread_join");
    }

    return 0;
}