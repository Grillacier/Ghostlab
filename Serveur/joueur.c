#include "../includes/joueur.h"

//initialise un joueur
joueur *initJoueur(char *id, char *ip, char *port) {
    joueur *j = malloc(sizeof(*j));
    assert(j != NULL);
    strcpy(j->id, id);
    strcpy(j->ip, ip);
    strcpy(j->port, port);
    j->score = 0;
    return j;
}

/*
int main() {
    Lab *l = initLab(10, 10, 5);
    printLab(l);
    joueur *jeromine = initJoueur(l, "jeromine", "127.0.0.1######", "8080");
    printf("id : %s\n", jeromine->id);
    printf("ip : %s\n", jeromine->ip);
    printf("port : %s\n", jeromine->port);
    printf("x : %s\n", jeromine->x);
    printf("y : %s\n", jeromine->y);
    printf("score : %d\n", jeromine->score);
    return 0;
}
*/
