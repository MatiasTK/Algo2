#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void armar_vector(const char* string, char caracter, int* posiciones, int tope, int posicion_string){
    if(string[posicion_string] == '\0'){
        posiciones[tope] = -1;
        tope++;
        return;
    }
    if(string[posicion_string] == caracter){
        posiciones[tope] = posicion_string;
        tope++;
    }
    armar_vector(string, caracter, posiciones, tope, posicion_string + 1);
}

int* buscar_posiciones(const char* string, char caracter){
    int* posiciones = malloc(sizeof(int) * strlen(string));
    int tope = 0;
    int posicion_string = 0;

    armar_vector(string, caracter, posiciones, tope, posicion_string);

    return posiciones;
}

void mostrar_vector(int* posicion){
    int i = 0;
    bool salir = false;
    printf("[ ");
    while(!salir){
        if(posicion[i] == -1){
            salir = true;
        }
        printf("%i , ", posicion[i]);
        i++;
    }
    printf("] \n");
}

int main(){

    int* posiciones = buscar_posiciones("155321197",'1');
    mostrar_vector(posiciones);

    free(posiciones);
    
    return 0;
}

