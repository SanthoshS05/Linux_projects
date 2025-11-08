/*
server.c
------------
Contains funcitonalities for the server side game

Author: Santhosh S <santhoshsuresh150@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "../include/tictactoe.h"

#define PORT 8080

void run_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int move;
    char board[BOARD_SIZE][BOARD_SIZE];
    char buffer[32];

    initBoard(board);

    // 1. Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Bind
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 3. Listen
    if (listen(server_fd, 1) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("[SERVER] Waiting for client...\n");

    // 4. Accept
    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("[SERVER] Client connected!\n");

    char my_symbol = 'X';
    char opp_symbol = 'O';
    int my_turn;

    printf("[SERVER] Who's Playing First?\n0. Client\n1. Server\n> ");
    while (1) {
        scanf("%d", &my_turn);
        if (my_turn == 0 || my_turn == 1)
            break;
        printf("[SERVER] Enter either 0 or 1:\n> ");
    }

    // Tell the client who starts
    sprintf(buffer, "%d", my_turn);
    send(new_socket, buffer, sizeof(buffer), 0);

    while (1) {
        printBoard(board);

        if (my_turn) {
            printf("[SERVER] Enter your move (1-9): ");
            scanf("%d", &move);

            if (!makeMove(board, move, my_symbol)) {
                printf("Invalid move. Try again.\n");
                continue;
            }

            sprintf(buffer, "%d", move);
            send(new_socket, buffer, sizeof(buffer), 0);

            if (checkWin(board, my_symbol)) {
                printBoard(board);
                printf("You (Server) win!\n");
                strcpy(buffer, "WIN");
                send(new_socket, buffer, sizeof(buffer), 0);
                break;
            }

            if (isDraw(board)) {
                printBoard(board);
                printf("It's a draw!\n");
                strcpy(buffer, "DRAW");
                send(new_socket, buffer, sizeof(buffer), 0);
                break;
            }

            my_turn = 0;
        } else {
            printf("[SERVER] Waiting for client's move...\n");
            recv(new_socket, buffer, sizeof(buffer), 0);

            if (strcmp(buffer, "WIN") == 0) {
                printBoard(board);
                printf("Client wins!\n");
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
                printf("Client wins!\n");
                strcpy(buffer, "WIN");
                send(new_socket, buffer, sizeof(buffer), 0);
                break;
            }

            if (isDraw(board)) {
                printf("It's a draw!\n");
                strcpy(buffer, "DRAW");
                send(new_socket, buffer, sizeof(buffer), 0);
                break;
            }

            my_turn = 1;
        }
    }

    close(new_socket);
    close(server_fd);
}
