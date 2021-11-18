#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa2mm.h"

bool prueba_iterador_interno(void* elemento_1, void* elemento_2){
    return true;
}

bool prueba_iterador_interno_hasta_anteultimo_elemento(void* elemento_1, void* elemento_2){
    if(*(char*)elemento_1 == 'M'){
        return false;
    }
    size_t* contador = elemento_2;
    (*contador)++;
    return true;
}

bool prueba_iterador_interno_con_contexto(void* elemento_1, void* contexto){
    if(!elemento_1 || !contexto){
        return false;
    }
    printf("Recorri el elemento %c en la posicion %i\n",*(char*)elemento_1,*(int*)contexto);
    (*(int*)contexto)++;
    return true;
}


void DadaUnaListaNULLSeCreaUnaVacia(){
    lista_t* lista = NULL;
    lista = lista_crear();
    pa2m_afirmar(lista != NULL, "Dada una lista NULL se crea una lista NO NULL");
    pa2m_afirmar(lista_vacia(lista),"Dada una lista NULL se crea una lista vacia");

    lista_destruir(lista);
} 

void DadaUnaListaNoNULLSeCreaUnaListaVacia(){
    lista_t* lista = lista_crear();
    pa2m_afirmar(lista != NULL, "Dada una lista NO NULL se crea una lista NO NULL");
    pa2m_afirmar(lista_vacia(lista),"Dada una lista NO NULL se crea una lista vacia")
    lista_destruir(lista);
}

void DadaUnaListaNULLPuedoInsertarYRemover(){
    lista_t* lista = NULL;
    int elemento = 5;

    pa2m_afirmar(lista_insertar(lista,&elemento)==NULL,"No puedo insertar un elemento en una lista NULL");
    pa2m_afirmar(lista_quitar(lista) == NULL,"No puedo quitar un elemento de una lista NULL");
    pa2m_afirmar(lista_vacia(lista),"Dada una lista NULL esta vacia");

    lista_destruir(lista);
}

void DadaUnaListaNoNULLPuedoInsertarYRemoverUnSoloElemento(){
    lista_t* lista = lista_crear();
    int elemento = 5;

    pa2m_afirmar(lista != NULL, "Se crea la lista correctamente");
    pa2m_afirmar(lista_vacia(lista),"Inicialmente la lista esta vacia");
    pa2m_afirmar(lista_insertar(lista,&elemento)==lista,"Puedo insertar un elemento en una lista valida");
    pa2m_afirmar(lista_tamanio(lista)==1,"La lista tiene 1 elemento");
    pa2m_afirmar(*(int*)lista->nodo_inicio->elemento == 5, "El primer elemento de la lista es el 5");
    pa2m_afirmar(*(int*)lista->nodo_fin->elemento == 5, "El ultimo elemento de la lista es el 5");
    pa2m_afirmar(lista->nodo_fin->siguiente == NULL, "El ultimo nodo apunta a NULL");
    pa2m_afirmar(*(int*)lista_elemento_en_posicion(lista,0)==5,"El elemento esta en la primer posicion")
    pa2m_afirmar(lista_quitar(lista)==&elemento,"Puedo remover correctamente el elemento que ingrese a la lista");
    pa2m_afirmar(lista_vacia(lista),"La lista vuelve a estar vacia");
    pa2m_afirmar(lista_quitar(lista)==NULL,"No se pueden quitar elementos de una lista vacia");

    lista_destruir(lista);
}

void DadaUnaListaNoNULLPuedoInsertarYRemoverVariosElementos(){
    lista_t* lista = lista_crear();
    int elemento_1 = 5, elemento_2 = 100, elemento_3 = 1000;
    char caracter = 'S';
    pa2m_afirmar(lista_vacia(lista),"Inicialmente la lista esta vacia");
    pa2m_afirmar(lista_primero(lista)==NULL,"Si no inserto elementos el primero es NULL");
    lista_insertar(lista,&elemento_1);
    pa2m_afirmar(*(int*)lista_primero(lista)==5,"El primer elemento es 5");
    pa2m_afirmar(lista_tamanio(lista)==1,"La lista tiene 1 elemento");
    lista_insertar(lista,&elemento_2);
    pa2m_afirmar(*(int*)lista_ultimo(lista)==100,"El segundo elemento es 100");
    pa2m_afirmar(lista_tamanio(lista)==2,"La lista tiene 2 elementos");
    lista_insertar(lista,&elemento_3);
    pa2m_afirmar(*(int*)lista_ultimo(lista)==1000,"El tercer elemento es 1000");
    pa2m_afirmar(lista_tamanio(lista)==3,"La lista tiene 3 elementos");
    lista_insertar(lista,&caracter);
    pa2m_afirmar(*(char*)lista_ultimo(lista)=='S',"El ultimo elemento es 'S'");
    pa2m_afirmar(lista_tamanio(lista)==4,"La lista tiene 4 elementos");
    pa2m_afirmar(lista_vacia(lista)==false,"La lista ya no esta vacia");
    pa2m_afirmar(lista_elemento_en_posicion(lista,2)==&elemento_3,"El tercer elemento esta en la tercera posicion");
    pa2m_afirmar(lista_primero(lista)==&elemento_1,"El primer elemento es el 5");
    pa2m_afirmar(lista_ultimo(lista)==&caracter,"El ultimo elemento es 'S'");
    pa2m_afirmar(lista_elemento_en_posicion(lista,3)==&caracter,"El ultimo elemento esta en la ultima posicion");
    pa2m_afirmar(lista_quitar(lista)==&caracter,"Puedo remover el ultimo elemento de la lista");

    lista_destruir(lista);
}

