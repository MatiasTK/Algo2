#include "solucion.h"

void bubble_sort(char vector_desordenado[MAX_VECTOR], char vector_ordenado[MAX_VECTOR], int tope, bool ascendente){
    int i, j;
    char aux;
    for(i = 0; i < tope - 1; i++){
        for(j = 0; j < tope - i - 1; j++){
            if(ascendente){
                if(vector_desordenado[j] > vector_desordenado[j + 1]){
                    aux = vector_desordenado[j];
                    vector_desordenado[j] = vector_desordenado[j + 1];
                    vector_desordenado[j + 1] = aux;
                }
            }else{
                if(vector_desordenado[j] < vector_desordenado[j + 1]){
                    aux = vector_desordenado[j];
                    vector_desordenado[j] = vector_desordenado[j + 1];
                    vector_desordenado[j + 1] = aux;
                }
            }
        }
    }
    for(i = 0; i < tope; i++){
        vector_ordenado[i] = vector_desordenado[i];
    }
}