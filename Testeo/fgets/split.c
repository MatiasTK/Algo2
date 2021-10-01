#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t contar_separador(const char* string,char separador,int len){
    size_t contador = 0;
    for(int i = 0; i < len;i++){
        if(string[i] == separador){
            contador++;
        }
    }
    return contador;
}

size_t buscar_proximo_separador(const char* string, char separador){
    size_t i = 0;
    while(string[i] != '\0' && string[i] != separador){
        i++;
    }
    return i;
}

char* duplicar_string(const char* string,size_t cantidad){
    char* nuevo_string = malloc((1+cantidad) * sizeof(char));
    if(!nuevo_string){
        return NULL;
    }
    for(size_t i = 0; i < cantidad; i++){
        nuevo_string[i] = string[i];
    }
    nuevo_string[cantidad] = 0;
    return nuevo_string;
}

void liberar_todo(char** vector){
    while(*vector){
        free(*vector);
        vector++;
    }
}

char** split(const char* string,char separador){
    if(!string){
        return NULL;
    }

    int string_len = (int)strlen(string);
    size_t contador = contar_separador(string,separador,string_len);
    size_t substrings = contador+1;

    char** vector = calloc(substrings+1,sizeof(void*));
    if(!vector){
        return NULL;
    }


    for(size_t i = 0; i < substrings;i++){
        size_t tamanio_substring = buscar_proximo_separador(string,separador);
        char* substring = duplicar_string(string,tamanio_substring);
        if(!substring){
            liberar_todo(vector);
            return NULL;
        }
        vector[i] = substring;
        string += tamanio_substring + 1;
    }

    return vector;
}
