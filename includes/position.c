#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct position{

	char x [4];
	char y [4];
	
}Position;

int setPos(Position p , char x , char y){
    
    strcpy( &p.x, &x);
    strcpy( &p.y, &y);
    x [3] = '\n';
	y [3] = '\n';
    
    return 1;
}
    
}
int addToChar(char *base , char ajout){ // Addition de char
    int x = atoi(base);
    int plus = atoi(&ajout);
    int res = x + plus;
    char str_res [4];
    str_res[3] = '\n';
    if(res < 10){
        str_res[0] = '0';
        str_res[1] = '0';
        sprintf(str_res + sizeof(char)*2,"%d",res);
        return 1;
    }
    else{
        str_res[0] = '0';
        sprintf(str_res + sizeof(char),"%d",res);
        return 1;
    
    }
    return 0;
    
}

int rmToChar(char *base , char ajout){ // Soustraction de char
    int x = atoi(base);
    int moins = atoi(&ajout);
    int res = x - moins;
    char str_res [4];
    str_res[3] = '\n';
    if(res < 10){
        str_res[0] = '0';
        str_res[1] = '0';
        sprintf(str_res + sizeof(char)*2,"%d",res);
        return 1;
    }
    else{
        str_res[0] = '0';
        sprintf(str_res + sizeof(char),"%d",res);
        return 1;
    
    }
    return 0;

}





