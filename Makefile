CC = gcc
CFLAGS = -Wall -Wextra -pedantic

all: main

main: main.c map.c workfile.c
	$(CC) $(CFLAGS) -o main main.c map.c workfile.c

clean:
	rm -f main