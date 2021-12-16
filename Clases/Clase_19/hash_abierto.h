#ifndef HASH_ABIERTO_H_
#define HASH_ABIERTO_H_

//! Ejemplo de hash abierto con zona de desborde. No es el que hay que implementar.

typedef struct{
    char* clave;
    void* valor;
    int estado; //? 0: libre, 1: ocupado, 2: eliminado
}casillero_t;

typedef struct {
    casillero_t* casilleros;
    size_t cantidad_de_casilleros;

    casillero_t* zona_desborde;
    size_t cantidad_de_casilleros_desborde;
}hash_t;

