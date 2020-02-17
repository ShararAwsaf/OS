/*
dispatcher.c

Student Name : ....
Student ID # : ....

Dispatch Algorithm : ....
*/

#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include "queue.h"
#include "LinkedListAPI.h"


#define MAX_LINE_LENGTH 100
#define TIME_STEP 1
#define DEBUG 0
#define DEBUG_COMPACT 0
/*
Any required standard libraries and your header files here
*/

/**
 * The process control block to be used to store states of process
*/

typedef struct PCB{
    // GIVEN
    int pid; // process id
    int initTime; // when the process first reached the system
    int executionTime; // the total execution time of process
    PriorityQ* exchangeTimes; // cycles after which the task set to blocked
    int totalExchanges; // total number of exchanges :: count of exchangeTimes

    // COMPUTED
    int nextArrivalTime; // when the next instance of the process will arrive
    
    int remainingTime; // how much of execution time left to be completed
    int currentCycleTime; // how long can the current process function before Exchange occurs
    int isBlockedAfterCurrentCycle;

    int totalRunningTime; // total running time of the current process

    int blockStart; // the start of exchange block
    int totalBlockTime; // total time the task stayed blocked. Incremented by += currentTime - blockStart
    
    int readyStart; // the start of process in ready list
    int totalReadyTime; // total time the task stayed in ready. Incremented by += currentTime - readyStart

}PCB;

// PCB QUEUE
PCB* createPCB(int pid, int initTime, int executionTime, PriorityQ* exchangeTimes, int totalExchanges);
void printPCB(void* aPCB);
void deletePCB(void* aPCB);
int comparePCB(const void* PCB1, const void* PCB2);
int compareConstant(const void* PCB1, const void* PCB2);

/*
Linked List Functions
*/
// Exchange Time list
void printExchange(void* exTime);
void deleteExchange(void* exTime);
int compareExchange(const void* exTime1, const void* exTime2);


/**
 * 
 * QUEUE HELPER METHOD
 */

int* popExchange(PriorityQ* aPriorityQ){
    if(aPriorityQ == NULL || aPriorityQ->count == 0)
        return NULL;
    
    int* firstExchange = malloc(sizeof(int));
    *firstExchange = *((int*)peek(aPriorityQ));
    pop(aPriorityQ);

    return firstExchange;
}


PCB* copyPCB(PCB* aPCB){
    if(aPCB == NULL)
        return NULL;
    
    PriorityQ* newPCBExchangeTimes = createQ(&printExchange, &deleteExchange, &compareConstant);
    int newPCBTotalExchanges = aPCB->totalExchanges;
    while(aPCB->exchangeTimes->count > 0){
        enqueue(newPCBExchangeTimes, popExchange(aPCB->exchangeTimes));
    }
    PCB* newPCB = malloc(sizeof(PCB));

    newPCB->pid = aPCB->pid;
    newPCB->initTime = aPCB->initTime;
    newPCB->executionTime = aPCB->executionTime;
    newPCB->totalExchanges = newPCBTotalExchanges;
    newPCB->exchangeTimes = newPCBExchangeTimes;

    newPCB->nextArrivalTime = aPCB->nextArrivalTime;
    newPCB->remainingTime = aPCB->remainingTime;
    newPCB->currentCycleTime = aPCB->currentCycleTime;
    newPCB->isBlockedAfterCurrentCycle = aPCB->isBlockedAfterCurrentCycle;
    

    newPCB->totalRunningTime = aPCB->totalRunningTime;
    
    newPCB->blockStart = aPCB->blockStart;
    newPCB->totalBlockTime = aPCB->totalBlockTime;

    newPCB->readyStart = aPCB->readyStart;
    newPCB->totalReadyTime = aPCB->totalReadyTime;

    return newPCB;
}


PCB* popPCB(PriorityQ* aPriorityQ){
    
    if(aPriorityQ == NULL || aPriorityQ->count == 0)
        return NULL;
    
    PCB* firstPCB = (PCB*)peek(aPriorityQ);
    

    PCB* newPCB = copyPCB(firstPCB);
    
    pop(aPriorityQ);

    return newPCB;
}

