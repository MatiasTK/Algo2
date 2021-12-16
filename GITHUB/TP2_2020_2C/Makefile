CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

test: juego.c definiciones.c batallas.c TDAHeap/heap.c TDALista/lista.c
	gcc juego.c definiciones.c batallas.c TDAHeap/heap.c TDALista/lista.c $(CFLAGS) -o juego
	clear
	./juego

c: juego.c definiciones.c batallas.c TDAHeap/heap.c TDALista/lista.c
	gcc juego.c definiciones.c batallas.c TDAHeap/heap.c TDALista/lista.c $(CFLAGS) -o juego

debug:
	gdb ./juego

memory: 
	gcc juego.c definiciones.c batallas.c TDAHeap/heap.c TDALista/lista.c $(CFLAGS) -o juego
	clear
	valgrind $(VFLAGS) ./juego

clean:
	rm -rf juego

	#gcc juego.c definiciones.c batallas.c TDAHeap/heap.c TDALista/lista.c -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -o juego

	#valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./juego