#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

struct Board {
    char** board;
    char** shipLocation;
    int size;
    bool gameWon; 
    struct Ship* Ships;
};

struct Board createBoard(int size);
void printBoard(struct Board arr, int size);
void fillBoard(struct Board myArray, int size);
void deleteBoard(struct Board arr, int size);
void isHit(struct Board arr, int row, int col); //don't think i need this
void addShips(struct Board arr);
void readInput(struct Board arr);
void shoot(struct Board arr, char coords[]);//function to shoot
#endif