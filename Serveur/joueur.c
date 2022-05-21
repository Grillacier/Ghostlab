#include "../includes/joueur.h"

//initialise un joueur
joueur initJoueur(char *id, char *ip, char *port) {
    joueur j;
    strcpy(j.id, id);
    strcpy(j.ip, ip);
    strcpy(j.port, port);
    j.place = 0;
    j.score = 0;
    return j;
}

// Fonction d'unite
joueur setUpPlayer(joueur p) {
    p.place = 0;
    return p;
}

joueur addPlayer(joueur list, char *id , char *p) {
    strcpy(list.id ,id);
    list.id[8] = '\n';
    strcpy(list.port,p);
    list.port[4] = '\n';
    list.place = 1;
    return list;
}

joueur rmvPlayer(joueur p) {
    p.place = 0;
    return p;
}

// Fonction de liste
int findPlace(joueur list[]) {
    for(int i = 0; i<5; i++){
        if(list[i].place == 0){
            return i;
        }
    }
    return -1;
}

int searchById(joueur list[], char *ide) {
    for(int i = 0 ;i<5;i++){
        if(strncmp(list[i].id,ide,8) == 0){
            return i;
        }
    }
    return -1;
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