void DadaUnaListaNoNULLPuedoInsertarYRemoverElementosNULL(){
    lista_t* lista = lista_crear();
    int* entero_null = NULL;

    pa2m_afirmar(lista_vacia(lista),"Inicialmente la lista esta vacia");
    pa2m_afirmar(lista_quitar(lista)==NULL,"No se puede eliminar elementos de una lista vacia");
    lista_insertar(lista,entero_null);
    pa2m_afirmar(lista_primero(lista)==NULL,"El primer elemento es NULL");
    pa2m_afirmar(lista_ultimo(lista)==NULL,"El ultimo elemento es igual al primero por lo tanto es NULL");
    pa2m_afirmar(lista_vacia(lista)==false,"La lista ya no esta vacia ya que contiene elementos NULL");
    pa2m_afirmar(lista_quitar(lista)==NULL,"Intentar remover un elemento NULL devuelve NULL");
    pa2m_afirmar(lista_primero(lista)==NULL,"Si elimino el primer elemento la lista sigue siendo NULL ya que esta vacia");
    pa2m_afirmar(lista_ultimo(lista)==NULL,"Si elimino el ultimo elemento la lista sigue siendo NULL ya que esta vacia");
    pa2m_afirmar(lista_vacia(lista),"La lista vuelve a estar vacia");

    lista_destruir(lista);
}

void DadaUnaListaNoNULLPuedoInsertarYRemoverEnPosicionDada(){
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_vacia(lista),"Inicialmente la lista esta vacia");
    int elemento_1 = 5, elemento_2 = 100, elemento_3 = 1000;
    int elemento_4 = 99;
    int elemento_5 = 199;
    int elemento_6 = 299;
    int elemento_7 = 300;

    lista_insertar(lista,&elemento_1);
    lista_insertar(lista,&elemento_2);
    lista_insertar(lista,&elemento_3);
    pa2m_afirmar(lista_tamanio(lista)==3,"Se ingresaron 3 elementos de manera ordenada");
    lista_insertar_en_posicion(lista,&elemento_4,1);
    pa2m_afirmar(*(int*)lista_elemento_en_posicion(lista,1)==99,"Se pudo ingresar correctamente un elemento en la posicion 1");
    pa2m_afirmar(lista_tamanio(lista)==4,"Ahora hay 4 elementos en la lista");
    lista_insertar_en_posicion(lista,&elemento_5,0);
    pa2m_afirmar(*(int*)lista_elemento_en_posicion(lista,0)==199,"Se pudo ingresar correctamente un elemento en la posicion 0");
    pa2m_afirmar(lista_tamanio(lista)==5,"Ahora hay 5 elementos en la lista");
    lista_insertar_en_posicion(lista,&elemento_6,6);
    pa2m_afirmar(*(int*)lista_elemento_en_posicion(lista,6)==299,"Se pudo ingresar correctamente un elemento en la posicion 6");
    pa2m_afirmar(lista_tamanio(lista)==6,"Ahora hay 6 elementos en la lista");
    lista_insertar_en_posicion(lista,&elemento_7,80);
    pa2m_afirmar(*(int*)lista_elemento_en_posicion(lista,7)==300,"Se intento ingresar un elemento en la posicion 80 pero como no existe se lo puso al final de la lista");
    pa2m_afirmar(lista_tamanio(lista)==7,"Ahora hay 7 elementos en la lista");

    /*
    * Para ahorrarte cuentas la lista quedaria asi -> [199,5,99,100,1000,289,300]
    */

    lista_quitar(lista);
    pa2m_afirmar(lista_elemento_en_posicion(lista,7)==NULL,"Puedo remover un ultimo elemento de la lista");
    pa2m_afirmar(lista_tamanio(lista)==6,"Ahora hay 6 elementos en la lista");
    lista_quitar_de_posicion(lista,6);
    pa2m_afirmar(lista_elemento_en_posicion(lista,6)==NULL,"Puedo remover un ultimo elemento de la lista usando la funcion de remover por posicion");
    pa2m_afirmar(lista_tamanio(lista)==5,"Ahora hay 5 elementos en la lista");
    lista_quitar_de_posicion(lista,0);
    pa2m_afirmar(*(int*)lista_elemento_en_posicion(lista,0)==5,"Puedo remover el primer elemento de la lista usando la funcion de remover por posicion");
    pa2m_afirmar(lista_tamanio(lista)==4,"Ahora hay 4 elementos en la lista");
    lista_quitar_de_posicion(lista,1);
    pa2m_afirmar(*(int*)lista_elemento_en_posicion(lista,1)==100,"Puedo remover un elemento intermedio de la lista usando la funcion de remover por posicion");
    pa2m_afirmar(lista_tamanio(lista)==3,"Ahora hay 3 elementos en la lista");

    /*
    * Para ahorrarte cuentas la lista quedaria asi una vez removido los elementos y reacomodada -> [5,100,1000]
    */

    lista_destruir(lista);
}

