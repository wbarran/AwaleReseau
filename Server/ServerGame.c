#include "ServerGame.h"

void playGame(Client *player1, Client *player2, Client *spectators, int nbSpectators)
{
    Awale game;
    initializeBoard(&game);
    char *start = (game.currentPlayer == 1) ? player1->name : player2->name;
    char buffer[100] = "Welcome to your Awale game, starting player : ";
    strcat(buffer, start);
    write_client(player1->sock, buffer);
    write_client(player2->sock, buffer);

    int quit = 0;
    while (game.end == 0)
    {
        write_client(player1->sock, printBoard(&game, 1));
        write_client(player2->sock, printBoard(&game, 2));
        for (int i = 0; i < nbSpectators; i++)
        {
            write_client(spectators[i].sock, printBoard(&game, 1));
        }

        SOCKET currentPlayer = (game.currentPlayer == 1) ? player1->sock : player2->sock;
        write_client(currentPlayer, "It is your turn to play, pick a house please (from A to F)");
        char response;
        int house = -1;
        while (house == -1 && quit == 0)
        {
            read_client(currentPlayer, &response);
            response = toupper(response);
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
            case 'N':
                game.end = 3;
                quit = 1;
                break;
            default:
                write_client(currentPlayer, "Invalid choice, pick A-F");
                house = -1;
            }
        }

        playMove(&game, house);
    }

    char buffer2[100] = "";
    if (game.end == 3)
        strcat(buffer2, "Draw");
    else
    {
        char *winner = (game.end == 1) ? player1->name : player2->name;
        strcat(buffer2, "The winner is : ");
        strcat(buffer2, winner);
    }
    write_client(player1->sock, buffer2);
    write_client(player2->sock, buffer2);
    player1->inGame = 0;
    player2->inGame = 0;
}

void *gameThread(void *arg)
{
    GameArgs *args = (GameArgs *)arg;

    playGame(args->player1, args->player2, args->spectators, args->nbSpectators);

    free(arg); // très important : libère la mémoire allouée dynamiquement
    pthread_exit(NULL);
}