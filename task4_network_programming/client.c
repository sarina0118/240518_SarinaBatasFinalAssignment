#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
int main()
{
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024] = {0};
    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        printf("Socket creation failed.\n");
        return 1;
    }
    printf("Socket created successfully.\n");
    // Server information
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    // Connect to server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        printf("Connection failed.\n");
        return 1;
    }
    printf("Connected to server.\n");
    // Send message
    char message[1024];
    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    send(clientSocket, message, strlen(message), 0);
    // Receive reply
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("Server says: %s\n", buffer);
    close(clientSocket);
    return 0;
}
