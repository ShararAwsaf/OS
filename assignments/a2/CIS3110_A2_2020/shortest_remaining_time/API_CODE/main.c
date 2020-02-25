#include "LinkedListAPI.h"

void testListInit();
void testNodeInit();
void testGetFromFront();
void testGetFromBack();
void testListInsertFront();
void testDeleteCompleteListInsertFront();
void testListInsertBack();
void testDeleteCompleteListInsertBack();
void testDeleteCompleteListInsertMixed();
void testDeleteCompleteListInsertSorted();
void testDeleteCompleteListOneAtATime();

int main(void){

    printf("STARTED TESTING LINKED LIST\n");
    //testListInit();
    //testNodeInit();
    //testGetFromFront();
    //testGetFromBack();
    //testListInsertFront();
    // testDeleteCompleteListInsertFront();
    // testListInsertBack();
    // testDeleteCompleteListInsertBack();
    // testDeleteCompleteListInsertMixed();
    // testDeleteCompleteListInsertSorted();
    testDeleteCompleteListOneAtATime();

    return 0;
}

void printInt(void* data){
    if (data != NULL)
        printf("ITEM : %d\n", *((int*)data));
    else
        printf("NO ITEM TO PRINT!\n");
}

void deleteInt(void* data){
    if(data != NULL)
        free(data);
}

int compareInt(const void* data1, const void* data2){
    return *((int*)data1) - *((int*)data2);
}

void testListInit(){
    printf("INITIALIZING AN EMPTY LIST\n");
    List testList = initializeList(printInt, deleteInt, compareInt);

    if(testList.head != NULL){
        printf("LIST HAS ELEMENTS\n");
    }

}

void testNodeInit(){
    int* testInt = malloc(sizeof(int));
    *testInt = 7;
    Node* testNode = initializeNode(testInt);

    printf("TESTING VALID NODE : ");
    printInt(testNode->data);

    free(testNode->data);
    free(testNode->previous);
    free(testNode->next);
    free(testNode);

    int* invalidInt = NULL;
    Node* invalidTestNode = initializeNode(invalidInt);

    printf("TESTING INVALID NODE : ");
    if(invalidTestNode != NULL){
        printInt(invalidTestNode->data);

        free(invalidTestNode->data);
        free(invalidTestNode->previous);
        free(invalidTestNode->next);
        free(invalidTestNode);
    }

}


void testGetFromFront(){
    int* testInt = malloc(sizeof(int));
    *testInt = 7;
    Node* testNode = initializeNode(testInt);
    
    List testList = initializeList(printInt, deleteInt, compareInt);
    testList.head = testNode;

    printf("TESTING HEAD NODE : ");
    printInt(getFromFront(&testList));

    free(testNode->data);
    free(testNode->previous);
    free(testNode->next);
    free(testNode);

    int* invalidInt = NULL;
    Node* invalidTestNode = initializeNode(invalidInt);
    testList.head = invalidTestNode;

    printf("TESTING INVALID NODE : ");
    if(invalidTestNode != NULL){
        printInt(getFromFront(&testList));

        free(invalidTestNode->data);
        free(invalidTestNode->previous);
        free(invalidTestNode->next);
        free(invalidTestNode);
    }

}

void testGetFromBack(){
    int* testInt = malloc(sizeof(int));
    *testInt = 7;
    Node* testNode = initializeNode(testInt);
    
    List testList = initializeList(printInt, deleteInt, compareInt);
    testList.tail = testNode;

    printf("TESTING TAIL NODE : ");
    printInt(getFromBack(&testList));

    free(testNode->data);
    free(testNode->previous);
    free(testNode->next);
    free(testNode);

    int* invalidInt = NULL;
    Node* invalidTestNode = initializeNode(invalidInt);
    testList.tail = invalidTestNode;

    printf("TESTING INVALID NODE : ");
    if(invalidTestNode != NULL){
        printInt(getFromBack(&testList));

        free(invalidTestNode->data);
        free(invalidTestNode->previous);
        free(invalidTestNode->next);
        free(invalidTestNode);
    }

}

