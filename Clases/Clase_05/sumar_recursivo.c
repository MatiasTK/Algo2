#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sumar_numeros(int* numeros,int cantidad_numeros){
    if(!cantidad_numeros){
        return 0;
    }
    return *numeros+sumar_numeros(numeros+1,cantidad_numeros-1);
} 

int main(int argc, char const *argv[]){

    int numeros[] = {1,5,7,8,0,2,1};

    int resultado = sumar_numeros(numeros,sizeof(numeros)/sizeof(int));    

    printf("La suma da: %d\n",resultado);

    return 0;
}
