#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
int main()
{
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize;
    char buffer[1024] = {0};
    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        printf("Socket creation failed.\n");
        return 1;
    }
    printf("Socket created successfully.\n");
    // Server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    // Bind socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        printf("Bind failed.\n");
        return 1;
    }
    printf("Bind successful.\n");
    // Listen
    if (listen(serverSocket, 5) < 0)
    {
        printf("Listen failed.\n");
        return 1;
    }
    printf("Server listening on port %d...\n", PORT);
    addrSize = sizeof(clientAddr);
    // Accept one client
    clientSocket = accept(serverSocket,
                          (struct sockaddr *)&clientAddr,
                          &addrSize);
    if (clientSocket < 0)
    {
        printf("Accept failed.\n");
        return 1;
    }
    printf("Client connected.\n");
    // Receive message
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("Client says: %s\n", buffer);
    // Reply
    char message[] = "Hello Client!";
    send(clientSocket, message, strlen(message), 0);
    close(clientSocket);
    close(serverSocket);
    return 0;
}
