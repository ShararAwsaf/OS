/*
 * author : Sharar mahmood
 * date : Oct 1 2017
 * name : main.c
 * */
# ifndef LINKEDLISAPI_H
# define LINKEDLISAPI_H

# include "LinkedListAPI.h"
# include "direction.h"


void deleteListNode(void * element){
	
	free((Node*)element);
	
	element = NULL;
}

typedef void(*deleteFunction)(void*);
typedef int(*compareFunction)(const void*,const void *);
typedef void (*printFunction)(void*);


int main(void){
	List *dList;
	Node *dNode;
	char come1 ,come2 ,come3 ,come4;
	char go1 ,go2 ,go3 ,go4;
	int  arrive1 ,arrive2 ,arrive3 ,arrive4;
	double finish1 ,finish2 ,finish3 ,finish4; 
	Dir *dir1 , *dir2 , *dir3 , *dir4;
	
	deleteFunction dirDel;
	compareFunction dirComp;
	printFunction dirPrint;
	
	dirDel = &deleteDir;
	dirComp = &compareDir;
	dirPrint = &printDir;
	
	/*
	 * Values for cars
	 * */
	 
	come1 = 'N';
	come2 = 'E';
	come3 = 'S';
	come4 = 'W';
	 
	go1 = 'L';
	go2 = 'R';
	go3 = 'F';
	go4 = 'R';
	 
	arrive1 = 2;
	arrive2 = 3;
	arrive3 = 4;
	arrive4 = 5;
	 
	finish1 = 12.3;
	finish2 = 14.5;
	finish3 = 30.0;
	finish4 = 31.0;
	 
	dir1 = malloc(sizeof(Dir));
	dir2 = malloc(sizeof(Dir));
	dir3 = malloc(sizeof(Dir));
	dir4 = malloc(sizeof(Dir));
	 
	setArrival(dir1,come1);
	setArrival(dir2,come2);
	setArrival(dir3,come3);
	setArrival(dir4,come4);
	
	setDeparture(dir1,go1);
	setDeparture(dir2,go2);
	setDeparture(dir3,go3);
	setDeparture(dir4,go4);
	 
	setTime(dir1,arrive1);
	setTime(dir2,arrive2);
	setTime(dir3,arrive3);
	setTime(dir4,arrive4);
	
	setFinishTime(dir1,finish1);
	setFinishTime(dir2,finish2);
	setFinishTime(dir3,finish3);
	setFinishTime(dir4,finish4);
	 
	printf("Testing initialization of a list\n\n");
	
	dList = initializeList(dirPrint,dirDel,dirComp);
	
	printf("Testing for successful list initialization : %s\n\n", dList == NULL ? "Failed":"Passed");
	
	printf("Testing initialization of a Node\n\n");
	dNode = initializeNode(dir4);
	
	printf("Testing for successful node initialization : %s\n\n", dNode == NULL ? "Failed":"Passed");
	
	printf("Testing adding to the front of list\n\n");
	
	insertFront(dList,(void*)dir1);
	
	printf("Testing for successful adding to front : %s\n\n", ((Dir*)(dList->head->data)) == dir1 ? "Passed" : "Failed");
	
	printf("Testing for finding the first element in list\n\n");
	
	printf("Testing for successful peeking head : %s\n\n", (Dir*)getFromFront(dList) == dir1 ? "Passed":"Failed");
	
	
	printf("Testing adding to the end of list\n\n");
	
	insertBack(dList,(void*)dir2);

	printf("Testing for successful adding to end : %s\n\n", ((Dir*)(dList->tail->data)) == dir2 ? "Passed" : "Failed");
	
	printf("Testing finding tail of list\n\n");
	
	printf("Testing for successful peeking tail : %s\n\n", (Dir*)getFromBack(dList) == dir2 ? "Passed":"Failed");
	
	printf("Testing for printing list forwards\n\n");
	
	printForward(dList);
	
	printf("Testing for printing list backwards\n\n");
	
	printBackwards(dList);
	
	
	
	printf("Testing to remove non existent node keeping list unchanged\n\n");
	
	printf("Testing removal of non existent data : %s\n\n", deleteNodeFromList(dList,(void*)dir3) == -1 ? "Passed" : "Failed");
	
	printf("Testing to remove node keeping list unchanged\n\n");
	
	deleteNodeFromList(dList,(void*)dir1);

	printf("Testing removal of the head: %s\n\n", (Dir*)(dList->head->data) == dir2 ? "Passed" : "Failed");
	
	deleteListNode((void*)dNode);
	
	printf("Testing if deleting of list occurs : %s\n\n", (Dir*)dNode->data == dir4 ? "Failed":"Passed");
	
	deleteList(dList);
	
	printf("Testing if deleting of list occurs : %s\n\n", dList-> head != NULL ? "Failed":"Passed");
	
	return 0;
}

#endif

