/*
tictactoe.c
------------
Contains all the function definitions required for Tic Tac Toe gameplay.

Author: Santhosh S <santhoshsuresh150@gmail.com>
*/

#include <stdio.h>
#include "tictactoe.h"

// Initialized board with spaces
void initBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

// Display the current board
void printBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < BOARD_SIZE - 1)
                printf("|");
        }
        printf("\n");
        if (i < BOARD_SIZE - 1)
            printf("---|---|---\n");
    }
    printf("\n");
}

// Make a move on the board
// pos = 1-9 (mapped to 3x3 grid)
int makeMove(char board[BOARD_SIZE][BOARD_SIZE], int pos, char symbol) {
    if (pos < 1 || pos > 9) return 0; // invalid position

    int row = (pos - 1) / BOARD_SIZE;
    int col = (pos - 1) % BOARD_SIZE;

    if (board[row][col] == ' ') {
        board[row][col] = symbol;
        return 1;
    }
    return 0; 
}

// Check if given player has won
int checkWin(char board[BOARD_SIZE][BOARD_SIZE], char symbol) {
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
            return 1;
    }

    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol)
            return 1;
    }

    // Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
        return 1;

    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return 1;

    return 0;
}

// Check if the board is full and Draw
int isDraw(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ')
                return 0; 
        }
    }
    return 1; 
}

void run_local_game() {
    char board[BOARD_SIZE][BOARD_SIZE];
    initBoard(board);
    char current = 'X';
    int pos;

    while (1) {
        printBoard(board);
        printf("Player %c, enter position (1-9): ", current);
        scanf("%d", &pos);

        if (!makeMove(board, pos, current)) {
            printf("Invalid move, try again!\n");
            continue;
        }

        if (checkWin(board, current)) {
            printBoard(board);
            printf("Player %c wins!\n", current);
            break;
        }

        if (isDraw(board)) {
            printBoard(board);
            printf("It's a draw!\n");
            break;
        }

        current = (current == 'X') ? 'O' : 'X';
    }
}
