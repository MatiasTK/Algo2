#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1
#define EXITO 0


/*
 * Comparador de elementos. Recibe dos elementos del heap y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
typedef int (*heap_comparador)(void*, void*);

/*
 * Destructor de elementos. Al destruir el heap, se invoca al destructor,
 * pasandole el elemento.
 */
typedef void (*heap_liberar_elemento)(void*);


typedef struct heap {
    void** vector;
    size_t tope;
    heap_comparador comparador;
    heap_liberar_elemento destructor;
} heap_t;

/*
* Pre: El comparador debe ser un puntero a la función que compara los elementos del heap.
    El destructor será invocado cuando se destruya el heap con cada elemento del mismo. Si no
    se necesita, se pasa NULL.
* Post: Crea un heap con el comparador y destructor recibidos. Si falla su creación, devuelve NULL.
    Sino, un puntero al heap creado.
*/
heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor);

/*
* Pre: -
* Post: Devuelve true si el heap no tiene elementos o es NULL. Sino, devuelve false.
*/
bool heap_vacio(heap_t* heap);

/*
* Pre: -
* Post: Inserta el elemento recibido en el heap, de acuerdo al comparador del mismo.
*/
int heap_insertar(heap_t* heap, void* elemento);

/*
* Pre: -
* Post: Devuelve la raíz del heap de acuerdo al resultado del comparador del mismo.
*/
void* heap_extraer_raiz(heap_t* heap);

/*
* Pre: -
* Post: Libera la memoria reservada por el heap, invocando al destructor 
    con cada elemento del mismo.
*/
void heap_destruir(heap_t* heap);