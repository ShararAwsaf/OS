CC = gcc
CFLAGS = -Wall -g -pedantic -std=c99
BIN = ./bin/
SRC = ./src/

all: program

program: 
	$(CC) $(CFLAGS) -o $(BIN)program -Llib $(SRC)main.c $(SRC)direction.c -Iinclude -lLinkedList 

clean:
	rm $(BIN)*
