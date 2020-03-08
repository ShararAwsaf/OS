#include <stdio.h>
#include <stdlib.h>

#include "LinkedListAPI.h"

List initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)){
    
    List linkedList;

    linkedList.deleteNode = deleteFunction;
    linkedList.printNode = printFunction;
    linkedList.compare = compareFunction;

    linkedList.tail = NULL;
    linkedList.head = NULL;


    return linkedList;
}

void deleteList(List *list){

    if(list == NULL){
        return;
    }
    else if(list->tail == NULL && list->head == NULL){
        return;
    }

    Node* tmp = list->head;

    while(tmp!=NULL){
        Node* deletedNode = tmp;
        tmp = tmp->next;
        list->deleteNode(deletedNode->data);
        deleteListNode(deletedNode);
    }
    tmp = NULL;
    list->tail = NULL;
    list->head = NULL;
}

Node *initializeNode(void *data){
    Node* aNode = NULL;

    if(data == NULL){
        return aNode;
    }

    aNode = malloc(sizeof(Node));

    aNode->data = data;
    aNode->previous = NULL;
    aNode->next = NULL;

    aNode->priority = 0;

    return aNode;
}



void *getFromFront(List *list){
    if(list != NULL && list->head != NULL)
        return list->head->data;

    return NULL;
}

void *getFromBack(List *list){
    if(list != NULL && list->tail != NULL)
        return list->tail->data;

    return NULL;
}

// NOT TESTED
void printForward(List *list){
    if(list == NULL || list->head == NULL)
        return;

    Node* tempListNode = list->head;

    while(tempListNode != NULL){
        if(tempListNode->data != NULL)
            list->printNode(tempListNode->data);
        tempListNode = tempListNode->next;
    }

}

// NOT TESTED
void printBackwards(List *list){
    if(list == NULL || list->tail == NULL)
        return;

    Node* tempListNode = list->tail;

    while(tempListNode != NULL){
        if(tempListNode->data != NULL)
            list->printNode(tempListNode->data);
        tempListNode = tempListNode->previous;
    }

}



void insertFront(List *list, void *toBeAdded){
    if(toBeAdded == NULL)
        return;

    else if(list == NULL)
        return;
    
    Node* aNode = initializeNode(toBeAdded);

    // FOR FIRST ENTRY
    if(list->head != NULL && list->tail != NULL){
        aNode->previous = NULL;
        aNode->next = list->head;
        
        list->head->previous = aNode;
        list->head = aNode;
    }
    // FOR OTHER ENTRIES
    else{
        list->tail = aNode;
        list->head = list->tail;
    }
    
}


void insertBack(List *list, void *toBeAdded){
    if(toBeAdded == NULL)
        return;

    else if(list == NULL)
        return;

    Node* aNode = initializeNode(toBeAdded);

    //FOR FIRST ENTRY
    if(list->tail != NULL && list->head != NULL){
        aNode->previous = list->tail;
        aNode->next = NULL;

        list->tail->next = aNode;
        list->tail = aNode;
    }
    // FOR OTHER ENTRIES
    else{
        list->head = aNode;
        list->tail = list->head;
    }
}

void insertSorted(List *list, void *toBeAdded, int value){
    if(toBeAdded == NULL)
        return;

    else if(list == NULL)
        return;

    // LIST IS EMPTY
    if(list->tail == NULL){
        insertFront(list, toBeAdded);
        return;
    }

    // ITEM SMALLER THAN LIST HEAD (ASSUMING LIST IS ALREADY SORTED)
    if(list->head != NULL && list->compare(toBeAdded, list->head->data) < 0){
        insertFront(list, toBeAdded);
        return;
    }

    //ITEM LARGER THAN LIST TAIL (ASSUMING LIST IS ALREADY SORTED)
    if(list->compare(list->tail->data, toBeAdded) <= 0){
        insertBack(list, toBeAdded);
        return;
    }

    Node* tmp = list->head;
    Node* aNode = NULL;

    while(tmp!=NULL){
        if(list->compare(toBeAdded, tmp->data) < 0){
            aNode = initializeNode(toBeAdded);
            aNode->next = tmp;
            aNode->previous = tmp->previous;

            if(tmp->previous != NULL)
                tmp->previous->next = aNode;
            tmp->previous = aNode;

            return;
        }

        tmp = tmp->next;
    }


}


void deleteListNode(void *toBeDeleted){
    if(toBeDeleted == NULL)
        return;

    free(toBeDeleted);
}

int deleteNodeFromList(List *list, void *toBeDeleted){
    int deletionReturn = EXIT_SUCCESS;
    if(toBeDeleted == NULL)
        return deletionReturn;

    else if(list == NULL)
        return deletionReturn;

    Node* tmp = list->head;
    Node* deletedNode = NULL;
    while(tmp!=NULL){
        if(tmp->data == toBeDeleted){
            deletedNode = tmp;
            // ADJUST THE LINKS
            if(deletedNode->previous != NULL){
                deletedNode->previous->next = deletedNode->next;
            }
            else{
                // HEAD IS BEING DELETED
                list->head = deletedNode->next;
            }

            if(deletedNode->next!=NULL){
                deletedNode->next->previous = deletedNode->previous;
            }
            else{
                // TAIL IS BEING DELETED
                list->tail = deletedNode->previous;
            }

            //DELETE
            list->deleteNode(deletedNode->data);
            deletedNode->data = NULL;
            deleteListNode(deletedNode);
            return deletionReturn;
        }
        tmp = tmp->next;
    }

    deletionReturn = EXIT_FAILURE;
    return deletionReturn;
}

// NEVER USED SO NEVER TESTED
int compare(const void * first,const void * second) {

	return ((Node*)first)->priority - ((Node*)second)->priority;
}