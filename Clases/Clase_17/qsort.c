#include <stdio.h>

void swap(int* vector, size_t inicial, size_t final){
    int aux;
    aux = vector[inicial];
    vector[inicial] = vector[final];
    vector[final] = aux;
}

size_t pivotear(int* vector, size_t cantidad){
    size_t pos_pivote = cantidad - 1;
    size_t pos_actual = 0;
    size_t pos_final_pivote = 0;

    for(pos_actual; pos_actual < pos_pivote; pos_actual++){
        if(vector[pos_actual] < vector[pos_pivote]){
            swap(vector,pos_actual,pos_final_pivote);
            pos_final_pivote++;
        }
    }

    swap(vector,pos_pivote,pos_final_pivote);

    return pos_final_pivote;
}

void qsort(int* vector, size_t cantidad){
    if(cantidad <= 1){
        return;
    }

    size_t pos_final_pivote = pivotear(vector, cantidad);
    qsort(vector, pos_final_pivote);
    qsort(vector + pos_final_pivote + 1, cantidad - pos_final_pivote - 1);
}


void mostrar_vector(int* vector,size_t cantidad){
    for(int i=0;i<cantidad;i++){
        printf("%d ",vector[i]);
    }
    printf("\n===========================\n");
}

int main(){
    int numeros[] = {5,4,2,6,3,7,1,1,55,3,7,8,19};
    size_t cantidad = sizeof(numeros)/sizeof(int);

    mostrar_vector(numeros,cantidad);
    qsort(numeros,cantidad);
    mostrar_vector(numeros,cantidad);

    return 0;
}