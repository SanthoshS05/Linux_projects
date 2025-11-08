/*
main.c
-------
Entry point for Tic Tac Toe project.
Allows user to choose between Server, Client, or Local Two-Player mode.

Author: Santhosh S <santhoshsuresh150@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include "tictactoe.h"

int main() {
    int choice;

    printf("=====================================\n");
    printf("       Tic Tac Toe - Main Menu       \n");
    printf("=====================================\n");
    printf("1. Run as Server\n");
    printf("2. Run as Client\n");
    printf("3. Run Local 2-Player Game\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            run_server();
            break;
        case 2:
            run_client();
            break;
        case 3:
            run_local_game();
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    return 0;
}
