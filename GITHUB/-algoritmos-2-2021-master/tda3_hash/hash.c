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

