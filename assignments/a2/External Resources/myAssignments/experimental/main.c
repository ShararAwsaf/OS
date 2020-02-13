# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# include "LinkedListAPI.h"
# include "direction.h"


void analyzeMovement(List * aList, int * simClock);
void action(Dir * aDir);
int directionMove(List * aList, int* time);

int main(int argc, char * argv[]){
	FILE * file;
	List *n, *s, *e, *w; 
	Node *tempN, *tempE, *tempS, *tempW;
	int globalClock ;
	//int nClock = 0,eClock = 0, sClock = 0, wClock = 0;
	int clear = 0, sameCycle = 0;
	
	file = fopen(argv[1],"r");
	
	if(file == NULL){
		printf("Unable to access file\n");
		return 0;
	}
	
	n = fill('N',fopen(argv[1],"r"));
	e = fill('E',fopen(argv[1],"r"));
	s = fill('S',fopen(argv[1],"r"));
	w = fill('W',fopen(argv[1],"r"));
	
	tempN = n->head;
	tempE = e->head;
	tempS = s->head;
	tempW = w->head;
	
	printf("Initial vehicle information\n\n");
	printForward(n);
	printForward(e);
	printForward(s);
	printForward(w);
	
	printf("Initial vehicle information Backwards\n\n");
	printBackwards(n);
	printBackwards(e);
	printBackwards(s);
	printBackwards(w);

	globalClock = ((Dir*)getFromFront(n))->timeArrive;
	
	while(!clear){
		
		while(tempN != NULL){
			sameCycle = 1;
			((Dir*)tempN -> data) -> timeFinish = globalClock;
			
			if(tempN->previous!=NULL && sameCycle){
				((Dir*)tempN -> data) -> timeFinish += ((Dir*)tempN-> previous -> data) -> timeFinish; 
			}
			action(tempN->data);
			globalClock = ((Dir*)tempN -> data) -> timeFinish;
			
			
			if(globalClock % 10 == 0){
				sameCycle = 0;
				if(((Dir*)tempN -> data)->go == 'L'){	
					action(tempN->data);
					globalClock = ((Dir*)tempN -> data) -> timeFinish;
					tempN = tempN->next;
				}
				globalClock += 18;
				
				((Dir*)tempE -> data) -> timeFinish = globalClock;
				break;
			}
			tempN = tempN->next;
		}
		
		while(tempE != NULL){
			sameCycle = 1;
			((Dir*)tempE -> data) -> timeFinish = globalClock;
			
			if(tempE->previous!=NULL && sameCycle){
				((Dir*)tempE -> data) -> timeFinish += ((Dir*)tempE -> previous->data) -> timeFinish; 
			}
			action(tempE->data);
			globalClock = ((Dir*)tempE -> data) -> timeFinish;
			
			if(globalClock % 10 == 0){
				sameCycle = 0;
				if(((Dir*)tempE -> data)->go == 'L'){	
					action(tempE->data);
					globalClock = ((Dir*)tempE -> data) -> timeFinish;
					tempE = tempE->next;
				}
				globalClock += 18;
				
				globalClock = ((Dir*)tempE -> data) -> timeFinish;
				break;
			}
			
			tempE = tempE->next;

		}
		
		while(tempS != NULL){
			sameCycle = 1;
			((Dir*)tempS -> data) -> timeFinish = globalClock;
			
			if(tempS->previous!=NULL ){
				((Dir*)tempS -> data) -> timeFinish += ((Dir*)tempS -> previous->data) -> timeFinish; 
			}
			
			action(tempS->data);
			globalClock = ((Dir*)tempS -> data) -> timeFinish;
			
			
			if(globalClock % 10 == 0){
				sameCycle = 0;
				if(((Dir*)tempS -> data)->go == 'L'){	
					action(tempS->data);
					globalClock = ((Dir*)tempS -> data) -> timeFinish;
					tempS = tempS->next;
				}
				globalClock += 18;
				
				globalClock = ((Dir*)tempS -> data) -> timeFinish;
				break;
			}
			
			tempS = tempS->next;

		}
		
		while(tempW != NULL){
			sameCycle = 1;
			((Dir*)tempW -> data) -> timeFinish = globalClock;
				
			if(tempW->previous!=NULL){
				((Dir*)tempW -> data) -> timeFinish += ((Dir*)tempW -> previous->data) -> timeFinish; 
			}
			
			action(tempW->data);
			globalClock = ((Dir*)tempW -> data) -> timeFinish;
			
			
			if(globalClock % 10 == 0){
				sameCycle = 0;
				if(((Dir*)tempW -> data)->go == 'L'){	
					action(tempW->data);
					globalClock = ((Dir*)tempW -> data) -> timeFinish;
					tempW = tempW->next;
				}
				globalClock += 18;
				
				globalClock = ((Dir*)tempW -> data )-> timeFinish;
				break;
			}
			
			tempW = tempW->next;

		}
		
		if(tempN == NULL && tempE == NULL && tempS == NULL && tempW == NULL)
			clear = 1;
	}
	
	printf("REACHED END OF WHILE\n\n");
	
	printForward(n);
	printForward(e);
	printForward(s);
	printForward(w);
	
	return 0;	
}

void action(Dir * aDir) {
	int time ;
	
	time = 0;
	printf("REACHED\n\n");
	char a = aDir -> go;
	
	if(a == 'F'){
		time = time + 2;
	}
	else if(a == 'R'){
		time = time + 1;
	}
	else {
		time = time + 3;
	}
	aDir -> timeFinish += time;
	printf("COME : %c GO : %c\n\n",aDir->come,aDir->go);
	printf("Arrived at : %d Finished at : %d\n\n",aDir -> timeArrive,aDir -> timeFinish);
}
/*
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
*/
