#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define X 20
#define Y 20

typedef struct labyrinthe {
    char matrice[X][Y];
    int ghosts;

} Lab;

void printLab(Lab *l) {
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            printf("%c ", l->matrice[i][j]);
        }
        printf("\n");
    }
}

Lab createLab(Lab *l, int px, int py) {
    l->matrice[px][py] = ' ';
    int way = rand() % 4;

    for (int i = 0; i < 4; i++) {
        way = (way + 1) % 4;
        switch (way) {
            case 0:
                if (py + 2 < Y) {
                    if (l->matrice[px][py + 2] == 'n') {
                        l->matrice[px][py + 1] = ' ';
                        createLab(l, px, py + 2);
                    }
                }
                break;

            case 1:
                if (py - 2 > 0) {
                    if (l->matrice[px][py - 2] == 'n') {
                        l->matrice[px][py - 1] = ' ';
                        createLab(l, px, py - 2);
                    }
                }
                break;

            case 2:
                if (px + 2 < X) {
                    if (l->matrice[px + 2][py] == 'n') {
                        l->matrice[px + 1][py] = ' ';
                        createLab(l, px + 2, py);
                    }
                }
                break;

            case 3:
                if (px - 2 > 0) {
                    if (l->matrice[px - 2][py] == 'n') {
                        l->matrice[px - 1][py] = ' ';
                        createLab(l, px - 2, py);
                    }
                }
                break;

            default:
                break;
        }
    }
    return *l;
}

void ghost(Lab *l, int nb) {
    for (int i = 0; i < nb; i++) {
        int x = rand() % X;
        int y = rand() % Y;
        while (l->matrice[x][y] != ' ') {
            x = rand() % X;
            y = rand() % Y;
        }
        l->matrice[x][y] = 'G';
    }
}

Lab fillLab(Lab *l, int nb) {
    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            l->matrice[x][y] = 'n';
        }
    }
    for (int x = 0; x < X; x += 2) {
        for (int y = 0; y < Y; y++) {
            l->matrice[x][y] = '+';
        }
    }
    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y += 2) {
            l->matrice[x][y] = '+';
        }
    }

    srand(time(NULL));
    int px = rand() % X;
    int py = rand() % Y;
    while (l->matrice[px][py] == '+') {
        px = rand() % X;
        py = rand() % Y;
    }

    createLab(l, px, py);
    ghost(l, nb);
    return *l;
}

/*
int main() {
    Lab* test;
    test->ghosts = 5;
    fillLab(test, test->ghosts);
    printLab(test);
    return 0;
}
*/