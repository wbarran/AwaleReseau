#ifndef SERVERCHALLENGE_H
#define SERVERCHALLENGE_H

// --- Includes ---
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#include "server2.h"
#include "client2.h"
#include "ServerGame.h"

void challengeUser(Client *clients, Client sender, int actual, const char *targetName);
void acceptChallenge(Client *clients, Client *accepter, int actual, const char *fromName);
void refuseChallenge(Client *clients, Client *refuser, int actual, const char *fromName);
#endif