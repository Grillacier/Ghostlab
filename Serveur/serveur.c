#include "../includes/serveur.h"

//Variable globale
Gamelist list[100];

//Verrou
pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;

int listGame(int sock) {
    pthread_mutex_lock(&verrou);
    if (sendGames(sock, length(list)) == 0) {
        perror("LISTGAME: cannot sendGames");
        return 0;
    }

    for (int i = 0; i < 100; i++) {
        if (list[i].create == 1 && list[i].started < 6) {
            uint8_t u_int = i;
            printf("%d  ", i);
            if (sendOgame(sock, u_int, getNbPlayer(list[i])) == 0) {
                perror("LISTGAME: cannot sendOGame");
                return 0;
            }
        }
    }
    pthread_mutex_unlock(&verrou);
    return 1;
}
uint8_t inGame(int sock, char *ur_id, uint8_t ur_game_id) {
    sendWelco(sock, ur_game_id, list[ur_game_id].lab, list[ur_game_id].port_cast);
    int v = searchById(list[ur_game_id].player_list, ur_id);
    initPos(list[ur_game_id].lab, &list[ur_game_id].player_list[v]);
    player(list[ur_game_id].lab, list[ur_game_id].player_list[v]);
    sendPosit(sock, ur_id, list[ur_game_id].player_list[v].x, list[ur_game_id].player_list[v].y);
    while (1) {
        char receiver [250];
	int r = recv(sock, receiver, 249, 0);
        if (r < 0) {
            perror("INGAME: End of connexion \n");
            return -2;
        }
        if (r == 0) {
            perror("INGAME: No sent data\n");
            return -2;
        }


        char request[6];
        memmove(&request, receiver, sizeof(char) * 5);
        request[5] = '\0';
         if (strncmp(receiver, "IQUIT",5) == 0) {
         	sendGobye(sock);
         	return -2;
         }
          if (strncmp(receiver, "MALL?",5) == 0) {
          	char umess [200];
          	memcpy(umess,receiver + sizeof(char)*5,sizeof(char)*r-3);
         	sendAllMessage(ur_id,list[ur_game_id].port_cast,umess);
             sendMall(sock);
         	return ur_game_id;
         }
          if (strncmp(receiver, "UPMOV?", 5) == 0 || strncmp(receiver, "DOMOV?", 5) == 0 ||
                  strncmp(receiver, "LEMOV?", 5) == 0 || strncmp(receiver, "RIMOV?", 5) == 0) {
              sendMove(list[ur_game_id].lab, sock, receiver, list[ur_game_id].player_list[searchById(list[ur_game_id].player_list, ur_id)], list[ur_game_id].port_cast);
              printLab(list[ur_game_id].lab);
          }

          if (strncmp(receiver, "SEND?",5) == 0) {
          	char umess [200];
          	memcpy(umess,receiver + sizeof(char)*14,sizeof(char)*r-3);
          	char t_id [8];
          	memcpy(t_id,receiver + sizeof(char)*6,sizeof(char)*8);
          	int index = searchById(list[ur_game_id].player_list,t_id);
          	if(index == -1){
          		sendNos(sock);
          	}
         	if(sendMessage(ur_id,list[ur_game_id].player_list[index].ip,list[ur_game_id].player_list[index].port,umess)==1){
                 sendSend(sock);
         	}
         	
         	return ur_game_id;
         }
          if (strncmp(receiver, "LIBRE",5) == 0) {
         	
         	return ur_game_id;
         }
          if (strncmp(receiver, "LIBRE",5)== 0) {
         	sendGobye(sock);
         	return ur_game_id;
         }
         
 }
}

