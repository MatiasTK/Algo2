#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define EXITO 0
#define ERROR -1

/* 
 * Se encarga de comparar elementos del heap.
 * Recibe dos punteros validos con los elementos a comparar.
 * Devuelve: 1 si el primero elemento es mayor.
 *          -1 si el segundo elemento es mayor.
 *           0 si los elementos son iguales.
 */
typedef int (*heap_comparador)(void*, void*);

/* 
 * Se encarga de liberar los elementos insertados por el usuario
 * los cuales son desconocidos por la implementacion.
 * Recibe un puntero a elemento.
 * Devuelve el elemento liberado.
 */
typedef void (*heap_liberar_elemento)(void*);

typedef struct heap{
    void** vector;
    size_t tope;
    heap_comparador comparador;
    heap_liberar_elemento destructor;
} heap_t;

/* 
 * Reserva la cantidad de memoria necesaria para un struct de tipo heap_t.
 * Recibe un puntero a funcion de comparador valido y uno a destructor, no
 * necesariamente valido.
 * Devuelve un puntero a heap_t o NULL en caso de error.
 */
heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor);

/* 
 * Se encarga de insertar un elemento en el heap, y luego acomodarlo
 * segun corresponda.
 * Recibe un puntero a heap valido y un puntero a elemento.
 * Devuelve 0 si se pudo agregar el elemento, o -1 en caso de error.
 */

int heap_insertar(heap_t* heap, void* elemento);

/* 
 * Se encarga de extraer el elemento que está en la raiz del heap, y luego
 * reacomodar el heap.
 * Recibe un puntero a heap valido.
 * Devuelve el elemento que está en la raiz o NULL en caso de error.
 */
void* heap_extraer_raiz(heap_t* heap);

/*
 * Se encarga de liberar la memoria reservada para el heap.
 * Recibe un puntero a heap valido.
 * Devuelve el heap y todos sus elementos liberados.
 */
void heap_destruir(heap_t* heap);

/*
 * Se encarga de determinar la cantidad de elementos en el heap.
 * Recibe un puntero a heap.
 * Devuelve la cantidad de elementos en el heap.
 */
size_t heap_elementos(heap_t* heap);

/*
 * Se encarga de determina si el heap esta vacio o no.
 * Recibe un puntero a heap.
 * Devuelve true si esta vacio, o false en caso contrario.
 */
bool heap_vacio(heap_t* heap);

#endif /* _HEAP_H__ */