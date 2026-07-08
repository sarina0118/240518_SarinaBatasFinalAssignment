#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define USERNAME "sarinabatas"
#define PASSWORD "janakjanuka@18"
int authenticated = 0;
void login();
void createFile();
void writeFile();
void readFile();
void deleteFile();
// Login Function
void login()
{
    char username[50];
    char password[50];
    printf("Username: ");
    scanf("%50s", username);
    printf("Password: ");
    scanf("%50s", password);
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
// Create File
void createFile()
{
    if (!authenticated)
    {
        printf("Please login first!\n");
        return;
    }
    char filename[100];
    printf("Enter file name: ");
    scanf("%70s", filename);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error creating file!\n");
        return;
    }
    fclose(fp);
    printf("File created successfully.\n");
}
// Write File
void writeFile()
{
    if (!authenticated)
    {
        printf("Please login first!\n");
        return;
    }
    char filename[100];
    char text[500];
    printf("Enter file name: ");
    scanf("%99s", filename);
    FILE *fp = fopen(filename, "a");
    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }
    getchar(); 
    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    fprintf(fp, "%s", text);
    fclose(fp);
    printf("Data written successfully.\n");
}
// Read File
void readFile()
{
    if (!authenticated)
    {
        printf("Please login first!\n");
        return;
    }
    char filename[100];
    char ch;
    printf("Enter file name: ");
    scanf("%70s", filename);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }
    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }
    fclose(fp);
}
// Delete File
void deleteFile()
{
    if (!authenticated)
    {
        printf("Please login first!\n");
        return;
    }
    char filename[100];
    printf("Enter file name: ");
    scanf("%70s", filename);
    if (remove(filename) == 0)
        printf("File deleted successfully.\n");
    else
        printf("Unable to delete file.\n");
}
// Main Function
int main()
{
    int choice;
    while (1)
    {
        printf(" Secure File Management System\n");
        printf("1. Login\n");
        printf("2. Create File\n");
        printf("3. Write to File\n");
        printf("4. Read File\n");
        printf("5. Delete File\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                login();
                break;
            case 2:
                createFile();
                break;
            case 3:
                writeFile();
                break;
            case 4:
                readFile();
                break;
            case 5:
                deleteFile();
                break;
            case 6:
                printf("Exit from here\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
