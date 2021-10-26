#include "solucion.h"

entrenador_t* entrenador_con_mas_victorias(lista_iterador_t* it_lista){
    if(!it_lista){
        return NULL;
    }
    entrenador_t* ganador = lista_iterador_elemento_actual(it_lista);
    while(lista_iterador_tiene_siguiente(it_lista)){
        entrenador_t* comparar = lista_iterador_elemento_actual(it_lista);
        if(comparar->b_ganadas == ganador->b_ganadas){
            if(comparar->b_perdidas < ganador->b_perdidas){
                ganador = comparar;
            }
        }else if(comparar->b_ganadas > ganador->b_ganadas){
            ganador = comparar;
        }
        lista_iterador_avanzar(it_lista);
    }
    return ganador;
}