

#include <stdlib.h>
#include <stdbool.h>


typedef struct _abb_t abb_t;

typedef enum {INORDEN,PREORDEN,POSORDEN} recorrido_abb_t;

abb_t* abb_crear();

abb_t* abb_insertar(abb_t* abb,void* elemento,int (comparador)(void*,void*));

abb_t abb_buscar(abb_t* abb,void* elemento,int (comparador)(void*,void*));

abb_t* abb_quitar(abb_t* abb,void* elemento,int (comparador)(void*,void*),void (*destruir_elemento)(void*));

size_t abb_con_cada_elemento(abb_t* abb, recorrido_abb_t recorrido, bool(*funcion)(void*,void*),void* aux);

void abb_destruir(abb_t* abb);

void abb_destruir_todo(abb_t* abb,void(*destruir_elemento)(void*));