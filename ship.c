//Thomas Lau
//t_lau11@u.pacific.edu
#include "ship.h"
#include "board.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void generateShip(struct Board* arr, int size){
    char shipTypes[] = {'c','b','f','f'};
    srand(time(0));
    for(int i = 0; i < 4; i++){
        struct Ship* tempShip = malloc(sizeof(struct Ship) * 1);
        tempShip->type = shipTypes[i];
        tempShip->isDead = 0;
        switch(tempShip->type){ //assign size/length depending on type
            case 'c':
                tempShip->length = 5;
                break;
            case 'b':
                tempShip->length = 4;
                break;
            case 'f':
                tempShip->length = 2;
                break;
        }
        int collide = 1;
        while(collide == 1){
            tempShip->isVertical = rand() % 2;
            if(tempShip->isVertical){
                tempShip->row = rand() % (size - tempShip->length + 1);
                tempShip->col = rand() % size;
            }
            else{
                tempShip->row = rand() % size;
                tempShip->col = rand() % (size - tempShip->length + 1);
            }
             collide = isValid(*arr, tempShip);
        }
        addShipToMap(arr, tempShip);
        arr->Ships[i] = tempShip;
    }
}

int isValid(struct Board arr, struct Ship* temp){
    int shipRow = temp->row;
    int shipCol = temp->col;
    for(int i = 0; i < temp->length; i++){
        if (temp->isVertical) //ship is vertical
        {
            if(arr.shipLocation[shipRow + i][shipCol] != '-'){
                return 1;
            }
        }
        else{ //horizontal ship
            if(arr.shipLocation[shipRow][shipCol + i] != '-'){
                return 1;
            }
        }
    }
    return 0;
}

void readFileShip(struct Board* arr, char* file){
    FILE* input_file;
    char buffer[1000];
    
    input_file = fopen(file, "r");
    if(!input_file){
        addShips(arr);
    }
    else{
        int i = 0;
        while(fgets(buffer, 1000, input_file) != NULL){
            if(buffer[0] == '#'){
                continue;
            }
            else{
                struct Ship* tempShip = malloc(sizeof(struct Ship) * 1);
                if(buffer[0] == 'c'){
                    tempShip->type = 'c';
                    tempShip->isDead = 0;
                    tempShip->length = 5;
                    if(buffer[2] == 'r'){
                        tempShip->isVertical = 0;
                    }
                    else{
                        tempShip->isVertical = 1;
                    }
                    tempShip->col = toupper(buffer[4]) - 65;
                    tempShip->row = buffer[5] - 49;
                }
                else if(buffer[0] == 'b'){
                    tempShip->type = 'b';
                    tempShip->isDead = 0;
                    tempShip->length = 4;
                    if(buffer[2] == 'r'){
                        tempShip->isVertical = 0;
                    }
                    else{
                        tempShip->isVertical = 1;
                    }
                    tempShip->col = toupper(buffer[4]) - 65;
                    tempShip->row = buffer[5] - 49;
                }
                if(buffer[0] == 'f'){
                    tempShip->type = 'f';
                    tempShip->isDead = 0;
                    tempShip->length = 2;
                    if(buffer[2] == 'r'){
                        tempShip->isVertical = 0;
                    }
                    else{
                        tempShip->isVertical = 1;
                    }
                    tempShip->col = toupper(buffer[4]) - 65;
                    tempShip->row = buffer[5] - 49;
                }
                addShipToMap(arr, tempShip);
                arr->Ships[i] = tempShip;
                i++;
            }
        }
    }
    fclose(input_file);
}

void addShipToMap(struct Board* arr, struct Ship* s){
    int row = s->row;
    int col = s->col;
    for(int k = 0; k < s->length; k++){
        if(s->isVertical){
            arr->shipLocation[row + k][col] = s->type;
        }
        else{
            arr->shipLocation[row][col + k] = s->type;
        }
    }
}