#ifndef __QUEUE_H
#define __QUEUE_H

#include<stdbool.h>

#define INIT_QUEUE_CAPACITY 1024
typedef int E;
typedef struct Queue{
    E *data;
    int front, rear;
    int size;
    int capacity;
}Queue;

bool queue_empty(const Queue *q);

bool queue_full(const Queue *q);

void queue_push(Queue *q, E val);

E queue_pop(Queue *q);

E queue_peek(const Queue *q);

Queue* queue_create();

Queue* queue_destory();



#endif