#include "labyrinthe.h"

Lab* init(int x, int y, uint8_t ghosts) {
    Lab* lab = malloc(sizeof(Lab));
    lab->x = x;
    lab->y = y;
    lab->matrice = malloc(sizeof(char*) * x);
    for (int i = 0; i < x; i++) {
        lab->matrice[i] = malloc(sizeof(char) * y);
    }
    lab->ghosts = ghosts;
    fillLab(lab, ghosts);
    return lab;
}

void printLab(Lab *l) {
    for (int i = 0; i < l->x; i++) {
        for (int j = 0; j < l->y; j++) {
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
                if (py + 2 < l->y) {
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
                if (px + 2 < l->x) {
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

void ghost(Lab *l, uint8_t nb) {
    for (int i = 0; i < nb; i++) {
        int x = rand() % l->x;
        int y = rand() % l->y;
        while (l->matrice[x][y] != ' ') {
            x = rand() % l->x;
            y = rand() % l->y;
        }
        l->matrice[x][y] = 'G';
    }
}

Lab fillLab(Lab *l, uint8_t nb) {
    for (int x = 0; x < l->x; x++) {
        for (int y = 0; y < l->y; y++) {
            l->matrice[x][y] = 'n';
        }
    }
    for (int x = 0; x < l->x; x += 2) {
        for (int y = 0; y < l->y; y++) {
            l->matrice[x][y] = '+';
        }
    }
    for (int x = 0; x < l->x; x++) {
        for (int y = 0; y < l->y; y += 2) {
            l->matrice[x][y] = '+';
        }
    }

    srand(time(NULL));
    int px = rand() % l->x;
    int py = rand() % l->y;
    while (l->matrice[px][py] == '+') {
        px = rand() % l->x;
        py = rand() % l->y;
    }

    createLab(l, px, py);
    ghost(l, nb);
    return *l;
}

/*
int main() {
    Lab* test = init(10, 10, 5);
    printLab(test);
    return 0;
}
*/