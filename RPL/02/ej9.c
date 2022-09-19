#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM 5

int sumar_calorias(int cantidad_filas, int cantidad_columnas, int matriz[MAX_TAM][MAX_TAM]){
    if(cantidad_filas == 0 && cantidad_columnas == 0){
        return matriz[cantidad_filas][cantidad_columnas];
    }
    if(cantidad_columnas == 0){
        return matriz[cantidad_filas][cantidad_columnas] + sumar_calorias(cantidad_filas-1,MAX_TAM,matriz);
    }else{
        return matriz[cantidad_filas][cantidad_columnas] + sumar_calorias(cantidad_filas,cantidad_columnas-1,matriz);
    }
}

int main(int argc, char const *argv[]){
    
    int matriz[MAX_TAM][MAX_TAM];
    for(int i = 0; i < MAX_TAM; i++){
        for(int j = 0; j < MAX_TAM; j++){
            matriz[i][j] = 1;
        }
    }

    int r = sumar_calorias(5,5,matriz);

    printf("El resultado es %i", r);

    return 0;
}
