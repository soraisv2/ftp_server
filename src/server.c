/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-victor.sorais
** File description:
** main
*/

#include "../include/myftp.h"

int socketErr(const int errStep, int returnValue)
{
    switch (errStep)
    {
    case 100:
        printf("Error: Creation of server's fd failed");
        break;
    case 101:
        printf("Error in argument: There is only one argv accepted.\r\n=> ./myftp [PORT] or [-help]\r\n");
        break;
    case 102:
        printf("Connexion Failed\r\n");
        break;
    default:
        break;
    }
    return returnValue;
}

int create_socket_server(int port)
{
    int socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int option = 1;
    struct sockaddr_in server;
    if (socketFd == 0 || socketFd == -1) {
        socketErr(100, 84);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    bind(socketFd, (struct sockaddr *) &server, sizeof(server));

    return (socketFd);
}

void server_loop(int socketFd)
{
    int socketFdclient;
    struct sockaddr_in client;
    int size = sizeof(client);
    fd_set read_fd;
    fd_set tmp;
    FD_ZERO(&read_fd);
    FD_SET(socketFd, &read_fd);
    void *addrClient = (struct sockaddr *) &client;
    void *addrSize = (socklen_t *) &size;
    liste_t *liste = initList();
    while (1)
    {
        tmp = read_fd;
        if(select(FD_SETSIZE, &tmp, NULL, NULL, NULL) >= 1) {
            for (int fd = 0; fd != FD_SETSIZE; fd++) {
                if (FD_ISSET(fd, &tmp)) {
                    if (fd == socketFd) {
                        socketFdclient = accept(socketFd, addrClient, addrSize);
                        if (socketFdclient >= 0) {
                            createDbUser(liste, ++liste->block->id, fd);
                            dprintf(socketFdclient, "220 server connected\r\n");
                            FD_SET(socketFdclient, &read_fd);
                            printf("New client onnected...\r\n");
                        } else
                            socketErr(102, 84);
                    } else {
                        char buff[256] = {0};
                        int ret = read(fd, buff, 255);
                        if (ret == 0)
                            FD_CLR(fd, &read_fd);
                        buff[ret] = '\0';
                        printf("%d: %s\n",fd,  buff);
                        getClientRet(buff, socketFdclient, liste, fd);
                    }}}}}
}