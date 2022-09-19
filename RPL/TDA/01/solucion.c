#include "solucion.h"

bool se_encuentra_el_elemento(lista_iterador_t* it_lista, int numero){
    if(!it_lista){
        return false;
    }
    lista_iterador_t* it = NULL;
    for(it = lista_iterador_crear(it_lista);lista_iterador_tiene_siguiente(it);lista_iterador_avanzar(it)){
        if(atoi(lista_iterador_elemento_actual(it)) == numero){
            return true;
        }
    }
    return false;
}