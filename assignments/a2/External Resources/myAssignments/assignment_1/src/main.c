# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# include "LinkedListAPI.h"
# include "direction.h"


void analyzeMovement(List * aList, int * simClock);
void action(Dir * aDir,int* time);
int directionMove(List * aList, int* time);

int main(int argc, char * argv[]){
	FILE * file;
	List *n, *s, *e, *w;
	int globalClock = 1, nClock = 0,eClock = 0, sClock = 0, wClock = 0;
	int clear = 0, count = 0;
	
	file = fopen(argv[1],"r");
	
	if(file == NULL){
		printf("Unable to access file\n");
		return 0;
	}
	
	n = fill('N',fopen(argv[1],"r"));
	e = fill('E',fopen(argv[1],"r"));
	s = fill('S',fopen(argv[1],"r"));
	w = fill('W',fopen(argv[1],"r"));
	
	printf("Initial vehicle information\n\n");
	printForward(n);
	printForward(e);
	printForward(s);
	printForward(w);
	
	while(!clear){
		
		globalClock += directionMove(n,&nClock);
		
		
		clear = 1;
	}
	printf("REACHED END OF WHILE");
	return 0;	
}

void action(Dir * aDir,int* time) {
	char a = aDir -> go;
	
	if(a == 'F'){
		*time = *time + 2;
	}
	else if(a == 'R'){
		*time = *time + 1;
	}
	else {
		*time = *time + 3;
	}
	aDir -> timeFinish += *time;
}

int directionMove(List * aList, int* time){
	
	Node * temp;
	
	temp = aList->head;
	
	while(temp->next != NULL){
		
		if(((Dir*)temp->data)->timeArrive == ((Dir*)temp->data)->timeFinish){
			printf("REACHED\n\n");
			action((Dir*)temp->data,time);
		}
		if(*time%14 == 0){
			return *time;
		}
	}
	return *time;
	
}
