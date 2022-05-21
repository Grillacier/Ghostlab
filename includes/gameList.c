#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "./playerList.c"

typedef struct gamelist{

	
	
  	Playerlist player_list [5];
  	int started; // 6 si lancé
  	char ip_cast [16]; // TODO: Implementer l'addresse 
  	char port_cast [5]; //TODO: De meme
  	int create;
}Gamelist;

// Fonction de tableau

uint8_t length(Gamelist list[]){
	//printf("HERE %u \n", list[17].create);
        uint8_t taille = 0;	
	for(int i = 0; i<100;i++){
		if(list[i].create == 1 && list[i].started != -1){
			taille = taille + 1;
		}
	}
	return taille;
}

uint8_t findRoom(Gamelist list[]){
	for(int i = 0; i<100;i++){
		if(list[i].create == 0){
			return i;
		}
	}
	return -1;
}

//Fonction d'unite

uint8_t getNbPlayer(Gamelist list){
	uint8_t nbp = 0;
	for(int i = 0; i < 5 ; i++){
		if(list.player_list[i].place == 1){
			nbp = nbp +1;
			}
		}
	
	return nbp;
	}

Gamelist addPlayerTo(Gamelist list, char *id, char *p){
	int libre = findPlace(list.player_list);
	if(libre == -1){
		perror("Partie complete \n");
	}
	list.player_list[libre] = addPlayer(list.player_list[libre],id,p);
	printf("Inscrit! \n");
	return list;

}

int isCreate(Gamelist list){
	return list.create;
}

Gamelist upStart(Gamelist list){

	list.started = list.started + 1;
	if(getNbPlayer(list) == list.started){
		list.started = 6;
	}
	return list;
}

Gamelist create(Gamelist list){
	list.create = 1;
	return list;
}

Gamelist setUpList(Gamelist list){
	list.started = 0;
	list.create = 0;
	for(int i = 0;i<5;i++){
		list.player_list[i] = setUpPlayer(list.player_list[i]);
	}
	return list;
	
}



	


/*

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
				
				strcpy(list -> player_list[place].id,i);
				
				strcpy(list -> player_list[place].port,po);
				
			}
			printf("Vous etes inscrit \n");
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
	return 0; */
//}

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


