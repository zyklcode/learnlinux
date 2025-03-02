#ifndef __WD_BLOCKQ_H
#define __WD_BLOCKQ_H

#include <pthread.h>
#include <stdbool.h>

#define N 1024
typedef int E;

typedef struct{
    E elements[N];
    int front;
    int rear;
    int size;

    pthread_mutex_t lock;
    pthread_cond_t no_empty;
    pthread_cond_t no_full;

}BlockQ;

// API
BlockQ* blockq_create(void);
void blockq_destory(BlockQ *q);

void blockq_push(BlockQ *q, E val);
E    blockq_pop(BlockQ *q);

E    blockq_peek(const BlockQ *q);

bool blockq_empty(const BlockQ *q);
bool blockq_full(const BlockQ *q);




#endif