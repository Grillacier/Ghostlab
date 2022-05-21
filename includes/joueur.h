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
    int place; // 0 libre , 1 prise
    char port[5]; //numero de port du joueur
    char x[4]; //position x du joueur
    char y[4]; //position y du joueur
    int score; //score du joueur
} joueur;

joueur initJoueur(char *id, char *ip, char *port);
joueur setUpPlayer(joueur p);
joueur addPlayer(joueur list, char *id , char *p);
joueur rmvPlayer(joueur p);
int findPlace(joueur list[]);
int searchById(joueur list[], char *ide);

#endif //JOUEUR_H
