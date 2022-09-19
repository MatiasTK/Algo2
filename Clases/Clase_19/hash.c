#include "hash.h"

hash_t* hash_crear(){
    hash_t* hash = malloc(sizeof(hash_t));
    if(!hash){
        return NULL;
    }
    hash->cantidad_casilleros = 10;
    hash->casilleros = calloc(hash->cantidad_casilleros, sizeof(casillero_t));
    if(!hash->casilleros){
        free(hash);
        return NULL;
    }
    return hash;
}

size_t funcion_hash(const char* clave){
    size_t hash = 0;
    while(*clave){
        hash += *(clave++);
    }
    return hash;
}

casillero_t* crear_casillero(const char* clave, void* dato){
    casillero_t* casillero = malloc(sizeof(casillero_t));
    if(!casillero){
        return NULL;
    }
}

casillero_t* encadenar_colision(casillero_t* casillero, const char* clave, void* valor){
    if(!casillero){
        casillero_t* casillero_nuevo = crear_casillero(clave, valor);
        if(!casillero_nuevo){
            return NULL;
        }
        return casillero_nuevo;
    }

    if(strcmp(casillero->clave, clave) == 0){
        casillero->valor= valor;
        return casillero;
    }

    casillero->siguiente = encadenar_colision(casillero->siguiente, clave, valor);

    return casillero;
}

hash_t* hash_insertar(hash_t* hash, const char* clave, void* valor){
    if(!hash || !clave){
        return NULL;
    }

    size_t posicion = funcion_hash(clave) % hash->cantidad_casilleros;

    if(!hash->casilleros[posicion]){
        casillero_t* nuevo_casillero = crear_casillero(clave, valor);
        if(!nuevo_casillero){
            return NULL;
        }
        hash->casilleros[posicion] = nuevo_casillero;
        return hash;
    }

    hash->casilleros[posicion] = encadenar_colision(hash->casilleros[posicion], clave, valor); 
}

casillero_t* obtener(casillero_t* actual, const char* clave){
    if(!actual){
        return NULL;
    }

    if(strcmp(actual->clave, clave) == 0){
        return actual;
    }

    return obtener(actual->siguiente, clave);
}

void* hash_buscar(hash_t* hash, const char* clave){
    if(!hash || !clave){
        return NULL;
    }

    size_t posicion = funcion_hash(clave) % hash->cantidad_casilleros;

    return obtener(hash->casilleros[posicion], clave);
}