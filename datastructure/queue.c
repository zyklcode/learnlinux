#include "queue.h"
#include <stdlib.h>
#include <string.h>

bool queue_empty(const Queue *q){
    return q->size == 0;
}

bool _queue_full(const Queue *q){
    return q->size == q->capacity;
}

void _queue_capacity_grow(Queue *q){
    int new_capacity = q->capacity + q->capacity / 8;
    E* new_data = calloc(new_capacity, sizeof(E));
    memcpy(new_data, q->data + q->front, q->capacity - q->front);
    memcpy(new_data, q->data, q->front);
    free(q->data);
    q->capacity = new_capacity;
    q->data = new_data;
    q->front = 0;
    q->rear = q->size - 1;
}

void queue_push(Queue *q, E val){
    if(_queue_full(q)){
        // 扩容
        _queue_capacity_grow(q);
    }
    q->size++;
    q->rear  = (q->rear + 1) % q->capacity;
    q->data[q->rear] = val;
}

int queue_pop(Queue *q, E* ret){
    if(queue_empty(q)){
        return -1;
    }
    q->size--;
    *ret = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    return 0;
}

int queue_peek(const Queue *q, E* ret){
    if(queue_empty(q)){
        return -1;
    }
    *ret = q->data[q->front];
    return 0;
}

Queue* queue_create(){
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if(q){
        q->size = 0;
        q->capacity = INIT_QUEUE_CAPACITY;
        q->data = calloc(q->capacity, sizeof(E));
        q->front = 0;
        q->rear = -1;
        return q;
    }
    return NULL;
    
}

void queue_destory(Queue *q){
    if(q){
        free(q->data);
        free(q);
    }
}