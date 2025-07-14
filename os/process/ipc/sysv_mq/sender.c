#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct msg {
    long msg_type;
    char msg_text[1024];
};

int main()
{
    int msqid, flags;
    key_t key = ftok("keyfile", 10);
    struct msg sending_msg;

    printf("Key: %d\n", key);

    msqid = msgget(key, 0666 | IPC_CREAT);
    printf("IPC identifier: %d\n", msqid);

    sending_msg.msg_type = 1;
    snprintf(sending_msg.msg_text, 1024, "Hello from process %d", getpid());

    flags = 0;
    flags |= IPC_NOWAIT;
    printf("Sending message: %s\n", sending_msg.msg_text);
    msgsnd(msqid, &sending_msg, sizeof(sending_msg.msg_text), flags);

    return 0;
}