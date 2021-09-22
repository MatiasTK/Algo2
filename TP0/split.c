#include "split.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


char* strdup(const char* string){
    size_t longitud;
    int i;
    char* copia;

    i = 0;
    longitud = strlen(string);
    copia = malloc((longitud+1)*sizeof(char));

    if(copia == NULL){
        return NULL;
    }

    i = 0;
    while(i < longitud){
        copia[i] = string[i];
        i++;
    }
    copia[longitud] = '\0';
    return copia;
}

char** split(const char* string, char separador){
    if(!string){
        return NULL;
    }

    char** vector;
    vector = malloc(2 *sizeof(char*));
    if(!vector){
        return NULL;
    }

    if(string[0] == '\0'){
        vector[0] = strdup(string);
        vector[1] = NULL;
        return vector;
    }

    int contador_separadores = 0;
    size_t len_str = strlen(string);

    for(int i = 0; i < len_str;i++){
        if(string[i] == separador){
            contador_separadores++;
        }
    }
    contador_separadores++;

    vector = realloc(vector,(size_t)(contador_separadores + 1)*sizeof(string));
    int tope_vector = 0;

    int inicio = 0;

    for(int i = 0; i <= len_str; i++){
        char* substring;
        if(string[i] == separador || string[i] == '\0'){
            int len = i - inicio;
            substring = malloc((size_t)(len + 1) * sizeof(char));
            if(!substring){
                return NULL;
            }
            for(int j = 0; j < len; j++){
                substring[j] = string[inicio];
                inicio++;
                if(j == (len -1)){
                    substring[j+1] = '\0';
                }
            }
            if(len == 0){
                substring[len] = '\0';
            }
            inicio++;
            vector[tope_vector] = substring;
            tope_vector++;
        }
    vector[tope_vector] = NULL;
    }

    return vector;
}

/* int main(int argc, char const *argv[]){
    clock_t begin = clock();
    split("1,2,3",',');
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %f segundos",time_spent);
    return 0;
}  */
