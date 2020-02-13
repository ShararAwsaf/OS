# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# include "LinkedListAPI.h"
# include "direction.h"

int main(void){
	Dir * dir1 ,* dir2;
	dir1 = malloc(sizeof(Dir));
	dir2 = malloc(sizeof(Dir));
	
	dir1 -> timeArrive = 2;
	dir2 -> timeArrive = 3;
	printf("Diff : %d\n",compareDir(dir1,dir2));
}
