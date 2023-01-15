/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-victor.sorais
** File description:
** main
*/

#include "include/myftp.h"

int main(int ac, char **av)
{
    int socketFd;
    char *h = "-help";
    if (ac <= 3) {
        if (strcmp(av[1], h) == 0)
            helper();
        else if (atoi(av[1]) > 0) {
            socketFd = create_socket_server(atoi(av[1]));
            listen(socketFd, NB_CONNEXION);
            server_loop(socketFd);
        } else
            socketErr(101, 84);
    } else
        socketErr(101, 84);
    return (0); 
}