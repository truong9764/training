#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

const char error_socket_creating_msg[] = "Socket creating fail";
const char error_socket_binding_msg[] = "Socket binding fail";
const char hello_msg[] = "Hello from UNIX server";

static int server_fd;
static struct sockaddr_un server_addr;

#define SERVER_SOCKET "./streamsocket"

int init_server()
{
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);    /*Open a socket*/
    if(server_fd == -1)
    {
        perror(error_socket_creating_msg);
        return -1;
    }

    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SERVER_SOCKET, sizeof(server_addr.sun_path) - 1);

    if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        perror(error_socket_binding_msg);
        return -1;
    }

    return 0;
}

int server_start()
{

    int client_fd = 0;
    char receiving_msg[1024];

    listen(server_fd, 10);
    printf("Server listening on UNIX socket ... \n");

    while(1)
    {
        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd == -1)
        {
            perror("Accept fail\n");
            return -1;
        }

        printf("Accepted client %d\n", client_fd);

        /* Client send message to server */
        recv(client_fd, receiving_msg, 1024, 0);
        printf("Receiving message: %s\n", receiving_msg);

        /* Server send message to client */
        send(client_fd, hello_msg, strlen(hello_msg), 0);

        close(client_fd);
    }

    return 0;
}

int server_close()
{
    close(server_fd);
    remove(SERVER_SOCKET);

    return 0;
}

int main()
{
    if(init_server() == -1)
    {
        perror("Initialised server fail\n");
        close(server_fd);
        remove(SERVER_SOCKET);
        return 1;
    }

    server_start();
    server_close();

    return 0;
}