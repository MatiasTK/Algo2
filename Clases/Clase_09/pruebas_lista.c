#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa2mm.h"
#include "lista.h"


void mostrar_entero(void* i){
    int* entero = i;
    printf("%i", *entero);
}

int main(int argc, char const *argv[]){
    pa2m_nuevo_grupo("Pruebas de lista");
    
    lista_t* lista = lista_crear();
    int a = 4,b = 5, c = 6;

    lista = lista_insertar(lista,&a);
    lista = lista_insertar(lista,&b);
    lista = lista_insertar(lista,&c);

    lista_con_cada_elemento(lista,mostrar_entero);

    lista = lista_quitar(lista);
    lista_con_cada_elemento(lista,mostrar_entero);

    lista_destruir(lista);

    return pa2m_mostrar_reporte();
}
