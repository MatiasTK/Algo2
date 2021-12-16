#include "lista.h"
#include <stdio.h>
#include "pa2m.h"

#define ERROR -1
#define EXITO 0
#define MAX_ELEMENTOS_PRUEBA 10
#define MAX_CARACTERES_PRUEBA 5

#define MAX_ELEMENTOS_SOBRECARGA 30000
#define BORRADOS_PRIMERA_PASADA 5000
#define BORRADOS_SEGUNDA_PASADA 10000
#define BORRADOS_TERCERA_PASADA 15000

lista_t* generar_lista() {
    lista_t* lista = lista_crear();
    if (!lista) {
        printf(ROJO "No se pudo crear la lista. No se realizan las pruebas.\n" BLANCO);
        return NULL;
    }
    return lista;
}

/*
* Pre: -
* Post: Crea un iterador para la lista recibida y lo devuelve. Si no lo puede crear, 
    imprime por pantalla el error y devuelve NULL.
*/
lista_iterador_t* generar_iterador(lista_t* lista) {
    if(!lista) {
        printf("No se pudo crear el iterador debido a que la lista es nula. No se realizan las pruebas.\n");
        return NULL;
    }
    lista_iterador_t* iterador = lista_iterador_crear(lista);
    if (!iterador) {
        printf(ROJO "No se pudo crear el iterador. No se realizan las pruebas.\n" BLANCO);
        return NULL;
    }
    return iterador;
}


void probar_creacion_lista() {
    lista_t* lista = lista_crear();

    pa2m_afirmar(lista != NULL, "Puedo crear una lista");
    pa2m_afirmar(lista->nodo_inicio == NULL, "La lista se crea con un nodo inicio nulo");
    pa2m_afirmar(lista->nodo_fin == NULL, "La lista se crea con un nodo fin nulo");
    pa2m_afirmar(lista->cantidad == 0, "La lista se crea vacía");

    lista_destruir(lista); 

}

void probar_insercion_en_lista(lista_t* lista) {

    lista_t* lista_sin_elementos = generar_lista();
    if (!lista_sin_elementos) return;
    int num1 = 5;
    int num2 = 9;
    int num3 = 7;
    int num4 = 20;
    int num0 = 10;
    size_t cant_actual = lista->cantidad;

    pa2m_afirmar((lista_insertar(lista, &num1) == EXITO) && (lista->nodo_inicio->elemento == &num1) && 
        (lista->nodo_inicio->siguiente == NULL) && (lista->nodo_fin->elemento == &num1) && 
        (lista->cantidad == cant_actual+1), "Puedo insertar un elemento al final de una lista vacía");
    cant_actual++;

    pa2m_afirmar((lista_insertar(lista, &num2) == EXITO) && (lista->nodo_inicio->siguiente->elemento == &num2) && 
        (lista->nodo_inicio->elemento == &num1) && (lista->nodo_fin->elemento == &num2) && (lista->cantidad == cant_actual+1), 
        "Puedo insertar un segundo elemento al final de una lista");

    pa2m_afirmar(lista_insertar(lista, NULL) == EXITO, "Puedo insertar un elemento nulo al final");
    pa2m_afirmar(lista_insertar(NULL, &num1) == ERROR, "No puedo insertar un elemento al final de una lista nula");


    pa2m_afirmar((lista_insertar_en_posicion(lista, &num3, 1) == EXITO) && (lista->nodo_inicio->siguiente->elemento == (&num3) && 
        (lista->nodo_inicio->siguiente->siguiente->elemento == (&num2))), "Puedo insertar un elemento en medio de dos elementos de la lista");
    pa2m_afirmar((lista_insertar_en_posicion(lista, &num0, 0) == EXITO) && (lista->nodo_inicio->elemento == (&num0)), "Puedo insertar un elemento al inicio de la lista");
    pa2m_afirmar((lista_insertar_en_posicion(lista, &num4, 200) == EXITO) && (lista->nodo_fin->elemento == (&num4)), "Al pasar una posición inexistente, inserta al final");
    pa2m_afirmar(lista_insertar_en_posicion(lista_sin_elementos, &num1, 4) == EXITO, "Puedo insertar un elemento en alguna posición de una lista vacía");
    pa2m_afirmar(lista_insertar_en_posicion(NULL, &num1, 3) == ERROR, "No puedo insertar un elemento en alguna posición de una lista nula");


    lista_destruir(lista_sin_elementos);
}

