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
    if (argc != 3)
    {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        error_handling("socket() error");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        error_handling("connect() error");
    }

    while (1)
    {
        printf("Input message (type 'close' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin);

        if (!strcmp(buffer, "close\n"))
        {
            write(sock, "close", 5);
            break;
        }

        write(sock, buffer, strlen(buffer));
        int str_len = read(sock, buffer, BUFFER_SIZE - 1);
        if (str_len == -1)
        {
            error_handling("read() error");
        }

        buffer[str_len] = 0;
        printf("Message from server: %s\n", buffer);
    }

    close(sock);
    return 0;
}