void testListInsertFront(){
    int* int1 = malloc(sizeof(int));
    int* int2 = malloc(sizeof(int));
    int* int3 = malloc(sizeof(int));

    
    *int1 = 2;
    *int2 = 3;
    *int3 = 1;

    List testList = initializeList(printInt, deleteInt, compareInt);

    insertFront(&testList, int1);
    printf("FORWARD PRINT OF ITEMS (1/3) expected : 2\n");
    printForward(&testList);
    printf("BACKWARD PRINT OF ITEMS (1/3) expected: 2\n");
    printBackwards(&testList);

    
    insertFront(&testList, int2);
    printf("FORWARD PRINT OF ITEMS (2/3) expected : 3 2\n");
    printForward(&testList);
    printf("BACKWARD PRINT OF ITEMS 2 3\n");
    printBackwards(&testList);

    
    
    insertFront(&testList, int3);
    printf("FORWARD PRINT OF ITEMS (3/3) 1 3 2\n");
    printForward(&testList);
    printf("BACKWARD PRINT OF ITEMS (3/3) 2 3 1\n");
    printBackwards(&testList);

    
    deleteInt(int1);
    deleteInt(int2);
    deleteInt(int3);


    Node* tmp = testList.head;

    while(tmp!=NULL){
        Node* deletedNode = tmp;
        tmp = tmp->next;
        deleteListNode(deletedNode);
        
    }

}

void testListInsertBack(){
    int* int1 = malloc(sizeof(int));
    int* int2 = malloc(sizeof(int));
    int* int3 = malloc(sizeof(int));

    
    *int1 = 2;
    *int2 = 3;
    *int3 = 1;

    List testList = initializeList(printInt, deleteInt, compareInt);

    insertBack(&testList, int1);
    printf("FORWARD PRINT OF ITEMS (1/3) expected : 2\n");
    printForward(&testList);
    printf("BACKWARD PRINT OF ITEMS (1/3) expected: 2\n");
    printBackwards(&testList);

    
    insertBack(&testList, int2);
    printf("FORWARD PRINT OF ITEMS (2/3) expected : 2 3\n");
    printForward(&testList);
    printf("BACKWARD PRINT OF ITEMS 3 2\n");
    printBackwards(&testList);

    
    
    insertBack(&testList, int3);
    printf("FORWARD PRINT OF ITEMS (3/3) 2 3 1\n");
    printForward(&testList);
    printf("BACKWARD PRINT OF ITEMS (3/3) 1 3 2\n");
    printBackwards(&testList);

    
    deleteInt(int1);
    deleteInt(int2);
    deleteInt(int3);


    Node* tmp = testList.head;

    while(tmp!=NULL){
        Node* deletedNode = tmp;
        tmp = tmp->next;
        deleteListNode(deletedNode);
        
    }

}


void testDeleteCompleteListInsertFront(){
    int* int1 = malloc(sizeof(int));
    *int1 = 2;

    List testList1 = initializeList(printInt, deleteInt, compareInt);

    insertFront(&testList1, int1);
    printf("FORWARD PRINT OF ITEMS (1/3) expected : 2\n");
    printForward(&testList1);
    printf("BACKWARD PRINT OF ITEMS (1/3) expected: 2\n");
    printBackwards(&testList1);
    deleteList(&testList1);

    int1 = malloc(sizeof(int));
    int* int2 = malloc(sizeof(int));
    *int1 = 2;
    *int2 = 3;

    List testList2 = initializeList(printInt, deleteInt, compareInt);

    insertFront(&testList2, int1);
    insertFront(&testList2, int2);
    printf("FORWARD PRINT OF ITEMS (2/3) expected : 3 2\n");
    printForward(&testList2);
    printf("BACKWARD PRINT OF ITEMS 2 3\n");
    printBackwards(&testList2);
    deleteList(&testList2);
    
    int1 = malloc(sizeof(int));
    int2 = malloc(sizeof(int));
    int* int3 = malloc(sizeof(int));
    
    *int1 = 2;
    *int2 = 3;
    *int3 = 1;

    List testList3 = initializeList(printInt, deleteInt, compareInt);

    insertFront(&testList3, int1);
    insertFront(&testList3, int2);
    insertFront(&testList3, int3);
    printf("FORWARD PRINT OF ITEMS (3/3) 1 3 2\n");
    printForward(&testList3);
    printf("BACKWARD PRINT OF ITEMS (3/3) 2 3 1\n");
    printBackwards(&testList3);
    deleteList(&testList3);

    printf("POST DELETETION:\n");
    printf("LIST 1:  expected : \n");
    printForward(&testList1);
    printBackwards(&testList1);


    printf("LIST 2: expected : \n");
    printForward(&testList2);
    printBackwards(&testList2);

    printf("LIST 3: expected: \n");
    printForward(&testList3);
    printBackwards(&testList3);
}



