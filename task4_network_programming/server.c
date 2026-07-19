#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#define PORT 8080
void *handleClient(void *socketDesc)
{
    int clientSocket = *(int *)socketDesc;
    free(socketDesc);
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("Client says: %s\n", buffer);
    char reply[] = "Message received by server.";
    send(clientSocket, reply, strlen(reply), 0);
    close(clientSocket);
    printf("Client disconnected.\n");
    return NULL;
}
int main()
{
    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        printf("Socket creation failed.\n");
        return 1;
    }
    printf("Socket created successfully.\n");
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        printf("Bind failed.\n");
        return 1;
    }
    printf("Bind successful.\n");
    if (listen(serverSocket, 5) < 0)
    {
        printf("Listen failed.\n");
        return 1;
    }
    printf("Server listening on port %d...\n", PORT);
    while (1)
    {
        addrSize = sizeof(clientAddr);
        int *clientSocket = malloc(sizeof(int));
        *clientSocket = accept(serverSocket,
                               (struct sockaddr *)&clientAddr,
                               &addrSize);
        if (*clientSocket < 0)
        {
            printf("Accept failed.\n");
            free(clientSocket);
            continue;
        }
        printf("New client connected.\n");
        pthread_t tid;
        pthread_create(&tid, NULL, handleClient, clientSocket);
        pthread_detach(tid);
    }
    close(serverSocket);
    return 0;
}
