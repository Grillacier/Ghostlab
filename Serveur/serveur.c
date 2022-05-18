#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <stdint.h>
#include "../includes/gameList.c"
#include "sendCode.c"

//Variable global
uint8_t nbgame = 0;
Gamelist *list = NULL;


//Verrou
pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;

int chooseGame(int sock, char * receiver) {
    //while (1) {
        //void *receiver = malloc(24);
        Gamelist *threadList = list;

       /* if (recv(sock, receiver, sizeof(char) * 20 + sizeof(uint8_t), 0) == 0) {
            perror("Cannot receive registration");
        }*/


        char request[6];
        memmove(&request, receiver, sizeof(char) * 5);
        request[5] = '\0';
        if (strncmp(receiver, "NEWPL",5) == 0) {
            char id[9];
            memmove(&id, receiver + sizeof(char) * 6, sizeof(char) * 8);
            id[8] = '\0';
            char p[5];
            memmove(&p, receiver + sizeof(char) * 15, sizeof(char) * 4);
            p[4] = '\0';

            Gamelist *threadList = list;
            printf("Creation of new game...");
            pthread_mutex_lock(&verrou);
            uint8_t nwgame = add(&list);
            addPlayerTo(threadList, nwgame, id, p);

            pthread_mutex_unlock(&verrou);
            if (nwgame != 0) {
                sendRegok(sock, nwgame);
                return 1;
            }
            sendRegno(sock);
            return 0;


        } else if (strncmp(request, "REGIS",5)==0) {
            char id[9];
            memmove(&id, receiver + sizeof(char) * 6, sizeof(char) * 8);
            id[8] = '\0';
            char p[5];
            memmove(&p, receiver + sizeof(char) * 16, sizeof(char) * 4);
            p[4] = '\0';
            uint8_t id_game = 0;
            memmove(&id_game, receiver + sizeof(char) * 21, sizeof(uint8_t));
            pthread_mutex_lock(&verrou);
            if (addPlayerTo(threadList, id_game, id, p) == 0) {
                sendRegno(sock);
                return 0;
            }
            pthread_mutex_unlock(&verrou);
            sendRegok(sock, id_game);
            return id_game;
        }

   // }

}

void *lobby(void *sock) {
    // Variable de thread
    int sock2 = *(int *) sock;
    uint8_t ur_game_id = 0;
    char ur_id[8];
    // ------
    pthread_mutex_lock(&verrou);
    if (sendGames(sock2, nbgame) == 0) {
        printf("ERREUR");
    }
    Gamelist *threadList = list;

    while (threadList != NULL) {
        sendOgame(sock2, threadList->num, threadList->nb_player);
        threadList = threadList->next;
    }

    pthread_mutex_unlock(&verrou);
    char receiver[100];
    while (1) {
        int rec = recv(sock2, receiver, 99, 0);
        if ( rec == 0) {
            perror("Cannot receive registration");

        }
        receiver[rec] = '\0';
        if(strncmp(receiver, "NEWPL", 5)==0) {
            ur_game_id = chooseGame(sock2, receiver);
            if (ur_game_id != 0) {
                printf(" Vous etes inscrit, TODO");
            }
            else {
                printf("Vous n'etes pas inscrit");
            }
        }else if(strncmp(receiver, "UNREG", 5)==0){
            //TODO: le reste
        }

        /*
        while (ur_game_id != 0) {
            printf(" Vous etes inscrit, TODO");
        }
        printf("Vous n'etes pas inscrit");
         */
    }
}


int main(int argc, char* argv[]) {
    if(argc!=2){
        printf("Usage : ./serveur <portTCP>\n");
        return -1;
    }

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address_sock;
    address_sock.sin_family = AF_INET;
    address_sock.sin_port = htons(atoi(argv[1]));
    address_sock.sin_addr.s_addr = htonl(INADDR_ANY);
    int r = bind(sock, (struct sockaddr *) &address_sock, sizeof(struct sockaddr_in));
    if (r == 0) {
        r = listen(sock, 0);
        while (1) {
            struct sockaddr_in caller;
            socklen_t size = sizeof(caller);
            int *sock2 = (int *) malloc(sizeof(int));
            *sock2 = accept(sock, (struct sockaddr *) &caller, &size);
            pthread_t th;
            pthread_create(&th, NULL, lobby, (void *) sock2);


        }

    }
    return 0;
}
    
