#include <stdio.h>
#include <string.h>
#include <fcntl.h> 
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define ERROR_FIFO_CREATING_MSG         "Fifo creating fail\n"
#define ERROR_FIFO_OPENNING_MSG         "Fifo openning fail\n"
#define HELLO_MSG_TEMPLATE              "Hello server from client " 

#define CLIENT_FIFO_TEMPLATE            "./client_fifo_"
#define SERVER_FIFO                     "./server_fifo"

int main()
{
    int client_id = 1001;
    int server_fd = 0;
    int client_fd = 0;
    int idx = 0;
    char server_msg[1000];
    char client_fifo_path[100];
    char hello_msg[100];

    memset(server_msg, 0, sizeof(server_msg));
    memset(client_fifo_path, 0, sizeof(client_fifo_path));
    memset(hello_msg, 0, sizeof(hello_msg));
    
    sprintf(client_fifo_path, CLIENT_FIFO_TEMPLATE"%d", client_id);      /*get name of the client fifo*/
    sprintf(hello_msg, HELLO_MSG_TEMPLATE"%d", client_id);

    if(access(client_fifo_path, R_OK) == -1)
    {   
        printf(ERROR_FIFO_OPENNING_MSG "Create new one: %s\n", client_fifo_path);
        if(mkfifo(client_fifo_path, 0660) == -1)                        /*Create client fifo*/
        {
            perror(ERROR_FIFO_CREATING_MSG);
            return 1;
        }
    }

    server_fd = open(SERVER_FIFO, O_WRONLY);                        /*Open server fifo*/
    if(server_fd == -1)
    {
        perror(ERROR_FIFO_OPENNING_MSG);
        return 1;
    }

    client_fd = open(client_fifo_path, O_RDWR);                    /*Open client fifo*/
    if(client_fd == -1)                                                          
    {
        perror(ERROR_FIFO_OPENNING_MSG);
        return 1;
    }

    write(server_fd, hello_msg, strlen(hello_msg));   /*send message to server by writing to server fifo*/
    idx = read(client_fd, server_msg, 1000);                                /*receive message from server by reading this client buffer*/

    server_msg[idx] = '\0';
    printf("Server message: %s", server_msg); 

    unlink(client_fifo_path );
    return 0;
}