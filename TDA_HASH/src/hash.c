#include "hash.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

#define EXITO 0
#define ERROR -1
#define FACTOR_CARGA 0.75

struct hash{
    lista_t** tabla;
    size_t capacidad;
    size_t cantidad;
    hash_destruir_dato_t destructor;
};

typedef struct elemento{
    char* clave;
    void* valor;
} elemento_t;

/*
* PRE: Recibe una tabla y su capacidad.
* POST: Destruye la tabla de hush en su totalidad
*/
void destruir_tabla(lista_t** tabla, size_t capacidad){
    for(size_t i=0; i < capacidad; i++){
        lista_destruir(tabla[i]);
    }

    free(tabla);
}

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial){
    hash_t* hash = malloc(sizeof(hash_t));
    if(!hash){
        return NULL;
    }

    if(capacidad_inicial < 3){
        capacidad_inicial = 3;
    }

    lista_t** tabla = calloc(capacidad_inicial, sizeof(lista_t*));
    if(!tabla){
        free(hash);
        return NULL;
    }

    for(int i = 0; i < capacidad_inicial; i++){
        tabla[i] = lista_crear();

        if(!tabla[i]){
            destruir_tabla(tabla, capacidad_inicial);
            return NULL;
        }
    }

    hash->tabla = tabla;
    hash->capacidad = capacidad_inicial;
    hash->cantidad = 0;
    hash->destructor = destruir_elemento;

    return hash;
}

/*
* PRE: Recibe una clave y la capacidad del hash.
* POST: Devuelve la posicion correspondiente en el hash a la clave.
*/
size_t funcion_hash(const char* clave, size_t capacidad){
    size_t indice = 0;

    for(size_t i = 0; clave[i]; i++){
        indice += clave[i];
    }

    return indice % capacidad;
}

/*
* PRE: Recibe un hash valido.
* POST: Aumenta la capacidad del hash. Devuelve 0 en caso de exito o -1 en caso de error.
*/
int rehash(hash_t* hash){
    size_t capacidad_nueva = hash->capacidad * 2;

    lista_t** tabla_nueva = calloc(capacidad_nueva, sizeof(lista_t*));
    if(!tabla_nueva){
        return ERROR;
    }

    for(size_t i = 0; i < capacidad_nueva; i++){
        tabla_nueva[i] = lista_crear();

        if(!tabla_nueva[i]){
            destruir_tabla(tabla_nueva, capacidad_nueva);
            return ERROR;
        }
    }

    for(size_t i = 0; i < hash->capacidad; i++){
        lista_iterador_t* iterador = lista_iterador_crear(hash->tabla[i]);

        while(lista_iterador_tiene_siguiente(iterador)){
            elemento_t* elemento = lista_iterador_elemento_actual(iterador);
            size_t posicion = funcion_hash(elemento->clave, capacidad_nueva);

            if(lista_insertar(tabla_nueva[posicion],elemento) == NULL){
                lista_iterador_destruir(iterador);
                destruir_tabla(tabla_nueva, capacidad_nueva);
                return ERROR;
            }

            lista_iterador_avanzar(iterador);
        }

        lista_iterador_destruir(iterador);
    }

    destruir_tabla(hash->tabla, hash->capacidad);

    hash->tabla = tabla_nueva;
    hash->capacidad = capacidad_nueva;

    return EXITO;
}

/*
* PRE: Recibe un hash y una clave.
* POST: Devuelve el elemento correspondiente a la clave. O NULL en caso de no encontrarlo/error.
*/
elemento_t* buscar_elemento(hash_t* hash, const char* clave){
    if(!hash || !clave){
        return NULL;
    }

    size_t posicion = funcion_hash(clave, hash->capacidad);

    lista_iterador_t* iterador = lista_iterador_crear(hash->tabla[posicion]);
    if(!iterador){
        return NULL;
    }
 
    while(lista_iterador_tiene_siguiente(iterador)){
        elemento_t* elemento = lista_iterador_elemento_actual(iterador);
    
        if(strcmp(elemento->clave, clave) == 0){
            lista_iterador_destruir(iterador);
            return elemento;
        }

        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);

    return NULL;
}

/*
* PRE: Recibe una clave
* POST: Devuelve una copia de la clave.
*/
char* copiar_clave(const char* clave){

    char* copia = malloc(strlen(clave) + 1);
    if(!copia){
        return NULL;
    }

    strcpy(copia, clave);

    return copia;
}

