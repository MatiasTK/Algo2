#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

//! NO ES LA IMPLEMENTACION DEL TP
//** Esto es la implementacion DE AVL!

abb_t* abb_crear(abb_comparador comparador){
    return NULL;
}

abb_t* abb_insertar_balanceado(abb_t* arbol, void* elemento, int (comparador)(void*,void*),int* incremento){
  if(!arbol){
    abb_t* nuevo = calloc(1,sizeof(abb_t));
    nuevo->elemento = elemento;
    nuevo->fe = 0;
    *incremento = 1;
    return arbol
  }
  int comparacion = comparador(elemento,arbol->elemento);
  if(comparacion <= 0){
    arbol->izquierda = abb_insertar_balanceado(arbol->izquierda, elemento, comparador,incremento);
    arbol->fe -= *incremento;
  }else{
    arbol->derecha = abb_insertar_balanceado(arbol->derecha,elemento, comparador,incremento);
    arbol->fe += *incremento;
  }

  if(arbol->fe == 0){
    *incremento = 0;
  }

  if(arbol->fe >= 2){ //* Se me desbalanceo hacia la derecha
    //? Verificar rotaciones simples
    abb_t* raiz = arbol;
    abb_t* nueva_raiz = raiz->derecha;
    abb_t* aux_hijo = nueva_raiz->izquierda;
    nueva_raiz->izquierda = raiz;
    nueva_raiz->izquierda->derecha = aux_hijo;
    arbol->fe = 0;
    nueva_raiz->fe = 0;
    arbol = nueva_raiz;
    *incremento = 0;
  }

  return arbol;
}

abb_t* abb_insertar(abb_t* arbol, void* elemento, int (comparador)(void*,void*)){
  int incremento = 0;
  return abb_insertar_balanceado(arbol,elemento,comparador,&incremento);
}

void* abb_quitar(abb_t* arbol, void *elemento){
  return NULL;
}

void* abb_buscar(abb_t* arbol, void* elemento){
  return NULL;
}

bool abb_vacio(abb_t* arbol){
  return true;
}

size_t abb_tamanio(abb_t *arbol){
  return 0;
}

void abb_destruir(abb_t *arbol){

}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *)){

}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux){
  return 0;
}

size_t abb_recorrer(abb_t* arbol, abb_recorrido recorrido, void** array, size_t tamanio_array){
  return 0;
}
