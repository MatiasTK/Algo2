#include <stdlib.h>
#include <stdio.h>

#define MAX_HEAP 100

//* Heap de tipo MAXIMAL
struct heap{
    int elementos[MAX_HEAP];
    size_t tamanio;
};

void heap_inicializar(struct heap* heap){
    heap->tamanio = 0;
}

void swap(int* elementos,size_t primero, size_t segundo){
    int aux = elementos[primero];
    elementos[primero] = elementos[segundo];
    elementos[segundo] = aux;
}

void sift_up(int* elementos,int posicion){

    if(posicion == 0){
        return;
    }

    int posicion_padre = (posicion-1)/2;

    int elemento = elementos[posicion];
    int elemento_padre = elementos[posicion_padre];

    if(elemento > elemento_padre){
        swap(elementos,posicion,posicion_padre);
        sift_up(elementos,posicion_padre);
    }
}

/*
* PRE:
* POST: 0 en caso de error, 1 en caso de exito.
*/
size_t heap_insertar(struct heap* heap,int elemento){
    if(heap->tamanio == MAX_HEAP){
        return 0;
    }
    heap->elementos[heap->tamanio] = elemento;
    heap->tamanio++;
    
    sift_up(heap->elementos,heap->tamanio-1);

    heap->tamanio++;

    return 1;
}

void sift_down(int* elementos,size_t posicion,size_t ultimo_elemento){
    size_t posicion_izquierda = 2*posicion+1;
    size_t posicion_derecha = 2*posicion+2;
    size_t posicion_a_intercambiar;

    if(posicion_izquierda > ultimo_elemento){ //Si es hoja(No tiene ningun hijo) no tengo que hacer sift_down
        return;
    }

    //Si llega aca tiene 1 hijo

    if(posicion_derecha > ultimo_elemento){ // Sigue teniendo un hijo entonces tengo dos veces el hijo izquierdo
        posicion_derecha = posicion_izquierda;
    }

    int elemento = elementos[posicion];
    int izquierdo = elementos[posicion_izquierda];
    int derecho = elementos[posicion_derecha];

    if(derecho > izquierdo){
        posicion_a_intercambiar = posicion_derecha;
    }else{
        posicion_a_intercambiar = posicion_izquierda;
    }

    if(elementos[posicion_a_intercambiar] > elemento){
        swap(elementos,posicion,posicion_a_intercambiar);
        sift_down(elementos,posicion_a_intercambiar,ultimo_elemento);
    }

}

int extraer_raiz(struct heap* heap){
    if(heap->tamanio == 0){
        return -1;
    }
    int raiz = heap->elementos[0];

    heap->tamanio--;
    heap->elementos[0] = heap->elementos[heap->tamanio];

    if(heap->tamanio > 0){
        sift_down(heap->elementos,0,heap->tamanio);
    }

    return raiz;
}


void heapify(int* elementos,size_t cantidad){
    if(cantidad == 0){
        return;
    }

    for(size_t pos = (cantidad-2)/2; pos > 0; pos--){
        sift_down(elementos,pos,cantidad-1);
    }
    sift_down(elementos,0,cantidad-1);
}

//!OPCIONAL
void heapify_desde_el_principio(int* elementos,size_t cantidad){
    if(cantidad == 0){
        return;
    }

    for(size_t pos = 0; pos < cantidad; pos++){
        sift_up(elementos,pos);
    }
}

void heap_sort_rec(int* elementos,size_t cantidad){
    if(cantidad <= 1){
        return;
    }

    swap(elementos,0,cantidad-1);
    cantidad--;
    sift_down(elementos,0,cantidad-1);
    heap_sort_rec(elementos,cantidad);
}

void heap_sort(int* elementos,size_t cantidad){
    heapify(elementos,cantidad);
    
    heap_sort_rec(elementos,cantidad);
}

int main(int argc, char const *argv[]){
    size_t cantidad = 10;
    int elementos[cantidad];

    for(size_t i = 0; i < cantidad; i++){
        elementos[i] = i;
    }

    printf("========================\n");
    printf("Creo el vector\n");
    printf("[ ");
    for(size_t i = 0; i < cantidad;i++){
        printf("%i ",elementos[i]);
    }
    printf(" ]");
    printf("\n========================\n");

    heapify(elementos,cantidad);

    printf("Luego de aplicar Heapify al vector\n");
    printf("[ ");
    for(size_t i = 0; i < cantidad;i++){
        printf("%i ",elementos[i]);
    }
    printf(" ]");
    printf("\n========================\n");

    heap_sort(elementos,cantidad);

    printf("Luego de aplicar Heap Sort al vector\n");
    printf("[ ");
    for(size_t i = 0; i < cantidad;i++){
        printf("%i ",elementos[i]);
    }
    printf(" ]");
    printf("\n========================\n");

    return 0;
}
