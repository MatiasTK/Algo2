#include <stdbool.h>
#include <stdio.h>

void merge(int* vector_1, int cantidad_1, int* vector_2, int cantidad_2,bool ascendente){
    int vector_3[cantidad_1 + cantidad_2];
    int i = 0, j = 0, k = 0;

    while(i < cantidad_1 && j < cantidad_2){
        if(ascendente){
            if(vector_1[i] <= vector_2[j]){
            vector_3[k] = vector_1[i];
            i++;
            }else{
            vector_3[k] = vector_2[j];
            j++;
            }
            k++; 
        }else{
            if(vector_1[i] > vector_2[j]){
            vector_3[k] = vector_1[i];
            i++;
            }else{
            vector_3[k] = vector_2[j];
            j++;
            }
            k++;
        }
        
    }

    while(i < cantidad_1){
        vector_3[k] = vector_1[i];
        i++;
        k++;
    }

    while(j < cantidad_2){
        vector_3[k] = vector_2[j];
        j++;
        k++;
    }

    for(int x = 0; x < cantidad_1 + cantidad_2; x++){
        vector_1[x] = vector_3[x];
    }

}

void merge_sort(int* numeros, int tope, bool ascendente){
    if(tope <= 1){
        return;
    }

    int mitad = tope / 2;

    merge_sort(numeros,mitad,ascendente); 
    merge_sort(numeros+mitad, tope - mitad,ascendente);

    merge(numeros,mitad,numeros+mitad,tope-mitad,ascendente);
}

void mostrar_vector(int* vector,int cantidad){
    for(int i=0;i<cantidad;i++){
        printf("%d ",vector[i]);
    }
    printf("\n===========================\n");
}

int main(){

    int numeros[] = {5,4,2,6,3,7,1,1,55,3,7,8,19};
    int cantidad = sizeof(numeros)/sizeof(int);

    mostrar_vector(numeros,cantidad);
    merge_sort(numeros,cantidad,false);
    mostrar_vector(numeros,cantidad);

    return 0;
}