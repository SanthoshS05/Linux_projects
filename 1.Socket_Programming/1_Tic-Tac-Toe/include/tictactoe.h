#ifndef TICTACTOE_H
#define TICTACTOE_H

#define BOARD_SIZE 3

void initBoard(char board[BOARD_SIZE][BOARD_SIZE]);
void printBoard(char board[BOARD_SIZE][BOARD_SIZE]);
int makeMove(char board[BOARD_SIZE][BOARD_SIZE], int pos, char symbol);
int checkWin(char board[BOARD_SIZE][BOARD_SIZE], char symbol);
int isDraw(char board[BOARD_SIZE][BOARD_SIZE]);


void run_server();
void run_client();
void run_local_game();
#endif
