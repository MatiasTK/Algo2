#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.c"
#include "pa2mm.h"

void DadaPilaVaciaAlPedirElTopeDevuelveNULL(){
    pila_t* pila = pila_crear();
    pa2m_afirmar(pila_tope(pila)== NULL, "Para una pila vacia el tope es NULL");

    pila_destruir(pila);
}

void DadaUnaPilaVaciaAlApilarUnElementoExitosamenteDevuelveLaPila(){
    pila_t* pila = pila_crear();
    
    int elemento = 25;
    
    pa2m_afirmar(pila_apilar(pila,&elemento)==pila,"Apilar devuelve la pila");

    pila_destruir(pila);
}

void DadaUnaPilaVaciaAlAPilarUnElementoExitosamenteLaPilaQuedaConTamanio1(){
    pila_t* pila = pila_crear();
    
    int elemento = 25;
    pila_apilar(pila,&elemento);

    pa2m_afirmar(pila_tamanio(pila)==1,"El tamaño de la pila es 1");

    pila_destruir(pila);
}

void DadaPilaConUnElementoAlPedirTopeDevuelveEseElemento(){
    pila_t* pila = pila_crear();
    
    int elemento = 25;
    pila_apilar(pila,&elemento);
    
    pa2m_afirmar(pila_tope(pila) == &elemento, "Para una pila con un elemento ese elemento es el tope");

    pila_destruir(pila);
}

todo_puede_salir_mal(){
    pa2m_afirmar(pila_tope(NULL) == NULL, "El tope de una pila nula es NULL");
    pila_destruir(NULL);
}

int main(int argc, char const *argv[]){
    
    pa2m_nuevo_grupo("Preubas de pila apilar");
    DadaUnaPilaVaciaAlApilarUnElementoExitosamenteDevuelveLaPila();
    DadaUnaPilaVaciaAlAPilarUnElementoExitosamenteLaPilaQuedaConTamanio1();

    pa2m_nuevo_grupo("Pruebas de pila tope");
    DadaPilaVaciaAlPedirElTopeDevuelveNULL();
    DadaPilaConUnElementoAlPedirTopeDevuelveEseElemento();

    pa2m_nuevo_grupo("PRuebas cuando toso sale mal");
    todo_puede_salir_mal();

    return pa2m_mostrar_reporte();
}
