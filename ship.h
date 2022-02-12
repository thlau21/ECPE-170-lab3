#ifndef SHIP_H
#define SHIP_H

#include <stdbool.h>
#include "board.h"
struct Ship {
    char type;
    int row; //position row
    int col; //position col
    int length;
    bool isDead;
    bool isVertical;
};

struct Ship create_shipFromFile(char *file, int size);
/*struct Ship**/ void generateShip(struct Board arr, int size);
int isValid(struct Board arr, struct Ship temp);
#endif