void probar_lista_vacia(lista_t* lista) {

    lista_t* lista_sin_elementos = generar_lista();
    if (!lista_sin_elementos) return;

    pa2m_afirmar(lista_vacia(lista_sin_elementos), "Una lista vacía está efectivamente vacía");
    pa2m_afirmar(!lista_vacia(lista), "Una lista no vacía efectivamente no está vacía");

    lista_destruir(lista_sin_elementos);

}

void probar_borrar_ultimo_elemento_lista(lista_t* lista) {

    lista_t* lista_sin_elementos = generar_lista();
    if (!lista_sin_elementos) return;
    size_t cant_inicial = (lista->cantidad);
    nodo_t* nodo_fin_inicial = (lista->nodo_fin);

    pa2m_afirmar(lista_borrar(lista_sin_elementos) == ERROR, "No puedo borrar el último elemento de una lista vacía");

    pa2m_afirmar((lista_borrar(lista) == EXITO) && (lista->nodo_fin != nodo_fin_inicial) && (lista->nodo_fin->siguiente == NULL) &&
        (lista->cantidad == cant_inicial-1), "Puedo borrar el último elemento de una lista");
    pa2m_afirmar(lista_borrar(NULL) == ERROR, "No puedo borrar de una lista nula");

    int num = 32;
    lista_insertar(lista_sin_elementos, &num);
    pa2m_afirmar(lista_borrar(lista_sin_elementos) == EXITO && (lista_sin_elementos->nodo_inicio == NULL) && (lista_sin_elementos->nodo_fin == NULL) && 
        (lista_sin_elementos->cantidad == 0), "Puedo borrar de una lista con un solo elemento y queda vacía");


    lista_destruir(lista_sin_elementos); 

}

/*
* Pre: elemento es un puntero al elemento que quiero insertar. Al pasarle n, 
    es decir, el número de elementos a insertar, debo asegurar que elemento es un
    vector de enteros que puedo recorrer n veces utilizando aritmética de punteros.
* Post: Inserta n elementos recibidos en la lista recibida. Si se recibe una lista 
    nula, no hace nada.
*/
void insertar_enteros(lista_t* lista, int* elemento, size_t n) {
    if (!lista) return;
    if (n > MAX_ELEMENTOS_PRUEBA) n = MAX_ELEMENTOS_PRUEBA;
    if (n == 0 || lista_insertar(lista, elemento) == ERROR) 
        return;
    insertar_enteros(lista, (elemento+1), n-1);
}


