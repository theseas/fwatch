CFLAGS=-Wall -Wextra -Wpedantic -std=c17

all: fwatch.c
	gcc ${CFLAGS} -o fwatch fwatch.c
