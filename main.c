#include <stdio.h>
#include "Awale.h"

int main()
{
    Awale game;
    initializeBoard(&game);
    printf("%s", printBoard(&game, 1));

    printf("\n--- TESTS ---\n");
    playMove(&game, 2);
    printBoard(&game, 1);

    playMove(&game, 8);
    printBoard(&game, 2);

    playMove(&game, 3);
    printBoard(&game, 1);

    playMove(&game, 7);
    printBoard(&game, 2);

    playMove(&game, 1);
    printBoard(&game, 1);

    playMove(&game, 9);
    printBoard(&game, 2);

    return 0;
}