#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

/*
* PRE: Elemento1 y Elemento2 deben ser punteros a int.
* POST: Devuelve el resultado de la resta del primer elemento menos el segundo.
*/
int comparar_enteros(void* elemento1, void* elemento2){
    int resultado = *(int*)elemento1 - *(int*)elemento2;
    return resultado;
}

/*
* PRE:
* POST: Devuelve el resutlado de comparar dos strings usando la funcion strcmp.
*/
int comparar_strings(void* elemento_1,void* elemento_2){
    return strcmp(*(char**)elemento_1,*(char**)elemento_2);
}

/*
* PRE:
* POST: Destruye el elemento recibido seteandolo como NULL.
*/
void destructor(void* elemento){
    elemento = NULL;
}

/*
* PRE:
* POST: Libera la memoria reservada para el elemento recibido.
*/
void destructor_string(void* elemento){
    free(elemento);
}

/*
* PRE: elemento_1 y extra deben ser punteros a enteros.
* POST: Imprime por pantalla los elementos de un nodo y asi poder chequear si estan ordenados, devuelve true para poder visitar todos los elementos.
*/
bool visitar_todos_elementos(void* elemento_1, void* extra){
    printf("%d\n", *(int*)elemento_1);
    (*(int*)extra)++;
    return true;
}

/*
* PRE: elemento_1 y extra deben ser punteros a enteros.
* POST: Imprime por pantalla los elementos de un nodo y asi poder chequear si estan ordenados, devuelve false si encuentra el entero 3 en caso contrario devuelve true.
*/
bool visitar_hasta_3(void* elemento_1, void* extra){
    if(*(int*)elemento_1 == 3){
        printf("%d\n", *(int*)elemento_1);
        (*(int*)extra)++;
        return false;
    }
    printf("%d\n", *(int*)elemento_1);
    (*(int*)extra)++;
    return true;
}

/*
* PRE: array debe ser un puntero a un array de enteros.
* POST: Imprime por pantalla los elementos del array hasta su tamaño, devuelve true si pudo imprimir todos los elementos, false en caso contrario.
*/
bool se_modifico_array(void** array, size_t tamanio_array){
    if(!array || tamanio_array == 0){
        return false;
    }
    if(&array[0] == NULL){
        return false;
    }
    for(int i = 0; i < tamanio_array; i++){
        printf("%d\n", *(int*)array[i]);
    }
    return true;
}

void DadoUnABBNULLYComparadorNULL_ElABBEsNULL(){
    abb_t* abb = NULL;
    abb = abb_crear(NULL);
    pa2m_afirmar(abb == NULL, "Dado un ABB NULL y un comparador NULL el arbol creado es NULL");
    abb_destruir(abb);
}

void DadoUnABBValidoYComparadorValido_PuedoCrearlo(){
    abb_t* abb = abb_crear(comparar_enteros);
    pa2m_afirmar(abb_vacio(abb),"El arbol inicialmente esta vacio");
    pa2m_afirmar(abb != NULL, "Dado un ABB valido y un comparador valido el arbol creado NO es NULL");
    pa2m_afirmar(abb_vacio(abb),"Luego de crear el arbol este sigue estando vacio ya que no se inserto ningun elemento");

    abb_destruir(abb);
}

void DadoUnABBNULL_NoPuedoInsertarDatos(){
    abb_t* abb = NULL;
    int elemento = 5;

    pa2m_afirmar(abb_vacio(abb),"Dado un arbol NULL este inicialmente esta vacio");
    pa2m_afirmar(abb_insertar(abb,&elemento)==NULL,"No puedo insertar un elemento en un arbol NULL");
    pa2m_afirmar(abb_vacio(abb),"El arbol sigue estando vacio ya que no puedo insertar elementos");
    pa2m_afirmar(abb_tamanio(abb)==0,"Dado que no ingrese elementos el tamaño del arbol es 0");

    abb_destruir(abb);
}

