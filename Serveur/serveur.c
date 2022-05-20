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

Gamelist list [100];


//Verrou
pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;


/*int prepareGame(int sock, char *ur_id, uint8_t ur_game_id){
	while(1){
		char receiver [100];
		 int r = recv(sock, receiver, sizeof(char) * 20 + sizeof(uint8_t), 0);
		 if (r < 0) {
            		perror("PREPARE:End of connexion \n");
            		return -1;
        }
        	if (r == 0) {
            		perror("PREPARE: No sended data \n");
            		return 0;
        }
        	char request[6];
        	memmove(request, receiver, sizeof(char) * 5);
        	request[5] = '\0';
        
		if (strncmp(receiver, "START",5) == 0) {
			if(imReady(list , ur_game_id) != 0){
				return 2;
			}
		}
		if (strncmp(receiver, "UNREG",5) == 0) {
			rmvPlayer(list, ur_game_id, ur_id);
			return 1;
		}
		if (strncmp(receiver, "SIZE?",5) == 0) {
			uint8_t n_p = 0;
			memcpy(&n_p,receiver + sizeof(char)*6,sizeof(uint8_t));
			if(sendSize(sock,n_p) == 0){
				printf("PREPARE: Error size \n");
				return 0;
			}
			
		}
		if (strncmp(receiver, "NEWPL",5) == 0) {
		
		}
		if (strncmp(receiver, "NEWPL",5) == 0) {
		
		}
		if (strncmp(receiver, "NEWPL",5) == 0) {
		
		}
	
	}
}
 */
uint8_t chooseGame(int sock,char *ur_id) { // TODO: Ajoutez les options supplémentaires
    while (1) {
        char receiver [100];
	int r = recv(sock, receiver, sizeof(char) * 20 + sizeof(uint8_t), 0);
        if (r < 0) {
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

           
            printf(" Creation of new game... \n");
            pthread_mutex_lock(&verrou);
            
            
            uint8_t nwgame = findRoom(list);
            printf("%u \n",nwgame);
            list[nwgame] = create(list[nwgame]);
            int isplace = findPlace(list[nwgame].player_list);
            printf("place: %d \n",isplace);
            if(isplace ==-1){
            	sendRegno(sock);
            	return 0;
            }
            list[nwgame].player_list[isplace] = addPlayer(list[nwgame].player_list[isplace],id,p);
            

            pthread_mutex_unlock(&verrou);
            if (nwgame > -1) {
            	strcpy(ur_id, id);
                sendRegok(sock, nwgame);
                return nwgame;
            }
            sendRegno(sock);
            return 0;


        }   else if (strncmp(request, "REGIS",5)==0) {
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
            if(check == 0){
            	perror("CHOOSEGAME: Partie non créer");
            	sendRegno(sock);
            	return 0;
            }
            int isplace = findPlace(list[id_game].player_list);
            printf("place: %d \n",isplace);
            if(isplace ==-1){
            	sendRegno(sock);
            	return 0;
            }
            list[id_game].player_list[isplace] = addPlayer(list[id_game].player_list[isplace],id,p);
	    
            pthread_mutex_unlock(&verrou);
            strcpy(ur_id, id);
            sendRegok(sock, id_game);
            return id_game;
        } 

    }

} 

int listGame (int sock){
	pthread_mutex_lock(&verrou);
	
//	printf("HERE2 %d \n",length(list));
    	if (sendGames(sock,length(list)) == 0) {
        perror("LISTGAME: cannot sendGames");
        return 0;
    	}
    	

    for(int i = 0; i<100;i++) {
    	
    	if(list[i].create == 1){
    		uint8_t u_int = i;
        	if(sendOgame(sock, u_int, getNbPlayer(list[i]) == 0)){
        		 perror("LISTGAME: cannot sendOGame");
        		return 0;
        	}
        }
        
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
            printf("NB: %u \n",getNbPlayer(list[0]));
            while (ur_game_id > 0) {
            	
                //printf(" Vous etes inscrit! \n");
               /* int status = prepareGame(sock2,ur_id, ur_game_id);
                if(status == 1){
                	ur_game_id = 0;
                	printf("Vous allez retourner au lobby \n"); 
                }
                while(status ==2){
                	printf("Vous etes pret! \n");
                } */
            } 

            printf("Vous n'etes pas/ plus inscrit");
            } 

       }
    

 

int main(int argc, char* argv[]){
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
    
   	//Initialisation de la liste de partie
   	for(int i = 0; i<100;i++){
   		list[i] = setUpList(list[i]);
   		
   	}
    if (r == 0) {
    printf("%d \n", getNbPlayer(list[17]));
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
    
