# include <stdio.h>
# include <stdlib.h>

/*
 * a struct to store parameters of patient
 * name, priority, symptomCode, processing and finishin times
 * */
typedef struct patient{
		char* name;
		int priorityVal;
		char* symptom ;
		int processTime;
		
		//filled after simulation
		int timeFinish;
}Pat;

/*
 * create a priority q using the patient struct and return created struct pointer
 * */
PriorityQ * createPatientQ();

/*
 * initialize a patient struct
 * @param a name
 * @param a priority
 * @param symptom
 * @aram processing time
 * */
Pat * createPatient(char * name, int priority,char * symptom,int processTime);

/*
 * accessor for name
 * */
char* getName(Pat * aPatient);

/*
 * mutator for name
 * */
void setName(Pat * aPatient, char * name);

/*
 * accessor for priority
 * */
int getPriorityVal(Pat * aPatient);
/*
 * mutator for priority
 * */
void setProrityVal(Pat * aPatient, int priorityVal);
/*
 * accessor for symptomcode
 * */
char* getSymptom(Pat * aPatient);
/*
 * mutator for symptomcode
 * */
void setSymptom(Pat * aPatient, char * symptom);

/*
 * accessor for process time
 * */
int getProcessTime(Pat * aPatient);
/*
 * mutator for processtime
 * */
void setProcessTime(Pat * aPatient, int processTime);
/*
 * helper function for update priority time
 * */
int generatePriority(char * aSymptom);

 /*
 * accessor for finish time
 * */
int  getTimeFinish(Pat * aPatient);
/*
 * mutator for finish time
 * */
void setTimeFinish(Pat * aPatient, int timeFinish);

/*
 * helper function for getting process time
 * */
int generateProcessTime(char ** aSymptom);

/*
 * function to print a patient node
 * */
void printPatient(void* aPatient);

/*
 * function to compare two patient struct
 * */
int equals(Pat * aPatient, Pat * bPatient);
