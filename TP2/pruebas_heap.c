#include "pa2mm.h"
#include "../src/heap.h"
#include <stdio.h>
#include "../src/estructura_aux.h"
#include "../src/hospital.h"
#include <string.h>

#define EXITO 0
#define ERROR -1

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

/*
* PRE: Recibe dos pokemones validos.
* POST: Devuelve un numero entero positivo si el primer pokemon tiene mas nivel que el segundo, un negativo si el primero tiene menos nivel o 0 si tienen el mismo nivel.
*/
int comparador_niveles_heap(void* p1, void* p2){
    pokemon_t* pokemon1 = (pokemon_t*)p1;
    pokemon_t* pokemon2 = (pokemon_t*)p2;

    if(pokemon1->nivel > pokemon2->nivel){
        return 1;
    }else if(pokemon1->nivel < pokemon2->nivel){
        return -1;
    }else{
        return 0;
    }
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

size_t agregar_pokemones_heap(hospital_t* hospital,heap_t* heap){
    if(!hospital){
        return 0;
    }

    size_t cantidad_agregados = 0;

    lista_iterador_t* iterador = lista_iterador_crear(hospital->lista_entrenadores);
    if(!iterador){
        return 0;
    }


    while(lista_iterador_tiene_siguiente(iterador)){
        entrenador_t* entrenador = lista_iterador_elemento_actual(iterador);
        if(!entrenador){
            lista_iterador_destruir(iterador);
            return 0;
        }

        lista_iterador_t* iterador_pokemones = lista_iterador_crear(entrenador->lista_pokemones);
        if(!iterador_pokemones){
            lista_iterador_destruir(iterador);
            return 0;
        }

        while(lista_iterador_tiene_siguiente(iterador_pokemones)){
            pokemon_t* pokemon = lista_iterador_elemento_actual(iterador_pokemones);
            if(!pokemon){
                lista_iterador_destruir(iterador_pokemones);
                lista_iterador_destruir(iterador);
                return 0;
            }

            heap_insertar(heap, pokemon);
            cantidad_agregados++;
            lista_iterador_avanzar(iterador_pokemones);
        }
        lista_iterador_destruir(iterador_pokemones);
        
        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);

    return cantidad_agregados;
}

void PruebasVariasTP(){
    heap_t* heap = heap_crear(comparador_niveles_heap, NULL);

    hospital_t* hospital = hospital_crear();
    if(!hospital){
        return;
    }

    pa2m_afirmar(hospital_leer_archivo(hospital, "ejemplos/varios_entrenadores.hospital"), "Se pudo leer el archivo");

    pa2m_afirmar(heap != NULL, "Se puede crear un heap exitosamente");

    pa2m_afirmar(heap_cantidad(heap)==0, "La cantidad del heap es 0");
    
    size_t cargados = agregar_pokemones_heap(hospital, heap);

    pa2m_afirmar(cargados == 24 , "Se cargaron 24 pokemones");
    pa2m_afirmar(heap_cantidad(heap)==24, "La cantidad del heap es 24");
    
    char* pokemones_extraidos[24] = {"rampardos","venonat","toxicroak","charizard","mothim","luxio","shieldon","hitmonlee","tyranitar","delcatty","munchlax","groudon","torkal","kecleon","swinub","miltank","kabuto","kingdra","magnemite","shuckle","alcremie","duskull","flareon","eternatus"};	
    int i = 0;

    while(cargados > 0){
        pokemon_t* pokemon = heap_extraer_raiz(heap);
        pa2m_afirmar(strcmp(pokemon->nombre, pokemones_extraidos[i]) == 0, "Se extrae la raiz correctamente");
        i++;
        cargados--;
    }

    pa2m_afirmar(heap_cantidad(heap)==0, "La cantidad del heap es 0");

    heap_destruir(heap);
    hospital_destruir(hospital);
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