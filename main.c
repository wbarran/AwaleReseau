#include <stdio.h>
#include "Awale.h"

int main()
{
    Awale game;
    initializeBoard(&game);
    printBoard(&game);

    printf("\n--- TESTS ---\n");
    playMove(&game, 2);
    printBoard(&game);

    playMove(&game, 8);
    printBoard(&game);

    playMove(&game, 3);
    printBoard(&game);

    playMove(&game, 7);
    printBoard(&game);

    playMove(&game, 1);
    printBoard(&game);

    playMove(&game, 9);
    printBoard(&game);

    return 0;
}