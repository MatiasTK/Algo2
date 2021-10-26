#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

#define INORDEN 0
#define PREORDEN 1
#define POSTORDEN 2

/*
* PRE:
* POST: Devuelve un nodo creado o NULL si fallo.
*/
nodo_abb_t* nodo_crear(){
    nodo_abb_t* nodo = calloc(1,sizeof(nodo_abb_t));
    if(!nodo){
        return NULL;
    }
    return nodo;
}

abb_t* abb_crear(abb_comparador comparador){
    if(!comparador){
        return NULL;
    }
    abb_t* arbol = calloc(1,sizeof(abb_t));
    if(!arbol){
        return NULL;
    }
    arbol->tamanio = 0;
    arbol->comparador = comparador;
    return arbol;
}

/*
* PRE: Arbol debe ser diferente de NULL.
* POST: Inserta un nuevo nodo con su elemento al arbol binario, si el elemento es menor al elemento del nodo lo inserta a la derecha, sino a la izquierda. En caso de fallos devuelve NULL.
*/
nodo_abb_t* nodo_insertar(abb_t* arbol, void* elemento, nodo_abb_t* nodo){
    if(!nodo){
        nodo = nodo_crear();
        if(!nodo){
            return NULL;
        }
        nodo->elemento = elemento;
        return nodo;
    }
    int comparacion = arbol->comparador(elemento,nodo->elemento); //? 0 Si son iguales, > 0 si el primero es mayor al segundo, < 0 si el primero es menor al segundo
    if(comparacion <= 0){
        nodo->izquierda = nodo_insertar(arbol,elemento,nodo->izquierda);
    }else{
        nodo->derecha = nodo_insertar(arbol,elemento,nodo->derecha);
    }
    return nodo;
}

abb_t* abb_insertar(abb_t* arbol, void* elemento){
    if(!arbol){
        return NULL;
    }
    arbol->nodo_raiz = nodo_insertar(arbol,elemento,arbol->nodo_raiz);
    if(!arbol->nodo_raiz){
        return NULL;
    }
    (arbol->tamanio)++;
    return arbol;
}

/*
* PRE: Nodo debe ser diferente de NULL.
* POST: Devuelve true si el nodo es hoja(No tiene hijos), false en caso contrario.
*/
bool es_hoja(nodo_abb_t* nodo){
    if(nodo->izquierda == NULL && nodo->derecha == NULL){
        return true;
    }
    return false;
}

/*
* PRE: Nodo debe ser diferente de NULL.
* POST: Devuelve true si el nodo tiene un solo hijo, false en caso contrario.
*/
bool tiene_un_hijo(nodo_abb_t* nodo){
    if(nodo->izquierda == NULL && nodo->derecha != NULL){
        return true;
    }else if(nodo->izquierda != NULL && nodo->derecha == NULL){
        return true;
    }
    return false;
}

/*
* PRE: Nodo debe ser diferente de NULL.
* POST: Devuelve true si el nodo tiene dos hijos, false en caso contrario.
*/
bool tiene_dos_hijos(nodo_abb_t* nodo){
    if(nodo->derecha != NULL && nodo->izquierda != NULL){
        return true;
    }
    return false;
}

/*
* PRE: Aux debe estar previamente inicializado.
* POST: Busca el nodo de mayor valor del arbol y actualiza en el auxiliar recibido por parametro. Devuelve NULL en caso de error.
*/
nodo_abb_t* buscar_nodo_mayor(nodo_abb_t* nodo, nodo_abb_t** aux){
    if(!nodo){
        return NULL;
    }
    if(nodo->derecha){
        nodo->derecha = buscar_nodo_mayor(nodo->derecha,aux);
        return nodo;
    }
    *aux = nodo;
    return nodo->izquierda;
}

/*
* PRE:
* POST: Busca el mayor valor del subarbol izquierdo
*/
nodo_abb_t* buscar_nodo_mayor_subarbol_izquierdo(nodo_abb_t* nodo){
    nodo_abb_t* aux = NULL;
    nodo->izquierda = buscar_nodo_mayor(nodo->izquierda,&aux);
    return aux;
}

