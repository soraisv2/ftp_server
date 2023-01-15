/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-victor.sorais
** File description:
** command
*/

#include "../include/myftp.h"

void user(int fdClient, char *value, liste_t *db, int i, char *cmd)
{
    if (strcmp(value, "Anonymous") == 0 && !db->block->isConnected && !db->block->isWait) {
        write(i, "331 user-name: ok.\r\n", strlen("331 user-name: ok.\r\n"));
        db->block->name = malloc(sizeof(char) * strlen(value));
        strcpy(db->block->name, value);
        db->block->isWait = true;

        printf("id: [%i] with name -> %s try to connect...\n",
        db->block->id ,db->block->name);
    }
    else if (!db->block->isConnected && !db->block->isWait)
        write(i, "331 USER\r\n", strlen("331 USER\r\n"));
    else
        dprintf(fdClient,
        "User name allready in waiting for connexion\r\n");
}

void pass(int fdClient, char *value, liste_t *db, int i)
{
    if (strcmp(value, "PASS") == 0 && db->block->isWait
    && !db->block->isConnected) {
        printf("230 PASS\r\n");
        db->block->pass = NULL;
        db->block->isConnected = true;
        printf("User name -> %s connected\r\n", db->block->name);
        write (i, "230 user connected\r\n",
        strlen("230 user connected\r\n"));
        db->block->isConnected = true;
    }
    else if (!db->block->isConnected)
        write (i, "530 error in user-name", strlen("530 error in user-name"));
    else if (db->block->isWait && db->block->name == NULL) {
        write (i, "Need the user-name for login",
        strlen("Need the user-name for login"));
    }
    else
        write(i, "User Already connected\r\n",
        strlen("User Already connected\r\n"));
}

void quit(int fdClient, liste_t *db, int i)
{
    printf("221 QUIT %s disconnected.\n", db->block->name);
    dprintf(fdClient, "221 Disconnection...\r\n");
    db->block->isConnected = false;
    close(fdClient);
}

void help(int fdClient, int i)
{
    dprintf(fdClient, "214 USER <username> : Specify user for login\r\n");
    dprintf(fdClient, "214 PASS <password> : Specify password for login\r\n");
    dprintf(fdClient, "214 QUIT            : Disconnection\r\n");
    dprintf(fdClient, "214 HELP            : List of available commands\r\n\n");
}

void getClientPwd(int fdClient)
{
    char *activePath = getcwd(NULL, 0);
    dprintf(fdClient, "257 %s\r\n", activePath);
}