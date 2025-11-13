#ifndef CLIENT_H
#define CLIENT_H

#include "server2.h"

typedef struct
{
   SOCKET sock;
   char name[BUF_SIZE / 4];
   int inGame;
   char challengedBy[BUF_SIZE / 4];
} Client;

#endif /* guard */
