CC = gcc
CFLAGS = -Wall -g -std=c99
BIN = ./bin/
SRC = ./src/

all : testProgram program

program: 
	$(CC) $(CFLAGS) $(SRC)direction.c $(SRC)LinkedListAPI.c $(SRC)main.c -Iinclude -o $(BIN)program


testProgram: 
	$(CC) $(CFLAGS) $(SRC)direction.c $(SRC)LinkedListAPI.c $(SRC)testMain.c -Iinclude -o $(BIN)testProgram

clean:
	rm $(BIN)*
