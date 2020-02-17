# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

# include "LinkedListAPI.h"

List initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)){
	List aList;
	
	aList.head = NULL;
	aList.tail = NULL;
	
	aList.printNode = printFunction;
	aList.deleteNode = deleteFunction;
	aList.compare = compareFunction;
	
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
	if(list->head == NULL)
		return NULL;

	return list->head -> data;
}

void * getFromBack(List * list){
	if (list->tail == NULL){
		return NULL;
	}
	
	return list->tail->data;
}

void insertSorted(List *list, void *toBeAdded, int value){
	if (list == NULL || toBeAdded == NULL){
		return;
	}
	
	if (list->head == NULL){
		insertBack(list, toBeAdded);
		
		return;
	}
	
	if (list->compare(toBeAdded, list->head->data) <= 0){
		insertFront(list, toBeAdded);
		
		return;
	}
	
	if (list->compare(toBeAdded, list->tail->data) > 0){
		insertBack(list, toBeAdded);
		
		return;
	}
	
	Node* currNode = list->head;
	
	while (currNode != NULL){
		if (list->compare(toBeAdded, currNode->data) <= 0){
		
			
			Node* newNode = initializeNode(toBeAdded);
			newNode->next = currNode;
			newNode->previous = currNode->previous;
			currNode->previous->next = newNode;
			currNode->previous = newNode;
			
			
			return;
		}
	
		currNode = currNode->next;
	}
	
	return;
}

Node * initializeNode(void *data){
	Node* tmpNode;
	
	tmpNode = (Node*)malloc(sizeof(Node));
	
	if (tmpNode == NULL){
		return NULL;
	}
	
	tmpNode->data = data;
	tmpNode->previous = NULL;
	tmpNode->next = NULL;
	
	return tmpNode;
}

void insertFront(List *list, void *toBeAdded){

	if (list == NULL || toBeAdded == NULL){
		return;
	}
	
	Node* newNode = initializeNode(toBeAdded);
	
    if (list->head == NULL && list->tail == NULL){
        list->head = newNode;
        list->tail = list->head;
    }else{
		newNode->next = list->head;
        list->head->previous = newNode;
    	list->head = newNode;
    }
	

}

void insertBack(List* list, void * toBeAdded){
	if (list == NULL || toBeAdded == NULL){
		return;
	}
	
	Node* newNode = initializeNode(toBeAdded);
	
    if (list->head == NULL && list->tail == NULL){
        list->head = newNode;
        list->tail = list->head;
    }else{
		newNode->previous = list->tail;
        list->tail->next = newNode;
    	list->tail = newNode;
    }
    
}

void deleteList(List* list){
	if (list == NULL){
		return;
	}
	
	if (list->head == NULL && list->tail == NULL){
		return;
	}
	
	Node* tmp;
	
	while (list->head != NULL){
		list->deleteNode(list->head->data);
		tmp = list->head;
		list->head = list->head->next;
		free(tmp);
		
	}
	
	list->head = NULL;
	list->tail = NULL;
	
}

int deleteNodeFromList(List * list,void * toBeDeleted){
	
	if (list == NULL || toBeDeleted == NULL){
		return -1;
	}
	
	Node* tmp = list->head;
	
	while(tmp != NULL){
		if (toBeDeleted==tmp->data){
			//Unlink the node
			Node* delNode = tmp;
			
			if (tmp->previous != NULL){
				tmp->previous->next = delNode->next;
			}else{
				list->head = delNode->next;
			}
			
			if (tmp->next != NULL){
				tmp->next->previous = delNode->previous;
			}else{
				list->tail = delNode->previous;
			}
			
			list->deleteNode(delNode->data);
			free(delNode);

			
			return EXIT_SUCCESS;
			
		}else{
			tmp = tmp->next;
		}
	}
	
	return -1;
	
}


/*
 * A function to compare two patient nodes
 * @param a direction node
 * @param a comapring patient node
 * */
int compare(const void * first,const void * second) {

	return ((Node*)first)->priority - ((Node*)second)->priority;
}
