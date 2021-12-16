#include "pa2mm.h"
#include "src/hash.h"
#include <string.h>

#define EXITO 0
#define ERROR -1

#define CAPACIDAD_INICIAL 4

/*
* PRE: Recibe un hash, una clave y un auxiliar.
* POST: Castea el auxiliar a size_t y lo aumenta, imprime por pantalla el contenido de la clave y retorna false.
*/
bool visitar_todos_elementos(hash_t* hash, const char* clave, void* aux){
    printf("%s\n", clave);

    (*(size_t*)aux)++;

    return false;
}

/*
* PRE: Recibe un hash, una clave y un auxiliar.
* POST: Castea el auxiliar a size_t y lo aumenta, imprime por pantalla el contenido de la clave y retorna false si la clave es diferente a "clave2", en caso contrario devuelve true.
*/
bool visitar_hasta_la_clave_2(hash_t* hash, const char* clave, void* aux){
    printf("%s\n", clave);
    
    (*(size_t*)aux)++;

    if(strcmp(clave, "clave2") == 0){
        return true;
    }

    return false;
}

/*
* PRE: Recibe un string
* POST: Retorna una copia del string reservada en el heap.
*/
char* copiar_string(const char* string){
    if(!string){
        return NULL;
    }

    char* copia = malloc(strlen(string) + 1);
    strcpy(copia, string);

    return copia;
}

int cantidad_de_invocaciones_a_destructor = 0;

/*
* PRE: Recibe un dato.
* POST: Libera ese dato mediante free y aumenta la cantidad de invocaciones a destructor.
*/
void destructor(void* dato){
    cantidad_de_invocaciones_a_destructor++;
    free(dato);
}

// -----------------------------------------------------------------------------
void PuedoCrearUnHashConTamanio10(){
    hash_t* hash = hash_crear(NULL,10);

    pa2m_afirmar(hash != NULL,"Puedo crear un hash con tamanio 10");

    hash_destruir(hash);
}

void PuedoCrearUnHashConTamanio1(){
    hash_t* hash = hash_crear(NULL,1);

    pa2m_afirmar(hash != NULL,"Puedo crear un hash con tamanio 1");

    hash_destruir(hash);
}

void PuedoCrearUnHashConDestructor(){
    hash_t* hash = hash_crear(free,10);

    pa2m_afirmar(hash != NULL,"Puedo crear un hash con destructor");

    hash_destruir(hash);
}

void NoPuedoInsertarElementosEnHashNULL(){
    hash_t* hash = NULL;

    char* clave = "clave";
    char* valor = "valor";

    pa2m_afirmar(hash == NULL, "Creo un nuevo hash NULL");
    pa2m_afirmar(hash_insertar(hash,clave,valor) == ERROR, "No puedo insertar elementos en un hash NULL");
}

void PuedoInsertarUnElementoEnHashNoNULL(){
    hash_t* hash = hash_crear(NULL, CAPACIDAD_INICIAL);

    char* clave = "clave";
    char* valor = "valor";

    pa2m_afirmar(hash != NULL, "Creo un nuevo hash no NULL");
    pa2m_afirmar(hash_insertar(hash,clave,valor) == EXITO, "Puedo insertar un elemento en un hash no NULL");

    hash_destruir(hash);
}

void PuedoInsertarVariosElementosEnHashNoNULL(){
    hash_t* hash = hash_crear(NULL, CAPACIDAD_INICIAL);

    char* clave = "clave";
    char* valor = "valor";

    pa2m_afirmar(hash != NULL, "Creo un nuevo hash no NULL");
    pa2m_afirmar(hash_insertar(hash,clave,valor) == EXITO, "Puedo insertar un elemento en un hash no NULL");

    clave = "clave2";
    valor = "valor2";

    pa2m_afirmar(hash_insertar(hash,clave,valor) == EXITO, "Puedo insertar un elemento en un hash no NULL");

    clave = "clave3";
    valor = "valor3";

    pa2m_afirmar(hash_insertar(hash,clave,valor) == EXITO, "Puedo insertar un elemento en un hash no NULL");

    hash_destruir(hash);
}

void PuedoInsertarElementosDeValorNULLEnHashNoNULL(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave = "clave";
    char* valor = NULL;
    char* clave2 = "clave2";
    char* valor2 = NULL;
    char* clave3 = "clave3";
    char* valor3 = NULL;

    pa2m_afirmar(hash != NULL, "Creo un nuevo hash no NULL");
    pa2m_afirmar(hash_insertar(hash,clave,valor) == EXITO, "Puedo insertar un elemento con valor NULL en un hash no NULL");
    pa2m_afirmar(hash_insertar(hash,clave2,valor2) == EXITO, "Puedo insertar un elemento con valor NULL en un hash no NULL");
    pa2m_afirmar(hash_insertar(hash,clave3,valor3) == EXITO, "Puedo insertar un elemento con valor NULL en un hash no NULL");

    hash_destruir(hash);
}

