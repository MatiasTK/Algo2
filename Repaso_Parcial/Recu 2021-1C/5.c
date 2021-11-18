// EJ -> https://i.imgur.com/oemeBeC.png
#include <stdio.h>

int sumar_numeros(int* numeros, size_t cantidad_de_numeros){
    if(!cantidad_de_numeros){
        return 0;
    }
    return numeros[cantidad_de_numeros - 1] + sumar_numeros(numeros, cantidad_de_numeros - 1);
}

int main(){

    int numeros[] = {1, 2, 3, 4, 5};
    printf("%d\n", sumar_numeros(numeros, 5));

    return 0;
}