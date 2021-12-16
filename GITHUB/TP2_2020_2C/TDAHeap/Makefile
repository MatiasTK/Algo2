CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

test: pruebas_heap.c heap.c
	gcc pruebas_heap.c heap.c $(CFLAGS) -o pruebas_heap
	clear
	./pruebas_heap

c: pruebas_heap.c heap.c
	gcc pruebas_heap.c heap.c $(CFLAGS) -o pruebas_heap

debug:
	gdb ./pruebas_heap

memory:
	valgrind $(VFLAGS) ./pruebas_heap

clean:
	rm -rf pruebas_heap

	#gcc pruebas_heap.c heap.c -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -o pruebas_heap

	#valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas_heap