CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

test: lista.c lista_pruebas.c
	gcc lista.c lista_pruebas.c $(CFLAGS) -o lista_se
	clear
	./lista_se

minitest: lista.c lista_minipruebas.c
	gcc lista.c lista_minipruebas.c $(CFLAGS) -o lista_se
	clear
	./lista_se

c: lista.c lista_pruebas.c
	gcc lista.c lista_pruebas.c $(CFLAGS) -o lista_se

cmini: lista.c lista_minipruebas.c
	gcc lista.c lista_minipruebas.c $(CFLAGS) -o lista_se

debug:
	gdb ./lista_se

memory:
	valgrind $(VFLAGS) ./lista_se

clean:
	rm -rf lista_se

	#gcc lista.c lista_minipruebas.c -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -o lista_se

	#valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_se