void DadoUnABBVacio_PuedoInsertarElementos(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 1, elemento_2 = 2, elemento_3 = 3;

    pa2m_afirmar(abb_vacio(abb),"Dado un arbol vacio este está inicialmente esta vacio");
    pa2m_afirmar(abb_insertar(abb,&elemento_1)!=NULL,"Puedo insertar un entero 1 al arbol");
    pa2m_afirmar(abb_insertar(abb,&elemento_2)!=NULL,"Puedo insertar un entero 2 al arbol");
    pa2m_afirmar(abb_insertar(abb,&elemento_3)!=NULL,"Puedo insertar un entero 3 al arbol");
    pa2m_afirmar(abb_vacio(abb)==false,"El arbol deja de estar vacio ya que ingrese 3 elementos");
    pa2m_afirmar(abb_tamanio(abb)==3,"Dado que ingrese 3 elementos el tamanio del arbol es 3");

    abb_destruir(abb);
}

void DadoUnABBVacio_PuedoInsertarElementosYEliminarlos(){
    abb_t* abb = abb_crear(comparar_enteros);
    char elemento_1 = 'a', elemento_2 = 'b', elemento_3 = 'c';

    pa2m_afirmar(abb_vacio(abb),"Dado un arbol vacio este está inicialmente esta vacio");
    pa2m_afirmar(abb_insertar(abb,&elemento_1)!=NULL,"Puedo insertar un entero 1 al arbol");
    pa2m_afirmar(abb_insertar(abb,&elemento_2)!=NULL,"Puedo insertar un entero 2 al arbol");
    pa2m_afirmar(abb_insertar(abb,&elemento_3)!=NULL,"Puedo insertar un entero 3 al arbol");
    pa2m_afirmar(abb_vacio(abb)==false,"El arbol deja de estar vacio ya que ingrese 3 elementos");
    pa2m_afirmar(abb_tamanio(abb)==3,"Dado que ingrese 3 elementos el tamanio del arbol es 3");

    abb_destruir_todo(abb,destructor);
}

void DadoUnABBVacio_SeInserta123DeManeraOrdenada(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 1, elemento_2 = 2, elemento_3 = 3;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);

    pa2m_afirmar(abb_tamanio(abb)==3,"Puedo insertar los elementos 1 - 2 - 3 en el ABB");

    pa2m_afirmar(*(int*)(abb->nodo_raiz->elemento) == 1, "El elemento en la raiz del ABB es el 1");
    pa2m_afirmar(*(int*)(abb->nodo_raiz->derecha->elemento) == 2, "El elemento a la derecha de la raiz es el 2");
    pa2m_afirmar(*(int*)(abb->nodo_raiz->derecha->derecha->elemento) == 3, "El elemento a la derecha de el subarbol 2 es el 3");

    abb_destruir_todo(abb,destructor);
}

void DadoUnABBVacio_SeInserta321DeManeraOrdenada(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 2, elemento_3 = 1;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);

    pa2m_afirmar(abb_tamanio(abb)==3,"Puedo insertar los elementos 3 - 2 - 1 en el ABB");

    pa2m_afirmar(*(int*)(abb->nodo_raiz->elemento) == 3, "El elemento en la raiz del ABB es el 3");
    pa2m_afirmar(*(int*)(abb->nodo_raiz->izquierda->elemento) == 2, "El elemento a la izquierda de la raiz es el 2");
    pa2m_afirmar(*(int*)(abb->nodo_raiz->izquierda->izquierda->elemento) == 1, "El elemento a la izquierda de el subarbol 2 es el 1");

    abb_destruir_todo(abb,destructor);
}

void DadoUnABBVacio_SeInserta132DeManeraOrdenada(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 1, elemento_2 = 3, elemento_3 = 2;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);

    pa2m_afirmar(abb_tamanio(abb)==3,"Puedo insertar los elementos 1 - 3 - 2 en el ABB");

    pa2m_afirmar(*(int*)(abb->nodo_raiz->elemento) == 1, "El elemento en la raiz del ABB es el 1");
    pa2m_afirmar(*(int*)(abb->nodo_raiz->derecha->elemento) == 3, "El elemento a la derecha de la raiz es el 3");
    pa2m_afirmar(*(int*)(abb->nodo_raiz->derecha->izquierda->elemento) == 2, "El elemento a la izquierda de el subarbol 3 es el 2");

    abb_destruir_todo(abb,destructor);
}