void PuedoInsertarElementosConColisionEnHashNoNULL(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave = "clave";
    char* valor = "valor";
    char* clave2 = "clave2";
    char* valor2 = "valor2";
    char* clave3 = "clave3";
    char* valor3 = "valor3";

    pa2m_afirmar(hash != NULL, "Creo un nuevo hash no NULL");
    pa2m_afirmar(hash_insertar(hash,clave,valor) == EXITO, "Puedo insertar un elemento con valor NULL en un hash no NULL");
    pa2m_afirmar(hash_insertar(hash,clave2,valor2) == EXITO, "Puedo insertar un elemento con valor NULL en un hash no NULL");
    pa2m_afirmar(hash_insertar(hash,clave3,valor3) == EXITO, "Puedo insertar un elemento con valor NULL en un hash no NULL");

    char* clave4 = "clave";
    char* valor4 = "valor4";

    pa2m_afirmar(hash_insertar(hash,clave4,valor4) == EXITO, "Puedo insertar un elemento con colision en un hash no NULL");

    hash_destruir(hash);
}

void PuedoInsertarElementosConRehashEnHashNoNULL(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave = "clave";
    char* valor = "valor";
    char* clave2 = "clave2";
    char* valor2 = "valor2";
    char* clave3 = "clave3";
    char* valor3 = "valor3";
    char* clave4 = "clave4";
    char* valor4 = "valor4";
    char* clave5 = "clave5";
    char* valor5 = "valor5";
    char* clave6 = "clave6";
    char* valor6 = "valor6";

    pa2m_afirmar(hash != NULL, "Creo un nuevo hash no NULL");
    hash_insertar(hash,clave,valor);    
    hash_insertar(hash,clave2,valor2);
    hash_obtener(hash,clave2);
    hash_insertar(hash,clave3,valor3);
    hash_insertar(hash,clave4,valor4);
    hash_obtener(hash,clave2);
    pa2m_afirmar(hash_insertar(hash,clave5,valor5) == EXITO, "Puedo insertar un elemento despues de rehashear un hash no NULL");
    pa2m_afirmar(hash_insertar(hash,clave6,valor6) == EXITO, "Puedo insertar un segundo elemento despues de rehashear un hash no NULL");

    hash_destruir(hash);
}

void NoPuedoQuitarElementosEnHashNULL(){
    hash_t* hash = NULL;

    char* clave = "clave";
    char* valor = "valor";

    pa2m_afirmar(hash == NULL, "Creo un nuevo hash NULL");
    pa2m_afirmar(hash_insertar(hash,clave,valor) == ERROR, "No puedo insertar elementos en un hash NULL");
    pa2m_afirmar(hash_quitar(hash,clave) == ERROR, "No puedo quitar elementos en un hash NULL");
}

void NoPuedoQuitarElementosEnHashVacio(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave = "clave";

    pa2m_afirmar(hash != NULL, "Creo un nuevo hash no NULL");
    pa2m_afirmar(hash_quitar(hash,clave) == ERROR, "No puedo quitar elementos en un hash vacio");

    hash_destruir(hash);
}

void PuedoQuitarUnElementoEnHashNoNULL(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave = "clave";
    char* valor = "valor";

    pa2m_afirmar(hash != NULL, "Creo un nuevo hash no NULL");
    pa2m_afirmar(hash_insertar(hash,clave,valor) == EXITO, "Puedo insertar un elemento en un hash no NULL");
    pa2m_afirmar(hash_quitar(hash,clave) == EXITO, "Puedo quitar un elemento en un hash no NULL");

    hash_destruir(hash);
}

void PuedoQuitarVariosElementosEnHashNoNULL(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave1 = "clave1";
    char* valor1 = "valor1";
    char* clave2 = "clave2";
    char* valor2 = "valor2";
    char* clave3 = "clave3";
    char* valor3 = "valor3";

    pa2m_afirmar(hash != NULL, "Creo un nuevo hash no NULL");
    hash_insertar(hash,clave1,valor1);
    hash_insertar(hash,clave2,valor2);
    hash_insertar(hash,clave3,valor3);
    pa2m_afirmar(hash_quitar(hash,clave1) == EXITO, "Puedo quitar un elemento en un hash no NULL");
    pa2m_afirmar(hash_quitar(hash,clave2) == EXITO, "Puedo quitar un elemento en un hash no NULL");
    pa2m_afirmar(hash_quitar(hash,clave3) == EXITO, "Puedo quitar un elemento en un hash no NULL");

    hash_destruir(hash);
}