void DadaUnaListaVaciaNoPuedoEliminarElementos(){
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_vacia(lista),"La lista se crea vacia");
    pa2m_afirmar(lista_tamanio(lista)==0,"El tamaño de la lista es 0");
    pa2m_afirmar(lista_elemento_en_posicion(lista,0)==NULL,"Dado que la lista esta vacia no hay nada en la primer posicion");
    pa2m_afirmar(lista_elemento_en_posicion(lista,80)==NULL,"Dado que la lista esta vacia no hay nada en ninguna posicion");
    pa2m_afirmar(lista_quitar(lista)==NULL,"No puedo eliminar el ultimo elemento de la lista ya que esta vacia");
    pa2m_afirmar(lista_quitar_de_posicion(lista,0)==NULL,"No puedo eliminar el primer elemento de la lista ya que esta vacia");
    pa2m_afirmar(lista_quitar_de_posicion(lista,80)==NULL,"No puedo remover ningun elemento de la lista si esta esta vacia");

    lista_destruir(lista);
}

void DadaUnaListaNULLNoPuedoEliminarElementos(){
    lista_t* lista = NULL;

    pa2m_afirmar(lista_vacia(lista),"La lista no existe");
    pa2m_afirmar(lista_tamanio(lista)==0,"El tamaño de la lista es 0 ya que no existe");
    pa2m_afirmar(lista_elemento_en_posicion(lista,0)==NULL,"Dado que la lista no existe no hay nada en la primer posicion");
    pa2m_afirmar(lista_elemento_en_posicion(lista,80)==NULL,"Dado que la lista no existe no hay nada en ninguna posicion");
    pa2m_afirmar(lista_quitar(lista)==NULL,"No puedo eliminar el ultimo elemento de la lista ya que no existe");
    pa2m_afirmar(lista_quitar_de_posicion(lista,0)==NULL,"No puedo eliminar el primer elemento de la lista ya que no existe");
    pa2m_afirmar(lista_quitar_de_posicion(lista,80)==NULL,"No puedo remover ningun elemento de la lista si esta no existe");
}

void DadaUnaListaNoNULLPuedoAgregarYRemoverElementosNULL(){
    lista_t* lista = lista_crear();
    int* elemento = NULL;
    int elemento_valido = 5;

    pa2m_afirmar(lista_vacia(lista),"La lista esta vacia");
    pa2m_afirmar(lista_tamanio(lista)==0,"El tamaño de la lista es 0");
    lista_insertar(lista,elemento);
    pa2m_afirmar(lista_tamanio(lista)==1,"Si inserto NULL a la lista esta ahora tiene 1 elemento");
    lista_insertar(lista,&elemento_valido);
    lista_insertar(lista,elemento);
    lista_insertar(lista,&elemento_valido);
    pa2m_afirmar(lista_tamanio(lista)==4,"El tamaño de la lista es 4");
    lista_insertar_en_posicion(lista,elemento,1);
    pa2m_afirmar(lista_tamanio(lista)==5,"Puedo meter un elemento NULL entre medio de la lista");
    pa2m_afirmar(lista_quitar_de_posicion(lista,0)==NULL,"Puedo remover un elemento NULL en la primer posicion");
    pa2m_afirmar(lista_quitar_de_posicion(lista,2)==NULL,"Puedo remover un elemento NULL ubicado en el medio de la lista");
    lista_quitar(lista);
    lista_quitar(lista);
    pa2m_afirmar(lista_quitar(lista)==NULL,"Puedo remover un elemento NULL en el final de la lista");
    pa2m_afirmar(lista_vacia(lista),"La lista vuelve a estar vacia");

    lista_destruir(lista);

}

