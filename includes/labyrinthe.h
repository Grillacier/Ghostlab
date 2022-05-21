#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "messageUDP.h"
#include "joueur.h"

typedef struct labyrinthe {
    char** matrice;
    uint16_t x;
    uint16_t y;
    uint8_t ghosts;
} Lab;

Lab* initLab(int x, int y, uint8_t ghosts);
void printLab(Lab *l);
Lab createLab(Lab *l, int px, int py);
void ghost(Lab *l, uint8_t nb);
joueur* initPos(Lab* l, joueur* p);
joueur player(Lab *l, joueur j);
Lab fillLab(Lab *l, uint8_t nb);
int upmove(Lab* lab, joueur *p, char* dir, char* port);
int downmove(Lab* lab, joueur *p, char* dir, char* port);
int leftmove(Lab* lab, joueur *p, char* dir, char* port);
int rightmove(Lab* lab, joueur *p, char* dir, char* port);

#endif //LABYRINTHE_H
