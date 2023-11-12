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

        rendermap[startY][startX] = 'o';
        rendermap[finishY][finishX] = 'o';

        if (startX == finishX) {
            // проверка на длину по буквам
            if (abs(finishY - startY) > 1) {
                // отрисовуем корабль по вертикали
                if (finishY > startY) {
                    for (j = startY; j < finishY; j++) {
                        rendermap[j][startX] = 'o';
                    }
                } else {
                    for (j = finishY; j < startY; j++) {
                        rendermap[j][startX] = 'o';
                    }
                }
                
            }
        } else {
            // проверка на длину по цифрам
            if (abs(finishX - startX) > 1) {
                // отрисуем по горизонтали
                if (finishX > startX) {
                    for (j = startX; j < finishX; j++) {
                        rendermap[startY][j] = 'o';
                    }
                } else {
                    for (j = finishX; j < startX; j++) {
                        rendermap[startY][j] = 'o';
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
            newmap[i][j] = '~';
        }
    }
}

char checkShoot(char checkmap[MAPSIZE][MAPSIZE], int shootx, int shooty) {
    return checkmap[shooty][shootx];
}

// char registerShoot(char checkmap[MAPSIZE][MAPSIZE], char shootmap[MAPSIZE][MAPSIZE], struct Ship ships[SHIPSNUMBER], int shootx, int shooty) {
//     // checkmap жертвы, shootmap среляющего
//     // -1, 3- уже проверено
//     // 0, 4 - мимо
//     // 1, 5 - ранен
//     // 2, 6 - убит
//     int to_return;
//     if (shootmap[shooty][shootx] == "=" || shootmap[shooty][shootx] == "x" ) {
//         return "a";
//     } else {
//         char result = checkmap[shooty][shootx];

//         if (result == "~") {
//             shootmap[shooty][shootx] = "=";
//             checkmap[shooty][shootx] = "=";
//             return "o";

//         } else if (result == "o") {
//             struct Ship gship;
//             for (int i = 0; i < SHIPSNUMBER; i++) {
//                 gship = ships[i];
//                 if (shooty >= getY(gship.letter1) && shooty <= getY(gship.letter2) && shootx >= gship.x1 && shootx <= gship.x2) {
//                     gship.lenght -= 1;
//                     shootmap[shooty][shootx] = "x";
//                     checkmap[shooty][shootx] = "x";
//                     if (gship.lenght == 0) {
//                         return "k"; 
//                     } else {
//                         return  "h";
//                     }
                    
//                 }
//             }

//         }
//     }
//     //return to_return;
    
// }