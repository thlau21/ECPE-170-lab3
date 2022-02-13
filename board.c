//Thomas Lau
//t_lau11@u.pacific.edu
#include "board.h"
#include "ship.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct Board createBoard(int size){
    struct Board arr;
    arr.gameOver = 0;
    arr.size = size;
    arr.shots = (size * size) / 2;
    arr.shipSunk = 0;
    arr.gamesWon = 0;
    arr.Ships = malloc(sizeof(struct Ship*) * 4);
    fillBoard(&arr, size);
    return arr;
}

void clearBoard(struct Board* arr){
    int size = arr->size;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            arr->board[i][j] = '-';
            arr->shipLocation[i][j] = '-';
        }
    }
}

void fillBoard(struct Board* arr, int size){
    arr->board = (char**)malloc(sizeof(char*) * size); //allocate memory for the 1xrows of array
    arr->shipLocation = (char**)malloc(sizeof(char*) * size);
    //loop to allocate memory for the arrays "within"
    for(int i = 0; i < size; i++){
        arr->board[i] = (char*)malloc(sizeof(char) * size);
        arr->shipLocation[i] = (char*)malloc(sizeof(char) * size);
        for(int j = 0; j < size; j++){
            arr->board[i][j] = '-';
            arr->shipLocation[i][j] = '-';
        }
    }
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
            printf(" %c ", arr.board[i][j]);
            //printf(" %c ", arr.shipLocation[i][j]);
        }
        printf("\n");
    }
}

void printHiddenBoard(struct Board arr, int size){
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
            printf(" %c ", arr.shipLocation[i][j]);
        }
        printf("\n");
    }
}


void deleteBoard(struct Board* arr, int size){
    for(int i = 0; i < size; i++){
        free(arr->board[i]);
        free(arr->shipLocation[i]);
    }
    for(int j = 0;j < 4; j++){
        free(arr->Ships[j]);
    }
    free(arr->board);
    free(arr->shipLocation);
    free(arr->Ships);
    return;
}

void readInput(struct Board* arr){
    char* a = (char*)malloc(sizeof(char) * 5);
    printf("Enter the coordinate for your shot (%d shots remaining): ", arr->shots);
    scanf("%s", a);
    printf("\n");
    shoot(arr, a);
}

void shoot(struct Board* arr, char coords[]){
    int i = 0;
    int row = 0;
    int col = 0;
    char colu = 'a';
    if(toupper(coords[i]) >= 65 && toupper(coords[i]) <= 90){
        col = toupper(coords[i]) - 65;
        colu = toupper(coords[i]);
        i++;
    }
    while(coords[i] > 47 && coords[i] < 58){ //check if first input is number 
            row *= 10;
            row += coords[i] - 49;
            i++;
    }
    if(toupper(coords[i]) >= 65 && toupper(coords[i]) <= 90){
        col = toupper(coords[i]) - 65;
        colu = toupper(coords[i]);
    }

    if(row < 0 || row >= arr->size){
        printf("ERROR\n");
        return;
    }

    if(col < 0 || col >= arr->size){
        printf("ERROR\n");
        return;
    }

    char temp = arr->shipLocation[row][col];
    char bTemp = arr->board[row][col];
    if(bTemp == 'h' || bTemp == 'm' || bTemp == 'c' || bTemp == 'f' || bTemp == 'b'){
        printf("Already shot here\n");
    }
    else if(temp != '-'){

        printf("\n%c%d is a hit\n\n",colu,row);
        arr->board[row][col] = 'h';
        arr->shots -= 1;
        handleSunkShip(arr);
        if(arr->shipSunk == 4){
            arr->gameOver = 1;
            arr->gamesWon = 1;
        }
    }
    else{
        printf("\n%c%d is a miss\n\n",colu,row);
        arr->board[row][col] = 'm';
        arr->shots -= 1;
    }
    if(arr->shots <= 0){
        arr->gameOver = 1;
        printf("You do not have enough shells to sink the remaining ships\nHere is your original ship locations\n\n");
        printHiddenBoard(*arr, arr->size);
        printf("\nYou sunk %d ships\n\n", arr->shipSunk);
    }
}
void addShips(struct Board* arr){
    // arr->Ships = malloc(sizeof(struct Ship*) * 4);
    generateShip(arr, arr->size);
}

void handleSunkShip(struct Board* arr){
    for(int i = 0; i < 4; i++){
        struct Ship temp = *arr->Ships[i];
        if(isSunk(*arr, temp)){
            int tempRow = temp.row;
            int tempCol = temp.col;
            if(temp.isVertical){
                for(int j = 0; j < temp.length; j++){
                    arr->board[tempRow + j][tempCol] = temp.type;
                }
            }
            else{
                for(int j = 0; j < temp.length; j++){
                    arr->board[tempRow][tempCol + j] = temp.type;
                }
            }
            arr->Ships[i]->isDead = 1;
            arr->shipSunk += 1;
        }
    }
}

int isSunk(struct Board arr, struct Ship s){
    int tempRow = s.row;
    int tempCol = s.col;
    int hit = 0;
    for(int i = 0; i < s.length; i++){
        if(s.isVertical){
            if(arr.board[tempRow + i][tempCol] == 'h'){
                hit += 1;
            }
        }
        else{
            if(arr.board[tempRow][tempCol + i] == 'h'){
                hit += 1;
            }
        }
    }
    return (float)hit / s.length > (float)0.7;
}