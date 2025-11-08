#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "../include/tictactoe.h"

#define PORT 8080

void run_client() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char board[BOARD_SIZE][BOARD_SIZE];
    char buffer[32];
    int move;

    initBoard(board);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("[CLIENT] Connected to server!\n");

    char my_symbol = 'O';
    char opp_symbol = 'X';
    int my_turn;

    // Receive who plays first
    recv(sock, buffer, sizeof(buffer), 0);
    my_turn = atoi(buffer) ? 0 : 1; 
    

    while (1) {
        printBoard(board);

        if (my_turn) {
            printf("[CLIENT] Enter your move (1-9): ");
            scanf("%d", &move);

            if (!makeMove(board, move, my_symbol)) {
                printf("Invalid move! Try again.\n");
                continue;
            }

            sprintf(buffer, "%d", move);
            send(sock, buffer, sizeof(buffer), 0);

            if (checkWin(board, my_symbol)) {
                printBoard(board);
                printf("You (Client) win!\n");
                strcpy(buffer, "WIN");
                send(sock, buffer, sizeof(buffer), 0);
                break;
            }

            if (isDraw(board)) {
                printBoard(board);
                printf("It's a draw!\n");
                strcpy(buffer, "DRAW");
                send(sock, buffer, sizeof(buffer), 0);
                break;
            }

            my_turn = 0;
        } else {
            printf("[CLIENT] Waiting for server's move...\n");
            recv(sock, buffer, sizeof(buffer), 0);

            if (strcmp(buffer, "WIN") == 0) {
                printBoard(board);
                printf("Server wins!\n");
                break;
            } else if (strcmp(buffer, "DRAW") == 0) {
                printBoard(board);
                printf("It's a draw!\n");
                break;
            }

            move = atoi(buffer);
            makeMove(board, move, opp_symbol);
            printBoard(board);

            if (checkWin(board, opp_symbol)) {
                printf("Server wins!\n");
                strcpy(buffer, "WIN");
                send(sock, buffer, sizeof(buffer), 0);
                break;
            }

            if (isDraw(board)) {
                printf("It's a draw!\n");
                strcpy(buffer, "DRAW");
                send(sock, buffer, sizeof(buffer), 0);
                break;
            }

            my_turn = 1;
        }
    }

    close(sock);
}