void DadaUnaListaNoNULLPuedoOperarConStrings(){
    lista_t* lista = lista_crear();
    char* s1 = "Hola";
    char* s2 = "Mundo";
    char* s3 = "Este es un string innecesariamente largo el cual solo tiene como finalidad poder probar el programa";
    char* s4 = "gfdjgfdjgkfdgkfdklgjdfkgjfdklgfdjklgjdflkgdfjgioewurehfufesufhsdujfdoghjdofgjdfogrkegpdrgkdgordgpodjgirsfjdroesofjhsefosehfosejfseofisfhdsfjkdslhgfodigfdoigfdjgiofdjgdfpgkfdgfdkgfdpgdfgdf";

    pa2m_afirmar(lista_vacia(lista),"Inicialmente la lista esta vacia");
    pa2m_afirmar(lista_tamanio(lista)==0,"El tamaño de la lista es 0");
    lista_insertar(lista,s1);
    lista_insertar(lista,s2);
    lista_insertar(lista,s3);
    lista_insertar_en_posicion(lista,s4,1);
    pa2m_afirmar(strcmp(lista_elemento_en_posicion(lista,2),"Mundo")==0,"Los strings estan en la posicion correcta");
    pa2m_afirmar(lista_tamanio(lista)==4,"El tamaño de la lista es 4 despues de ingresar strings");
    lista_quitar_de_posicion(lista,0);
    pa2m_afirmar(lista_tamanio(lista)==3,"Puedo remover un string del principio de la lista");
    lista_quitar_de_posicion(lista,1);
    pa2m_afirmar(lista_tamanio(lista)==2,"Puedo remover un string del medio de la lista");
    lista_quitar_de_posicion(lista,2);
    pa2m_afirmar(lista_tamanio(lista)==1,"Puedo remover un string del final de la lista");
    lista_quitar(lista);
    pa2m_afirmar(lista_vacia(lista),"La lista vuelve a estar vacia");

    lista_destruir(lista);
}

void DadaUnaListaNoNULLYUnIteradorExternoNULLNoPuedoIterarElementos(){
    lista_t* lista = lista_crear();
    int* nulo = NULL;
    int elemento_1 = 5;
    int elemento_2 = 10;
    char elemento_3 = 'M';
    char* string = "Hola";


    lista_insertar(lista,&nulo);
    lista_insertar(lista,&elemento_1);
    lista_insertar(lista,&elemento_2);
    lista_insertar(lista,&elemento_3);
    lista_insertar(lista,&string);

    lista_iterador_t* iterador = NULL;

    pa2m_afirmar(lista_iterador_avanzar(iterador)==false,"No puedo avanzar si el iterador es NULL");
    pa2m_afirmar(lista_iterador_tiene_siguiente(iterador)==false,"No puedo saber si hay siguiente si el iterador es NULL");
    pa2m_afirmar(lista_iterador_elemento_actual(iterador)==NULL,"No puedo saber el elemento actual si el iterador es NULL");

    lista_destruir(lista);
}

void DadaUnaListaNULLYUnIteradorExternoValidoNoPuedoIterarElementos(){
    lista_t* lista = NULL;
    lista_iterador_t* iterador = lista_iterador_crear(lista);

    pa2m_afirmar(lista_iterador_avanzar(iterador)==false,"No puedo avanzar si el iterador se crea sobre una lista NULL");
    pa2m_afirmar(lista_iterador_tiene_siguiente(iterador)==false,"No puedo saber si hay siguiente si el iterador se crea sobre una lista NULL");
    pa2m_afirmar(lista_iterador_elemento_actual(iterador)==NULL,"No puedo saber el elemento actual si el iterador se crea sobre una lista NULL");

    lista_iterador_destruir(iterador);
}

void DadaUnaListaVaciaYUnIteradorExternoValidoNopuedoIterarElementos(){
    lista_t* lista = lista_crear();
    lista_iterador_t* iterador = lista_iterador_crear(lista);

    pa2m_afirmar(lista_iterador_avanzar(iterador)==false,"No puedo avanzar si el iterador se crea sobre una lista vacia");
    pa2m_afirmar(lista_iterador_tiene_siguiente(iterador)==false,"No puedo saber si hay siguiente si el iterador se crea sobre una lista vacia");
    pa2m_afirmar(lista_iterador_elemento_actual(iterador)==NULL,"No puedo saber el elemento actual si el iterador se crea sobre una lista vacia");

    lista_iterador_destruir(iterador);
    lista_destruir(lista);
}

