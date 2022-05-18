#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define X 20
#define Y 20
typedef struct labyrinthe{

	int matrice [X][Y];
  	// TODO: Ajoutez fantomes
  	// TODO: Ajoutez tableaux de point??
  	// TODO: Arretez de me les casser
  	
}Lab;

void printLab( Lab l){
	for(int i = 0; i<Y;i++){
		for(int j = 0; j<X;j++){
			printf("%d|",l.matrice[i][j]);
	
		}
		printf("\n");
	}
	
} 


int notIllegal (Lab l , int px, int py){

	if(px<0 || px>X-1){
		return -1;
	}
	if(py<0 || py>Y-1){
		return -1;
	}
	return 1;
}
int surrounded(Lab l , int px , int py){
	if(notIllegal(l,px,py+1) == 1){
		return 1;
	}
	if(notIllegal(l,px,py+1) == 1){
		return 1;
	}
	if(notIllegal(l,px,py+1) == 1){
		return 1;
	}
	if(notIllegal(l,px,py+1) == 1){
		return 1;
	}
	return -1;
	
}

Lab createLab(Lab l, int px , int py, int running){

	if (running == 0){
		return l;
	}
	//srand(time(NULL));
	l.matrice[py][px] = 1;
	int way = rand() % 4;
	int notDone = 1;
	while(notDone == 1){
	//printLab(l);
	way = rand() % 4;
	//printf("WAY: %d \n",way);
	//printf("px: %d , py: %d \n",px,py);
	switch(way){
		
		
		case 0:
			//printf("GO DOWN ?\n");
			if(notIllegal(l,px,py+1) == 1){
			//printf("YES\n");
			py = py +1;
			l.matrice[py][px] = 1;
			notDone = 0;
			}
			
			break;
		case 1:
			//printf("GO UP ? \n");
			if(notIllegal(l,px,py-1) == 1){
			//printf("YES \n");
			py = py -1;
			l.matrice[py][px] = 1;
			notDone = 0;
			}
			
			break;
		case 2:
			//printf("GO RIGTH ? \n");
			if(notIllegal(l,px+1,py) == 1){
			//printf("YES \n");
			px = px +1;
			l.matrice[py][px] = 1;
			notDone = 0;
			}
			
			break;
		case 3:
			//printf("GO LEFT ? \n");
			if(notIllegal(l,px-1,py) == 1){
			//printf("YES \n");
			px = px- 1;
			l.matrice[py][px] = 1;
			notDone = 0;
			
			}
			
			break;
		default:
			break;
		}
	}
	//printf("NEXT\n");
	return createLab(l,px,py,running -1);
}

// Prototype, meilleur rendement mais bug
/*Lab setLab(Lab l, int px , int py, int running){

	if (running == 0){
		return l;
	}
	srand(time(NULL));
	l.matrice[py][px] = 1;
	int way = rand() % 4;
	int notDone = 2;
	while(notDone == 2){
	way = rand() % 4;
	printf("WAY: %d \n",way);
	switch(way){
	printf("SWITCH");
		case 0:
			if(notIllegal(l,px,py+1) == 1){
			printf("GO DOWN \n");
			py = py +1;
			l.matrice[py][px] = 1;
			notDone = rand() % 2;
			}
		case 1:
			if(notIllegal(l,px,py-1) == 1){
			printf("GO UP \n");
			py = py -1;
			l.matrice[py][px] = 1;
			notDone = rand() % 2;
			}
		case 2:
			if(notIllegal(l,px+1,py) == 1){
			printf("GO RIGHT \n");
			px = px +1;
			l.matrice[py][px] = 1;
			notDone = rand() % 2;
			}
		case 3:
			if(notIllegal(l,px-1,py) == 1){
			printf("GO LEFT \n");
			px = px- 1;
			l.matrice[py][px] = 1;
			notDone = rand() % 2;
			}
		}
	}
	switch(notDone){
		case 0:
			return setLab(l,px,py,running -1);
		
		case 1:
			px = rand() % 10;
			py = rand() % 10;
			while(l.matrice[py][px] == 0 || surrounded(l,px,py) == -1){
			px = rand() % 10;
			py = rand() % 10;	
			}
			return setLab(l,px,py,running -1);
	}
	return l;
} */

Lab fillLab(Lab l){
	for(int y = 0; y<Y ; y++){
		
		for(int x = 0; x<X ; x++){
			l.matrice[y][x] = 0;
		}
	}
	//printLab(l);
	int px = 11;
	int py = 9;
	l =createLab(l,px,py,800);
	return l;
}


void main(){
	Lab test = fillLab(test);
	
	printLab(test);
	



}
