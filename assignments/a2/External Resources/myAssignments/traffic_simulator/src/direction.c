# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# include "LinkedListAPI.h"
# include "direction.h"

/*
 * A function that creates a direction Node
 * @param tempA specifies which direction car is coming from
 * @param tempD specifies destination of car
 * @param tempT specifies arrival time of car
 * @return a pointer to a direction Node
 * */
Dir * createDir(char tempA,char tempD, int tempT){
	Dir * aDir;
	
	aDir = malloc(sizeof(Dir));
	setArrival(aDir,tempA);
	setDeparture(aDir,tempD);
	setTime(aDir,tempT);
	setFinishTime(aDir,tempT);	
	
	return aDir;
}

/*
 * A function to get arrival direction of car
 * return character of arrival
 * */
char getArrival(Dir * aDir){
		return aDir -> come;
}

/*
 * A function to get departure direction of car
 * return character of destination
 * */
char getDeparture(Dir * aDir){
		return aDir -> go;
}

/*
 * A function to get arrival time of car
 * return integer time of arrival
 * */
int getTime(Dir * aDir){
		return aDir -> timeArrive;
}

/*
 * A function to get processing time of car
 * return float time of finished processing
 * */
float getFinishTime(Dir * aDir){
		return aDir -> timeFinish;
}

/*
 * A function to set arrival direction of car
 * @param character of arrival
 * */
void setArrival(Dir * aDir,char val){
	aDir -> come = val;
}

/*
 * A function to set destination direction of car
 * @param character of destination
 * */
void setDeparture(Dir * aDir, char val){
	aDir -> go = val;
}

/*
 * A function to set arrival time of car
 * @param integer time of arrival
 * */
void setTime(Dir * aDir, int val){
	aDir -> timeArrive = val;
}

/*
 * A function to set processing time of car
 * return float time of processing
 * */
void setFinishTime(Dir * aDir, float val){
	aDir -> timeFinish = val;
}

/*
 * A function to print information of car
 * @param a pointer to a direction node
 * */
void printDir(void* aDir) {
	printf("%c %c %d \t\t\t\t\t %d\t\t%.2f\n\n",getArrival(aDir),getDeparture(aDir),getTime(aDir),getTime(aDir),getFinishTime(aDir));
}

/*
 * A function to delete a direction node
 * @param a direction node
 * */
void deleteDir(void * element){
	free((Dir*)element);
	element = NULL;
}

/*
 * A function to compare two direction nodes
 * @param a direction node
 * @param a comapring direction node
 * */
int compareDir(const void * a,const void * b) {

	return (int)(((Dir*)a)->timeArrive) - (int)(((Dir*)b)->timeArrive);
}

typedef void(*print)(void*);
typedef void(*delete)(void*);
typedef int(*tCompare)(const void*,const void*);

/*
 * A function to prepare list of direction nodes based on direction of arrival
 * @param a direction for building node
 * @param a source file for extracting information
 * @return a sorted list of nodes of similar arrival time
 * */
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
