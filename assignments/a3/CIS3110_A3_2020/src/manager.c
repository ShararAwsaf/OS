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

     // Initialized to -1 to indicate a frame is not yet assigned to this page
    pgAddr->frameNumber = -1;

    return pgAddr;
}


void deletePageAddress(void* pgAddr){
    if(pgAddr != NULL)
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

    printf("LOGICAL ADDRESS: %d  |  PAGE INDEX: %d  |  PAGE OFFSET: %d  |  FRAME: %d\n", ((PageAddress*)pgAddr)->logicalAddress, ((PageAddress*)pgAddr)->pageNumber, ((PageAddress*)pgAddr)->offset, ((PageAddress*)pgAddr)->frameNumber);
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
    if(buffer == NULL)
        return;

    for(int i = 0; i < size; i++){

        printf("%d : %u\n",i, buffer[i]);
    }
    printf("\n");
}

char* fetchPhysicalAddress(int pageNumber){
    FILE* fp = fopen(PHYSICAL_MEMORY, "rb");

    if(fp == NULL){
        
        return NULL;
    }

    char* buffer = malloc( (sizeof(char)*FRAMESIZE) + 1);
    int wordSize = 1;
    
    // JUMP TO FRAME
    int memOffset = (pageNumber*FRAMESIZE);
    fseek(fp, memOffset, SEEK_SET);

    //int readSize = (PHYSICAL_MEMSIZE - ftell(fp)) > FRAMESIZE ? FRAMESIZE : PHYSICAL_MEMSIZE - ftell(fp);
    int readSize = FRAMESIZE;
    // GET FRAME
    fread(buffer, readSize, wordSize, fp);


    fclose(fp);

    return buffer;
}

