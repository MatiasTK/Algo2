#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

lista_t* lista_crear(){
    lista_t* lista = calloc(1,sizeof(lista_t));
    if(!lista){
        return NULL;
    }
    return lista;
}
/*
* PRE: 
* POST: Devuelve un nodo creado con su elemento o NULL si fallo
*/
nodo_t* nodo_crear(void* elemento){
    nodo_t* nodo = calloc(1,sizeof(nodo_t));
    if(!nodo){
        return NULL;
    }
    nodo->elemento = elemento;
    return nodo;
}

lista_t* lista_insertar(lista_t* lista, void* elemento){
    if(!lista){
        return NULL;
    }
    nodo_t* nodo = nodo_crear(elemento);
    if(!nodo){
        return NULL;
    }
    if(lista_vacia(lista)){
        lista->nodo_inicio = nodo;
        lista->nodo_fin = nodo;
    }else{
        lista->nodo_fin->siguiente = nodo;
        lista->nodo_fin = nodo;
    }
    lista->cantidad++;
    return lista;
}

/*
* PRE:  El nodo debe estar previamente creado, la posicion debe ser un entero positivo
* POST: Recorre los nodos hasta llegar a la posicion enviada por paraemtro y devuelve dicho nodo
*/
nodo_t* posicion_nodo_anterior(nodo_t* nodo,size_t posicion){
    if(posicion == 1){
        return nodo;
    }
    return posicion_nodo_anterior(nodo->siguiente,posicion-1);
}

lista_t* lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
    if(!lista){
        return NULL;
    }
    if(posicion == 0){
        if(lista_vacia(lista)){
            return lista_insertar(lista,elemento);
        }else{
            nodo_t* nodo = nodo_crear(elemento);
            if(!nodo){
                return NULL;
            }
            nodo->siguiente = lista->nodo_inicio;
            lista->nodo_inicio = nodo;
            lista->cantidad++;
            return lista;
        }
    }
    if(posicion >= lista_tamanio(lista)){
        return lista_insertar(lista,elemento);
    }
    nodo_t* nodo = nodo_crear(elemento);
    if(!nodo){
        return NULL;
    }
    nodo_t* nodo_aux_anterior = posicion_nodo_anterior(lista->nodo_inicio,posicion);
    nodo_t* nodo_aux_siguiente = nodo_aux_anterior->siguiente;
    nodo_aux_anterior->siguiente = nodo;
    nodo->siguiente = nodo_aux_siguiente;
    lista->cantidad++;

    return lista;
}

void* lista_quitar(lista_t* lista){
    if(!lista || lista_vacia(lista)){
        return NULL;
    }
    void* elemento_removido = NULL;
    if(lista->nodo_inicio != lista->nodo_fin){
        nodo_t* nodo_aux = posicion_nodo_anterior(lista->nodo_inicio,lista->cantidad - 1);
        nodo_aux->siguiente = lista->nodo_fin->siguiente;
        elemento_removido = lista->nodo_fin->elemento;
        free(lista->nodo_fin);
        lista->nodo_fin = nodo_aux;
        if(lista_tamanio(lista) == 1){
            lista->nodo_fin = lista->nodo_inicio;
        }
    }else{
        elemento_removido = lista->nodo_fin->elemento;
        free(lista->nodo_fin);
        lista->nodo_fin = NULL;
        lista->nodo_inicio = NULL;
    }
    lista->cantidad--;
    return elemento_removido;
}

/*
* PRE:  lista debe estar previamente inicializada
* POST: Quita de la lista el elemento en la primera posicion, devuelve el elemento removido de la lista o NULL en caso de error.
*/
void* lista_quitar_primer_elemento(lista_t* lista){
    if(!lista || lista_vacia(lista)){
        return NULL;
    }
    void* elemento_removido = NULL;
    nodo_t* aux = lista->nodo_inicio;
    elemento_removido = aux->elemento;
    lista->nodo_inicio = aux->siguiente;
    lista->cantidad--;
    if(lista_tamanio(lista) == 1){
        lista->nodo_fin = lista->nodo_inicio;
    }
    if(lista_vacia(lista)){
        lista->nodo_fin = NULL;
        lista->nodo_inicio = NULL;
    }
    free(aux);
    return elemento_removido;
}

