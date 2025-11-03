#ifndef AWALE_H
#define AWALE_H

// --- Includes ---
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// --- Définitions de constantes ou macros ---
#define SEEDS_PER_HOUSE 4
#define HOUSE_PER_PLAYER 6
#define BUF_SIZE 4096

// --- Déclarations de types ou structures ---
typedef struct
{
    int board[HOUSE_PER_PLAYER * 2];
    int score1;
    int score2;
    int currentPlayer; // 1 or 2
    int end;
} Awale;

// --- Prototypes de fonctions ---
void initializeBoard(Awale *g);
char *printBoard(const Awale *g, int player);
void playMove(Awale *game, int houseIndex);
void endGame(Awale *game);

#endif // AWALE_H
