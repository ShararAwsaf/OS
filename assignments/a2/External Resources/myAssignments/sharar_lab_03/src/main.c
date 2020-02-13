/*
 * author : Sharar mahmood
 * date : Oct 1 2017
 * name : main.c
 * */
# ifndef LINKEDLISAPI_H
# define LINKEDLISAPI_H

# include <stdio.h>
# include "LinkedListAPI.h"
# include "book.h"

void dummyFunction(void * ptr){
		return;
}

int dummyFunction2(const void * a, const void * b){
	return 0;
}

void myPrint(void *a){
	printf("%d\n",*((int*)a));
}

int compareNum(const void * a,const void * b){
	return (*(int*)a - *(int*)b);
}

typedef void(*aFunction)(void*);
typedef int(*aFunction2)(const void*,const void *);
typedef void (*print)(void*);

int main (void) {
	List * list,*list2;
	char * name1;
	char * name2;
	char * name3;
	double num1,num2,num3;
	int *n1 ,*n2,*n3;
	Book * b1,*b2,*b3;
	
	//Stuff with books
	name1 = "Book 1";
	name2 = "Book 2";
	name3 = "Book 3";
	
	aFunction f;
	aFunction2 g;
	aFunction2 compInt;
	print pFptr;
	print yFptr;
	
	f = &dummyFunction;
	g = &dummyFunction2;
	pFptr = &printBook;
	
	// TASK : 1 - Book linked list
	
	b1 = malloc(sizeof(Book));
	b2 = malloc(sizeof(Book));
	b3 = malloc(sizeof(Book));
	
	
	num1 = 12.5;
	setName(b1,name1);
	setPrice(b1,&num1);
	
	num2 = 15;
	setName(b2,name2);
	setPrice(b2,&num2);
	
	num3 = 100.7;
	setName(b3,name3);
	setPrice(b3,&num3);
	
	list = initializeList(pFptr,f,g);
	insertFront(list,(void*)b1);
	insertFront(list,(void*)b2);
	insertFront(list,(void*)b3);
	
	printForward(list);
	
	//TASK 2 : Integer Linked list Insert sorted
	
	yFptr = &myPrint;
	compInt = &compareNum;
	
	list2 = initializeList(yFptr,f,compInt);
	n1 = malloc(sizeof(int));
	n2 = malloc(sizeof(int));
	n3 = malloc(sizeof(int));
	
	*n1 = 7;
	insertSorted(list2,(void*)n1);
	*n2 = 10;
	insertSorted(list2,(void*)n2);
	*n3 = 3;
	insertSorted(list2,(void*)n3);
	
	printf("Ascending\n");
	printForward(list2);
	
	printf("Descending\n");
	printBackwards(list2);
	
	return 0;
}

# endif
