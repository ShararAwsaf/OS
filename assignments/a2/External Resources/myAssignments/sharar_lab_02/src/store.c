/**
* author Sharar Mahmood
* date 23 Sept 2017
*/
# include <stdio.h>
# include <stdlib.h>

# include "store.h"
# include "book.h"
# include "boardGame.h"

/**
 * Return a store's item
 * @param  s Store
 * @return   void* item stored
 */

void * getItem(Store * s){
	return s -> item;
}

/**
 * Assign value to item of store
 * @param  Store s
 * @param  void* element
 */
void setItem(Store *s,void * element){
	s -> item = element;
}

/**
 * Assign value to function pointer fPtr of store
 * @param  Store s
 * @param  void* fPtr
 */
void setFunction(Store *s, void * fPtr){
	s -> fPtr = fPtr;
}

/**
 * Display a store's item details
 * @param s [Store]
 */
void displayStore(Store * s){
	
	s -> fPtr(getItem(s));
}
