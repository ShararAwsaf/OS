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
# include "stack.h"


Stack * createStack(void (*printFunction)(void *toBePrinted),
					void (*deleteFunction)(void *toBeDeleted),
					int (*compareFunction)(const void *first, const void *second)
					){

	Stack * aStack = NULL;
	aStack = malloc(sizeof(Stack));
	
	aStack->list = initializeList(printFunction,deleteFunction,compareFunction);
	aStack->count = 0;
	
	return aStack;
}

void push(Stack * aStack,void * data){
	insertFront(aStack->list,data);
	aStack -> count += 1;	
}

void pop(Stack * aStack) {
	if(aStack == NULL || aStack -> list == NULL){
		return;
	}
	
	int result = deleteNodeFromList(aStack -> list,top(aStack));

	if(result == EXIT_SUCCESS){
		aStack -> count -= 1;
	}
}

void * top(Stack * aStack){
	return getFromFront(aStack -> list);
}

int count(Stack * aStack){
	return aStack -> count;
}
# endif
