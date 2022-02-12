#include "ship.h"
#include "board.h"
struct Ship create_shipFromFile(char *file, int size){
        //placeholder
}
/*struct Ship**/ void generateShip(struct Board arr, int size){
    char shipTypes[] = {'c','b','f','f'};
    //struct Ship *Ships = malloc(sizeof(struct Ship) * 4);
    //struct Ships[4];
    srand(time(0));
    for(int i = 0; i < 4; i++){
        struct Ship tempShip;
        tempShip.type = shipTypes[i];
        switch(tempShip.type){ //assign size/length depending on type
            case 'c':
                tempShip.length = 5;
                break;
            case 'b':
                tempShip.length = 4;
                break;
            case 'f':
                tempShip.length = 2;
                break;
        }
        // int collide = 0;
        // while(collide == 0){
            tempShip.isVertical = rand() % 2;
            if(tempShip.isVertical){
                tempShip.row = rand() % (size - tempShip.length + 1);
                tempShip.col = rand() % size;
            }
            else{
                tempShip.row = rand() % size;
                tempShip.col = rand() % (size - tempShip.length + 1);
            }
        //     collide = isValid(arr, tempShip);
        // }
        arr.Ships[i] = tempShip;
    }
}

int isValid(struct Board arr, struct Ship temp){
    int shipRow = temp.row;
    int shipCol = temp.col;
    for(int i = 0; i < temp.length; i++){
        if (temp.isVertical) //ship is vertical
        {
            if(arr.shipLocation[shipRow][shipCol + i] != '-'){
                return 0;
            }
        }
        else{ //horizontal ship
            if(arr.shipLocation[shipRow + i][shipCol] != '-'){
                return 0;
            }
        }
    }
    return 1;
}