# include <stdio.h>
# include <stdlib.h>


typedef struct direction {
		char come;
		char go;
		int timeArrive;
		float timeFinish;
}Dir;

/*
 * A function to initialize a direction node
 * */
Dir * createDir(char tempA,char tempD, int tempT);

/*
 * A function that returns a list of direction nodes of similar arrival direction in sorted manner
 * */
List * fill(char a,FILE * f);

/*
 * A function to obtain arrival direction of car
 * */
char getArrival(Dir * aDir);

/*
 * A function to obtain destination direction of car
 * */
char getDeparture(Dir * aDir);

/*
 * A function to obtain arrival time of car
 * */
int getTime(Dir * aDir);

/*
 * A function to obtain processing time of car
 * */
float getFinishTime(Dir * aDir);

/*
 * A function to set arrival direction of car
 * */
void setArrival(Dir * aDir,char val);

/*
 * A function to set departure direction of car
 * */
void setDeparture(Dir * aDir, char val);

/*
 * A function to set time of arrival of car
 * */
void setTime(Dir * aDir, int val);

/*
 * A function to processing time of car
 * */
void setFinishTime(Dir * aDir, float val);


/*
 * A function to print details of car
 * */
void printDir(void* aDir);


/*
 * A function to delete a node of car
 * */
void deleteDir(void * element);

/*
 * A function to compare two cars
 * */
int compareDir(const void * a,const void * b);
