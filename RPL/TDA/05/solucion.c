#include "solucion.h"

bool gano_batallas(void* elemento_1, void* elemento_2){
    entrenador_t entrenador = *(entrenador_t*)elemento_1;
    int batallas_ganadas = *(int)batallas_ganadas;
    if(entrenador.b_ganadas > batallas_ganadas){
        return true;
    }
    return false;
}

void entrenadores_con_muchas_victorias(lista_t* entrenadores, lista_t* entrenadores_ganadores, int batallas_ganadas){
    if(!entrenadores || !entrenadores_ganadores){
        return;
    }
    size_t* contador = 0;
    contador = lista_con_cada_elemento(entrenadores,batallas_ganadas,batallas_ganadas);
    for(int i = 0; i < contador; i++){
        lista_insertar(entrenadores_ganadores,entrenadores.b_ganadas[i]);
    }
    return;
}