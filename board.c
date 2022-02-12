#include "board.h"
#include "ship.h"
//#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct Board createBoard(int size){
    printf("enterB");
    struct Board arr;
    arr.gameWon = false;
    arr.size = size;
    printf("before memory");
    arr.board = (char**)malloc(sizeof(char*) * size); //allocate memory for the 1xrows of array
    arr.shipLocation = (char**)malloc(sizeof(char*) * size);
    //loop to allocate memory for the arrays "within"
    printf("insideBard");
    for(int i = 0; i < size; i++){
        arr.board[i] = (char*)malloc(sizeof(char) * size);
        arr.shipLocation[i] = (char*)malloc(sizeof(char) * size);
        for(int j = 0; j < size; j++){
            arr.board[i][j] = '-';
            arr.shipLocation[i][j] = '-';
        }
    }
    return arr;
}
void printBoard(struct Board arr, int size){
    printf("    ");
    for(int i = 0; i < size; i++){
        printf(" %c ",(char)(i+65));
    }
    printf("\n   +");
    for(int i = 0; i < size; i++){
        printf(" - ");
    }
    printf("\n");
    for(int i = 0; i < size; i++){
        printf("  %d|",(i+1));
        for(int j = 0; j < size; j++){
            //printf(" %c ", arr.board[i][j]);
            printf(" %c ", arr.shipLocation[i][j]);
        }
        printf("\n");
    }
}

void deleteBoard(struct Board arr, int size){
    for(int i = 0; i < size; i++){
        free(arr.board[i]);
    }
    free(arr.board);
}

void isHit(struct Board arr, int row, int col){
    if(arr.shipLocation[row][col] != '-'){
        arr.board[row][col] = 'h';
    }
}

void readInput(struct Board arr){
    char* a = (char*)malloc(sizeof(char) * 5);
    printf("Enter the coordinate for your shot: ");
    scanf("%s", a);
    shoot(arr, a);
}

void shoot(struct Board arr, char coords[]){
    int row = coords[1] - '1';

    //printf("\n%d\n",row);
    if(row < 0 || row > arr.size){
        //printf("row");
        return;
    }

    int col = toupper(coords[0]) - 65;
    //printf("\n%d\n",arr.size);
    if(col < 0 || col > arr.size){
        //printf("col");
        //printf("\nenter %d\n",col);
        return;
    }

    //printf("ship %c",arr.shipLocation[row][col]);

    if(arr.shipLocation[row][col] != '-'){
        arr.board[row][col] = 'h';
        printf("shot\n");
        //subtract shots
    }
}
void addShips(struct Board arr){
    arr.Ships = malloc(sizeof(struct Ship) * 4);
    printf("test");
    generateShip(arr, arr.size);
    for (int i = 0; i < 4; i++)
    {
        int tempRow = arr.Ships[i].row;
        int tempCol = arr.Ships[i].col;
        for(int j = 0; j < arr.Ships[i].length; j++){
            if(arr.Ships[i].isVertical){ //if ship is vert
                arr.shipLocation[tempRow][tempCol + j] = arr.Ships[i].type;
            }
            else{ //horizontal
                arr.shipLocation[tempRow + j][tempCol] = arr.Ships[i].type;
            }
        }
    }
}