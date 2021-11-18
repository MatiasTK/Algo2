//EJ -> https://i.imgur.com/h4xfaXx.png
//! Esta re dificil este XD
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    Compartimiento principal;
    Compartimiento bolsillos[5];
}Mochila;

typedef struct{
    size_t capacidad;
    size_t capacidad_utilizada;
    Elemento* elementos;
}Compartimiento;

typedef struct{
    size_t capacidad_necesaria;
    void* elemento; // opcional?
    Elemento* siguiente;
}Elemento;

Mochila* mochila_crear(){
    Mochila* mochila = calloc(1, sizeof(Mochila));
    if(!mochila){
        return NULL;
    }
}

int Mochila_agregar_elemento(Mochila* mochi, void* elemento, size_t capacidad){
    if(!mochi || !elemento){
        return -1;
    }
    if(mochi->capacidad - mochi->capacidad_utilizada < capacidad){
        return -1;
    }
    Elemento* nuevo_elemento = calloc(1, sizeof(Elemento));
    if(!nuevo_elemento){
        return -1;
    }
    nuevo_elemento->elemento = elemento;
    nuevo_elemento->capacidad_necesaria = capacidad;
    nuevo_elemento->siguiente = mochi->elementos;
    mochi->elementos = nuevo_elemento;
    mochi->capacidad_utilizada += capacidad;
    return 0;
}