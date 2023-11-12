#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int MAPSIZE =8;
const int SHIPSNUMBER = 10;

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

    //resultOfShoot = checkShoot(Bloc, Aattack, shipsA, shoot_number_x - 1 , shoot_number_y - 1); // shipsA - только здесь это корабли жертвы
    resultOfShoot = checkShoot(Bloc, shoot_number_x -1, shoot_number_y);

    printf("You pick %c:%d - you get %c\n", shoot_letter_y, shoot_number_x, resultOfShoot);
    // выводит аски код числа


    return 0;
}