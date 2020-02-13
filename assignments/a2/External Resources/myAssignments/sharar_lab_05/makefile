CC = gcc
CFLAGS = -Wall -g -pedantic -std=c99
BIN = ./bin/
SRC = ./src/


program: 
	$(CC) $(CFLAGS) -o $(BIN)program -Llib $(SRC)main.c $(SRC)stack.c -Iinclude -lLinkedList

clean:
	rm $(BIN)*
