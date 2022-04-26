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



//Verrou
pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;
void * listGame = malloc(sizeof(char)*9+sizeof(uint8_t));

void *lobby(void* sock){
    int sock2 = *(int*)sock;
         
	 printf("%ld \n",sizeof(listGame));
	 char *str_game = "GAMES ";
	 char *str_etoile = "***";
	 
	 printf("%ld \n",strlen(str_game));
	 
	 pthread_mutex_lock(&verrou);
	 memmove(listGame,str_game,strlen(str_game));
	 memmove(listGame+strlen(str_game),&nbgame,sizeof(uint8_t));
	 memmove(listGame+strlen(str_game)+sizeof(uint8_t),str_etoile,strlen(str_etoile));
	 
	 if(send(sock2,listGame,sizeof(char)*9+sizeof(uint8_t),0) == -1){
	 	pthread_mutex_unlock(&verrou);
	 	perror("Cannot send GAMES_nbgame***");
	 	
	}
     	 pthread_mutex_unlock(&verrou);
     	 
     	 while(1){
     	 	//printf("SWITCH");
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
    
