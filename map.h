#ifndef MAP_H
#define MAP_H

#include "config.h"

struct Ship {
    // СДЕЛАТЬ НА БУДУЩЕЕ: написать функцию которая будет из цифры в букву
    int letter1;
    int x1;
    int letter2;
    int x2;
    int lenght;

};

struct FireShoot {
    int x;
    int y;
    char res;
};


int getY(char letter);
void createShipsMap(char rendermap[MAPSIZE][MAPSIZE], struct Ship ships[SHIPSNUMBER]);
void showShips(char showmap[MAPSIZE][MAPSIZE]);
void createMaps(char newmap[MAPSIZE][MAPSIZE]);
char checkShoot(char checkmap[MAPSIZE][MAPSIZE], int shootx, int shooty);
void registerShoot(char checkmap[MAPSIZE][MAPSIZE], char shootmap[MAPSIZE][MAPSIZE], int *score, struct Ship ships[SHIPSNUMBER], struct FireShoot fireshoot);

#endif