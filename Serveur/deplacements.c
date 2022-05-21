#include "../includes/labyrinthe.h"
#include "../includes/joueur.h"

int upmove(Lab* lab, joueur *p, char* dir) {
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
        }
    }
    lab->matrice[x][y] = ' ';
    sprintf(p->x, "%03d" , x-i);
    char initial = p->id[0];
    lab->matrice[x-i][y] = initial;
    return ghost;
}

int downmove(Lab* lab, joueur *p, char* dir) {
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
        }
    }
    lab->matrice[x][y] = ' ';
    sprintf(p->x, "%03d" , x+i);
    char initial = p->id[0];
    lab->matrice[x+i][y] = initial;
    return ghost;
}

int leftmove(Lab* lab, joueur *p, char* dir) {
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
        }
    }
    lab->matrice[x][y] = ' ';
    sprintf(p->y, "%03d" , y-i);
    char initial = p->id[0];
    lab->matrice[x][y-i] = initial;
    return ghost;
}

int rightmove(Lab* lab, joueur *p, char* dir) {
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
        }
    }
    lab->matrice[x][y] = ' ';
    sprintf(p->y, "%03d" , y+i);
    char initial = p->id[0];
    lab->matrice[x][y+i] = initial;
    return ghost;
}

/*
int main() {
    Lab* test = initLab(10, 10, 5);
    printLab(test);
    printf("on crée un joueur\n");
    joueur p = initJoueur("prout123", "127.0.0.1######", "5678");
    printf("on initialise sa position\n");
    initPos(test, &p);
    printf("p.x : %s\n", p.x);
    printf("p.y : %s\n", p.y);
    printf("on le place dans le labyrinthe\n");
    player(test, p);

    printf("on veut monter\n");
    upmove(test, &p, "3");
    printLab(test);
    printf("on est monté\n");

    printf("on veut descendre\n");
    downmove(test, &p, "3");
    printLab(test);
    printf("on est descendu\n");

    printf("on veut gauche\n");
    leftmove(test, &p, "3");
    printLab(test);
    printf("on a gauche\n");

    printf("on veut droite\n");
    rightmove(test, &p, "3");
    printLab(test);
    printf("on a droite\n");
    return 0;
}
*/