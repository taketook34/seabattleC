#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "config.h"

const char alphletters[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

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
    int i, j;
    printf("  ");

    for (i =1; i <= MAPSIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (i = 0; i < MAPSIZE; i++) {
        printf("%c ", alphletters[i]);
        for (j = 0; j < MAPSIZE; j++) {
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



void setkilledships(char attackmap[MAPSIZE][MAPSIZE], int xa, int ya, int xb, int yb) {
    int i, j, startX, startY, finishX, finishY;
    if (xa == 0) {
        startX = xa;
    } else {
        startX = xa - 1;
    }

    if (xb == MAPSIZE - 1) {
        finishX = xb;
    } else {
        finishX = xb + 1;
    }

    if (ya == 0) {
        startY = ya;
    } else {
        startY = ya - 1;
    }

    if (yb == MAPSIZE - 1) {
        finishY = yb;
    } else {
        finishY = yb + 1;
    }

    for (i = startY; i <= finishY; i++) {
        for (j = startX; j <= finishX; j++) {
            if (attackmap[i][j] == WATER) {
                
                attackmap[i][j] = AIMWATER;
            }
        }
    }


}

void registerShoot(char checkmap[MAPSIZE][MAPSIZE], char shootmap[MAPSIZE][MAPSIZE], int *score, struct Ship ships[SHIPSNUMBER], struct FireShoot fireshoot) {
    int gletter1, gletter2, gx1, gx2;
    if (fireshoot.res == SHIP) {
        
        for (int i = 0; i < SHIPSNUMBER; i++) {

            gletter1 = ships[i].letter1;
            gletter2 = ships[i].letter2;
            gx1 = ships[i].x1;
            gx2 = ships[i].x2;

            if (fireshoot.y >= gletter1 && fireshoot.y <= gletter2 && fireshoot.x >= gx1 && fireshoot.x <= gx2) {
                ships[i].lenght--;// -= 1;
                shootmap[fireshoot.y][fireshoot.x] = AIMSHIP;
                checkmap[fireshoot.y][fireshoot.x] = AIMSHIP;

                if (ships[i].lenght == 0) {
                    printf("You killed ship");
                    setkilledships(shootmap, gx1, gletter1, gx2, gletter2);
                    setkilledships(checkmap, gx1, gletter1, gx2, gletter2);
                    (*score) += 1; // прибавляем счет + 1
                    
                } else {
                    printf("You aimed ship");
                    // printf(" Last: %d", gship.lenght);
                }
                printf("\nYou can shoot one more");
            }
        }

    } else if (fireshoot.res == AIMWATER || fireshoot.res == AIMSHIP) {
        printf("You've already shooted here");
        printf("\nYou can shoot one more");

    } else {
        shootmap[fireshoot.y][fireshoot.x] = AIMWATER;
        checkmap[fireshoot.y][fireshoot.x] = AIMWATER;
        printf("You missed");
    } 

    printf("\n");
}
