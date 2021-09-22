#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector{
    void** elementos;
    size_t cantidad_elementos;
} vector_t;

vector_t* vector_crear(){
    return calloc(1,sizeof(vector_t)); //reserva memoria y pone todo en 0
}

vector_t* vector_agregar(vector_t* vector, void* elemento){
    if(!vector){
        return NULL;
    }

    void** vector_aux = realloc(vector->elementos,sizeof(void*)*(vector->cantidad_elementos+1));
    if(!vector_aux){
        return NULL;
    }

    vector->elementos = vector_aux;
    vector->elementos[vector->cantidad_elementos] = elemento;
    vector->cantidad_elementos++;
}

void vector_destruir(vector_t* vector){
    if(!vector){
        return;
    }
    free(vector->elementos);
    free(vector);
}

void** vector_elementos(vector_t* vector){
    if(!vector){
        return NULL;
    }
    return vector->elementos;
}

size_t vector_cantidad(vector_t* vector){
    if(!vector){
        return 0;
    }
    return vector->cantidad_elementos;
}

size_t vector_por_cada_elemento(vector_t* vector,void (*funcion)(void*)){

    if(!vector){
        return 0;
    }

    int** elementos = (int**)vector_elementos(vector);
    size_t cantidad_elementos_recorridos = 0;
    for (size_t i = 0; i < vector_cantidad(vector); i++){
        funcion(elementos[i]);
        cantidad_elementos_recorridos++;
    }

    return cantidad_elementos_recorridos;
}

void mostrar_entero(void* entero_p){
    int* pentero = entero_p;
    printf("Elemento: %d\n",*pentero);
}

int main(int argc, char const *argv[]){
    
    vector_t* vector = vector_crear();

    vector_t* vector_original = vector;

    int a=0,b=5,c=4,d=3,e=9;

    vector = vector_agregar(vector,&a);
    vector = vector_agregar(vector,&b);
    vector = vector_agregar(vector,&c);
    vector = vector_agregar(vector,&d);
    vector = vector_agregar(vector,&e);

    if(vector == NULL){
        vector_destruir(vector_original);
        return -1;       
    }
    vector = vector_original;

    vector_por_cada_elemento(vector,mostrar_entero);
   
    vector_destruir(vector_original);

    return 0;
}
