#include <stdio.h>
#include <stdlib.h>
#include "manager.h"

int main(int argc, char **argv){

    //argc : argument count
    //argv : argument values

    if(argc != 2){ // BY DEFAULT THE ARG COUNT IS 1
        fprintf(stderr, "Invalid number of arguments.\nPassed : %d Required: 1\n", argc-1);
        return -1;
    }
    else{
        int status = memmanager(argv[1]);

        if(status == EXIT_FAILURE){
            fprintf(stderr,"Failed processing file : %s\n", argv[1]);
        }
    }

    return 0;
}

/**
 * Shortcuts
 * 
 * **/

// code transfer: scp ./src/* oscreader@192.168.56.03:~/OS-ASSIGNMENTS/A3/CIS3110_A3_2020/src/
// tests transfer: scp ./* oscreader@192.168.56.03:~/OS-ASSIGNMENTS/A3/CIS3110_A3_2020/
// execution : valgrind --leak-check=full ./virmem ../testAddresses.txt