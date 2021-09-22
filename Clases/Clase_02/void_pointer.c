#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t vtrlen_recursivo(void** ptr){
    if(!ptr || !*ptr){ //Si es null el vector no tiene nada
        return 0;
    }
    return 1 + (vtrlen_recursivo(ptr+1));
}

size_t vtrlen(void** ptr){
    if(!ptr){ //Si es null el vector no tiene nada
        return 0;
    }
    size_t i;
    for(i = 0; ptr[i] != NULL; i++);
    return i;
}

/*
Paso 0: Creacion-> Creo void** vector y la apunto a NULL
Paso 1: Agregar elemento-> le cambio el tamaño con malloc a 1 por ejemplo -> esto va a apuntar al elemento del usuario(El cual debe ser un puntero tamb) -> El puntero final va a apuntar a NULL ya que no sabemos el tamaño

*/
void** vtradd(void** ptr,void* item){
    if(!ptr){
        ptr = malloc(2*sizeof(void*)); //Reservo espacio para 2 punteros -> 2 ya que tengo que poner 1 item y 1 null
        ptr[0] = item;
        ptr[1] = NULL;
        return ptr;
    }
    size_t tam = vtrlen_recursivo(ptr);
    ptr = realloc(ptr,tam+2*sizeof(void));
    ptr[tam-2] = item;
    ptr[tam-1] = NULL;
    return ptr;
    //Falta chequear que todo funcione bien los malloc,free y esas cosas
}


int main(){

    void* mi_puntero = NULL; //Void no tiene tamaño -> pero void* es un puntero y si tiene tamaño

    void** vector = NULL;
    printf("El vector tiene %zu elementos\n",vtrlen_recursivo(vector));

    int numero = 0;
    void** vector_aux = vector;
    vector = vtradd(vector,&numero);

    printf("El vector tiene %zu elementos\n",vtrlen_recursivo(vector));

    return 0;
}