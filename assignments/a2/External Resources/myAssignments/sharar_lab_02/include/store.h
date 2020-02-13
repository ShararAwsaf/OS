/**
 * This File contains the Store structure
 * Store contains an interface of getters and accessors.
 */

# include <stdio.h>

typedef void(*funcPtr)(void *);

/**
 * This structure holds an item as a void pointer, funcPtr as a pointer to a function.
 */
typedef struct store{
	void * item;
	funcPtr fPtr;	

}Store;

/**
 * Accessor for the item
 * @param  s Store
 * @return the item s
 */
void * getItem(Store * s);

/**
 * Sets the item for a Store
 * @param s    Properly created Store
 * @param element    a void pointer
 */
void setItem(Store *s,void * element);

/**
 * Sets the function for a Store item
 * @param s    Properly created Store
 * @param fPtr    a function pointer
 */
void setFunction(Store *s, void * fPtr);

/**
 * Prints the details of the item stored as s Store.
 * @param s Store 
 */
void displayStore(Store * s);
