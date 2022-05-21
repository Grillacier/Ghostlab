#ifndef JOUEUR_H
#define JOUEUR_H

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct joueur {
    char id[9]; //identifiant joueur
    char ip[16]; //adresse IP du joueur
    char port[5]; //numero de port du joueur
    char x[4]; //position x du joueur
    char y[4]; //position y du joueur
    int score; //score du joueur
} joueur;

joueur* initJoueur(char *id, char *ip, char *port);

#endif //JOUEUR_H