void DadoUnABBVacio_SeInserta213DeManeraOrdenada(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 2, elemento_2 = 1, elemento_3 = 3;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);

    pa2m_afirmar(abb_tamanio(abb)==3,"Puedo insertar los elementos 2 - 1 - 3 en el ABB");

    pa2m_afirmar(*(int*)(abb->nodo_raiz->elemento) == 2, "El elemento en la raiz del ABB es el 2");
    pa2m_afirmar(*(int*)(abb->nodo_raiz->derecha->elemento) == 3, "El elemento a la derecha de la raiz es el 3");
    pa2m_afirmar(*(int*)(abb->nodo_raiz->izquierda->elemento) == 1, "El elemento a la izquierda de la raiz es el 1");

    abb_destruir_todo(abb,destructor);
}

void DadoUnABBVacio_SeInserta231DeManeraOrdenada(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 2, elemento_2 = 3, elemento_3 = 1;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);

    pa2m_afirmar(abb_tamanio(abb)==3,"Puedo insertar los elementos 2 - 3 - 1 en el ABB");

    pa2m_afirmar(*(int*)(abb->nodo_raiz->elemento) == 2, "El elemento en la raiz del ABB es el 2");
    pa2m_afirmar(*(int*)(abb->nodo_raiz->derecha->elemento) == 3, "El elemento a la derecha de la raiz es el 3");
    pa2m_afirmar(*(int*)(abb->nodo_raiz->izquierda->elemento) == 1, "El elemento a la izquierda de la raiz es el 1");

    abb_destruir_todo(abb,destructor);
}

void DadoUnABBVacio_SeInserta312DeManeraOrdenada(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);

    pa2m_afirmar(abb_tamanio(abb)==3,"Puedo insertar los elementos 3 - 1 - 2 en el ABB");

    pa2m_afirmar(*(int*)(abb->nodo_raiz->elemento) == 3, "El elemento en la raiz del ABB es el 3");
    pa2m_afirmar(*(int*)(abb->nodo_raiz->izquierda->elemento) == 1, "El elemento a la izquierda de la raiz es el 1");
    pa2m_afirmar(*(int*)(abb->nodo_raiz->izquierda->derecha->elemento) == 2, "El elemento a la derecha del subarbol 1 es el 3");

    abb_destruir_todo(abb,destructor);
}

void DadoUnABBNULL_NoSePuedeEliminar(){
    abb_t* abb = NULL;
    int elemento_1 = 3;
    pa2m_afirmar(abb_insertar(abb,&elemento_1)==NULL,"Dada un ABB NULL no puedo insertar elementos");
    pa2m_afirmar(abb_quitar(abb,&elemento_1)==NULL,"Dada un ABB NULL no puedo remover elementos");

    abb_destruir(abb);
}

void DadoUnABBVacio_NoSePuedeEliminar(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3;

    pa2m_afirmar(abb_vacio(abb),"Creo un nuevo ABB vacio");
    pa2m_afirmar(abb_quitar(abb,&elemento_1)==NULL,"No puedo remover elementos de un ABB vacio");

    abb_destruir(abb);
}

void DadoUnABBConUnElemento_PuedoEliminar(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3;

    int resultado;

    abb_insertar(abb,&elemento_1);

    pa2m_afirmar(abb_tamanio(abb)==1,"Dado un abb vacio nuevo puedo insertar el elemento 3");
    pa2m_afirmar(abb_vacio(abb)==false,"La lista deja de estar vacia");

    resultado = *(int*)abb_quitar(abb,&elemento_1);

    pa2m_afirmar(resultado == 3,"Puedo remover un elemento de un abb con un solo elemento");

    pa2m_afirmar(abb_tamanio(abb)==0,"El ABB ahora tiene tamaño 0");

    abb_destruir_todo(abb,destructor);
}

