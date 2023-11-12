#ifndef MAP_H
#define MAP_H

#define MAPSIZE 8
#define SHIPSNUMBER 10

struct Ship {
    // СДЕЛАТЬ НА БУДУЩЕЕ: написать функцию которая будет из цифры в букву
    int letter1;
    int x1;
    int letter2;
    int x2;
    int lenght;
    // int hitted;
    // bool killed;
};

int getY(char letter);
void createShipsMap(char rendermap[MAPSIZE][MAPSIZE], struct Ship ships[SHIPSNUMBER]);
void showShips(char showmap[MAPSIZE][MAPSIZE]);
void createMaps(char newmap[MAPSIZE][MAPSIZE]);
char checkShoot(char checkmap[MAPSIZE][MAPSIZE], int shootx, int shooty);

#endif