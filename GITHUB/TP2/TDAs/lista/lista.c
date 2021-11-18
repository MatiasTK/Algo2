#include "lista.h"
#include <stdlib.h>

#define EXITO 0
#define ERROR -1

#define ES_PRIMERO true
#define NO_ES_PRIMERO false

/*
 * Inserta un nodo en la primera posicion de la lista.
 * 
 * Recibe un puntero a la lista (que debe ser valido) y al elemento del nodo a insertar.
 *
 * Devuelve: 0 si se pudo insertar el nodo.
 *		  	-1 si no se pudo insertar el nodo.
 */
int insertar_nodo_al_principio(lista_t* lista, void* elemento, bool es_primero){

	nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
	
	if (nodo_nuevo){
		(*nodo_nuevo).elemento = elemento;
		
		if (es_primero){
			(*nodo_nuevo).siguiente = NULL;
			(*lista).nodo_inicio = nodo_nuevo;
			(*lista).nodo_fin = nodo_nuevo;
		}
		else {
			(*nodo_nuevo).siguiente = (*lista).nodo_inicio;
			(*lista).nodo_inicio = nodo_nuevo;
		}
		
		(*lista).cantidad+= 1;	
		return EXITO;
	}

	return ERROR;
}

/*
 * Inserta un nodo en la ultima posicion de la lista.
 * 
 * Recibe un puntero a la lista (que debe ser valido) y al elemento del nodo a insertar.
 *
 * Devuelve: 0 si se pudo insertar el nodo.
 *		  	-1 si no se pudo insertar el nodo.
 */
int insertar_nodo_al_final(lista_t* lista, void* elemento){

	nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));

	if (nodo_nuevo){
		(*nodo_nuevo).elemento = elemento;
		(*nodo_nuevo).siguiente = NULL;

		(*(*lista).nodo_fin).siguiente = nodo_nuevo;
		(*lista).nodo_fin = nodo_nuevo;
		(*lista).cantidad+= 1;

		return EXITO;
	}

	return ERROR;
}

/*
 * Inserta un nodo en una posicion de la lista que no sea la primera ni la ultima.
 * 
 * Recibe un puntero a la lista (que debe ser valido), al elemento del nodo a insertar
 * y una copia de la posicion de la lista donde se debe insertar el nodo.
 * 
 * Devuelve: 0 si se pudo insertar el nodo.
 *			-1 si no se pudo insertar el nodo.
 */
int insertar_nodo_al_medio(lista_t* lista, void* elemento, size_t posicion){

	nodo_t* nodo_actual = (*lista).nodo_inicio;
	nodo_t* nodo_anterior = NULL;

	while (posicion > 0){
		nodo_anterior = nodo_actual;
		nodo_actual = (*nodo_actual).siguiente;
		posicion--;
	}

	nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));

	if (nodo_nuevo){
		(*nodo_nuevo).siguiente = nodo_actual;
		(*nodo_nuevo).elemento = elemento;
		(*nodo_anterior).siguiente = nodo_nuevo;
		(*lista).cantidad+= 1;
	
		return EXITO;
	}

	return ERROR;
}

