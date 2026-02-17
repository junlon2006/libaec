CC = gcc
CFLAGS = -O2 -Wall -lm

all: example

example: example.c aec.c aec.h
	$(CC) $(CFLAGS) -o example example.c aec.c

clean:
	rm -f example
