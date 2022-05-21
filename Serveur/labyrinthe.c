#include "../includes/labyrinthe.h"

//initialisation du labyrinthe avec les fantomes
Lab* initLab(int x, int y, uint8_t ghosts) {
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

//affichage du labyrinthe
void printLab(Lab *l) {
    //imprimer le numero de la colonne
    printf("  ");
    for (int i = 0; i < l->x; i++) {
        printf("%d ", i);
    }
    printf("\n");

    //imprimer le numero de la ligne et la matrice
    for (int i = 0; i < l->y; i++) {
        printf("%d ", i);
        for (int j = 0; j < l->x; j++) {
            printf("%c ", l->matrice[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//creation du chemin du labyrinthe
Lab createLab(Lab *l, int px, int py) {
    l->matrice[px][py] = ' ';
    int way = rand() % 4;

    for (int i = 0; i < 4; i++) {
        way = (way + 1) % 4;
        switch (way) {
            case 0:
                if (py + 2 < l->y) {
                    if (l->matrice[px][py + 2] == '&') {
                        l->matrice[px][py + 1] = ' ';
                        createLab(l, px, py + 2);
                    }
                }
                break;

            case 1:
                if (py - 2 > 0) {
                    if (l->matrice[px][py - 2] == '&') {
                        l->matrice[px][py - 1] = ' ';
                        createLab(l, px, py - 2);
                    }
                }
                break;

            case 2:
                if (px + 2 < l->x) {
                    if (l->matrice[px + 2][py] == '&') {
                        l->matrice[px + 1][py] = ' ';
                        createLab(l, px + 2, py);
                    }
                }
                break;

            case 3:
                if (px - 2 > 0) {
                    if (l->matrice[px - 2][py] == '&') {
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

//placement des fantomes
void ghost(Lab *l, uint8_t nb) {
    for (int i = 0; i < nb; i++) {
        int x = rand() % l->x;
        int y = rand() % l->y;
        while (l->matrice[x][y] != ' ') {
            x = rand() % l->x;
            y = rand() % l->y;
        }
        l->matrice[x][y] = '#';
    }
}

//place le joueur dans le labyrinthe
joueur* initPos(Lab* l, joueur* p) {
    srand(time(NULL));
    int x = rand() % l->x;
    int y = rand() % l->y;
    while (l->matrice[x][y] != ' ') {
        x = rand() % l->x;
        y = rand() % l->y;
    }
    sprintf(p->x, "%03d", x);
    sprintf(p->y, "%03d", y);
    return p;
}

//placer un joueur
joueur player(Lab *l, joueur j) {
    if (l->matrice[atoi(j.x)][atoi(j.y)] == ' ') {
        char initial = j.id[0];
        l->matrice[atoi(j.x)][atoi(j.y)] = initial;
    }
    return j;
}

//remplissage final du labyrinthe
Lab fillLab(Lab *l, uint8_t nb) {
    for (int x = 0; x < l->x; x++) {
        for (int y = 0; y < l->y; y++) {
            l->matrice[x][y] = '&';
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

//deplacements
int upmove(Lab* lab, joueur *p, char* dir, char* port) {
    int ghost = 0;
    int d = atoi(dir);
    int x = atoi(p->x);
    int y = atoi(p->y);
    int i;

    for (i = 0; i < d; i++) {
        if ( x - i - 1 < 0 || lab->matrice[x - i - 1][y] == '+')
            break;
        if (lab->matrice[x-i][y] == '#') {
            lab->matrice[x-i][y] = ' ';
            ghost++;
            p->score += 10;
            //[SCORE␣id␣p␣x␣y+++]
            char msg[50];
            sprintf(msg, "SCORE %s %04d %s %s+++", p->id, p->score, p->x, p->y);
            sendMess(port, msg);
        }
    }
    lab->matrice[x][y] = ' ';
    sprintf(p->x, "%03d" , x-i);
    char initial = p->id[0];
    lab->matrice[x-i][y] = initial;
    return ghost;
}

int downmove(Lab* lab, joueur *p, char* dir, char* port) {
    int ghost = 0;
    int d = atoi(dir);
    int x = atoi(p->x);
    int y = atoi(p->y);
    int i;

    for (i = 0; i < d; i++) {
        if (x + i + 1 >= lab->x || lab->matrice[x + i + 1][y] == '+')
            break;
        if (lab->matrice[x+i][y] == '#') {
            lab->matrice[x+i][y] = ' ';
            ghost++;
            p->score += 10;
            //[SCORE␣id␣p␣x␣y+++]
            char msg[50];
            sprintf(msg, "SCORE %s %04d %s %s+++", p->id, p->score, p->x, p->y);
            sendMess(port, msg);
        }
    }
    lab->matrice[x][y] = ' ';
    sprintf(p->x, "%03d" , x+i);
    char initial = p->id[0];
    lab->matrice[x+i][y] = initial;
    return ghost;
}

int leftmove(Lab* lab, joueur *p, char* dir, char* port) {
    int ghost = 0;
    int d = atoi(dir);
    int x = atoi(p->x);
    int y = atoi(p->y);
    int i;

    for (i = 0; i < d; i++) {
        if (y - i - 1 < 0 || lab->matrice[x][y-i-1] == '+')
            break;
        if (lab->matrice[x][y-i] == '#') {
            lab->matrice[x][y-i] = ' ';
            ghost++;
            p->score += 10;
            //[SCORE␣id␣p␣x␣y+++]
            char msg[50];
            sprintf(msg, "SCORE %s %04d %s %s+++", p->id, p->score, p->x, p->y);
            sendMess(port, msg);
        }
    }
    lab->matrice[x][y] = ' ';
    sprintf(p->y, "%03d" , y-i);
    char initial = p->id[0];
    lab->matrice[x][y-i] = initial;
    return ghost;
}

int rightmove(Lab* lab, joueur *p, char* dir, char* port) {
    int ghost = 0;
    int d = atoi(dir);
    int x = atoi(p->x);
    int y = atoi(p->y);
    int i;

    for (i = 0; i < d; i++) {
        if (y + i + 1 >= lab->y || lab->matrice[x][y+i+1] == '+')
            break;
        if (lab->matrice[x][y+i] == '#') {
            lab->matrice[x][y+i] = ' ';
            ghost++;
            p->score += 10;
            //[SCORE␣id␣p␣x␣y+++]
            char msg[50];
            sprintf(msg, "SCORE %s %04d %s %s+++", p->id, p->score, p->x, p->y);
            sendMess(port, msg);
        }
    }
    lab->matrice[x][y] = ' ';
    sprintf(p->y, "%03d" , y+i);
    char initial = p->id[0];
    lab->matrice[x][y+i] = initial;
    return ghost;
}