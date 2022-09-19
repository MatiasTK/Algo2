#include <stdio.h>
#include <stdbool.h>

void swap(int* vector, int inicial, int final){
    int aux = vector[inicial];
    vector[inicial] = vector[final];
    vector[final] = aux;
}

int buscar_pivote_final(int* numeros,int tope,bool ascendente){
    int pos_pivote = tope - 1;
    int pos_actual = 0;
    int pos_pivote_final = 0;   

    for(pos_actual;pos_actual < pos_pivote; pos_actual++){
        if(ascendente){
            if(numeros[pos_actual] < numeros[pos_pivote]){
                swap(numeros,pos_actual,pos_pivote_final);
                pos_pivote_final++;
            }
        }else{
            if(numeros[pos_actual] > numeros[pos_pivote]){
                swap(numeros,pos_actual,pos_pivote_final);
                pos_pivote_final++;
            }
        }
    }

    swap(numeros,pos_pivote,pos_pivote_final);

    return pos_pivote_final;
}

void quick_sort(int* numeros, int tope, bool ascendente){
    if(tope <= 1){
        return;
    }

    int pos_pivote_final = buscar_pivote_final(numeros, tope, ascendente);
    quick_sort(numeros, pos_pivote_final, ascendente);
    quick_sort(numeros + pos_pivote_final + 1, tope - pos_pivote_final - 1, ascendente);
}

void mostrar_vector(int* vector,size_t cantidad){
    for(int i=0;i<cantidad;i++){
        printf("%d ",vector[i]);
    }
    printf("\n===========================\n");
}

int main(){
    int numeros[] = {5,4,2,6,3,7,1,1,55,3,7,8,19};
    int cantidad = sizeof(numeros)/sizeof(int);

    mostrar_vector(numeros,cantidad);
    quick_sort(numeros,cantidad,true);
    mostrar_vector(numeros,cantidad);

    return 0;
}