/*
* PRE: Recibe un hash, una clave y un valor.
* POST: Modifica el valor del elemento en el hash. Devuelve 0 en caso de exito o -1 en caso de error.
*/
int modificar_valor_hash(hash_t* hash, const char* clave, void* elemento){
    if(!hash){
        return ERROR;
    }

    elemento_t* elemento_nuevo = buscar_elemento(hash, clave);
    if(!elemento_nuevo){
        return ERROR;
    }

    if(hash->destructor){
        hash->destructor(elemento_nuevo->valor);
    }

    elemento_nuevo->valor = elemento;

    return EXITO;
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento){
    if(!hash || !clave){
        return ERROR;
    }

    if(hash->cantidad / hash->capacidad >= FACTOR_CARGA){
        rehash(hash);
    }

    size_t posicion = funcion_hash(clave, hash->capacidad);

    if(hash_contiene(hash, clave)){
        return modificar_valor_hash(hash, clave, elemento);
    }

    elemento_t* elemento_nuevo = calloc(1, sizeof(elemento_t));
    if(!elemento_nuevo){
        return ERROR;
    }

    elemento_nuevo->valor = elemento;
    elemento_nuevo->clave = copiar_clave(clave);

    if(lista_insertar(hash->tabla[posicion], elemento_nuevo) == NULL){
        free(elemento_nuevo->clave);
        free(elemento_nuevo);
        return ERROR;
    }

    hash->cantidad++;

    return EXITO;
}

/*
* PRE: Recibe un hash y una clave.
* POST: Devuelve la posicion en el hash en donde esta esa clave.
*/
size_t buscar_posicion_en_lista(hash_t* hash, const char* clave){
    if(!hash || !clave){
        return 0;
    }
    
    size_t posicion_encontrada = 0;

    size_t pos = funcion_hash(clave, hash->capacidad);

    lista_iterador_t* iterador = lista_iterador_crear(hash->tabla[pos]);
    if(!iterador){
        return 0;
    }

    while(lista_iterador_tiene_siguiente(iterador)){
        elemento_t* elemento = lista_iterador_elemento_actual(iterador);

        if(strcmp(elemento->clave, clave) == 0){
            lista_iterador_destruir(iterador);
            return posicion_encontrada;
        }

        posicion_encontrada++;

        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);

    return posicion_encontrada;
}

int hash_quitar(hash_t* hash, const char* clave){
    if(!hash || !clave){
        return ERROR;
    }

    size_t posicion = funcion_hash(clave,hash->capacidad);

    elemento_t* elemento_a_eliminar = buscar_elemento(hash, clave);
    if(!elemento_a_eliminar){
        return ERROR;
    }

    size_t posicion_a_eliminar = buscar_posicion_en_lista(hash, clave);

    if(lista_quitar_de_posicion(hash->tabla[posicion], posicion_a_eliminar) == NULL){
        return ERROR;
    }

    if(hash->destructor){
        hash->destructor(elemento_a_eliminar->valor);
    }
    free(elemento_a_eliminar->clave);
    free(elemento_a_eliminar);

    hash->cantidad--;

    return EXITO;
}

void* hash_obtener(hash_t* hash, const char* clave){
    if(!hash || !clave){
        return NULL;
    }

    elemento_t* elemento = buscar_elemento(hash, clave);
    if(!elemento){
        return NULL;
    }

    return elemento->valor;
}

bool hash_contiene(hash_t* hash, const char* clave){
    if(!hash || !clave || hash->cantidad == 0){
        return false;
    }

    return buscar_elemento(hash, clave) != NULL;
}

size_t hash_cantidad(hash_t* hash){
    if(!hash){
        return 0;
    }

    return hash->cantidad;
}

void hash_destruir(hash_t* hash){
    if(!hash){
        return;
    }

    for(size_t i = 0; i < hash->capacidad; i++){
        while(!lista_vacia(hash->tabla[i])){
            elemento_t* elemento = lista_ultimo(hash->tabla[i]);

            if(hash->destructor){
                hash->destructor(elemento->valor);
            }
            free(elemento->clave);
            free(elemento);

            lista_quitar(hash->tabla[i]);
        }

        lista_destruir(hash->tabla[i]);
    }

    free(hash->tabla);
    free(hash);
}

size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
    if(!hash || !funcion){
        return 0;
    }

    size_t cantidad = 0;

    for(size_t i = 0; i < hash->capacidad; i++){
        lista_iterador_t* iterador = lista_iterador_crear(hash->tabla[i]);
        if(!iterador){
            return 0;
        }

        while(lista_iterador_tiene_siguiente(iterador)){
            elemento_t* elemento = lista_iterador_elemento_actual(iterador);

            if(!funcion(hash, elemento->clave, aux)){
                cantidad++;
            }else{
                cantidad++;
                lista_iterador_destruir(iterador);
                return cantidad;
            }
            lista_iterador_avanzar(iterador);
        }
        lista_iterador_destruir(iterador);
    }
    return cantidad;
}
