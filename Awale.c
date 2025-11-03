#include "Awale.h" // Inclure le header correspondant

void initializeBoard(Awale *g)
{
    srand(time(NULL));

    for (int i = 0; i < HOUSE_PER_PLAYER * 2; i++)
    {
        g->board[i] = SEEDS_PER_HOUSE;
    }
    g->score1 = 0;
    g->score2 = 0;
    g->end = 0;
    g->currentPlayer = (rand() % 2) + 1; // First player is random
}

char *printBoard(const Awale *g, int player)
{
    char *buffer = malloc(BUF_SIZE);
    if (!buffer)
        return NULL;
    buffer[0] = '\0';

    int remaining = BUF_SIZE;
    int written = 0;
    int n = 0;

    n = snprintf(buffer + written, remaining, "\nAwale\n");
    written += n;
    remaining -= n;

    n = snprintf(buffer + written, remaining, "you are player : %d\n\n", player);
    written += n;
    remaining -= n;

    if (player == 1)
    {
        // ligne du haut : indices 11 -> 6
        for (int i = 11; i > 5; --i)
        {
            n = snprintf(buffer + written, remaining, " %2d ", g->board[i]);
            written += n;
            remaining -= n;
            if (remaining <= 0)
                break;
        }
        n = snprintf(buffer + written, remaining, "\n");
        written += n;
        remaining -= n;

        for (int i = 0; i < 6; ++i)
        {
            n = snprintf(buffer + written, remaining, " %2d ", g->board[i]);
            written += n;
            remaining -= n;
            if (remaining <= 0)
                break;
        }
    }
    else
    {
        // joueur 2 => afficher son point de vue
        for (int i = 5; i >= 0; --i)
        {
            n = snprintf(buffer + written, remaining, " %2d ", g->board[i]);
            written += n;
            remaining -= n;
            if (remaining <= 0)
                break;
        }
        n = snprintf(buffer + written, remaining, "\n");
        written += n;
        remaining -= n;

        for (int i = 6; i < 12; ++i)
        {
            n = snprintf(buffer + written, remaining, " %2d ", g->board[i]);
            written += n;
            remaining -= n;
            if (remaining <= 0)
                break;
        }
    }

    n = snprintf(buffer + written, remaining, "\n  A   B   C   D   E   F\n\n");
    written += n;
    remaining -= n;

    n = snprintf(buffer + written, remaining, "Player 1 score : %d\n", g->score1);
    written += n;
    remaining -= n;

    n = snprintf(buffer + written, remaining, "Player 2 score : %d\n", g->score2);
    written += n;
    remaining -= n;

    // Si on a manqué d'espace, le texte est tronqué mais on évite le crash.
    return buffer;
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

    // Check if the game is finished
    if (game->score1 > 24 || game->score2 > 24 || (game->score1 == 24 && game->score2 == 24))
    {
        endGame(game);
    }
}

void endGame(Awale *game)
{
    if (game->score1 > 24)
        game->end = 1;
    else if (game->score2 > 24)
        game->end = 2;
    else
        game->end = 3;
}