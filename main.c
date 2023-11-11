#include <stdio.h>
#include <stdlib.h>

const int N =8;

int getY(char letter) {
    switch (letter) {
        case 'a':
        return 0;
        break;
        default:
        return -1;
    }
}

void createMaps(char newmap[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            newmap[i][j] = '~';
        }
    }
}

struct Ship {
    char letter1;
    int x1;
    char letter2;
    int x2;
};

int main() {
    char line[10][6];
    //char line2[6];
    char Aloc[N][N], Aattack[N][N];
    char Bloc[N][N], Battack[N][N];
    struct Ship ship1;
    struct Ship shipsA[10], shipsB[10];


    FILE *file = fopen("write.txt", "r");

    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return 1;
    }
    // Читання в циклу 
    for (int i = 0; i < 10; i++) {
        fscanf(file, "%c%c %c%c\n", &line[i][0], &line[i][1], &line[i][2], &line[i][3]);
    }


    fclose(file);
    int a, b;
    // запис кораблів
    for (int i = 0; i < 10; i++) {
        a = line[i][1] - '0';
        b = line[i][3] - '0';
    
        shipsA[i].letter1 = line[i][0];
        shipsA[i].x1 = a;
        shipsA[i].letter2 = line[i][2];
        shipsA[i].x2 = b;
        printf("Ship %d coordinates %c:%d - %c:%d\n", i+1, shipsA[i].letter1, shipsA[i].x1, shipsA[i].letter2, shipsA[i].x2);
    }


    createMaps(Aloc);
    //createMaps(Bloc);
    createMaps(Aattack);
    //createMaps(Battack);

    return 0;
}