Frame* createFrame(int frameNumber, int pageNumber){

    if(frameNumber < 0 || pageNumber < 0)
        return NULL;

    // FETCH MEMORY FROM BACKING STORE
    char* frameAddress = fetchPhysicalAddress(pageNumber);

    if(frameAddress == NULL)
        return NULL;

    Frame* newFrame = malloc(sizeof(Frame));

    newFrame->frameNumber = frameNumber;
    newFrame->frameAddress = frameAddress;

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

// Fetches a new block of memory from backing store to physical memory
// returns address to new frame
Frame* findFrame(Frame** memory, int* frameNumber, int pageNumber){ 

    if(memory == NULL){
        
        return NULL;
    }
    
    // The frame exists in page table
    if(*frameNumber >= 0){
        
        return memory[*frameNumber];
    }

    // Fetch the frame from backing memory.
    for(int i = 0; i < FRAMESIZE; i++){
        if(memory[i] == NULL){ 
            Frame* newFrame = createFrame(i, pageNumber);
            memory[i] = newFrame;
            *frameNumber = i;
            return newFrame;
        }
    }

    return NULL;
}

void printMemory(Frame** memory){
    for(int i = 0; i < FRAMESIZE; i++){
        printf("FRAME NUMBER : %d | ", i);
        if(memory[i] == NULL){
            printf("UNOCCUPIED");
        }
        else{
            printFrame(memory[i]);
        }
        printf("\n");
    }
}

void printBackingMemory(){
    FILE* fp = fopen(PHYSICAL_MEMORY, "rb");
    char buffer[10000];
    int i = 0;
    while(!feof(fp)){
        fread(buffer, 1, 1, fp);
        char val = buffer[0];
        printf("i:%x = %x\n", i, val);
        i += 1;
    }

    fclose(fp);
}

void deleteTLB(void* delItem){
    // A DUMMY METHOD THAT DOESNOT FREE MEMORY
    // THIS IS BECAUSE LATER THE MEMORY GETS FREED
}

void clearTable(void** table, int size, void (*deleteFunc)(void* delItem)){
    if(table == NULL)
        return;

    for(int i = 0; i < size; i++){
        if(table[i] != NULL)
            deleteFunc(table[i]);
    }
}

int memmanager(char* addresses){
    PriorityQ* pageAddresses = getPageAddressesFromFile(addresses);
    

    if(pageAddresses == NULL){
        return EXIT_FAILURE;
    }

    
    Frame* memory[FRAMESIZE];
    for(int i =0; i<FRAMESIZE; i++){
        // i = frame number
        memory[i] = NULL; // Initally no physical memory is allocated
    }

    int pgTable[PAGE_TABLE_SIZE];
    for(int i =0; i<PAGE_TABLE_SIZE; i++){
        // i = frame number
        pgTable[i] = -1; // Initally no frames exist (-1 indicates no frames exist)
    }

    int processed = 0;
    int tlbTableHits = 0;
    int pgTableHits = 0;
    int backstoreHits = 0;
    int totalAddresses = pageAddresses->count;
    PageAddress* processedAddresses[totalAddresses];
    for(int i =0; i<totalAddresses; i++){
        processedAddresses[i] = NULL; // Initally no addresses processed
    }

    PriorityQ* tlbTable = createQ(printPageAddress, deleteTLB, comparePageAddress);

    while (pageAddresses->count){

        // Get the addresses one by one
        PageAddress* pgAddr = dequeue_front(pageAddresses, copyPageAddress);
        int foundFrame = -1;
        
        // SEARCH IN TLB
        PageAddress* tlbSearchResult = searchQ(tlbTable, pgAddr);

        // TLB HIT
        if(tlbSearchResult != NULL){
            foundFrame = tlbSearchResult->frameNumber;
            pgAddr->frameNumber = foundFrame;
            
            tlbTableHits += 1;
        }

        // TLB MISS
        if(foundFrame < 0){
            // PAGE TABLE MISS : SOURCE = BACKING STORE
            if(pgTable[pgAddr->pageNumber] == -1){    
                findFrame(memory, &(pgAddr->frameNumber), pgAddr->pageNumber); // UPDATES PG TABLE
                pgTable[pgAddr->pageNumber] = pgAddr->frameNumber;
                foundFrame = pgAddr->frameNumber;

                backstoreHits += 1;
            }
            // PAGE TABLE HIT : SOURCE = PAGE TABLE
            else{
                pgAddr->frameNumber = pgTable[pgAddr->pageNumber];
                foundFrame = pgAddr->frameNumber;
                
                
                pgTableHits += 1;
            }

            // ADJUST TLB TO HOLD RECENT SEARCH oF PG TABLE
            if(tlbTable->count == TLB_TABLE_SIZE){
                pop(tlbTable);
            }
            enqueue(tlbTable, pgAddr);
        }

        

        Frame* pgFrame = NULL;
        pgFrame =  memory[foundFrame];
        
        char targetPhysicalAddress = pgFrame->frameAddress[pgAddr->offset];
        //printf("\nPROCESSED: %d  |  TARGET FRAME: %d  |  TARGET ADDRESS: %u\n", processed, pgAddr->frameNumber, targetPhysicalAddress);
        printf("Virtual address: %d Physical address: %d Value: %d\n", pgAddr->logicalAddress, (pgAddr->frameNumber*FRAMESIZE) + pgAddr->offset, targetPhysicalAddress);
        //printPageAddress(pgAddr);

        processedAddresses[processed] = pgAddr;
        processed += 1;
    }

    printf("Number of Translated Addresses = %d\n", processed);
    
    printf("Page Faults = %d\n", backstoreHits);
    printf("Page Fault Rate = %.3f\n", (float)backstoreHits/(float)processed);

    printf("TLB Hits = %d\n", tlbTableHits);
    printf("TLB Hit Rate = %.3f\n", (float)tlbTableHits/(float)processed);
    
    //printBackingMemory();

    
    //printf("PG TABLE HITS : %d/%d = %f %% \n", pgTableHits, processed, (float)pgTableHits/(float)processed);
    
    /*
        Fetch address from tlb :: (yet to be implemented)
    */

    /*
        Fetch address from page table :: 
    */
    
    /*
        Translate address :: (yet to be implemented)
    */

    
    // CLEANUP
    clearTable((void**)memory, FRAMESIZE, deleteFrame);
    clearTable((void**)processedAddresses, totalAddresses, deletePageAddress);
    deleteQ(tlbTable);
    deleteQ(pageAddresses);
    return EXIT_SUCCESS;
}

void* copyPageAddress(const void* pgAddr){
    if(pgAddr == NULL)
        return NULL;

    PageAddress* toBeCopied = (PageAddress*)pgAddr;
    PageAddress* newPgAddr = createPageAddress(toBeCopied->logicalAddress);

    newPgAddr->logicalAddress = toBeCopied->logicalAddress;
    newPgAddr->pageNumber = toBeCopied->pageNumber;
    newPgAddr->offset = toBeCopied->offset;
    newPgAddr->frameNumber = toBeCopied->frameNumber;

    return newPgAddr;
}

void* dequeue_front(PriorityQ* aQ, void* (*copyData)(const void* currentFront)){
    if(aQ == NULL)
        return NULL;

    void* qTop = peek(aQ);
    void* frontItem = copyData(qTop);

    pop(aQ);
    return frontItem;
}

void* searchQ(PriorityQ* aQ, void* searchItem){
    if(aQ == NULL || aQ->count == 0 || searchItem == NULL)
        return NULL;

    int i = 0;
    List aList = aQ->list;
    Node* tmp = aList.head;
    while(i < aQ->count && aList.compare(searchItem, tmp->data)!=0) {
        tmp = tmp->next;
        i++;
    }

    return tmp!=NULL ? tmp->data : NULL;
}
