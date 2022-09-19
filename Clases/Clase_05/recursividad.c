#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mostrar_invertido(const char* string){
    if(!*string){
        return;
    }
    mostrar_invertido(string+1);
    printf("%c",*string); // Como esto esta abajo de la recursiva se va a imprimir invertido
}

int main(int argc, char *argv[]){
    
    char* string = "Hola como estas";

    if(argc > 2){
        string = argv[1];
    }

    mostrar_invertido(string);

    return 0;
}
