#include <stdio.h>

int main(){
    int** matriz = calloc(5,sizeof(int*));

    for(int i = 0; i < 5; i++){
        matriz[i] = calloc(5,sizeof(int));
    }

    int* enteros = calloc(25,sizeof(int));

    for(int i = 0; i < 5; i++){
        matriz[i] = enteros+i*5;
    }
}