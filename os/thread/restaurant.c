#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_salad_func(void* args)
{
    int* status = malloc(sizeof(int));
    sleep(10);

    *status = 1;
    if(*status == 1)
    {
        printf("Salad ready\n");
    }
    
    return status;
}

void* thread_pasta_func(void* args)
{
    int* status = malloc(sizeof(int));
    sleep(8);

    *status = 1;
    if(*status == 1)
    {
        printf("Pasta ready\n");
    }

    return status;
}

void* thread_dessert_func(void* args)
{
    int* status = malloc(sizeof(int));
    sleep(5);

    *status = 1;
    if(*status == 1)
    {
        printf("Dessert ready\n");
    }

    return status;
}

int main()
{
    void* salad_status;
    void* pasta_status;
    void* dessert_status;

    pthread_t thread_salad;
    pthread_t thread_pasta;
    pthread_t thread_dessert;
    
    printf("Start prepare pasta and salad!\n");

    if(pthread_create(&thread_pasta, NULL, thread_pasta_func, NULL) > 0)
    {
        perror("thread_pasta creation");
        return 1;
    }

    if(pthread_create(&thread_salad, NULL, thread_salad_func, NULL) > 0)
    {
        perror("thread_salad creation");
        return 1;
    }

    if(pthread_join(thread_pasta, &pasta_status) > 0)
    {
        perror("thread_pasta joining");
        return 1;
    }

    if(pthread_join(thread_salad, &salad_status) > 0)
    {
        perror("thread_pasta joining");
        return 1;
    }

    if(((*(int*)salad_status) | (*(int*)pasta_status)) == 1)
    {
        printf("Start serving pasta and salad!\n");
        printf("Start prepare dessert!\n");
        if(pthread_create(&thread_dessert, NULL, thread_dessert_func, NULL) > 0)
        {
            perror("thread_dessert creation");
            return 1;
        }

        if(pthread_join(thread_dessert, &dessert_status) > 0)
        {
            perror("thread_pasta joining");
            return 1;
        }

        if((*(int*)dessert_status) == 1)
        {
            printf("Start serving dessert!\n");
            sleep(10);
            printf("Finished\n");
        }
    }
    else {
        printf("Salad and pasta are not ready\n");
    }

    return 0;
}