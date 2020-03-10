#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <string.h>

/**
 * Constants
 * **/

#define PAGESIZE  256
#define FRAMESIZE  256

#define PAGE_TABLE_SIZE  256
#define TLB_TABLE_SIZE  16

#define TOTAL_FRAMES 256

#define PHYSICAL_MEMSIZE  TOTAL_FRAMES * FRAMESIZE
#define PHYSICAL_MEMORY "../BACKING_STORE.bin"

/**
 * Data structures
 * **/

// DATA STRUCTURE FOR PAGE TABLE
typedef struct PageAddress{
    int logicalAddress;
    int pageNumber;
    int offset;

    int frameNumber;
} PageAddress;

// DATA STRUCTURE FOR PHYSICAL MEMORY
typedef struct Frame{
    int frameNumber;
    char* frameAddress; // Fixed size : FRAME_SIZE
} Frame;

/***
 * Functions
 * **/

// The top level method that will do the memory management
int memmanager(char* addresses);

// Page address utils
PageAddress* createPageAddress(int logicalAddress);
void* copyPageAddress(const void* pgAddr);
void deletePageAddress(void* pgAddr);
void printPageAddress(void* pgAddr);
int comparePageAddress(const void* pgAddr1, const void* pgAddr2);
int isPageAddress(PageAddress* pgAddr, int pageNumber);

// Page Table utils
Frame* createFrame(int frameNumber);
void deleteFrame(void* frame);
void printFrame(void* frame);
int compareFrames(const void* frame1, const void* frame2);

// Helpers

// Priority Q
PriorityQ* getPageAddressesFromFile(char* filePath);
void deleteQ(PriorityQ* aQ);
void* dequeue_front(PriorityQ* aQ, void* (*copyData)(const void* currentFront));
void* searchQ(PriorityQ* aQ, void* searchItem);

char* fetchPhysicalAddress(int frameNumber);
void printPhysicalAddress(char* buffer, int size);
Frame* findFrame(Frame** memory, int* frameNumber);

void printMemory(Frame** memory);
void clearTable(void** table, int size, void (*deleteFunc)(void* delItem));
void deleteTLB(void* delItem);