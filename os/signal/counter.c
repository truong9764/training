#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int paused = 0;
static int counter_value = 1;
void count(int value)
{
    while(counter_value <= value)
    {
        if(paused == 0)
        {
            printf("Counter value: %d\n", counter_value);
            sleep(1);
            counter_value++;
        }
    }
}

void sigint_handler(int arg)
{
    paused = 1;

    char confirmation;
    printf("Do you really want to exit? (y/n): ");
    scanf("%c", &confirmation);

    if(confirmation == 'y'){
        exit(0);
    }

    paused = 0;
}

void sigterm_handler(int arg)
{
    printf("Received terminate signal");
    exit(0);
}

void sigpause_handler(int arg)
{
    paused = 1;
}

void sigresume_handler(int arg)
{
    paused = 0;
}

void sigreset_handler(int arg)
{
    counter_value = 1;
}

int main(int argc, char* argv[])
{
    int value;
    printf("Process id: %d\n", getpid());

    if(argc < 2)
    {
        printf("Missing counter value argument\n");
        return 1;
    }
    
    if(argc == 2)
    {
        value = atoi(argv[1]);
        printf("Start counting from 1 to %d\n", value);
        if(atoi(argv[1]) < 1)
        {
            printf("Invalid counter value\n");
            return 1;
        }
    }
    
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);
    signal(SIGUSR1, sigpause_handler);
    signal(SIGUSR2, sigresume_handler);

    count(value);

    return 0;
}