void testDeleteCompleteListInsertBack(){
    int* int1 = malloc(sizeof(int));
    *int1 = 2;

    List testList1 = initializeList(printInt, deleteInt, compareInt);

    insertBack(&testList1, int1);
    printf("FORWARD PRINT OF ITEMS (1/3) expected : 2\n");
    printForward(&testList1);
    printf("BACKWARD PRINT OF ITEMS (1/3) expected: 2\n");
    printBackwards(&testList1);
    deleteList(&testList1);

    int1 = malloc(sizeof(int));
    int* int2 = malloc(sizeof(int));
    *int1 = 2;
    *int2 = 3;

    List testList2 = initializeList(printInt, deleteInt, compareInt);

    insertBack(&testList2, int1);
    insertBack(&testList2, int2);
    printf("FORWARD PRINT OF ITEMS (2/3) expected : 2 3\n");
    printForward(&testList2);
    printf("BACKWARD PRINT OF ITEMS 3 2\n");
    printBackwards(&testList2);
    deleteList(&testList2);
    
    int1 = malloc(sizeof(int));
    int2 = malloc(sizeof(int));
    int* int3 = malloc(sizeof(int));
    
    *int1 = 2;
    *int2 = 3;
    *int3 = 1;

    List testList3 = initializeList(printInt, deleteInt, compareInt);

    insertBack(&testList3, int1);
    insertBack(&testList3, int2);
    insertBack(&testList3, int3);
    printf("FORWARD PRINT OF ITEMS (3/3) 2 3 1\n");
    printForward(&testList3);
    printf("BACKWARD PRINT OF ITEMS (3/3) 1 3 2\n");
    printBackwards(&testList3);
    deleteList(&testList3);

    printf("POST DELETETION:\n");
    printf("LIST 1:  expected : \n");
    printForward(&testList1);
    printBackwards(&testList1);


    printf("LIST 2: expected : \n");
    printForward(&testList2);
    printBackwards(&testList2);

    printf("LIST 3: expected: \n");
    printForward(&testList3);
    printBackwards(&testList3);
}

