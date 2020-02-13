/**
* author Sharar Mahmood
* date 23 Sept 2017
*/
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

# include "book.h"
# include "boardGame.h"

/**
 * Return a boardGame's name
 * @param  aBoard Board
 * @return   char* string of name
 */

char * getBoardName(Board * aBoard){
	return aBoard->name;
}

/**
 * Return a boardGame's brand name
 * @param  aBoard Board
 * @return   char* string of brand name
 */

char * getBrandName(Board * aBoard){
	return aBoard->brandName;
}

/**
 * Get price of boardGame
 * @param  aBoard Board
 * @return   Double price
 */

double getBoardPrice(Board * aBoard){
	return aBoard->price;
}

/**
 * Assign value to name of boardGame
 * @param  aBoard Board
 * @param  char* s
 */
void setBoardName(Board * board,char * s){
	board -> name = s;
}

/**
 * Assign value to brandName of boardGame
 * @param  aBoard Board
 * @param  char* s
 */
void setBrandName(Board * board,char * s){
	board -> brandName = s;
}

/**
 * Assign value to price of boardGame
 * @param  aBoard Board
 * @param  double s
 */
void setBoardPrice(Board * board,double * s){
	board -> price = *s;
}

/**
 * Display a boardGame's name and price.
 * @param aBoard [Board]
 */

void printBoard(Board * aBoard){
	printf("%s\t%.2lf\t%s\n",getBoardName(aBoard),getBoardPrice(aBoard), getBrandName(aBoard));
}
