#ifndef _AVENTURA_H_
#define _AVENTURA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "batallas.h"
#include "TDAs/lista/lista.h"
#include "TDAs/abb/abb.h"
#include "TDAs/heap/heap.h"
#include "herramientas_graficas.h"

#define ERROR -1
#define EXITO 0

#define MAX_LINEA 100
#define MAX_NOMBRE 100
#define MAX_RUTA 100
#define MAX_POKEMONES_BATALLA 6
#define MAX_FUNCIONES 5
#define MAX_BONIFICACION 63
#define MIN_ENTRENADORES 2

#define NATURAL 'l'
#define ENTERO 'i'
#define RACIONAL 'f'
#define CARACTER 'c'
#define STRING 's'

#define FORMATO_INCIAL "%c;%[^\n]\n"
#define FORMATO_GIMNASIO "%[^;];%i;%i\n"
#define FORMATO_ENTRENADOR "%[^\n]\n"
#define FORMATO_POKEMON "%[^;];%i;%i;%i\n"

#define DATOS_INICIALES 2
#define DATOS_GIMNASIO 3
#define DATOS_ENTRENADOR 1
#define DATOS_POKEMON 4

#define GIMNASIO 'G'
#define LIDER 'L'
#define ENTRENADOR 'E'
#define POKEMON 'P'

/*
 * Funcion de batalla. Se encarga de determinar quien gana la batalla
 * entre dos pokemones.
 * Recibe dos punteros genericos validos a pokemon_t.
 * Devuelve 1 si gana el primer pokemon, -1 si gana el segundo.
 */
typedef int (*funcion_batalla)(void*, void*);

typedef struct pokemon{
    char nombre[MAX_NOMBRE];
    int velocidad;
    int defensa;
    int ataque;
}pokemon_t;

typedef struct entrenador{
    char nombre[MAX_NOMBRE];
    lista_t* pokemones; //lista simplemente enlazada
}entrenador_t;

typedef struct gimnasio{
    char nombre[MAX_NOMBRE];
    int dificultad;
    int id_funcion;
    funcion_batalla funcion_de_batalla;
    lista_t* entrenadores; //lista simplemente enlazada
}gimnasio_t;

typedef struct personaje{
    char nombre[MAX_NOMBRE];
    lista_t* caja; //lista simplemente enlazada
    lista_t* party; //lista simplemente enlazada
}personaje_t;

typedef struct juego{
    heap_t* gimnasios;
    personaje_t* personaje;
}juego_t;

/*
 * El reemplazo de scanf. Se encarga de inicializar la variable segun
 * lo que lea del stdin y el tipo de variable que se especifique.
 * Recibe un puntero generico valido y un caracter inicializado.
 * Devuelve 0 si pudo inicializar la variable o -1 si no pudo.
 */
int leer_input(void* variable, char tipo_variable);

/* 
 * Reserva la cantidad de memoria necesaria para el tipo de dato 'gimnasio_t'
 * Devuelve una direccion de memoria o NULL en caso de error.
 */
gimnasio_t* crear_gimnasio();

/* 
 * Reserva la cantidad de memoria necesaria para el tipo de dato 'entrenador_t'
 * Devuelve una direccion de memoria o NULL en caso de error.
 */
entrenador_t* crear_entrenador();

/* 
 * Reserva la cantidad de memoria necesaria para el tipo de dato 'pokemon_t'
 * Devuelve una direccion de memoria o NULL en caso de error.
 */
pokemon_t* crear_pokemon();

/* 
 * Reserva la cantidad de memoria necesaria para el tipo de dato 'personaje_t'
 * Devuelve una direccion de memoria o NULL en caso de error.
 */
personaje_t* crear_personaje();

/* 
 * Compara los gimnasios que se insertan en el heap de gimnasios.
 * Recibe dos punteros validos a gimnasio.
 * Devuelve: 1 si el gim1 es mayor al gim2.
 *          -1 si el gim1 es menor al gim2.
 *           0 si son iguales o hay error.
 */
int comparar_gimnasios(void* gim1, void* gim2);

/* 
 * Libera la memoria reservada para el tipo de dato 'pokemon_t'.
 * Recibe un puntero valido a pokemon.
 * Devuelve la memoria utilizada liberada.
 */
void destruir_pokemon(void* pokemon);

/* 
 * Libera la memoria reservada par el tipo de dato 'entrenador_t'.
 * Recibe un puntero valido a entrenador.
 * Devuelve la memoria utilizada liberada.
 */
void destruir_entrenador(void* entrenador);

/* 
 * Libera la memoria reservada para el tipo de dato 'gimnasio_t'
 * Recibe un puntero valido a gimnasio.
 * Devuelve la memoria utilizada liberada.
 */
void destruir_gimnasio(void* gimnasio);

/* 
 * Libera la memoria reservada para el tipo de dato 'personaje_t'
 * Recibe un puntero valido a personaje.
 * Devuelve la memoria utilizada liberada.
 */
void destruir_personaje(void* personaje);

/* 
 * Carga los gimnasios en el heap de gimnasios segun el archivo que reciba.
 * Recibe un puntero valido a heap y un puntero a string valido con el nombre del archivo del gimnasio
 * Devuelve: 0 si pudo cargar el gimnasio.
 *          -1 si no pudo cargar el gimnasio.
 */
int cargar_gimnasio(heap_t* gimnasios, const char* arch_gimnasio);

/*
 * Carga todos los datos del personaje principal segun el archivo que reciba.
 * Recibe un puntero valido a personaje y un puntero a string valido con el nombre del archivo del personaje.
 * Devuelve: 0 si pudo cargar al personaje.
 *          -1 si no pudo cargar al personaje.
 */
int cargar_personaje(personaje_t* personaje, const char* arch_personaje);

/*
 * Crea un nuevo pokemon copiando sus datos de otro pokemon.
 * Recibe un puntero valido a pokemon_t y sus campos inicializados.
 * Devuelve un nuevo puntero a pokemon_t o NULL en caso de error.
 */
pokemon_t* crear_pokemon_copiado(pokemon_t* pokemon_a_copiar);

#endif /* _AVENTURA_H_ */