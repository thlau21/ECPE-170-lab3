//Thomas Lau
//t_lau11@u.pacific.edu
#ifndef SHIP_H
#define SHIP_H

#include "board.h"
struct Ship {
    char type;
    int row; //position row
    int col; //position col
    int length;
    int isDead;
    int isVertical;
};

void readFileShip(struct Board* arr, char* file);
void generateShip(struct Board* arr, int size);
int isValid(struct Board arr, struct Ship* temp);
void addShipToMap(struct Board* arr, struct Ship* s);
#endif