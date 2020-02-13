/*
 * author : Sharar mahmood
 * date : Oct 1 2017
 * name : main.c
 * */
# ifndef QUEUE_H
# define QUEUE_H

# include "queue.h"
# include "LinkedListAPI.h"

void deleteListNode(void * element){
	
	free((Node*)element);
	
	element = NULL;
}

void deleteDir(void * element){

}

void printF(void * a){
	printf("%d\n",*(int*)a);
}

int compareF(const void * a, const void * b){
	return (int)(*(int*)a-*(int*)b);
}

typedef void(*deleteFunction)(void*);
typedef int(*compareFunction)(const void*,const void *);
typedef void (*printFunction)(void*);


int main(void){
	PriorityQ *aQ = NULL, *bQ = NULL,*cQ = NULL;
	int*  num1;
	
	deleteFunction dirDel;
	compareFunction dirComp;
	printFunction dirPrint;
	
	dirDel = &deleteDir;
	dirComp = &compareF;
	dirPrint = &printF;
	
	num1 = malloc(sizeof(int));
	*num1 = 5;
	
	printf("Testing initialization of a queue\n\n");
	
	aQ = createQ(dirPrint,dirDel,dirComp);
	
	printf("Testing for successful queue initialization : %s\n\n", aQ == NULL ? "Failed":"Passed");
	
	printf("Testing initialization of a queue\n\n");
	
	cQ = createQ(dirPrint,dirDel,dirComp);
	
	printf("Testing for successful queue initialization : %s\n\n", cQ == NULL ? "Failed":"Passed");
	
	printf("Testing adding to the front of que\n\n");
	
	enqueue(aQ,(void*)(num1));
	
	printf("Testing for successful adding to front : %s\n\n", *((int*)(aQ->list->head->data)) == *num1 ? "Passed" : "Failed");
	
	printf("Testing for finding the first element in list\n\n");
	
	printf("Testing for successful peeking head : %s\n\n", *(int*)peek(aQ) == *num1 ? "Passed":"Failed");
	
	
	printf("Testing for printing list forwards\n\n");
	
	printQ(aQ);
	
	
	printf("Testing to remove node from queue unchanged\n\n");
	pop(bQ);
	printf("Testing queue deletion : %s\n\n",  bQ == NULL ? "Passed" : "Failed");
	
	return 0;
}

#endif