/*
* PRE:
* POST: Recorre el arbol hasta encontrar el nodo a eliminar, una vez lo encuentra lo quita dependiendo de sus hijos y devuelve la nueva referencia al nodo padre. Si falla devuelve NULL.
*/
nodo_abb_t* nodo_quitar(abb_t* arbol, nodo_abb_t* nodo,void* elemento, void** elemento_removido){
    if(!nodo){
        return NULL;
    }
    if(arbol->comparador(elemento,nodo->elemento) == 0){
        *elemento_removido = nodo->elemento;
        if(es_hoja(nodo)){ //? Si es hoja libera el nodo y como no tiene hijos el padre va a apuntar a NULL.
            free(nodo);
            arbol->tamanio--;
            return NULL;
        }else if(tiene_un_hijo(nodo)){ //? Si tiene un hijo remueve el indicado y devuelve hacia donde tiene que apuntar el padre -> El nodo hijo
            nodo_abb_t* aux = NULL;
            if(nodo->derecha == NULL){
                aux = nodo->izquierda;
            }else{
                aux = nodo->derecha;
            }
            free(nodo);
            arbol->tamanio--;
            return aux;
        }else if(tiene_dos_hijos(nodo)){ //? Si tiene dos hijos remueve el indicado y busca el nodo menor del subarbol derecho, tambien arregla si este nodo menor tiene hijos.
            nodo_abb_t* nodo_anterior = buscar_nodo_mayor_subarbol_izquierdo(nodo);
            nodo_abb_t* aux = nodo;
            nodo = nodo_anterior;
            nodo->izquierda = aux->izquierda;
            nodo->derecha = aux->derecha;
            free(aux);
            arbol->tamanio--;
            return nodo;
        }
    }
    if(arbol->comparador(elemento,nodo->elemento) > 0){
        nodo->derecha = nodo_quitar(arbol,nodo->derecha,elemento,elemento_removido);
    }else{
        nodo->izquierda = nodo_quitar(arbol,nodo->izquierda,elemento,elemento_removido);
    }
    return nodo;
}

void* abb_quitar(abb_t* arbol, void *elemento){
    if(!arbol || !elemento || arbol->tamanio == 0){
        return NULL;
    }
    void* elemento_removido = NULL;
    arbol->nodo_raiz = nodo_quitar(arbol,arbol->nodo_raiz,elemento,&elemento_removido);
    return elemento_removido;
}

/*
* PRE: El arbol debe tener una funcion de comparador.
* POST: Devuelve el nodo que contiene el elemento buscado.
*/
nodo_abb_t* buscar_nodo(abb_t* arbol,nodo_abb_t* nodo, void* elemento){
    if(!nodo){
        return NULL;
    }
    if(arbol->comparador(elemento,nodo->elemento) == 0){
        return nodo;
    }
    if(arbol->comparador(elemento,nodo->elemento) > 0){
        return buscar_nodo(arbol,nodo->derecha,elemento);
    }else{
        return buscar_nodo(arbol,nodo->izquierda,elemento);
    }
}

void* abb_buscar(abb_t* arbol, void* elemento){
    if(!arbol || !elemento || arbol->tamanio == 0){
        return NULL;
    }
    nodo_abb_t* nodo = buscar_nodo(arbol,arbol->nodo_raiz,elemento);
    if(!nodo){
        return NULL;
    }
    return nodo->elemento;
}

bool abb_vacio(abb_t* arbol){
    if(abb_tamanio(arbol) == 0){
    return true;
    }
    return false;
}

size_t abb_tamanio(abb_t *arbol){
    if(!arbol){
        return 0;
    }
    return arbol->tamanio;
}

void abb_destruir(abb_t *arbol){
    abb_destruir_todo(arbol,NULL);
}

/*
* PRE: Recibe una funcion de destruccion de elementos.
* POST: Destruye el nodo y sus hijos, si la funcion de destruccion no es NULL la llama.
*/
void liberar_nodo(nodo_abb_t* nodo, void (*destructor)(void *)){
    if(!nodo){
        return;
    }
    liberar_nodo(nodo->izquierda,destructor);
    liberar_nodo(nodo->derecha,destructor);
    if(destructor){
        destructor(nodo->elemento);
    }
    free(nodo);
}   

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *)){
    if(!arbol){
        return;
    }
    liberar_nodo(arbol->nodo_raiz,destructor);
    free(arbol);
}

/*
* PRE:
* POST: Devuelve la cantidad de elementos que hay en el arbol mediante un recorrido inorden.
*/
size_t abb_con_cada_elemento_inorder(nodo_abb_t* nodo, bool (*visitar)(void*, void*), void* extra, size_t contador){
    if(!nodo){
        return contador;
    }
    contador = abb_con_cada_elemento_inorder(nodo->izquierda,visitar,extra,contador);
    if(visitar(nodo->elemento,extra)){
        contador++;
    }else{
        return contador;
    }
    contador = abb_con_cada_elemento_inorder(nodo->derecha,visitar,extra,contador);
    return contador;
}