void DadoUnABBLLeno_SePuedeEliminarUnNodoHoja(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);

    pa2m_afirmar(abb_tamanio(abb)==3,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 en el ABB");

    pa2m_afirmar(*(int*)abb_quitar(abb,&elemento_3)==2,"Puedo remover el nodo hoja 2 del ABB");

    pa2m_afirmar(abb_tamanio(abb)==2,"El ABB ahora tiene tamaño 2");

    abb_destruir(abb);
}

void DadoUnABBLLeno_SePuedeElimiarUnNodoConUnSoloHijo(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);

    pa2m_afirmar(abb_tamanio(abb)==3,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 en el ABB");

    pa2m_afirmar(*(int*)abb_quitar(abb,&elemento_2)==1,"Puedo remover el nodo con un solo hijo 1 del ABB");

    pa2m_afirmar(abb_tamanio(abb)==2,"El ABB ahora tiene tamaño 2");

    abb_destruir(abb);
}

void DadoUnABBLLeno_SePuedeEliminarUnNodoConDosHijos(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");

    pa2m_afirmar(*(int*)abb_quitar(abb,&elemento_1)==3,"Puedo remover el nodo con dos hijos (3) del ABB");

    pa2m_afirmar(abb_tamanio(abb)==3,"El ABB ahora tiene tamaño 3");

    abb_destruir(abb);
}

void DadoUnABBLLeno_SePuedeEliminarUnNodoConDosHijosComplejo(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 18, elemento_2 = 9, elemento_3 = 25, elemento_4 = 7, elemento_5 = 12, elemento_6 = 11, elemento_7 = 23, elemento_8 = 29;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);
    abb_insertar(abb,&elemento_5);
    abb_insertar(abb,&elemento_6);
    abb_insertar(abb,&elemento_7);
    abb_insertar(abb,&elemento_8);

    pa2m_afirmar(abb_tamanio(abb)==8,"Dado un abb vacio nuevo puedo insertar los elementos 18 - 9 - 25 - 7 - 12 - 11 - 23 - 29 en el ABB");

    pa2m_afirmar(*(int*)abb_quitar(abb,&elemento_1)==18,"Puedo remover el nodo con dos hijos (18) de un ABB complejo");

    pa2m_afirmar(abb_tamanio(abb)==7,"El ABB ahora tiene tamaño 7");

    abb_destruir(abb);

}

void DadoUnABBLLeno_NoSePuedeEliminarUnNodoQueNoExiste(){
    abb_t* abb = abb_crear(comparar_enteros);

    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);

    pa2m_afirmar(abb_tamanio(abb)==3,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 en el ABB");

    pa2m_afirmar(abb_quitar(abb,&elemento_4)==NULL,"No puedo remover un elemento que no existe");

    pa2m_afirmar(abb_tamanio(abb)==3,"El ABB ahora tiene tamaño 3");

    abb_destruir(abb);
}

void DadoUnABBNULL_NoSePuedeBuscar(){
    abb_t* abb = NULL;
    int elemento_1 = 3;

    pa2m_afirmar(abb_insertar(abb,&elemento_1)==NULL,"No puedo insertar un elemento en un ABB NULL");

    pa2m_afirmar(abb_buscar(abb,&elemento_1)==NULL,"No puedo buscar un elemento en un ABB NULL");
}

void DadoUnABBVacio_NoSePuedeBuscar(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3;

    pa2m_afirmar(abb_buscar(abb,&elemento_1)==NULL,"No puedo buscar un elemento en un ABB vacio");

    abb_destruir(abb);
}

void DadoUnABBLLeno_SePuedeBuscar(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");

    pa2m_afirmar(*(int*)abb_buscar(abb,&elemento_1)==3,"Puedo buscar el nodo 3 en el ABB");

    abb_destruir(abb);
}

