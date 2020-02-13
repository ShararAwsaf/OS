/*
 * author : Sharar mahmood
 * date : Oct 1 2017
 * name : main.c
 * */
 
#ifndef MAIN_H
#define MAIN_H

# include <string.h>
# include "queue.h"
# include "LinkedListAPI.h"
# include "patient.h"

# define MAX_SIZE 100

char menu();
void addPatient(PriorityQ * aQ, PriorityQ * outputQ);
void addFromFile(PriorityQ * patientQ,PriorityQ * outputQ,FILE * file);
void runSimulation(PriorityQ * aQ);
void setOutputTime(PriorityQ * aQ , PriorityQ * bQ);
void filePrint(FILE * file, PriorityQ * outputQ);
//void adjustPriority(PriorityQ * patientQ, Node * temp);

int main (int argc, char * argv[]){
	
	FILE * file;
	char choice = ' ';
	PriorityQ * patientQ = NULL;
	PriorityQ * outputQ = NULL;
	
	patientQ = createPatientQ();
	outputQ = createPatientQ();
	
	file = fopen(argv[1],"r");
	
	if(file == NULL){
		printf("No files provided \n\n");
	}
	else{
		addFromFile(patientQ,outputQ,file);
		fclose(file);
		//printf("Patient ID\t     Priority\t Symptom Code\t\n");
		//printQ(patientQ);
	}
	
	printf("Welcome to Hospital Simulation\n");	
	choice = menu();

	while(choice != 'q'){
		if(choice == 'a'){
			addPatient(patientQ,outputQ);
			//printf("Patient ID\t     Priority\t Symptom Code\t\n");
			//printQ(patientQ);
		}
		else if (choice == 'r'){
			runSimulation(patientQ);
			setOutputTime(patientQ,outputQ);
			printf("Patient ID\t     Priority\t Symptom Code\t Time Finished\n");
			printQ(outputQ);
			
			//Print inside file
			file = fopen("OUTPUT.txt","w+");
			filePrint(file,outputQ);
			fclose(file);
		}
		choice = menu();
	}
	
	printf("\nThanks for staying\n");
	return 0;
}

/*
 * The command loop
 * */
char menu(){
	
	char* choice = malloc(sizeof(char) * MAX_SIZE);
	
	printf("Press a to add new patient\n");
	printf("Press r to run simulation\n");
	printf("Press q to exit\n");
	
	while( choice[0] != 'a' && choice[0] != 'r' && choice[0] != 'q'){
		printf("Your choice : ");
		scanf("%s",choice);
		//getchar();
		if(strlen(choice)> 1 || (choice[0] != 'a' && choice[0] != 'r' && choice[0] != 'q')){
			printf("Invalid Selection\n\n");
			
			printf("Press a to add new patient\n");
			printf("Press r to run simulation\n");
			printf("Press q to exit\n");
		}
	}
	
	return choice[0];
}

/*
 * adding values from file into priority ques
 * @ param two priority ques
 * */
void addFromFile(PriorityQ * aQ, PriorityQ * outputQ, FILE * file){
	
	//printf("Extracting data from file\n");
	char * aName;
	int priority = -1;
	char * aSymptom;
	int processTime = -1;
	
	aName = malloc(sizeof(char) * MAX_SIZE);
	aSymptom = malloc(sizeof(char) * MAX_SIZE);
	
	while(!feof(file)){
		fscanf(file,"%s %d %s\n",aName,&priority,aSymptom);
		processTime = generateProcessTime(&aSymptom);
		
		enqueue(outputQ,(void *) createPatient(aName,priority,aSymptom,processTime));
		insert(aQ, (void *) createPatient(aName,priority,aSymptom,processTime), priority);
	}
}

/*
 * adding patients to priority que
 * @param two priority ques
 * */
