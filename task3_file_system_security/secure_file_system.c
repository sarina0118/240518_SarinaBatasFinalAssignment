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
void viewAuditLog();
void logAction(const char *action);
void changePermissions();
void encryptFile();
void decryptFile();
//Audit Log 
void logAction(const char *action)
{
    FILE *log = fopen("audit.log", "a");
    if (log != NULL)
    {
        fprintf(log, "%s\n", action);
        fclose(log);
    }
}
//Login
void login()
{
    char username[50];
    char password[50];
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);
    if (strcmp(username, USERNAME) == 0 &&
        strcmp(password, PASSWORD) == 0)
    {
        authenticated = 1;
        printf("\nLogin Successful!\n");
        logAction("User logged in successfully.");
    }
    else
    {
        printf("\nInvalid Username or Password!\n");
        logAction("Failed login attempt.");
    }
}
//Create File
void createFile()
{
    if (!authenticated)
    {
        printf("Please login first!\n");
        return;
    }
    char filename[100];
    char action[200];
    printf("Enter file name: ");
    scanf("%99s", filename);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error creating file!\n");
        return;
    }
    fclose(fp);
    printf("File created successfully.\n");
    sprintf(action, "Created file: %s", filename);
    logAction(action);
}
//Write File
void writeFile()
{
    if (!authenticated)
    {
        printf("Please login first!\n");
        return;
    }
    char filename[100];
    char text[500];
    char action[200];
    printf("Enter file name: ");
    scanf("%99s", filename);
    FILE *fp = fopen(filename, "a");
    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }
    getchar(); // remove newline
    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    fprintf(fp, "%s", text);
    fclose(fp);
    printf("Data written successfully.\n");
    sprintf(action, "Wrote to file: %s", filename);
    logAction(action);
}
//Read File
void readFile()
{
    if (!authenticated)
    {
        printf("Please login first!\n");
        return;
    }
    char filename[100];
    char action[200];
    char ch;
    printf("Enter file name: ");
    scanf("%99s", filename);
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
    sprintf(action, "Read file: %s", filename);
    logAction(action);
}
//Delete File
void deleteFile()
{
    if (!authenticated)
    {
        printf("Please login first!\n");
        return;
    }
    char filename[100];
    char action[200];
    printf("Enter file name: ");
    scanf("%99s", filename);
    if (remove(filename) == 0)
    {
        printf("File deleted successfully.\n");
        sprintf(action, "Deleted file: %s", filename);
        logAction(action);
    }
    else
    {
        printf("Unable to delete file.\n");
    }
}
//View Audit Log 
void viewAuditLog()
{
    FILE *fp = fopen("audit.log", "r");
    if (fp == NULL)
    {
        printf("No audit log found.\n");
        return;
    }
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }
    fclose(fp);
}
void changePermissions()
{
    if (!authenticated)
    {
        printf("Please login first!\n");
        return;
    }
    char filename[100];
    char permission[10];
    char command[150];
    char action[200];
    printf("Enter file name: ");
    scanf("%99s", filename);
    printf("Enter permission (e.g. 644, 755, 777): ");
    scanf("%9s", permission);
    sprintf(command, "chmod %s %s", permission, filename);
    if (system(command) == 0)
    {
        printf("Permissions updated successfully.\n");
        sprintf(action, "Changed permissions of %s to %s", filename, permission);
        logAction(action);
    }
    else
    {
        printf("Failed to change permissions.\n");
    }
}
void encryptFile()
{
    if (!authenticated)
    {
        printf("Please login first!\n");
        return;
    }
    char filename[100];
    char action[200];
    char ch;
    printf("Enter file name: ");
    scanf("%99s", filename);
    FILE *fp = fopen(filename, "r+");
    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }
    while ((ch = fgetc(fp)) != EOF)
    {
        fseek(fp, -1, SEEK_CUR);
        fputc(ch ^ 123, fp);
        fflush(fp);
    }
    fclose(fp);
    printf("File encrypted successfully.\n");
    sprintf(action, "Encrypted file: %s", filename);
    logAction(action);
}
void decryptFile()
{
    if (!authenticated)
    {
        printf("Please login first!\n");
        return;
    }
    char filename[100];
    char action[200];
    char ch;
    printf("Enter file name: ");
    scanf("%99s", filename);
    FILE *fp = fopen(filename, "r+");
    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }
    while ((ch = fgetc(fp)) != EOF)
    {
        fseek(fp, -1, SEEK_CUR);
        fputc(ch ^ 123, fp);
        fflush(fp);
    }
    fclose(fp);
    printf("File decrypted successfully.\n");
    sprintf(action, "Decrypted file: %s", filename);
    logAction(action);
}
//Main
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
        printf("6. Change File Permissions\n");
        printf("7. Encrypt File\n");
        printf("8. Decrypt File\n");
        printf("9. View Audit Log\n");
        printf("10. Exit\n");
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
                changePermissions();
                break;
            case 7:
               encryptFile();
               break;
            case 8:
              decryptFile();
              break;
            case 9:
                viewAuditLog();
                break;
            case 10:
                printf("Exit from here\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
