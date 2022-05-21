#ifndef GAMELIST_H
#define GAMELIST_H

#include <stdio.h>
#include <stdint.h>
#include "joueur.h"
#include "labyrinthe.h"

typedef struct gamelist{
    Lab *lab;
    joueur player_list [5];
    int started; // 6 si lance
    char port_cast [5]; 
    int create;
}Gamelist;

uint8_t length(Gamelist list[]);
uint8_t findRoom(Gamelist list[]);
uint8_t getNbPlayer(Gamelist list);
Gamelist addPlayerTo(Gamelist list, char *id, char *p);
int isCreate(Gamelist list);
Gamelist upStart(Gamelist list);
Gamelist create(Gamelist list);
Gamelist setUpList(Gamelist list, int i);

#endif //GAMELIST_H
