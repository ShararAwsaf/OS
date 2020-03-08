#include <stdio.h>
#include <stdlib.h>
#include "manager.h"

int main(int argc, char* argv[]){

    //argc : argument count
    //argv : argument values

    if(argc != 2){ // BY DEFAULT THE ARG COUNT IS 1
        fprintf(stderr, "Invalid number of arguments.\nPassed : %d Required: 1\n", argc-1);
    }

    // memmanager();

    return 0;
}