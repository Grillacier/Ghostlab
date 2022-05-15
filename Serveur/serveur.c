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

void *lobby(void* sock){
         int sock2 = *(int*)sock;
	 pthread_mutex_lock(&verrou);
	 if(sendGames(sock2,nbgame) == 0){
	 	printf("ERREUR");
	 }
	 Gamelist *threadList = list;
	 
	 while(threadList != NULL){
	 	sendOgame(sock2, threadList ->num , threadList ->nb_player);
	 	threadList = threadList -> next;
	}

     	 pthread_mutex_unlock(&verrou);
     	 
     	 while(1){
     	 void *receiver = malloc(24);
     	 if(recv(sock2,receiver,sizeof(char)*20 + sizeof(uint8_t),0) == 0){
     	 	perror("Cannot receive registration");
     	 	
     	 	} 
     	 
     	 
     	 char request [6];
     	 memmove(&request,receiver,sizeof(char)*5);
     	 request[5] = '\0';
     	 if(strcmp(request,"NEWPL") == 0){
     	 	char id[9];
     	 	memmove(&id,receiver+sizeof(char)*6,sizeof(char)*8);
     	 	id[8] = '\0';
     	 	char p[5];
     	 	memmove(&p,receiver+sizeof(char)*6,sizeof(char)*8);
     	 	p[4] = '\0';
     	 	
     	 	threadList = list;
     	 	printf("Creation of new game...");
     	 	pthread_mutex_lock(&verrou);
     	 	uint8_t nwgame = add(&list);
     	 	threadList = list;
     	 	addPlayerTo(threadList,nwgame,id,p);
     	 	
     	 	pthread_mutex_unlock(&verrou);
     	 	if(nwgame != 0){
     	 		sendRegok(sock2,nwgame);
     	 	}
     	 	
     	 	
     	 	
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
    
