#include "hospital.h"
#include "split.h"
#include "lista.h"
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
    lista_t* lista_pokemones;
    size_t cantidad_pokemon;
    size_t cantidad_entrenador;
};

struct _pkm_t{
    char* nombre;
    size_t nivel;
    entrenador_t* entrenador;
};

struct _entrenador_t{
    char* nombre;
    size_t id;
};

/*
* PRE: Recibe un string
* POST: Devuelve una copia del string almacenada en el heap.
*/
char* strdup(char* str){
    char* copia = malloc(strlen(str) + 1);
    strcpy(copia, str);
    return copia;
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
    hospital_t* hospital = calloc(1, sizeof(hospital_t));
    if(!hospital){
        return NULL;
    }

    hospital->lista_pokemones = lista_crear();
    if(!hospital->lista_pokemones){
        free(hospital);
        return NULL;
    }

    return hospital;
}

/*
* PRE: hospital debe estar creado, linea_split debe estar inicializado y ser distinto de null, vector debe estar creado previamente, posicion debe estar incializado
* POST: Agrega el pokemon al vector y aumenta la cantidad de pokemones
*/
void agregar_pokemon(hospital_t* hospital,char** linea_split,int posicion){
    pokemon_t* pokemon = calloc(1,sizeof(pokemon_t));
    if(!pokemon){
        return;
    }
    entrenador_t* entrenador = calloc(1,sizeof(entrenador_t));
    if(!entrenador){
        return;
    }

    entrenador->id = (size_t)atoi(linea_split[POSICION_ID_ENTRENADOR]);
    entrenador->nombre = strdup(linea_split[POSICION_NOMBRE_ENTRENADOR]);

    pokemon->nombre = strdup(linea_split[posicion]);
    pokemon->nivel = (size_t)atoi(linea_split[posicion + 1]);
    pokemon->entrenador = entrenador;

    lista_insertar(hospital->lista_pokemones, pokemon);

    hospital->cantidad_pokemon++;
}  

/*
* PRE: El hospital debe estar creado, linea debe ser una linea valida, vector debe estar creado previamente, size debe estar inicializado
* POST: Busca el proximo pokemon en la linea y la agrega al vector, devuelve false en caso de error o true en caso contrario
*/
bool buscar_y_agregar_pokemon(hospital_t* hospital,char* linea){
    char** linea_split;
    linea_split = split(linea,SEPARADOR);
    if(!linea_split){
        return ERROR;
    }

    int len = split_len(linea_split);
    for(int i = 2; i <= len;i++){  
        if(i % 2 == 0){
            agregar_pokemon(hospital,linea_split,i);
        }
    }
    free(linea_split[POSICION_ID_ENTRENADOR]);
    free(linea_split[POSICION_NOMBRE_ENTRENADOR]); 
    for(int i = 2; i <= len; i++){
        free(linea_split[i]);
    } 
    free(linea_split);
    hospital->cantidad_entrenador++;
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

    while(linea){
        if(buscar_y_agregar_pokemon(hospital,linea) == ERROR){
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

int comparador_pokemones(void* pokemon1, void* pokemon2){
    if(!pokemon1 || !pokemon2){
        return ERROR;
    }
    pokemon_t* p1 = (pokemon_t*)pokemon1;
    pokemon_t* p2 = (pokemon_t*)pokemon2;
    return strcmp(p1->nombre,p2->nombre);
}

size_t hospital_a_cada_pokemon(hospital_t* hospital, bool (*funcion)(pokemon_t* p)){
    if(!hospital || !funcion){
        return 0;
    }
    size_t contador = 0;
    lista_ordenar(hospital->lista_pokemones,comparador_pokemones);

    lista_iterador_t* iterador = lista_iterador_crear(hospital->lista_pokemones);
    if(!iterador){
        return 0;
    }

    while(lista_iterador_tiene_siguiente(iterador)){
        pokemon_t* pokemon = lista_iterador_elemento_actual(iterador);
        if(!funcion(pokemon)){
            contador++;
            lista_iterador_destruir(iterador);
            return contador;
        }
        contador++;
        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);
    return contador;
}

void hospital_destruir(hospital_t* hospital){
    if(!hospital){
        return;
    }

    lista_iterador_t* iterador = lista_iterador_crear(hospital->lista_pokemones);
    if(!iterador){
        lista_destruir(hospital->lista_pokemones);
        free(hospital);
        return;
    }

    while(lista_iterador_tiene_siguiente(iterador)){
        pokemon_t* pokemon = lista_iterador_elemento_actual(iterador);
        free(pokemon->nombre);
        free(pokemon->entrenador->nombre);
        free(pokemon->entrenador);
        free(pokemon);
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);
    lista_destruir(hospital->lista_pokemones);

    free(hospital);

    return;
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

entrenador_t* pokemon_entrenador(pokemon_t* pokemon){
    if(!pokemon){
        return NULL;
    }
    return pokemon->entrenador;
}

bool hospital_guardar_archivo(hospital_t* hospital, const char* nombre_archivo){ 
    if(!hospital || !nombre_archivo || hospital->cantidad_pokemon == 0){
        return ERROR;
    }

    FILE* archivo = fopen(nombre_archivo,"w");
    if(!archivo){
        return ERROR;
    }

    bool entrenador_escrito = false;

    for(int i = 1; i < hospital->cantidad_entrenador + 1; i++){
        fprintf(archivo,"%i",i);

        lista_iterador_t* iterador = lista_iterador_crear(hospital->lista_pokemones);
        if(!iterador){
            fclose(archivo);
            return ERROR;
        }

        while(lista_iterador_tiene_siguiente(iterador)){
            pokemon_t* pokemon = lista_iterador_elemento_actual(iterador);

            if(pokemon->entrenador->id == i){

                if(entrenador_escrito == false){
                    fprintf(archivo,";%s",pokemon->entrenador->nombre);
                    entrenador_escrito = true;
                }

                fprintf(archivo,";%s;%ld",pokemon->nombre,pokemon->nivel);
            }
            lista_iterador_avanzar(iterador);
        }

        fprintf(archivo,"\n");

        entrenador_escrito = false;

        lista_iterador_destruir(iterador);
    }

    fclose(archivo);
    return EXITO;
}