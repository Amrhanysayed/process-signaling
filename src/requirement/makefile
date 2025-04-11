CC = gcc
CFLAGS = -g -Wall

all: run

run: cmpsh
	./cmpsh

cmpsh: main.c parser.c builtins.c execute.c noninteractive.c
	$(CC) $(CFLAGS) main.c parser.c builtins.c execute.c noninteractive.c   -o cmpsh

clean:
	rm -f cmpsh
