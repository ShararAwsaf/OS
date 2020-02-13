# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# include "LinkedListAPI.h"
# include "direction.h"

Dir * createDir(char tempA,char tempD, int tempT){
	Dir * aDir;
	
	aDir = malloc(sizeof(Dir));
	setArrival(aDir,tempA);
	setDeparture(aDir,tempD);
	setTime(aDir,tempT);
	setFinishTime(aDir,tempT);	
	
	return aDir;
}

char getArrival(Dir * aDir){
		return aDir -> come;
}

char getDeparture(Dir * aDir){
		return aDir -> go;
}

int getTime(Dir * aDir){
		return aDir -> timeArrive;
}

int getFinishTime(Dir * aDir){
		return aDir -> timeFinish;
}

void setArrival(Dir * aDir,char val){
	aDir -> come = val;
}

void setDeparture(Dir * aDir, char val){
	aDir -> go = val;
}

void setTime(Dir * aDir, int val){
	aDir -> timeArrive = val;
}

void setFinishTime(Dir * aDir, int val){
	aDir -> timeFinish = val;
}

void printDir(void* aDir) {
	printf("%c %c %d %d\n\n",getArrival(aDir),getDeparture(aDir),getTime(aDir),getFinishTime(aDir));
}

void deleteDir(void * element){
	free(element);
	element = NULL;
}

int compareDir(const void * a,const void * b) {

	return (int)(((Dir*)a)->timeArrive) - (int)(((Dir*)b)->timeArrive);
}

typedef void(*print)(void*);
typedef void(*delete)(void*);
typedef int(*tCompare)(const void*,const void*);

List * fill(char s,FILE * f){
	List *aList;
	char tempA;
	char tempD;
	int tempT;
	print p;
	delete d;
	tCompare c;
	
	p = &printDir;
	d = &deleteDir;
	c = &compareDir;
	
	aList = initializeList(p,d,c);
	
	while(!feof(f)) {
		fscanf(f,"%c %c %d\n",&tempA,&tempD,&tempT);
		if(tempA == s) {			
			
			insertSorted(aList,createDir(tempA,tempD,tempT));
						
		}
	}
	
	return aList;
	
}
