CFLAGS=-Wall -Wextra -Wpedantic -std=gnu17 -g

all: fwatch.c
	gcc ${CFLAGS} -o fwatch fwatch.c