void testDeleteCompleteListInsertMixed(){
    int* int1 = malloc(sizeof(int));
    *int1 = 2;

    List testList1 = initializeList(printInt, deleteInt, compareInt);

    insertBack(&testList1, int1);
    printf("FORWARD PRINT OF ITEMS (1/4) expected : 2\n");
    printForward(&testList1);
    printf("BACKWARD PRINT OF ITEMS (1/4) expected: 2\n");
    printBackwards(&testList1);
    deleteList(&testList1);

    int1 = malloc(sizeof(int));
    int* int2 = malloc(sizeof(int));
    *int1 = 2;
    *int2 = 3;

    List testList2 = initializeList(printInt, deleteInt, compareInt);

    insertFront(&testList2, int1);
    insertBack(&testList2, int2);
    printf("FORWARD PRINT OF ITEMS (2/4) expected : 2 3\n");
    printForward(&testList2);
    printf("BACKWARD PRINT OF ITEMS (2/4) expected : 3 2\n");
    printBackwards(&testList2);
    deleteList(&testList2);
    
    int1 = malloc(sizeof(int));
    int2 = malloc(sizeof(int));
    int* int3 = malloc(sizeof(int));
    
    *int1 = 2;
    *int2 = 3;
    *int3 = 1;

    List testList3 = initializeList(printInt, deleteInt, compareInt);

    insertBack(&testList3, int1);
    insertFront(&testList3, int2);
    insertBack(&testList3, int3);
    printf("FORWARD PRINT OF ITEMS (3/4) 3 2 1\n");
    printForward(&testList3);
    printf("BACKWARD PRINT OF ITEMS (3/4) 1 2 3\n");
    printBackwards(&testList3);
    deleteList(&testList3);

    int1 = malloc(sizeof(int));
    int2 = malloc(sizeof(int));
    int3 = malloc(sizeof(int));
    int* int4 = malloc(sizeof(int));

    *int1 = 2;
    *int2 = 3;
    *int3 = 1;
    *int4 = 4;

    List testList4 = initializeList(printInt, deleteInt, compareInt);

    insertBack(&testList4, int1);
    insertFront(&testList4, int2);
    insertBack(&testList4, int3);
    insertFront(&testList4, int4);
    printf("FORWARD PRINT OF ITEMS (4/4) expected : 4 3 2 1\n");
    printForward(&testList4);
    printf("BACKWARD PRINT OF ITEMS (4/4) 1 2 3 4\n");
    printBackwards(&testList4);
    deleteList(&testList4);


    printf("POST DELETETION:\n");
    printf("LIST 1:  expected : \n");
    printForward(&testList1);
    printBackwards(&testList1);


    printf("LIST 2: expected : \n");
    printForward(&testList2);
    printBackwards(&testList2);

    printf("LIST 3: expected: \n");
    printForward(&testList3);
    printBackwards(&testList3);

    printf("LIST 4: expected: \n");
    printForward(&testList4);
    printBackwards(&testList4);
}

