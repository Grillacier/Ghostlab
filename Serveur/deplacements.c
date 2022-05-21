#include "../includes/labyrinthe.h"
#include "../includes/position.h"
#include "../includes/joueur.h"

int upmove(Lab* lab, joueur* p, char* dir) {
    int ghost = 0;
    int d = atoi(dir);
    int x = atoi(p->position.x);
    int y = atoi(p->position.y);
    int i;

    for (i = 0; i < d; i++) {
        if ( x - i - 1 < 0 || lab->matrice[x - i - 1][y] == '+')
            break;
        if (lab->matrice[x-i][y] == 'G') {
            lab->matrice[x-i][y] = ' ';
            ghost++;
            p->score += 10;
        }
    }
    lab->matrice[x][y] = ' ';
    sprintf(p->position.x, "%03d" , x-i);
    lab->matrice[x-i][y] = '@';
    return ghost;
}

int downmove(Lab* lab, joueur* p, char* dir) {
    int ghost = 0;
    int d = atoi(dir);
    int x = atoi(p->position.x);
    int y = atoi(p->position.y);
    int i;

    for (i = 0; i < d; i++) {
        if (x + i + 1 > lab->x || lab->matrice[x + i + 1][y] == '+')
            break;
        if (lab->matrice[x+i][y] == 'G') {
            lab->matrice[x+i][y] = ' ';
            ghost++;
            p->score += 10;
        }
    }
    lab->matrice[x][y] = ' ';
    sprintf(p->position.x, "%03d" , x+i);
    lab->matrice[x+i][y] = '@';
    return ghost;
}

int leftmove(Lab* lab, joueur* p, char* dir) {
    int ghost = 0;
    int d = atoi(dir);
    int x = atoi(p->position.x);
    int y = atoi(p->position.y);
    int i;

    for (i = 0; i < d; i++) {
        if (y - i - 1 < 0 || lab->matrice[x][y-i-1] == '+')
            break;
        if (lab->matrice[x][y-i] == 'G') {
            lab->matrice[x][y-i] = ' ';
            ghost++;
            p->score += 10;
        }
    }
    lab->matrice[x][y] = ' ';
    sprintf(p->position.y, "%03d" , y-i);
    lab->matrice[x][y-i] = '@';
    return ghost;
}

int rightmove(Lab* lab, joueur* p, char* dir) {
    int ghost = 0;
    int d = atoi(dir);
    int x = atoi(p->position.x);
    int y = atoi(p->position.y);
    int i;

    for (i = 0; i < d; i++) {
        if (y + i + 1 > lab->y || lab->matrice[x][y+i+1] == '+')
            break;
        if (lab->matrice[x][y+i] == 'G') {
            lab->matrice[x][y+i] = ' ';
            ghost++;
            p->score += 10;
        }
    }
    lab->matrice[x][y] = ' ';
    sprintf(p->position.y, "%03d" , y+i);
    lab->matrice[x][y+i] = '@';
    return ghost;
}

int main() {
    Lab* test = init(10, 10, 5);
    test->matrice[1][1] = '@';
    printLab(test);
    joueur* p = initJoueur("prout123", "127.0.0.1######", "5678");
    printf("on veut monter\n");
    upmove(test, p, "3");
    printLab(test);
    printf("on est monté\n");
    printf("on veut descendre\n");
    downmove(test, p, "3");
    printLab(test);
    printf("on est descendu\n");
    printf("on veut gauche\n");
    leftmove(test, p, "3");
    printLab(test);
    printf("on est allé à gauche\n");
    printf("on veut droite\n");
    rightmove(test, p, "3");
    printLab(test);
    printf("on est allé à droite\n");
    return 0;
}