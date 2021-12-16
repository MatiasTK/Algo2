#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

#define FALLO_ITERADOR 0
#define ERROR -1
#define EXITO 0
#define SIN_ELEMENTOS 0

int lista_desencolar(lista_t* lista);

/*
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t* lista_crear(lista_liberar_elemento destructor) {
	lista_t* lista = calloc(1, sizeof(lista_t));
	if (!lista) return NULL;
	lista->destructor = destructor;
	return lista;
}

/* 
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t* lista) {
	if(!lista) return true;
	return(lista->nodo_inicio == NULL && lista->nodo_fin == NULL && lista->cantidad == SIN_ELEMENTOS);
}

/*
 * Inserta un elemento al final de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar(lista_t* lista, void* elemento) {
	if(!lista) return ERROR;

	nodo_t* nodo_nuevo = calloc(1, sizeof(nodo_t));
	if(!nodo_nuevo) return ERROR;

	if(lista_vacia(lista))
		lista->nodo_inicio = nodo_nuevo;
	else
		lista->nodo_fin->siguiente = nodo_nuevo;

	lista->nodo_fin = nodo_nuevo;
	nodo_nuevo->elemento = elemento;
	(lista->cantidad)++;

	return EXITO;
}

/*
* Pre: La lista no puede ser nula y debe estar vacía. El nodo recibido
	debe estar reservado en el HEAP y estar inicializado con el elemento
	a asignar.
* Post: Inserta el elemento recibido en la lista vacía recibida. 
*/
void insertar_nodo_en_lista_vacia(lista_t* lista, nodo_t* nodo_nuevo) {
	lista->nodo_inicio = nodo_nuevo;
	lista->nodo_fin = nodo_nuevo;
	(lista->cantidad)++;
}

/*
* Pre: La lista no debe ser nula ni estar vacía. El nodo recibido debe
	estar reservado en el HEAP y estar inicializado con el elemento a 
	asignar.
* Post: Inserta el nodo recibido en la posicion recibida de la lista.
*/
void insertar_nodo_en_posicion(lista_t* lista, nodo_t* nodo_nuevo, size_t posicion) {
	nodo_t* nodo_actual = lista->nodo_inicio;
	if (posicion >= (lista->cantidad))  {
		lista->nodo_fin->siguiente = nodo_nuevo;
		lista->nodo_fin = nodo_nuevo;
	} else if (posicion == 0) {
		nodo_nuevo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo_nuevo;
	} else {
		for (int i = 1; i < posicion; i++)
			nodo_actual = nodo_actual->siguiente;

		nodo_nuevo->siguiente = (nodo_actual->siguiente);
		nodo_actual->siguiente = nodo_nuevo;
	}
	(lista->cantidad)++;
}


/*
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion) {
	if (!lista) 
		return ERROR;
	nodo_t* nodo_nuevo = calloc(1, sizeof(nodo_t));
	if (!nodo_nuevo) 
		return ERROR;

	nodo_nuevo->elemento = elemento;	

	if(lista_vacia(lista)) {
		insertar_nodo_en_lista_vacia(lista, nodo_nuevo);
		return EXITO;
	}

	insertar_nodo_en_posicion(lista, nodo_nuevo, posicion);

	return EXITO;
}



/*
* Pre: La lista debe ser "múltiple", es decir, debe tener más de un elemento, y 
	ser válida (no nula).
* Post: Borra el elemento en la posición recibida de la lista recibida, 
	y devuelve EXITO. En caso de que la lista tenga un elemento o ninguno,
	devuelve ERROR.
*/
int borrar_elemento_lista_multiple(lista_t* lista, size_t posicion) {
	nodo_t* nodo_actual = (lista->nodo_inicio);
	// Nodo actual debe ser el anterior al que quiero borrar
	for (int i = 0; i < (posicion-1); i++)
		nodo_actual = (nodo_actual->siguiente);

	nodo_t* nodo_a_borrar = NULL;	
	if (posicion == 0) {
		nodo_a_borrar = nodo_actual;
		lista->nodo_inicio = (nodo_actual->siguiente);
	} else {
		nodo_a_borrar = (nodo_actual->siguiente);
		nodo_actual->siguiente = (nodo_actual->siguiente->siguiente);
	}

	if (nodo_actual->siguiente == NULL) // El que quiero borrar es el nodo fin
		lista->nodo_fin = nodo_actual;
	if (lista->destructor)
		lista->destructor(nodo_a_borrar->elemento); // Agrego destructor
	free(nodo_a_borrar);
	(lista->cantidad)--;
	return EXITO;
}

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar(lista_t* lista) {
	if (!lista || lista_vacia(lista)) return ERROR;

	if (lista->cantidad == 1) {
		if (lista->destructor)
			lista->destructor(lista->nodo_inicio->elemento); // Agrego destructor
		free(lista->nodo_inicio);
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
		(lista->cantidad)--;
		return EXITO;
	}

	return borrar_elemento_lista_multiple(lista, (lista->cantidad)-1);
}