void PuedoQuitarVariosElementosConValorNULLEnHashNoNULL(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave1 = "clave1";
    char* valor1 = NULL;
    char* clave2 = "clave2";
    char* valor2 = NULL;
    char* clave3 = "clave3";
    char* valor3 = NULL;

    pa2m_afirmar(hash != NULL, "Creo un nuevo hash no NULL");
    hash_insertar(hash,clave1,valor1);
    hash_insertar(hash,clave2,valor2);
    hash_insertar(hash,clave3,valor3);

    pa2m_afirmar(hash_quitar(hash,clave1) == EXITO, "Puedo quitar un elemento con valor NULL en un hash no NULL");
    pa2m_afirmar(hash_quitar(hash,clave2) == EXITO, "Puedo quitar un elemento con valor NULL en un hash no NULL");
    pa2m_afirmar(hash_quitar(hash,clave3) == EXITO, "Puedo quitar un elemento con valor NULL en un hash no NULL");

    hash_destruir(hash);
}

void PuedoQuitarVariosElementosLuegoDeRehashearEnHashNoNULL(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave1 = "clave1";
    char* valor1 = "valor1";
    char* clave2 = "clave2";
    char* valor2 = "valor2";
    char* clave3 = "clave3";
    char* valor3 = "valor3";
    char* clave4 = "clave4";
    char* valor4 = "valor4";
    char* clave5 = "clave5";
    char* valor5 = "valor5";
    char* clave6 = "clave6";
    char* valor6 = "valor6";

    pa2m_afirmar(hash != NULL, "Creo un nuevo hash no NULL");
    hash_insertar(hash,clave1,valor1);
    hash_insertar(hash,clave2,valor2);
    hash_insertar(hash,clave3,valor3);
    hash_insertar(hash,clave4,valor4);
    hash_insertar(hash,clave5,valor5);
    hash_insertar(hash,clave6,valor6);
    pa2m_afirmar(hash_quitar(hash,clave1) == EXITO, "Puedo quitar un elemento luego de rehashear en un hash no NULL");
    pa2m_afirmar(hash_quitar(hash,clave2) == EXITO, "Puedo quitar un elemento luego de rehashear en un hash no NULL");
    pa2m_afirmar(hash_quitar(hash,clave3) == EXITO, "Puedo quitar un elemento luego de rehashear en un hash no NULL");
    pa2m_afirmar(hash_quitar(hash,clave4) == EXITO, "Puedo quitar un elemento luego de rehashear en un hash no NULL");
    pa2m_afirmar(hash_quitar(hash,clave5) == EXITO, "Puedo quitar un elemento luego de rehashear en un hash no NULL");
    pa2m_afirmar(hash_quitar(hash,clave6) == EXITO, "Puedo quitar un elemento luego de rehashear en un hash no NULL");

    hash_destruir(hash);
}

void UnHashNULLNoContieneElementos(){
    hash_t* hash = NULL;

    char* clave = "clave";

    pa2m_afirmar(hash_contiene(hash,clave) == false, "Un hash NULL no contiene elementos");
}

void UnHashVacioNoContieneElementos(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave = "clave";

    pa2m_afirmar(hash_contiene(hash,clave) == false, "Un hash vacio no contiene elementos");

    hash_destruir(hash);
}

void UnHashConUnElementoContieneElemento(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave = "clave";
    char* valor = "valor";

    hash_insertar(hash,clave,valor);

    pa2m_afirmar(hash_contiene(hash,clave) == true, "Un hash con un elemento contiene el elemento");

    hash_destruir(hash);
}

void UnHashCon5ElementosContiene5Elementos(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave1 = "clave1";
    char* valor1 = "valor1";
    char* clave2 = "clave2";
    char* valor2 = "valor2";
    char* clave3 = "clave3";
    char* valor3 = "valor3";
    char* clave4 = "clave4";
    char* valor4 = "valor4";
    char* clave5 = "clave5";
    char* valor5 = "valor5";

    hash_insertar(hash,clave1,valor1);
    hash_insertar(hash,clave2,valor2);
    hash_insertar(hash,clave3,valor3);
    hash_insertar(hash,clave4,valor4);
    hash_insertar(hash,clave5,valor5);

    pa2m_afirmar(hash_contiene(hash,clave1) == true, "Un hash con 5 elementos contiene el elemento 1");
    pa2m_afirmar(hash_contiene(hash,clave2) == true, "Un hash con 5 elementos contiene el elemento 2");
    pa2m_afirmar(hash_contiene(hash,clave3) == true, "Un hash con 5 elementos contiene el elemento 3");
    pa2m_afirmar(hash_contiene(hash,clave4) == true, "Un hash con 5 elementos contiene el elemento 4");
    pa2m_afirmar(hash_contiene(hash,clave5) == true, "Un hash con 5 elementos contiene el elemento 5");

    hash_destruir(hash);
}