void probar_borrar_posicion_especifica_lista() {
    lista_t* lista = generar_lista();
    if (!lista) return;
    lista_t* lista_sin_elementos = generar_lista();
    if (!lista_sin_elementos) return;
    int elementos[MAX_ELEMENTOS_PRUEBA] = {3, 5, 6, 7, 5, 10, 8, 20, 21, 22};

    insertar_enteros(lista, elementos, 4);
    size_t cant_elementos = (lista->cantidad);
    nodo_t* nodo_inicio_inicial = (lista->nodo_inicio);

    pa2m_afirmar(lista_borrar_de_posicion(lista_sin_elementos, 0) == ERROR, "No puedo borrar el primer elemento de una lista vacía");
    pa2m_afirmar(lista_borrar_de_posicion(lista_sin_elementos, 1) == ERROR, "No puedo borrar el segundo elemento de una lista vacía");

    pa2m_afirmar((lista_borrar_de_posicion(lista, 0) == EXITO) && (lista->nodo_inicio != nodo_inicio_inicial) && 
        (lista->cantidad == (cant_elementos-1)), "Puedo borrar el primer elemento de una lista");
    cant_elementos--;
    nodo_t* nodo_aux = (lista->nodo_inicio->siguiente);
    pa2m_afirmar((lista_borrar_de_posicion(lista, 1) == EXITO) && (lista->nodo_inicio->siguiente != nodo_aux) && 
        (lista->cantidad == (cant_elementos-1)), "Puedo borrar el segundo elemento de una lista");
    cant_elementos--;
    pa2m_afirmar((lista_borrar_de_posicion(lista, 1) == EXITO) && (lista->nodo_fin == lista->nodo_inicio) && 
        (lista->cantidad == (cant_elementos-1)), "Puedo borrar el último elemento de una lista");
    cant_elementos--;

    pa2m_afirmar((lista_borrar_de_posicion(NULL, 3) == ERROR) && (lista->cantidad == cant_elementos), "No puedo borrar un elemento de una lista nula");

    lista_destruir(lista_sin_elementos);
    lista_destruir(lista);
}

void probar_elemento_en_posicion() {
    lista_t* lista = generar_lista();
    if (!lista) return;
    lista_t* lista_sin_elementos = generar_lista();
    if (!lista_sin_elementos) return;

    int elementos[MAX_ELEMENTOS_PRUEBA] = {3, 5, 6, 7, 5, 10, 8, 20, 21, 22};
    insertar_enteros(lista, elementos, MAX_ELEMENTOS_PRUEBA);

    pa2m_afirmar((lista_elemento_en_posicion(lista_sin_elementos, 0) == NULL), "El primer elemento de una lista vacía es nulo");
    pa2m_afirmar((lista_elemento_en_posicion(lista_sin_elementos, 4) == NULL), "El quinto elemento de una lista vacía es nulo");

    pa2m_afirmar((lista_elemento_en_posicion(lista, 0) == elementos), "El primer elemento es el indicado");
    pa2m_afirmar((lista_elemento_en_posicion(lista, 1) == (elementos+1)), "El segundo elemento es el indicado");
    pa2m_afirmar((lista_elemento_en_posicion(lista, 4) == (elementos+4)), "El quinto elemento es el indicado");
    pa2m_afirmar((lista_elemento_en_posicion(lista, 9) == (elementos+9)), "El último elemento es el indicado");

    pa2m_afirmar(lista_elemento_en_posicion(NULL, 0) == NULL, "No puedo acceder a elementos de una lista nula");

    lista_destruir(lista_sin_elementos);
    lista_destruir(lista);
}

void probar_lista_ultimo() {
    lista_t* lista = generar_lista();
    if (!lista) return;
    int elementos[MAX_ELEMENTOS_PRUEBA] = {3, 5, 6, 7, 5, 10, 8, 20, 21, 22};

    pa2m_afirmar(lista_ultimo(lista) == NULL, "El último elemento de una lista vacía es nulo");

    insertar_enteros(lista, elementos, 1);
    pa2m_afirmar(lista_ultimo(lista) == elementos, "El último elemento de una lista con un solo elemento se obtiene correctamente");

    insertar_enteros(lista, elementos+1, 3);
    pa2m_afirmar(lista_ultimo(lista) == (elementos+3), "El último elemento de una lista se obtiene correctamente");

    pa2m_afirmar(lista_ultimo(NULL) == NULL, "El último elemento de una lista nula es nulo");

    lista_destruir(lista);
}

void probar_lista_elementos() {
    lista_t* lista = generar_lista();
    if (!lista) return;
    int elementos[MAX_ELEMENTOS_PRUEBA] = {3, 5, 6, 7, 5, 10, 8, 20, 21, 22};


    pa2m_afirmar(lista_elementos(lista) == 0, "Una lista vacía tiene cero elementos");

    insertar_enteros(lista, elementos, 1);
    pa2m_afirmar(lista_elementos(lista) == 1, "Una lista tiene un elemento");

    insertar_enteros(lista, elementos+1, 2);
    pa2m_afirmar(lista_elementos(lista) == 3, "Una lista tiene tres elementos");

    pa2m_afirmar(lista_elementos(NULL) == 0, "Una lista nula tiene cero elementos");

    lista_destruir(lista);
}