void* lista_quitar_de_posicion(lista_t* lista, size_t posicion){
    void* elemento_removido = NULL;
    if(!lista || lista_vacia(lista)){
        return NULL;
    }
    if(posicion == 0){
        return lista_quitar_primer_elemento(lista);
    }else if(posicion >= lista_tamanio(lista)){
        return lista_quitar(lista);
    }else{
        nodo_t* nodo_anterior = posicion_nodo_anterior(lista->nodo_inicio,posicion);
        nodo_t* nodo_remover = nodo_anterior->siguiente;
        elemento_removido = nodo_remover->elemento;
        nodo_anterior->siguiente = nodo_remover->siguiente;
        lista->cantidad--;
        free(nodo_remover);
        return elemento_removido;
    }
    return elemento_removido;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
    if(!lista || lista_vacia(lista)){
        return NULL;
    }
    if(posicion == 0){
        return lista_primero(lista);
    }
    if(posicion == lista_tamanio(lista)){
        return lista_ultimo(lista);
    }
    if(posicion > lista_tamanio(lista)){
        return NULL;
    }
    nodo_t* nodo_anterior = posicion_nodo_anterior(lista->nodo_inicio,posicion);

    return nodo_anterior->siguiente->elemento;
}

void* lista_primero(lista_t* lista){
    if(!lista || lista_vacia(lista)){
        return NULL;
    }
    return lista->nodo_inicio->elemento;
}

void* lista_ultimo(lista_t* lista){
    if(!lista || lista_vacia(lista)){
        return NULL;
    }
    return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t* lista){
    if(!lista || lista_tamanio(lista) == 0){
        return true;
    }
    return false;
}

size_t lista_tamanio(lista_t* lista){
    if(!lista){
        return 0;
    }
    return lista->cantidad;
}

void lista_destruir(lista_t* lista){
    if(!lista){
        return;
    }
    for(int i = 0; i < lista_tamanio(lista);){
        lista_quitar(lista);
    }
    free(lista);
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
    if(!lista){
        return NULL;
    }
    lista_iterador_t* iterador = calloc(1,sizeof(lista_iterador_t));
    if(!iterador){
        return NULL;
    }
    iterador->lista = lista;
    iterador->corriente = lista->nodo_inicio;
    return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
    if(!iterador){
        return false;
    }
    if(iterador->corriente != NULL){
        return true;
    }
    return false;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){
    if(!iterador || lista_iterador_tiene_siguiente(iterador) == false){
        return false;
    }
    iterador->corriente = iterador->corriente->siguiente;
    if(iterador->corriente == NULL){
        return false;
    }
    return true;

}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
    if(!iterador || iterador->corriente == NULL || iterador->corriente->elemento == NULL){
        return NULL;
    }
    return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador){
    free(iterador);
}
/*
* PRE:
* POST: Recorre los nodos de la lista hasta que la funcion de false o llegue al final de la lista. Devuelve la cantidad de iteraciones que hizo.
*/
size_t recorrer_iterador_interno(nodo_t* nodo, bool (*funcion)(void*, void*), void *contexto){
    if(!nodo){
        return 0;
    }
    if(funcion(nodo->elemento,contexto)){
        return 1 + recorrer_iterador_interno(nodo->siguiente,funcion,contexto);
    }
    return 0;
}   

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
    if(!lista || !funcion ||!contexto){
        return 0;
    }
    nodo_t* nodo = lista->nodo_inicio;
    if(!nodo){
        return 0;
    }
    return recorrer_iterador_interno(nodo,funcion,contexto);

    return 0;
}

void lista_ordenar(lista_t* lista, int (*comparar)(void*, void*)){
    if(!lista || !comparar){
        return;
    }
    if(lista_tamanio(lista) <= 1){
        return;
    }

    nodo_t* actual = lista->nodo_inicio;
    nodo_t* index = NULL;

    while(actual != NULL){
        index = actual->siguiente;
        while(index != NULL){
            if(comparar(actual->elemento,index->elemento) > 0){
                void* aux = actual->elemento;
                actual->elemento = index->elemento;
                index->elemento = aux;
            }
            index = index->siguiente;
        }
        actual = actual->siguiente;
    }

}