/*
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t* lista_crear(lista_liberar_elemento destructor){

	lista_t* lista = malloc(sizeof(lista_t));
	
	if (lista){
		(*lista).nodo_inicio = NULL;
		(*lista).nodo_fin = NULL;
		(*lista).cantidad = 0;
		(*lista).destructor = destructor;
	}

	return lista;
}

/*
 * Inserta un elemento al final de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar(lista_t* lista, void* elemento){

	if (!lista) return ERROR;

	if (!(*lista).nodo_inicio)
		return insertar_nodo_al_principio(lista, elemento, ES_PRIMERO);

	return insertar_nodo_al_final(lista, elemento);
}

/*
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){

	if (!lista) return ERROR;

	if (!(*lista).nodo_inicio)
		return insertar_nodo_al_principio(lista, elemento, ES_PRIMERO);

	if (posicion == 0)
		return insertar_nodo_al_principio(lista, elemento, NO_ES_PRIMERO);

	if (posicion >= lista_elementos(lista))
		return insertar_nodo_al_final(lista, elemento);

	return insertar_nodo_al_medio(lista, elemento, posicion);
}

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar(lista_t* lista){

	if (!lista || !(*lista).nodo_inicio) return ERROR;

	nodo_t* nodo_actual = (*lista).nodo_inicio;
	nodo_t* nodo_anterior = NULL;

	while (nodo_actual != (*lista).nodo_fin){
		nodo_anterior = nodo_actual;
		nodo_actual = (*nodo_actual).siguiente;
	}

	if ((*lista).nodo_inicio != (*lista).nodo_fin){

		(*lista).nodo_fin = nodo_anterior;
		(*(*lista).nodo_fin).siguiente = NULL;
	}

	if ((*lista).nodo_inicio == nodo_actual){

		(*lista).nodo_inicio = NULL;
		(*lista).nodo_fin = NULL;
	}

	if ((*lista).destructor)
		(*lista).destructor((*nodo_actual).elemento);
	free(nodo_actual);
	(*lista).cantidad-= 1;

	return EXITO;
}

/*
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento.  
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar_de_posicion(lista_t* lista, size_t posicion){

	if (!lista || !(*lista).nodo_inicio) return ERROR;

	if (posicion == 0){
		nodo_t* nodo_a_borrar = (*lista).nodo_inicio;
		nodo_t* nodo_aux = (*(*lista).nodo_inicio).siguiente;

		if ((*lista).destructor)
			(*lista).destructor((*nodo_a_borrar).elemento);
		free(nodo_a_borrar);
		(*lista).nodo_inicio = nodo_aux;
		(*lista).cantidad--;

		return EXITO;
	}

	if (posicion >= (*lista).cantidad - 1)
		return lista_borrar(lista);

	nodo_t* nodo_actual = (*lista).nodo_inicio;
	nodo_t* nodo_anterior = NULL;

	while (posicion > 0){
		nodo_anterior = nodo_actual;
		nodo_actual = (*nodo_actual).siguiente;
		posicion--;
	}

	(*nodo_anterior).siguiente = (*nodo_actual).siguiente;

	if ((*lista).destructor)
		(*lista).destructor((*nodo_actual).elemento);
	free(nodo_actual);
	(*lista).cantidad--;

	return EXITO;
}

void* buscar_elemento(nodo_t* nodo_actual, size_t pos){
	
	if (!nodo_actual) return NULL;
	
	if (pos > 1 && !(*nodo_actual).siguiente) return NULL;

	if (pos == 0) return (*nodo_actual).elemento;
	
	return buscar_elemento((*nodo_actual).siguiente, pos-1);
}

/*
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){

	if (!lista) return NULL;

	return buscar_elemento((*lista).nodo_inicio, posicion);
}

/* 
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
void* lista_ultimo(lista_t* lista){
	
	if (!lista || !(*lista).nodo_fin) return NULL;

	return (*(*lista).nodo_fin).elemento;
}

/* 
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t* lista){
	return (!lista || !(*lista).nodo_inicio);
}

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t* lista){
	
	if (!lista) return 0;

	return (*lista).cantidad;
}

/* 
 * Apila un elemento.
 * Devuelve 0 si pudo o -1 en caso contrario.
 */
int lista_apilar(lista_t* lista, void* elemento){
	return lista_insertar(lista, elemento);
}

/* 
 * Desapila un elemento.
 * Devuelve 0 si pudo desapilar o -1 si no pudo.
 */
int lista_desapilar(lista_t* lista){
	return lista_borrar(lista);
}

/*
 * Devuelve el elemento en el tope de la pila o NULL
 * en caso de estar vacía.
 */
void* lista_tope(lista_t* lista){
	return lista_ultimo(lista);
}

/* 
 * Encola un elemento.
 * Devuelve 0 si pudo encolar o -1 si no pudo.
 */
int lista_encolar(lista_t* lista, void* elemento){
	return lista_insertar(lista, elemento);
}

