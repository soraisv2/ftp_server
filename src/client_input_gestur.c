/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-victor.sorais
** File description:
** client_input_gestur
*/

#include "../include/myftp.h"

void noop(int fd)
{
    dprintf(fd, "200 noop, nothing.\r\n");
}

void sendCmd(char *cmd, char *value, int fdClient, liste_t *liste, int i)
{
    if (strcmp(cmd, "USER") == 0){
        user(fdClient, value, liste, i, cmd);
    }
    if (strcmp(cmd, "PASS") == 0){
        pass(fdClient, cmd, liste, i);
    }
    else if (strcmp(cmd, "HELP") == 0)
        help(fdClient, i);
    else if (strcmp(cmd, "QUIT") == 0)
        quit(fdClient, liste, i);
    else if (strcmp(cmd, "PWD") == 0)
        getClientPwd(fdClient);
    else if (strcmp(cmd, "NOOP") == 0)
        noop(fdClient);
}

void getClientRet(char *buff, int fdClient, liste_t *liste, int i)
{
    char cmd[255] = {0}, value[255] = {0};
    bool is = false, isPassCmd = false;
    int p = 0, k = 0;
    for (; buff[p] != '\0'; p++) {
        if (buff[p] == 32) {
            is = true;
            continue;
        }
        if (!is)
            cmd[p] = buff[p];
        if (is) {
            if (strcmp(cmd, "PASS") == 0) {
                isPassCmd = true;
                break;
            }
            value[k++] = buff[p];
        }
    }
    if (value[k - 1] == '\n' && value[k - 2] == '\r')
        value[k - 2] = '\0';
    else if (cmd[p - 1] == '\n' && cmd[p - 2] == '\r')
        cmd[p - 2] = '\0';
    sendCmd(cmd, value, fdClient, liste, i);
}