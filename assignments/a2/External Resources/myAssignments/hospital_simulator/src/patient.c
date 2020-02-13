# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# include "LinkedListAPI.h"
# include "queue.h"
# include "patient.h"

typedef void(*print)(void*);
typedef void(*delete)(void*);
typedef int(*tCompare)(const void*,const void*);

/*
 * accessor : name
 * @param a patient sturuct
 * @return name
 * */
char* getName(Pat * aPatient){
	return aPatient -> name;
}

/*
 * mutator : name
 * @param a patient struct
 * @param a name
 * */
void setName(Pat * aPatient, char * name){
	char * patientName = malloc(sizeof(char) * strlen(name));
	strcpy(patientName,name);
	patientName[strlen(patientName)] = '\0';
	aPatient -> name = patientName;
}
/*
 * accessor : priority
 * @param a patient struct
 * @return a priority
 * */
int getPriorityVal(Pat * aPatient){
	return aPatient -> priorityVal;
}

/*
 * mutator : priority
 * @param a patient struct
 * @param a priority
 * */
void setPriorityVal(Pat * aPatient, int priorityVal){
	aPatient -> priorityVal = priorityVal;
}

/*
 * accessor : ssymptom code
 * @param a patient struct
 * @return a symptom code
 * */
char* getSymptom(Pat * aPatient){
	return aPatient -> symptom;
}

/*
 * mutator : symptom code
 * @param a patient struct
 * @param a symptom code
 * */
void setSymptom(Pat * aPatient, char * symptom){
	char * patientSymptom = malloc(sizeof(char) * strlen(symptom));
	strcpy(patientSymptom,symptom);
	patientSymptom[strlen(patientSymptom)] = '\0';
	aPatient -> symptom = patientSymptom ;
}

/*
 * accessor : processing time
 * @param a patient struct
 * @return a process time
 * */
int getProcessTime(Pat * aPatient){
	return aPatient -> processTime;
}

/*
 * mutator : processing time
 * @param a patient struct
 * @param a process time
 * */
void setProcessTime(Pat * aPatient, int processTime){
	aPatient -> processTime = processTime;
}

/*
 * accessor : finish time
 * @param a patient struct
 * @return a finish time
 * */
int getTimeFinish(Pat * aPatient){
	return aPatient -> timeFinish;
}

/*
 * mutator : finish time
 * @param a patient struct
 * @param a finish time
 * */
void setTimeFinish(Pat * aPatient, int timeFinish){
	aPatient -> timeFinish = timeFinish;
}

/*
 * helper : processing a string to get a valid symptom code
 * @param a string
 * @return a validate symptom code
 * */
char * processString(char * aString){
	char * newString;
	int i = 0;
	int j = 0;
	
	newString = malloc(sizeof(char) * strlen(aString));
	
	while(j<strlen(aString)){
		if(aString[j] != ' '){
			newString[i] = toupper(aString[j]);
			i++;
		}
		j++;
	}
	newString[i] = '\0';
	
	return newString;
}

/*
 * helper : processing a symptom to get a valid processing time
 * @param a symptom code
 * @return a valid processing time
 * */
int generateProcessTime(char ** aSymptom){
	*aSymptom = processString(*aSymptom);
	
	if (strcmp(*aSymptom,"CV") == 0){
		return 5;
	}
	
	else if (strcmp(*aSymptom,"HN") == 0){
		return 3;
	}
	
	else if (strcmp(*aSymptom,"EV") == 0){
		return 10;
	}
	
	else if (strcmp(*aSymptom,"GI") == 0){
		return 2;
	}
	
	else if (strcmp(*aSymptom,"MH") == 0){
		return 5;
	}
	
	else if (strcmp(*aSymptom,"NC") == 0){
		return 5;
	}
	
	else if (strcmp(*aSymptom,"EC") == 0){
		return 1;
	}
	
	else if (strcmp(*aSymptom,"RC") == 0){
		return 1;
	}
	
	else if (strcmp(*aSymptom,"SK") == 0){
		return 2;
	}
	
	else if (strcmp(*aSymptom,"SA") == 0){
		return 7;
	}
	
	else if (strcmp(*aSymptom,"TR") == 0){
		return 4;
	}
	
	return -1;
}

/*
 * A function to compare two patient nodes
 * @param a direction node
 * @param a comapring patient node
 * */
int comparePatient(const void * a,const void * b) {

	return (int)(((Pat*)a)->priorityVal) - (int)(((Pat*)b)->priorityVal);
}

/*
 * A function to delete a direction node
 * @param a direction node
 * */
void deletePatient(void * element){
	free((Pat*)element);
	element = NULL;
}

/*
 * A function to print information of patient
 * @param a pointer to a patient node
 * */
void printPatient(void* aPatient) {
	printf("%s\t\t\t%d \t\t%s \t\t%d\n\n",getName(aPatient),getPriorityVal(aPatient),getSymptom(aPatient),getTimeFinish(aPatient));
}

/*
 * initialize a priority que for starting the simulation
 * @return an initialized priority que
 * */
PriorityQ * createPatientQ(){
	
	PriorityQ * q;
	print p;
	delete d;
	tCompare c;
	p = &printPatient;
	d = &deletePatient;
	c = &comparePatient;
	
	q = createQ(p,d,c);
	
	return q;
}

/*
 * creating a node for the priority que of patient
 * @param name
 * @param symptom
 * @param processing time
 * @param priority
 * @return an initialized node
 * */
Pat * createPatient(char * name, int priority,char * symptom,int processTime){
	Pat * aPatient;
	
	aPatient = malloc(sizeof(Pat)); 
	
	setName(aPatient,name);
	setPriorityVal(aPatient,priority);
	setSymptom(aPatient,symptom);
	setProcessTime(aPatient,processTime);
	setTimeFinish(aPatient,processTime+1);
	
	return aPatient;	
	
}

/*
 * comparator for two patient nodes
 * @param : a patient node 
 * @param : b patient node
 * @return 1 if equal else 0
 * */
int equals(Pat * aPatient, Pat * bPatient){
	return( (aPatient -> priorityVal == bPatient -> priorityVal) && strcmp(aPatient -> name, bPatient -> name) == 0 && strcmp(aPatient -> symptom,bPatient -> symptom) == 0 && aPatient->processTime == bPatient->processTime );
}
