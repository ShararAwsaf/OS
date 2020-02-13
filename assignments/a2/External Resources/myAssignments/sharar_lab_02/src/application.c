# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

# include "store.h"
# include "book.h"
# include "boardGame.h"

int main (void){

	Store * myStore;

	myStore = malloc(sizeof(Store));

	Board * aBoard;
	char * aName = "Snakes";
	char * aBrand = "Kidco";
	double aPrice = 12.5;

	Board * aBoard2;
	char * aName2 = "Game";
	char * aBrand2 = "Motion";
	double aPrice2 = 11.3;

	Book * book1;
	char * bName = "cat Book";
	double bPrice = 11.5;

	Book * book2;
	char * bName2 = "ugly Duck";
	double bPrice2 = 19.90;

	//Board -1
	aBoard = malloc(sizeof(Board));

	setBoardName(aBoard,aName);
	setBoardPrice(aBoard,&aPrice);
	setBrandName(aBoard,aBrand);

	setItem(myStore,aBoard);
	setFunction(myStore,&printBoard);
	displayStore(myStore);
	

	free(aBoard);


	//Board -2
	aBoard2 = malloc(sizeof(Board));

	setItem(myStore,aBoard2);
	setFunction(myStore,&printBoard);

	setBoardName(aBoard2,aName2);
	setBoardPrice(aBoard2,&aPrice2);
	setBrandName(aBoard2,aBrand2);
	displayStore(myStore);

	free(aBoard2);

	//Book -1
	book1 = malloc(sizeof(Book));

	setItem(myStore,book1);
	setFunction(myStore,&printBook);

	setName(book1,bName);
	setPrice(book1,&bPrice);
	displayStore(myStore);

	free(book1);

	//Book -2
	book2 = malloc(sizeof(Book));

	setItem(myStore,book2);
	setFunction(myStore,&printBook);

	setName(book2,bName2);
	setPrice(book2,&bPrice2);
	displayStore(myStore);

	free(book2);

	free(myStore);


	return 0;
}