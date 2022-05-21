#ifndef JOUEUR_H
#define JOUEUR_H

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "labyrinthe.h"

typedef struct joueur {
    char id[9]; //identifiant joueur
    char ip[16]; //adresse IP du joueur
    char port[5]; //numero de port du joueur
    Position position; //position du joueur
    int score; //score du joueur
} joueur;

typedef struct position {
    char x[4];
    char y[4];
} Position;

joueur *initJoueur(char *id, char *ip, char *port);
void initPos(Lab* l, joueur* p);

#endif //JOUEUR_H