/*
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento.  
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.  
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar_de_posicion(lista_t* lista, size_t posicion) {
	if (!lista || lista_vacia(lista)) 
		return ERROR;
	if (posicion >= (lista->cantidad))
		posicion = ((lista->cantidad)-1);

	if (posicion == 0) {
		return lista_desencolar(lista);
	}

	return borrar_elemento_lista_multiple(lista, posicion);
}

/*
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t* lista) {
	if (!lista_vacia(lista)) {
		nodo_t* nodo_a_liberar = (lista->nodo_inicio);
		nodo_t* nodo_actual = (lista->nodo_inicio->siguiente);

		for(int i = 0; i < (lista->cantidad); i++) {
			if (lista->destructor)
				lista->destructor(nodo_a_liberar->elemento); // Agrego destructor
			free(nodo_a_liberar);
			nodo_a_liberar = nodo_actual;
			if (nodo_actual) // Si el nodo actual no es NULL
				nodo_actual = (nodo_actual->siguiente);
		}
	}
	free(lista);
}


/*
* Pre: La lista no debe ser nula. El nodo_actual debe ser el nodo_inicio de la lista.
* Post: Devuelve el elemento en la posición recibida, de manera recursiva. Si la posición es 
	mayor a la cantidad de elementos de la lista devuelve NULL.
*/
void* elemento_en_posicion_aux(lista_t* lista, size_t posicion, nodo_t* nodo_actual) {
	if ((posicion >= (lista->cantidad)))
		return NULL;
	if (posicion == 0)
		return (nodo_actual->elemento);
	return elemento_en_posicion_aux(lista, posicion-1, nodo_actual->siguiente);
}

/*
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion) {
	if(!lista) return NULL;
	return elemento_en_posicion_aux(lista, posicion, lista->nodo_inicio);
}

/* 
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
void* lista_ultimo(lista_t* lista) {
	if ((!lista) || lista_vacia(lista))
		return NULL;
	return (lista->nodo_fin->elemento);
}

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t* lista) {
	if (!lista)
		return 0;
	return (lista->cantidad);
}

/*
* Pre: La lista no debe ser nula ni debe estar vacía. El nodo recibido
	debe estar reservado en el HEAP y estar inicializado con el elemento
	a asignar.
* Post: Inserta el nodo recibido al final de la lista recibida.
*/
void insertar_nodo_al_final(lista_t* lista, nodo_t* nodo_nuevo) {
	lista->nodo_fin->siguiente = nodo_nuevo;
	lista->nodo_fin = nodo_nuevo;
	(lista->cantidad)++;
}

/* 
 * Apila un elemento.
 * Devuelve 0 si pudo o -1 en caso contrario.
 */
int lista_apilar(lista_t* lista, void* elemento) {

	if(!lista) return ERROR;

	nodo_t* nodo_nuevo = calloc(1, sizeof(nodo_t));
	if(!nodo_nuevo) return ERROR;

	nodo_nuevo->elemento = elemento;	

	if(lista_vacia(lista))
		insertar_nodo_en_lista_vacia(lista, nodo_nuevo);
	else
		insertar_nodo_al_final(lista, nodo_nuevo);

	return EXITO;
}

/* 
 * Desapila un elemento.
 * Devuelve 0 si pudo desapilar o -1 si no pudo.
 */
int lista_desapilar(lista_t* lista) {
	if (!lista || lista_vacia(lista)) return ERROR;

	if (lista->cantidad == 1) {
		if (lista->destructor)
			lista->destructor(lista->nodo_inicio->elemento); // Agrego destructor
		free(lista->nodo_inicio);
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
		(lista->cantidad)--;
		return EXITO;
	}

	return borrar_elemento_lista_multiple(lista, (lista->cantidad)-1);
}

