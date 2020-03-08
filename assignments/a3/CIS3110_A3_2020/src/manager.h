#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/**
 * Constants
 * **/

#define PAGESIZE  256
#define TABLE_ENTRIES  256
#define TLB_ENTRIES  16
#define FRAMESIZE  256
#define TOTAL_FRAMES 256
#define PHYSICAL_MEMSIZE  TOTAL_FRAMES * FRAMESIZE

/**
 * Data structures
 * **/

typedef struct PageAddress{
    int logicalAddress;
    int pageNumber;
    int offset;
} PageAddress;


/***
 * Functions
 * **/

// The top level method that will do the memory management
int memmanager(char* addresses);

// Page address utils
PageAddress* createPageAddress(int logicalAddress);
void deletePageAddress(void* pgAddr);
void printPageAddress(void* pgAddr);
int comparePageAddress(const void* pgAddr1, const void* pgAddr2);

int isPageAddress(PageAddress* pgAddr, int pageNumber);

// Helpers
PriorityQ* getPageAddressesFromFile(char* filePath);
void deleteQ(PriorityQ* aQ);