void DadoUnABBLleno_NoSePuedeBuscarYaQueNoExiste(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4, elemento_5 = 100;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");

    pa2m_afirmar(abb_buscar(abb,&elemento_5)==NULL,"No puedo buscar un elemento que no existe en el ABB");

    abb_destruir(abb);
}

void DadoUnABBNULL_NoSePuedeIterar(){
    abb_t* abb = NULL;

    int contador = 0;

    pa2m_afirmar(abb_tamanio(abb)==0,"Creo un ABB NULL");
    pa2m_afirmar(abb_con_cada_elemento(abb,INORDEN,visitar_todos_elementos,&contador)==0,"No puedo iterar un ABB NULL");
}

void DadoUnABBVacio_SiIteroMeDa0(){
    abb_t* abb = abb_crear(comparar_enteros);

    int contador = 0;

    pa2m_afirmar(abb_tamanio(abb)==0,"Creo un ABB vacio");
    pa2m_afirmar(abb_con_cada_elemento(abb,INORDEN,visitar_todos_elementos,&contador)==0,"No puedo iterar un ABB vacio");
    pa2m_afirmar(contador==0,"El parametro auxiliar no se modifico");

    abb_destruir(abb);
}

void DadoUnABBLLeno_NoPuedoIterarSiLaFuncionDeVisitaEsNULL(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    int contador = 0;

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");
    pa2m_afirmar(abb_con_cada_elemento(abb,INORDEN,NULL,&contador)==0,"No puedo iterar un ABB si la funcion enviada es NULL");
    pa2m_afirmar(contador==0,"El parametro auxiliar no se modifico");

    abb_destruir(abb);
}

void DadoUnABBLLeno_PuedoIterar_Inorder(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    int contador = 0;

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");
    pa2m_afirmar(abb_con_cada_elemento(abb,INORDEN,visitar_todos_elementos,&contador)==4,"Puedo iterar un abb lleno y recorrer todos sus elementos con el metodo Inorder");
    pa2m_afirmar(contador==4,"El parametro auxiliar se modifico");

    abb_destruir(abb);
}

void DadoUnABBLLeno_PuedoIterar_Preorder(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    int contador = 0;

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");
    pa2m_afirmar(abb_con_cada_elemento(abb,PREORDEN,visitar_todos_elementos,&contador)==4,"Puedo iterar un abb lleno y recorrer todos sus elementos con el metodo Preorder");
    pa2m_afirmar(contador==4,"El parametro auxiliar se modifico");

    abb_destruir(abb);
}

void DadoUnABBLLeno_PuedoIterar_Postorder(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    int contador = 0;

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");
    pa2m_afirmar(abb_con_cada_elemento(abb,POSTORDEN,visitar_todos_elementos,&contador)==4,"Puedo iterar un abb lleno y recorrer todos sus elementos con el metodo Postorder");
    pa2m_afirmar(contador==4,"El parametro auxiliar se modifico");

    abb_destruir(abb);
}

void DadoUnABBLLeno_PuedoIterarHastaFalse_Inorder(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    int contador = 0;

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");
    pa2m_afirmar(abb_con_cada_elemento(abb,INORDEN,visitar_hasta_3,&contador)==3,"Puedo iterar un abb lleno y recorrer todos sus elementos hasta que la funcion devuelva false con el metodo Inorder");
    pa2m_afirmar(contador==3,"El parametro auxiliar es igual a la cantidad de veces que itero");

    abb_destruir(abb);
}

void DadoUnABBLLeno_PuedoIterarHastaFalse_Preorder(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    int contador = 0;

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");
    pa2m_afirmar(abb_con_cada_elemento(abb,PREORDEN,visitar_hasta_3,&contador)==1,"Puedo iterar un abb lleno y recorrer todos sus elementos hasta que la funcion devuelva false con el metodo Preorder");
    pa2m_afirmar(contador==1,"El parametro auxiliar es igual a la cantidad de veces que itero");

    abb_destruir(abb);
}

