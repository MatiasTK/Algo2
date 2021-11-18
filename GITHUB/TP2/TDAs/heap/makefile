CFLAGS=-g -O0 -std=c99 -Wall -Werror -Wconversion -lm -Wtype-limits -pedantic

testing: testing.c heap.c
	gcc testing.c heap.c $(FLAGS) -o testing

ejecutar_testing: testing
	clear
	./testing

valgrind_testing: testing
	clear
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./testing

debug_testing: testing
	clear
	gdb ./testing