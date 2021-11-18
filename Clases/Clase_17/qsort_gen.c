#include <stdio.h>
#include <string.h> //! Memcpy

void swap(char* vector, size_t tamanio,size_t p1, size_t p2){
    char aux[tamanio];
    memcpy(aux,vector+p1*tamanio,tamanio);
    memcpy(vector+p1*tamanio,vector+p2*tamanio,tamanio);
    memcpy(vector+p2*tamanio,aux,tamanio);
}

size_t pivotear(void* vector, size_t tamanio,size_t cantidad, int (*comparar)(void*, void*)){
    size_t pos_pivote = cantidad-1;
    size_t pos_final_pivote = 0;
    size_t pos_actual = 0;
    char* vector_c = vector;

    for(pos_actual; pos_actual < pos_pivote; pos_actual++){
        if(comparar(vector_c+pos_actual*tamanio, vector_c+pos_pivote*tamanio) < 0){
            swap(vector_c, tamanio,pos_actual, pos_final_pivote);
            pos_final_pivote++;
        }
    }

    swap(vector_c,tamanio,pos_pivote, pos_final_pivote);

    return pos_final_pivote;
}

//! Tamanio_elemento es el sizeof del bytes y cantidad es la cantidad de elementos del vector.
void qsort(void* vector, size_t tamanio_elemento, size_t cantidad, int (*comparar)(void*,void*)){
    if(cantidad <= 1){
        return;
    } 
    size_t pos_pivote = pivotear(vector,tamanio_elemento,cantidad, comparar);

    qsort(vector,tamanio_elemento,pos_pivote,comparar);
    qsort((((char*)vector)+(pos_pivote+1)*tamanio_elemento),tamanio_elemento,cantidad-pos_pivote-1,comparar); //! el * tamañio elemento ya que sino estoy avanzando bytes y no elementos.
    //? Se casteo a char* ya que vale 1 y voy a avanzar 1 posicion y no bytes.
}

int comparar_double(void* e1, void* e2){
    double* _e1 = e1;
    double* _e2 = e2;
    return ((*_e1) - (*_e2));
}

int main(){
    double numeros[] = {5.5,4.3,2.2,6.1,3.3,7.4,1.5,1.6,5.75,3.1,7.2,8.2,19.4};

    qsort(numeros,sizeof(double),sizeof(numeros)/sizeof(double),comparar_double);

    for(int i = 0; i < sizeof(numeros)/sizeof(double); i++){
        printf(" %f ",numeros[i]);
    }
    printf("\n");

    return 0;
}