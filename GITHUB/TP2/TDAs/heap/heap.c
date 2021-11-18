#include "heap.h"

/* 
 * Se encarga de calcular la posicion del padre
 * del  elemento "n" del heap.
 * Recibe un numero entero positivo
 * Devuelve un numero entero positivo.
 */
int posicion_padre(int n){
    return (n-1)/2;
}

/* 
 * Se encarga de calcular la posicion del hijo
 * izquierdo del  elemento "n" del heap.
 * Recibe un numero entero positivo
 * Devuelve un numero entero positivo.
 */
int posicion_hijo_izquierdo(int n){
    return (2*n)+1;
}

/* 
 * Se encarga de calcular la posicion del hijo
 * derecho del  elemento "n" del heap.
 * Recibe un numero entero positivo
 * Devuelve un numero entero positivo.
 */
int posicion_hijo_derecho(int n){
    return (2*n)+2;
}

/* 
 * Se encarga de intercambiar los elementos segun las posiciones
 * indicadas en 'i' y 'j'.
 * Recibe dos numeros enteros positivos y un vector.
 * Devuelve el vector con el intercambio realizado.
 */
void swap(void** vector, int i, int j){
    
    void* aux = vector[i];
    vector[i] = vector[j];
    vector[j] = aux;
}

/* 
 * Se encarga de mover el elemento de posicion 'n' indicado por el heap
 * hasta que la posicion que le corresponde.
 * Recibe un puntero a heap valido y un numero entero positivo.
 * Devuelve el vector del heap ordenado segun corresponda.
 */
void sift_up(heap_t* heap, int n){
    
    if (!heap || (*heap).tope == 0) return;
    
    int padre = posicion_padre(n);

    if (padre < 0) return;

    if ((*heap).comparador((*heap).vector[n], (*heap).vector[padre]) < 0){
        swap((*heap).vector, n, padre);
        sift_up(heap, padre);
    }
}

/* 
 * Se encarga de mover el elemento de posicion 'n' indicado por el heap
 * hasta que la posicion que le corresponde.
 * Recibe un puntero a heap valido y un numero entero positivo.
 * Devuelve el vector del heap ordenado segun corresponda.
 */
void sift_down(heap_t* heap, int n){
    
    if (!heap || (*heap).tope == 0) return;

    int derecha = posicion_hijo_derecho(n);
    int izquierda = posicion_hijo_izquierdo(n);
    int menor = izquierda;

    if (izquierda >= (*heap).tope) return;

    if (derecha < (*heap).tope){
        if ((*heap).comparador((*heap).vector[derecha], (*heap).vector[izquierda]) < 0)
            menor = derecha;
    }

    if ((*heap).comparador((*heap).vector[n], (*heap).vector[menor]) > 0){
        swap((*heap).vector, n, menor);
        sift_down(heap, menor);
    }
}

heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor){

    if (!comparador) return NULL;

    heap_t* heap = malloc(sizeof(heap_t));
    if (heap){
        (*heap).vector = NULL;
        (*heap).comparador = comparador;
        (*heap).destructor = destructor;
        (*heap).tope = 0;
    }
    return heap;
}

int heap_insertar(heap_t* heap, void* elemento){

    if (heap){
        void** vector = realloc((*heap).vector, ((*heap).tope+1)*sizeof(void*));
        if (vector){
            (*heap).vector = vector;
            (*heap).vector[(*heap).tope] = elemento;
            (*heap).tope++;
            sift_up(heap, (int)(*heap).tope-1);
            return EXITO;
        }
    }

    return ERROR;
}

void* heap_extraer_raiz(heap_t* heap){
    
    if (!heap || (*heap).tope == 0) return NULL;

    void* elemento = (*heap).vector[0];

    swap((*heap).vector, 0, (int)(*heap).tope-1);
    (*heap).tope--;

    if ((*heap).tope > 0)
        sift_down(heap, 0);

    return elemento;
}

void heap_destruir(heap_t* heap){
    
    if (heap){
        if ((*heap).vector){
            if ((*heap).destructor){
                for (int i = 0; i < (*heap).tope; i++)
                    (*heap).destructor((*heap).vector[i]);
            }
            free((*heap).vector);
        }
        free(heap);
    }
}

size_t heap_elementos(heap_t* heap){

    if (!heap) return 0;

    return ((*heap).tope);
}

bool heap_vacio(heap_t* heap){
    return (!heap || (*heap).tope == 0);
}