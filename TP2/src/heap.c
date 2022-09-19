#include "heap.h"
#include <stdbool.h>

#define EXITO 0
#define ERROR -1

heap_t* heap_crear(heap_comparador_t comparador, heap_destructor_t destructor){
    if(!comparador){
        return NULL;
    }

    heap_t* heap = calloc(1, sizeof(heap_t));
    if(!heap){
        return NULL;
    }

    heap->comparador = comparador;
    heap->destructor = destructor;

    return heap;
}

/*
* PRE: Recibe un posicion del heap
* POST: Devuelve el padre de esa posicion del heap.
*/
int buscar_pos_padre(int pos){
    return (pos-1)/2;
}

/*
* PRE: El comparador y el heap deben ser validos.
* POST: "Mueve" el elemento de la posicion recibida del heap hacia arriba segun lo indique el comparador.
*/
void sift_up(heap_t* heap, int pos, heap_comparador_t comparador){
    if(!heap || !comparador || pos == 0){
        return;
    }

    int pos_padre = buscar_pos_padre(pos);

    if(comparador(heap->array[pos], heap->array[pos_padre]) < 0){
        void* aux = heap->array[pos];
        heap->array[pos] = heap->array[pos_padre];
        heap->array[pos_padre] = aux;
        sift_up(heap, pos_padre, comparador);
    }
}

int heap_insertar(heap_t* heap, void* elemento){
    if(!heap){
        return ERROR;
    }

    void** nuevo_array = realloc(heap->array, sizeof(void*) * (heap->tope + 1));
    if(!nuevo_array){
        return ERROR;
    }

    heap->tope++;
    heap->array = nuevo_array;
    heap->array[(heap->tope)-1] = elemento;

    sift_up(heap, (int)(heap->tope)-1, heap->comparador);
   
    return EXITO;
}

/*
* PRE: Recibe un comparador y un heap valido.
* POST: "Mueve" el elemento de la posicion recibida del heap hacia abajo segun lo indique el comparador.
*/
void sift_down(heap_t* heap, size_t pos, heap_comparador_t comparador){
    if(!heap || !comparador || pos >= heap->tope){
        return;
    }

    size_t hijo_izq = 2 * pos + 1;
    size_t hijo_der = 2 * pos + 2;

    if(hijo_izq >= heap->tope){
        return;
    }

    size_t hijo_mas_grande = hijo_izq;
    if(hijo_der < heap->tope){
        int comparacion = comparador(heap->array[hijo_izq], heap->array[hijo_der]);
        if(comparacion >= 0){
            hijo_mas_grande = hijo_der;
        }
    }

    int comparacion = comparador(heap->array[pos], heap->array[hijo_mas_grande]);
    if(comparacion > 0){
        void* aux = heap->array[pos];
        heap->array[pos] = heap->array[hijo_mas_grande];
        heap->array[hijo_mas_grande] = aux;
        sift_down(heap, hijo_mas_grande, comparador);
    }
}

void* heap_extraer_raiz(heap_t* heap){
    if(!heap || heap->tope == 0){
        return NULL;
    }

    void* raiz = heap->array[0];
    void* ultimo = heap->array[(heap->tope)-1];
    heap->array[0] = ultimo;
    heap->tope--;

    if(heap->tope > 0){
        void** nuevo_array = realloc(heap->array, sizeof(void*) * heap->tope);
        if(!nuevo_array){
            return NULL;
        }
        heap->array = nuevo_array;
    }

    if(heap->tope > 0){
        sift_down(heap, 0, heap->comparador);
    }

    return raiz;
}

size_t heap_cantidad(heap_t* heap){
    if(!heap){
        return 0;
    }

    return heap->tope;
}

bool heap_esta_vacio(heap_t* heap){
    if(!heap){
        return true;
    }

    return heap->tope == 0;
}

void heap_destruir(heap_t* heap){
    if(!heap){
        return;
    }

    if(heap->destructor){
        for(size_t i = 0; i < heap->tope; i++){
            heap->destructor(heap->array[i]);
        }
    }

    free(heap->array);
    free(heap);
}