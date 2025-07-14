#include <fcntl.h>
#include <stdio.h>
#include <mqueue.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    mqd_t mqd;
    char *receiving_msg;
    struct mq_attr attr;
    unsigned int msg_prio = 0;
    unsigned int bytes_read;

    mqd = mq_open("/posix_queue", O_RDONLY | O_NONBLOCK);
    if (mqd == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    if (mq_getattr(mqd, &attr) == -1) {
        perror("mq_getattr");
        mq_close(mqd);
        exit(EXIT_FAILURE);
    }

    receiving_msg = malloc(attr.mq_msgsize + 1);
    if (!receiving_msg) {
        perror("malloc");
        mq_close(mqd);
        exit(EXIT_FAILURE);
    }

    printf("Reading messages (non-blocking)...\n");

    while (1) {
        bytes_read = mq_receive(mqd, receiving_msg, attr.mq_msgsize + 1, &msg_prio);
        if(bytes_read >= 0)
        {
            receiving_msg[bytes_read] = '\0'; // Null-terminate the message
            printf("Received (prio %u): %s\n", msg_prio, receiving_msg);
        }
        else 
        {
            if (errno == EAGAIN) {
                // No more messages to read in non-blocking mode
                break;
            } else {
                perror("mq_receive");
                break;
            }
        }
    }

    free(receiving_msg);
    if (mq_close(mqd) == -1) {
        perror("mq_close");
        exit(EXIT_FAILURE);
    }
    return 0;
}
