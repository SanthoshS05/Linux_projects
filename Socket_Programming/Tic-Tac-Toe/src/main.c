#include <stdio.h>
#include "tictactoe.h"

int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    char currentPlayer = 'X';
    int position;
    int filledCells = 0;   // track moves

    initBoard(board);

    printf("==== TIC TAC TOE ====\n");
    printf("Player 1: X\nPlayer 2: O\n\n");

    while (1) {
        printBoard(board);
        printf("Player %c, enter position (1-9): ", currentPlayer);
        scanf("%d", &position);

        if (!makeMove(board, position, currentPlayer)) {
            printf("Invalid move! Try again.\n");
            continue;
        }

        filledCells++;

        if (checkWin(board, currentPlayer)) {
            printBoard(board);
            printf("Player %c wins!\n", currentPlayer);
            break;
        }

        if (filledCells == BOARD_SIZE * BOARD_SIZE) {
            printBoard(board);
            printf("It's a draw!\n");
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    printf("Game Over.\n");
    return 0;
}