uint8_t prepareGame(int sock, char *ur_id, uint8_t ur_game_id, char *ready) {
    while (1) {
        char receiver[100];
        int r = recv(sock, receiver, sizeof(char) * 20 + sizeof(uint8_t), 0);
        if (r < 0) {
            perror("PREPARE:End of connexion \n");
            return ur_game_id;
        }
        if (r == 0) {
            perror("PREPARE: No sent data \n");
            return ur_game_id;
        }

        char request[6];
        memmove(&request, receiver, sizeof(char) * 5);
        request[5] = '\0';
        if (strncmp(receiver, "SIZE?", 5) == 0) {
            uint8_t num_game = -1;
            memcpy(&num_game, receiver + sizeof(char) * 6, sizeof(uint8_t));
            if (num_game > 99) {
                sendDunno(sock);
                return ur_game_id;
            }
            pthread_mutex_lock(&verrou);
            if (isCreate(list[num_game]) == 0) {
                pthread_mutex_unlock(&verrou);
                sendDunno(sock);
                return ur_game_id;
            }
            if (sendSize(sock, num_game) == 0) {
                pthread_mutex_unlock(&verrou);
                perror("PREPARE: Cannot send size \n");
                return ur_game_id;
            }
            pthread_mutex_unlock(&verrou);
            return ur_game_id;
        }

        if (strncmp(receiver, "START", 5) == 0) {
            char str[2];
            str[0] = 'Y';
            str[1] = '\0';
            pthread_mutex_lock(&verrou);
            list[ur_game_id] = upStart(list[ur_game_id]);
            memcpy(ready, str, sizeof(char) * 1);
            printf("PREPAREGAME: Start, waiting for other \n");
            printf("PREPAREGAME: Start set up to %d \n", list[ur_game_id].started);
            pthread_mutex_unlock(&verrou);
            return ur_game_id;
        }
        if (strncmp(receiver, "UNREG", 5) == 0) {
            pthread_mutex_lock(&verrou);
            int ur_place = searchById(list[ur_game_id].player_list, ur_id);
            if (ur_place == -1) {

                pthread_mutex_unlock(&verrou);
                if (sendRegno(sock) == 0) {
                    perror("Cannot send REGNO \n");
                }
                return ur_game_id;
            }
            printf("UR PLACE: %d \n", ur_place);
            list[ur_game_id].player_list[ur_place] = rmvPlayer(list[ur_game_id].player_list[ur_place]);
            pthread_mutex_unlock(&verrou);
            if (sendUnrok(sock, ur_game_id) == 0) {
                perror("Cannot send UNROK \n");
            }
            return -1;
        }
        if (strncmp(receiver, "LIST?", 5) == 0) {
            uint8_t num_game = -1;
            memmove(&num_game, receiver + sizeof(char) * 6, sizeof(uint8_t));
            if (num_game < 0 || num_game > 99) {
                sendDunno(sock);
                return ur_game_id;
            }
            pthread_mutex_lock(&verrou);
            if (isCreate(list[num_game]) == 0) {
                pthread_mutex_unlock(&verrou);
                sendDunno(sock);

                return ur_game_id;
            }

            uint8_t nb_player = getNbPlayer(list[num_game]);
            if (sendList(sock, num_game, nb_player) == 0) {
                perror("CHOOSEGAME: Cannot send pList \n");
                pthread_mutex_unlock(&verrou);
                return ur_game_id;
            }
            for (int i = 0; i < 5; i++) {
                if (list[num_game].player_list[i].place == 1) {
                    if (sendPlayr(sock, list[num_game].player_list[i].id) == 0) {
                        perror("CHOOSEGAME: Cannot send Playr \n");
                        pthread_mutex_unlock(&verrou);
                        return ur_game_id;
                    }
                }
            }
            pthread_mutex_unlock(&verrou);
            return ur_game_id;

        }
        if (strncmp(receiver, "GAME?", 5) == 0) {
            printf("CHOOSEGAME: GAMES? request \n");
            if (listGame(sock) == 0) {
                perror("CHOOSEGAME:Cannot send list \n");
                return ur_game_id;
            }
            return ur_game_id;
        }
        if (strncmp(receiver, "NEWPL", 5) == 0) {
            if (sendRegno(sock) == 0) {
                perror("Cannot send REGNO \n");
            }
            return ur_game_id;
        } else if (strncmp(request, "REGIS", 5) == 0) {

            if (sendRegno(sock) == 0) {
                perror("Cannot send REGNO \n");
            }
            return ur_game_id;
        }

    }

}

