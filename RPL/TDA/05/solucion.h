#include <stdbool.h>
#include "lista_iterador.h"

typedef struct entrenador {
    int b_ganadas;
    int b_perdidas;
    int b_empatadas;
} entrenador_t;

void entrenadores_con_muchas_victorias(lista_t* entrenadores, lista_t* entrenadores_ganadores, int batallas_ganadas);