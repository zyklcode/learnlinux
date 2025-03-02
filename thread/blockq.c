#include "blockq.h"
#include <stdlib.h>
#include <errno.h>
#include <error.h>

BlockQ* blockq_create(void){
    BlockQ *q = (BlockQ*)malloc(sizeof(BlockQ));
    if(!q){
        error(1, 0, "malloc");
    }
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->no_empty, NULL);
    pthread_cond_init(&q->no_full, NULL);

    return q;

}
void blockq_destory(BlockQ *q){
    pthread_mutex_destroy(&q->lock);
    pthread_cond_destroy(&q->no_empty);
    pthread_cond_destroy(&q->no_full);
    free(q);
}

void blockq_push(BlockQ *q, E val){
    // 获取锁
    pthread_mutex_lock(&q->lock);

    // 如果队列满了，就阻塞，等待队列不满
    while(q->size == N){
        // 当不满足条件时，释放锁并阻塞
        // 当返回时，表示前面某刻曾满足条件，现在是否满足条件不确定，需要再一次检查
        // 获取锁
        pthread_cond_wait(&q->no_full, &q->lock); 
    } // 获取了互斥锁，size != N

    q->elements[q->rear] = val;
    q->rear = (q->rear + 1)%N;
    q->size++;

    // not_empty成立，唤醒等待not_empty的线程
    pthread_cond_signal(&q->no_empty);

    // 释放锁
    pthread_mutex_unlock(&q->lock);

}
E    blockq_pop(BlockQ *q){
    // 获取锁
    pthread_mutex_lock(&q->lock);

    // 判断是否为空
    while(q->size == 0){
        pthread_cond_wait(&q->no_empty, &q->lock);
    }

    E retval = q->elements[q->front];
    q->front = (q->front + 1) % N;
    q->size--;

    // 现在队列size减少，肯定不满了
    pthread_cond_signal(&q->no_full);

    // 释放锁
    pthread_mutex_unlock(&q->lock);

    return retval;
}

E    blockq_peek(const BlockQ *q){
    // 获取锁
    pthread_mutex_lock(&q->lock);

    // 判断是否为空
    while(q->size == 0){
        pthread_cond_wait(&q->no_empty, &q->lock);
    }

    E retval = q->elements[q->front];

    // 释放锁
    pthread_mutex_unlock(&q->lock);

    return retval;

    
}

bool blockq_empty(const BlockQ *q){
    pthread_mutex_lock(&q->lock);
    int size = q->size;
    pthread_mutex_unlock(&q->lock);
    return size == 0;
}

bool blockq_full(const BlockQ *q){
    pthread_mutex_lock(&q->lock);
    int size = q->size;
    pthread_mutex_unlock(&q->lock);
    return size == N;
}

