VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2
CFLAGS =-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
CC = gcc

all: pruebas

pruebas: *.c prueba.c
	gcc $(CFLAGS) lista.c prueba.c -o pruebas 2>&1


