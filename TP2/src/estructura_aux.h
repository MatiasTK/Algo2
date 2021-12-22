#ifndef __ESTRUCTURA_AUX_H__
#define __ESTRUCTURA_AUX_H__

#include "lista.h"
#include <stdlib.h>

typedef struct _hospital_pkm_t hospital_t;
typedef struct _pkm_t pokemon_t;
typedef struct _entrenador_t entrenador_t;

struct _hospital_pkm_t{
    lista_t* lista_entrenadores;
    size_t cantidad_pokemon;
    size_t cantidad_entrenador;
};

struct _pkm_t{
    char* nombre;
    size_t nivel;
    entrenador_t* entrenador;
};

struct _entrenador_t{
    char* nombre;
    lista_t* lista_pokemones;
    size_t id;
};

#endif // __ESTRUCTURA_AUX_H__