void probar_pila() {
    lista_t* pila = generar_lista();
    if (!pila) return;

    char elementos[MAX_CARACTERES_PRUEBA] = {'M','a','t','e','o'};
    size_t cant_apilados = 0;
    size_t i = 0;

    while(i < MAX_CARACTERES_PRUEBA) {
        if (lista_apilar(pila, elementos+i) == EXITO)
            cant_apilados++;
        i++;
    }
    pa2m_afirmar((cant_apilados == i) && (pila->cantidad == cant_apilados), "Puedo apilar varios elementos"); 

    for(int j = 1; j <= MAX_CARACTERES_PRUEBA; j++) {
        pa2m_afirmar(lista_tope(pila) == (elementos+MAX_CARACTERES_PRUEBA-j), "El elemento en el tope de la pila es el correcto");
        pa2m_afirmar((lista_desapilar(pila) == EXITO) && (pila->cantidad == (MAX_CARACTERES_PRUEBA-j)), "Puedo desapilar un elemento de la pila correctamente");
    }

    pa2m_afirmar(lista_vacia(pila), "La pila queda vacía al desapilar el último elemento");
    pa2m_afirmar(lista_desapilar(pila) == ERROR, "No puedo desapilar de una pila vacía");
    pa2m_afirmar(!(lista_tope(pila)), "El elemento tope de una pila vacía es nulo");

    pa2m_afirmar(lista_apilar(NULL, elementos) == ERROR, "No puedo apilar en una pila nula");
    pa2m_afirmar(lista_desapilar(NULL) == ERROR, "No puedo desapilar de una pila nula");
    pa2m_afirmar(!(lista_tope(NULL)), "El elemento tope de una pila nula es nulo");
    

    lista_destruir(pila);
}

void probar_cola() {
    lista_t* cola = generar_lista();
    if (!cola) return;
    int elementos[MAX_ELEMENTOS_PRUEBA] = {3, 5, 6, 7, 5, 10, 8, 20, 21, 22};
    size_t cant_encolados = 0;
    size_t i = 0;

    while(i < (MAX_ELEMENTOS_PRUEBA/2)) {
        if (lista_encolar(cola, elementos+i) == EXITO)
            cant_encolados++;
        i++;
    }
                                                                                                                    
    pa2m_afirmar((cant_encolados == i) && (cola->cantidad == cant_encolados), "Puedo encolar varios elementos");
    
    for(int j = 0; j < (MAX_ELEMENTOS_PRUEBA/2); j++) {
        pa2m_afirmar(lista_primero(cola) == elementos+j, "El primer elemento se obtiene correctamente");
        pa2m_afirmar((lista_desencolar(cola) == EXITO) && (cola->cantidad == (MAX_ELEMENTOS_PRUEBA/2)-j-1), "Puedo desencolar correctamente un elemento");

    }
    pa2m_afirmar(lista_vacia(cola), "La cola queda vacía luego de desencolar el último elemento");
    pa2m_afirmar((lista_desencolar(cola) == ERROR) && (lista_vacia(cola)),  "No puedo desencolar de una cola vacía");
    pa2m_afirmar(lista_primero(cola) == NULL, "El primer elemento de una cola vacía es nulo");


    pa2m_afirmar(lista_encolar(NULL, elementos) == ERROR, "No puedo encolar en una cola nula");
    pa2m_afirmar(lista_desencolar(NULL) == ERROR, "No puedo desencolar de una cola nula");
    pa2m_afirmar(lista_primero(NULL) == NULL, "El primer elemento de una cola nula es nulo");


    lista_destruir(cola);
}

