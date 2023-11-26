#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "map.h"
#include "config.h"
#include "workfile.h"


int main(int argc, char *argv[]) {
    char line[SHIPSNUMBER][6];
    char Aloc[MAPSIZE][MAPSIZE], Aattack[MAPSIZE][MAPSIZE];
    char Bloc[MAPSIZE][MAPSIZE], Battack[MAPSIZE][MAPSIZE];
    struct Ship shipsA[SHIPSNUMBER], shipsB[SHIPSNUMBER];
    struct FireShoot fireshoot;

    int Ascore = 0;
    int Bscore = 0;

    // написать проверку входных параметров

    if (argc != 3) {
        perror("Wrong number of parametres");
        return 1;
    }

    // проверка соществования файла

    if (access(argv[1], F_OK) != 0 && access(argv[2], F_OK) != 0 ) {
        perror("One of files is not exist");
        return 1;
    }

    getfileships(argv[1], shipsA);
    getfileships(argv[2], shipsB);
    

    createMaps(Aloc);
    createShipsMap(Aloc, shipsA);
    createMaps(Aattack);
    showShips(Aloc);
    printf("\n");
    createMaps(Bloc);
    createShipsMap(Bloc, shipsB);    
    createMaps(Battack);
    showShips(Bloc);

    // НАЧАЛО ИГРЫ


    char shoot_letter_y;
    int shoot_number_x, shoot_number_y;
    char resultOfShoot;

    printf("Hello, everyone! Welocome to Sea Battle game!\n");
    printf("Okay, let's start\n");
    
    do {
        do {
            printf("User A, type letter to shoot: ");
            scanf(" %c", &shoot_letter_y);  // СДЕЛАТЬ В БУДУЩЕМ: добавить проверку что бы буква проверялась
            shoot_number_y = getY(shoot_letter_y);

            printf("Type number to shoot: ");
            scanf(" %d", &shoot_number_x);


            resultOfShoot = checkShoot(Bloc, shoot_number_x -1, shoot_number_y);
            fireshoot.x = shoot_number_x - 1;
            fireshoot.y = shoot_number_y;
            fireshoot.res = resultOfShoot;


            printf("You pick %c:%d\n", shoot_letter_y, shoot_number_x);
            // shipsA - только здесь это корабли жертвы, надо свой shipsB иметь
            registerShoot(Bloc, Aattack, &Ascore, shipsB, fireshoot);
            printf("\n");
            showShips(Aattack);

            if (Ascore == SHIPSNUMBER) {
                printf("GAME END! Winner is user A\n");
                return 0;
            } else {
                printf("Your score: %d\n", Ascore);
            }

        } while (fireshoot.res != WATER);

        do {
            printf("User B, type letter to shoot: ");
            scanf(" %c", &shoot_letter_y);  // СДЕЛАТЬ В БУДУЩЕМ: добавить проверку что бы буква проверялась
            shoot_number_y = getY(shoot_letter_y);

            printf("Type number to shoot: ");
            scanf(" %d", &shoot_number_x);


            resultOfShoot = checkShoot(Aloc, shoot_number_x -1, shoot_number_y);
            fireshoot.x = shoot_number_x - 1;
            fireshoot.y = shoot_number_y;
            fireshoot.res = resultOfShoot;


            printf("You pick %c:%d\n", shoot_letter_y, shoot_number_x);
            // shipsA - только здесь это корабли жертвы, надо свой shipsB иметь
            registerShoot(Aloc, Battack, &Bscore, shipsA, fireshoot);
            printf("\n");
            showShips(Battack);

            if (Bscore == SHIPSNUMBER) {
                printf("GAME END! Winner is user B\n");
                return 0;
            } else {
                printf("Your score: %d\n", Bscore);
            }
                

        } while (fireshoot.res != WATER);

    } while (2 < 3);


    return 0;
}