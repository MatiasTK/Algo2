#include "hospital.h"
#include "split.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SEPARADOR ';'
#define BUFFER_INICIAL 512

#define ERROR false
#define EXITO true

#define POSICION_ID_ENTRENADOR 0
#define POSICION_NOMBRE_ENTRENADOR 1

struct _hospital_pkm_t{
    size_t cantidad_pokemon;
    pokemon_t* vector_pokemones;
    size_t cantidad_entrenador;
};

struct _pkm_t{
    char* nombre;
    size_t nivel;
};

/*
* PRE: hospital debe ser un hospital valido, tope debe estar inicializado
* POST: Ordena un vector de pokemones con el metodo de ordenamiento bubble sort y devuelve un puntero del vector ordenado
*/
pokemon_t* bubble_sort(hospital_t* hospital, int tope){
    pokemon_t aux;
    for(int i = 0; i < tope; i++){
        for(int j = 0; j < tope - i - 1; j++){
            if(strcmp(hospital->vector_pokemones[j].nombre,hospital->vector_pokemones[j+1].nombre) > 0){
                aux = hospital->vector_pokemones[j];
                hospital->vector_pokemones[j] = hospital->vector_pokemones[j+1];
                hospital->vector_pokemones[j+1] = aux;
            }
        }
    }
    return hospital->vector_pokemones;
}

/* 
* PRE: Archivo debe ser un archivo valido
* POST: Lee la linea de un archivo y devuelve un puntero hacia el string de esa linea
*/
char* leer_linea(FILE* archivo){
    size_t bytes_leidos = 0;
    size_t tam_buffer = BUFFER_INICIAL;

    char* buffer = malloc(sizeof(char) * tam_buffer);
    if (!buffer){
        return NULL;
    }

    while (fgets(buffer + bytes_leidos, (int)(tam_buffer - bytes_leidos), archivo)){
        size_t leido = strlen(buffer + bytes_leidos);
        if (leido > 0 && *(buffer + bytes_leidos + leido - 1) == '\n'){
            return buffer;
        }else{
            char* auxiliar = realloc(buffer, sizeof(char) * tam_buffer + BUFFER_INICIAL);
            if(!auxiliar) {
                free(buffer);
                return NULL;
            }
            buffer = auxiliar;
            tam_buffer += BUFFER_INICIAL;
        }
        bytes_leidos += leido;
    }
    
    if(bytes_leidos == 0){
        free(buffer);
        return NULL;
    }

    return buffer;
}

/*
* PRE: String debe ser un string valido
* POST: Devuelve la cantidad de elementos en la que se spliteo una linea
*/
int split_len(char** string){
    int len = 0;
    while(string[len] != 0){
        len++;
    }
    len--;
    return len;
}

hospital_t* hospital_crear(){
    return calloc(1,sizeof(hospital_t));
}

/*
* PRE: hospital debe estar creado, linea_split debe estar inicializado y ser distinto de null, vector debe estar creado previamente, posicion debe estar incializado
* POST: Agrega el pokemon al vector y aumenta la cantidad de pokemones
*/
void agregar_pokemon(hospital_t* hospital,char** linea_split, pokemon_t* vector,int posicion){
    hospital->vector_pokemones = vector;
    hospital->vector_pokemones[hospital->cantidad_pokemon].nombre = linea_split[posicion];
    hospital->vector_pokemones[hospital->cantidad_pokemon].nivel = (size_t)atoi(linea_split[posicion+1]);
    hospital->cantidad_pokemon++;
}

/*
* PRE: El hospital debe estar creado, linea debe ser una linea valida, vector debe estar creado previamente, size debe estar inicializado
* POST: Busca el proximo pokemon en la linea y la agrega al vector, devuelve false en caso de error o true en caso contrario
*/
bool buscar_y_agregar_pokemon(hospital_t* hospital,char* linea,pokemon_t* vector,size_t size){
    char** linea_split;
    linea_split = split(linea,SEPARADOR);
    if(!linea_split){
        return ERROR;
    }
    int len = split_len(linea_split);
    for(int i = 2; i <= len;i++){
        if(i % 2 == 0){
            if(hospital->cantidad_pokemon >= size){
                size = (hospital->cantidad_pokemon * 2);
                pokemon_t* vector_aux = NULL;
                vector_aux = realloc(hospital->vector_pokemones,sizeof(pokemon_t) * (size));
                if(!vector_aux){
                    free(linea_split);
                    return ERROR;
                }
                vector = vector_aux;
            }
            agregar_pokemon(hospital,linea_split,vector,i);
        }
    }
    hospital->cantidad_entrenador++;
    free(linea_split[POSICION_ID_ENTRENADOR]);
    free(linea_split[POSICION_NOMBRE_ENTRENADOR]); 
    for(int i = 2; i <= len; i++){
        if(i % 2 == 0){
            free(linea_split[i+1]);
        }
    } 
    free(linea_split); 
    return EXITO;
}

bool hospital_leer_archivo(hospital_t* hospital, const char* nombre_archivo){
    if(!hospital){
        return ERROR;
    }
    
    FILE* archivo = fopen(nombre_archivo,"r"); 
    if(!archivo){
        return ERROR;
    }else{
        int is_empty = fgetc(archivo);
        if(is_empty == EOF){
            fclose(archivo);
            return EXITO;
        }
        ungetc(is_empty,archivo);
    }

    char* linea = leer_linea(archivo);
    if(!linea){
        free(linea);
        fclose(archivo);
        return ERROR;
    }
    size_t size = (hospital->cantidad_pokemon + 1);
    pokemon_t* vector = realloc(hospital->vector_pokemones,sizeof(pokemon_t) * (size));
    if(!vector){
        free(linea);
        fclose(archivo);
        return ERROR;
    }
    while(linea){
        if(buscar_y_agregar_pokemon(hospital,linea,vector,size) == ERROR){
            free(linea);
            fclose(archivo);
            return ERROR;
        }
        free(linea);
        linea = leer_linea(archivo);
    }
    fclose(archivo);
    return EXITO;
}

size_t hospital_cantidad_pokemon(hospital_t* hospital){
    if(!hospital){
        return 0;
    }
    return hospital->cantidad_pokemon;
}

size_t hospital_cantidad_entrenadores(hospital_t* hospital){
    if(!hospital){
        return 0;
    }
    return hospital->cantidad_entrenador;
}

size_t hospital_a_cada_pokemon(hospital_t* hospital, bool (*funcion)(pokemon_t* p)){
    if(!hospital || !funcion){
        return 0;
    }
    size_t contador = 0;
    size_t tope = hospital_cantidad_pokemon(hospital);
    pokemon_t* vector_ordenado = bubble_sort(hospital,(int)tope);
    for(int i = 0; i < tope; i++){
        if(funcion(vector_ordenado) == ERROR){
            contador++;
            return contador;
        }
        vector_ordenado++;
        contador++;
    }
    return contador;
}

void hospital_destruir(hospital_t* hospital){
    if(!hospital){
        return;
    }
    size_t tope = hospital_cantidad_pokemon(hospital);
    for(int i = 0; i < tope;i++){
        free(hospital->vector_pokemones[i].nombre);
    }
    free(hospital->vector_pokemones);
    free(hospital);
}

size_t pokemon_nivel(pokemon_t* pokemon){
    if(!pokemon){
        return 0;
    }
    return pokemon->nivel;
}

const char* pokemon_nombre(pokemon_t* pokemon){
    if(!pokemon){
        return NULL;
    }
    return pokemon->nombre;
}