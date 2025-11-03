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

void printBoard(const Awale *g, int player)
{
    printf("\nAwale\n");
    printf("you are player : %1d\n\n", g->currentPlayer);

    if (player == 1)
    {
        // board line one
        for (int i = 11; i > 5; i--)
        {
            printf(" %2d ", g->board[i]);
        }

        printf("\n");

        for (int i = 0; i < 6; i++)
        {
            printf(" %2d ", g->board[i]);
        }
    }
    else
    {
        // board line one
        for (int i = 5; i >= 0; i--)
        {
            printf(" %2d ", g->board[i]);
        }

        printf("\n");

        for (int i = 6; i < 12; i++)
        {
            printf(" %2d ", g->board[i]);
        }
    }

    printf("\n");
    printf("  A   B   C   D   E   F\n\n");
    printf("Player 1 score : %2d\n", g->score1);
    printf("Player 2 score : %2d\n", g->score2);
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
    // You only score when the last house is in the opponent side
    int minHouse = (game->currentPlayer == 1) ? 6 : 0;
    int maxHouse = (game->currentPlayer == 1) ? 11 : 5;
    if (!((numberOfSeeds == 2 || numberOfSeeds == 3) && (lastHouse >= minHouse && lastHouse <= maxHouse)))
    {
        game->currentPlayer = (game->currentPlayer == 1) ? 2 : 1;
        return;
    }

    // Yes, how many ?
    int point = 0;

    while (currentHouse >= minHouse && currentHouse <= maxHouse && (game->board[currentHouse] == 2 || game->board[currentHouse] == 3))
    {
        point += game->board[currentHouse];
        game->board[currentHouse] = 0;
        currentHouse--;
    }

    // Update the score
    if (game->currentPlayer == 1)
        game->score1 += point;
    else
        game->score2 += point;

    // Change player
    game->currentPlayer = (game->currentPlayer == 1) ? 2 : 1;
}