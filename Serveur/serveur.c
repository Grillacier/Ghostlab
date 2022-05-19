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

Gamelist *list = NULL;


//Verrou
pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;

int prepareGame(int sock, char *ur_id, uint8_t ur_game_id){
	while(1){
		char receiver [100];
		 Gamelist *threadList = list;
		 int r = recv(sock, receiver, sizeof(char) * 20 + sizeof(uint8_t), 0);
		 if (r > 0) {
            		perror("CHOOSEGAME:End of connexion \n");
            		return -1;
        }
        	if (r == 0) {
            		perror("CHOOSEGAME: No sended data \n");
            		return 0;
        }
        	char request[6];
        	memmove(&request, receiver, sizeof(char) * 5);
        	request[5] = '\0';
        
		if (strncmp(receiver, "START",5) == 0) {
			if(imReady(threadList , ur_game_id) != 0){
				return 2;
			}
		}
		if (strncmp(receiver, "UNREG",5) == 0) {
			rmvPlayer(threadList, ur_game_id, ur_id);
			return 1;
		}
		if (strncmp(receiver, "NEWPL",5) == 0) {
		
		}
		if (strncmp(receiver, "NEWPL",5) == 0) {
		
		}
		if (strncmp(receiver, "NEWPL",5) == 0) {
		
		}
		if (strncmp(receiver, "NEWPL",5) == 0) {
		
		}
	
	}
}

int chooseGame(int sock,char *ur_id) { // TODO: Ajoutez les options supplémentaires
    while (1) {
        char receiver [100];
        Gamelist *threadList = list;
	int r = recv(sock, receiver, sizeof(char) * 20 + sizeof(uint8_t), 0);
        if (r > 0) {
            perror("CHOOSEGAME:End of connexion \n");
            return -1;
        }
        if (r == 0) {
            perror("CHOOSEGAME: No sended data \n");
            return 0;
        }


        char request[6];
        memmove(&request, receiver, sizeof(char) * 5);
        request[5] = '\0';
        if (strncmp(receiver, "NEWPL",5) == 0) {
            printf("CHOOSEGAME: NEWPL request");
            char id[9];
            memmove(&id, receiver + sizeof(char) * 6, sizeof(char) * 8);
            id[8] = '\0';
            char p[5];
            memmove(&p, receiver + sizeof(char) * 15, sizeof(char) * 4);
            p[4] = '\0';

            Gamelist *threadList = list;
            printf(" Creation of new game... \n");
            pthread_mutex_lock(&verrou);
            uint8_t nwgame = add(&list);
            addPlayerTo(threadList, nwgame, id, p);

            pthread_mutex_unlock(&verrou);
            if (nwgame > 0) {
            	memcpy(ur_id,&id,sizeof(char)*8);
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
            memmove(&p, receiver + sizeof(char) * 15, sizeof(char) * 4);
            p[4] = '\0';
            uint8_t id_game = 0;
            memmove(&id_game, receiver + sizeof(char) * 20, sizeof(uint8_t));
            pthread_mutex_lock(&verrou);
            if (addPlayerTo(threadList, id_game, id, p) == 0) {
                sendRegno(sock);
                return 0;
            }
            pthread_mutex_unlock(&verrou);
            sendRegok(sock, id_game);
            return id_game;
        }

    }

}

int listGame (int sock){
	pthread_mutex_lock(&verrou);
	Gamelist *threadList = list;
	
    	if (sendGames(sock,length(threadList)) == 0) {
        perror("LISTGAME: cannot sendGames");
        return 0;
    	}
    	

    while (threadList != NULL) {
    	if(threadList -> started != -1){
        	if(sendOgame(sock, threadList->num, threadList->nb_player) == 0){
        		 perror("LISTGAME: cannot sendOGame");
        		return 0;
        	}
        }
        threadList = threadList->next;
    }
    pthread_mutex_unlock(&verrou);
    return 1;

}

void *lobby(void *sock) {
    // Variable de thread
    int sock2 = *(int *) sock;
    uint8_t ur_game_id = 0;
    char ur_id[9];
    ur_id[8] = '\n';
    // ------
    
    if(listGame(sock2) == 0){
    	perror(" SERVEUR: Cannot send the list of game \n");
    }
    
    
    while(1){

            ur_game_id = chooseGame(sock2,ur_id); // ur_game_id == 0 : pas de partie, <0 : fin de transmission ,>0 :inscrit
            if(ur_game_id == -1){
            	close(sock2);
            }
            while (ur_game_id > 0) {
            	
                printf(" Vous etes inscrit, preparez vous! \n");
                int status = prepareGame(sock2,ur_id, ur_game_id);
                if(status == 1){
                	ur_game_id = 0;
                	printf("Vous allez retourner au lobby \n");
                }
                while(status ==2){
                	printf("Vous etes pret! \n");
                }
            }

            printf("Vous n'etes pas/ plus inscrit");
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
    