/* 
 * Desencola un elemento.
 * Devuelve 0 si pudo desencolar o -1 si no pudo.
 */
int lista_desencolar(lista_t* lista){
	return lista_borrar_de_posicion(lista, 0);
}

/*
 * Devuelve el primer elemento de la cola o NULL en caso de estar
 * vacía.
 */
void* lista_primero(lista_t* lista){
	return lista_elemento_en_posicion(lista, 0);
}

/*
 * Recorre nodos de forma recursiva (hasta llega a un nodo nulo) para liberarlos.
 * 
 * Recibe un puntero a un nodo.
 * 
 * Devuelve una llamada a si misma o un free del nodo que recibe.
 */
void recorrer_para_liberar(nodo_t* nodo, lista_liberar_elemento destructor){

	if ((*nodo).siguiente)
		recorrer_para_liberar((*nodo).siguiente, destructor);
	
	if (destructor)
		destructor((*nodo).elemento);
	free(nodo);
}

/*
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t* lista){

	if (lista){

		if ((*lista).nodo_inicio)
			recorrer_para_liberar((*lista).nodo_inicio, (*lista).destructor);
		
		free(lista);
	}
}

/*
 * Crea un iterador para una lista. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique la lista iterada (agregando o quitando
 * elementos de la lista). 
 *
 * Al momento de la creación, el iterador queda listo para devolver el
 * primer elemento utilizando lista_iterador_elemento_actual.
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
lista_iterador_t* lista_iterador_crear(lista_t* lista){

	if (!lista) return NULL;

	lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));

	if (iterador){
		(*iterador).lista = lista;
		(*iterador).corriente = (*lista).nodo_inicio;
	}
	
	return iterador;
}

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	return (iterador && (*iterador).corriente);
}

/*
 * Avanza el iterador al siguiente elemento.
 * Devuelve true si pudo avanzar el iterador o false en caso de
 * que no queden elementos o en caso de error.
 *
 * Una vez llegado al último elemento, si se invoca a
 * lista_iterador_elemento_actual, el resultado siempre será NULL.
 */
bool lista_iterador_avanzar(lista_iterador_t* iterador){

	if (lista_iterador_tiene_siguiente(iterador)){

		(*iterador).corriente = (*(*iterador).corriente).siguiente;
		
		if (!(*iterador).corriente) return false;

		return true;
	}

	return false;
}

/*
 * Devuelve el elemento actual del iterador o NULL en caso de que no
 * exista dicho elemento o en caso de error.
 */
void* lista_iterador_elemento_actual(lista_iterador_t* iterador){

	if (!iterador || !(*iterador).corriente) return NULL;

	return (*(*iterador).corriente).elemento;
}

/*
 * Libera la memoria reservada por el iterador.
 */
void lista_iterador_destruir(lista_iterador_t* iterador){
	free(iterador);
}

/*
 * Recorrer los nodos de la lista hasta encontrar uno nulo o hasta que
 * la funcion devuelva false, sumando 1 cada vez que pueda seguir reco-
 * rriendo.
 * Recibe un puntero a nodo, un puntero a funcion valido y un puntero a contexto.
 * Devuelve 1 + un llamado a si mismo, o 0.
 */
size_t recorrer_nodos(nodo_t* nodo_actual, bool (*funcion)(void*, void*), void *contexto){
	if (!nodo_actual) return 0;

	if (funcion((*nodo_actual).elemento, contexto))
		return 1+recorrer_nodos((*nodo_actual).siguiente, funcion, contexto);
	
	return 1;
}

/*
 * Iterador interno. Recorre la lista e invoca la funcion con cada elemento de
 * la misma. Dicha función puede devolver true si se deben seguir recorriendo
 * elementos o false si se debe dejar de iterar elementos.
 *
 * La función retorna la cantidad de elementos iterados o 0 en caso de error.
 */
size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){

	if (!lista || !funcion) return 0;

	return recorrer_nodos((*lista).nodo_inicio, funcion, contexto);
}