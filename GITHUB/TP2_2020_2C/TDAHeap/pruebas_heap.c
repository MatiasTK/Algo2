#include "pa2m.h"
#include "heap.h"
#define MAX_ELEMENTOS_PRUEBA 4
#define MAX_PRUEBAS_EXHAUSTIVAS 30000
#define MAYOR 1
#define MENOR -1
#define IGUAL 0

/*
* Pre:
* Post:
*/
int comparador_enteros(void* num1, void* num2) {
    if (!num1 && !num2) return IGUAL;
    if (!num1) return MENOR;
    if (!num2) return MAYOR;

    if ((*((int*)num1)) > (*((int*)num2)))
        return MAYOR;
    if ((*((int*)num1)) < (*((int*)num2)))
        return MENOR;
    return IGUAL;
}

void destructor_enteros(void* elemento) {
    printf("El destructor funciona\n");
}

void pruebas_creacion_heap() {
    heap_t* heap = heap_crear(comparador_enteros, NULL);
    if (!heap) return;
    pa2m_afirmar(heap != NULL, "Un heap creado no es nulo.");
    pa2m_afirmar(heap->destructor == NULL, "Puedo crear un heap sin destructor.");
    pa2m_afirmar(heap->vector == NULL, "Un heap se crea con un vector nulo.");
    pa2m_afirmar(heap_vacio(heap), "Un heap se crea sin elementos.");

    heap_destruir(heap);

    heap = heap_crear(NULL, NULL);
    pa2m_afirmar(!heap, "No puedo crear un heap sin comparador.");

    heap = heap_crear(comparador_enteros, destructor_enteros);
    if (!heap) return;
    pa2m_afirmar(heap != NULL, "Puedo crear un heap con destructor.");
    pa2m_afirmar(heap->destructor == destructor_enteros, "El destructor se asigna correctamente.");
    heap_destruir(heap);
}


void pruebas_ordenadas_heap() {
    heap_t* heap = heap_crear(comparador_enteros, destructor_enteros);
    if (!heap) return;

    int elementos_ordenados[MAX_ELEMENTOS_PRUEBA] = {7, 8, 9, 10};
    //heap_comparador comparador = comparador_enteros;

    for (int i = 0; i < 2; i++)
        pa2m_afirmar(heap_insertar(heap, elementos_ordenados+i) == EXITO, 
        "Se inserta correctamente un elemento en el heap.");
    
    for (int j = 0; j < 2; j++) {
        void* extraido = heap_extraer_raiz(heap);
        pa2m_afirmar((int*)extraido == elementos_ordenados+j, "La raíz extraída es la correcta");
    }

    pa2m_afirmar(heap_vacio(heap), "El heap queda vacío luego de extraer todos sus elementos.");

    heap_destruir(heap); //////////////////////////////////////////////////
}

void pruebas_desordenadas_heap() {
    heap_t* heap = heap_crear(comparador_enteros, NULL);
    if (!heap) return;

    int elementos_desordenados[MAX_ELEMENTOS_PRUEBA] = {15, 11, 23, 20};
    int extracciones[MAX_ELEMENTOS_PRUEBA] = {11, 15, 20, 23};
    //heap_comparador comparador = comparador_enteros;

    for (int i = 0; i < MAX_ELEMENTOS_PRUEBA; i++) {
        pa2m_afirmar(heap_insertar(heap, elementos_desordenados+i) == EXITO, 
            "Se inserta correctamente un elemento en el heap.");
    }

    for (int j = 0; j < MAX_ELEMENTOS_PRUEBA; j++) {
        int extraido = (*(int*)heap_extraer_raiz(heap));
        pa2m_afirmar(extraido == extracciones[j], "La raíz extraída es la correcta");
    }

    pa2m_afirmar(heap_vacio(heap), "El heap queda vacío luego de extraer todos sus elementos.");


    heap_destruir(heap); //////////////////////////////////////////////////
}

void pruebas_exhaustivas_heap() {
    heap_t* heap = heap_crear(comparador_enteros, NULL);
    if (!heap) return;

    int elementos_ordenados[MAX_PRUEBAS_EXHAUSTIVAS];
    // heap_comparador comparador = comparador_enteros;

    for (int i = 0; i < MAX_PRUEBAS_EXHAUSTIVAS; i++) {
        elementos_ordenados[i] = i;
    }

    int resultado_operacion = EXITO;
    for (int j = MAX_PRUEBAS_EXHAUSTIVAS-1; j >= 0; j--) {
        if (heap_insertar(heap, elementos_ordenados+j) == ERROR)
            resultado_operacion = ERROR;
    }
    pa2m_afirmar(resultado_operacion == EXITO, 
        "Se insertan correctamente 30000 elementos en el heap.");


    resultado_operacion = EXITO;
    for (int k = 0; k < (MAX_PRUEBAS_EXHAUSTIVAS/2); k++) {
        int extraido = (*(int*)heap_extraer_raiz(heap));
        if (extraido != elementos_ordenados[k])
            resultado_operacion = ERROR;
    }
    pa2m_afirmar(resultado_operacion == EXITO, "Se extraen correctamente 15000 elementos.");

    heap_destruir(heap);
}



int main() {

    printf("\n\nP R U E B A S   T D A   H E A P\n");

    pa2m_nuevo_grupo("PRUEBAS CREACIÓN");
    pruebas_creacion_heap();

    pa2m_nuevo_grupo("PRUEBAS CON ELEMENTOS EN ORDEN");
    pruebas_ordenadas_heap();
    
    pa2m_nuevo_grupo("PRUEBAS CON ELEMENTOS DESORDENADOS");
    pruebas_desordenadas_heap();

    pa2m_nuevo_grupo("PRUEBAS EXHAUSTIVAS");
    pruebas_exhaustivas_heap();

    pa2m_mostrar_reporte();

    return 0;
}