#include "position.h"

int setPos(Position* p, char* x, char* y) {
    strcpy(p->x, x);
    strcpy(p->y, y);
    return 1;
}

int addToChar(Position* p, char* base, char* ajout) { // Addition de char
    int x = atoi(base);
    int plus = atoi(ajout);
    int res = x + plus;
    sprintf(p->x, "%03d", res);
    /* 0 : caractère avec lequel on veut compléter la chaîne
     * 3 : taille de la chaîne
     * le caractère de fin \0 est ajouté par sprintf */
    return 1;
}

int rmToChar(Position* p, char* base, char* ajout) { // Soustraction de char
    int x = atoi(base);
    int moins = atoi(ajout);
    int res = x - moins;
    sprintf(p->x, "%03d", res);
    return 0;
}