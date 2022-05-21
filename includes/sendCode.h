#ifndef SENDCODE_H
#define SENDCODE_H

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
#include <stdint.h>
#include "gameList.h"

int sendSize(int sock, uint8_t ngame);
int sendList(int sock, uint8_t m, uint8_t s);
int sendPlayr(int sock, char *id);
int sendDunno(int sock);
int sendNos(int sock);
int sendRegno(int sock);
int sendRegok(int sock, uint8_t id_game);
int sendUnrok(int sock, uint8_t id_game);
int sendGobye(int sock);
int sendSend(int sock);
int sendGames(int sock, uint8_t num_game);
int sendOgame(int sock, uint8_t id_game, uint8_t nb_player);
int sendMove(Lab *lab, int socket, char *mess, joueur p, char* port);
int sendGlis(int sock, Gamelist g);

#endif //SENDCODE_H
