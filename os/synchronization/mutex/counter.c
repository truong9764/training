/* Thread-Safe Counter */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define VALUE   50
static int counter_value;
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void* counter1_func(void* args)
{
    int* rtn = malloc(sizeof(int));
    *rtn = 0;

    printf("thread 1 is running\n");

    while(counter_value < VALUE)
    {
        /*Enter critical section */
        if(pthread_mutex_lock(&counter_mutex))
        {
            perror("pthread_mutex_lock");
            *rtn = -1;
            return rtn;
        }

        counter_value++;
        printf("Counter value: %d\n", counter_value);
        
        /*Exit critical section */
        if(pthread_mutex_unlock(&counter_mutex))
        {
            perror("pthread_mutex_unlock");
            *rtn = -1;
            return rtn;
        }

        sleep(1);
    }
}

void* counter2_func(void* args)
{
    int* rtn = malloc(sizeof(int));
    *rtn = 1;
    
    printf("thread 2 is running\n");

    while(counter_value < VALUE)
    {
        /*Enter critical section */
        if(pthread_mutex_lock(&counter_mutex))
        {
            perror("pthread_mutex_lock");
            *rtn = -1;
            return rtn;
        }

        counter_value++;
        printf("Counter value: %d\n", counter_value);

        /*Exit critical section */
        if(pthread_mutex_unlock(&counter_mutex))
        {
            perror("pthread_mutex_unlock");
            *rtn = -1;
            return rtn;
        }

        sleep(1);
    }
    
    return rtn;
}

int main(){

    pthread_t counter1_thread;
    pthread_t counter2_thread;

    void* counter1_thread_rtn;
    void* counter2_thread_rtn;

    if(pthread_create(&counter1_thread, NULL, counter1_func, NULL) > 0)
    {
        perror("thread_create");
        return 1;
    }

    if(pthread_create(&counter2_thread, NULL, counter2_func, NULL) > 0)
    {
        perror("thread_create");
        return 1;
    }

    if(pthread_join(counter1_thread, &counter1_thread_rtn) > 0)
    {
        perror("thread_join");
        return 1;
    }

    if(pthread_join(counter2_thread, &counter2_thread_rtn) > 0)
    {
        perror("thread_join");
        return 1;
    }

    return 0;

}