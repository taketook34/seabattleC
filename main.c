#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int MAPSIZE =8;
const int SHIPSNUMBER = 10;

struct Ship {
    char letter1;
    int x1;
    char letter2;
    int x2;
    bool hitted;
    bool killed;
};

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
        startY = getY(ships[i].letter1);
        finishY = getY(ships[i].letter2);
        startX = ships[i].x1 - 1;
        finishX = ships[i].x2 - 1;

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





int main() {
    char line[SHIPSNUMBER][6];
    char Aloc[MAPSIZE][MAPSIZE], Aattack[MAPSIZE][MAPSIZE];
    char Bloc[MAPSIZE][MAPSIZE], Battack[MAPSIZE][MAPSIZE];
    struct Ship shipsA[SHIPSNUMBER], shipsB[SHIPSNUMBER];


    FILE *file = fopen("write.txt", "r");

    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return 1;
    }
    // Читання в циклу 
    for (int i = 0; i < SHIPSNUMBER; i++) {
        fscanf(file, "%c%c %c%c\n", &line[i][0], &line[i][1], &line[i][2], &line[i][3]);
    }
    fclose(file);


    int a, b;
    // запис кораблів
    for (int i = 0; i < SHIPSNUMBER; i++) {
        // тут также сделать для корбалей для B
        a = line[i][1] - '0';
        b = line[i][3] - '0';
    
        shipsA[i].letter1 = line[i][0];
        shipsA[i].x1 = a;
        shipsA[i].letter2 = line[i][2];
        shipsA[i].x2 = b;
        shipsA[i].hitted = false;
        shipsA[i].killed = false;
        //printf("Ship %d coordinates %c:%d - %c:%d\n", i+1, shipsA[i].letter1, shipsA[i].x1, shipsA[i].letter2, shipsA[i].x2);
    }


    createMaps(Aloc);
    createShipsMap(Aloc, shipsA);
    createMaps(Aattack);
    showShips(Aloc);
    printf("\n");
    createMaps(Bloc);
    createShipsMap(Bloc, shipsA);    
    createMaps(Battack);
    showShips(Bloc);

    return 0;
}