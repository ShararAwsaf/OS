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

void insertSorted(List *list, void *toBeAdded, int value){
	Node * temp,*aNode;
	temp = list->head;
	aNode = malloc(sizeof(Node));
	aNode -> priority = value;
	if(temp == NULL){
		aNode = malloc(sizeof(Node));
		aNode -> data = toBeAdded;
		aNode -> priority = value;
		aNode -> next = NULL;
		aNode -> previous = NULL;
		list->head = aNode;
		list->tail = aNode;
		list->head->next = NULL;
		list->tail->next = NULL;
		return;
	}
	
	if(compare(aNode,list->head)<0){
		aNode = malloc(sizeof(Node));
		aNode -> data = toBeAdded;
		aNode -> priority = value;
		aNode -> previous = NULL;
		aNode->next = list->head;
		list->head = aNode;
		return;
		
	}
	
	if(list->head->next == NULL && compare(aNode,list->head)<0){
			
			aNode = malloc(sizeof(Node));
			aNode->data = toBeAdded;
			aNode -> priority = value;
			aNode -> previous = NULL;
			list->head->next = NULL;
			list ->tail = list->head;
			aNode->next = list->head;
			list->head = aNode;
			
			return;
	}
	else if(list->head->next == NULL && compare(aNode,list->head)>=0){
		aNode = malloc(sizeof(Node));
		aNode->data = toBeAdded;
		aNode -> priority = value;
		aNode -> previous = list->head;
		aNode->next = NULL;
		list->head->next = aNode;
		list->tail = aNode;
		return;
	}

	if(temp == NULL){
		aNode = malloc(sizeof(Node));
		aNode -> data = toBeAdded;
		aNode -> priority = value;
		aNode -> next = NULL;
		aNode -> previous = NULL;
		list->head = aNode;
		list->tail = aNode;
		return;
	}
		
	while(temp->next != NULL) {
		
		if(compare(aNode,temp)>=0 && compare(aNode,temp->next)<0){
			aNode = malloc(sizeof(Node));
			aNode->data = toBeAdded;
			aNode -> priority = value;
			aNode -> previous = temp;
			aNode->next = temp->next;
			temp->next = aNode;
			
			return;
		}
		temp = temp -> next;
	}
	
	aNode = malloc(sizeof(Node));
	aNode -> data = toBeAdded;
	aNode -> priority = value;
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
	
	if(list -> head == NULL){
		list->head = newNode;
		return;
	}
	
	if(list->tail == NULL){
		newNode -> previous = list->head;
	}
	
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
	
	if(list->head == NULL || toBeDeleted == NULL){
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
		if(list->head != NULL)
			list-> head -> previous = NULL;

		list->deleteNode((void*)temp->data);
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


/*
 * A function to compare two patient nodes
 * @param a direction node
 * @param a comapring patient node
 * */
int compare(const void * first,const void * second) {

	return (int)(((Node*)first)->priority) - (int)(((Node*)second)->priority);
}
