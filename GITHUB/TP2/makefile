CFLAGS=-g -O0 -std=c99 -Wall -Werror -Wconversion -Wtype-limits -pedantic -lm
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes

juego: juego.c aventura.c batallas.c herramientas_graficas.c TDAs/lista/lista.c TDAs/heap/heap.c
	gcc juego.c aventura.c batallas.c herramientas_graficas.c TDAs/lista/lista.c TDAs/heap/heap.c $(CFLAGS) -o juego

ejecutar_juego: juego
	clear
	./juego

valgrind_juego: juego
	clear
	valgrind $(VFLAGS) ./juego

debug_juego: juego
	clear
	gdb ./juego