#include <stdio.h>

int bubble_sort_recursivo(int array[], int tope){
    int contador = 0;

    if(tope < 2){
        return contador;
    }

    if(array[0] > array[1]){
        int aux;
        aux = array[0];
        array[0] = array[1];
        array[1] = aux;
        contador++;
    }

    contador += bubble_sort_recursivo(array + 1, tope - 1);
    return contador;
}

void bubble_sort(int array[],int tope){
    int contador = bubble_sort_recursivo(array,tope);

    if(contador >= 1){
        bubble_sort(array,tope);
    }
}

void mostrar(int array[], int tope){
    int i;
    for(i=0;i<tope;i++){
        printf("%d - ",array[i]);
    }
    printf("\n==============================\n");
}

int main(){

    int vector[] = {5,123,65,3,9,15,76};
    int tope = sizeof(vector)/sizeof(vector[0]);

    mostrar(vector,tope);
    bubble_sort(vector,tope);
    mostrar(vector,tope);

    return 0;
}