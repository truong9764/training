#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    mqd_t mqd;
    struct mq_attr attr;
    char sending_msg[100];
    int i;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    attr.mq_curmsgs = 0;
    mqd = mq_open("/posix_queue", O_CREAT | O_WRONLY, 0666, &attr);
    if (mqd == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    snprintf(sending_msg, 100, "Hello from process %d", getpid());

    for(i = 0; i < 10; i++)
    {
        mq_send(mqd, sending_msg, strlen(sending_msg) + 1, i);
    }

    mq_close(mqd);

    return 0;
}
