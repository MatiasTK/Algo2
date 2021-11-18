#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "split.h"

typedef struct pokemon{
    char* nombre;
    size_t nivel;
} pokemon_t;

typedef struct entrenadores{
    char* nombre;
    size_t id_entrenador;
}entrenadores_t;

typedef struct hospital{
    size_t cantidad_pokemon;
    pokemon_t vector_pokemones[100];
    size_t cantidad_entrenadores;
    entrenadores_t vector_entrenadores[100];
} hospital_t;


char* leer_linea_dinamico(FILE* archivo){
    size_t tamanio = 1024;
    size_t offset = 0;
    size_t bytes_leidos = 0;
    char* buffer = malloc(tamanio);
    if(!buffer){
        return NULL;
    }
    while(fgets(buffer+bytes_leidos,tamanio-bytes_leidos,archivo)){
        size_t leido = strlen(buffer + bytes_leidos);
        if(leido > 0 && *(buffer+bytes_leidos+leido-1) == '\n'){
            *(buffer+bytes_leidos+leido-1) = 0;
            return buffer;
        }else{
            char* aux = realloc(buffer, tamanio*2);
            if(!aux){
                free(buffer);
                return NULL;
            }
            buffer = aux;
            tamanio *= 2;
        }
        bytes_leidos += leido;
    }
    if(bytes_leidos == 0){
        free(buffer);
        return NULL;
    }

    return buffer;
}

int main(int argc, char const *argv[]){
    FILE* file = fopen("texto.txt","r");
    if(!file){
        perror("No se pudo abrir el archivo");
        return -1;
    }

    char* linea = leer_linea_dinamico(file);

    while(linea != NULL){
        char** linea_split = split(linea,';');
        int i = 0;
        while(linea_split[i] != NULL){
            printf("%s \n",linea_split[i]);
            i++;
        }
        printf("Tamaño del split: %i",i);
        
        linea = leer_linea_dinamico(file);
    }
    

    fclose(file);

    return 0;
}
