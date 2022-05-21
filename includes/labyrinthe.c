#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define X 20
#define Y 20
typedef struct labyrinthe {

    char matrice[X][Y];
    // TODO: Ajoutez fantomes
    // TODO: Ajoutez tableaux de point??

} Lab;

void printLab(Lab* l) {
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            printf("%c ", l->matrice[i][j]);
        }
        printf("\n");
    }
}


int notIllegal(Lab l, int px, int py) {
    if (px < 0 || px > X - 1) {
        return -1;
    }
    if (py < 0 || py > Y - 1) {
        return -1;
    }
    return 1;
}

int surrounded(Lab l, int px, int py) {
    if (notIllegal(l, px, py + 1) == 1) {
        return 1;
    }
    if (notIllegal(l, px, py - 1) == 1) {
        return 1;
    }
    if (notIllegal(l, px + 1, py) == 1) {
        return 1;
    }
    if (notIllegal(l, px - 1, py) == 1) {
        return 1;
    }
    return -1;
}

Lab createLab(Lab* l, int px, int py) {
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
}


Lab fillLab(Lab* l) {
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

    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            if (l->matrice[x][y] == 'v') {
                l->matrice[x][y] = ' ';
            }
        }
    }
}


int main() {
    Lab* test;
    fillLab(test);
    printLab(test);
    return 0;
}
