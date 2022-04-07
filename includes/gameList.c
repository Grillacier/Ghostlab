#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct gamelist{

	struct gamelist *next;
	uint8_t num;  // Numero de partie
  	uint8_t nb_player; // Nombre de joueurs
  	// TODO: Ajouter une liste de joueurs
}Gamelist;

int ind = 1;

void add(Gamelist **list){
	Gamelist *element = malloc(sizeof(Gamelist));
	assert(element != NULL);
	element -> num = ind;
	ind = ind + 1;
	element -> nb_player = 1;
	element ->next = *list;
	*list = element;
	
	
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

/* void main(){
	Gamelist *test = NULL;
	add(&test);
	add(&test);
	add(&test);
	printf("%d \n",length(test));
	uint8_t v = 2;
	printf("RMV : %d\n",rmv(test,v));
	printf("%d \n",length(test));
	
} */