void probar_creacion_iterador_externo() {
    lista_t* lista = generar_lista();
    if (!lista) return;
    lista_iterador_t* iterador = lista_iterador_crear(lista);
    int elementos[MAX_ELEMENTOS_PRUEBA] = {3, 5, 6, 7, 5, 10, 8, 20, 21, 22};

    pa2m_afirmar((iterador) && (iterador->lista == lista) && (iterador->corriente == NULL), 
        "Un iterador se crea exitosamente para una lista vacía");
    lista_iterador_destruir(iterador);

    insertar_enteros(lista, elementos, 1);
    iterador = lista_iterador_crear(lista);
    pa2m_afirmar((iterador) && (iterador->lista == lista) && (iterador->corriente == lista->nodo_inicio), 
        "Un iterador se crea exitosamente para una lista con un elemento");
    lista_iterador_destruir(iterador);

    insertar_enteros(lista, elementos, 2);
    iterador = lista_iterador_crear(lista);
    pa2m_afirmar((iterador) && (iterador->lista == lista) && (iterador->corriente == lista->nodo_inicio), 
        "Un iterador se crea exitosamente para una lista con tres elementos");
    lista_iterador_destruir(iterador);

    iterador = lista_iterador_crear(NULL);
    pa2m_afirmar((iterador == NULL), "No se puede crear un iterador para una lista nula");
    if (iterador) lista_iterador_destruir(iterador);

    lista_destruir(lista);
}


void probar_iterador_externo() {
    lista_t* lista = generar_lista();
    if (!lista) return;
    int elementos[MAX_ELEMENTOS_PRUEBA] = {3, 5, 6, 7, 5, 10, 8, 20, 21, 22};

    // PRUEBAS LISTA VACÍA
    lista_iterador_t* iterador = generar_iterador(lista);
    if (!iterador) return;  

    pa2m_afirmar(!(lista_iterador_avanzar(iterador)) && !(iterador->corriente), "No puedo avanzar un iterador en una lista vacía");
    pa2m_afirmar(!(lista_iterador_tiene_siguiente(iterador)), "Un iterador de una lista vacía no tiene elemento siguiente");
    pa2m_afirmar(!(lista_iterador_elemento_actual(iterador)), "No hay elementos en una lista vacía");
    lista_iterador_destruir(iterador);

    // PRUEBAS LISTA CON UN ELEMENTO
    insertar_enteros(lista, elementos, 1);
    iterador = generar_iterador(lista);
    if (!iterador) return;

    pa2m_afirmar(lista_iterador_elemento_actual(iterador) == elementos, "En una lista con un elemento, el elemento actual es ese único elemento");
    pa2m_afirmar((lista_iterador_tiene_siguiente(iterador)) && !(lista_iterador_avanzar(iterador)) && 
        !(lista_iterador_elemento_actual(iterador)), "Al intentar avanzar el iterador en una lista con un solo elemento, devuelve false y el elemento actual es NULL");
    lista_iterador_destruir(iterador);

    // PRUEBAS LISTA CON 10 ELEMENTOS
    insertar_enteros(lista, elementos+1, MAX_ELEMENTOS_PRUEBA-1);
    iterador = generar_iterador(lista);
    if (!iterador) return;  

    int i = 0;
    while(i < (MAX_ELEMENTOS_PRUEBA-1)) {
        pa2m_afirmar(lista_iterador_elemento_actual(iterador) == elementos+i, "El elemento actual es el correcto");
        pa2m_afirmar((lista_iterador_tiene_siguiente(iterador)) && (lista_iterador_avanzar(iterador) && 
            (iterador->corriente)), "Hay un siguiente elemento para iterar, entonces avanzo el iterador");
        i++;
    }
    pa2m_afirmar(lista_iterador_elemento_actual(iterador) == elementos+i, "El elemento actual es el último elemento");
    pa2m_afirmar((lista_iterador_tiene_siguiente(iterador)) && !(lista_iterador_avanzar(iterador)) && 
        !(lista_iterador_elemento_actual(iterador)), "Al intentar avanzar el iterador, devuelve false y el elemento actual es NULL");
    i++;

    pa2m_afirmar((lista->cantidad == i), "La cantidad de elementos iterados coincide con la cantidad de elementos en la lista");
    lista_iterador_destruir(iterador);

    // PRUEBAS ITERADOR NULO
    pa2m_afirmar(!(lista_iterador_elemento_actual(NULL)), "El elemento actual de un iterador nulo es nulo");
    pa2m_afirmar(!(lista_iterador_tiene_siguiente(NULL)), "Un iterador nulo no tiene siguiente");
    pa2m_afirmar(!(lista_iterador_avanzar(NULL)), "No puedo avanzar un iterador nulo");

    lista_destruir(lista);
}



