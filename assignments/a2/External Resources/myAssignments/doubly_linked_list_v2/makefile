CC = gcc
CFLAGS = -Wall -g -std=c99
BIN = ./bin/
SRC = ./src/

program: 
	$(CC) $(CFLAGS) $(SRC)direction.c $(SRC)LinkedListAPI.c $(SRC)main.c -lm -Iinclude -o $(BIN)program

testProgram: 
	$(CC) $(CFLAGS) -o $(BIN)testProgram -Llib $(SRC)testMain.c $(SRC)direction.c -Iinclude -lLinkedList 

clean:
	rm $(BIN)*
