#ifndef __ABB_ITERADOR_H__
#define __ABB_ITERADOR_H__

#include "abb.h"

/*
 * Iterador interno. Recorre el arbol e invoca la funcion con cada
 * elemento del mismo. El puntero 'extra' se pasa como segundo
 * parámetro a la función. Si la función devuelve false, se finaliza el
 * recorrido aun si quedan elementos por recorrer. Si devuelve true
 * se sigue recorriendo mientras queden elementos.
 * El recorrido se realiza de acuerdo al recorrido solicitado.  Los
 * recorridos válidos son: ABB_RECORRER_INORDEN, ABB_RECORRER_PREORDEN
 * y ABB_RECORRER_POSTORDEN.
*/
void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra);

#endif /*__ABB_ITERADOR_H__*/