/*
 * Devuelve el elemento en el tope de la pila o NULL
 * en caso de estar vacía.
*/
void* lista_tope(lista_t* lista) {
	if (!lista || lista_vacia(lista))
		return NULL;
	return (lista->nodo_fin->elemento);
}

/* 
 * Encola un elemento.
 * Devuelve 0 si pudo encolar o -1 si no pudo.
 */
int lista_encolar(lista_t* lista, void* elemento) {
	if(!lista) return ERROR;

	nodo_t* nodo_nuevo = calloc(1, sizeof(nodo_t));
	if(!nodo_nuevo) return ERROR;

	nodo_nuevo->elemento = elemento;	

	if(lista_vacia(lista))
		insertar_nodo_en_lista_vacia(lista, nodo_nuevo);
	else
		insertar_nodo_al_final(lista, nodo_nuevo);

	return EXITO;
}

/* 
 * Desencola un elemento.
 * Devuelve 0 si pudo desencolar o -1 si no pudo.
 */
int lista_desencolar(lista_t* lista) {
	if (!lista || lista_vacia(lista)) 
		return ERROR;

	nodo_t* nodo_inicio_nuevo = (lista->nodo_inicio->siguiente);
	if (lista->destructor)
		lista->destructor(lista->nodo_inicio->elemento); // Agrego destructor
	free(lista->nodo_inicio);
	lista->nodo_inicio = nodo_inicio_nuevo;
	(lista->cantidad)--;

	if (lista->cantidad == 0)
		lista->nodo_fin = NULL;

	return EXITO;
}


/*
 * Devuelve el primer elemento de la cola o NULL en caso de estar
 * vacía.
 */
void* lista_primero(lista_t* lista) {
	if (!lista || lista_vacia(lista)) 
		return NULL;
	return (lista->nodo_inicio->elemento);
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
lista_iterador_t* lista_iterador_crear(lista_t* lista) {
	if (!lista)			
		return NULL;

	lista_iterador_t* iterador = calloc(1, sizeof(lista_iterador_t));
	if (!iterador)
		return NULL;

	iterador->lista = lista;
	iterador->corriente = (lista->nodo_inicio);
	return iterador;
}

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador) {
	if (!iterador) 
		return false;
	return !!(iterador->corriente);
}

/*
 * Avanza el iterador al siguiente elemento.
 * Devuelve true si pudo avanzar el iterador o false en caso de
 * que no queden elementos o en caso de error.
 *
 * Una vez llegado al último elemento, si se invoca a
 * lista_iterador_elemento_actual, el resultado siempre será NULL.
 */
bool lista_iterador_avanzar(lista_iterador_t* iterador) {
	if (!iterador || !(iterador->corriente)) 
		return false;

	iterador->corriente = (iterador->corriente->siguiente);
	if (!(iterador->corriente)) 
		return false;
	return true;
}

/*
 * Devuelve el elemento actual del iterador o NULL en caso de que no
 * exista dicho elemento o en caso de error.
 */
void* lista_iterador_elemento_actual(lista_iterador_t* iterador) {
	if (!iterador || !(iterador->corriente))
		return NULL;
	return (iterador->corriente->elemento);
}

/*
 * Libera la memoria reservada por el iterador.
 */
void lista_iterador_destruir(lista_iterador_t* iterador) {
	free(iterador);
}

/*
 * Iterador interno. Recorre la lista e invoca la funcion con cada elemento de
 * la misma. Dicha función puede devolver true si se deben seguir recorriendo
 * elementos o false si se debe dejar de iterar elementos.
 *
 * La función retorna la cantidad de elementos iterados o 0 en caso de error.
 */
size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto) {
	if (!lista || lista_vacia(lista) || !funcion)
		return FALLO_ITERADOR;

	size_t i = 0;
	nodo_t* nodo_actual = (lista->nodo_inicio);
	bool sigo_recorriendo = true;
	
	do {
		sigo_recorriendo = funcion(nodo_actual->elemento, contexto);
		nodo_actual = (nodo_actual->siguiente);
		if (sigo_recorriendo) i++;
	} while ((i < (lista->cantidad)) && sigo_recorriendo);

	return i;
}