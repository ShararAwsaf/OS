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
    List* exchangeTimes; // cycles after which the task set to blocked

    // COMPUTED
    int nextArrivalTime; // when the next instance of the process will arrive
    
    int remainingTime; // how much of execution time left to be completed
    int currentCycleTime; // how long can the current process function before Exchange occurs

    int totalRunningTime; // total running time of the current process

    int blockStart; // the start of exchange block
    int totalBlockTime; // total time the task stayed blocked. Incremented by += currentTime - blockStart
    
    int readyStart; // the start of process in ready list
    int totalReadyTime; // total time the task stayed in ready. Incremented by += currentTime - readyStart

}PCB;


/*
Linked List Functions
*/
// Exchange Time list
void printExchange(void* exTime);
void deleteExchange(void* exTime);
int compareExchange(const void* exTime1, const void* exTime2);


void printExchange(void* exTime){
    printf("EXCHANGE : %d", *((int*)exTime));
}

void deleteExchange(void* exTime){

}

int compareExchange(const void* exTime1, const void* exTime2){
    return *((int*)exTime1) - *((int*)exTime2);
}

// PCB QUEUE
PCB* createPCB(int pid, int initTime, int executionTime, List* exchangeTimes);
void printPCB(void* aPCB);
void deletePCB(void* aPCB);
int comparePCB(const void* PCB1, const void* PCB2);
int compareConstant(const void* PCB1, const void* PCB2);


PCB* createPCB(int pid, int initTime, int executionTime, List* exchangeTimes){
    PCB* aPCB;
    aPCB = malloc(sizeof(PCB));

    aPCB->pid = pid;
    aPCB->initTime = initTime;
    aPCB->exchangeTimes = exchangeTimes;

    return aPCB;
}

void printPCB(void* aPCB){
    
    printf("PID : %d", ((PCB*)aPCB)->pid);
    printf("INIT @: %d", ((PCB*)aPCB)->initTime);
    printf("EXEC TIME : %d", ((PCB*)aPCB)->executionTime);
    printForward(((PCB*)aPCB)->exchangeTimes);

    printf("TOTAL BLOCKED TIME : %d", ((PCB*)aPCB)->totalBlockTime);
    printf("TOTAL READY TIME : %d", ((PCB*)aPCB)->totalReadyTime);
}

void deletePCB(void* aPCB){

    deleteList(((PCB*)aPCB)->exchangeTimes);
}

// FOR FIFO Q : newArrivalQ, blockedQ
int compareConstant(const void* PCB1, const void* PCB2){
    return 1;
}

// FOR PRIORITY Q : readyQ
int comparePCB(const void* PCB1, const void* PCB2){

    return (int)((PCB*)PCB1)->remainingTime - (int)((PCB*)PCB2)->remainingTime;

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
    
    PriorityQ* newArrivalQ = createQ(&printPCB, &deletePCB, &compareConstant);

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
        List* exchangeTimes = initializeList(&printExchange, &deleteExchange, &compareExchange);

        num_exchanges = 0;
        token = strtok(NULL, " ");
        while ( token != NULL ){
            num_exchanges += sscanf(token, "%d",&exchange_time);
            insertBack(exchangeTimes, &exchange_time);
            token = strtok(NULL, " ");
        }
       printf("Process %3d wants to start at %6dms and run for %6dms and has %3d hard drive exchanges\n",  process_id, start_time, run_time, num_exchanges);    
    }
}
