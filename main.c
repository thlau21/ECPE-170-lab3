#include "board.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){
    int x;
    printf("Welcome to Frigate!\n\n");
    printf("How large should I make the grid?");
    scanf("%d",&x);
    //printf("createBard\n");
    struct Board board = createBoard(x);
    printf("testMain");
    addShips(board);
    printBoard(board,x);
    // board.shipLocation[2][2] = 'f';
    // board.shipLocation[2][3] = 'f';
    // while(board.gameWon == false){
    //     readInput(board);
    //     printBoard(board,x);
    // }
    // readInput(board);
    // printBoard(board,x);
}