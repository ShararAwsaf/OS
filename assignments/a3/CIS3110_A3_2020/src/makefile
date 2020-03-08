# Your code must compile using ths command.
TARGET = virmem

SOURCE = main.c manager.c
TEST_SOURCE = testMain.c manager.c

all:
	make main

main: $(SOURCE)
	gcc -Werror -Wall -g -std=c99 -o virmem $(SOURCE)

test: $(TEST_SOURCE)
	gcc -Werror -Wall -g -std=c99 -o virmem $(TEST_SOURCE)

clean: 
	rm -rf $(TARGET)