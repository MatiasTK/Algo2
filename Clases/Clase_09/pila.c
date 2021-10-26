#include "pila.h"
#include "lista.h"

#define MAX_ELEMENTOS 10

struct _pila_t{
    void* elementos[MAX_ELEMENTOS];
    size_t tope;
};

pila_t* pila_crear(){
    return calloc(1,sizeof(pila_t));
}

pila_t* pila_apilar(pila_t* pila, void* elemento){
    if(pila->tope < MAX_ELEMENTOS){
        pila->elementos[pila->tope] = elemento;
        pila->tope++;
        return pila;
    }
    return NULL;
}

void* pila_desapilar(pila_t* pila){
    return NULL;
}

void* pila_tope(pila_t* pila){
    if(pila_vacia(pila)){
        return NULL;
    }

    return pila->elementos[pila->tope-1];
}

size_t pila_tamanio(pila_t* pila){
    return pila->tope;
}

bool pila_vacia(pila_t* pila){
    if(pila->tope == 0 || !pila){
        return true;
    }
    return false;
}

void pila_destruir(pila_t* pila){
    free(pila);
}
