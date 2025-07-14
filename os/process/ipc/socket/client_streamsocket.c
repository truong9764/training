#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

const char error_socket_creating_msg[] = "Socket creating fail";
const char error_socket_connection_msg[] = "Connection fail";
const char hello_msg[] = "Hello from UNIX server";

int client_connect(const char server_socket[])
{
    int client_fd;
    struct sockaddr_un server_addr;

    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(client_fd == -1)
    {
        perror(error_socket_creating_msg);
        return -1;
    }

    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, server_socket, sizeof(server_addr.sun_path) - 1);

    if(connect(client_fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_un)) == -1)
    {
        perror(error_socket_connection_msg);
        return -1;
    }

    return client_fd;
}

int client_send(const char sending_msg[], int server_fd)
{
    int bytes_send;

    bytes_send = send(server_fd, sending_msg, strlen(sending_msg), 0);

    return 0;
}

// int client_receive(char receiving_msg[])
// {
//     int bytes_received;

//     bytes_received = recv(int , void *buf, size_t n, int flags)
// }

int main()
{
    char server_socket[1024];
    int server_fd = 0;
    char sending_msg[1024];
    char receiving_msg[1024];

    printf("Enter server address: ");
    if (fgets(server_socket, sizeof(server_socket), stdin) != NULL) {
        server_socket[strcspn(server_socket, "\n")] = '\0';
    }
    printf("Connecting to %s\n", server_socket);

    server_fd = client_connect(server_socket);
    if(server_fd == -1)
    {
        return 1;
    }

    printf("Enter sending message: ");
    fgets(sending_msg, 1024, stdin);

    client_send(sending_msg, server_fd);
    // client_receive(receiving_msg);
    

    return 0;
}