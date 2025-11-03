#include "ServerGame.h"

void playGame(Client *player1, Client *player2, Client *spectators, int nbSpectators)
{
    Awale game;
    initializeBoard(&game);
    char *start[32] = (game.currentPlayer == 1) ? player1->name : player2->name;
    char buffer[100] = "Welcome to your Awale game, starting player : ";
    strcat(buffer, start);
    write_client(player1->sock, buffer);
    write_client(player2->sock, buffer);

    while (game.end == 0)
    {
        write_client(player1->sock, printBoard(&game, 1));
        write_client(player2->sock, printBoard(&game, 2));
        for (int i = 0; i < nbSpectators; i++)
        {
            write_client(spectators[i], printBoard(&game, 1));
        }

        SOCKET currentPlayer = (game.currentPlayer == 1) ? player1->sock : player2->sock;
        write_client(currentPlayer, "It is your turn to play, pick a house please (from A to F)");
        char response;
        int house;
        switch (response)
        {
        case 'A':
            house = (game.currentPlayer == 1) ? 0 : 6;
            break;
        case 'B':
            house = (game.currentPlayer == 1) ? 1 : 7;
            break;
        case 'C':
            house = (game.currentPlayer == 1) ? 2 : 8;
            break;
        case 'D':
            house = (game.currentPlayer == 1) ? 3 : 9;
            break;
        case 'E':
            house = (game.currentPlayer == 1) ? 4 : 10;
            break;
        case 'F':
            house = (game.currentPlayer == 1) ? 5 : 11;
            break;
        default:
            printf("there is a problem");
        }
        playMove(&game, house);
    }

    char buffer[100] = "";
    if (game.end == 3)
        strcat(buffer, "Draw");
    else
    {
        char winner[32] = (game.end == 1) ? player1->name : player2->name;
        strcat(buffer, "The winner is : ");
        strcat(buffer, winner);
    }
    write_client(player1->sock, buffer);
    write_client(player2->sock, buffer);
}
