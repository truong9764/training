#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    pid = fork();

    if(pid < 0)
    {
        perror("fork error");
        return 1;
    }
    else if(pid == 0)
    {
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        exit(0);
    }
    else 
    {
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
        while(1);
    }

    return 0;
}