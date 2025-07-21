#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/* Demonstrate usage of signal()

    void (*signal(int sig, void (*handler)(int)) (int)

    sig: identidfies the signal whose disposition we wish to change
    handler: address of the function that should be called when this signal is delivered. This function return nothing and take an int as an arg

    return: previous disposition of the signal 
*/


void handler_1st(int arg)
{
    if(arg == -1)
    {
        printf("1st handler is removed\n");
    }
    else {
        printf("1st handler\n");
    }
}

void handler_2nd(int arg)
{
    if(arg == -1)
    {
        printf("2nd handler is removed\n");
    }
    else {
        printf("2nd handler\n");    
    }
}

int main(int argc, char *argv[])
{
    int sig = SIGINT;
    int option = 0;
    void (*old_handler)(int);

    printf("%s is running with pid %d\n", argv[0], getpid());

    while(1)
    {
        printf("0. Default handler\n"  
            "1. Hanlder 1st\n"
            "2. Handler 2nd\n"
            "3. Ignore signal\n");
        printf("Enter option: ");
        if(scanf("%d", &option) != 1)
        {
            fprintf(stderr, "Invalid input!\n");
            continue;
        }

        switch (option)
        {
            case 0:
                /* reset handler of the signal to default */
                if(signal(sig, SIG_DFL) == SIG_ERR)
                {
                    perror("signal");
                    return 1;
                }
                break;
            case 3:
                /* Ignore the signal. If the signal is generated for this process, the kernel silently discard it*/
                if(signal(sig, SIG_IGN) == SIG_ERR)
                {
                    perror("signal");
                    return 1;
                }
                break;
            case 1:
                /* replace new handler for the signal*/
                old_handler = signal(sig, handler_1st);         
                if(old_handler == SIG_ERR)
                {
                    perror("signal");
                    return 1;
                }

                if(old_handler != SIG_DFL && old_handler != SIG_IGN)
                {
                    old_handler(-1);
                }

                break;
            case 2:
                /* replace new handler for the signal*/
                old_handler = signal(sig, handler_2nd);
                if(old_handler == SIG_ERR)
                {
                    perror("signal");
                    return 1;
                }

                if(old_handler != SIG_DFL && old_handler != SIG_IGN)
                {
                    old_handler(-1);
                }

                break;
        }
    }
    
    return 0;
}
