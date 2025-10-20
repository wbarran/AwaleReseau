#include <stdio.h>
#include "Awale.h"

int main()
{
    Awale game;
    initializeBoard(&game);
    printBoard(game.board);

    printf("\n--- TESTS ---\n");
    playMove(&game, 2);
    printBoard(game.board);

    playMove(&game, 8);
    printBoard(game.board);

    return 0;
}