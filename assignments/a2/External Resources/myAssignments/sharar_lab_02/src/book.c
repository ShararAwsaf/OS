/**
* author Sharar Mahmood
* date 23 Sept 2017
*/
# include <stdio.h>
# include "book.h"

/**
 * Return a books name
 * @param  b Book
 * @return   char* string of name
 */

char * getName(Book *b){
	return b->name;
}

/**
 * Get price of book
 * @param  b Book
 * @return   Double price
 */

double getPrice(Book * b){
	return b->price;
}

/**
 * Assign value to name of book
 * @param  Book b
 * @param  char* p
 */
void setName(Book * b, char * p){
	b -> name = p;
}


/**
 * Assign value to price of book
 * @param  Book b
 * @param  double p
 */
void setPrice(Book * b, double * p){
	b -> price = *p;
}

/**
 * Display a book's name and price.
 * @param b [Book]
 */

void printBook(Book * b){
	printf("%s : %lf\n",getName(b),getPrice(b));
}

