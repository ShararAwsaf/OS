CC = gcc
CFLAGS = -Wall -g -pedantic -std=c99
BIN = ./bin/
SRC = ./src/

all: program testProgram

program: 
	$(CC) $(CFLAGS) -o $(BIN)program -Llib $(SRC)main.c $(SRC)book.c -Iinclude -lLinkedList 

testProgram: 
	$(CC) $(CFLAGS) -o $(BIN)testProgram -Llib $(SRC)testMain.c $(SRC)book.c -Iinclude -lLinkedList 


clean:
	rm $(BIN)*
