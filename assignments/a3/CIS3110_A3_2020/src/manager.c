#include "manager.h"


PageAddress* createPageAddress(int logicalAddress){
    PageAddress* pgAddr = malloc(sizeof(PageAddress));

    // bit masks
    int bits_7_0 =  0x000000FF;
    int bits_15_8 = 0x0000FF00;
    int shift_amount = 8; // LAST8 BITS NEED TO BE REMOVED

    pgAddr->logicalAddress = logicalAddress;
    pgAddr->pageNumber = (logicalAddress & bits_15_8) >> shift_amount;
    pgAddr->offset = logicalAddress & bits_7_0;

    return pgAddr;
}


void deletePageAddress(void* pgAddr){
    free((PageAddress*)pgAddr);
}

int isPageAddress(PageAddress* pgAddr, int pageNumber){
    if(pgAddr == NULL){
        return 0;
    }
    return pgAddr->pageNumber == pageNumber;
}

void printPageAddress(void* pgAddr){
    if(pgAddr == NULL)
        return;

    printf("LOGICAL ADDRESS: %d  |  PAGE INDEX: %d  |  PAGE OFFSET: %d\n", ((PageAddress*)pgAddr)->logicalAddress, ((PageAddress*)pgAddr)->pageNumber, ((PageAddress*)pgAddr)->offset);
}

int comparePageAddress(const void* pgAddr1, const void* pgAddr2){

    if(pgAddr1 == NULL || pgAddr2 == NULL)
        return -1;

    return ((PageAddress*)pgAddr1)->pageNumber - ((PageAddress*)pgAddr2)->pageNumber;
}

PriorityQ* getPageAddressesFromFile(char* filePath){

    FILE* fp = fopen(filePath, "r");

    if(fp == NULL){
        
        return NULL;
    }

    PriorityQ* addressQ = createQ(printPageAddress, deletePageAddress, comparePageAddress);
    while(!feof(fp)){
        int* logicalAddress = malloc(sizeof(int));
        fscanf(fp, "%d\n", logicalAddress);
        int logicalAddressVal = *logicalAddress;
        PageAddress* pgAddr = createPageAddress(logicalAddressVal);
        enqueue( addressQ, pgAddr);
        free(logicalAddress);
    }
    fclose(fp);
    return addressQ;
}

void deleteQ(PriorityQ* aQ){
    while(aQ->count){
        pop(aQ);
    }
    free(aQ);
}

void printPhysicalAddress(char* buffer, int size){
    for(int i = 0; i < size; i++){

        printf("%d : %u\n",i, buffer[i]);
    }
    printf("\n");
}

char* fetchPhysicalAddress(int frameNumber, int offset){
    FILE* fp = fopen(PHYSICAL_MEMORY, "rb");

    if(fp == NULL){
        
        return NULL;
    }
    char* buffer = malloc(sizeof(FRAMESIZE));
    int word_size = 1;
    
    // JUMP TO FRAME -> OFFSET
    int memOffset = (frameNumber*FRAMESIZE) + offset;
    fseek(fp, memOffset, SEEK_SET);

    int readSize = (PHYSICAL_MEMSIZE - ftell(fp)) > FRAMESIZE ? FRAMESIZE : PHYSICAL_MEMSIZE - ftell(fp);
    // READ THE NEXT FRAME SIZE
    fread(buffer, readSize, word_size, fp);

    fclose(fp);

    return buffer;
}

Frame* createFrame(int frameNumber){

    FILE* fp = fopen(PHYSICAL_MEMORY, "rb");

    if(fp == NULL){
        
        return NULL;
    }

    if(frameNumber < 0)
        return NULL;
    Frame* newFrame = malloc(sizeof(Frame));

    newFrame->frameNumber = frameNumber;
    newFrame->frameAddress = fetchPhysicalAddress(frameNumber, 0);

    return newFrame;
}

void deleteFrame(void* frame){
    if(frame == NULL)
        return;
    
    free(((Frame*)frame)->frameAddress);
    free((Frame*)frame);
}

void printFrame(void* frame){
    if(frame == NULL)
        return;

    printf("FRAME INDEX: %d  |  FRAME ADDRESS:\n",((Frame*)frame)->frameNumber);
    printPhysicalAddress(((Frame*)frame)->frameAddress, FRAMESIZE);
}

int compareFrames(const void* frame1, const void* frame2){
    if(frame1 == NULL || frame2 == NULL)
        return -1;

    return ((Frame*)frame1)->frameNumber - ((Frame*)frame2)->frameNumber;
}

int memmanager(char* addresses){
    /*
        Fetch address from tlb :: (yet to be implemented)
    */

   /*
        Fetch address from page table :: (yet to be implemented)
    */

   /*
        Translate address :: (yet to be implemented)
    */

   /*
        Fetch address from tlb :: (yet to be implemented)
    */
   PriorityQ* pageAddresses = getPageAddressesFromFile(addresses);
   
   if(pageAddresses == NULL){
       return EXIT_FAILURE;
   }

   deleteQ(pageAddresses);

   return EXIT_SUCCESS;
}
