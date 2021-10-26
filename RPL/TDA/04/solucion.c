#include "solucion.h"

bool comparador(void* elemento_1, void* elemento_2){
    pokemon_t* pokemon = (pokemon_t*) elemento_1;
    lista_t* podio = elemento_2;

    int mayor_nivel = 0;

    if(pokemon->rapidez > mayor_nivel){
        mayor_nivel = pokemon->rapidez;
    }
    
    if(mayor_nivel == pokemon->rapidez){
        lista_insertar(podio, pokemon);
    }
    return true;
}

void podio_de_pokemones(lista_t* pokemones, lista_t* podio){
    if(!pokemones || !podio){
        return;
    }

    size_t recorrer = 0;

    recorrer = lista_con_cada_elemento(pokemones,comparador,podio);
    
    return;
}