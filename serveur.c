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

//Variable global
uint8_t nbgame = 0;



//Verrou
pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;

void *jeu(void* sock){
    int sock2 = *(int*)sock;
    while(1){ 
         
	 pthread_mutex_lock(&verrou);
	 void * listGame = malloc(sizeof(char)*9+sizeof(uint8_t));
	 printf("%ld \n",sizeof(listGame));
	 char *str_game = "GAMES ";
	 char *str_etoile = "***";
	 
	 printf("%ld \n",sizeof(listGame));
	 
	 memmove(listGame,str_game,strlen(str_game));
	 memmove(listGame+strlen(str_game),&nbgame,sizeof(uint8_t));
	 memmove(listGame+strlen(str_game)+sizeof(uint8_t),str_etoile,strlen(str_etoile));
	 
	 int recu=send(sock2,listGame,sizeof(listGame),0);
     	 pthread_mutex_unlock(&verrou);
     	}
     }
     
int main(){
  int sock=socket(PF_INET,SOCK_STREAM,0);
  struct sockaddr_in address_sock;
  address_sock.sin_family=AF_INET;
  address_sock.sin_port=htons(4102);
  address_sock.sin_addr.s_addr=htonl(INADDR_ANY);
  int r=bind(sock,(struct sockaddr *)&address_sock,sizeof(struct sockaddr_in));
  if(r==0){
    r=listen(sock,0);
    printf("Listen \n");
    while(1){
      struct sockaddr_in caller;
      socklen_t size=sizeof(caller);
      int *sock2=(int *)malloc(sizeof(int));
      *sock2=accept(sock,(struct sockaddr *)&caller,&size);
      printf("accept \n");
      pthread_t th;
      pthread_create(&th,NULL,jeu,(void*)sock2);
      
      
    }
    
  }
  return 0;
}
    