void UnHashCon5ElementosConValorNULLContiene5Elementos(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave1 = "clave1";
    char* valor1 = NULL;
    char* clave2 = "clave2";
    char* valor2 = NULL;
    char* clave3 = "clave3";
    char* valor3 = NULL;
    char* clave4 = "clave4";
    char* valor4 = NULL;
    char* clave5 = "clave5";
    char* valor5 = NULL;

    hash_insertar(hash,clave1,valor1);
    hash_insertar(hash,clave2,valor2);
    hash_insertar(hash,clave3,valor3);
    hash_insertar(hash,clave4,valor4);
    hash_insertar(hash,clave5,valor5);

    pa2m_afirmar(hash_contiene(hash,clave1) == true, "Un hash con 5 elementos con valor NULL contiene el elemento 1");
    pa2m_afirmar(hash_contiene(hash,clave2) == true, "Un hash con 5 elementos con valor NULL contiene el elemento 2");
    pa2m_afirmar(hash_contiene(hash,clave3) == true, "Un hash con 5 elementos con valor NULL contiene el elemento 3");
    pa2m_afirmar(hash_contiene(hash,clave4) == true, "Un hash con 5 elementos con valor NULL contiene el elemento 4");
    pa2m_afirmar(hash_contiene(hash,clave5) == true, "Un hash con 5 elementos con valor NULL contiene el elemento 5");

    hash_destruir(hash);
}

void PuedoReinsertarClavesLuegoDeQuitarlasEnHashNoNULL(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave1 = "clave1";
    char* valor1 = "valor1";
    char* clave2 = "clave2";
    char* valor2 = "valor2";
    char* clave3 = "clave3";
    char* valor3 = "valor3";
    char* clave4 = "clave4";
    char* valor4 = "valor4";
    char* clave5 = "clave5";
    char* valor5 = "valor5";

    hash_insertar(hash,clave1,valor1);
    hash_insertar(hash,clave2,valor2);
    hash_insertar(hash,clave3,valor3);
    hash_insertar(hash,clave4,valor4);
    hash_insertar(hash,clave5,valor5);

    pa2m_afirmar(hash_quitar(hash,clave1) == EXITO, "Puedo quitar un elemento en un hash no NULL");
    pa2m_afirmar(hash_quitar(hash,clave2) == EXITO, "Puedo quitar un elemento en un hash no NULL");
    pa2m_afirmar(hash_quitar(hash,clave3) == EXITO, "Puedo quitar un elemento en un hash no NULL");
    pa2m_afirmar(hash_quitar(hash,clave4) == EXITO, "Puedo quitar un elemento en un hash no NULL");
    pa2m_afirmar(hash_quitar(hash,clave5) == EXITO, "Puedo quitar un elemento en un hash no NULL");

    hash_insertar(hash,clave1,valor1);
    hash_insertar(hash,clave2,valor2);
    hash_insertar(hash,clave3,valor3);
    hash_insertar(hash,clave4,valor4);
    hash_insertar(hash,clave5,valor5);

    pa2m_afirmar(hash_cantidad(hash) == 5, "Puedo reinsertar claves luego de quitarlas en un hash no NULL");

    hash_destruir(hash);
}

void UnHashNULLTieneCantidad0(){
    hash_t* hash = NULL;

    pa2m_afirmar(hash_cantidad(hash) == 0, "Un hash NULL tiene cantidad 0");

    hash_destruir(hash);
}

void UnHashVacioTieneCantidad0(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    pa2m_afirmar(hash_cantidad(hash) == 0, "Un hash vacio tiene cantidad 0");

    hash_destruir(hash);
}

void UnHashCon1ElementoTieneCantidad1(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave = "clave";
    char* valor = "valor";

    hash_insertar(hash,clave,valor);

    pa2m_afirmar(hash_cantidad(hash) == 1, "Un hash con 1 elemento tiene cantidad 1");

    hash_destruir(hash);
}

void UnHashCon5ElementosTieneCantidad5(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave1 = "clave1";
    char* valor1 = "valor1";
    char* clave2 = "clave2";
    char* valor2 = "valor2";
    char* clave3 = "clave3";
    char* valor3 = "valor3";
    char* clave4 = "clave4";
    char* valor4 = "valor4";
    char* clave5 = "clave5";
    char* valor5 = "valor5";

    hash_insertar(hash,clave1,valor1);
    hash_insertar(hash,clave2,valor2);
    hash_insertar(hash,clave3,valor3);
    hash_insertar(hash,clave4,valor4);
    hash_insertar(hash,clave5,valor5);

    pa2m_afirmar(hash_cantidad(hash) == 5, "Un hash con 5 elementos tiene cantidad 5");

    hash_destruir(hash);
}

