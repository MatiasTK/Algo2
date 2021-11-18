//EJ -> https://i.imgur.com/ti9yp6b.png
//! CHEQUEAR

#include "pila.h"
#include <stdio.h>

void transferir_pila(pila_t* p, pila_t* q) {
    if(pila_tope(p) == 0) {
        return;
    }
    pila_apilar(q, pila_tope(p));
    pila_desapilar(p);

    transferir_pila(p, q);    
}

void mostrar_elemento(void* elemento) {
    printf("%d ", *(int*)elemento);
}

void mostrar_pila_alternada_rec(pila_t* p, pila_t* q) {
    if(pila_tope(p) == 0) {
        return;
    }
    void* elemento = pila_tope(p);
    pila_desapilar(p);
    mostrar_elemento(elemento);
    transferir_pila(p, q);
    mostrar_pila_alternada_rec(q, p);
}

void mostrar_pila_alternada(pila_t* p){
    pila_t* q = pila_crear();
    mostrar_pila_alternada_rec(p, q);
    pila_destruir(q);
}

int main(){
    
    pila_t* p = pila_crear();
    pila_apilar(p, &(int){2});
    pila_apilar(p, &(int){4});
    pila_apilar(p, &(int){5});
    pila_apilar(p, &(int){3});
    pila_apilar(p, &(int){1});

    mostrar_pila_alternada(p);

    pila_destruir(p);

    return 0;
}