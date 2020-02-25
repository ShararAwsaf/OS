# include "LinkedListAPI.h"
/*
 * a priority queue
 * has a list to store node
 * has a counter
 * */
typedef struct priorityQ{
	List list;
	int count;
	
}PriorityQ;

/*
 * to create a priority queue
 * @param a print function pointer
 * @param a delete function pointer
 * @param a compare function pointer
 * @return a priority queue
 * */
PriorityQ * createQ(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first, const void *second));

/*
 * to add new nodes to a queue
 * @param a priority queue to add node
 * @param data to store in the new node added to tail
 * */
void enqueue(PriorityQ * aQ,void * data);

/*
 * insert ascending order in que
 * @param a priority que 
 * @param new node to be inserted
 * */
void insert(PriorityQ * aQ, void * data, int value);

/*
 * get first element of que
 * @param returns the pointer to first node's data
 * */
void * peek(PriorityQ * aQ);

/*
 * remove the last element of queue
 * @param a priority que
 * */
void pop(PriorityQ * aQ);

/*
 * returns number of element in que
 * @param a priority que
 * */
int count(PriorityQ * aQ);

/*
 * prints the nodes in que based on function pointer
 * @param a priority que 
 * */
void printQ(PriorityQ * aQ);
