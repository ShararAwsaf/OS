# include <stdio.h>
# include <stdlib.h>


typedef struct direction {
		char come;
		char go;
		int timeArrive;
		float timeFinish;
}Dir;

Dir * createDir(char tempA,char tempD, int tempT);
List * fill(char a,FILE * f);
char getArrival(Dir * aDir);
char getDeparture(Dir * aDir);
int getTime(Dir * aDir);
float getFinishTime(Dir * aDir);

void setArrival(Dir * aDir,char val);
void setDeparture(Dir * aDir, char val);
void setTime(Dir * aDir, int val);
void setFinishTime(Dir * aDir, float val);

void printDir(void* aDir);
void deleteDir(void * element);
int compareDir(const void * a,const void * b);