void DadaUnaListaNoNULLYUnIteradorExternoValidoPuedoIterarElementos(){
    lista_t* lista = lista_crear();

    int* nulo = NULL;
    int elemento_1 = 5;
    int elemento_2 = 10;
    char elemento_3 = 'M';
    char* string = "Hola";

    lista_insertar(lista,&nulo);
    lista_insertar(lista,&elemento_1);
    lista_insertar(lista,&elemento_2);
    lista_insertar(lista,&elemento_3);
    lista_insertar(lista,&string);

    lista_iterador_t* iterador = lista_iterador_crear(lista);

    size_t contador_movimientos = 0;
    while(lista_iterador_tiene_siguiente(iterador) == true){
        contador_movimientos++;
        lista_iterador_avanzar(iterador);
    }
    pa2m_afirmar(contador_movimientos==5,"Dada una lista y un iterador externo validos puedo avanzar la cantidad de elementos en la lista con el iterador");

    lista_iterador_destruir(iterador);
    lista_destruir(lista);
}

void DadaUnaListaNoNULLYUnIteradorExternoValidoPuedoOperarIterando(){
    lista_t* lista = lista_crear();

    int* nulo = NULL;
    int elemento_1 = 5;
    int elemento_2 = 10;
    char elemento_3 = 'M';
    char* string = "Hola";

    lista_insertar(lista,&nulo);
    lista_insertar(lista,&elemento_1);
    lista_insertar(lista,&elemento_2);
    lista_insertar(lista,&elemento_3);
    lista_insertar(lista,&string);

    lista_iterador_t* iterador = lista_iterador_crear(lista);

    pa2m_afirmar(lista_iterador_tiene_siguiente(iterador),"Dado una lista llena y iterador valido puedo iterar si hay mas elementos siguientes");
    pa2m_afirmar(*(int**)lista_iterador_elemento_actual(iterador)==NULL,"Dado una lista llena y iterador valido puedo ver el elemento actual iterando correctamente");
    pa2m_afirmar(lista_iterador_avanzar(iterador),"Dado una lista llena y iterador valido puedo avanzar al siguiente elemento");

    pa2m_afirmar(lista_iterador_tiene_siguiente(iterador),"Dado una lista llena y iterador valido puedo iterar si hay mas elementos siguientes");
    pa2m_afirmar(*(int*)lista_iterador_elemento_actual(iterador)==5,"Dado una lista llena y iterador valido puedo ver el elemento actual iterando correctamente");
    pa2m_afirmar(lista_iterador_avanzar(iterador),"Dado una lista llena y iterador valido puedo avanzar al siguiente elemento");

    pa2m_afirmar(lista_iterador_tiene_siguiente(iterador),"Dado una lista llena y iterador valido puedo iterar si hay mas elementos siguientes");
    pa2m_afirmar(*(int*)lista_iterador_elemento_actual(iterador)==10,"Dado una lista llena y iterador valido puedo ver el elemento actual iterando correctamente");
    pa2m_afirmar(lista_iterador_avanzar(iterador),"Dado una lista llena y iterador valido puedo avanzar al siguiente elemento");

    pa2m_afirmar(lista_iterador_tiene_siguiente(iterador),"Dado una lista llena y iterador valido puedo iterar si hay mas elementos siguientes");
    pa2m_afirmar(*(char*)lista_iterador_elemento_actual(iterador)=='M',"Dado una lista llena y iterador valido puedo ver el elemento actual iterando correctamente");
    pa2m_afirmar(lista_iterador_avanzar(iterador),"Dado una lista llena y iterador valido puedo avanzar al siguiente elemento");

    pa2m_afirmar(lista_iterador_tiene_siguiente(iterador),"Dado una lista llena y iterador valido puedo iterar si hay mas elementos siguientes");
    pa2m_afirmar(strcmp(*(char**)lista_iterador_elemento_actual(iterador),"Hola")==0,"Dado una lista llena y iterador valido puedo ver el elemento actual iterando correctamente");
    pa2m_afirmar(lista_iterador_avanzar(iterador) == false,"Dado una lista llena y iterador valido puedo avanzar al siguiente elemento el cual es NULL");

    pa2m_afirmar(lista_iterador_tiene_siguiente(iterador)==false,"Dado una lista llena y iterador valido no puedo avanzar ya que estoy en el final");
    pa2m_afirmar(lista_iterador_elemento_actual(iterador)==NULL,"Dado una lista llena y iterador valido ya estoy en el final el elemento es NULL");
    pa2m_afirmar(lista_iterador_avanzar(iterador) == false,"Dado una lista llena y iterador valido ya no puedo seguir avanzando ya que estoy en una posicion NULL");

    lista_iterador_destruir(iterador);
    lista_destruir(lista);
}

