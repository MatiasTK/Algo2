#include "solucion.h"

bool llenar_ganadores(void* elemento_1, void* elemento_2){
    entrenador_t entrenador = *(entrenador_t*)elemento_1;
    lista_t* datos = (lista_t*)elemento_2;

    lista_t* nueva = (lista_t*)lista_elemento_en_posicion(datos,0);

    if(entrenador.b_ganadas > *(int*)(lista_elemento_en_posicion(datos, 1))){
        lista_insertar(nueva, (entrenador_t*)elemento_1);
    }

    return true;
}

void entrenadores_con_muchas_victorias(lista_t* entrenadores, lista_t* entrenadores_ganadores, int batallas_ganadas){
    if(!entrenadores || !entrenadores_ganadores || lista_vacia(entrenadores) || batallas_ganadas <= 0){
        return;
    }

    lista_t* datos = lista_crear();
    lista_insertar(datos, entrenadores_ganadores);
    lista_insertar(datos, &batallas_ganadas);

    lista_con_cada_elemento(entrenadores,llenar_ganadores,datos);
}