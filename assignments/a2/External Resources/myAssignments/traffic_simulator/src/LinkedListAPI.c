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
		list->head->next = NULL;
		list->tail->next = NULL;
		return;
	}
	if(list->compare(toBeAdded,list->head->data)<=0){
		aNode = malloc(sizeof(Node));
		aNode -> data = toBeAdded;
		aNode -> previous = NULL;
		aNode->next = list->head;
		list->head = aNode;
		return;
		
	}
	if(list->head->next == NULL && list->compare(toBeAdded,list->head->data)<=0){
			
			aNode = malloc(sizeof(Node));
			aNode->data = toBeAdded;
			aNode -> previous = NULL;
			list->head->next = NULL;
			list ->tail = list->head;
			aNode->next = list->head;
			list->head = aNode;
			
			return;
	}
	else if(list->head->next == NULL && list->compare(toBeAdded,list->head->data)>=0){
		aNode = malloc(sizeof(Node));
		aNode->data = toBeAdded;
		aNode -> previous = list->head;
		aNode->next = NULL;
		list->head->next = aNode;
		list->tail = aNode;
		return;
	}

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

void insertFront(List *list, void *toBeAdded){
	
	Node * newNode;
	
	newNode = initializeNode(toBeAdded);
	
	newNode -> next = list -> head;
	
	newNode -> previous = NULL;
	
	if(list -> head != NULL){
		list -> head->previous = newNode;
	}
	
	list -> head = newNode;
	
	

}

void insertBack(List* list, void * toBeAdded){
	Node * newNode;
	
	newNode = initializeNode(toBeAdded);
	
	newNode -> next = NULL;
	newNode -> previous = list->tail;
	if(list -> tail != NULL){
		list -> tail -> next = newNode;
	}
	list -> tail = newNode;
	
	if(list -> head != NULL && list -> tail -> previous == NULL){
		list -> tail -> previous = list -> head;
	}
	
	if(list-> head != NULL && list -> head -> next == NULL && list -> tail != NULL){
		list -> head -> next = list -> tail;
	}
}

void deleteList(List* list){
	Node * temp;
	temp = list->head;
	while(list->head!=NULL){
		list->deleteNode(temp->data);
		temp = list -> head;
		list->head = temp->next;
		free(temp);
	}
	list -> tail = NULL;
	free(list);
	
	list  = NULL;
}

int deleteNodeFromList(List * list,void * toBeDeleted){
	
	if(list->head == NULL){
		return EXIT_FAILURE;
	}
	
	Node * temp = list -> head;
	
	while(temp!= NULL){
		
		if(temp->data == toBeDeleted){
			break;
		}
		temp = temp->next;
	}
	
	if(temp == NULL){
		return -1;	
	}
	
	if(temp -> previous == NULL) {
		//printf("REACHED\n");
		list -> head = temp-> next;
		list-> head -> previous = NULL;

		list->deleteNode(temp->data);
		free(temp);
		return EXIT_SUCCESS;
	}
	
	else if(temp -> next == NULL) {
		
		list->tail = temp -> previous;
		list -> tail -> next = NULL;
		list->deleteNode(temp->data);
		free(temp);
		return EXIT_SUCCESS;
	}
	
	else {
		temp-> previous ->next = temp-> next;
		temp-> next -> previous = temp-> previous;
		list->deleteNode(temp -> data);
		free(temp);
		return EXIT_SUCCESS;
	}
	
}
