#include "pa2mm.h"
#include "src/heap.h"
#include <stdio.h>

#define EXITO 0
#define ERROR -1

typedef struct pokemones{
    int nivel;
    char* nombre;
} pokemones_t;

int comparador_numeros(void* n1,void* n2) {
    int a = *(int*)n1;
    int b = *(int*)n2;

    if (a < b)
        return -1;
    else if (a > b)
        return 1;
    else
        return 0;
}

void probar_destructor(void* elemento){
    printf("Se invoco al destructor\n");
}

int comparador_niveles(void* n1,void* n2) {
    pokemones_t* a = (pokemones_t*)n1;
    pokemones_t* b = (pokemones_t*)n2;

    if (a->nivel < b->nivel)
        return -1;
    else if (a->nivel > b->nivel)
        return 1;
    else
        return 0;
}

// -----------------------------------------------------------------------------

void SePuedeCrearHeap(){
    heap_t* heap = heap_crear(comparador_numeros, NULL);

    pa2m_afirmar(heap != NULL, "Se puede crear un heap exitosamente");
    pa2m_afirmar(heap->destructor == NULL, "El destructor del heap es NULL");
    pa2m_afirmar(heap->array == NULL, "El array del heap es NULL");
    pa2m_afirmar(heap_cantidad(heap)==0, "La cantidad del heap es 0");
    pa2m_afirmar(heap_esta_vacio(heap), "El heap esta vacio");

    heap_destruir(heap);
}

void SePuedenInsertarElementosEnElHeap(){
    heap_t* heap = heap_crear(comparador_numeros, probar_destructor);

    int n1 = 5;
    int n2 = 250;
    int n3 = 153;

    pa2m_afirmar(heap != NULL, "Se puede crear un heap exitosamente");
    pa2m_afirmar(heap_insertar(heap, &n1) == EXITO, "Se puede insertar un elemento en el heap");
    pa2m_afirmar(heap_insertar(heap, &n2) == EXITO, "Se puede insertar un elemento en el heap");
    pa2m_afirmar(heap_insertar(heap, &n3) == EXITO, "Se puede insertar un elemento en el heap");

    pa2m_afirmar(heap_cantidad(heap)==3, "La cantidad del heap es 3");
    pa2m_afirmar(!heap_esta_vacio(heap), "El heap no esta vacio");

    heap_destruir(heap);
}

void SePuedeExtraerLaRaiz(){
    heap_t* heap = heap_crear(comparador_numeros, probar_destructor);

    int n1 = 5;
    int n2 = 250;
    int n3 = 153;

    pa2m_afirmar(heap != NULL, "Se puede crear un heap exitosamente");
    heap_insertar(heap, &n1);
    heap_insertar(heap, &n2);
    heap_insertar(heap, &n3);

    pa2m_afirmar(heap_cantidad(heap)==3, "La cantidad del heap es 3");

    pa2m_afirmar(heap_extraer_raiz(heap) == &n1, "Se extrae la raiz correctamente");

    pa2m_afirmar(heap_cantidad(heap)==2, "La cantidad del heap es 2");

    pa2m_afirmar(heap_extraer_raiz(heap) == &n3, "Se extrae la raiz correctamente");

    pa2m_afirmar(heap_cantidad(heap)==1, "La cantidad del heap es 1");

    pa2m_afirmar(heap_extraer_raiz(heap) == &n2, "Se extrae la raiz correctamente");

    pa2m_afirmar(heap_cantidad(heap)==0, "La cantidad del heap es 0");

    pa2m_afirmar(heap_esta_vacio(heap), "El heap esta vacio");

    heap_destruir(heap);
}

void SePuedeOperarConVariosElementos(){
    heap_t* heap = heap_crear(comparador_numeros, NULL);

    int Elementos[5000];

    int estado = -1;

    for(int i = 0; i < 5000; i++){
        Elementos[i] = i;
        estado = heap_insertar(heap, &Elementos[i]);
        if(estado == -1){
            break;
        }
    }

    pa2m_afirmar(estado == EXITO, "Se puede insertar varios elementos en el heap");
    pa2m_afirmar(heap_cantidad(heap)==5000, "La cantidad del heap es 5000");

    int raiz_extraida = 0; 

    pa2m_afirmar(*(int*)heap_extraer_raiz(heap) == raiz_extraida, "Se extrae la raiz correctamente");

    raiz_extraida = 4999;

    int ultimo_extraido = -1;

    for(int i = 0; i < 4999; i++){
       ultimo_extraido = *(int*)heap_extraer_raiz(heap);
    }

    pa2m_afirmar(ultimo_extraido == raiz_extraida, "Se extraen varias raices correctamente");

    pa2m_afirmar(heap_cantidad(heap)==0, "La cantidad del heap es 0");

    pa2m_afirmar(heap_esta_vacio(heap), "El heap esta vacio");

    heap_destruir(heap);
}

void PruebasVariasTP(){
    heap_t* heap = heap_crear(comparador_niveles, NULL);

    pokemones_t p1 = {50, "Pikachu"};
    pokemones_t p2 = {25, "Charmander"};
    pokemones_t p3 = {100, "Bulbasaur"};

    pa2m_afirmar(heap != NULL, "Se puede crear un heap exitosamente");

    pa2m_afirmar(heap_insertar(heap, &p1) == EXITO, "Puedo insertar a Pikachu con nivel 50");
    pa2m_afirmar(heap_insertar(heap, &p2) == EXITO, "Puedo insertar a Charmander con nivel 25");
    pa2m_afirmar(heap_insertar(heap, &p3) == EXITO, "Puedo insertar a Bulbasaur con nivel 100");

    pa2m_afirmar(heap_cantidad(heap)==3, "La cantidad del heap es 3");
    pa2m_afirmar(heap_extraer_raiz(heap) == &p2, "Se extrae Charmander");
    pa2m_afirmar(heap_extraer_raiz(heap) == &p1, "Se extrae Pikachu");
    pa2m_afirmar(heap_extraer_raiz(heap) == &p3, "Se extrae Bulbasaur");

    pa2m_afirmar(heap_cantidad(heap)==0, "La cantidad del heap es 0");

    heap_destruir(heap);
}

int main(){

    pa2m_nuevo_grupo("Pruebas de creacion");
    SePuedeCrearHeap();

    pa2m_nuevo_grupo("Pruebas de insercion de elementos");
    SePuedenInsertarElementosEnElHeap();

    pa2m_nuevo_grupo("Pruebas de extraer la raiz");
    SePuedeExtraerLaRaiz();

    pa2m_nuevo_grupo("Pruebas de varios elementos");
    SePuedeOperarConVariosElementos();

    pa2m_nuevo_grupo("Pruebas para el TP");
    PruebasVariasTP();

    return pa2m_mostrar_reporte();
}