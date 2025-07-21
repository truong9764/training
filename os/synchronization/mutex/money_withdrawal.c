#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int money;
static pthread_mutex_t mutex;

void* account1_func(void* args)
{
    int *rtn = malloc(sizeof(int));
    *rtn = 0;

    int* max_draw = (int*)args;
    int amount = *max_draw;

    while(money > amount)
    {
        pthread_mutex_lock(&mutex);
        money -= amount;
        printf("Account 1 draw %d | ", amount);
        printf("Money left %d\n", money);
        //return rtn;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    return rtn;
}   

void* account2_func(void* args)
{
    int *rtn = malloc(sizeof(int));
    *rtn = 0;

    int* max_draw = (int*)args;
    int amount = *max_draw;

    while(money > amount)
    {
        pthread_mutex_lock(&mutex);
        money -= amount;
        printf("Account 2 draw %d | ", amount);
        printf("Money left %d\n", money);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    return rtn;
}

void* account3_func(void* args)
{   
    int *rtn = malloc(sizeof(int));
    *rtn = 0;

    int* max_draw = (int*)args;
    int amount = *max_draw;

    while(money > amount)
    {
        pthread_mutex_lock(&mutex);
        money -= amount;
        printf("Account 3 draw %d | ", amount);
        printf("Money left %d\n", money);
        pthread_mutex_unlock(&mutex);
        sleep(1);
        
    }

    return rtn;
}

void* system_thread_func(void* arg)
{
    int *rtn = malloc(sizeof(int));
    *rtn = 0;

    while(money > 0)
    {
        pthread_mutex_lock(&mutex);
        printf("Money left %d\n", money);
        pthread_mutex_unlock(&mutex);
        sleep(3);
    }

    return rtn;
}

int main(int argc, char* argv[])
{
    pthread_t account1_thread;
    pthread_t account2_thread;
    pthread_t account3_thread;
    pthread_t system_thread;

    void* account1_rtn;
    void* account2_rtn;
    void* account3_rtn;
    void* system_rtn;

    int max_draw1;
    int max_draw2;
    int max_draw3;

    if(argc > 1)
    {
        money = atoi(argv[1]);
        max_draw1 = atoi(argv[2]);
        max_draw2 = atoi(argv[3]);
        max_draw3 = atoi(argv[4]);

        printf("Total money: %d\n", money);
        printf("Max money account 1 can withdraw: %d\n", max_draw1);
        printf("Max money account 2 can withdraw: %d\n", max_draw2);
        printf("Max money account 3 can withdraw: %d\n", max_draw3);

        if(pthread_create(&account1_thread, NULL, account1_func, &max_draw1) > 0)
        {
            perror("pthread_create");
            return 1;
        }

        if(pthread_create(&account2_thread, NULL, account2_func, &max_draw2) > 0)
        {
            perror("pthread_create");
            return 1;
        }

        if(pthread_create(&account3_thread, NULL, account3_func, &max_draw3) > 0)
        {
            perror("pthread_create");
            return 1;
        }

        if(pthread_create(&system_thread, NULL, system_thread_func, NULL) > 0)
        {
            perror("pthread_create");
            return 1;
        }

        if(pthread_join(account1_thread, &account1_rtn) > 0)
        {
            perror("pthread_join");
            return 1;
        }

        if(pthread_join(account2_thread, &account2_rtn) > 0)
        {
            perror("pthread_join");
            return 1;
        }

        if(pthread_join(account3_thread, &account3_rtn) > 0)
        {
            perror("pthread_join");
            return 1;
        }

        if(pthread_join(system_thread, &system_rtn) > 0)
        {
            perror("pthread_join");
            return 1;
        }
    }

    return 0;
}