void testDeleteCompleteListInsertSorted(){
    int* int1 = malloc(sizeof(int));
    *int1 = 2;

    List testList1 = initializeList(printInt, deleteInt, compareInt);

    insertSorted(&testList1, int1, *int1);
    printf("FORWARD PRINT OF ITEMS (1/5) expected : 2\n");
    printForward(&testList1);
    printf("BACKWARD PRINT OF ITEMS (1/5) expected: 2\n");
    printBackwards(&testList1);
    deleteList(&testList1);

    int1 = malloc(sizeof(int));
    int* int2 = malloc(sizeof(int));
    *int1 = 2;
    *int2 = 3;

    List testList2 = initializeList(printInt, deleteInt, compareInt);

    insertSorted(&testList2, int1, *int1);
    insertSorted(&testList2, int2, *int2);
    printf("FORWARD PRINT OF ITEMS (2/5) expected : 2 3\n");
    printForward(&testList2);
    printf("BACKWARD PRINT OF ITEMS (2/5) expected : 3 2\n");
    printBackwards(&testList2);
    deleteList(&testList2);
    
    int1 = malloc(sizeof(int));
    int2 = malloc(sizeof(int));
    int* int3 = malloc(sizeof(int));
    
    *int1 = 2;
    *int2 = 3;
    *int3 = 1;

    List testList3 = initializeList(printInt, deleteInt, compareInt);

    insertSorted(&testList3, int1, *int1);
    insertSorted(&testList3, int2, *int2);
    insertSorted(&testList3, int3, *int3);
    printf("FORWARD PRINT OF ITEMS (3/5) 1 2 3\n");
    printForward(&testList3);
    printf("BACKWARD PRINT OF ITEMS (3/5) 3 2 1\n");
    printBackwards(&testList3);
    deleteList(&testList3);

    int1 = malloc(sizeof(int));
    int2 = malloc(sizeof(int));
    int3 = malloc(sizeof(int));
    int* int4 = malloc(sizeof(int));

    *int1 = 2;
    *int2 = 3;
    *int3 = 1;
    *int4 = 4;

    List testList4 = initializeList(printInt, deleteInt, compareInt);

    insertSorted(&testList4, int1, *int1);
    insertSorted(&testList4, int2, *int2);
    insertSorted(&testList4, int3, *int3);
    insertSorted(&testList4, int4, *int4);
    printf("FORWARD PRINT OF ITEMS (4/5) expected : 1 2 3 4\n");
    printForward(&testList4);
    printf("BACKWARD PRINT OF ITEMS (4/5) 4 3 2 1\n");
    printBackwards(&testList4);
    deleteList(&testList4);

    int1 = malloc(sizeof(int));
    int2 = malloc(sizeof(int));
    int3 = malloc(sizeof(int));
    int4 = malloc(sizeof(int));
    int* int5 = malloc(sizeof(int));
    int* int6 = malloc(sizeof(int));
    int* int7 = malloc(sizeof(int));

    *int1 = 2;
    *int2 = 0;
    *int3 = 10;
    *int4 = 5;
    *int5 = 4;
    *int6 = 1;
    *int7 = 0;

    List testList5 = initializeList(printInt, deleteInt, compareInt);

    insertSorted(&testList5, int1, *int1);
    insertSorted(&testList5, int2, *int2);
    insertSorted(&testList5, int3, *int3);
    insertSorted(&testList5, int4, *int4);
    insertSorted(&testList5, int5, *int5);
    insertSorted(&testList5, int6, *int6);
    insertSorted(&testList5, int7, *int7);

    printf("FORWARD PRINT OF ITEMS (4/5) expected : 0 0 1 2 4 5 10\n");
    printForward(&testList5);
    printf("BACKWARD PRINT OF ITEMS (4/5) 10 5 4 2 1 0 0\n");
    printBackwards(&testList5);
    deleteList(&testList5);



    printf("POST DELETETION:\n");
    printf("LIST 1:  expected : \n");
    printForward(&testList1);
    printBackwards(&testList1);


    printf("LIST 2: expected : \n");
    printForward(&testList2);
    printBackwards(&testList2);

    printf("LIST 3: expected: \n");
    printForward(&testList3);
    printBackwards(&testList3);

    printf("LIST 4: expected: \n");
    printForward(&testList4);
    printBackwards(&testList4);

    printf("LIST 5: expected: \n");
    printForward(&testList5);
    printBackwards(&testList5);
}