/*
* Pre: El elemento recibido debe ser un entero. El contador debe ser un entero válido.
* Post: Suma uno al contador si el elemento recibido es par, y siempre devuelve true.
*/
bool contar_entero_par_actual(void* elemento, void* contador) {
    if ((((*(int*)elemento) % 2) == 0)){
        (*(int*)contador)++;
    }
    return true;
}

/*
* Pre: -
* Post: Función que siempre devuelve false para probar el iterador.
*/
bool funcion_falsa(void* elemento, void* contador) {
        return false;
}


void probar_iterador_interno() {
    lista_t* lista = generar_lista();
    if (!lista)
        return;

    int elementos[MAX_ELEMENTOS_PRUEBA] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int contador_pares = 0;
    size_t elementos_recorridos = 0;

    elementos_recorridos = lista_con_cada_elemento(lista, contar_entero_par_actual, (void*)&contador_pares);
    pa2m_afirmar(!(elementos_recorridos), "No puedo iterar una lista vacía");

    insertar_enteros(lista, elementos, 1);
    elementos_recorridos = lista_con_cada_elemento(lista, contar_entero_par_actual, (void*)&contador_pares);
    pa2m_afirmar((elementos_recorridos == 1) && !(contador_pares), "Itero una vez por una lista con un solo elemento impar");

    contador_pares = 0;
    insertar_enteros(lista, elementos+1, 1);
    elementos_recorridos = lista_con_cada_elemento(lista, contar_entero_par_actual, (void*)&contador_pares);
    pa2m_afirmar((elementos_recorridos == 2) && (contador_pares == 1), "Itero dos veces por una lista con dos elementos, uno es par");

    contador_pares = 0;
    insertar_enteros(lista, elementos+2, 8);
    elementos_recorridos = lista_con_cada_elemento(lista, contar_entero_par_actual, (void*)&contador_pares);
    pa2m_afirmar((elementos_recorridos == MAX_ELEMENTOS_PRUEBA) && (contador_pares == (MAX_ELEMENTOS_PRUEBA/2)), 
        "Itero diez veces por una lista con diez elementos, cinco de ellos son pares");

    contador_pares = 0;
    elementos_recorridos = lista_con_cada_elemento(lista, funcion_falsa, (void*)&contador_pares);
    pa2m_afirmar(!(elementos_recorridos) && !(contador_pares), "No puedo iterar si la función no lo permite");

    contador_pares = 0;
    elementos_recorridos = lista_con_cada_elemento(lista, NULL, (void*)&contador_pares);
    pa2m_afirmar(!(elementos_recorridos) && !(contador_pares), "No puedo iterar si la función es nula");


    lista_destruir(lista);
}

