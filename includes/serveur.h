#ifndef SERVEUR_H
#define SERVEUR_H

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
#include "gameList.h"
#include "../Serveur/sendCode.c"

int listGame(int sock);
uint8_t prepareGame(int sock, char *ur_id, uint8_t ur_game_id, char *ready);
int chooseGame(int sock, char *ur_id);
void *lobby(void *sock);

#endif //SERVEUR_H
