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
    int board[HOUSE_PER_PLAYER * 2];
    int score1;
    int score2;
    int currentPlayer; // 1 or 2
} Awale;

// --- Prototypes de fonctions ---
void initializeBoard(Awale *g);
void printBoard(const Awale *g, int player);
void playMove(Awale *jeu, int houseIndex);
int endGame(const Awale *jeu);

#endif // AWALE_H