void deleteQ(PriorityQ* aPriorityQ){
    deleteList(&(aPriorityQ->list));
    free(aPriorityQ);
}


void printExchange(void* exTime){
    printf("EXCHANGE : %d\n", *((int*)exTime));
}

void deleteExchange(void* exTime){
    free((int*)exTime);
}

int compareExchange(const void* exTime1, const void* exTime2){
    return *((int*)exTime1) - *((int*)exTime2);
}



PCB* createPCB(int pid, int initTime, int executionTime, PriorityQ* exchangeTimes, int totalExchanges){
    
    PCB* aPCB = malloc(sizeof(PCB));

    aPCB->pid = pid;
    aPCB->initTime = initTime;
    aPCB->executionTime = executionTime;
    aPCB->exchangeTimes = exchangeTimes;
    
    aPCB->nextArrivalTime = initTime;
    aPCB->remainingTime = executionTime;

    aPCB->totalRunningTime = 0;
    if(totalExchanges == 0) {
        aPCB->currentCycleTime =  executionTime;
        aPCB->isBlockedAfterCurrentCycle = 0;
    }
    else {
        int* cycleTime = popExchange(aPCB->exchangeTimes) ;
        aPCB->currentCycleTime = *cycleTime - aPCB->totalRunningTime;
        free(cycleTime);

        totalExchanges -= 1;
        aPCB->isBlockedAfterCurrentCycle = 1;
    }

    aPCB->totalExchanges = totalExchanges;
    
    
    aPCB->blockStart = 0;
    aPCB->totalBlockTime = 0;

    aPCB->readyStart = 0;
    aPCB->totalReadyTime = 0;

    return aPCB;
}

void printPCB(void* aPCB){

    printf("\n");

    printf("PID : %d\n", ((PCB*)aPCB)->pid);
    printf("INIT @: %d\n", ((PCB*)aPCB)->initTime);
    
    printf("EXEC TIME : %d\n", ((PCB*)aPCB)->executionTime);
    printf("CYCLE TIME: %d\n", ((PCB*)aPCB)->currentCycleTime);
    printf("TOTAL EXCHANGES: %d\n", ((PCB*)aPCB)->totalExchanges);
    printQ(((PCB*)aPCB)->exchangeTimes);
    printf("BLOCKED AFTER CYCLE: %d\n", ((PCB*)aPCB)->isBlockedAfterCurrentCycle);
    printf("REMAINING TIME: %d\n", ((PCB*)aPCB)->remainingTime);

    printf("TOTAL BLOCKED TIME : %d\n", ((PCB*)aPCB)->totalBlockTime);
    printf("TOTAL READY TIME : %d\n", ((PCB*)aPCB)->totalReadyTime);
    printf("TOTAL RUNNING TIME : %d\n", ((PCB*)aPCB)->totalRunningTime);

    printf("NEXT ARRIVAL @: %d\n", ((PCB*)aPCB)->nextArrivalTime);
}

void printOutputPCB(void* aPCB){
    PCB* pcb = aPCB;
    printf("%d %d %d %d\n", pcb->pid, pcb->totalRunningTime, pcb->totalReadyTime, pcb->totalBlockTime);
}

void printIdlePCB(PCB idlePCB){
    printf("%d %d\n", idlePCB.pid, idlePCB.totalRunningTime);
}

void deletePCB(void* aPCB){

    if (aPCB == NULL)
        return;

    // while(((PCB*)aPCB)->exchangeTimes->count > 0){
    //     pop(((PCB*)aPCB)->exchangeTimes);
    //     ((PCB*)aPCB)->totalExchanges -= 1;
    // }
    deleteQ(((PCB*)aPCB)->exchangeTimes);
    // free(((PCB*)aPCB)->exchangeTimes);
    free(((PCB*)aPCB));
}

// FOR FIFO Q : newArrivalQ, blockedQ, exhangeTimes
int compareConstant(const void* PCB1, const void* PCB2){
    return 1;
}

// FOR PRIORITY Q : readyQ
int comparePCB(const void* PCB1, const void* PCB2){

    return ((PCB*)PCB1)->remainingTime - ((PCB*)PCB2)->remainingTime;

}


