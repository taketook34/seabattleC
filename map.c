#include <stdio.h>
#include <stdlib.h>
#include "map.h"


int getY(char letter) {
    switch (letter) {
        case 'a':
            return 0;
            break;
        case 'b':
            return 1;
            break;
        case 'c':
            return 2;
            break;
        case 'd':
            return 3;
            break;
        case 'e':
            return 4;
            break;
        case 'f':
            return 5;
            break;
        case 'g':
            return 6;
            break;
        case 'h':
            return 7;
            break;
        default:
            return -1;
    }
}

void createShipsMap(char rendermap[MAPSIZE][MAPSIZE], struct Ship ships[SHIPSNUMBER]) {
    int startY, finishY, startX, finishX, i, j;


    for (i = 0; i < SHIPSNUMBER; i++) {
        startY = ships[i].letter1;
        finishY = ships[i].letter2;
        startX = ships[i].x1;
        finishX = ships[i].x2;

        rendermap[startY][startX] = SHIP;
        rendermap[finishY][finishX] = SHIP;

        if (startX == finishX) {
            // проверка на длину по буквам
            if (abs(finishY - startY) > 1) {
                // отрисовуем корабль по вертикали
                if (finishY > startY) {
                    for (j = startY; j < finishY; j++) {
                        rendermap[j][startX] = SHIP;
                    }
                } else {
                    for (j = finishY; j < startY; j++) {
                        rendermap[j][startX] = SHIP;
                    }
                }
                
            }
        } else {
            // проверка на длину по цифрам
            if (abs(finishX - startX) > 1) {
                // отрисуем по горизонтали
                if (finishX > startX) {
                    for (j = startX; j < finishX; j++) {
                        rendermap[startY][j] = SHIP;
                    }
                } else {
                    for (j = finishX; j < startX; j++) {
                        rendermap[startY][j] = SHIP;
                    }
                }

            }
        }
    }
}

void showShips(char showmap[MAPSIZE][MAPSIZE]) {
    for (int i = 0; i < MAPSIZE; i++) {
        for (int j = 0; j < MAPSIZE; j++) {
            printf("%c ", showmap[i][j]);
        }
        printf("\n");
    }
}

void createMaps(char newmap[MAPSIZE][MAPSIZE]) {
    for (int i = 0; i < MAPSIZE; i++) {
        for (int j = 0; j < MAPSIZE; j++) {
            newmap[i][j] = WATER;
        }
    }
}

char checkShoot(char checkmap[MAPSIZE][MAPSIZE], int shootx, int shooty) {
    // сделать что бы уже стреляные регало по стреляющей сетке
    return checkmap[shooty][shootx];
}

void setcheckedhits(char setmap[MAPSIZE][MAPSIZE], int shootx, int shooty) {
    int i, j, startX, startY, finishX, finishY;
    // определим границы для X
    if (shootx == 0) {
        startX = 0;
        finishX = startX + 1;
    } else if (shootx == MAPSIZE - 1) {
        finishX = MAPSIZE - 1;
        startX = finishX - 1; 
    } else {
        startX = shootx - 1;
        finishX = shootx + 1;
    }

    // определим границы для Y
    if (shooty == 0) {
        startY = 0;
        finishY = startY + 1;
    } else if (shooty == MAPSIZE - 1) {
        finishY = MAPSIZE - 1;
        startY = finishY - 1; 
    } else {
        startY = shooty - 1;
        finishY = shooty + 1;
    }
    //printf("%d:%d = %d:%d - %d:%d\n", shooty, shootx, startY, finishY, startX, startY);
    for (i = startY; i <= finishY; i++) {
        for (j = startX; j <= finishX; j++) {
            if (setmap[i][j] == WATER) {
                setmap[i][j] = AIMWATER;
            }
        }
    }
}

void registerShoot(char checkmap[MAPSIZE][MAPSIZE], char shootmap[MAPSIZE][MAPSIZE], struct Ship ships[SHIPSNUMBER], struct FireShoot fireshoot) {
    struct Ship gship;
    if (fireshoot.res == SHIP) {
        
        for (int i = 0; i < SHIPSNUMBER; i++) {
            gship = ships[i];
            if (fireshoot.y >= gship.letter1 && fireshoot.y <= gship.letter2 && fireshoot.x >= gship.x1 && fireshoot.x <= gship.x2) {

                gship.lenght -= 1;
                shootmap[fireshoot.y][fireshoot.x] = AIMSHIP;
                checkmap[fireshoot.y][fireshoot.x] = AIMSHIP;
                setcheckedhits(checkmap, fireshoot.x, fireshoot.y);

                if (gship.lenght == 0) {
                    printf("You killed ship"); 

                } else {
                    printf("You aimed ship");
                }
                
            }
        }

    } else if (fireshoot.res == AIMWATER || fireshoot.res == AIMSHIP) {
        printf("You've already shooted here");

    } else {
        shootmap[fireshoot.y][fireshoot.x] = AIMWATER;
        checkmap[fireshoot.y][fireshoot.x] = AIMWATER;
        printf("You missed");
    } 

    printf("\n");
}
