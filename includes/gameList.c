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
  	Playerlist playerlist;
}Gamelist;

int ind = 1;



uint8_t add(Gamelist **list){
	Gamelist *element = malloc(sizeof(Gamelist));
	assert(element != NULL);
	element -> num = ind;
	ind = ind + 1;
	element ->next = *list;
	*list = element;
	return element -> num;
	
	
}

int addPlayerTo(Gamelist *list, uint8_t ngame , char *i , char*p){
	while(list != NULL){
		if(ngame == list -> num){
			Playerlist *pl = &(list ->playerlist);
			addPlayer(&pl,i,p);
			list -> nb_player = (list -> nb_player) + 1;
			return 1;
		}
		list = list -> next;
	}
	return 0;
}

Gamelist* search(Gamelist * list,uint8_t n){
	while(list != NULL){
		if(n == list -> num){
			return list;
		}
		list = list -> next;
	}
	return NULL;
	
}

int length(Gamelist *list){
	int i = 0;
	while(list != NULL){
		i = i+1;
		list = list -> next;
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
	printf("%d \n",length(test));
	add(&test);
	add(&test);
	add(&test);
	uint8_t n = 12;
	Gamelist *res = search(test,n);
	n = 0;
	n = res -> num;
	printf("%u \n",res -> num);
	printf("%d \n",length(test));
	uint8_t v = 2;
	printf("RMV : %d\n",rmv(test,v));
	printf("%d \n",length(test));
	
}  */


