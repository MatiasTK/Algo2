#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//El malloc es como archivos tengo que verificar si paso todo bien sino tengo que cerrar el programa-> lo mismo con realloc
//Conviene hacer el realloc en otra variable asi no pierdo lo que esta en malloc

int main(){

    int cantidad = 10;
    int* numeros = malloc(cantidad*sizeof(int)); //Le pones un tamaño al vector de cantidad -> 10

    if(numeros == NULL){ // Chequeo si malloc dio error, si dio error salgo del programa ya no puedo trabajar
        return -1;
    }

    for(int i = 0; i < cantidad; i++){
        numeros[i] = i*2;
    }
    cantidad++;
    int* numeros_aux = realloc(numeros,cantidad*sizeof(int)); // Cambio a que numeros tenga un tamaño de 11 enteros y no a 10 -> Lo pongo en aux por si falla el realloc asi no pierdo
    
    if(!numeros_aux){ //verifico si realloc fallo
        //No es necesario hacer free de numeros_aux ya que numeros_aux ahora es null
        return -1;
    }

    numeros = numeros_aux;

    numeros[cantidad-1] = 99;

    //Si no lo inicializo me tira basura
    for(int i = 0; i < cantidad; i++){
        printf("Posicion %i, valor %i\n",i,numeros[i]);
    }

    free(numeros); //Liberas el espacio del malloc

    return 0;
}