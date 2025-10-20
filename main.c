#include <stdio.h>
#include "Awale.h"

int main()
{
    Awale game;
    initializeBoard(&game);
    printBoard(game);

    printf("\n--- TESTS ---\n");
    jouerCoup(&game, 2);
    printBoard(game);

    jouerCoup(&game, 8);
    printBoard(game);

    return 0;
}