#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct labyrinthe {
    char** matrice;
    uint16_t x;
    uint16_t y;
    uint8_t ghosts;
} Lab;

Lab* init(int x, int y, uint8_t ghosts);
void printLab(Lab *l);
Lab createLab(Lab *l, int px, int py);
void ghost(Lab *l, uint8_t nb);
Lab fillLab(Lab *l, uint8_t nb);

#endif //LABYRINTHE_H
