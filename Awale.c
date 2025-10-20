#include "Awale.h" // Inclure le header correspondant
#include <math.h>  // Autres bibliothèques nécessaires

void initializeBoard(Game *g)
{
    int board[HOUSE_PER_PLAYER * 2];
    for (int i = 0; i < 12; i++)
    {
        board[i] = SEEDS_PER_HOUSE;
    }
    g->board = board;
}
