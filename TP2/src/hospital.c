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
    lista_t* lista_entrenadores;
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
    lista_t* lista_pokemones;
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

    hospital->lista_entrenadores = lista_crear();
    if(!hospital->lista_entrenadores){
        free(hospital);
        return NULL;
    }

    return hospital;
}

/*
* PRE: Recibe una lista_pokemones inicializada, la linea split, la posicion del split en la que esta, y el entrenador del pokemon.
* POST: Añade el pokemon a la lista de pokemones del entrenador.
*/
void agregar_pokemon(lista_t* lista_pokemones,char** linea_split,int posicion, entrenador_t* entrenador){
    pokemon_t* pokemon_nuevo = calloc(1, sizeof(pokemon_t));
    if(!pokemon_nuevo){
        return;
    }

    pokemon_nuevo->nombre = strdup(linea_split[posicion]);
    pokemon_nuevo->nivel = (size_t)atoi(linea_split[posicion + 1]);
    pokemon_nuevo->entrenador = entrenador;

    lista_insertar(lista_pokemones, pokemon_nuevo);

    return;
}  

/*
* PRE: El hospital debe estar creado, linea debe ser una linea valida.
* POST: Añade el entrenador a la lista de entrenadores del hospital con sus debidos pokemones. La lista de entrenadores debe estar inicializada. Devuelve false en caso de error o true en caso de exito.
*/
bool buscar_y_agregar_pokemon(hospital_t* hospital,char* linea){
    char** linea_split;
    linea_split = split(linea,SEPARADOR);
    if(!linea_split){
        return ERROR;
    }

    entrenador_t* entrenador_nuevo = calloc(1, sizeof(entrenador_t));
    if(!entrenador_nuevo){
        return ERROR;
    }

    entrenador_nuevo->nombre = strdup(linea_split[POSICION_NOMBRE_ENTRENADOR]);
    entrenador_nuevo->id = (size_t)atoi(linea_split[POSICION_ID_ENTRENADOR]);
    entrenador_nuevo->lista_pokemones = lista_crear();
    if(!entrenador_nuevo->lista_pokemones){
        free(entrenador_nuevo);
        return ERROR;
    }

    int len = split_len(linea_split);
    for(int i = 2; i <= len;i++){  
        if(i % 2 == 0){
            agregar_pokemon(entrenador_nuevo->lista_pokemones,linea_split,i, entrenador_nuevo);
            hospital->cantidad_pokemon++;
        }
    }
    free(linea_split[POSICION_ID_ENTRENADOR]);
    free(linea_split[POSICION_NOMBRE_ENTRENADOR]); 
    for(int i = 2; i <= len; i++){
        free(linea_split[i]);
    } 
    free(linea_split);
    lista_insertar(hospital->lista_entrenadores, entrenador_nuevo);
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

/*
* PRE: Recibe dos pokemones.
* POST: Devuelve 0 si el nombre de los dos pokemones son iguales, 1 si el primero es mayor alfabeticamente y -1 si el segundo es mayor alfabeticamente.
*/
int comparador_pokemones(void* pokemon1, void* pokemon2){
    if(!pokemon1 || !pokemon2){
        return ERROR;
    }
    pokemon_t* p1 = (pokemon_t*)pokemon1;
    pokemon_t* p2 = (pokemon_t*)pokemon2;
    return strcmp(p1->nombre,p2->nombre);
}

/*
* PRE: Recibe un hospital y una lista ya inicializada.
* POST: Carga la lista con todos los pokemones del hospital sin importar su entrenador.
*/
void cargar_pokemones_en_lista(hospital_t* hospital, lista_t* lista_pokemones){
    if(!hospital || !lista_pokemones){
        return;
    }
    
    lista_iterador_t* iterador = lista_iterador_crear(hospital->lista_entrenadores);
    if(!iterador){
        return;
    }

    while(lista_iterador_tiene_siguiente(iterador)){
        entrenador_t* entrenador = lista_iterador_elemento_actual(iterador);
        if(!entrenador){
            lista_iterador_destruir(iterador);
            return;
        }

        lista_iterador_t* iterador_pokemones = lista_iterador_crear(entrenador->lista_pokemones);
        if(!iterador_pokemones){
            lista_iterador_destruir(iterador);
            return;
        }

        while(lista_iterador_tiene_siguiente(iterador_pokemones)){
            pokemon_t* pokemon = lista_iterador_elemento_actual(iterador_pokemones);
            if(!pokemon){
                lista_iterador_destruir(iterador_pokemones);
                lista_iterador_destruir(iterador);
                return;
            }
            lista_insertar(lista_pokemones, pokemon);
            lista_iterador_avanzar(iterador_pokemones);
        }
        lista_iterador_destruir(iterador_pokemones);
        
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);
}

size_t hospital_a_cada_pokemon(hospital_t* hospital, bool (*funcion)(pokemon_t* p)){
    if(!hospital || !funcion){
        return 0;
    }
    size_t contador = 0;

    lista_t* lista_pokemones = lista_crear();
    if(!lista_pokemones){
        return 0;
    }

    cargar_pokemones_en_lista(hospital, lista_pokemones);

    lista_ordenar(lista_pokemones,comparador_pokemones); //Ordeno la lista de pokemones alfabeticamente.

    lista_iterador_t* iterador = lista_iterador_crear(lista_pokemones);
    if(!iterador){
        return 0;
    }

    while(lista_iterador_tiene_siguiente(iterador)){
        pokemon_t* pokemon = lista_iterador_elemento_actual(iterador);
        if(!funcion(pokemon)){
            contador++;
            lista_iterador_destruir(iterador);
            lista_destruir(lista_pokemones);
            return contador;
        }
        contador++;
        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);

    lista_destruir(lista_pokemones);

    return contador;
}

void hospital_destruir(hospital_t* hospital){
    if(!hospital){
        return;
    }

    lista_iterador_t* iterador_entrenadores = lista_iterador_crear(hospital->lista_entrenadores);
    if(!iterador_entrenadores){
        free(hospital);
        return;
    }

    while(lista_iterador_tiene_siguiente(iterador_entrenadores)){
        entrenador_t* entrenador = lista_iterador_elemento_actual(iterador_entrenadores);
        
        lista_iterador_t* iterador_pokemones = lista_iterador_crear(entrenador->lista_pokemones);
        while(lista_iterador_tiene_siguiente(iterador_pokemones)){
            pokemon_t* pokemon = lista_iterador_elemento_actual(iterador_pokemones);

            free(pokemon->nombre);
            free(pokemon);

            lista_iterador_avanzar(iterador_pokemones);
        }

        lista_iterador_destruir(iterador_pokemones);

        lista_destruir(entrenador->lista_pokemones);

        free(entrenador->nombre);
        free(entrenador);
        lista_iterador_avanzar(iterador_entrenadores);
    }
    lista_iterador_destruir(iterador_entrenadores);
    lista_destruir(hospital->lista_entrenadores);

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

    lista_iterador_t* iterador_entrenadores = lista_iterador_crear(hospital->lista_entrenadores);
    if(!iterador_entrenadores){
        fclose(archivo);
        return ERROR;
    }

    while(lista_iterador_tiene_siguiente(iterador_entrenadores)){
        entrenador_t* entrenador = lista_iterador_elemento_actual(iterador_entrenadores);
        if(!entrenador){
            fclose(archivo);
            return ERROR;
        }

        fprintf(archivo,"%ld;%s",entrenador->id,entrenador->nombre);

        lista_iterador_t* iterador_pokemones = lista_iterador_crear(entrenador->lista_pokemones);

        while(lista_iterador_tiene_siguiente(iterador_pokemones)){
            pokemon_t* pokemon = lista_iterador_elemento_actual(iterador_pokemones);
            if(!pokemon){
                fclose(archivo);
                return ERROR;
            }

            fprintf(archivo,";%s;%ld",pokemon->nombre,pokemon->nivel);

            lista_iterador_avanzar(iterador_pokemones);
        }

        lista_iterador_destruir(iterador_pokemones);

        fprintf(archivo,"\n");

        lista_iterador_avanzar(iterador_entrenadores);
    }

    lista_iterador_destruir(iterador_entrenadores);

    fclose(archivo);
    return EXITO; 
}