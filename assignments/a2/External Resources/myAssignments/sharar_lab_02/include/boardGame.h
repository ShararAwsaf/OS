/**
 * This File contains the Board structure
 * Board contains an interface of getters and accessors.
 */

# include <stdio.h>

/**
 * This structure holds a name as a string, brand name as a string and a price as double.
 */
typedef struct board{
	char * name; // pass in char * 
	double price;
	char * brandName; // pass in char * 
}Board;


/**
 * Accessor for the name
 * @param  aBoard Board
 * @return the name of Board aBoard
 */
char * getBoardName(Board * aBoard);

/**
 * Accessor for the price
 * @param  aBoard Board
 * @return the price of Board aBoard
 */
double getBoardPrice(Board * aBoard);

/**
 * Accessor for the brandName
 * @param  aBoard Board
 * @return the brandName of Board aBoard
 */
char * getBrandName(Board * aBoard);



/**
 * Sets the name for a board
 * @param board    Properly created Board
 * @param s    string
 */
void setBoardName(Board * board,char * s);

/**
 * Sets the brandName for a board
 * @param board    Properly created Board
 * @param s    string
 */
void setBrandName(Board * board,char * s);

/**
 * Sets the price for a board
 * @param board   Properly created Board
 * @param s    string
 */
void setBoardPrice(Board * board,double * s);

/**
 * Prints the name and price of a board.
 * @param aBoard Board 
 */
void printBoard(Board * aBoard);