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

//Variable global
uint8_t nbgame = 0;
Gamelist *list = NULL;


//Verrou
pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;

void *lobby(void* sock){
    int sock2 = *(int*)sock;
         
	 pthread_mutex_lock(&verrou);
	 void * listGame = malloc(sizeof(char)*9+sizeof(uint8_t));
	 printf("%ld \n",sizeof(listGame));
	 char *str_game = "GAMES ";
	 char *str_star = "***";
	 
	 printf("%ld \n",strlen(str_game));
	 
	 memmove(listGame,str_game,strlen(str_game));
	 memmove(listGame+strlen(str_game),&nbgame,sizeof(uint8_t));
	 memmove(listGame+strlen(str_game)+sizeof(uint8_t),str_star,strlen(str_star));
	 
	 if(send(sock2,listGame,sizeof(char)*9+sizeof(uint8_t),0) == -1){
	 	pthread_mutex_unlock(&verrou);
	 	perror("Cannot send GAMES_nbgame***");
	 	
	}
	
	 char *str_space = " ";
	 char *str_ogame = "OGAME ";
	 Gamelist *threadList = list;
	 while(threadList != NULL){
	 	void * gameInf = malloc(sizeof(char)*10 + sizeof(uint8_t)*2);
	 	memmove(gameInf,str_ogame,strlen(str_ogame));
	 	memmove(gameInf + strlen(str_ogame),&(list->num),sizeof(uint8_t));
	 	memmove(gameInf + strlen(str_ogame)+sizeof(uint8_t),str_space,strlen(str_space));
	 	memmove(gameInf + strlen(str_ogame)+sizeof(uint8_t)+strlen(str_space),&(list->nb_player),sizeof(uint8_t));
	 	memmove(gameInf + strlen(str_ogame)+sizeof(uint8_t)+strlen(str_space)+sizeof(uint8_t),str_star,strlen(str_star));
	 	 if(send(sock2,gameInf,sizeof(char)*10+sizeof(uint8_t)*2,0) == -1){
	 	pthread_mutex_unlock(&verrou);
	 	perror("Cannot send OGAME_num_plr***");
	 	
	 	
	}
	free(gameInf);
	 threadList = threadList -> next;
	 	
	 }
     	 pthread_mutex_unlock(&verrou);
     	 while(1){
     	 void *receiver = malloc(24);
     	 if(recv(sock2,receiver,sizeof(char)*20 + sizeof(uint8_t),0) == 0){
     	 	perror("Cannot receive registration");
     	 	
     	 }
     	 char request[6];
     	 request[5] = '\0';
     	 memmove(&request,receiver,sizeof(char)*5);
     	
     	 if(strcmp(request,"NEWPL") == 0){
     	 	char id [9];
     	 	char p [5];
     	 	memmove(&id,receiver+sizeof(char)*6,sizeof(char)*8);
     	 	id[8] = '\0';
     	 	memmove(&p,receiver+sizeof(char)*6,sizeof(char)*8);
     	 	p[4] = '\0';
     	 	
     	 	
     	 	printf("Creation of new game...");
     	 	pthread_mutex_lock(&verrou);
     	 	uint8_t nwgame = add(&list);
     	 	threadList = list;
     	 	addPlayerTo(threadList,nwgame,id,p);
     	 	
     	 	pthread_mutex_unlock(&verrou);
     	 	
     	 	
     	 	
     	 	break;
     	 }
     	 else if(strcmp(request,"REGIS")){
     	 	printf("TO DO");
     	 }
     	 
     	 }
     	while(1){
     		printf("DONE");
     	}
     }
     
int main(){
  int sock=socket(PF_INET,SOCK_STREAM,0);
  struct sockaddr_in address_sock;
  address_sock.sin_family=AF_INET;
  address_sock.sin_port=htons(5551);
  address_sock.sin_addr.s_addr=htonl(INADDR_ANY);
  int r=bind(sock,(struct sockaddr *)&address_sock,sizeof(struct sockaddr_in));
  if(r==0){
    r=listen(sock,0);
    while(1){
      struct sockaddr_in caller;
      socklen_t size=sizeof(caller);
      int *sock2=(int *)malloc(sizeof(int));
      *sock2=accept(sock,(struct sockaddr *)&caller,&size);
      pthread_t th;
      pthread_create(&th,NULL,lobby,(void*)sock2);
      
      
    }
    
  }
  return 0;
}
    
