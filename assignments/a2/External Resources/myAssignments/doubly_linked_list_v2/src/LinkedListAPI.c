# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

# include "LinkedListAPI.h"

List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)){
	List * aList;
	aList = malloc(sizeof(List));
	aList->head = NULL;
	aList->tail = NULL;
	
	aList->printNode = printFunction;
	aList->deleteNode = deleteFunction;
	aList->compare = compareFunction;
	
	return aList;
}

void printForward(List * list){
	Node * temp;
	temp = list -> head;
	
	while(temp!=NULL) {
		list->printNode(temp->data);
		temp = temp->next;
	}
}

void printBackwards(List * list){
	Node * temp;
	temp = list -> tail;
	
	while(temp!=NULL) {
		list->printNode(temp->data);
		temp = temp->previous;
	}
}

void * getFromFront(List * list){
	return list->head -> data;
}

void * getFromBack(List * list){
	return list->tail-> data;
}

void insertSorted(List *list, void *toBeAdded){
	Node * temp,*aNode;
	temp = list->head;
	
	if(temp == NULL){
		aNode = malloc(sizeof(Node));
		aNode -> data = toBeAdded;
		aNode -> next = NULL;
		aNode -> previous = NULL;
		list->head = aNode;
		list->tail = aNode;
		return;
	}
		
	while(temp->next != NULL) {
		
		if(list->compare(toBeAdded,temp->data)>=0 && list->compare(toBeAdded,temp->next->data)<=0){
			aNode = malloc(sizeof(Node));
			aNode->data = toBeAdded;
			aNode -> previous = temp;
			aNode->next = temp->next;
			temp->next = aNode;
			
			return;
		}
		temp = temp -> next;
	}
	
	aNode = malloc(sizeof(Node));
	aNode -> data = toBeAdded;
	temp->next = aNode;
	aNode -> next = NULL;
	aNode -> previous = temp;
	list -> tail = aNode;
	
}

Node * initializeNode(void *data){
	Node * newNode;
	newNode = malloc(sizeof(Node));
	
	newNode -> data = data;
	newNode -> next = NULL;
	newNode -> previous = NULL;
	
	return newNode;
}

void insertFront(List *list, void *tobBeAdded){
	Node * newNode;
	
	newNode = initializeNode(toBeAdded);
	
	if(list->head == NULL){
		list->head = newNode;
		list -> tail = NULL;
		
		return;
	}
	
	newNode -> next = list -> head;
	list -> head = newNode;
}

void insertBack(List* list, void * toBeAdded){
	Node * newNode;
	
	newNode = initializeNode(toBeAdded);
	
	newNode -> next = NULL;
	list -> tail = newNode;
	
}

void deleteList(List* list){
	Node * temp;
	temp = list->head;
	while(list->head!=NULL){
		list->deleteNode(temp->data);
		list->head = temp->next;
		free(temp);
	}
	free(list);
}

int deleteNodeFromList(List * list,void * toBeDeleted){
	printf("REACHED\n");
	
	if(list->head == NULL){
		return EXIT_FAILURE;
	}
	
	Node * temp = list -> head;
	Node * position = NULL;
	
	
	while(temp != NULL){
		if(temp == toBeDeleted){
			position = temp;
			break;
		}
		temp = temp->next
	}
	
	if(postion -> previous == NULL){
		list -> head = postion -> next;
		list->deleteNode(position->data);
		free(position);
		return EXIT_SUCCESS;
	}
	
	else if(position -> next == NULL){
		list->tail = position -> previous;
		list->deleteNode(position->data);
		free(position);
		return EXIT_SUCCESS;
	}
	
	else{
		position -> previous ->next = position -> next;
		position -> next -> previous = position -> previous;
		list->deleteNode(position -> data);
		free(postion);
		return EXIT_SUCCESS;
	}
	return -1;
}