void UnHashCon5ElementosConValorNULLTieneCantidad5(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave1 = "clave1";
    char* valor1 = NULL;
    char* clave2 = "clave2";
    char* valor2 = NULL;
    char* clave3 = "clave3";
    char* valor3 = NULL;
    char* clave4 = "clave4";
    char* valor4 = NULL;
    char* clave5 = "clave5";
    char* valor5 = NULL;

    hash_insertar(hash,clave1,valor1);
    hash_insertar(hash,clave2,valor2);
    hash_insertar(hash,clave3,valor3);
    hash_insertar(hash,clave4,valor4);
    hash_insertar(hash,clave5,valor5);

    pa2m_afirmar(hash_cantidad(hash) == 5, "Un hash con 5 elementos con valor NULL tiene cantidad 5");

    hash_destruir(hash);
}

void NoPuedoObtenerElementosEnHashNULL(){
    hash_t* hash = NULL;

    char* clave = "clave";

    pa2m_afirmar(hash_obtener(hash,clave) == NULL, "No puedo obtener elementos en un hash NULL");
}

void NoPuedoObtenerElementosENHashVacio(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave = "clave";

    pa2m_afirmar(hash_obtener(hash,clave) == NULL, "No puedo obtener elementos en un hash vacio");

    hash_destruir(hash);
}

void PuedoObtenerUnElementoEnHashNoNULL(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave = "clave";
    char* valor = "valor";

    hash_insertar(hash,clave,valor);

    pa2m_afirmar(hash_obtener(hash,clave) == valor, "Puedo obtener un elemento en un hash no NULL");

    hash_destruir(hash);
}

void PuedoObtener5ElementosEnHashNoNULL(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave1 = "clave1";
    char* valor1 = "valor1";
    char* clave2 = "clave2";
    char* valor2 = "valor2";
    char* clave3 = "clave3";
    char* valor3 = "valor3";
    char* clave4 = "clave4";
    char* valor4 = "valor4";
    char* clave5 = "clave5";
    char* valor5 = "valor5";

    hash_insertar(hash,clave1,valor1);
    hash_insertar(hash,clave2,valor2);
    hash_insertar(hash,clave3,valor3);
    hash_insertar(hash,clave4,valor4);
    hash_insertar(hash,clave5,valor5);

    pa2m_afirmar(hash_obtener(hash,clave1) == valor1, "Puedo obtener un elemento en un hash no NULL");
    pa2m_afirmar(hash_obtener(hash,clave2) == valor2, "Puedo obtener un elemento en un hash no NULL");
    pa2m_afirmar(hash_obtener(hash,clave3) == valor3, "Puedo obtener un elemento en un hash no NULL");
    pa2m_afirmar(hash_obtener(hash,clave4) == valor4, "Puedo obtener un elemento en un hash no NULL");
    pa2m_afirmar(hash_obtener(hash,clave5) == valor5, "Puedo obtener un elemento en un hash no NULL");

    hash_destruir(hash);
}

void PuedoObtener5ElementosConValorNULLEnHashNoNULL(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave1 = "clave1";
    char* valor1 = NULL;
    char* clave2 = "clave2";
    char* valor2 = NULL;
    char* clave3 = "clave3";
    char* valor3 = NULL;
    char* clave4 = "clave4";
    char* valor4 = NULL;
    char* clave5 = "clave5";
    char* valor5 = NULL;

    hash_insertar(hash,clave1,valor1);
    hash_insertar(hash,clave2,valor2);
    hash_insertar(hash,clave3,valor3);
    hash_insertar(hash,clave4,valor4);
    hash_insertar(hash,clave5,valor5);

    pa2m_afirmar(hash_obtener(hash,clave1) == valor1, "Puedo obtener un elemento en un hash no NULL");
    pa2m_afirmar(hash_obtener(hash,clave2) == valor2, "Puedo obtener un elemento en un hash no NULL");
    pa2m_afirmar(hash_obtener(hash,clave3) == valor3, "Puedo obtener un elemento en un hash no NULL");
    pa2m_afirmar(hash_obtener(hash,clave4) == valor4, "Puedo obtener un elemento en un hash no NULL");
    pa2m_afirmar(hash_obtener(hash,clave5) == valor5, "Puedo obtener un elemento en un hash no NULL");

    hash_destruir(hash);
}