void DadaUnaListaVaciaYUnIteradorInternoValidoNoPuedoIterarElementos(){
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista_vacia(lista),"Se crea una lista vacia");

    size_t* contexto = 0;

    size_t recorrer = lista_con_cada_elemento(lista,prueba_iterador_interno,&contexto);

    pa2m_afirmar(recorrer == 0,"Dada una lista vacia y un iterador interno valido no puedo recorrer ya que la lista esta vacia");

    lista_destruir(lista);
}

void DadaUnaListaNULLYUnIteradorInternoValidoNoPuedoIterarElementos(){
    lista_t* lista = NULL;

    pa2m_afirmar(lista_vacia(lista),"Se crea una lista vacia");

    size_t* contexto = 0;

    size_t recorrer = lista_con_cada_elemento(lista,prueba_iterador_interno,&contexto);

    pa2m_afirmar(recorrer == 0,"Dada una lista NULL y un iterador interno valido no puedo recorrer ya que la lista esta NULL");
}

void DadaUnaListaNoNULLYUnIteradorInternoValidoConFuncionNULLNoPuedoIterarElementos(){
    lista_t* lista = lista_crear();

    int* nulo = NULL;
    int elemento_1 = 5;
    int elemento_2 = 10;
    char elemento_3 = 'M';
    char* string = "Hola";

    lista_insertar(lista,&nulo);
    lista_insertar(lista,&elemento_1);
    lista_insertar(lista,&elemento_2);
    lista_insertar(lista,&elemento_3);
    lista_insertar(lista,&string);

    size_t* contexto = 0;

    size_t recorrer = lista_con_cada_elemento(lista,NULL,&contexto);

    pa2m_afirmar(recorrer == 0,"Dada una lista valida y un iterador interno valido no puedo recorrer ya que la funcion enviada es NULL");

    lista_destruir(lista);
}

void DadaUnaListaNoNULLYUnIteradorInternoValidoConFuncionValidaYContextoNULLNoPuedoIterarElementos(){
    lista_t* lista = lista_crear();

    int* nulo = NULL;
    int elemento_1 = 5;
    int elemento_2 = 10;
    char elemento_3 = 'M';
    char* string = "Hola";

    lista_insertar(lista,&nulo);
    lista_insertar(lista,&elemento_1);
    lista_insertar(lista,&elemento_2);
    lista_insertar(lista,&elemento_3);
    lista_insertar(lista,&string);

    size_t recorrer = lista_con_cada_elemento(lista,prueba_iterador_interno,NULL);

    pa2m_afirmar(recorrer == 0,"Dada una lista valida y un iterador interno valido no puedo recorrer ya que la funcion enviada es NULL");

    lista_destruir(lista);
}

void DadaUnaListaNoNULLYUnIteradorInternoValidoConFuncionValidaYContextoValidoPuedoIterarElementos(){
    lista_t* lista = lista_crear();

    int* nulo = NULL;
    int elemento_1 = 5;
    int elemento_2 = 10;
    char elemento_3 = 'M';
    char* string = "Hola";

    lista_insertar(lista,&nulo);
    lista_insertar(lista,&elemento_1);
    lista_insertar(lista,&elemento_2);
    lista_insertar(lista,&elemento_3);
    lista_insertar(lista,&string);

    size_t* contexto = 0;

    size_t recorrer = lista_con_cada_elemento(lista,prueba_iterador_interno,&contexto);

    pa2m_afirmar(recorrer == 5,"Dada una lista valida y un iterador interno puedo recorrer la lista hasta el final");

    lista_destruir(lista);
}

void DadaUnaListaNoNULLYUnIteradorInternoValidoConFuncionValidaYContextoValidoPuedoIterarHastaAnteultimoElemento(){
    lista_t* lista = lista_crear();

    int* nulo = NULL;
    int elemento_1 = 5;
    int elemento_2 = 10;
    char elemento_3 = 'M';
    char* string = "Hola";

    lista_insertar(lista,&nulo);
    lista_insertar(lista,&elemento_1);
    lista_insertar(lista,&elemento_2);
    lista_insertar(lista,&elemento_3);
    lista_insertar(lista,&string);

    size_t* contexto = 0;

    size_t recorrer = lista_con_cada_elemento(lista,prueba_iterador_interno_hasta_anteultimo_elemento,&contexto);

    pa2m_afirmar(recorrer == 3,"Dada una lista valida y un iterador interno puedo recorrer la lista hasta el anteultimo elemento");

    lista_destruir(lista);
}

void DadaUnaListaNoNULLYUnIteradorInternoValidoConFuncionValidaYContextoValidoPuedoIterarUsandoContexto(){
    lista_t* lista = lista_crear();

    char elemento_1 = 'H';
    char elemento_2 = 'O';
    char elemento_3 = 'L';
    char elemento_4 = 'A';

    lista_insertar(lista,&elemento_1);
    lista_insertar(lista,&elemento_2);
    lista_insertar(lista,&elemento_3);
    lista_insertar(lista,&elemento_4);

    size_t contexto_contador = 0;

    size_t recorrer = lista_con_cada_elemento(lista,prueba_iterador_interno_con_contexto,&contexto_contador);

    pa2m_afirmar(recorrer == 4,"Dada una lista valida y un iterador interno con contexto valido puedo recorrer toda la lista");
    pa2m_afirmar(contexto_contador == 4,"Pude recorrer la lista y modificar el contexto enviado");

    lista_destruir(lista);
}

