#ifndef SERVERGAME_H
#define SERVERGAME_H

// --- Includes ---
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#include "server2.h"
#include "client2.h"
#include "../Awale.h"

typedef struct {
    Client* player1;
    Client* player2;
    Client spectators[MAX_CLIENTS];
    int nbSpectators;
} GameArgs;

void playGame(Client *player1, Client *player2, Client *spectators, int nbSpectators);
void *gameThread(void *arg);


#endif