void DadoUnABBLLeno_PuedoIterarHastaFalse_Postorder(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    int contador = 0;

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");
    pa2m_afirmar(abb_con_cada_elemento(abb,POSTORDEN,visitar_hasta_3,&contador)==4,"Puedo iterar un abb lleno y recorrer todos sus elementos hasta que la funcion devuelva false con el metodo Postorder");
    pa2m_afirmar(contador==4,"El parametro auxiliar es igual a la cantidad de veces que itero");

    abb_destruir(abb);
}

void DadoUnABBNULL_NoSePuedeIterarConIteradorExterno(){
    abb_t* abb = NULL;
    int elemento_1 = 5;

    int* array[10] = {NULL};

    pa2m_afirmar(abb_insertar(abb,&elemento_1)==NULL,"Dado un abb NULL nuevo no puedo insertar un elemento");
    pa2m_afirmar(abb_recorrer(abb,INORDEN,(void**)array,10)==0,"Dado un abb NULL nuevo si intento recorrer con el iterador interno me da 0");
    pa2m_afirmar(array[0] == NULL,"No se añadio ningun elemento al array");
}

void DadoUnABBVacio_SiIteroConIteradorExternoMeDa0(){
    abb_t* abb = abb_crear(comparar_enteros);

    int* array[10] = {NULL};

    pa2m_afirmar(abb_tamanio(abb)==0,"Creo un nuevo ABB vacio y no le inserto ningun numero");
    
    pa2m_afirmar(abb_recorrer(abb,INORDEN,(void**)array,10)==0,"Si intento recorrer el ABB vacio me da 0");

    pa2m_afirmar(array[0] == NULL,"No se añadio ningun elemento al array");

    abb_destruir(abb);
} 

void DadoUnABBLLeno_NoSePuedeIterarSiElArrayEsNULL(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");
    pa2m_afirmar(abb_recorrer(abb,INORDEN,NULL,10)==0,"Si intento recorrer un abb lleno con un array NULL me da 0");

    abb_destruir(abb);
}

void DadoUnABBLLeno_SiIntentoIterarConTamanio0MeDa0(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    int* array[10] = {NULL};

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");
    pa2m_afirmar(abb_recorrer(abb,INORDEN,(void**)array,0)==0,"Si intento recorrer un abb lleno con un tamanio 0 me da 0");
    pa2m_afirmar(array[0] == NULL,"No se añadio ningun elemento al array");

    abb_destruir(abb);
}

void DadoUnABBLLeno_PuedoIterarConTamanioMayorAlTamanioDelABB(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    int* array[10] = {NULL};

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");
    pa2m_afirmar(abb_recorrer(abb,INORDEN,(void**)array,10)==4,"Si intento recorrer un abb lleno con un vector de tamaño mayor al tamaño del ABB me da la cantidad de elementos del ABB");
    pa2m_afirmar(se_modifico_array((void**)array,4),"Se modifico el array");

    abb_destruir(abb);
}

void DadoUnABBLLeno_PuedoIterarConTamanioMenorAlTamanioDelABB(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    int* array[3] = {NULL};

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");
    pa2m_afirmar(abb_recorrer(abb,INORDEN,(void**)array,3)==3,"Si intento recorrer un abb lleno con un vector de tamaño menor al tamaño del ABB me da los elementos del ABB hasta el maximo del vector");
    pa2m_afirmar(se_modifico_array((void**)array,3),"Se modifico el array");

    abb_destruir(abb);
}   
void DadoUnABBLLeno_PuedoIterarConIteradorExterno_Inorder(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    int* array[10] = {NULL};

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");
    pa2m_afirmar(abb_recorrer(abb,INORDEN,(void**)array,4)==4,"Si intento recorrer un abb lleno con el iterador externo inorder me da 4 ");
    pa2m_afirmar(se_modifico_array((void**)array,4),"Se modifico el array");

    abb_destruir(abb);
}

