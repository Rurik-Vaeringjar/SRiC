CC = gcc
CFLAGS = -lncurses -lm -I./include/
SOURCES = ./src/*.c

all: rogue run clean

rogue:
	$(CC) $(SOURCES) $(CFLAGS) -g -O3 -o rogue

run:
	gdb rogue
	#./rogue

clean:
	#rm rogue
