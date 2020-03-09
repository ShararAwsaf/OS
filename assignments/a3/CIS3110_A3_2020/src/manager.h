#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

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

typedef struct PageAddress{
    int logicalAddress;
    int pageNumber;
    int offset;
} PageAddress;

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
PriorityQ* getPageAddressesFromFile(char* filePath);
void deleteQ(PriorityQ* aQ);
char* fetchPhysicalAddress(int frameNumber, int offset);
void printPhysicalAddress(char* buffer, int size);