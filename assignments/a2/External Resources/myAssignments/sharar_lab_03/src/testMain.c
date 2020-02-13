/*
 * author : Sharar mahmood
 * date : Oct 1 2017
 * name : main.c
 * */
# ifndef LINKEDLISAPI_H
# define LINKEDLISAPI_H

# include "LinkedListAPI.h"
# include "book.h"

void deleteBook(void *element){
	free((Book*)element);
	element = NULL;
}

void deleteInt(void* a){
	free((int*)a);
	a = NULL;
}

void deleteListNode(void * element){
	
	free((Node*)element);
	
	element = NULL;
}

int compareNum(const void * a,const void * b){
	return (*(int*)a - *(int*)b);
}

void myPrint(void *a){
	printf("%d\n",*((int*)a));
}

typedef void(*aFunction)(void*);
typedef int(*aFunction2)(const void*,const void *);
typedef void (*print)(void*);


int main(void){
	
	List * bList,* iList;
	Node * bNode,* iNode;
	char * name1;
	char * name2;
	char * name3;
	char * name4;
	double num1,num2,num3,num4;
	int *n1 ,*n2,*n3,*n4,*n5;
	Book * b1,*b2,*b3,*b4;
	
	aFunction bd,id;
	aFunction2 f2;
	print p=&myPrint; // Nothing to print
	

	
	f2 = &compareNum;
	bd = &deleteBook;
	id = &deleteInt;
	
	//Stuff with books
	name1 = "Book 1";
	name2 = "Book 2";
	name3 = "Book 3";
	name4 = "Book 4";
	
	b1 = malloc(sizeof(Book));
	b2 = malloc(sizeof(Book));
	b3 = malloc(sizeof(Book));
	b4 = malloc(sizeof(Book));
	
	num1 = 12.5;
	setName(b1,name1);
	setPrice(b1,&num1);
	
	num2 = 15;
	setName(b2,name2);
	setPrice(b2,&num2);
	
	num3 = 100.7;
	setName(b3,name3);
	setPrice(b3,&num3);
	
	num4 = 500.17;
	setName(b4,name4);
	setPrice(b3,&num4);
	
	//Stuff with numbers
	n1 = malloc(sizeof(int));
	n2 = malloc(sizeof(int));
	n3 = malloc(sizeof(int));
	n4 = malloc(sizeof(int));
	n5 = malloc(sizeof(int));
	
	*n1 = 7;
	*n2 = 10;
	*n3 = -1;
	*n4 = 11;
	*n5 = 22;
	
	
	printf("Testing initialization of a list\n\n");
	
	bList = initializeList(p,bd,f2);
	iList = initializeList(p,id,f2);
	
	printf("Testing for successful list initialization : %s\n\n", bList == NULL ? "Failed":"Passed");
	printf("Testing for successful list initialization : %s\n\n", iList == NULL ? "Failed":"Passed");
	
	printf("Testing initialization of a Node\n\n");
	bNode = initializeNode(b4);
	iNode = initializeNode(n5);
	
	printf("Testing for successful node initialization : %s\n\n", bNode == NULL ? "Failed":"Passed");
	printf("Testing for successful node initialization : %s\n\n", iNode == NULL ? "Failed":"Passed");
	
	printf("Testing adding to the front of list\n\n");
	
	
	insertFront(bList,(void*)b1);
	insertFront(iList,(void*)n1);
	
	printf("Testing for successful adding to front : %s\n\n", ((Book*)(bList->head->data)) == b1 ? "Passed" : "Failed");
	printf("Testing for successful adding to front : %s\n\n", *((int*)(iList->head->data)) == *n1 ? "Passed" : "Failed");
	
	printf("Testing for finding the first element in list\n\n");
	
	printf("Testing for successful peeking head : %s\n\n", (Book*)getFromFront(bList) == b1 ? "Passed":"Failed");
	printf("Testing for successful peeking head : %s\n\n", *(int*)getFromFront(iList) == *n1 ? "Passed":"Failed");
	
	
	printf("Testing adding to the end of list\n\n");
	
	insertBack(bList,(void*)b2);
	insertBack(iList,(void*)n2);
	
	
	printf("Testing for successful adding to end : %s\n\n", ((Book*)(bList->tail->data)) == b2 ? "Passed" : "Failed");
	printf("Testing for successful adding to end : %s\n\n", *((int*)(iList->tail->data)) == *n2 ? "Passed" : "Failed");
	
	printf("Testing finding tail of list\n\n");
	
	printf("Testing for successful peeking tail : %s\n\n", (Book*)getFromBack(bList) == b2 ? "Passed":"Failed");
	printf("Testing for successful peeking tail : %s\n\n", *(int*)getFromBack(iList) == *n2 ? "Passed":"Failed");
	
	printf("Testing the sorted insertion of data to list\n\n");
	
	insertSorted(iList,(void*)n3);
	
	
	printf("Testing for sorted insertion to front of list : %s\n\n",*(int*)(iList->head->data) == *n3 ? "Passed":"Failed");
	
	insertSorted(iList,(void*)n4);
	
	printf("Testing for sorted insertion to back of list : %s\n\n",*(int*)(iList->tail->data) == *n4 ? "Passed":"Failed");
	
	
	printf("Testing to remove node keeping list unchanged\n\n");
	
	deleteNodeFromList(bList,(void*)b1);
	
	printf("Testing removal of the head : %s\n\n", (Book*)(bList->head->data) == b2 ? "Passed" : "Failed");
	
	deleteNodeFromList(iList,(void*)n4);
	
	printf("Testing removal of the tail : %s\n\n", *(int*)(iList->tail->data) == *n2 ? "Passed" : "Failed");
	
	printf("Testing to remove non existent node keeping list unchanged\n\n");
	
	printf("\nTesting removal of non existent data : %s\n\n", deleteNodeFromList(bList,(void*)b3) == -1 ? "Passed" : "Failed");
	
	
	deleteListNode((void*)iNode);
	
	printf("Testing if deleting of list occurs : %s\n\n", *(int*)iNode->data == *n5 ? "Failed":"Passed");
	
	deleteListNode((void*)bNode);
	
	printf("Testing if deleting of list occurs : %s\n\n", (Book*)bNode->data == b4 ? "Failed":"Passed");
	
	printf("Testing for list deleting\n\n");
	
	deleteList(iList);
	
	printf("Testing if deleting of list occurs : %s\n\n", iList->head != NULL ? "Failed":"Passed");
	
	deleteList(bList);
	
	printf("Testing if deleting of list occurs : %s\n\n", bList->tail != NULL ? "Failed":"Passed");
	
	return 0;
}

#endif
