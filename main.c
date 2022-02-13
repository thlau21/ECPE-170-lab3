//Thomas Lau
//t_lau11@u.pacific.edu
#include "board.h"
#include "ship.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){
    char y = 'y';
    int x = 0;
    int gamesWon = 0;
    int gamesPlayed = 0;
    printf("Welcome to Frigate!\n\n");
    printf("How large should I make the grid? ");
    scanf("%d",&x);
    if(x < 5){
        x = 5;
        printf("The minimum grid size is 5... I'll make one that size.\n\n");
    }
    struct Board board = createBoard(x);
    while(y == 'y' || y == 'Y'){
        gamesPlayed++;
        board = createBoard(x);
        if(argc > 1){
            readFileShip(&board, argv[1]);
        }
        else{
            addShips(&board);
        }
        printBoard(board,x);
        while(board.gameOver == false){
            readInput(&board);
            if(board.gameOver == false){
                printBoard(board,x);
            }
        }
        if(board.gamesWon){
            printBoard(board,x);
            gamesWon++;
        }
        clearBoard(&board);//reset board but not de-allocate memory
        printf("Play again? (y/N) ");
        scanf(" %c",&y);
    }
    deleteBoard(&board,x); //de-allocate memory
    printf("\nYou won out of %d out of %d games", gamesWon, gamesPlayed);
    printf("\n\nThanks for playing!\n");
}