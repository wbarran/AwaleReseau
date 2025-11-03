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

void playMove(Awale *game, int houseIndex)
{
    // Adding one seed in the houses after the one selected
    int seedNumber = game->board[houseIndex];
    game->board[houseIndex] = 0;
    int currentHouse = houseIndex;
    for (int i = 1; i <= seedNumber; i++)
    {
        currentHouse = (currentHouse + 1) % (HOUSE_PER_PLAYER * 2);
        game->board[currentHouse]++;
    }

    // Update the score

    // Did the player score points
    int lastHouse = currentHouse;
    int numberOfSeeds = game->board[lastHouse];
    if (numberOfSeeds != 2 || numberOfSeeds != 3)
        return;

    // Yes, how many ?
    int point = 0;
    while (game->board[currentHouse] == 2 || game->board[currentHouse] == 3)
    {
        point += game->board[currentHouse];
        game->board[currentHouse] = 0;
        if (currentHouse == 0)
            currentHouse = 12;
        currentHouse--;
    }

    // Find which player is playing
    int player = 1;
    if (houseIndex < 6)
        player = 0;

    // Update the score
    if (player == 0)
        game->score1 += point;
    else
        game->score2 += point;
}