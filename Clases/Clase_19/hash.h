#ifndef HASH_H_
#define HASH_H_

#include <stdlib.h>

typedef struct casillero{
    char* clave;
    void* valor;
    struct casillero* siguiente;
} casillero_t;

typedef struct{
    casillero_t* casilleros;
    size_t cantidad_casilleros;
} hash_t;

hash_t* hash_crear();

hash_t* hash_insertar(hash_t* hash, const char* clave, void* valor);

void* hash_buscar(hash_t* hash, const char* clave);

void hash_destruir(hash_t* hash);