void NoPuedoRealizarOperacionesEnHashNULL(){
    hash_t* hash = NULL;
    
    char* clave = "clave";
    char* valor = "valor";

    pa2m_afirmar(hash_cantidad(hash) == 0, "Un hash NULL contiene 0 elementos");
    pa2m_afirmar(hash_insertar(hash,clave,valor) == ERROR, "No puedo insertar en un hash NULL");
    pa2m_afirmar(hash_contiene(hash,clave) == false, "Un hash NULL no contiene ninguna clave");
    pa2m_afirmar(hash_obtener(hash,clave) == NULL, "No puedo obtener un elemento en un hash NULL");
    pa2m_afirmar(hash_quitar(hash,clave)== ERROR, "No puedo borrar en un hash NULL");
}

void IterarEnHashNULLDevuelve0Elementos(){
    hash_t* hash = NULL;

    size_t contador = 0;

    pa2m_afirmar(hash_con_cada_clave(hash,visitar_todos_elementos,&contador) == 0, "Iterar sobre un Hash NULL me devuelve 0");
}

void IterarEnHashVacioDevuelve0Elementos(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    size_t contador = 0;

    pa2m_afirmar(hash_con_cada_clave(hash,visitar_todos_elementos,&contador) == 0, "Iterar sobre un Hash vacio me devuelve 0");

    hash_destruir(hash);
}

void IterarEnHashConFuncionNULLElDevuelve0Elementos(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    size_t contador = 0;

    char* clave = "clave";
    char* valor = "valor";

    hash_insertar(hash,clave,valor);

    pa2m_afirmar(hash_con_cada_clave(hash,NULL,&contador) == 0, "Iterar sobre un Hash con funcion NULL me devuelve 0");

    hash_destruir(hash);
}

void IterarEnHashCon1ElementoDevuelve1Elemento(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave = "clave";
    char* valor = "valor";

    hash_insertar(hash,clave,valor);

    size_t contador = 0;

    pa2m_afirmar(hash_con_cada_clave(hash,visitar_todos_elementos,&contador) == 1, "Iterar sobre un Hash con 1 elemento me devuelve 1");
    pa2m_afirmar(contador == 1, "El auxiliar devuelve la cantidad correcta");

    hash_destruir(hash);
}

void IterarEnHashCon5ElementosDevuelve5Elementos(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave1 = "clave1";
    char* valor1 = "valor1";
    char* clave2 = "clave2";
    char* valor2 = "valor2";
    char* clave3 = "clave3";
    char* valor3 = "valor3";
    char* clave4 = "clave4";
    char* valor4 = "valor4";
    char* clave5 = "clave5";
    char* valor5 = "valor5";

    hash_insertar(hash,clave1,valor1);
    hash_insertar(hash,clave2,valor2);
    hash_insertar(hash,clave3,valor3);
    hash_insertar(hash,clave4,valor4);
    hash_insertar(hash,clave5,valor5);

    size_t contador = 0;

    pa2m_afirmar(hash_con_cada_clave(hash,visitar_todos_elementos,&contador) == 5, "Iterar sobre un Hash con 5 elementos me devuelve 5");
    pa2m_afirmar(contador == 5, "El auxiliar devuelve la cantidad correcta");

    hash_destruir(hash);
}

void PuedoIterarhastael3erElemento(){
    hash_t* hash = hash_crear(NULL,CAPACIDAD_INICIAL);

    char* clave1 = "clave1";
    char* valor1 = "valor1";
    char* clave2 = "clave2";
    char* valor2 = "valor2";
    char* clave3 = "clave3";
    char* valor3 = "valor3";
    char* clave4 = "clave4";
    char* valor4 = "valor4";
    char* clave5 = "clave5";
    char* valor5 = "valor5";

    hash_insertar(hash,clave1,valor1);
    hash_insertar(hash,clave2,valor2);
    hash_insertar(hash,clave3,valor3);
    hash_insertar(hash,clave4,valor4);
    hash_insertar(hash,clave5,valor5);

    size_t contador = 0;

    pa2m_afirmar(hash_con_cada_clave(hash,visitar_hasta_la_clave_2,&contador) == 3, "Iterar sobre un Hash hasta la clave2 me devuelve 3");
    pa2m_afirmar(contador == 3, "El auxiliar devuelve la cantidad correcta");

    hash_destruir(hash);
}

