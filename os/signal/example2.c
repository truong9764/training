#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* Demonstrate usage of kill()

    int kill(pid_t pid, int sig);

    pid: identifies one or more processes to which the signal specified by sig to be sent
        pid > 0: signal is sent to process with pid = pid
        pid = 0: signal is sent to every process in the same process group as the calling process
        pid < -1: signal is sent to all of the processes in the process group whose id = absolute value of pid
        pid = -1: signal is sent to every process for which the calling process has permission to send a signal, except init and the calling process

    return: -1 on error, 0 on success
*/

void sigint_handler(int arg)
{
    printf("Received SIGINT\n");
    exit(0);
}

int main(int argc, char* agrv[])
{

    pid_t pid;

    pid = fork();

    if(pid < 0)
    {
        perror("fork");
        return 1;
    }
    else if(pid > 0)    /* Parent activity*/
    {
        sleep(10);
        kill(pid, SIGINT);
        wait(NULL);
    }
    else {  /* Child activity*/
        signal(SIGINT, sigint_handler);
        
        while(1)
        {
            printf("Waiting for signal ... \n");
            sleep(1);
        }
    }

    return 0;
}