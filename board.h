//Thomas Lau
//t_lau11@u.pacific.edu
#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

struct Board {
    char** board;
    char** shipLocation;
    int shots;
    int size;
    int gameOver; 
    struct Ship** Ships;
    int shipSunk;
    int gamesWon;
};

struct Board createBoard(int size);
void fillBoard(struct Board* arr, int size);
void printBoard(struct Board arr, int size); //print board
void printHiddenBoard(struct Board arr, int size);//print board with ships location
void deleteBoard(struct Board* arr, int size); //free all memory
void addShips(struct Board* arr); //add ships
void readInput(struct Board* arr); //read userinput
void shoot(struct Board* arr, char coords[]);//function to shoot
int isSunk(struct Board arr, struct Ship s); //check if ship is sunk
void handleSunkShip(struct Board* arr); //loops to check all ships
void clearBoard(struct Board* arr);
#endif