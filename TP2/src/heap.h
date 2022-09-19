#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <stdbool.h>

//* Destructor, se lo invoca al finalizar el programa enviandole por parametro el elemento.
typedef void (*heap_destructor_t)(void *);

/* 
* Comparador de elementos, recibe dos elementos del heap y devuelve un entero.
* Devuelve 0 en caso de que los elementos sean iguales
* Deuvelve un entero negativo si el primer elemento es menor que el segundo
* Devuelve un entero positivo si el primer elemento es mayor que el segundo
*/
typedef int (*heap_comparador_t)(void*, void*);

typedef struct heap{
    void** array;
    size_t tope;
    heap_comparador_t comparador;
    heap_destructor_t destructor;
} heap_t;

/* 
* Crea el heap reservando memoria.
* Comparador es una funcion de comparacion de elementos en el heap, debe ser un puntero a la funcion, NO puede ser NULL.
* Destructor es una funcion de destruccion de elementos en el heap sera invocado para destruir el heap, puede ser NULL.
* Devuelve un puntero al heap creado o NULL en caso de error.
*/
heap_t* heap_crear(heap_comparador_t comparador, heap_destructor_t destructor);

/* 
* Inserta un elemento en el heap.
* Devuelve -1 en caso de error o 0 en caso de exito.
*/
int heap_insertar(heap_t* heap, void* elemento);

/* 
* Extrae la raiz del heap utilizando el comparador.
* Devuelve obtenida o NULL en caso de error.
*/
void* heap_extraer_raiz(heap_t* heap);

/* 
* Devuelve la cantidad de elementos almacenados en el heap o 0 en caso de error.
*/
size_t heap_cantidad(heap_t* heap);

/* 
* Devuelve true si el heap esta vacio o false en caso contrario.
*/
bool heap_esta_vacio(heap_t* heap);

/*  
 * Destruye el heap liberando la memoria reservada y asegurandose de
 * invocar la funcion destructora con cada elemento almacenado en el
 * heap.
*/
void heap_destruir(heap_t* heap);

#endif // __HEAP_H__