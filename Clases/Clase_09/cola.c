#include "cola.h"
#include "lista.h"

#define VALOR_ARBITRARIO 7

struct _cola_t{
    void** elementos;
    size_t primero,tope,tamanio;
};

cola_t* cola_crear(){
    cola_t* cola = calloc(1,sizeof(cola_t));
    if(!cola){
        return NULL;
    }
    cola->tamanio = VALOR_ARBITRARIO;
    cola->elementos = malloc(cola->tamanio * sizeof(void*));
    if(!cola->elementos){
        free(cola);
        cola = NULL;
    }

    return cola;
}

cola_t* cola_encolar(cola_t* cola, void* elemento){

    return NULL;
}

void* cola_desencolar(cola_t* cola){
    return NULL;
}

void* cola_frente(cola_t* cola){
    return NULL;
}

size_t cola_tamanio(cola_t* cola){
    return 0;
}

bool cola_vacia(cola_t* cola){
    return false;
}

void cola_destruir(cola_t* cola){

}