void DadoUnABBLLeno_PuedoIterarConIteradorExterno_Preorder(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    int* array[10] = {NULL};

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");
    pa2m_afirmar(abb_recorrer(abb,PREORDEN,(void**)array,4)==4,"Si intento recorrer un abb lleno con el iterador externo preorder me da 4");
    pa2m_afirmar(se_modifico_array((void**)array,4),"Se modifico el array");

    abb_destruir(abb);
}

void DadoUnABBLLeno_puedoIterarConIteradorExterno_Postorder(){
    abb_t* abb = abb_crear(comparar_enteros);
    int elemento_1 = 3, elemento_2 = 1, elemento_3 = 2, elemento_4 = 4;

    abb_insertar(abb,&elemento_1);
    abb_insertar(abb,&elemento_2);
    abb_insertar(abb,&elemento_3);
    abb_insertar(abb,&elemento_4);

    int* array[10] = {NULL};

    pa2m_afirmar(abb_tamanio(abb)==4,"Dado un abb vacio nuevo puedo insertar los elementos 3 - 1 - 2 - 4 en el ABB");
    pa2m_afirmar(abb_recorrer(abb,POSTORDEN,(void**)array,4)==4,"Si intento recorrer un abb lleno con el iterador externo postorder me da 4");
    pa2m_afirmar(se_modifico_array((void**)array,4),"Se modifico el array");

    abb_destruir(abb);
}

void  DadoUnABBLLeno_PuedoIterarConIteradorInternoYStringsEnHeap(){
    char** elemento_1 = calloc(1,sizeof(char*) * 10);
    char** elemento_2 = calloc(1,sizeof(char*) * 10);
    char** elemento_3 = calloc(1,sizeof(char*) * 10);
    char** elemento_4 = calloc(1,sizeof(char*) * 10);
    char** elemento_5 = calloc(1,sizeof(char*) * 10);

    *elemento_1 = "Carlos";
    *elemento_2 = "Ana";
    *elemento_3 = "Benja";
    *elemento_4 = "Daniel";
    *elemento_5 = "Esteban";

    abb_t* abb = abb_crear(comparar_strings);

    abb_insertar(abb,elemento_1);
    abb_insertar(abb,elemento_2);
    abb_insertar(abb,elemento_3);
    abb_insertar(abb,elemento_4);
    abb_insertar(abb,elemento_5);

    char** array_inorden[5];
    char** array_preorden[5];
    char** array_postorden[5];

    char* array_inorden_esperado[5] = {"Ana","Benja","Carlos","Daniel","Esteban"};
    char* array_preorden_esperado[5] = {"Carlos","Ana","Benja","Daniel","Esteban"};
    char* array_postorden_esperado[5] = {"Benja","Ana","Esteban","Daniel","Carlos"};


    pa2m_afirmar(abb_tamanio(abb)==5,"Dado un abb vacio nuevo puedo insertar los elementos Jorge - Juan - Pedro - Pablo - Matias en el ABB");
    
    pa2m_afirmar(abb_recorrer(abb,INORDEN,(void**)array_inorden,5)==5,"Se recorre todo el arbol completo de forma INORDEN");

    pa2m_afirmar(abb_recorrer(abb,PREORDEN,(void**)array_preorden,5)==5,"Se recorre todo el arbol completo de forma PREORDEN");
    
    pa2m_afirmar(abb_recorrer(abb,POSTORDEN,(void**)array_postorden,5)==5,"Se recorre todo el arbol completo de forma POSTORDEN");

    for(size_t i = 0; i < 5; i++){
        printf("\nPosicion numero -> %li\n",i);
        pa2m_afirmar(strcmp(*(char**)array_inorden[i],array_inorden_esperado[i])==0,"El elemento del array INORDEN es el correcto");
        pa2m_afirmar(strcmp(*(char**)array_preorden[i],array_preorden_esperado[i])==0,"El elemento del array PREORDEN es el correcto");
        pa2m_afirmar(strcmp(*(char**)array_postorden[i],array_postorden_esperado[i])==0,"El elemento del array POSTORDEN es el correcto");
    }
    abb_destruir_todo(abb,destructor_string);
}

