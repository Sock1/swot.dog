.PHONY: all

CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS=

all: swotdog clean

swotdog: main.o parse.o swot.o
	$(CC) $(LDFLAGS) $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $^ -o $@

parse.o: parse.c parse.h
	$(CC) $(CFLAGS) -c $< -o $@

swot.o: swot.c swot.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

