#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct playerlist{

	struct playerlist *next; // Joueur suivant
	char id [9]; // Identifiant joueur
  	char port[5]; // Numero du port joueur
  
  	// TODO: Ajouter une liste de joueurs
}Playerlist;





void addPlayer(Playerlist **list , char *i , char *p){
	Playerlist *element = malloc(sizeof(Playerlist));
	assert(element != NULL);
	strcpy(element -> id,i);
	strcpy(element -> port,p);
	
	element ->next = *list;
	*list = element;
	
}

Playerlist* searchPlayer(Playerlist * list, char* i){
	while(list != NULL){
		if(strcmp(i,list -> id) == 0){
			return list;
		}
		list = list -> next;
	}
	return NULL;
	
}
int lengthPlayer(Playerlist *list){
	int i = 0;
	while(list != NULL){
		i = i+1;
		list = list -> next;
	}
	return i;
}

int rmvPlayer(Playerlist *list,char *i){
	Playerlist *last = NULL;
	while(list!= NULL){
		//printf("uint : %u \n",n);
		if(strcmp(i,list -> id) == 0){
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
	Playerlist *test = NULL;
	printf("%d \n",length(test));
	add(&test,"lalalala","1234");
	add(&test,"lolololo","5678");
	add(&test,"lilolyrp","2587");
	printf("%d \n",length(test));
	
	printf("RMV : %d\n",rmv(test,"lalalala"));
	printf("%d \n",length(test));
	
} */


