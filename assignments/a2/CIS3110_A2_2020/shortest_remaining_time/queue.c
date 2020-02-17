/*
 * author : Sharar mahmood
 * date : Oct 9 2017
 * name : main.c
 * */
# ifndef STACK_H
# define STACK_H

# include <stdio.h>
# include <stdlib.h>

# include "LinkedListAPI.h"
# include "queue.h"

/*
 * create a new que
 * @param print function pointer
 * @param delete function pointer
 * @param compare function pointer to compare priority values
 * 
 * @return a priority que initialized
 * */
PriorityQ * createQ(void (*printFunction)(void *toBePrinted),
					void (*deleteFunction)(void *toBeDeleted),
					int (*compareFunction)(const void *first, const void *second)
					){

	PriorityQ * aQ = NULL;
	aQ = malloc(sizeof(PriorityQ));
	
	aQ->list = initializeList(printFunction,deleteFunction,compareFunction);
	aQ->count = 0;
	
	return aQ;
}

/*
 * adding elements to prioroty que
 * @param a priority que
 * @param an element to be added
 * */
void enqueue(PriorityQ * aQ,void * data){
	insertBack( &(aQ->list),data);
	aQ -> count += 1;	
}

/*
 * inserting based on priority value in ascending order
 * @param a priority que
 * @param data to be placed
 * */
void insert(PriorityQ * aQ,void * data,int value){
	insertSorted(&(aQ->list),data, value);
	aQ -> count += 1;	
}

/*
 *getting top element of que
 * @param a priority que
 * @return element on top
 * */
void * peek(PriorityQ * aQ){
	if(&(aQ ->list) != NULL)
		return getFromFront(&(aQ->list));
	else
		return NULL;
}

/*
 * remove last element of que
 * @param a priority que
 * */
void pop(PriorityQ * aQ) {
	if(aQ == NULL){
		return;
	}
	else if(&(aQ -> list) == NULL){
		return;
	}
	
	int result = deleteNodeFromList(&(aQ->list), peek(aQ));

	if(result == EXIT_SUCCESS){
		aQ -> count -= 1;
	}
}

/*
 * to get the size of que
 * @param priority que
 * @return total elements in que
 * */
int count(PriorityQ * aQ){
	return aQ -> count;
}

/*
 * print a que based on given print function pointer
 * @param a priority q to print
 * */
void printQ(PriorityQ * aQ){
	printForward(&(aQ->list));
}
# endif

