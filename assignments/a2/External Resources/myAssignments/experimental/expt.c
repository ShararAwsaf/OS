
void analyzeMovement(List * aList, int * simClock){
	printForward(aList);
	printf("Clock : %d\n",*simClock);
	
	if(aList->head ==NULL){
			return;
	}
	
	while(*simClock != (((Dir*)aList->head->data)->timeArrive)){
		printf("%d\n\n",(((Dir*)aList->head->data)->timeArrive));
		if(*simClock % 16 == 0){
			*simClock = *simClock + 1;
			printf("TIME UP!!\n");
			return;
		}
		
		//KEEP ON TICKING WHILE NOT FOUND
		*simClock = *simClock + 1;
	}
	// FOUND THEN DO STUFF & POP IT
	/*
	 * STUFF
	*/
	
	//POP
	printf("REACHED DELETE\n\n");
	if(aList!=NULL){
		deleteNodeFromList(aList,getFromFront(aList));
	}
	if(aList!=NULL)
		printForward(aList);
	printf("Clock : %d\n",*simClock);
	// THEN GO AGAIN
	printf("RETURNING\n\n");

	analyzeMovement(aList,simClock);
}


/*
int directionMove(List * aList, int* time){
	
	Node * temp;
	
	temp = aList->head;
	
	while(temp->next != NULL){
		
		if(((Dir*)temp->data)->timeArrive == ((Dir*)temp->data)->timeFinish){
			printf("REACHED\n\n");
			action((Dir*)temp->data,time);
		}
		if(*time%14 == 0){
			return *time;
		}
	}
	return *time;
	
}
*/

