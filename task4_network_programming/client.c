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
    char username[50];
    char password[50];
    char message[1024];
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
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0)
    {
        printf("Invalid server address.\n");
        close(clientSocket);
        return 1;
    }
    // Connect to server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        printf("Connection failed.\n");
        close(clientSocket);
        return 1;
    }
    printf("Connected to server.\n");
    // User Authentication
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);
    getchar(); // Clear newline
    // Enter Message
    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    // Validate message
    if (strlen(message) <= 1)
{
    printf("Message cannot be empty.\n");
    close(clientSocket);
    return 1;
}
    // Send username
    send(clientSocket, username, sizeof(username), 0);
    // Send password
    send(clientSocket, password, sizeof(password), 0);
    // Send message
    send(clientSocket, message, sizeof(message), 0);
    // Receive server reply
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);
    close(clientSocket);
    return 0;
}
