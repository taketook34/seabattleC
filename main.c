#include <stdio.h>
#include <stdlib.h>
#include "map.h"


int main() {
    char line[SHIPSNUMBER][6];
    char Aloc[MAPSIZE][MAPSIZE], Aattack[MAPSIZE][MAPSIZE];
    char Bloc[MAPSIZE][MAPSIZE], Battack[MAPSIZE][MAPSIZE];
    struct Ship shipsA[SHIPSNUMBER], shipsB[SHIPSNUMBER];
    struct FireShoot fireshoot;


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


    int xa, xb, ya, yb;
    // запис кораблів
    for (int i = 0; i < SHIPSNUMBER; i++) {
        // СДЕЛАТЬ В БУДУЩЕМ: тут также сделать для корбалей для B и переписать что бы они были от меньшей к большей координате
        xa = line[i][1] - '0';
        xb = line[i][3] - '0';
        xa -= 1;
        xb -= 1;
        ya = getY(line[i][0]);
        yb = getY(line[i][2]);

        if (xa == xb && yb < ya) {
            shipsA[i].letter1 = yb;
            shipsA[i].x1 = xb;
            shipsA[i].letter2 = ya;
            shipsA[i].x2 = xa;
            shipsA[i].lenght = ya - yb + 1;
        } else if (yb == ya && xb < xa) {
            shipsA[i].letter1 = yb;
            shipsA[i].x1 = xb;
            shipsA[i].letter2 = ya;
            shipsA[i].x2 = xa;
            shipsA[i].lenght = xa - xb + 1;
        } else if (yb != ya && xb != xa) {
            perror("Error in file");
            return 1;
        } else {
            shipsA[i].letter1 = ya;
            shipsA[i].x1 = xa;
            shipsA[i].letter2 = yb;
            shipsA[i].x2 = xb;
            shipsA[i].lenght = (yb - ya) + (xb - xa) + 1;
        }

        //printf("%d\n", shipsA[i].lenght);
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

    // НАЧАЛО ИГРЫ


    char shoot_letter_y;
    int shoot_number_x, shoot_number_y;
    char resultOfShoot;

    printf("Hello, everyone! Welocome to Sea Battle game!\nWrite files for getting patterns: \n");
    // СДЕЛАТЬ В БУДУЩЕМ: Тут должен быть реализован выбор файла для каждого игрока и взять файл
    printf("Okay, let's start\n");
    printf("User A, type letter to shoot: ");
    scanf(" %c", &shoot_letter_y);  // СДЕЛАТЬ В БУДУЩЕМ: добавить проверку что бы буква проверялась
    shoot_number_y = getY(shoot_letter_y);

    printf("Type number to shoot: ");
    scanf(" %d", &shoot_number_x);

    // shipsA - только здесь это корабли жертвы
    resultOfShoot = checkShoot(Bloc, shoot_number_x -1, shoot_number_y);
    fireshoot.x = shoot_number_x - 1;
    fireshoot.y = shoot_number_y;
    fireshoot.res = resultOfShoot;


    printf("You pick %c:%d\n", shoot_letter_y, shoot_number_x);
    registerShoot(Bloc, Aattack, shipsA, fireshoot);
    // выводит аски код числа
    showShips(Bloc);

    return 0;
}