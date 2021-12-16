#include "heap.h"
#include <stdio.h>

// FUNCIÓN PÚBLICA
heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor) {
    if (!comparador) return NULL;
    heap_t* heap = calloc(1, sizeof(heap_t));
    if (!heap) return NULL;
    heap->comparador = comparador;
    heap->destructor = destructor;
    return heap;
}

/*
* Pre: n debe ser una posición válida del heap.
* Post: Devuelve la posición del padre de la posición del heap recibida.
*/
int heap_pos_padre(int n) {
    return (n-1)/2;
}

/*
* Pre: n debe ser una posición válida del heap.
* Post: Devuelve la posición del hijo izquierdo de la posición del heap recibida.
*/
int heap_pos_hijo_izq(int n) {
    return 2*n+1;
}

/*
* Pre: n debe ser una posición válida del heap.
* Post: Devuelve la posición del hijo derecho de la posición del heap recibida.
*/
int heap_pos_hijo_der(int n) {
    return 2*n+2;
}

// FUNCIÓN PÚBLICA
bool heap_vacio(heap_t* heap) {
    if (!heap) return true;
    return (heap->tope == 0);
}

/*
* Pre: El vector debe ser válido, a y b deben ser >= 0.
* Post: Intercambia los elementos en las posiciones recibidas del vector (a,b).
*/
void swap(void** vector, int a, int b) {
    void* aux = vector[a];
    vector[a] = vector[b];
    vector[b] = aux;
}


/*
* Pre: El comparador y el heap deben ser válidos, y n una posición 
    válida del heap.
* Post: Flota el elemento en la posición n del heap hacia arriba, según 
    lo determine el comparador. Si el elemento n es menor que su padre, 
    este flota hacia arriba, intercambiándo su posición.
*/
void sift_up(heap_t* heap, int n, heap_comparador comparador) {
    if(n == 0) // No tiene padre
        return;

    int pos_padre = heap_pos_padre(n);

    if (comparador(heap->vector[n], heap->vector[pos_padre]) < 0) {
        swap(heap->vector, n, pos_padre);
        sift_up(heap, pos_padre, comparador);
    }
}

/*
* Pre: El comparador y el heap deben ser válidos, y n una posición 
    válida del heap.
* Post: Hunde el elemento en la posición n del heap, hacia abajo, según 
    el comparador. Si el elemento n es mayor que alguno de sus hijos, este se 
    hunde, intercambiándose con su hijo menor.
*/
void sift_down(heap_t* heap, int n, heap_comparador comparador) {

    int pos_hijo_izq = heap_pos_hijo_izq(n);
    int pos_hijo_der = heap_pos_hijo_der(n);
    
    // Si no tiene hijo izquierdo, tampoco tiene derecho, pues el heap es casi completo.
    if(pos_hijo_izq >= (heap->tope)) {
        return;
    }

    int comparacion;
    int pos_intercambio = pos_hijo_izq;

    if(pos_hijo_der < (heap->tope))  { // Tiene ambos hijos 
        comparacion = comparador(heap->vector[pos_hijo_izq], heap->vector[pos_hijo_der]);
        if (comparacion >= 0) // Hijo derecho es menor
            pos_intercambio = pos_hijo_der;
    } // Sino, tiene un solo hijo, que es el izquierdo

    comparacion = comparador(heap->vector[n], heap->vector[pos_intercambio]); // Comparo el actual con su hijo menor
    if (comparacion > 0) { // El actual (n) se hunde por ser mayor
        swap(heap->vector, n, pos_intercambio);
        sift_down(heap, pos_intercambio, comparador);
    }
}

// FUNCIÓN PÚBLICA
int heap_insertar(heap_t* heap, void* elemento) {
    if (!heap) return ERROR;
    void** nuevo_aux = realloc(heap->vector, (((heap->tope)+1))*sizeof(void*) ); //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (!nuevo_aux)
        return ERROR;
    
    (heap->tope)++;
    (heap->vector) = nuevo_aux;

    heap->vector[(heap->tope)-1] = elemento;

    // Sift up del elemento a la posición deseada
    sift_up(heap, (int)(heap->tope)-1, heap->comparador);

    return EXITO;
}

// FUNCIÓN PÚBLICA
void* heap_extraer_raiz(heap_t* heap) {
    if (!heap || heap->tope == 0)
        return NULL;
    
    void* raiz = heap->vector[0];    
    heap->vector[0] = heap->vector[(heap->tope)-1];
    (heap->tope)--;

    if (heap->tope > 0) {
        void** aux = realloc(heap->vector, (heap->tope)*sizeof(void*)); //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (!aux) return NULL;
        heap->vector = aux;
    }

    if (heap->tope > 0)
        sift_down(heap, 0, heap->comparador);

    return raiz;
}

/*
* Pre: -
* Post: Invoca al destructor (si lo hay) con cada elemento del heap y libera el elemento.

void destruir_cada_elemento_heap(void** vector, heap_liberar_elemento destructor, size_t tope, int n) {
    
    if (n < tope) {
        destruir_cada_elemento_heap(vector, destructor, tope, n+1);
    }
    if (destructor && n < tope)
        (destructor)(vector[n]);
    
}*/

// FUNCIÓN PÚBLICA
void heap_destruir(heap_t* heap) {
    if (heap) {
        if(heap->vector) {
            if (heap->destructor) {
                for(int i = 0; i < (heap->tope); i++) {
                    (heap->destructor)(heap->vector[i]);
                }
            }
            //destruir_cada_elemento_heap(heap->vector, heap->destructor, heap->tope, 0);
            free(heap->vector);
        }
        free(heap);
    }
}