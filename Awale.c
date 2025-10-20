#include "Awale.h" // Inclure le header correspondant
#include <math.h>  // Autres bibliothèques nécessaires

void initializeBoard(Awale *g)
{
    for (int i = 0; i < HOUSE_PER_PLAYER * 2; i++)
    {
        g->board[i] = SEEDS_PER_HOUSE;
    }
    g->score1 = 0;
    g->score2 = 0;
    g->currentPlayer = 1;
}

void printBoard(const int *board)
{
    printf("\nAwale\n");
    // board line one
    for (int i = 11; i > 5; i--)
    {
        printf(" %2d ", board[i]);
    }

    printf("\n");

    for (int i = 0; i < 6; i++)
    {
        printf(" %2d ", board[i]);
    }

    printf("\n");
    printf("  A   B   C   D   E   F");
    printf("\n");
}

int playMove(Awale *jeu, int houseIndex)
{
    // Adding one seed in the houses after the one selected
    int seedNumber = jeu->board[houseIndex];
    jeu->board[houseIndex] = 0;
    int currentHouse = (houseIndex + 1) % (HOUSE_PER_PLAYER * 2);
    for (int i = 1; i <= seedNumber; i++)
    {
        jeu->board[currentHouse]++;
        currentHouse = (currentHouse + 1) % (HOUSE_PER_PLAYER * 2);
    }

    // TODO : Update the score
}