/*
* PRE:
* POST: Devuelve la cantidad de elementos que hay en el arbol mediante un recorrido preorden.
*/
size_t abb_con_cada_elemento_preorder(nodo_abb_t* nodo, bool (*visitar)(void*, void*), void* extra, size_t contador){
    if(!nodo){
        return contador;
    }
    if(visitar(nodo->elemento,extra)){
        contador++;
    }else{
        return contador;
    }
    contador = abb_con_cada_elemento_preorder(nodo->izquierda,visitar,extra,contador);
    contador = abb_con_cada_elemento_preorder(nodo->derecha,visitar,extra,contador);
    return contador;
}

/*
* PRE: 
* POST: Devuelve la cantidad de elementos que hay en el arbol mediante un recorrido postorden.
*/
size_t abb_con_cada_elemento_postorder(nodo_abb_t* nodo, bool (*visitar)(void*, void*), void* extra, size_t contador){
    if(!nodo){
        return contador;
    }
    contador = abb_con_cada_elemento_postorder(nodo->izquierda,visitar,extra,contador);
    contador = abb_con_cada_elemento_postorder(nodo->derecha,visitar,extra,contador);
    if(visitar(nodo->elemento,extra)){
        contador++;
    }else{
        return contador;
    }
    return contador;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux){
    if(!arbol || !funcion){
        return 0;
    }
    size_t contador = 0;
    if(recorrido == PREORDEN){
        return abb_con_cada_elemento_preorder(arbol->nodo_raiz,funcion,aux,contador);
    }else if(recorrido == INORDEN){
        return abb_con_cada_elemento_inorder(arbol->nodo_raiz,funcion,aux,contador);
    }else if(recorrido == POSTORDEN){
        return abb_con_cada_elemento_postorder(arbol->nodo_raiz,funcion,aux,contador);
    }
    return contador;
}

/*
* PRE:
* POST: Recorre el arbol con el recorrido inorder y añade los elementos al array, devuelve la cantidad de elementos añadidos.
*/
size_t abb_recorrer_inorder(nodo_abb_t* nodo,void** array, size_t tamanio_array, size_t contador){
    if(!nodo){
        return contador;
    }
    contador = abb_recorrer_inorder(nodo->izquierda,array,tamanio_array,contador);
    if(contador < tamanio_array){
        array[contador] = nodo->elemento;
        contador++;
    }else{
        return contador;
    }
    contador = abb_recorrer_inorder(nodo->derecha,array,tamanio_array,contador);
    return contador;
}

/*
* PRE:
* POST: Recorre el arbol con el recorrido preorder y añade los elementos al array, devuelve la cantidad de elementos añadidos.
*/
size_t abb_recorrer_preorder(nodo_abb_t* nodo,void** array, size_t tamanio_array, size_t contador){
    if(!nodo){
        return contador;
    }
    if(contador < tamanio_array){
        array[contador] = nodo->elemento;
        contador++;
    }
    contador = abb_recorrer_preorder(nodo->izquierda,array,tamanio_array,contador);
    contador = abb_recorrer_preorder(nodo->derecha,array,tamanio_array,contador);
    return contador;
}

/*
* PRE:
* POST: Recorre el arbol con el recorrido postorder y añade los elementos al array, devuelve la cantidad de elementos añadidos.
*/
size_t abb_recorrer_postorder(nodo_abb_t* nodo,void** array, size_t tamanio_array, size_t contador){
    if(!nodo){
        return contador;
    }
    contador = abb_recorrer_postorder(nodo->izquierda,array,tamanio_array,contador);
    contador = abb_recorrer_postorder(nodo->derecha,array,tamanio_array,contador);
    if(contador < tamanio_array){
        array[contador] = nodo->elemento;
        contador++;
    }
    return contador;
}

size_t abb_recorrer(abb_t* arbol, abb_recorrido recorrido, void** array, size_t tamanio_array){
    if(!arbol || !array || tamanio_array == 0){
        return 0;
    }
    size_t contador = 0;
    if(recorrido == PREORDEN){
        return abb_recorrer_preorder(arbol->nodo_raiz,array,tamanio_array,contador);
    }else if(recorrido == INORDEN){
        return abb_recorrer_inorder(arbol->nodo_raiz,array,tamanio_array,contador);
    }else if(recorrido == POSTORDEN){
        return abb_recorrer_postorder(arbol->nodo_raiz,array,tamanio_array,contador);
    }
    return contador;
}

