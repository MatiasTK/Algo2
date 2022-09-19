#include <stdio.h>

typedef struct pokemon {
    char* nombre_pokemon;
    int fuerza;  
} pokemon_t;

typedef struct entrenador {
    char* nombre_entrenador;
    pokemon_t* pokemones;
    int tope;
} entrenador_t;

pokemon_t* pokemon_buscado(entrenador_t* entrenador, char* nombre_pokemon){
    if(!entrenador || !nombre_pokemon){
        return 0;
    }
    for(int i = 0; i < entrenador->tope; i++){
        pokemon_t* pokemon = &(entrenador->pokemones[i]);
        if(pokemon->nombre_pokemon == nombre_pokemon){
            return pokemon;
        }
    }
    return 0;
}

