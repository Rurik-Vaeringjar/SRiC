CC = gcc
CFLAGS = -lncurses -lm -I./include/
SOURCES = ./src/*.c

all: rogue

rogue:
	$(CC) $(SOURCES) $(CFLAGS) -g -O3 -o rogue

.PHONY: noop run test memtest clean

noop:
	$(CC) $(SOURCES) $(CFLAGS) -g -o rogue

run:
	./rogue

test:
	gdb rogue

memtest:
	valgrind ./rogue

clean:
	rm rogue
