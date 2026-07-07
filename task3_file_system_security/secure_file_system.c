#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define USERNAME "sarinabatas"
#define PASSWORD "janakjanuka@18"
int authenticated = 0;
void login()
{
    char username[50];
    char password[50];
    printf("Username: ");
    scanf("%30s", username);
    printf("Password: ");
    scanf("%30s", password);
    if (strcmp(username, USERNAME) == 0 &&
        strcmp(password, PASSWORD) == 0)
    {
        authenticated = 1;
        printf("\nLogin Successful!\n");
    }
    else
    {
        printf("\nInvalid Username or Password!\n");
    }
}
int main()
{
    int choice;
    while (1)
    {
        printf(" Secure File Management System\n");
        printf("1. Login\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                login();
                break;
            case 2:
                printf("Exit from here\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
