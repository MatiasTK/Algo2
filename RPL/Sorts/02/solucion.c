#include <stdio.h>
#include <stdbool.h>

#define MAX_VECTOR 10

void selection_sort(char vector_desordenado[MAX_VECTOR], char vector_ordenado[MAX_VECTOR], int tope, bool ascendente){
    int i, j;
    char aux;
    int minimo;
    for(i = 0; i < tope; i++){
        minimo = i;
        for(j = i+1; j < tope; j++){
            if(ascendente){
                if(vector_desordenado[minimo] > vector_desordenado[j]){
                    minimo = j;
                }
            }else{
                if(vector_desordenado[minimo] < vector_desordenado[j]){
                    minimo = j;

                }
            }
            aux = vector_desordenado[i];
            vector_desordenado[i] = vector_desordenado[minimo];
            vector_desordenado[minimo] = aux;
        }
    }
    for(int k = 0; k < tope; k++){
        vector_ordenado[k] = vector_desordenado[k];
    }
}

int main(){

    char vector[10] = "IHGFD";
    char vector_nuevo[10];
    int tope = 10;
    selection_sort(vector,vector_nuevo,tope,true);

    for(int i=0;i < tope; i++){
        printf(" %c ", vector_nuevo[i]);
    }

    return 0;
}