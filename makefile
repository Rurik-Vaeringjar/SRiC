CC = gcc
CFLAGS = -lncurses -lm -I./include/
SOURCES = ./src/*.c

all: rogue

rogue:
	$(CC) $(SOURCES) $(CFLAGS) -g -O3 -o rogue

.PHONY: run test memtest clean

run:
	./rogue

test:
	gdb rogue

memtest:
	valgrind ./rogue

clean:
	rm rogue