// DISPATCHER 
void dispatcher(FILE *fd, int harddrive){
    /*
        Your code here.
        You may edit the following code
    */
    char line_buffer[MAX_LINE_LENGTH];
    int start_time, run_time, process_id, num_exchanges, exchange_time;
    char *token;

    // Helper variables
    int maxRemainingTime = -1;
    int totalProcesses = 0;

    // TIMING
    int globalTime = 0;

    // IDLE PROCESS
    PCB idle = {
        .pid = 0,
        .initTime = 0,
        .executionTime = 0,
        .exchangeTimes = createQ(&printExchange, &deleteExchange, &compareConstant),
        .totalExchanges = 0,

        .nextArrivalTime = 0,
        .remainingTime = maxRemainingTime,
        .currentCycleTime = 0,
        .isBlockedAfterCurrentCycle = 0,

        .totalRunningTime = 0,
        
        .blockStart = 0,
        .totalBlockTime = 0,
        
        .readyStart = 0,
        .totalReadyTime = 0
    };

    

    // Running
    PCB* running = &idle;
    

    // New Arrival Q
    int countNewArrival = 0;
    PriorityQ* newArrivalQ = createQ(&printPCB, &deletePCB, &compareConstant);
    
    
    // Ready Q
    int countReady = 0;
    PriorityQ* readyQ = createQ(&printPCB, &deletePCB, &comparePCB);

    // Blocked Q
    int countBlocked = 0;
    PriorityQ* blockedQ = createQ(&printPCB, &deletePCB, &compareConstant);

    // Done Q
    int countDone = 0;
    PriorityQ* doneQ = createQ(&printOutputPCB, &deletePCB, &compareConstant);
    
    //Process simulation input line by line
    while (fgets(line_buffer, MAX_LINE_LENGTH, fd) != NULL && line_buffer[0] != '\n'){
        // Parsed Initialization Time
        token = strtok(line_buffer, " ");
        sscanf(token, "%d",&start_time);


        // Parsed Process Id
        token = strtok(NULL, " ");
        sscanf(token, "%d",&process_id);
            
        // Parsed Execution Time
        token = strtok(NULL, " ");
        sscanf(token, "%d",&run_time);

        // Parsed Exchange Times
        PriorityQ* exchangeTimes = createQ(&printExchange, &deleteExchange, &compareConstant);

        num_exchanges = 0;
        token = strtok(NULL, " ");
        while ( token != NULL ){
            num_exchanges += sscanf(token, "%d",&exchange_time);
            int* newExchange = malloc(sizeof(int));
            *newExchange = exchange_time;
            enqueue(exchangeTimes, newExchange);
            
            token = strtok(NULL, " ");
        }

        if(DEBUG)
            printf("Process %3d wants to start at %6dms and run for %6dms and has %3d hard drive exchanges\n",  process_id, start_time, run_time, num_exchanges);

        PCB* newPCB =  createPCB(process_id, start_time, run_time, exchangeTimes, num_exchanges);
        enqueue(newArrivalQ, newPCB);
        countNewArrival += 1;
        totalProcesses += 1;

        // GET THE REMAINING TIME FOR IDLE PROCESS
        if(run_time > maxRemainingTime){
            maxRemainingTime = run_time+1;
            idle.remainingTime = maxRemainingTime;
        }
    }
    if(DEBUG){
        printf("\nALL THE NEW ARRIVAL RECORDS\n");
        printQ(newArrivalQ);
    }

    // int tmpNewArrival = countNewArrival;
    // while(tmpNewArrival){
    //     enqueue(newArrivalQ, popPCB(newArrivalQ));
        
    //     tmpNewArrival -=1;
    // }

    // printf("\nAFTER POP PUSH\n");
    // printQ(newArrivalQ);




    /***
     * SCHEDULING SECTION
    */

   PCB* block_head = NULL;
   PCB* newArrival_head = NULL;
   PCB* isReadyPCB = NULL;

   // PREVIOUSLY: (countNewArrival > 0 || countReady > 0 || countBlocked > 0)
    while(totalProcesses > countDone){
        if(DEBUG_COMPACT)
            printf("Clock: %d | Running: %d\n", globalTime, running->pid);
        // EXCHANGE TIME OCCURRED FOR CURRENT RUNNING PROCESS
        if(running->pid > 0){
            
            
            // IF CYCLE TIME IS COMPLETE
            if(running->currentCycleTime == 0){
                if(DEBUG)
                    printf("!!!!!!!!!!!!!! REACHED EXCHANGE @ %d !!!!!!!!!!!!!", globalTime);    
                
                int isBlockedAfterCurrentCycle = running->isBlockedAfterCurrentCycle;

                // RELOAD NEXT CYCLE TIME

                // RUN TILL BLOCKING
                if(running->totalExchanges > 0){
                    int* newExchange = popExchange(running->exchangeTimes);
                    running->currentCycleTime = *(newExchange) - running->totalRunningTime;
                    free(newExchange);

                    running->totalExchanges -= 1;
                    running->isBlockedAfterCurrentCycle = 1;
                }

                // RUN TILL COMPLETION
                else{        
                    
                    running->currentCycleTime = running->remainingTime;
                    running->isBlockedAfterCurrentCycle = 0;
                }

                // IF COMPLETED CYCLE IS A RUN TILL BLOCKING
                if(isBlockedAfterCurrentCycle){
                    if(DEBUG)
                        printf("\n>>>>>>>>>>>>>>BLOCKING CYCLE<<<<<<<<<<<<\n");
                    // ADJUST NEXT ARRIVAL TIME
                    int overHead = blockedQ->count == 0 ? globalTime : ((PCB*)peek(blockedQ))->nextArrivalTime;
                    int harDriveCount = blockedQ->count == 0 ? 1 : blockedQ->count;
                    running->nextArrivalTime = overHead + harddrive*(harDriveCount);

                    // ADJUST BLOCK START TIME
                    running->blockStart = globalTime;

                    // PUSH TO BLOCKED Q
                    PCB* newBlockedPCB = copyPCB(running);
                    enqueue(blockedQ, newBlockedPCB);
                    countBlocked += 1;

                    deletePCB(running);
                    running = NULL;
                }

                //------------------------DEBUG------------------------//
                if (DEBUG){
                    printf("\n!!!!!!!!!!!!!!!AFTER EXCHANGE BLOCKED!!!!!!!!!!!!!!!!!!\n");
                    printQ(blockedQ);
                    printf("!!!!!!!!!!!!!!!AFTER EXCHANGE BLOCKED!!!!!!!!!!!!!!!!!!\n");
                }
                //------------------------DEBUG------------------------//

            }
            // else { // ADJUST ARRIVAL TIME TO NOW
            //     running->nextArrivalTime = globalTime;
            // }

            // CURRENT RUNNING PROCESS IS COMPLETE
            if(running != NULL && running->remainingTime == 0){
                
                // PUSH TO DONE Q
                PCB* newDonePCB = copyPCB(running);
                enqueue(doneQ, newDonePCB);
                countDone += 1;

                deletePCB(running);
                running = NULL;

                //------------------------DEBUG------------------------//
                if(DEBUG){
                    printf("\n$$$$$$$$$$$$$$$$$$$$$DONE PROCESSES$$$$$$$$$$$$$$$$$$$$$\n");
                    printQ(doneQ);
                    printf("$$$$$$$$$$$$$$$$$$$$$DONE PROCESSES$$$$$$$$$$$$$$$$$$$$$\n");
                }
                //------------------------DEBUG------------------------//
            }

        } // DONE PROCESSING or BLOCKING A PROCESS that is NOT IDLE

        
        // PREMPTIVE SCHEDULING

        // PUT CURRENTLY RUNNING PROCESS TO READY Q (SORTED BY RT ASCENDING)
        if(running != NULL && running->pid > 0 ){
            running->readyStart = globalTime;

            // INSERT SORTED BY SRT
            PCB* newRunningPCB = copyPCB(running);
            insert(readyQ, newRunningPCB, running->remainingTime);
            countReady += 1;

            deletePCB(running);
            running = NULL;
        }

        block_head = countBlocked > 0 ? peek(blockedQ) : NULL;
        newArrival_head = countNewArrival > 0 ? peek(newArrivalQ) : NULL;

        // GLOBAL TIME MATCHES THE ARRIVAL TIME OF BLOCKED TOP THEN PUT IN READY Q
        if (block_head != NULL && globalTime >= block_head->nextArrivalTime){
            // ADJUST TOTAL BLOCKED TIME
            block_head->totalBlockTime += (globalTime - block_head->blockStart);

            // ADJUST READY TIME
            block_head->readyStart = globalTime;

            // PUSH TO READY Q
            PCB* blockedToReadyPCB = popPCB(blockedQ);
            insert(readyQ, blockedToReadyPCB, blockedToReadyPCB->remainingTime);
            countReady += 1;
            countBlocked -= 1;
        }

        // IF GLOBAL TIME MATCHES ARRIVAL TIME OF NEW ARRIVAL HEAD THEN PUT IN READY Q
        if(newArrival_head != NULL && globalTime >= newArrival_head->nextArrivalTime){
            // ADJUST READY TIME
            newArrival_head->readyStart = globalTime;

            // PUSH TO READY Q
            PCB* newArrivalToReadyPCB = popPCB(newArrivalQ);
            insert(readyQ, newArrivalToReadyPCB, newArrivalToReadyPCB->remainingTime);
            countReady += 1;
            countNewArrival -= 1;
        }

        

        

        isReadyPCB = countReady > 0 ? peek(readyQ) : NULL;

        //------------------------- DEBUG ------------------------//
        if(DEBUG && globalTime % 50 == 0){
            printf("\nTASK SCHEDULING @ TIME: %d\n", globalTime);
            printf("\n*********BEFORE SCHEDULING READY*********\n");
            printQ(readyQ);
            printf("*********BEFORE SCHEDULING READY*********\n");
        }
        //------------------------- DEBUG ------------------------//

        // ASSIGN THE SRT PROCESS FROM READY Q TO RUNNING
        if(isReadyPCB != NULL ){ // 
            running = popPCB(readyQ);
            countReady -= 1;
        }
        // IF NO READY PROCESS AVAILABLE ASSIGN IDLE AS THE RUNNING PROCESS
        else{
            running = &idle;
        }
        
        //------------------------- DEBUG ------------------------//
        if(DEBUG && globalTime % 50 == 0){
            printf("\n*********RUNNING*********\n");
            printPCB(running);
            printf("\n*********RUNNING*********\n");
            
            printf("BLOCKED: %d, NEW ARRIVAL: %d, READY: %d, DONE: %d", countBlocked, countNewArrival, countReady, countDone);
            printf("\n*********AFTER SCHEDULING READY*********\n");
            printQ(readyQ);
            printf("*********AFTER SCHEDULING READY*********\n");
        }
        //------------------------- DEBUG ------------------------//
        
        // TO PREVENT IDLE FROM RUNNING AS THE LAST PROCESS
        if(totalProcesses > countDone){
            
            // PROCESSING NEEDS TO BE DONE ONLY IF THERE IS REMAINING TIME LEFT FOR NON-IDLE PROCESS
            if(running->pid == 0 || (running->pid > 0 && running->remainingTime > 0)) {
                // ADJUST READY TIME
                running->totalReadyTime += (globalTime - running->readyStart);
                running->totalRunningTime += TIME_STEP;
                running->currentCycleTime -= TIME_STEP;
                running->remainingTime -= TIME_STEP;

                globalTime += TIME_STEP;
            }
        }
    }

    if(DEBUG){
        printf("\n\n SRT SCHEDULING IS COMPLETE. RESULTS: \n\n");
        
    }   


    // FINAL OUTPUT PRINTING IN FORMAT EXPECTED
    printIdlePCB(idle);
    printQ(doneQ);

    deleteQ(idle.exchangeTimes);

    // REMOVE PRIORITY Q
    deleteQ(newArrivalQ);
    deleteQ(readyQ);
    deleteQ(blockedQ);

    while(countDone > 0){
        pop(doneQ);
        countDone -= 1;
    }
    deleteQ(doneQ);



    
}


/**
 * SCP: scp dispatcher.c LinkedListAPI.c LinkedListAPI.h queue.c oscreader@192.168.56.03:~/OS-ASSIGNMENTS/A2/shortest_remaining_time/
 * VALGRIND : valgrind --leak-check=full ./Dispatcher 800 <test_inputs/test2.txt
 * **/