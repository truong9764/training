#include <stdio.h>
#include <string.h>
#include <fcntl.h> 
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>


#define ERROR_FIFO_CREATING_MSG         "Fifo creating fail\n"
#define ERROR_FIFO_OPENNING_MSG         "Fifo openning fail\n"
#define HELLO_MSG                       "Hello client from UNIX server\n" 

#define CLIENT_FIFO_TEMPLATE            "./client_fifo_"
#define SERVER_FIFO                 "server_fifo"

int main()
{
    int server_fd = 0;
    int idx = 0;
    int client_id = 0;
    int client_fd = 0;
    char client_msg[100];
    char client_fifo_path[100];

    memset(client_msg, 0, sizeof(client_msg));
    memset(client_fifo_path, 0 ,sizeof(client_fifo_path));

    if(access(SERVER_FIFO, R_OK) == -1)
    {   
        printf(ERROR_FIFO_OPENNING_MSG " Create new one: " SERVER_FIFO "\n");
        if(mkfifo(SERVER_FIFO, 0660) == -1)     /*Create new server fifo*/
        {
            perror(ERROR_FIFO_CREATING_MSG);
            return 1;
        }
    }

    server_fd = open(SERVER_FIFO, O_RDWR);    /*Open server fifo*/
    if (server_fd == -1)                                    /*If fail to open*/
    {
        perror(ERROR_FIFO_OPENNING_MSG);
        return 1;   
    }

    printf("Server is running ... \n");

    while(1)
    {
        idx = read(server_fd, client_msg, 100);     /*Receive message from client by reading server fifo*/
        if(idx > 0) 
        {
            sscanf(client_msg, "Hello server from client %d", &client_id);
            client_msg[idx] = '\0';
            printf("Client's message: %s\n", client_msg);
            //printf("Client %d sent message\n", client_id);
        
            sprintf(client_fifo_path, CLIENT_FIFO_TEMPLATE"%d", client_id);

            client_fd = open(client_fifo_path, O_WRONLY);
            if(client_fd == -1)
            {
                perror(ERROR_FIFO_OPENNING_MSG);
                return 1;
            }
            
            write(client_fd, HELLO_MSG, strlen(HELLO_MSG));

            memset(client_msg, 0, sizeof(client_msg));

            close(client_fd);
        }
    }
    
    close(server_fd);
    unlink(SERVER_FIFO);

    return 0;
}