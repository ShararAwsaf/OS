# include "LinkedListAPI.h"

typedef struct stack{
	List * list;
	int count;
	
}Stack;

Stack * createStack(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first, const void *second));

void push(Stack * s, void * data);

void pop(Stack * s);

void * top(Stack * s);

int count(Stack * s);
