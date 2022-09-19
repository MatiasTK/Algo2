#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leer_linea.h"

char* leer_linea(FILE* file){
    char* linea = NULL;
    char* aux = NULL;
    int inicio = 0;
    int final = 0;
    int incremento = 80;

    while(aux = realloc(linea,(size_t)(final+incremento))){
        linea = aux;
        final += incremento;
        aux[final-1] = 1;

        if(!fgets(aux+inicio,final-inicio,file)){
            free(linea);
            return NULL;
        }

        if(aux[final-1] != 0 || (aux[final-1]== 0 && aux[final-2] == '\n')){
            inicio = final;
        }
    }
    free(linea);
    return NULL;
}

