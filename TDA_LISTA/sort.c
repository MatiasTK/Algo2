#include "src/lista.h"
#include <stdio.h>
#include <stdbool.h>

bool imprimir_lista(void *dato,void *param){
    printf("%s", (char*)dato);
    return true;
}


int main(){

    lista_t* lista = lista_crear();

    char* pokemon_1 = "Pikachu";
    char* pokemon_2 = "Charmander";
    char* pokemon_3 = "Bulbasaur";

    lista_insertar(lista, pokemon_1);
    lista_insertar(lista, pokemon_2);
    lista_insertar(lista, pokemon_3);

    lista_con_cada_elemento(lista, imprimir_lista,NULL);

    lista_destruir(lista);

    return 0;
}