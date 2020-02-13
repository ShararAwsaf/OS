CC = gcc
CFLAGS = -Wall -g -std=c99
BIN = ./bin/
SRC = ./src/

all : testProgram program tempTest

program: 
	$(CC) $(CFLAGS) $(SRC)direction.c $(SRC)LinkedListAPI.c $(SRC)main.c -Iinclude -o $(BIN)program


testProgram: 
	$(CC) $(CFLAGS) $(SRC)direction.c $(SRC)LinkedListAPI.c $(SRC)testMain.c -Iinclude -o $(BIN)testProgram

tempTest:
	$(CC) $(CFLAGS) $(SRC)direction.c $(SRC)LinkedListAPI.c $(SRC)tempTest.c -Iinclude -o $(BIN)tempTest

clean:
	rm $(BIN)*
