#include <stdio.h>
#include <stdlib.h>
#include "manager.h"

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

void testCalculatePhysicalAddress(){
    int logicalAddress = 47709;
    PageAddress* pgAddr = createPageAddress(logicalAddress);
    printPageAddress(pgAddr);


    char* physicalAddr = fetchPhysicalAddress(pgAddr);
    
    printPhysicalAddress(physicalAddr, FRAMESIZE);
    free(physicalAddr);

    deletePageAddress(pgAddr);
}

int main(void){
    printf("\n\nStarted Testing Manager\n\n");

    //testPageAddressCreate();
    //testFileParser();
    testCalculatePhysicalAddress();

    printf("\n\nFinished Testing Manager\n\n");
}