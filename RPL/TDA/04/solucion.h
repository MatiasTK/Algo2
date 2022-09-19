#include <stdbool.h>
#include "lista_iterador.h"

typedef struct pokemon {
    int fuerza;
    int rapidez;
    int inteligencia;
} pokemon_t;

void podio_de_pokemones(lista_t* pokemones, lista_t* podio);