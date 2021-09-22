#include <stdio.h>

int main(){

    char* buffer;
    int* numeros;

    buffer = (char*)malloc(10); 

    numeros = (int*)malloc(5);

    //Aca tendriamos que hacer algo con los buffer
    
    free((void*)buffer);
    free((void*)numeros);

    return 0;
}

/*
Malloc es para reversar una memoria "Manualmente" de una variable -> malloc(10) reserva 10 bytes de memoria
*/