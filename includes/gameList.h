#ifndef GAMELIST_H
#define GAMELIST_H

#include <stdio.h>
#include <stdint.h>

typedef struct gamelist{
    joueur player_list [5];
    int started; // 6 si lancé
    char ip_cast [16]; // TODO: Implementer l'addresse
    char port_cast [5]; //TODO: De meme
    int create;
}Gamelist;

uint8_t length(Gamelist list[]);
uint8_t findRoom(Gamelist list[]);
uint8_t getNbPlayer(Gamelist list);
Gamelist addPlayerTo(Gamelist list, char *id, char *p);
int isCreate(Gamelist list);
Gamelist upStart(Gamelist list);
Gamelist create(Gamelist list);
Gamelist setUpList(Gamelist list);

#endif GAMELIST_H
