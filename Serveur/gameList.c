#include "../includes/gameList.h"
#include "../includes/joueur.h"

//Fonction de tableau
uint8_t length(Gamelist list[]) {
    uint8_t taille = 0;
    for (int i = 0; i < 100; i++) {
        if (list[i].create == 1 && list[i].started != -1) {
            taille = taille + 1;
        }
    }
    return taille;
}

uint8_t findRoom(Gamelist list[]) {
    for (int i = 0; i < 100; i++) {
        if (list[i].create == 0) {
            return i;
        }
    }
    return -1;
}

//Fonction d'unite
uint8_t getNbPlayer(Gamelist list) {
    uint8_t nbp = 0;
    for (int i = 0; i < 5; i++) {
        if (list.player_list[i].place == 1) {
            nbp = nbp + 1;
        }
    }
    return nbp;
}

Gamelist addPlayerTo(Gamelist list, char *id, char *p) {
    int libre = findPlace(list.player_list);
    if (libre == -1) {
        perror("Partie complete \n");
    }
    list.player_list[libre] = addPlayer(list.player_list[libre], id, p);
    printf("Inscrit! \n");
    return list;
}

int isCreate(Gamelist list) {
    return list.create;
}

Gamelist upStart(Gamelist list) {
    list.started = list.started + 1;
    if (getNbPlayer(list) == list.started) {
        list.started = 6;
    }
    return list;
}

Gamelist create(Gamelist list) {
    list.create = 1;
    return list;
}

Gamelist setUpList(Gamelist list) {
    list.started = 0;
    list.create = 0;
    for (int i = 0; i < 5; i++) {
        list.player_list[i] = setUpPlayer(list.player_list[i]);
    }
    return list;
}