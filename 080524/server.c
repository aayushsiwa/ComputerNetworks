#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void error_handling(char *message)
{
    perror(message);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size;
    char buffer[BUFFER_SIZE];

    server_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (server_sock == -1)
    {
        error_handling("socket() error");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        error_handling("bind() error");
    }

    if (listen(server_sock, 5) == -1)
    {
        error_handling("listen() error");
    }

    client_addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_size);
    if (client_sock == -1)
    {
        error_handling("accept() error");
    }

    printf("Connected client IP: %s\n", inet_ntoa(client_addr.sin_addr));
    printf("Connected client port: %d\n", ntohs(client_addr.sin_port));

    while (1)
    {
        int str_len = read(client_sock, buffer, BUFFER_SIZE - 1);
        if (str_len == -1)
        {
            error_handling("read() error");
        }

        buffer[str_len] = 0;
        printf("Message from client: %s\n", buffer);

        if (strcmp(buffer, "close") == 0)
        {
            printf("Connection closed by client\n");
            break;
        }

        write(client_sock, buffer, str_len);
    }

    close(client_sock);
    close(server_sock);
    return 0;
}
