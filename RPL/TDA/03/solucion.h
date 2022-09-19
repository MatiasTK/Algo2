#include <stdbool.h>
#include "lista_iterador.h"

typedef struct entrenador {
    int b_ganadas;
    int b_perdidas;
    int b_empatadas;
} entrenador_t;

entrenador_t* entrenador_con_mas_victorias(lista_t* entrenadores);