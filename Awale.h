#ifndef AWALE_H
#define AWALE_H

// --- Includes ---
#include <stdio.h>

// --- Définitions de constantes ou macros ---
#define SEEDS_PER_HOUSE 4
#define HOUSE_PER_PLAYER 6

// --- Déclarations de types ou structures ---
typedef struct
{
    int *board;
    int score1;
    int score2;
} Game;

// --- Prototypes de fonctions ---
void initializeBoard(Game *g);
void printBoard(const Game g);

#endif // AWALE_H
