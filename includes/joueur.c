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
    Position position; //position du joueur
    int score; //score du joueur
} joueur;

//initialise un joueur
joueur *initJoueur(char *id, char *ip, char *port) {
    joueur *j = malloc(sizeof(*j));
    assert(j != NULL);
    strcpy(j->id, id);
    strcpy(j->ip, ip);
    strcpy(j->port, port);
    j->position.x = 0;
    j->position.y = 0;
    j->score = 0;
    return j;
}

//libere la memoire d'un joueur
void freeJoueur(joueur *j) {
    assert(j != NULL);
    free(j);
}

int main() {
    Playerlist *test = NULL;
    printf("%d \n", lengthPlayer(test));
    addPlayer(&test, "lalalala", "1234");
    addPlayer(&test, "lolololo", "5678");
    addPlayer(&test, "lilolyrp", "2587");
    addPlayer(&test, "davydavy", "6666");
    printf("%d \n", lengthPlayer(test));
    Playerlist *dvy_chh = searchPlayer(test, "davydavy");
    printf("ID: %s \n", dvy_chh->id);
    printf("RMV : %d\n", rmvPlayer(test, "lalalala"));
    printf("%d \n", lengthPlayer(test));
    return 0;
}