void probar_sobrecarga_lista() {
    lista_t* lista = generar_lista();
    if (!lista) return;

    int elementos[MAX_ELEMENTOS_SOBRECARGA];
    int cant_insertados = 0;

    for (int i = 0; i < MAX_ELEMENTOS_SOBRECARGA; i++) {
        elementos[i] = i;
        if (lista_insertar(lista, elementos+i) == EXITO)
            cant_insertados++;
    }
    pa2m_afirmar((cant_insertados == MAX_ELEMENTOS_SOBRECARGA) && (lista_elementos(lista) == MAX_ELEMENTOS_SOBRECARGA), 
        "Puedo insertar correctamente 30k elementos en una lista");

    int cant_borrados = 0;
    for (int j = 0; j < BORRADOS_PRIMERA_PASADA; j++) {
        if (lista_borrar_de_posicion(lista, (size_t)j) == EXITO)
            cant_borrados++;
    }
    pa2m_afirmar((cant_borrados == BORRADOS_PRIMERA_PASADA) && (lista_elementos(lista) == (MAX_ELEMENTOS_SOBRECARGA - BORRADOS_PRIMERA_PASADA)), 
        "Puedo borrar 5k elementos de posiciones arbitrarias");

    for (int k = 0; k < BORRADOS_SEGUNDA_PASADA; k++) {
        if (lista_borrar_de_posicion(lista, (size_t)k) == EXITO)
            cant_borrados++;
    }
    pa2m_afirmar((cant_borrados == (BORRADOS_PRIMERA_PASADA + BORRADOS_SEGUNDA_PASADA)) && 
        (lista_elementos(lista) == (MAX_ELEMENTOS_SOBRECARGA - BORRADOS_PRIMERA_PASADA - BORRADOS_SEGUNDA_PASADA)), 
        "Puedo borrar 10k elementos del principio de la lista");


    for (int l = 0; l < BORRADOS_TERCERA_PASADA; l++) {
        if (lista_borrar(lista) == EXITO)
            cant_borrados++;
    }
    pa2m_afirmar((cant_borrados == (MAX_ELEMENTOS_SOBRECARGA)) && (lista_vacia(lista)), 
        "Puedo borrar 10k elementos del final de la lista y queda vacía");

    lista_destruir(lista);
}



void probar_lista() {
    lista_t* lista = lista_crear();
    pa2m_nuevo_grupo("PRUEBAS CREACIÓN LISTA");
    probar_creacion_lista();

    pa2m_nuevo_grupo("PRUEBAS INSERCIÓN EN LISTA");
    probar_insercion_en_lista(lista);

    pa2m_nuevo_grupo("PRUEBAS LISTA VACÍA");
    probar_lista_vacia(lista);

    pa2m_nuevo_grupo("PRUEBAS BORRAR ÚLTIMA POSICIÓN DE LISTA");
    probar_borrar_ultimo_elemento_lista(lista);

    pa2m_nuevo_grupo("PRUEBAS BORRAR EN POSICIÓN ESPECÍFICA DE LISTA");
    probar_borrar_posicion_especifica_lista();

    pa2m_nuevo_grupo("PRUEBAS ELEMENTO EN POSICIÓN");
    probar_elemento_en_posicion();

    pa2m_nuevo_grupo("PRUEBAS ÚLTIMO ELEMENTO DE LA LISTA");
    probar_lista_ultimo();

    pa2m_nuevo_grupo("PRUEBAS CANTIDAD ELEMENTOS LISTA");
    probar_lista_elementos();

    lista_destruir(lista);

}

void probar_iterador() {
    pa2m_nuevo_grupo("PRUEBAS CREACIÓN ITERADOR EXTERNO");
    probar_creacion_iterador_externo();

    pa2m_nuevo_grupo("PRUEBAS FUNCIONALIDAD ITERADOR EXTERNO");
    probar_iterador_externo();

    pa2m_nuevo_grupo("PRUEBAS ITERADOR INTERNO");
    probar_iterador_interno();
}

int main(){

    probar_lista();

    pa2m_nuevo_grupo("PRUEBAS PILA");
    probar_pila();

    pa2m_nuevo_grupo("PRUEBAS COLA");
    probar_cola();

    probar_iterador();

    pa2m_nuevo_grupo("PRUEBAS EXHAUSTIVAS");
    probar_sobrecarga_lista();


    pa2m_mostrar_reporte();
    printf("Se deberían haber corrido 117 pruebas\n");

    return 0;
}
