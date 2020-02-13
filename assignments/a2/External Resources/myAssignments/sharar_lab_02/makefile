CC = gcc
CFLAGS = -Wall -g -std=c99
BIN = ./bin/
SRC = ./src/

program: 
	$(CC) $(CFLAGS) $(SRC)book.c $(SRC)boardGame.c $(SRC)store.c $(SRC)application.c -Iinclude -o $(BIN)program

clean:
	rm $(BIN)*