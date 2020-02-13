# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <math.h>

# include "LinkedListAPI.h"
# include "direction.h"


void analyzeMovement(List * aList, int * simClock);
float action(Dir * aDir);
int directionMove(List * aList, int* time);
void deleteListNode(void * element);

int main(int argc, char * argv[]){
	FILE * file;
	List *n, *s, *e, *w; 
	Node *tempN, *tempE, *tempS, *tempW;
	float globalClock = 1.0 ;
	float lightClock = 10.0 ;
	
	int clear = 0, green = 0;
	
	
	
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

	globalClock = 1.0;
	lightClock = 10.0;
	green = 1;
		
	while(!clear){
		
		
		//NORTH LIST
		if(tempN == NULL){
			while(lightClock>=0){
				lightClock -=0.5;
				globalClock +=0.5;
			}
			
			while(lightClock>=-3.5 && (int)globalClock % 14 != 0){
					globalClock += 0.5;
					lightClock -= 0.5;
			}
				
			lightClock = 10.0;
			green = 1;
			
		}
		
		while(tempN != NULL){
			
			printf("GLOBAL CLOCK N : %.2f**\n\n",globalClock);
			printf("Light CLOCK N start : %.2f**\n\n",lightClock);
			
			while(globalClock < ((Dir*)tempN->data)->timeArrive ){
				globalClock +=  0.5;
				lightClock -= 0.5;
				if(lightClock == 0){
					green = 0;
					break;
				}
				
				if(tempN!= NULL && globalClock == ((Dir*)tempN->data)->timeArrive){
					green = 1;
					break;
				}
				
			}
			
			if(green){
				((Dir*)tempN -> data) -> timeFinish = globalClock;
				
				lightClock -= action(tempN->data);
				globalClock = ((Dir*)tempN -> data) -> timeFinish;
				tempN = tempN->next;
			}
			
			if(lightClock <= 0 || tempN == NULL){
				
				if(tempN!= NULL && ((Dir*)tempN -> data)->go == 'L' && lightClock ==0 ){	
					action(tempN->data);
					globalClock = ((Dir*)tempN -> data) -> timeFinish;
					tempN = tempN->next;
				}
				while(lightClock>=-3.5 && (int)globalClock % 14 != 0){
					globalClock += 0.5;
					lightClock -= 0.5;
				}
				
				lightClock = 10.0;
				green = 1;
				break;
			}
			
		}
		
		//EAST LIST
		if(tempE == NULL){
			while(lightClock>=0){
				lightClock --;
				globalClock ++;
			}
			
			while(lightClock>=-3.5 && (int)globalClock % 14 != 0){
					globalClock += 0.5;
					lightClock -= 0.5;
			}
				
			lightClock = 10.0;
			green = 1;
			
		}
		
		while(tempE != NULL){
			printf("GLOBAL CLOCK E : %.2f**\n\n",globalClock);
			printf("Light CLOCK E : %.2f**\n\n",lightClock);
			
			while(globalClock < ((Dir*)tempE->data)->timeArrive){
				globalClock +=0.5;
				lightClock -=0.5;
				if(lightClock == 0){
					green = 0;
					break;
				}
				
				if(tempE!= NULL && globalClock == ((Dir*)tempE->data)->timeArrive){
					green = 1;
					break;
				}
				
			}
			
			if(green){
				((Dir*)tempE -> data) -> timeFinish = globalClock;
				
				lightClock -= action(tempE->data);
				globalClock = ((Dir*)tempE -> data) -> timeFinish;
				tempE = tempE->next;
			}
			
			if(lightClock<= 0 || tempE==NULL){
				
				if(tempE!= NULL && ((Dir*)tempE -> data)->go == 'L' && lightClock == 0){	
					action(tempE->data);
					globalClock = ((Dir*)tempE -> data) -> timeFinish;
					tempE = tempE->next;
				}
				
				printf("Light CLOCK WEST END : %.2f**\n\n",lightClock);
			
				while(lightClock>=-3.5 && (int)globalClock % 14 != 0){
					globalClock += 0.5;
					lightClock -= 0.5;
				}
				
				printf("Light clock EAST leaving at : %.2lf\n",lightClock);
				printf("GLOBAL clock EAST leaving at : %.2lf\n",globalClock);
				
				lightClock = 10.0;
				green = 1;
				break;
			}
			
		}
		
		//SOUTH LIST
		
		if(tempS == NULL){
			while(lightClock>=0){
				lightClock -=0.5;
				globalClock +=0.5;
			}
			while(lightClock>=-3.5 && (int)globalClock % 14 != 0){
					globalClock += 0.5;
					lightClock -= 0.5;
			}
			lightClock = 10.0;
			green = 1;
			
		}
		
		while(tempS != NULL){
			printf("GLOBAL CLOCK S : %.2f**\n\n",globalClock);
			printf("Light clock SOUTH : %.2lf\n",lightClock);
			while(globalClock < ((Dir*)tempS->data)->timeArrive){
				
				globalClock +=0.5;
				lightClock -=0.5;
				if(lightClock == 0){
					green = 0;
					break;
				}
				
				if(tempS!= NULL && globalClock == ((Dir*)tempS->data)->timeArrive){
					green = 1;
					break;
				}
			}
			if(green){
				((Dir*)tempS -> data) -> timeFinish = globalClock;
				
				lightClock -= action(tempS->data);
				globalClock = ((Dir*)tempS -> data) -> timeFinish;
				tempS = tempS->next;
				
			}
			
			if(lightClock <= 0 || tempS == NULL){
				
				if(tempS!= NULL && ((Dir*)tempS -> data)->go == 'L' && lightClock == 0){	
					
					action(tempS->data);
					
					globalClock = ((Dir*)tempS -> data) -> timeFinish;
					tempS = tempS->next;
				}
				printf("Light clock SOUTH : %.2lf\n",lightClock);
				while(lightClock>=-3.5 && (int)globalClock % 14 != 0){
					globalClock += 0.5;
					lightClock -= 0.5;
				}
				printf("Light CLOCK SOUTH leaving at : %.2f**\n\n",lightClock);
			
				lightClock = 10.0;
				green = 1;
				break;
			}
			
		}
		
		
		//WEST LIST
		if(tempW == NULL){
			while(lightClock>=0){
				lightClock -=0.5;
				globalClock +=0.5;
			}
			
			while(lightClock>=-3.5 && (int)globalClock % 14 != 0){
					globalClock += 0.5;
					lightClock -= 0.5;
			}				
			lightClock = 10.0;
			green = 1;
		}
		
		while(tempW != NULL ){
			
			printf("GLOBAL CLOCK W : %.2f**\n\n",globalClock);
			printf("Light CLOCK WEST start : %.2f**\n\n",lightClock);
			
			while(globalClock < ((Dir*)tempW->data)->timeArrive){
				globalClock +=0.5;
				lightClock -=0.5;
				
				if(lightClock == 0){
					green = 0;
					break;
				}
				
				if(tempW!= NULL && globalClock == ((Dir*)tempW->data)->timeArrive){
					green = 1;
					break;
				}
			}
			
			if(green){
				((Dir*)tempW -> data) -> timeFinish = globalClock;
			
				lightClock -= action(tempW->data);
				globalClock = ((Dir*)tempW -> data) -> timeFinish;
				tempW = tempW->next;
				
			}
			
			if(lightClock<=0 || tempW == NULL){
				
				if(tempW!= NULL && ((Dir*)tempW -> data)->go == 'L' && lightClock == 0){	
					
					action(tempS->data);
					
					globalClock = ((Dir*)tempW -> data) -> timeFinish;
					tempW = tempW->next;
				}
				
				printf("Light CLOCK WEST end : %.2f**\n\n",lightClock);
			
				while(lightClock>=-3.5 && (int)globalClock % 14 != 0){
					globalClock += 0.5;
					lightClock -= 0.5;
				}
				printf("Light CLOCK WEST leaving at : %.2f**\n\n",lightClock);
			
				lightClock = 10.0;
				green = 1;
				break;
			}
		
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

float action(Dir * aDir) {
	float time ;
	
	time = 0;
	printf("REACHED ACTION\n\n");
	char a = aDir -> go;
	
	if(a == 'F'){
		time = time + 2;
	}
	else if(a == 'R'){
		time = time + 1;
	}
	else {
		time = time + 2.5;
	}
	aDir -> timeFinish += time;
	printf("COME : %c GO : %c\n\n",aDir->come,aDir->go);
	printf("Arrived at : %d Finished at : %.2f\n\n",aDir -> timeArrive,aDir -> timeFinish);
	
	return time;
}

void deleteListNode(void * element){
	
	free((Node*)element);
	
	element = NULL;
}


