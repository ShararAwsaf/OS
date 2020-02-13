CC = gcc
CFLAGS = -Wall -g -std=c99
BIN = ./bin/
SRC = ./src/

all : testProgram program

program: 
	$(CC) $(CFLAGS) $(SRC)patient.c $(SRC)LinkedListAPI.c $(SRC)queue.c $(SRC)main.c -Iinclude -o $(BIN)program


testProgram: 
	$(CC) $(CFLAGS) $(SRC)patient.c $(SRC)LinkedListAPI.c $(SRC)queue.c $(SRC)testMain.c -Iinclude -o $(BIN)testProgram

clean:
	rm $(BIN)*
