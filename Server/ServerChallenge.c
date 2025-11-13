#include "ServerChallenge.h"

void challengeUser(Client *clients, Client sender, int actual, const char *targetName)
{
    char message[BUF_SIZE];
    int found = 0;

    for (int j = 0; j < actual; j++)
    {
        if (strcmp(clients[j].name, targetName) == 0)
        {
            if (strcmp(clients[j].name, sender.name) == 0)
            {
                snprintf(message, BUF_SIZE,
                         " You can't challenge yourself. Challenge another person.");
                write_client(sender.sock, message);
                return;
            }
            if (clients[j].inGame)
            {
                snprintf(message, BUF_SIZE,
                         " %s is already in game. Challenge another person.", clients[j].name);
                write_client(sender.sock, message);
                return;
            }
            if (clients[j].challengedBy[0] != '\0')
            {
                snprintf(message, BUF_SIZE, "%s already has a pending challenge.\n", clients[j].name);
                write_client(sender.sock, message);
                return;
            }
            snprintf(message, BUF_SIZE,
                     " %s challenged you to an Awale game!\n To accept his challenge, please type {/accept %s} in your terminal. \n If you want to decline his invitation, please type {/refuse %s}.", sender.name, sender.name, sender.name);
            write_client(clients[j].sock, message);

            strncpy(clients[j].challengedBy, sender.name, BUF_SIZE / 4 - 1);
            found = 1;
            snprintf(message, BUF_SIZE,
                     " Waiting for a response.");
            write_client(sender.sock, message);
            break;
        }
    }

    if (!found)
    {
        snprintf(message, BUF_SIZE,
                 "Error : User '%s' not found or not connected.\n", targetName);
        write_client(sender.sock, message);
    }
}

void acceptChallenge(Client *clients, Client *accepter, int actual, const char *fromName)
{
    char message[BUF_SIZE];
    int found = 0;

    for (int j = 0; j < actual; j++)
    {
        if (strcmp(clients[j].name, fromName) == 0)
        {
            // Vérifie que c’est bien la personne qui l’a challengé
            if (strcmp(accepter->challengedBy, fromName) != 0)
            {
                snprintf(message, BUF_SIZE,
                         "No pending challenge from %s.\n", fromName);
                write_client(accepter->sock, message);
                return;
            }
            snprintf(message, BUF_SIZE,
                     "%s accepted your invitation! The game will now begin !\n", accepter->name);
            write_client(clients[j].sock, message);

            snprintf(message, BUF_SIZE,
                     "You accepted %s’s invitation.  The game will now begin !\n", fromName);
            write_client(accepter->sock, message);

            Client spectators[0];
            // playGame(&accepter, &clients[j], spectators, 0);
            GameArgs *args = malloc(sizeof(GameArgs));
            args->player1 = accepter;
            args->player2 = &clients[j];
            args->nbSpectators = 0; // pour le moment

            accepter->inGame = 1;
            clients[j].inGame = 1;

            accepter->challengedBy[0] = '\0';
            clients[j].challengedBy[0] = '\0';

            pthread_t thread;
            pthread_create(&thread, NULL, gameThread, args);
            pthread_detach(thread); // détaché pour ne pas bloquer le serveur

            found = 1;
            break;
        }
    }

    if (!found)
    {
        snprintf(message, BUF_SIZE,
                 "User '%s' not found.\n", fromName);
        write_client(accepter->sock, message);
    }
}

void refuseChallenge(Client *clients, Client *refuser, int actual, const char *fromName)
{
    char message[BUF_SIZE];
    int found = 0;

    for (int j = 0; j < actual; j++)
    {
        if (strcmp(clients[j].name, fromName) == 0)
        {
            // Vérifie que c’était bien un défi valide
            if (strcmp(refuser->challengedBy, fromName) != 0)
            {
                snprintf(message, BUF_SIZE,
                         "No pending challenge from %s.\n", fromName);
                write_client(refuser->sock, message);
                return;
            }
            snprintf(message, BUF_SIZE,
                     "%s declined your invitation. Try to challenge another player !\n", refuser->name);
            write_client(clients[j].sock, message);

            snprintf(message, BUF_SIZE,
                     "You declined %s’s invitation.\n", fromName);
            write_client(refuser->sock, message);

            refuser->challengedBy[0] = '\0';
            clients[j].challengedBy[0] = '\0';

            found = 1;
            break;
        }
    }

    if (!found)
    {
        snprintf(message, BUF_SIZE,
                 "User '%s' not found.\n", fromName);
        write_client(refuser->sock, message);
    }
}
