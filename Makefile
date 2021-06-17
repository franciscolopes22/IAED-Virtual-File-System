CC=gcc
CFLAGS=-ansi -pedantic -Wextra -Wall -Werror

all: main.c structure.c structure.h commands.c commands.h
	$(CC) $(CFLAGS) proj2.c structure.c commands.c -o proj2