void addPatient(PriorityQ * aQ, PriorityQ * outputQ){

	char * aName;
	int priority = -1;
	char * aSymptom;
	int processTime = -1;
		
	aName = malloc(sizeof(char) * MAX_SIZE);
	aSymptom = malloc(sizeof(char) * MAX_SIZE);
	
	/*
	 * BETTER INPUT
	printf("Set a name : ");
	scanf("%s",aName);
	
	while(priority < 0){
		printf("Set a priority : ");
		scanf("%d",&priority);
		
		if(priority<0){
			printf("Invalid input");
		}
	}
	
	while(processTime == -1){
		printf("List of symptoms\n CV -- HN -- EV -- GI -- MH -- NC -- EC -- RC -- SK -- SA -- TR \n");
		printf("Set a symptom : ");
		scanf("%s",aSymptom);
		processTime = generateProcessTime(&aSymptom);
		
		if(processTime == -1){
			printf("Invalid symptom\n");
		}
		//getchar();
	}
	*/
	
	printf("Enter : Patient ID Priority Symptom Code\n\n\t");
	
	fscanf(stdin,"%s %d %s",aName,&priority,aSymptom);
	
	processTime = generateProcessTime(&aSymptom);
	
	if(processTime != -1){
		enqueue(outputQ,(void *) createPatient(aName,priority,aSymptom,processTime));
		insert(aQ, (void *) createPatient(aName,priority,aSymptom,processTime),priority);
	}
}

void runSimulation(PriorityQ * aQ){
	int globalClock = 0;
	Node * temp;
	
	temp = aQ -> list -> head;
	
	while(temp!= NULL){

		if(temp != NULL){
			globalClock += ((Pat*)temp->data) -> processTime + 1;
			((Pat*)temp->data) -> timeFinish = globalClock;
		}
		//printPatient((void*)(temp->data));
		temp = temp -> next;
		
		/*Aging starvation algorithm
		 if (globalClock == 50){
		 	adjustPriority(aQ,temp);
		 }*/
	}
}

/*
 * Setting up output time for the priority que
 * @param two priority ques
 * */
void setOutputTime(PriorityQ * aQ , PriorityQ * bQ){
	Node * tempB = bQ -> list -> head;
	Node * tempA = aQ -> list -> head;
	
	while(tempB!= NULL){
		while(tempA != NULL){
			if(equals((Pat*)(tempB)->data,(Pat*)(tempA)->data)){
				((Pat*)tempB -> data) -> timeFinish = ((Pat*)tempA -> data) -> timeFinish;
			}
			tempA = tempA -> next;
		}
		tempB = tempB -> next;
		tempA = aQ -> list -> head;
	}
}

/*
 * Function to print output to file
 * @param file pointer
 * @param priority que with time finished
 * 
 * */
void filePrint(FILE * file, PriorityQ * outputQ){
	
	int i = 0;
	Node * temp;
	
	temp = outputQ->list->head;
	
	if(file == NULL){
		printf("File creation/access failed\n");
		return;
	}
	
	fprintf(file,"Patient ID\t\t\t\t\tPriority \tSymptom Code \tTime Finished\n");
	for(i = 0;i<outputQ->count;i++){
		if(temp != NULL)
			fprintf(file,"%s\t\t\t\t\t\t\t%d \t\t\t%s \t\t\t\t%d \n",((Pat*)(temp->data))->name, ((Pat*)(temp->data))->priorityVal, ((Pat*)(temp->data))->symptom, ((Pat*)(temp->data))->timeFinish);
		temp = temp -> next;
	}
	
}

/*Aging starvation algorithm
  void adjustPriority(PriorityQ * patientQ, Node * temp){
  		Node * node = patientQ -> list -> head;
  		while(node != temp){
  			node = node -> next;
  		}
  		while(node!= NULL){
  			((Pat*)(node -> data)) -> priorityVal = ((Pat*)(node -> data)) -> priorityVal -1;
  			node = node -> next;
  		}
  	
  }
*/ 

#endif

