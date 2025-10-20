#include "Awale.h" // Inclure le header correspondant
#include <math.h>  // Autres bibliothèques nécessaires

void initializeGame(Awale *g)
{
    for (int i = 0; i < HOUSE_PER_PLAYER * 2; i++)
    {
        g->board[i] = SEEDS_PER_HOUSE;
    }
    g->score1 = 0;
    g->score2 = 0;
    g->currentPlayer = 1;
}
