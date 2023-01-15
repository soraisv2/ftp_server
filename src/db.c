/*
** EPITECH PROJECT, 2021
** B-NWP-400-NCE-4-1-myftp-victor.sorais
** File description:
** db
*/

#include "../include/myftp.h"

liste_t *initList()
{
    node_t *node = malloc(sizeof(*node));
    liste_t *liste = malloc(sizeof(*liste));
    if (liste == NULL)
        exit(EXIT_FAILURE);

    node->name = "admin";
    node->pass = "admin";
    node->id = 0;
    node->next = NULL;

    liste->block = node;

    return(liste);
}

void createDbUser(liste_t *liste, int id, int socket)
{
    node_t *newNode = malloc(sizeof(*newNode));
    if (newNode == NULL || liste == NULL)
        exit(EXIT_FAILURE);

    // data insertion
    newNode->id = id;
    newNode->socketClient = socket;
    newNode->next = NULL;

    // insertion de la node dans la liste
    while (liste->block->next != NULL) {
        liste->block = liste->block->next;
    }
    liste->block->next = newNode;

        // newNode->next = liste->block;
        // liste->block = newNode;
}