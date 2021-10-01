#include "hospital.h"
#include "split.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SEPARADOR ';'
#define TAM_BUFFER_INI 512

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
* PRE: String debe ser un string valido
* POST: Devuelve un puntero que es una copia del string recibido
*/
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

/*
* PRE: Archivo debe ser un archivo valido
* POST: Lee la linea de un archivo y devuelve un puntero hacia el string de esa linea
*/
char* leer_linea(FILE* archivo){
    size_t bytes_leidos= 0;
    size_t tam_buffer = TAM_BUFFER_INI;

    char* buffer = malloc(sizeof(char) * tam_buffer);
    if (!buffer){
        return NULL;
    }

    while (fgets(buffer + bytes_leidos, (int)(tam_buffer - bytes_leidos), archivo)){
        size_t leido = strlen(buffer + bytes_leidos);
        if (leido > 0 && *(buffer + bytes_leidos + leido - 1) == '\n'){
            return buffer;
        }else{
            char* auxiliar = realloc(buffer, sizeof(char) * tam_buffer + TAM_BUFFER_INI);
            if(!auxiliar) {
                free(buffer);
                return NULL;
            }
            buffer = auxiliar;
            tam_buffer += TAM_BUFFER_INI;
        }
        bytes_leidos += leido;
    }

    if(bytes_leidos == 0) {
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
    char* nombre = strdup(linea_split[posicion]);
    char* nivel = strdup(linea_split[posicion+1]);
    hospital->vector_pokemones = vector;
    hospital->vector_pokemones[hospital->cantidad_pokemon].nombre = nombre;
    hospital->vector_pokemones[hospital->cantidad_pokemon].nivel = (size_t)atoi(nivel);
    hospital->cantidad_pokemon++;
    free(nivel);
}

/*
* PRE: El hospital debe estar creado, linea debe ser una linea valida, vector debe estar creado previamente, size debe estar inicializado
* POST: Busca el proximo pokemon en la linea y la agrega al vector, devuelve false en caso de error o true en caso contrario
*/
bool buscar_y_agregar_pokemon(hospital_t* hospital,char* linea,pokemon_t* vector,size_t size){
    char** linea_split;
    linea_split = split(linea,SEPARADOR);
    if(!linea_split){
        free(linea);
        return false;
    }
    int len = split_len(linea_split);
    for(int i = 2; i <= len;i++){
        if(i % 2 == 0){
            if(hospital->cantidad_pokemon >= size){
                size = (hospital->cantidad_pokemon * 2);
                pokemon_t* vector_aux = NULL;
                vector_aux = realloc(hospital->vector_pokemones,sizeof(pokemon_t) * (size));
                if(!vector_aux){
                    free(linea);
                    free(linea_split);
                    return false;
                }
                vector = vector_aux;
            }
            agregar_pokemon(hospital,linea_split,vector,i);
        }
    }
    hospital->cantidad_entrenador++; 
    for(int i = 0; i <= len; i++){
        free(linea_split[i]);
    } 
    free(linea_split); 
    free(linea);
    return true;
}

bool hospital_leer_archivo(hospital_t* hospital, const char* nombre_archivo){
    if(!hospital){
        return false;
    }
    
    FILE* archivo = fopen(nombre_archivo,"r");
    if(!archivo){
        return false;
    }

    char* linea = leer_linea(archivo);
    if(!linea){
        fclose(archivo);
        return true;
    }
    size_t size = (hospital->cantidad_pokemon + 1);
    pokemon_t* vector = realloc(hospital->vector_pokemones,sizeof(pokemon_t) * (size));
    if(!vector){
        free(linea);
        fclose(archivo);
        return false;
    }
    while(linea){
        if(buscar_y_agregar_pokemon(hospital,linea,vector,size) == false){
            fclose(archivo);
            return false;
        }
        linea = leer_linea(archivo);
    }
    fclose(archivo);
    return true;
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
        if(funcion(vector_ordenado) == false){
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
    for(int i = 0; i < hospital_cantidad_pokemon(hospital);i++){
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