#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

// Estructura de solo inicio no tiene tamanio ni fin
typedef struct _nodo{
    void* elemento;
    struct nodo* siguiente;
}lista_t;

lista_t* lista_crear(){
    return NULL; // Para crearla vacia significa que no existe
}

lista_t* lista_insertar(lista_t* lista, void* elemento){
    if(!lista){ // Si no hay lista significa que queres crear un nodo
        lista_t* nuevo = calloc(1,sizeof(lista_t));
        if(!nuevo){
            return NULL;
        }
        nueva->elemento = elemento;
        return nuevo;
    }
    //Si no estaba vacia recorro la lsita hasta el final y añado el nuevo
    //1er forma
    lista_t* actual = lista;
    while(actual->siguiente){// Itera hasta el elemento q apunta a nULL
        actual = actual->siguiente;
    }
    lista_t* nuevo = calloc(1,sizeof(lista_t));
    if(!nuevo){
        return NULL;
    }
    nueva->elemento = elemento;
    actual->siguiente = nuevo;
    return nuevo;
    //2Da forma -> Mejor
    if(!lista){ // Si no hay lista significa que queres crear un nodo
        lista_t* nuevo = calloc(1,sizeof(lista_t));fff
        if(!nuevo){
            return NULL;
        }
        nueva->elemento = elemento;
        return nuevo;
    }
    lista->siguiente = lista_insertar(lista->siguiente,elemento);
}

void* lista_quitar(lista_t* lista){
    if(!lista){
        return NULL;
    }
    if(!lista->siguiente){
        free(lista);
        return NULL;
    }
    lista->siguiente = lista_quitar(lista->siguiente);
    return lista;
}

void* lista_quitar_de_posicion(lista_t* lista, size_t posicion){
    return NULL;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
    return NULL;
}

void* lista_primero(lista_t* lista){
    return NULL;
}

void* lista_ultimo(lista_t* lista){
    return NULL;
}

bool lista_vacia(lista_t* lista){
    if(lista == NULL){
        return true;
    }
    return false;
}

size_t lista_tamanio(lista_t* lista){
    if(!lista){
        return 0;
    }
    return 1 + lista_tamanio(lista->siguiente);
}

void lista_destruir(lista_t* lista){
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
    return NULL;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
    return false;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){
    return false;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
    return NULL;
}

void lista_iterador_destruir(lista_iterador_t* iterador){
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
    if(!lista){
        return 0;
    }
    funcion(lista->elemento);
    return 1 + lista_con_cada_elemento(lista->siguiente);
}