This code is a simple UDP client written in C. It allows the user to send messages to a specified IP address and port. Here is a breakdown of the code:

### Includes and Definitions
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
```
These lines include the necessary headers for input/output operations, memory manipulation, network programming, and standard symbolic constants and types. `BUFFER_SIZE` is defined as 1024, which is the size of the buffer used for sending messages.

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
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
```
These variables are declared:
- `sockfd`: the socket file descriptor.
- `server_addr`: a structure to hold the server address.
- `buffer`: an array to store the message to be sent.

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

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip_address);
```
The `server_addr` structure is zeroed out and then filled with the appropriate values:
- `sin_family` is set to `AF_INET` (IPv4).
- `sin_port` is set to the specified port (converted to network byte order using `htons`).
- `sin_addr.s_addr` is set to the specified IP address (converted using `inet_addr`).

### Main Loop
```c
    while (1)
    {
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character

        sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));

        if (strcmp(buffer, "exit") == 0)
        {
            break;
        }
    }
```
This loop continuously prompts the user to enter a message. The message is read into the buffer, and the newline character (if any) is removed. The message is then sent to the server using `sendto`. If the user types "exit", the loop breaks.

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
- It continuously reads messages from the user and sends them to the specified server.
- The loop stops when the user types "exit".
- Finally, it closes the socket and exits.