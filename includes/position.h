#ifndef POSITION_H
#define POSITION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct position {
    char x[4];
    char y[4];
} Position;

int setPos(Position* p, char* x, char* y);
int addToChar(Position* p, char* base, char* ajout);
int rmToChar(Position* p, char* base, char* ajout);

#endif //POSITION_H