int main(){
    pa2m_nuevo_grupo("Pruebas de creacion y destruccion del ABB");
    DadoUnABBNULLYComparadorNULL_ElABBEsNULL();
    DadoUnABBValidoYComparadorValido_PuedoCrearlo();
    pa2m_nuevo_grupo("Preubas de insertar en el ABB");
    DadoUnABBNULL_NoPuedoInsertarDatos();
    DadoUnABBVacio_PuedoInsertarElementos();
    DadoUnABBVacio_PuedoInsertarElementosYEliminarlos();
    pa2m_nuevo_grupo("Pruebas de insertar elementos en forma ordenada");
    DadoUnABBVacio_SeInserta123DeManeraOrdenada();
    DadoUnABBVacio_SeInserta321DeManeraOrdenada();
    DadoUnABBVacio_SeInserta132DeManeraOrdenada();
    DadoUnABBVacio_SeInserta213DeManeraOrdenada();
    DadoUnABBVacio_SeInserta231DeManeraOrdenada();
    DadoUnABBVacio_SeInserta312DeManeraOrdenada();
    pa2m_nuevo_grupo("Pruebas de eliminacion de elementos");
    DadoUnABBNULL_NoSePuedeEliminar();
    DadoUnABBVacio_NoSePuedeEliminar();
    DadoUnABBConUnElemento_PuedoEliminar();
    DadoUnABBLLeno_SePuedeEliminarUnNodoHoja();
    DadoUnABBLLeno_SePuedeElimiarUnNodoConUnSoloHijo();
    DadoUnABBLLeno_SePuedeEliminarUnNodoConDosHijos();
    DadoUnABBLLeno_SePuedeEliminarUnNodoConDosHijosComplejo();
    DadoUnABBLLeno_NoSePuedeEliminarUnNodoQueNoExiste();
    pa2m_nuevo_grupo("Pruebas de busqueda");
    DadoUnABBNULL_NoSePuedeBuscar();
    DadoUnABBVacio_NoSePuedeBuscar();
    DadoUnABBLLeno_SePuedeBuscar();
    DadoUnABBLleno_NoSePuedeBuscarYaQueNoExiste();
    pa2m_nuevo_grupo("Pruebas de iterador interno");
    DadoUnABBNULL_NoSePuedeIterar();
    DadoUnABBVacio_SiIteroMeDa0();
    DadoUnABBLLeno_NoPuedoIterarSiLaFuncionDeVisitaEsNULL();
    DadoUnABBLLeno_PuedoIterar_Inorder();
    DadoUnABBLLeno_PuedoIterar_Preorder();
    DadoUnABBLLeno_PuedoIterar_Postorder();
    DadoUnABBLLeno_PuedoIterarHastaFalse_Inorder();
    DadoUnABBLLeno_PuedoIterarHastaFalse_Preorder();
    DadoUnABBLLeno_PuedoIterarHastaFalse_Postorder();
    pa2m_nuevo_grupo("Pruebas de iterador externo");
    DadoUnABBNULL_NoSePuedeIterarConIteradorExterno();
    DadoUnABBVacio_SiIteroConIteradorExternoMeDa0();
    DadoUnABBLLeno_NoSePuedeIterarSiElArrayEsNULL();
    DadoUnABBLLeno_SiIntentoIterarConTamanio0MeDa0();
    DadoUnABBLLeno_PuedoIterarConTamanioMayorAlTamanioDelABB();
    DadoUnABBLLeno_PuedoIterarConTamanioMenorAlTamanioDelABB();
    DadoUnABBLLeno_PuedoIterarConIteradorExterno_Inorder();
    DadoUnABBLLeno_PuedoIterarConIteradorExterno_Preorder();
    DadoUnABBLLeno_puedoIterarConIteradorExterno_Postorder();
    pa2m_nuevo_grupo("Pruebas con iterador externo y strings en el heap");
    DadoUnABBLLeno_PuedoIterarConIteradorInternoYStringsEnHeap();

    return pa2m_mostrar_reporte();
}
