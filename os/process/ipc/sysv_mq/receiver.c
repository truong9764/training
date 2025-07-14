#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg {
    long msg_type;
    char msg_text[1024];
};

int main()
{
    int msqid, flags;
    key_t key = ftok("keyfile", 10);
    struct msg receiving_msg;

    printf("Key: %d\n", key);

    msqid = msgget(key, 0666);
    printf("IPC identifier: %d\n", msqid);

    receiving_msg.msg_type = 0;
    flags = 0;
    flags |= IPC_NOWAIT;

    msgrcv(msqid, &receiving_msg, sizeof(receiving_msg.msg_text), receiving_msg.msg_type, flags);
    printf("Receiving message: %s", receiving_msg.msg_text);

    // to destroy the message queue
    msgctl(msqid, IPC_RMID, NULL);

    return 0;
}