/*
 * author : Sharar mahmood
 * date : Oct 9 2017
 * name : main.c
 * */
# ifndef STACK_H
# define STACK_H

# include <stdio.h>
# include "LinkedListAPI.h"
# include "stack.h"

void deleteInt(void* a);
void printNum(void *a);
int compareNum(const void * a,const void * b);

int getInput();
int decision(Stack * aStack,int num);
void adjust(Stack * aStack, int num);
void add(Stack * aStack, int num);
int * createNum(int num);

typedef void (*print)(void*);
typedef void(*dFunction)(void*);
typedef int(*cFunction)(const void*,const void *);


int main (void) {
	Stack *aStack;
	int num;
	int value;
	
	print pNum;
	dFunction dNum;
	cFunction compNum;
	
	pNum = printNum;
	dNum = &deleteInt;
	compNum = &compareNum;
	
	aStack = createStack(pNum,dNum,compNum);
	printf("SUCCESSFUL CREATION\n");
	
	
	while(1){
		num = getInput();
		value = decision(aStack,num);
		if(value == 1){
			adjust(aStack,num);
			/*
			if(aStack ->list != NULL){
				printf("\nLIST : \n");
				printForward(aStack -> list);
			}
			* */
		}
		else if(value == 0){
			add(aStack,num);
			if(aStack ->list != NULL){
				printf("\nLIST : \n");
				printForward(aStack -> list);
			}		
		}
		else if(value == -1){
			printf("Thank you\n");
			return 0;
		}
	}
	return 0;
}

void deleteInt(void* a){
	
	free((int*)a);
	a = NULL;
	
	return;
}


void printNum(void *a){
	printf("%d\n",*((int*)a));
}

int compareNum(const void * a,const void * b){
	return (*(int*)a - *(int*)b);
}

int getInput(){
	int num;
	
	printf("Enter a positive number to play or negative number to quit\n");
	scanf("%d",&num);
	
	return num;
}

int decision(Stack * aStack,int num){
	if(num < 0){
		return -1;
	}
	
	if(aStack->count == 0 || *(int*)top(aStack)>num){
		return 0;
	}
	
	return 1;
}

int * createNum(int num){
	int* aNum = malloc(sizeof(int));
	*aNum = num;
	
	return aNum;
}
void add(Stack * aStack, int num){
	if(aStack == NULL){
		return;
	}
	push(aStack, createNum(num));
	
}

void adjust(Stack * aStack, int num){
	
	while(aStack->count > 0 && *((int*)top(aStack)) < num){
		printf("Squashed : %d\n\n",*((int*)top(aStack)));
		pop(aStack);
	}
	push(aStack, createNum(num));
	printf("Remaining : \n");
	printForward(aStack->list);
}
# endif
