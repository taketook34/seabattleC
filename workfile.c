#include <stdio.h>
#include <stdlib.h>


#include "config.h"
#include "map.h"

// добавить функцию которая проверяет содержимое файла на правильность


void getfileships(char *filename, struct Ship *shipslist) {
    char line[SHIPSNUMBER][6];
    int xa, xb, ya, yb;
    FILE *file = fopen(filename, "r");

    // Читання в циклу 
    for (int i = 0; i < SHIPSNUMBER; i++) {
        fscanf(file, "%c%c %c%c\n", &line[i][0], &line[i][1], &line[i][2], &line[i][3]);
    }
    fclose(file);

    // формування масиву
    for (int i = 0; i < SHIPSNUMBER; i++) {
        // СДЕЛАТЬ В БУДУЩЕМ: тут также сделать для корбалей для B и переписать что бы они были от меньшей к большей координате
        xa = line[i][1] - '0';
        xb = line[i][3] - '0';
        xa -= 1;
        xb -= 1;
        ya = getY(line[i][0]);
        yb = getY(line[i][2]);

        if (xa == xb && yb < ya) {
            shipslist[i].letter1 = yb;
            shipslist[i].x1 = xb;
            shipslist[i].letter2 = ya;
            shipslist[i].x2 = xa;
            shipslist[i].lenght = ya - yb + 1;
        } else if (yb == ya && xb < xa) {
            shipslist[i].letter1 = yb;
            shipslist[i].x1 = xb;
            shipslist[i].letter2 = ya;
            shipslist[i].x2 = xa;
            shipslist[i].lenght = xa - xb + 1;
        } else if (yb != ya && xb != xa) {
            fprintf(stderr, "Error in file");
            //return 1;
        } else {
            shipslist[i].letter1 = ya;
            shipslist[i].x1 = xa;
            shipslist[i].letter2 = yb;
            shipslist[i].x2 = xb;
            shipslist[i].lenght = (yb - ya) + (xb - xa) + 1;
        }

        //printf("%d\n", shipsA[i].lenght);
        //printf("Ship %d coordinates %c:%d - %c:%d\n", i+1, shipsA[i].letter1, shipsA[i].x1, shipsA[i].letter2, shipsA[i].x2);
    }
}