void PuedoHacerVariasOperacionesEnHashNoNULL(){
    hash_t* hash = hash_crear(destructor,CAPACIDAD_INICIAL);

    int estado = ERROR;

    char clave[20];
    for(int i = 0; i < 500; i++){
        sprintf(clave,"clave%d",i);
        char* valor = copiar_string(clave);
        estado = hash_insertar(hash,clave,valor);
        if(estado == ERROR){
            break;
        }
    }

    pa2m_afirmar(estado == EXITO, "Pude insertar 500 claves diferentes exitosamente");
    pa2m_afirmar(hash_cantidad(hash) == 500, "La cantidad de claves almacenadas es 500");

    int comparacion_ok = false;

    for(int i = 0;i < 500; i++){
        sprintf(clave,"clave%d",i);
        comparacion_ok = strcmp((char*)hash_obtener(hash,clave),clave) == 0;
        if(!comparacion_ok){
            break;
        }
    }

    pa2m_afirmar(comparacion_ok, "Las claves almacenadas son las correctas");

    pa2m_afirmar(cantidad_de_invocaciones_a_destructor == 0, "Aún no se invocó el destructor");

    size_t contador = 0;
    pa2m_afirmar(hash_con_cada_clave(hash,visitar_todos_elementos,&contador) == 500, "Iterar sobre un Hash con 500 elementos me devuelve 500");
    pa2m_afirmar(contador == 500, "El auxiliar devuelve la cantidad correcta");

    estado = ERROR;
    for(int i = 0; i < 200; i++){
        sprintf(clave,"clave%d",i);
        estado = hash_quitar(hash,clave);
        if(estado == ERROR){
            break;
        }
    }
    pa2m_afirmar(estado == EXITO, "Pude eliminar 1/3 de las claves");
    pa2m_afirmar(hash_cantidad(hash) == 300, "La cantidad de claves almacenadas es 300");
    pa2m_afirmar(cantidad_de_invocaciones_a_destructor == 200, "Se invocó el destructor la cantidad de veces esperada");

    comparacion_ok = false;

    for(int i = 200;i < 500; i++){
        sprintf(clave,"clave%d",i);
        comparacion_ok = strcmp((char*)hash_obtener(hash,clave),clave) == 0;
        if(!comparacion_ok){
            break;
        }
    }

    pa2m_afirmar(comparacion_ok, "No hubo errores de destrucción (se invocó sobre la clave que se esperaba)");

    estado = ERROR;
    for(int i = 0; i < 200; i++){
        sprintf(clave,"clave%d",i);
        estado = hash_insertar(hash,clave,copiar_string(clave));
        if(estado == ERROR){
            break;
        }
    }

    pa2m_afirmar(estado == EXITO, "Pude volver insertar las mismas 500 claves sin errores"); 
    pa2m_afirmar(hash_cantidad(hash) == 500, "La cantidad de claves almacenadas es 500");

    hash_destruir(hash);
}

void PuedoHacerVariasOperacionesConElementosEnElHeapEnHashNoNULL(){
    hash_t* hash = hash_crear(free,CAPACIDAD_INICIAL);

    char* clave_1 = "clave1";
    char* valor_1 = "Jorge Luis Borges";
    char* clave_2 = "clave2";
    char* valor_2 = "Gabriel García Márquez";
    char* clave_3 = "clave3";
    char* valor_3 = "Mario Vargas Llosa";
    char* clave_4 = "clave4";
    char* valor_4 = "Ernesto Sabato";
    char* clave_5 = "clave5";
    char* valor_5 = "Juan Gris";
    char* clave_6 = "clave6";
    char* valor_6 = "Gabriel García Márquez";
    char* clave_7 = "clave7";
    char* valor_7 = "Franz Kafka";
    char* clave_8 = "clave8";
    char* valor_8 = NULL;

    hash_insertar(hash,clave_1,copiar_string(valor_1));
    hash_insertar(hash,clave_2,copiar_string(valor_2));
    hash_insertar(hash,clave_3,copiar_string(valor_3));
    hash_insertar(hash,clave_4,copiar_string(valor_4));
    hash_insertar(hash,clave_5,copiar_string(valor_5));
    hash_insertar(hash,clave_6,copiar_string(valor_6));
    hash_insertar(hash,clave_7,copiar_string(valor_7));
    hash_insertar(hash,clave_8,copiar_string(valor_8));

    pa2m_afirmar(hash_cantidad(hash) == 8, "La cantidad de claves almacenadas es 8");

    pa2m_afirmar(hash_contiene(hash,clave_8) == true, "La clave 8 está en el hash");
    pa2m_afirmar(hash_quitar(hash,clave_8) == EXITO, "Se pudo quitar la clave 8");
    pa2m_afirmar(hash_contiene(hash,clave_8) == false, "La clave 8 ya no está en el hash");

    hash_insertar(hash,clave_8,copiar_string(valor_8));
    pa2m_afirmar(hash_contiene(hash,clave_8) == true, "Se vuelve a insertar la clave 8 en el hash");

    pa2m_afirmar(hash_quitar(hash,clave_7) == EXITO, "Se pudo quitar la clave 7");
    pa2m_afirmar(hash_contiene(hash,clave_7) == false, "La clave 7 ya no está en el hash");
    hash_insertar(hash,clave_7,copiar_string(valor_7));
    pa2m_afirmar(hash_contiene(hash,clave_7) == true, "Se vuelve a insertar la clave 7 en el hash");

    pa2m_afirmar(hash_quitar(hash,clave_8) == EXITO, "Se pudo quitar la clave 8");
    pa2m_afirmar(hash_contiene(hash,clave_8) == false, "La clave 8 ya no está en el hash");

    pa2m_afirmar(hash_contiene(hash,clave_7) == true, "La clave 7 está en el hash");
    hash_insertar(hash,clave_8,copiar_string(valor_8));
    pa2m_afirmar(hash_contiene(hash,clave_8) == true, "Se vuelve a insertar la clave 8 en el hash");

    size_t contador = 0;

    pa2m_afirmar(hash_con_cada_clave(hash,visitar_todos_elementos,&contador) == 8, "Se pudo iterar sobre todas las claves");
    pa2m_afirmar(contador == 8, "El auxiliar se modifico correctamente");

    contador = 0;

    pa2m_afirmar(hash_con_cada_clave(hash,visitar_hasta_la_clave_2,&contador) == 6, "Se pudo iterar sobre las claves hasta la 2");
    pa2m_afirmar(contador == 6, "El auxiliar se modifico correctamente");

    hash_destruir(hash);
}

