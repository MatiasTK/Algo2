#include <stdio.h>
#include <string.h> //! memcpy

//? Memcpy -> Copia una cantidad de bytes desde una dirección de memoria a otra dirección de memoria 
//? Memset -> 

void merge(int* vector_1, size_t cantidad_1, int* vector_2, size_t cantidad_2){
    int vector_3[cantidad_1 + cantidad_2];
    size_t i = 0, j = 0, k = 0;

    while(i < cantidad_1 && j < cantidad_2){
        if(vector_1[i] <= vector_2[j]){
            vector_3[k] = vector_1[i];
            i++;
        }else{
            vector_3[k] = vector_2[j];
            j++;
        }
        k++;
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

    /* for(i = 0; i < cantidad_1 + cantidad_2; i++){
        vector_1[i] = vector_3[i];
    } */

    memcpy(vector_1, vector_3, sizeof(int) * (cantidad_1 + cantidad_2));

    return;
}

//! n^log(b_a) -> n (parte recursiva), n(parte no recursiva), por lo tanto -> n*log(n)
//? No se puede hacer con void ya que no tiene tamaño, por lo tanto no se puede hacer vector + mitad
void msort(int* vector, size_t cantidad){
    if(cantidad <= 1){
        return;
    }

    //!B = 2 (Teorema maestro)
    size_t mitad = cantidad / 2;

    //!A = 2 (Teorema maestro)
    msort(vector, mitad);
    msort(vector + mitad, cantidad - mitad);

    //!O(n)
    merge(vector, mitad, vector + mitad, cantidad - mitad);
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
    msort(numeros,cantidad);
    mostrar_vector(numeros,cantidad);

    return 0;
}