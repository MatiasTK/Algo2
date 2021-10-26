#include "solucion.h"

bool recorrer(){
    
}

entrenador_t* entrenador_con_mas_victorias(lista_t* entrenadores){
    if(!entrenadores){
        return NULL;
    }
    entrenador_t* ganador = lista_primero(entrenadores);
    size_t i = 0;
    while(i < lista_con_cada_elemento(entrenadores,recorrer,NULL)){
        entrenador_t* comparar = lista_elemento_en_posicion(entrenadores,i);
        if(comparar->b_ganadas == ganador->b_ganadas){
            if(comparar->b_perdidas < ganador->b_perdidas){
                ganador = comparar;
            }
        }else if(comparar->b_ganadas > ganador->b_ganadas){
            ganador = comparar;
        }
        i++;
    }

    return ganador;
}