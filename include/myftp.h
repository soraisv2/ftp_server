/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-victor.sorais
** File description:
** myftp
*/

#ifndef MYFTP_H_
#define MYFTP_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <stdbool.h>

#define PORT 8080
#define NB_CONNEXION 5

typedef struct node_s node_t;
struct node_s {
    node_t *next;

    char *name;
    char *pass;
    bool isWait;
    bool isConnected;
    int socketClient;
    int id;
};

typedef struct liste_s liste_t;
struct liste_s {
    node_t *block;
};

int helper();
void getClientRet(char *, int, liste_t *, int);
int create_socket_server(int);
void server_loop(int);
int socketErr(const int, int);
void user(int, char *, liste_t *, int, char *);
void pass(int, char *, liste_t *, int);
void quit(int, liste_t *, int);
void help(int, int);
void sendCmd(char *, char *, int, liste_t *, int);
liste_t *initList();
void createDbUser(liste_t *, int, int);
void getClientPwd(int);

#endif
