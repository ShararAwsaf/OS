/**
 * This File contains the Book structure
 * Book contains an interface of getters and accessors.
 */

# include <stdio.h>
/**
 * This structure holds a name as a string and a price as double.
 */
typedef struct book{
	double price;
	char * name;
}Book;

/**
 * Accessor for the name
 * @param  b Book
 * @return the name of Book b
 */
char * getName(Book *b);

/**
 * Accessor for the price
 * @param  b Book
 * @return the price of Book b
 */
double getPrice(Book * b);

/**
 * Sets the name for a book
 * @param b    Properly created Book
 * @param p    string
 */
void setName(Book * b, char * p);

/**
 * Sets the price for a book
 * @param b    Properly created Book
 * @param p    double
 */
void setPrice(Book * b, double * p);

/**
 * Prints the name and price of a book.
 * @param b Book 
 */
void printBook(void * b);