void DadaUnaColaNoNULLPuedoEncolarYDesencolarElementos(){
    cola_t* cola = cola_crear();

    int* nulo = NULL;
    int elemento_1 = 5;
    int elemento_2 = 10;
    char elemento_3 = 'M';
    char* string = "Hola";

    pa2m_afirmar(cola_vacia(cola),"La cola se crea incialmente vacia");

    cola_encolar(cola,&nulo);
    pa2m_afirmar(cola_tamanio(cola)==1,"Puedo ingresar un elemento NULL en la cola");

    cola_encolar(cola,&elemento_1);
    pa2m_afirmar(cola_tamanio(cola)==2,"Puedo ingresar un elemento int en la cola");

    cola_encolar(cola,&elemento_2);
    pa2m_afirmar(cola_tamanio(cola)==3,"Puedo ingresar un segundo elemento int en la cola");

    cola_encolar(cola,&elemento_3);
    pa2m_afirmar(cola_tamanio(cola)==4,"Puedo ingresar un elemento char en la cola");

    cola_encolar(cola,&string);
    pa2m_afirmar(cola_tamanio(cola)==5,"Puedo ingresar un elemento string en la cola");

    pa2m_afirmar(cola_vacia(cola)==false,"La cola ya no esta vacia");

    pa2m_afirmar(*(int**)cola_frente(cola)==NULL,"El primer elemento de la cola es el correcto");

    pa2m_afirmar(strcmp(*(char**)(lista_ultimo((lista_t*)cola)),"Hola")==0,"El ultimo elemento de la cola es el correcto");

    cola_destruir(cola);
}

void DadaUnaPilaNoNULLPuedoApilarYDesapilarElementos(){
    pila_t* pila = pila_crear();

    int* nulo = NULL;
    int elemento_1 = 5;
    int elemento_2 = 10;
    char elemento_3 = 'M';
    char* string = "Hola";

    pa2m_afirmar(pila_vacia(pila),"La pila se crea inicialmente vacia");

    pila_apilar(pila,&nulo);
    pa2m_afirmar(pila_tamanio(pila)==1,"Puedo ingresar un elemento NULL en la pila");

    pila_apilar(pila,&elemento_1);
    pa2m_afirmar(pila_tamanio(pila)==2,"Puedo ingresar un elemento int en la pila");

    pila_apilar(pila,&elemento_2);
    pa2m_afirmar(pila_tamanio(pila)==3,"Puedo ingresar un segundo elemento int en la pila");

    pila_apilar(pila,&elemento_3);
    pa2m_afirmar(pila_tamanio(pila)==4,"Puedo ingresar un elemento char en la pila");

    pila_apilar(pila,&string);
    pa2m_afirmar(pila_tamanio(pila)==5,"Puedo ingresar un elemento string en la pila");

    pa2m_afirmar(pila_vacia(pila),"La pila ya no esta vacia");

    pa2m_afirmar(strcmp(*(char**)pila_tope(pila),"Hola")==0,"El ultimo elemento de la pila es el correcto");

    pa2m_afirmar(*(int**)lista_primero((lista_t*)pila)==NULL,"El primer elemento de la pila es el correcto");

    pila_destruir(pila);
}

void AlBorrarUnElementoDeLalistaQuedaCon0Elementos(){
    lista_t* lista = lista_crear();

    int* nulo = NULL;
    int elemento_1 = 5;
    int elemento_2 = 10;
    char elemento_3 = 'M';
    char* string = "Hola";

    pa2m_afirmar(lista_vacia(lista),"Inicialmente la lista esta vacia");
    pa2m_afirmar(lista_tamanio(lista)==0,"Inicialmente la lista tiene tamaño 0");

    lista_insertar(lista,nulo);
    lista_insertar(lista,&elemento_1);
    lista_insertar(lista,&elemento_2);
    lista_insertar(lista,&elemento_3);
    lista_insertar(lista,string);

    pa2m_afirmar(lista_tamanio(lista)==5,"La lista tiene ahora tamaño 5");

    lista_quitar(lista);
    lista_quitar(lista);
    lista_quitar(lista);
    lista_quitar(lista);
    lista_quitar(lista);

    pa2m_afirmar(lista_tamanio(lista)==0,"La lista vuelve a tener tamaño 0");
    pa2m_afirmar(lista_quitar(lista)==NULL,"No puedo quitar un elemento de la lista si no tiene elementos");

    lista_destruir(lista);
}

