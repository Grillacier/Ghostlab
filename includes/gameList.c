#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "./playerList.c"

typedef struct gamelist{

	struct gamelist *next; // Parti suivante
	uint8_t num;  // Numero de partie
	uint8_t nb_player; // Nombre de joueurs
  	Playerlist player_list [5];
  	int place [5];
  	int started; //si started == nb_joueur alors on met a -1, impossible de rejoindre une partie si started est a -1
  	char ip_cast [16]; // TODO: Implementer l'addresse 
  	char port_cast [5]; //TODO: De meme
}Gamelist;

int ind = 1;

int getNbPlayer(Gamelist *list , uint8_t ngame){
	int nbp = 0;
	while(list != NULL){
		if(ngame == list -> num){
			for(int i = 0; i < 5 ; i++){
				nbp = list ->place[i] + nbp;
			}
			
		}
		list = list -> next;
	}
	
	return nbp;

}

int imReady(Gamelist *list , uint8_t ngame){ // Incremente started, 2 pret, en attente , 0 erreur 
	while(list != NULL){
		if(ngame == list -> num){
			list->started = list->started + 1;
			if(list->started == getNbPlayer(list,ngame)){
				list->started = -1;	
				printf("GAMELIST: La partie %u va démarrer \n",ngame);
				return 2;
			}
			
		}
		return 1;
		list = list -> next;
	}
	
	return 0;
}



uint8_t add(Gamelist **list){
	Gamelist *element = malloc(sizeof(Gamelist));
	assert(element != NULL);
	element -> num = ind;
	ind = ind + 1;
	element -> place[0] = 0;
	element -> place[1] = 0;
	element -> place[2] = 0;
	element -> place[3] = 0;
	element -> place[4] = 0;
	element-> started = 0;
	element ->next = *list;
	*list = element;
	return element -> num;
}
int rmvPlayer(Gamelist *list, uint8_t ngame, char *ide){


	while(list != NULL){
		if(ngame == list -> num){
			for(int i = 0; i < 5 ; i++){
				if(strcmp(list->player_list[i].id,ide) == 0){
				list->place[i] = 0;
				printf("GAMELIST: REMOVE \n");
				return 1;
			}
			}
			
		}
		list = list -> next;
	}
	printf("Cannot find ID in this game \n");
	return 0;
}
	


int addPlayerTo(Gamelist *list, uint8_t ngame , char *i , char*po){
	
	while(list != NULL){
		if(ngame == list -> num && list->started !=-1){
			int place = -1;
			for(int i = 0; i < 5 ; i++){
				if(list->place[i] == 0){
					place = i;
					list->place[i] = 1;
					i = 6;
					//printf("FIND A PLACE \n");
					
				}
			}
			if(place >-1){
				//list -> player_list[place].id = malloc(sizeof(char)*9);
				
				strcpy(list -> player_list[place].id,i);
				//printf("%ld",strlen(list->player_list[place].id));
				//printf("HERE: %s \n",list -> player_list[place].id);
				strcpy(list -> player_list[place].port,po);
				
			}
			
			return list->num;
		}
		list = list -> next;
	}
	printf("Partie complete \n");
	return 0;
}

Gamelist* search(Gamelist * list,uint8_t n){
	while(list != NULL){
		if(n == list -> num){
			printf("ID Searched: %u \n",list->num);
			return list;
		}
		list = list -> next;
	}
	
	return NULL;
	
}

int length(Gamelist *list){
	int i = 0;
	while(list != NULL){
		if(list -> started != -1){
			i = i+1;
		list = list -> next;
		}
	}
	return i;
}

int rmv(Gamelist *list,uint8_t n){
	Gamelist *last = NULL;
	while(list!= NULL){
		//printf("uint : %u \n",n);
		if(list->num == n){
			if(last == NULL){
				list = list -> next;
				//printf("last: NULL \n");
				return 1;
			}
			last->next = list -> next;
			//printf("last no NULL \n");
			return 1;
		}
		last = list;
		list = list -> next;
	}
	return 0;
}

 /*void main(){
	Gamelist *test = NULL;
	//printf("%d \n",length(test));
	add(&test);
	add(&test);
	//add(&test);
	uint8_t n = 12;
	Gamelist *res = search(test,n);
	n = 0;
	n = res -> num;
	printf("%u \n",res -> num);
	printf("%d \n",length(test));
	uint8_t v = 2;
	printf("RMV : %d\n",rmv(test,v));
	printf("%d \n",length(test)); 
	char *p = "8585";
	char *ide = "Sebastia";
	uint8_t ins = addPlayerTo(test,1,ide,p);
	printf("Partie inscrite: %u \n",ins);
	
	char *p2 = "5123";
	char *ide2 = "Kerosene";
	
	ins = addPlayerTo(test,2,ide2,p2);
	printf("LEN: %d \n", getNbPlayer(test,ins));
	printf("Partie inscrite: %u \n",ins);
	char *id = test->player_list[1].port; // ATTENTION : il faut chercher la partie puis les joueurs
	printf("LEN: %d \n", getNbPlayer(test,ins));
	int _res = rmvPlayer(test,ins,ide2);
	printf("LEN: %d \n", getNbPlayer(test,ins));
	
	printf("%s \n",id);
	char *id2 = test->player_list[0].port;
	
	printf("%s \n",id2);  
	
	
}  */