int main(){
    pa2m_nuevo_grupo("Pruebas de creacion de HASH");
    PuedoCrearUnHashConTamanio10();
    PuedoCrearUnHashConTamanio1();
    PuedoCrearUnHashConDestructor();

    pa2m_nuevo_grupo("Pruebas de añadir elementos al hash");
    NoPuedoInsertarElementosEnHashNULL();
    PuedoInsertarUnElementoEnHashNoNULL();
    PuedoInsertarVariosElementosEnHashNoNULL();
    PuedoInsertarElementosDeValorNULLEnHashNoNULL();
    PuedoInsertarElementosConColisionEnHashNoNULL();
    PuedoInsertarElementosConRehashEnHashNoNULL();
    
    pa2m_nuevo_grupo("Pruebas de quitar elementos al hash");
    NoPuedoQuitarElementosEnHashNULL();
    NoPuedoQuitarElementosEnHashVacio();
    PuedoQuitarUnElementoEnHashNoNULL();
    PuedoQuitarVariosElementosEnHashNoNULL();
    PuedoQuitarVariosElementosConValorNULLEnHashNoNULL();
    PuedoQuitarVariosElementosLuegoDeRehashearEnHashNoNULL();

    pa2m_nuevo_grupo("Pruebas de funcion contiene");
    UnHashNULLNoContieneElementos();
    UnHashVacioNoContieneElementos();
    UnHashConUnElementoContieneElemento();
    UnHashCon5ElementosContiene5Elementos();
    UnHashCon5ElementosConValorNULLContiene5Elementos();
    PuedoReinsertarClavesLuegoDeQuitarlasEnHashNoNULL();

    pa2m_nuevo_grupo("Pruebas de funcion cantidad");
    UnHashNULLTieneCantidad0();
    UnHashVacioTieneCantidad0();
    UnHashCon1ElementoTieneCantidad1();
    UnHashCon5ElementosTieneCantidad5();
    UnHashCon5ElementosConValorNULLTieneCantidad5();

    pa2m_nuevo_grupo("Pruebas de funcion obtener");
    NoPuedoObtenerElementosEnHashNULL();
    NoPuedoObtenerElementosENHashVacio();
    PuedoObtenerUnElementoEnHashNoNULL();
    PuedoObtener5ElementosEnHashNoNULL();
    PuedoObtener5ElementosConValorNULLEnHashNoNULL();

    pa2m_nuevo_grupo("Prueba de varias operaciones con hash NULL");
    NoPuedoRealizarOperacionesEnHashNULL();
 
    pa2m_nuevo_grupo("Pruebas del iterador");
    IterarEnHashNULLDevuelve0Elementos();
    IterarEnHashVacioDevuelve0Elementos();
    IterarEnHashConFuncionNULLElDevuelve0Elementos(); 
    IterarEnHashCon1ElementoDevuelve1Elemento();
    IterarEnHashCon5ElementosDevuelve5Elementos();
    PuedoIterarhastael3erElemento();

    pa2m_nuevo_grupo("Pruebas de insertar/eliminar muchos elementos");
    PuedoHacerVariasOperacionesEnHashNoNULL();

    pa2m_nuevo_grupo("Pruebas de operaciones con elementos en HEAP");
    PuedoHacerVariasOperacionesConElementosEnElHeapEnHashNoNULL();

    return pa2m_mostrar_reporte();
}