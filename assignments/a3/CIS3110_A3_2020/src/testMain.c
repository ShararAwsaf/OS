#include <stdio.h>
#include <stdlib.h>
#include "manager.h"

// DUMMY SUNCTIONS FOR TESTING
void printInt(void* num){
    if(num != NULL)
        printf("NUMBER : %d\n", *((int*)num));
}

void deleteInt(void* num){
    if(num!=NULL){
        free((int*)num);
    }
}

int compareInt(const void* n1, const void* n2){
    if(n1 != NULL && n2 != NULL)
        return *((int*)n1) - *((int*)n2);
    return -1;
}

void testPageAddressCreate(){
    
    PageAddress* pgAddr;

    int count = 7;
    int addresses[] = {1, 256, 32768, 32769, 128, 65534, 33153};

    while(count){
        count--;
        int logicalAddress = addresses[count];

        printf("SPLITTING ADDRESS: %d\n", logicalAddress);

        pgAddr = createPageAddress(logicalAddress);
        
        printPageAddress(pgAddr);

        deletePageAddress(pgAddr);
    }
}

void testFileParser(){
    //char* fileName = "../addresses.txt";
    char* fileName = "../testAddresses.txt";
    //char* fileName = "../reviewQ1.txt";

    printf("PARSING: %s\n", fileName);
    PriorityQ* addressQ = getPageAddressesFromFile(fileName);
    printQ(addressQ);
    deleteQ(addressQ);
}

void testFetchPhysicalAddress(){
    
    int frameNumber = 255;
    char* physicalAddr = fetchPhysicalAddress(frameNumber);
    
    printPhysicalAddress(physicalAddr, FRAMESIZE);
    free(physicalAddr);

}

void testFindFrame(){
    int logicalAddress = 16916;
    PageAddress* pgAddr = createPageAddress(logicalAddress);
    printPageAddress(pgAddr);
    
    Frame* memory[FRAMESIZE];
    for(int i =0; i < FRAMESIZE; i++){
        // i = frame number
        memory[i] = NULL; // Initally no physical memory is allocated
    }

    Frame* frameFetched = findFrame(memory, &(pgAddr->frameNumber));
    
    // printf("::MEMORY::\n");
    // printMemory(memory);
    // printf("::MEMORY::\n");
    

    printf("::FRAME::\n");
    printFrame(frameFetched);
    printf("::FRAME::\n");

    
    printPageAddress(pgAddr);

    clearTable((void**)memory, PAGE_TABLE_SIZE, deleteFrame);
    deletePageAddress(pgAddr);
}


void testSearchQ(){
    PriorityQ* aQ = createQ(printInt, deleteInt, compareInt);
    int* i1 = malloc(sizeof(int));
    int* i2 = malloc(sizeof(int));
    int* i3 = malloc(sizeof(int));
    int* i4 = malloc(sizeof(int));

    *i1 = 4;
    *i2 = 1;
    *i3 = 3;
    *i4 = 1;
    enqueue(aQ, i1);
    enqueue(aQ, i2);
    enqueue(aQ, i3);
    enqueue(aQ, i4);
    
    int sA = 0;
    int sB = 1;

    int* searchResultA = searchQ(aQ, &sA);

    if(searchResultA == NULL){
        printf("NOT FOUND\n");
    }
    else{
        printInt(searchResultA);
    }

    int* searchResultB = searchQ(aQ, &sB);

    if(searchResultB == NULL){
        printf("NOT FOUND\n");
    }
    else{
        printInt(searchResultB);
    }

    if(searchResultB == i2){
        printf("FOUND THE FIRST OCCURRANCE\n");
    }

    PriorityQ* emptyQ = createQ(printInt, deleteInt, compareInt);

    int* searchResultC = searchQ(emptyQ, &sB);

    if(searchResultC == NULL){
        printf("NOT FOUND\n");
    }
    else{
        printInt(searchResultB);
    }

    deleteQ(aQ);
    deleteQ(emptyQ);
}

int main(void){
    printf("\n\nStarted Testing Manager\n\n");

    //testPageAddressCreate();
    //testFileParser();
    //testFetchPhysicalAddress();
    //testFindFrame();
    testSearchQ();

    printf("\n\nFinished Testing Manager\n\n");
}