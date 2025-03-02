#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

#include<error.h>
#include<errno.h>

typedef struct {
    int id;
    char name[20];
    int age;
}Student;


typedef struct{
    int min;
    int max;
}Section;

void* start_routine(void* arg){

    Section* p_sec = (Section*)arg;
    int sum = 0;
    for(int i=p_sec->min;i<=p_sec->max;i++){
        sum += i;
    }
    pthread_exit((void*)sum);
    return NULL;
}

int main(int argc, char *argv[]){
    // 获取线程id
    // Student s1 = {20022, "ZhaoYongkang", 28};
    // pthread_t pid = pthread_self();
    // // 创建线程
    // pthread_t sub_pid1;
    // if(pthread_create(&sub_pid1, NULL, start_routine, (void*)&s1)){
    //     error(1, 0, "pthread_create");
    // }
    // int *res=NULL;
    // if(pthread_join(sub_pid1, (void**)&res)){
    //     error(1, 0, "pthread_join");
    // }

    // printf("pid=%lu res=%d\n", pid, res);
    if(argc!=3){
        error(1, 0, "Usage: %s min max", argv[0]);
    }
    int min = 0;
    int max = 0;
    sscanf(argv[1], "%d", &min);
    sscanf(argv[2], "%d", &max);

    Section sec = {min, max};
    pthread_t pid;
    if(pthread_create(&pid, NULL, start_routine, (void *)&sec)){
        error(1, 0, "pthread_create");
    }
    int sum=0;
    if(pthread_join(pid, (void**)&sum)){
        error(1, 0, "pthread_join");
    }
    printf("%d\n", sum);
    
    return 0;
}