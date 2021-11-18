#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VECTOR 10

void insertion_sort(char vector_desordenado[MAX_VECTOR], char vector_ordenado[MAX_VECTOR], int tope, bool ascendente){
    int i,j;
    char aux;

    for(i = 1; i < tope; i++){
        j = i;
        aux = vector_desordenado[i];
        while(j > 0 && aux < vector_desordenado[j-1]){
            vector_desordenado[j] = vector_desordenado[j-1];
            j--;
        }
        vector_desordenado[j] = aux;
    }

    if(ascendente){
        for(int k = 0; k < tope; k++){
            vector_ordenado[k] = vector_desordenado[k];
        }
    }else{
        int pos = 0;
        for(int k = tope-1; k >= 0; k--){
            vector_ordenado[pos] = vector_desordenado[k];
            pos++;
        }
    }
}

int main(){

    char vector_desordenado[MAX_VECTOR] = "BCDE";
    char vector_ordenado[MAX_VECTOR];
    int tope = strlen(vector_desordenado);
    bool ascendente = true;

    insertion_sort(vector_desordenado, vector_ordenado, tope, !ascendente);

    for(int i = 0; i < tope; i++){
        printf(" %c ", vector_ordenado[i]);
    }

    return 0; 
}