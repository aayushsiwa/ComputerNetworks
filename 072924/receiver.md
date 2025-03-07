This code is a simple UDP server written in C. It listens for messages from clients, prints received messages, and echoes them back to the sender. Here's a detailed explanation of each part of the code:

### Includes and Definitions
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
```
These lines include the necessary headers for input/output operations, memory manipulation, network programming, and standard symbolic constants and types. `BUFFER_SIZE` is defined as 1024, which is the size of the buffer used for receiving messages.

### Main Function
```c
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <IP Address> <Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *ip_address = argv[1];
    int port = atoi(argv[2]);
```
The `main` function checks if the correct number of arguments (IP address and port) are provided. If not, it prints the usage message and exits.

### Variable Declarations
```c
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);
```
These variables are declared:
- `sockfd`: the socket file descriptor.
- `server_addr`: a structure to hold the server address.
- `client_addr`: a structure to hold the client address.
- `buffer`: an array to store the message to be received.
- `addr_len`: a variable to hold the length of the client address structure.

### Create Socket
```c
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
```
A UDP socket is created using the `socket` function. If socket creation fails, an error message is printed, and the program exits.

### Configure Server Address
```c
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip_address);
```
The `server_addr` structure is zeroed out and then filled with the appropriate values:
- `sin_family` is set to `AF_INET` (IPv4).
- `sin_port` is set to the specified port (converted to network byte order using `htons`).
- `sin_addr.s_addr` is set to the specified IP address (converted using `inet_addr`).

### Bind Socket
```c
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
```
The socket is bound to the specified server address using the `bind` function. If binding fails, an error message is printed, the socket is closed, and the program exits.

### Main Loop
```c
    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);
        recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        printf("Received: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
        {
            break;
        }

        sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&client_addr, addr_len);
    }
```
This loop continuously listens for messages from clients:
- The buffer is cleared.
- A message is received using `recvfrom`, which stores the message in the buffer and the sender's address in `client_addr`.
- The received message is printed.
- If the message is "exit", the loop breaks.
- The message is echoed back to the sender using `sendto`.

### Clean Up
```c
    close(sockfd);
    return 0;
}
```
After exiting the loop, the socket is closed, and the program ends.

### Summary
- The program takes two command-line arguments: an IP address and a port number.
- It creates a UDP socket.
- It binds the socket to the specified server address.
- It continuously listens for messages from clients, prints them, and echoes them back to the sender.
- The loop stops when the received message is "exit".
- Finally, it closes the socket and exits.