void testDeleteCompleteListOneAtATime(){
    int* int1 = malloc(sizeof(int));
    *int1 = 2;

    List testList1 = initializeList(printInt, deleteInt, compareInt);

    insertSorted(&testList1, int1, *int1);

    printf("FORWARD PRINT OF ITEMS (1/5) expected : 2\n");
    printForward(&testList1);
    printf("BACKWARD PRINT OF ITEMS (1/5) expected: 2\n");
    printBackwards(&testList1);
    
    deleteNodeFromList(&testList1, int1);

    int1 = malloc(sizeof(int));
    int* int2 = malloc(sizeof(int));
    *int1 = 2;
    *int2 = 3;

    List testList2 = initializeList(printInt, deleteInt, compareInt);

    insertSorted(&testList2, int1, *int1);
    insertSorted(&testList2, int2, *int2);

    printf("FORWARD PRINT OF ITEMS (2/5) expected : 2 3\n");
    printForward(&testList2);
    printf("BACKWARD PRINT OF ITEMS (2/5) expected : 3 2\n");
    printBackwards(&testList2);

    deleteNodeFromList(&testList2, int1);
    deleteNodeFromList(&testList2, int2);
    
    int1 = malloc(sizeof(int));
    int2 = malloc(sizeof(int));
    int* int3 = malloc(sizeof(int));
    
    *int1 = 2;
    *int2 = 3;
    *int3 = 1;

    List testList3 = initializeList(printInt, deleteInt, compareInt);

    insertSorted(&testList3, int1, *int1);
    insertSorted(&testList3, int2, *int2);
    insertSorted(&testList3, int3, *int3);

    printf("FORWARD PRINT OF ITEMS (3/5) 1 2 3\n");
    printForward(&testList3);
    printf("BACKWARD PRINT OF ITEMS (3/5) 3 2 1\n");
    printBackwards(&testList3);

    deleteNodeFromList(&testList3, int1);
    deleteNodeFromList(&testList3, int2);
    deleteNodeFromList(&testList3, int3);

    int1 = malloc(sizeof(int));
    int2 = malloc(sizeof(int));
    int3 = malloc(sizeof(int));
    int* int4 = malloc(sizeof(int));

    *int1 = 2;
    *int2 = 3;
    *int3 = 1;
    *int4 = 4;

    List testList4 = initializeList(printInt, deleteInt, compareInt);

    insertSorted(&testList4, int1, *int1);
    insertSorted(&testList4, int2, *int2);
    insertSorted(&testList4, int3, *int3);
    insertSorted(&testList4, int4, *int4);
    
    printf("FORWARD PRINT OF ITEMS (4/5) expected : 1 2 3 4\n");
    printForward(&testList4);
    printf("BACKWARD PRINT OF ITEMS (4/5) 4 3 2 1\n");
    printBackwards(&testList4);

    deleteNodeFromList(&testList4, int1);
    deleteNodeFromList(&testList4, int2);
    deleteNodeFromList(&testList4, int3);
    deleteNodeFromList(&testList4, int4);

    int1 = malloc(sizeof(int));
    int2 = malloc(sizeof(int));
    int3 = malloc(sizeof(int));
    int4 = malloc(sizeof(int));
    int* int5 = malloc(sizeof(int));
    int* int6 = malloc(sizeof(int));
    int* int7 = malloc(sizeof(int));

    *int1 = 2;
    *int2 = 0;
    *int3 = 10;
    *int4 = 5;
    *int5 = 4;
    *int6 = 1;
    *int7 = 0;

    List testList5 = initializeList(printInt, deleteInt, compareInt);

    insertSorted(&testList5, int1, *int1);
    insertSorted(&testList5, int2, *int2);
    insertSorted(&testList5, int3, *int3);
    insertSorted(&testList5, int4, *int4);
    insertSorted(&testList5, int5, *int5);
    insertSorted(&testList5, int6, *int6);
    insertSorted(&testList5, int7, *int7);

    printf("FORWARD PRINT OF ITEMS (4/5) expected : 0 0 1 2 4 5 10\n");
    printForward(&testList5);
    printf("BACKWARD PRINT OF ITEMS (4/5) 10 5 4 2 1 0 0\n");
    printBackwards(&testList5);

    deleteNodeFromList(&testList5, int1);
    deleteNodeFromList(&testList5, int2);
    deleteNodeFromList(&testList5, int3);
    deleteNodeFromList(&testList5, int4);
    deleteNodeFromList(&testList5, int5);
    deleteNodeFromList(&testList5, int6);
    deleteNodeFromList(&testList5, int7);


    printf("POST DELETETION:\n");
    printf("LIST 1:  expected : \n");
    printForward(&testList1);
    printBackwards(&testList1);


    printf("LIST 2: expected : \n");
    printForward(&testList2);
    printBackwards(&testList2);

    printf("LIST 3: expected: \n");
    printForward(&testList3);
    printBackwards(&testList3);

    printf("LIST 4: expected: \n");
    printForward(&testList4);
    printBackwards(&testList4);

    printf("LIST 5: expected: \n");
    printForward(&testList5);
    printBackwards(&testList5);
}



// scp: scp LinkedListAPI.c LinkedListAPI.h queue.c queue.h makefile main.c oscreader@192.168.56.03:OS-ASSIGNMENTS/A2/api_code/
// valgrind: valgrind --leak-check=full ./LinkedListTest