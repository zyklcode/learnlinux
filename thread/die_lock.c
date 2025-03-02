#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<error.h>


typedef struct{
    int id;
    int account;
    pthread_mutex_t mutex;
}Account;

pthread_mutex_t global_mutex = PTHREAD_MUTEX_INITIALIZER;


// 破解循环等待条件
void withdraw1(Account* a, Account* b, int money){
    if(a->id > b->id){
        pthread_mutex_lock(&b->mutex);
        sleep(2);
        pthread_mutex_lock(&a->mutex);
    }else{
        pthread_mutex_lock(&a->mutex);
        sleep(2);
        pthread_mutex_lock(&b->mutex);
    }
        
    a->account = a->account - money;
    b->account = b->account + money;
    pthread_mutex_unlock(&b->mutex);
    pthread_mutex_unlock(&a->mutex);

}

// 破解不可剥夺条件
void withdraw2(Account* a, Account* b, int money){
    start:
        pthread_mutex_lock(&a->mutex);
        // sleep(1);
        if(pthread_mutex_trylock(&b->mutex)){
            pthread_mutex_unlock(&a->mutex);
            goto start;
        }    
    a->account = a->account - money;
    b->account = b->account + money;
    pthread_mutex_unlock(&b->mutex);
    pthread_mutex_unlock(&a->mutex);
}

// 破解持有并请求条件
void withdraw(Account* a, Account* b, int money){
    pthread_mutex_lock(&global_mutex);
    pthread_mutex_lock(&a->mutex);
    sleep(1);
    pthread_mutex_lock(&b->mutex);
    pthread_mutex_unlock(&global_mutex);
    a->account = a->account - money;
    b->account = b->account + money;
    pthread_mutex_unlock(&b->mutex);
    pthread_mutex_unlock(&a->mutex);
}

Account account1 = {20022, 1000, PTHREAD_MUTEX_INITIALIZER};
Account account2 = {20023, 2000, PTHREAD_MUTEX_INITIALIZER};

void* start_routine1(void* arg){
    int* monet_p = (int *)arg;
    int money = *monet_p;
    printf("account1--->account2 start, account1:%d, account2:%d\n", account1.account, account2.account);
    withdraw(&account1, &account2, money);
    printf("account1--->account2 end, account1:%d, account2:%d\n", account1.account, account2.account);
    return NULL;
}

void* start_routine2(void* arg){
    int* monet_p = (int *)arg;
    int money = *monet_p;
    printf("account2--->account1 start, account1:%d, account2:%d\n", account1.account, account2.account);
    withdraw(&account2, &account1, money);
    printf("account2--->account1 end, account1:%d, account2:%d\n", account1.account, account2.account);
    return NULL;
}

int main(void){
    int money = 500;
    pthread_t pid1, pid2;
    if(pthread_create(&pid1, NULL, start_routine1, (void*)&money)){
        error(1, 0, "pthread_create");
    }
    if(pthread_create(&pid2, NULL, start_routine2, (void*)&money)){
        error(1, 0, "pthread_create");
    }

    if(pthread_join(pid1, NULL)){
        error(1, 0, "pthread_join");
    }
    if(pthread_join(pid2, NULL)){
        error(1, 0, "pthread_join");
    }
    return 0;
}