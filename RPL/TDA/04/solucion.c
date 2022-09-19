#include "solucion.h"

typedef struct datos{
    pokemon_t* oro;
    pokemon_t* plata;
    pokemon_t* bronce;
} datos_t;

bool buscar_mas_veloces(void* elemento_1, void* elemento_2){
    pokemon_t* pokemon = elemento_1;
    datos_t* datos = elemento_2;

    if(pokemon->rapidez > datos->oro->rapidez){
        datos->bronce = datos->plata;
        datos->plata = datos->oro;
        datos->oro = pokemon;
    }else if(pokemon->rapidez > datos->plata->rapidez){
        datos->bronce = datos->plata;
        datos->plata = pokemon;
    }else if(pokemon->rapidez > datos->bronce->rapidez){
        datos->bronce = pokemon;
    }

    return true;
}

void podio_de_pokemones(lista_t* pokemones, lista_t* podio){
    if(!pokemones || lista_vacia(pokemones)){
        return;
    }

    datos_t dato;
    dato.oro = lista_primero(pokemones);
    dato.plata = lista_primero(pokemones);
    dato.bronce = lista_primero(pokemones);

    lista_con_cada_elemento(pokemones, buscar_mas_veloces, &dato);

    lista_insertar_en_posicion(podio, dato.oro, 0);
    lista_insertar_en_posicion(podio, dato.plata, 1);
    lista_insertar_en_posicion(podio, dato.bronce, 2);
}