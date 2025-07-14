#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd[2];
    int i;
    if(pipe(fd) == -1)
    {
        perror("fail to create pipe");
        return 1;
    }

    pid_t pid = fork();

    /*parent activity*/
    if(pid < 0)
    {
        perror("fork error");
        return 1;
    }
    else if(pid > 0)
    {
        close(fd[0]);
        for(i = 0; i < 100; i++)
        {
            write(fd[1], &i, sizeof(int));
            sleep(1);
        }
        close(fd[1]);
        
    }
    else /*child activity*/
    {
        close(fd[1]);
        int msg = 0;
        int j = 0;

        for(i = 0; i < 100; i++)
        {
            read(fd[0], &msg, sizeof(int));
            printf("%d\n", msg);
            fflush(stdout);
        }
        close(fd[0]);
    }

    return 0;
}