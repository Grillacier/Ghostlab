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


int sendDunno(int sock){
	char *buffer = "DUNNO***";
	if (send(sock,buffer,strlen(buffer),0) == -1){
		perror("Erreur DUNNO***");
		return 0;
	}
	printf("Ok DUNNO***");
	return 1;
}

int sendRegno(int sock){
	char *buffer = "REGNO***";
	if (send(sock,buffer,strlen(buffer),0) == -1){
		perror("Erreur REGNO***");
		return 0;
	}
	printf("Ok REGNO***");
	return 1;
}

int sendRegok(int sock, uint8_t id_game){
	char *buffer1 = "REGOK ";
	char *buffer2 = "***";
	uint8_t be_id_game = htons(id_game);
	void * buffer = malloc(sizeof(char)*9 + sizeof(uint8_t));
	memcpy(buffer,buffer1,strlen(buffer1));
	memcpy(buffer + strlen(buffer1),&be_id_game, sizeof(uint8_t));
	memcpy(buffer + strlen(buffer1)+sizeof(uint8_t),buffer2, strlen(buffer2));
	if (send(sock,buffer,sizeof(char)*9+sizeof(uint8_t),0) == -1){
		perror("Erreur REGOK_m***");
		return 0;
	}
	printf("Ok REGOK_m***");
	return 1;
	
}

int sendUnreg(int sock, uint8_t id_game){
	char *buffer1 = "UNREG ";
	char *buffer2 = "***";
	uint8_t be_id_game = htons(id_game);
	void * buffer = malloc(sizeof(char)*9 + sizeof(uint8_t));
	memcpy(buffer,buffer1,strlen(buffer1));
	memcpy(buffer + strlen(buffer1),&be_id_game, sizeof(uint8_t));
	memcpy(buffer + strlen(buffer1)+sizeof(uint8_t),buffer2, strlen(buffer2));
	if (send(sock,buffer,sizeof(char)*9+sizeof(uint8_t),0) == -1){
		perror("Erreur UNREG_m***");
		return 0;
	}
	printf("Ok UNREG_m***");
	return 1;
}

int sendGames(int sock, uint8_t num_game){
	char *buffer1 = "GAMES ";
	char *buffer2 = "***";
	uint8_t be_num_game = htons(num_game);
	void * buffer = malloc(sizeof(char)*9 + sizeof(uint8_t));
	memcpy(buffer,buffer1,strlen(buffer1));
	memcpy(buffer + strlen(buffer1),&be_num_game, sizeof(uint8_t));
	memcpy(buffer + strlen(buffer1)+sizeof(uint8_t),buffer2, strlen(buffer2));
	if (send(sock,buffer,sizeof(char)*9+sizeof(uint8_t),0) == -1){
		perror("Erreur GAMES_n***");
		return 0;
	}
	printf("Ok GAMES_n***");
	return 1;

}

int sendOgame(int sock, uint8_t id_game, uint8_t nb_player){
	char *buffer1 = "OGAME ";
	char *buffer2 = "***";
	uint8_t be_id_game = htons(id_game);
	char space = ' ';
	uint8_t be_nb_player = htons(nb_player) ; 
	void * buffer = malloc(sizeof(char)*10 + sizeof(uint8_t)*2);
	memcpy(buffer,buffer1,strlen(buffer1));
	memcpy(buffer + strlen(buffer1),&be_id_game, sizeof(uint8_t));
	memcpy(buffer + strlen(buffer1)+sizeof(uint8_t),&space,sizeof(char));
	memcpy(buffer + strlen(buffer1)+sizeof(uint8_t)+sizeof(char),&be_nb_player, sizeof(uint8_t));
	memcpy(buffer + strlen(buffer1)+sizeof(uint8_t)*2+sizeof(char),buffer2,strlen(buffer2));
	
	if (send(sock,buffer,sizeof(char)*9+sizeof(uint8_t),0) == -1){
		perror("Erreur OGAME_***");
		return 0;
	}
	printf("Ok OGAME_***");
	return 1;

}
