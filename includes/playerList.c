#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct playerlist{

	//struct playerlist *next; // Joueur suivant
	char id [9]; // Identifiant joueur
  	char port[5]; // Numero du port joueur
  	int place; // 0 libre , 1 prise
  
}Playerlist;

// Fonction d'unite
Playerlist setUpPlayer(Playerlist p){
	p.place = 0;
	return p;
}



Playerlist addPlayer(Playerlist list, char *id , char *p){
	strcpy(list.id ,id);
	list.id[8] = '\n';
	strcpy(list.port,p);
	list.port[4] = '\n';
	list.place = 1;
	return list;
}


Playerlist rmvPlayer(Playerlist p){
	p.place = 0;
	return p;
}
// Fonction de liste 

int findPlace(Playerlist list[]){
	for(int i = 0; i<5; i++){
		if(list[i].place == 0){
			return i;
		}
	}
	return -1;

}

int searchById(Playerlist list[], char *ide){
	for(int i = 0 ;i<5;i++){
		if(strncmp(list[i].id,ide,8) == 0){
			return i;
		}
	}
	return -1;
}
/*void addPlayer(Playerlist **list , char *i , char *p){
	Playerlist *element = malloc(sizeof(Playerlist));
	assert(element != NULL);
	strcpy(element -> id,i);
	printf("%s \n", element ->id);
	strcpy(element -> port,p);
	
	element ->next = *list;
	*list = element;
	
}

Playerlist* searchPlayer(Playerlist * list, char* i){
	while(list != NULL){
		
		if(strcmp(i,list -> id) == 0){
			printf("Trpuvé \n");
			return list;
		}
		list = list -> next;
	}
	printf("Passé \n");
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

  void main(){
	Playerlist *test = NULL;
	printf("%d \n",lengthPlayer(test));
	addPlayer(&test,"lalalala","1234");
	addPlayer(&test,"lolololo","5678");
	addPlayer(&test,"lilolyrp","2587");
	addPlayer(&test,"davydavy","6666");
	printf("%d \n",lengthPlayer(test));
	Playerlist *dvy_chh = searchPlayer(test,"davydavy");
	printf("ID: %s \n",dvy_chh -> id);
	printf("RMV : %d\n",rmvPlayer(test,"lalalala"));
	printf("%d \n",lengthPlayer(test));
	
} */


