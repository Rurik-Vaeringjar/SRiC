CC = gcc
CFLAGS = -lncurses -lm -I./include/
SOURCES = ./src/*.c

all: rogue

rogue:
	$(CC) $(SOURCES) $(CFLAGS) -g -O3 -o rogue

.PHONY: noop run test memtest fullmemtest clean

noop:
	$(CC) $(SOURCES) $(CFLAGS) -g -o rogue

run:
	./rogue

test:
	gdb rogue

memtest:
	valgrind ./rogue

fullmemtest:
	valgrind --leak-check=full --verbose ./rogue

clean:
	rm rogue
