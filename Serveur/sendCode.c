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



int sendSize(int sock, uint8_t ngame){

	uint16_t v_lt = htons(20);
	printf("vlt %u \n", v_lt);
	
	
	char buffer[17];
	char *size = "SIZE! ";
	char *s = " ";
	char *c = "***";
	buffer[16] = '\0';
	memcpy(buffer, size, sizeof(char)*6);
	memcpy(buffer+sizeof(char)*6, &ngame, sizeof(uint8_t));
	memcpy(buffer+sizeof(char)*6 + sizeof(uint8_t), s, strlen(s));
	memcpy(buffer+sizeof(char)*7+sizeof(uint8_t), &v_lt, sizeof(uint16_t));
	memcpy(buffer+sizeof(char)*9 + sizeof(uint8_t), s, strlen(s));
	memcpy(buffer+sizeof(char)*11, &v_lt, sizeof(uint16_t));
	memcpy(buffer+sizeof(char)*13, c, strlen(c));
	uint16_t cor = 478;
	memcpy(&cor,buffer+8,sizeof(uint16_t));
	
	if(send(sock,buffer,16,0) == 0){
		perror("SENDSIZE: Cannot send");
		return 0;
	}
	
	return 1;

}

int sendList(int sock , uint8_t m, uint8_t s){
	char *c = "LIST! ";
	char buffer[12];
	buffer[11]= '*';
	buffer[10]= '*';
	buffer[9] = '*';
	buffer[7] =' ';
	memcpy(buffer,c,strlen(c));
	memcpy(buffer+strlen(c),&m,sizeof(uint8_t));
	memcpy(buffer+strlen(c) + sizeof(uint8_t)+ sizeof(char),&s,sizeof(uint8_t));
	if (send(sock,buffer,12,0) == -1){
		perror("Erreur LIST***\n");
		return 0;
	}
	printf("Ok LIST***\n");
	return 1;
}

int sendPlayr(int sock, char *id){
	char buffer[18];
	char *s = "***";
	char *c = "PLAYR ";
	memcpy(buffer,c,strlen(c));
	memcpy(buffer+strlen(c),id,strlen(id));
	memcpy(buffer+strlen(c)+sizeof(char)*8,s,sizeof(char)*3);
	
	if (send(sock,buffer,17,0) == -1){
		perror("Erreur PLAYR***\n");
		return 0;
	}
	printf("Ok PLAYR***\n");
	return 1;
}

int sendDunno(int sock){
	char *buffer = "DUNNO***";
	if (send(sock,buffer,strlen(buffer),0) == -1){
		perror("Erreur DUNNO***\n");
		return 0;
	}
	printf("Ok DUNNO***\n");
	return 1;
}

int sendNos(int sock){
	char *buffer = "NSEND***";
	if (send(sock,buffer,strlen(buffer),0) == -1){
		perror("Erreur NSEND***\n");
		return 0;
	}
	printf("Ok NSEND***\n");
	return 1;
}


int sendRegno(int sock){
	char *buffer = "REGNO***";
	if (send(sock,buffer,strlen(buffer),0) == -1){
		perror("Erreur REGNO***\n");
		return 0;
	}
	printf("Ok REGNO***\n");
	return 1;
}

int sendRegok(int sock, uint8_t id_game){
	char *buffer1 = "REGOK ";
	char *buffer2 = "***";
	uint8_t be_id_game = id_game;
	void * buffer = malloc(sizeof(char)*9 + sizeof(uint8_t));
	memcpy(buffer,buffer1,strlen(buffer1));
	memcpy(buffer + strlen(buffer1),&be_id_game, sizeof(uint8_t));
	memcpy(buffer + strlen(buffer1)+sizeof(uint8_t),buffer2, strlen(buffer2));
	if (send(sock,buffer,sizeof(char)*9+sizeof(uint8_t),0) == 0){
		perror("Erreur REGOK_m***\n");
		return 0;
	}
	printf("Ok REGOK_m***\n");
	return 1;
	
}

int sendUnrok(int sock, uint8_t id_game){
	char *buffer1 = "UNROK ";
	char *buffer2 = "***";
	uint8_t be_id_game = id_game;
	char  buffer [10];
	memcpy(buffer,buffer1,strlen(buffer1));
	memcpy(buffer + strlen(buffer1),&be_id_game, sizeof(uint8_t));
	memcpy(buffer + strlen(buffer1)+sizeof(uint8_t),buffer2, strlen(buffer2));
	if (send(sock,buffer,sizeof(char)*9+sizeof(uint8_t),0) == -1){
		perror("Erreur UNROK_m***\n");
		return 0;
	}
	printf("Ok UNROK_m***\n");
	return 1;
}

int sendGobye(int sock){
	char *buffer = "GOBYE***";
		if (send(sock,buffer,strlen(buffer),0) == -1){
			perror("Erreur GOBYE***\n");
			return 0;
		}
		printf("Ok GOBYE***\n");
		return 1;
}

int sendSend(int sock){
	char *buffer = "SEND!***";
		if (send(sock,buffer,strlen(buffer),0) == -1){
			perror("Erreur SEND!***\n");
			return 0;
		}
		printf("Ok SEND!***\n");
		return 1;
}
int sendGames(int sock, uint8_t num_game){
	char *buffer1 = "GAMES ";
	char *buffer2 = "***";
	
	
	char buffer [10];
	memcpy(buffer,buffer1,strlen(buffer1));
	memcpy(buffer + strlen(buffer1),&num_game, sizeof(uint8_t));
	memcpy(buffer + strlen(buffer1)+sizeof(uint8_t),buffer2, strlen(buffer2));
	
	
	if (send(sock,buffer,sizeof(char)*9+sizeof(uint8_t),0) == -1){
		perror("Erreur GAMES_n***\n");
		return 0;
	}
	printf("Ok GAMES_n***\n");
	return 1;

}

int sendOgame(int sock, uint8_t id_game, uint8_t nb_player){
	char *buffer1 = "OGAME ";
	char *buffer2 = "***";
	char space = ' ';
	char buffer [12];
	memcpy(buffer,buffer1,strlen(buffer1));
	memcpy(buffer + strlen(buffer1),&id_game, sizeof(uint8_t));
	memcpy(buffer + strlen(buffer1)+sizeof(uint8_t),&space,sizeof(char));
	memcpy(buffer + strlen(buffer1)+sizeof(uint8_t)+sizeof(char),&nb_player, sizeof(uint8_t));
	memcpy(buffer + strlen(buffer1)+sizeof(uint8_t)*2+sizeof(char),buffer2,strlen(buffer2));
	
	if (send(sock,buffer,12,0) == -1){
		perror("Erreur OGAME_***\n");
		return 0;
	}
	printf("Ok OGAME_***\n");
	return 1;

}
