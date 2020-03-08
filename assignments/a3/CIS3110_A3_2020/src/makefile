# Your code must compile using ths command.
TARGET = virmem

HELPERS = LinkedListAPI.c queue.c
SOURCE = main.c manager.c
TEST_SOURCE = testMain.c manager.c

all:
	make main

main: $(SOURCE)
	gcc -Werror -Wall -g -std=c99 -o $(TARGET) $(SOURCE) $(HELPERS)

test: $(TEST_SOURCE)
	gcc -Werror -Wall -g -std=c99 -o $(TARGET) $(TEST_SOURCE) $(HELPERS)

clean: 
	rm -rf $(TARGET)