void PuedoBorrarEnUnaPosicionMayorALaCantidad(){
    lista_t* lista = lista_crear();

    int* nulo = NULL;
    int elemento_1 = 5;
    int elemento_2 = 10;
    char elemento_3 = 'M';
    char* string = "Hola";
    int elemento_4 = 100;

    pa2m_afirmar(lista_vacia(lista),"Inicialmente la lista esta vacia");
    pa2m_afirmar(lista_tamanio(lista)==0,"Inicialmente la lista tiene tamaño 0");

    lista_insertar(lista,nulo);
    lista_insertar(lista,&elemento_1);
    lista_insertar(lista,&elemento_2);
    lista_insertar(lista,&elemento_3);
    lista_insertar(lista,string);
    lista_insertar(lista,&elemento_4);

    pa2m_afirmar(lista_tamanio(lista)==6,"La lista tiene ahora tamaño 6");

    pa2m_afirmar(*(int*)lista_quitar_de_posicion(lista,10)==100,"Si intento eliminar un elemento en una posicion mayor al tamaño de la lista elimina el ultimo elemento de la lista");

    lista_destruir(lista);
}



int main() {
    pa2m_nuevo_grupo("Pruebas de creacion y destruccion de la lista");
    DadaUnaListaNULLSeCreaUnaVacia();
    DadaUnaListaNoNULLSeCreaUnaListaVacia();
    pa2m_nuevo_grupo("Pruebas de insertar y remover en lista NULL");
    DadaUnaListaNULLPuedoInsertarYRemover();
    pa2m_nuevo_grupo("Pruebas de insertar un solo elemento en una lista valida");
    DadaUnaListaNoNULLPuedoInsertarYRemoverUnSoloElemento();  
    pa2m_nuevo_grupo("Pruebas de insertar varios elementos en una lista valida");
    DadaUnaListaNoNULLPuedoInsertarYRemoverVariosElementos();
    pa2m_nuevo_grupo("Pruebas de insertar elementos NULL");
    DadaUnaListaNoNULLPuedoInsertarYRemoverElementosNULL(); 
    pa2m_nuevo_grupo("Pruebas de insertar y eliminar elementos en una posicion dada");
    DadaUnaListaNoNULLPuedoInsertarYRemoverEnPosicionDada();
    pa2m_nuevo_grupo("Pruebas de eliminar elementos sobre una lista vacia o NULL");
    DadaUnaListaVaciaNoPuedoEliminarElementos();
    DadaUnaListaNULLNoPuedoEliminarElementos();
    DadaUnaListaNoNULLPuedoAgregarYRemoverElementosNULL();
    pa2m_nuevo_grupo("Pruebas con listas y strings");
    DadaUnaListaNoNULLPuedoOperarConStrings();
    pa2m_nuevo_grupo("Pruebas usando el iterador externo");
    DadaUnaListaNoNULLYUnIteradorExternoNULLNoPuedoIterarElementos();
    DadaUnaListaNULLYUnIteradorExternoValidoNoPuedoIterarElementos();
    DadaUnaListaVaciaYUnIteradorExternoValidoNopuedoIterarElementos();
    DadaUnaListaNoNULLYUnIteradorExternoValidoPuedoIterarElementos();
    DadaUnaListaNoNULLYUnIteradorExternoValidoPuedoOperarIterando();
    pa2m_nuevo_grupo("Pruebas usando el iterador interno");
    DadaUnaListaVaciaYUnIteradorInternoValidoNoPuedoIterarElementos();
    DadaUnaListaNULLYUnIteradorInternoValidoNoPuedoIterarElementos();
    DadaUnaListaNoNULLYUnIteradorInternoValidoConFuncionNULLNoPuedoIterarElementos();
    DadaUnaListaNoNULLYUnIteradorInternoValidoConFuncionValidaYContextoNULLNoPuedoIterarElementos();
    DadaUnaListaNoNULLYUnIteradorInternoValidoConFuncionValidaYContextoValidoPuedoIterarElementos();
    DadaUnaListaNoNULLYUnIteradorInternoValidoConFuncionValidaYContextoValidoPuedoIterarHastaAnteultimoElemento();
    pa2m_nuevo_grupo("Pruebas usando a la lista como cola");
    DadaUnaColaNoNULLPuedoEncolarYDesencolarElementos();
    pa2m_nuevo_grupo("Recreacion de pruebas chanutron");
    AlBorrarUnElementoDeLalistaQuedaCon0Elementos();
    PuedoBorrarEnUnaPosicionMayorALaCantidad();

    return pa2m_mostrar_reporte();
}
