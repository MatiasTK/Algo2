#include "lista.h"
#include "pa2mm.h"

typedef struct pokemon {
    int fuerza;
    int rapidez;
    int inteligencia;
} pokemon_t;

typedef struct datos{
    pokemon_t* oro;
    pokemon_t* plata;
    pokemon_t* bronce;
} datos_t;

/* bool buscar_oro(void* elemento_1, void* elemento_2){
    pokemon_t* pokemon = elemento_1;
    datos_t* datos = elemento_2;

    if(pokemon > datos->oro){
        datos->oro = pokemon;
    }

    return true;
}

bool buscar_plata(void* elemento_1, void* elemento_2){
    pokemon_t* pokemon = elemento_1;
    datos_t* datos = elemento_2;

    if(pokemon > datos->plata && pokemon != datos->oro){
        datos->plata = pokemon;
    }

    return true;
}

bool buscar_bronce(void* elemento_1, void* elemento_2){
    pokemon_t* pokemon = elemento_1;
    datos_t* datos = elemento_2;

    if(pokemon > datos->bronce && pokemon != datos->oro && pokemon != datos->plata){
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

    lista_con_cada_elemento(pokemones, buscar_oro, &dato);
    lista_con_cada_elemento(pokemones, buscar_plata, &dato);
    lista_con_cada_elemento(pokemones, buscar_bronce, &dato);

    lista_insertar_en_posicion(podio, dato.oro, 0);
    lista_insertar_en_posicion(podio, dato.plata, 1);
    lista_insertar_en_posicion(podio, dato.bronce, 2);
} */

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

int main(){

    lista_t* pokemones = lista_crear();
    lista_t* podio = lista_crear();

    pokemon_t pikachu;
    pokemon_t charmander;
    pokemon_t squirtle;
    pokemon_t bulbasaur;

    pikachu.fuerza = 10;
    pikachu.rapidez = 5;
    pikachu.inteligencia = 30;

    charmander.fuerza = 20;
    charmander.rapidez = 10;
    charmander.inteligencia = 30;

    squirtle.fuerza = 30;
    squirtle.rapidez = 20;
    squirtle.inteligencia = 10;

    bulbasaur.fuerza = 20;
    bulbasaur.rapidez = 30;
    bulbasaur.inteligencia = 10;
    


    lista_insertar(pokemones, &pikachu);
    lista_insertar(pokemones, &charmander);
    lista_insertar(pokemones, &squirtle);
    lista_insertar(pokemones, &bulbasaur);

    podio_de_pokemones(pokemones, podio);

    pa2m_nuevo_grupo("Pruebas");
    pa2m_afirmar(lista_elemento_en_posicion(podio, 0) == &bulbasaur,"La medalla de oro es para bulbasaur");
    pa2m_afirmar(lista_elemento_en_posicion(podio, 1) == &squirtle,"La medalla de plata es para squirtle");
    pa2m_afirmar(lista_elemento_en_posicion(podio, 2) == &charmander,"La medalla de bronce es para charmarder");

    lista_destruir(pokemones);
    lista_destruir(podio);

    return pa2m_mostrar_reporte();
}