int chooseGame(int sock, char *ur_id) {
    while (1) {
        char receiver[100];
        int r = recv(sock, receiver, sizeof(char) * 20 + sizeof(uint8_t), 0);
        if (r < 0) {
            perror("CHOOSEGAME:End of connexion \n");
            return -2;
        }
        if (r == 0) {
            perror("CHOOSEGAME: No sended data \n");
            return -2;
        }

        char request[6];
        memmove(&request, receiver, sizeof(char) * 5);
        request[5] = '\0';
        if (strncmp(receiver, "SIZE?", 5) == 0) {
            uint8_t num_game = -1;
            memcpy(&num_game, receiver + sizeof(char) * 6, sizeof(uint8_t));
            if (num_game > 99) {
                sendDunno(sock);
                return -1;
            }
            pthread_mutex_lock(&verrou);
            if (isCreate(list[num_game]) == 0) {
                pthread_mutex_unlock(&verrou);
                sendDunno(sock);
                return -1;
            }
            if (sendSize(sock, num_game) == 0) {
                pthread_mutex_unlock(&verrou);
                perror("CHOOSEGAME: Cannot send size \n");
                return -1;
            }
            pthread_mutex_unlock(&verrou);
            return -1;
        }

        if (strncmp(receiver, "START", 5) == 0) {
            sendDunno(sock);
            return -1;
        }
        if (strncmp(receiver, "UNREG", 5) == 0) {
            sendDunno(sock);
            return -1;
        }
        if (strncmp(receiver, "LIST?", 5) == 0) {
            uint8_t num_game = -1;
            memmove(&num_game, receiver + sizeof(char) * 6, sizeof(uint8_t));
            if (num_game < 0 || num_game > 99) {
                sendDunno(sock);
                return -1;
            }
            pthread_mutex_lock(&verrou);
            if (isCreate(list[num_game]) == 0) {
                pthread_mutex_unlock(&verrou);
                sendDunno(sock);

                return -1;
            }

            uint8_t nb_player = getNbPlayer(list[num_game]);
            if (sendList(sock, num_game, nb_player) == 0) {
                perror("CHOOSEGAME: Cannot send pList \n");
                pthread_mutex_unlock(&verrou);
                return -1;
            }
            for (int i = 0; i < 5; i++) {
                if (list[num_game].player_list[i].place == 1) {
                    if (sendPlayr(sock, list[num_game].player_list[i].id) == 0) {
                        perror("CHOOSEGAME: Cannot send Playr \n");
                        pthread_mutex_unlock(&verrou);
                        return -1;
                    }
                }
            }
            pthread_mutex_unlock(&verrou);
            return -1;

        }
        if (strncmp(receiver, "GAME?", 5) == 0) {
            printf("CHOOSEGAME: GAMES? request \n");
            if (listGame(sock) == 0) {
                perror("CHOOSEGAME:Cannot send list \n");
                return -1;
            }
            return -1;
        }
        if (strncmp(receiver, "NEWPL", 5) == 0) {
            printf("CHOOSEGAME: NEWPL request");
            char id[9];
            memmove(&id, receiver + sizeof(char) * 6, sizeof(char) * 8);
            id[8] = '\0';
            char p[5];
            memmove(&p, receiver + sizeof(char) * 15, sizeof(char) * 4);
            p[4] = '\0';

            pthread_mutex_lock(&verrou);


            uint8_t nwgame = findRoom(list);

            printf("CHOOSEGAME: Nouvelle partie, ID: %u \n", nwgame);
            list[nwgame] = create(list[nwgame]);
            int isplace = findPlace(list[nwgame].player_list);
            if (isplace == -1) {
                sendRegno(sock);
                pthread_mutex_unlock(&verrou);
                return -1;
            }
            list[nwgame].player_list[isplace] = addPlayer(list[nwgame].player_list[isplace], id, p);


            pthread_mutex_unlock(&verrou);
            if (nwgame > -1) {
                memcpy(ur_id, &id, sizeof(char) * 8);
                sendRegok(sock, nwgame);
                return nwgame;
            }
            sendRegno(sock);
            return -1;


        } else if (strncmp(request, "REGIS", 5) == 0) {
            char id[9];
            memmove(&id, receiver + sizeof(char) * 6, sizeof(char) * 8);
            id[8] = '\0';
            char p[5];
            memmove(&p, receiver + sizeof(char) * 15, sizeof(char) * 4);
            p[4] = '\0';
            uint8_t id_game = 0;
            memmove(&id_game, receiver + sizeof(char) * 20, sizeof(uint8_t));
            pthread_mutex_lock(&verrou);
            int check = isCreate(list[id_game]);
            if (check == 0 || list[id_game].started > 5) {
                perror("CHOOSEGAME: Partie non créée");
                sendRegno(sock);
                pthread_mutex_unlock(&verrou);
                return -1;
            }
            int isplace = findPlace(list[id_game].player_list);
            if (isplace == -1) {
                sendRegno(sock);
                pthread_mutex_unlock(&verrou);
                return -1;
            }
            list[id_game].player_list[isplace] = addPlayer(list[id_game].player_list[isplace], id, p);

            pthread_mutex_unlock(&verrou);
            memcpy(ur_id, &id, sizeof(char) * 8);
            sendRegok(sock, id_game);
            return id_game;
        }
    }
}


void *lobby(void *sock) {
    // Variable de thread
    int sock2 = *(int *) sock;
    uint8_t ur_game_id = -1;
    char ready[2];
    ready[1] = '\0';
    ready[0] = 'N';
    char ur_id[9];
    ur_id[8] = '\0';
    // ------

    if (listGame(sock2) == 0) {
        perror(" SERVEUR: Cannot send the list of game \n");
    }


    while (1) {
        printf("LOBBY: Return to main menu \n");
        printf("idGame:  %u \n", ur_game_id);
        ur_game_id = chooseGame(sock2, ur_id);
        if (ur_game_id == 254) {
            printf("LOBBY: Close sock\n");
            close(sock2);
        }
        while (ur_game_id < 100) {
            printf(" LOBBY: waiting for start \n");
            ur_game_id = prepareGame(sock2, ur_id, ur_game_id, ready);
            while (strcmp(ready, "Y") == 0) {
                while (list[ur_game_id].started == 6) {
                    printf("LOBBY: inGame \n");
                    ur_game_id = inGame(sock2,ur_id,ur_game_id);
                    if(ur_game_id == -2){
                    	printf("FIN DE PARTIE \n");
                    	close(sock2);
                    }
                }
            }
        }

        // printf("Vous n'etes pas/ plus inscrit");
    }

}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage : ./serveur <portTCP>\n");
        return -1;
    }

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address_sock;
    address_sock.sin_family = AF_INET;
    address_sock.sin_port = htons(atoi(argv[1]));
    address_sock.sin_addr.s_addr = htonl(INADDR_ANY);
    int r = bind(sock, (struct sockaddr *) &address_sock, sizeof(struct sockaddr_in));

    //Initialisation de la liste de partie
    for (int i = 0; i < 100; i++) {
        list[i] = setUpList(list[i], i);

    }
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
    
