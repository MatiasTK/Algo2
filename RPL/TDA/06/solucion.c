#include "solucion.h"

bool impares(void* elemento_1, void* elemento_2){
    if(!(*(int*)elemento_1 % 2 == 0)){
        arbol_insertar((abb_t*)elemento_2, (int*)elemento_1);
    }

    return true; 
}

void elementos_impares(abb_t* abb_original, abb_t* abb_impares){
    if(arbol_vacio(abb_original) || !abb_original || !abb_impares){
        return;
    }
    abb_con_cada_elemento(abb_original, ABB_RECORRER_INORDEN,impares, abb_impares);
}