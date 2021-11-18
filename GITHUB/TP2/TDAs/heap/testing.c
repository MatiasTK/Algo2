#include "heap.h"
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_VECTOR 10

void mostrar_arbol(void** buffer, int n);
void destruir_numero(void* numero);
int comparar_numeros(void* nro1, void* nro2);
void imprimir_vector(int vector[], int tope);
void titulo(const char* titulo);
void afirmar(int condicion, const char* mensaje);
void resumen();

void pruebas_creacion_heap(){

	heap_t* heap = heap_crear(NULL, NULL);

    afirmar(heap == NULL, "No puedo crear un heap sin comparador.");

    heap = heap_crear(comparar_numeros, NULL);

    afirmar(heap != NULL, "Puedo crear un heap sin destructor.");

    heap_destruir(heap);
    heap = NULL;

    heap = heap_crear(comparar_numeros, destruir_numero);

    afirmar(heap != NULL, "Puedo crear un heap con comparador y destructor.");

    heap_destruir(heap);
}

void inicializar_vector(int vector[]){
    vector[0] = 3;
    vector[1] = 5;
    vector[2] = 9;
    vector[3] = 2;
    vector[4] = 7;
    vector[5] = 1;
    vector[6] = 8;
    vector[7] = 10;
    vector[8] = 4;
    vector[9] = 6;
}

int insertar_en_heap(heap_t* heap, int vector[], int tope){
    int i = 0;
    bool hay_error = false;

    while (i < tope && !hay_error){
        if (heap_insertar(heap, &vector[i]) == ERROR)
            hay_error = true;
        i++;
    }

    if (hay_error) return ERROR;

    return EXITO;
}

void pruebas_insercion_heap(){
    
    int vector[MAX_VECTOR];
    inicializar_vector(vector);
    
    heap_t* heap = heap_crear(comparar_numeros, NULL);
    if (!heap) return;

    afirmar(insertar_en_heap(heap, vector, MAX_VECTOR) == EXITO, "Puedo insertar 10 elementos en el heap.");
    afirmar(!heap_vacio(heap), "El heap no esta vacio.");
    afirmar(heap_elementos(heap) == MAX_VECTOR, "Hay 10 elementos en el heap.");

    mostrar_arbol((*heap).vector, (*heap).tope);

    heap_destruir(heap);
}

int inicializar_vector_dinamico(int* vector[]){
    vector[0] = malloc(sizeof(int));
    if (!vector[0]) return ERROR;
    (*vector[0]) = 3;

    vector[1] = malloc(sizeof(int));
    if (!vector[1]){
        free(vector[0]);
        return ERROR;
    }
    (*vector[1]) = 5;

    vector[2] = malloc(sizeof(int));
    if (!vector[2]){
        free(vector[0]);
        free(vector[1]);
        return ERROR;
    }
    (*vector[2]) = 9;

    vector[3] = malloc(sizeof(int));
    if (!vector[3]){
        free(vector[0]);
        free(vector[1]);
        free(vector[2]);
        return ERROR;
    }
    (*vector[3]) = 2;

    vector[4] = malloc(sizeof(int));
    if (!vector[4]){
        free(vector[0]);
        free(vector[1]);
        free(vector[2]);
        free(vector[3]);
        return ERROR;
    }
    (*vector[4]) = 7;

    vector[5] = malloc(sizeof(int));
    if (!vector[4]){
        free(vector[0]);
        free(vector[1]);
        free(vector[2]);
        free(vector[3]);
        free(vector[4]);
        return ERROR;
    }
    (*vector[5]) = 1;

    vector[6] = malloc(sizeof(int));
    if (!vector[6]){
        free(vector[0]);
        free(vector[1]);
        free(vector[2]);
        free(vector[3]);
        free(vector[4]);
        free(vector[5]);
        return ERROR;
    }
    (*vector[6]) = 8;

    vector[7] = malloc(sizeof(int));
    if (!vector[7]){
        free(vector[0]);
        free(vector[1]);
        free(vector[2]);
        free(vector[3]);
        free(vector[4]);
        free(vector[5]);
        free(vector[6]);
        return ERROR;
    }
    (*vector[7]) = 10;

    vector[8] = malloc(sizeof(int));
    if (!vector[8]){
        free(vector[0]);
        free(vector[1]);
        free(vector[2]);
        free(vector[3]);
        free(vector[4]);
        free(vector[5]);
        free(vector[6]);
        free(vector[7]);
        return ERROR;
    }
    (*vector[8]) = 4;

    vector[9] = malloc(sizeof(int));
    if (!vector[9]){
        free(vector[0]);
        free(vector[1]);
        free(vector[2]);
        free(vector[3]);
        free(vector[4]);
        free(vector[5]);
        free(vector[6]);
        free(vector[7]);
        free(vector[8]);
        return ERROR;
    }
    (*vector[9]) = 6;

    return EXITO;
}

void destruir_vector(int* vector[], int tope){
    for (int i = 0; i < tope; i++)
        free(vector[i]);
}

int insertar_dinamico_en_heap(heap_t* heap, int* vector[], int tope){
    int i = 0;
    bool hay_error = false;

    while (i < tope && !hay_error){
        if (heap_insertar(heap, vector[i]) == ERROR)
            hay_error = true;
        i++;
    }

    if (hay_error) return ERROR;

    return EXITO;
}

void pruebas_insercion_memoria_dinamica_heap(){

    int* vector[MAX_VECTOR];
    if (inicializar_vector_dinamico(vector) == ERROR) return;

    heap_t* heap = heap_crear(comparar_numeros, destruir_numero);
    if (!heap){
        destruir_vector(vector, MAX_VECTOR);
        return;
    }
    
    afirmar(insertar_dinamico_en_heap(heap, vector, MAX_VECTOR) == EXITO,
        "Puedo insertar 10 variables del heap en el heap.");
    afirmar(!heap_vacio(heap), "El heap no esta vacio.");
    afirmar(heap_elementos(heap) == MAX_VECTOR, "Hay 10 elementos en el heap.");

    mostrar_arbol((*heap).vector, (*heap).tope);

    heap_destruir(heap);
}

void pruebas_extraccion_raiz_heap(){

    int vector[MAX_VECTOR];
    inicializar_vector(vector);

    heap_t* heap = heap_crear(comparar_numeros, NULL);
    if (!heap) return;

    if (insertar_en_heap(heap, vector, MAX_VECTOR) == ERROR){
        heap_destruir(heap);
        return;
    }

    int elemento_en_la_raiz = *(int*)heap_extraer_raiz(heap);
    afirmar(elemento_en_la_raiz == 1, "El primer elemento extraido es el esperado.");

    elemento_en_la_raiz = *(int*)heap_extraer_raiz(heap);
    afirmar(elemento_en_la_raiz == 2, "El segundo elemento extraido es el esperado.");

    elemento_en_la_raiz = *(int*)heap_extraer_raiz(heap);
    afirmar(elemento_en_la_raiz == 3, "El tercer elemento extraido es el esperado.");

    elemento_en_la_raiz = *(int*)heap_extraer_raiz(heap);
    afirmar(elemento_en_la_raiz == 4, "El cuarto elemento extraido es el esperado.");

    elemento_en_la_raiz = *(int*)heap_extraer_raiz(heap);
    afirmar(elemento_en_la_raiz == 5, "El quinto elemento extraido es el esperado.");

    elemento_en_la_raiz = *(int*)heap_extraer_raiz(heap);
    afirmar(elemento_en_la_raiz == 6, "El sexto elemento extraido es el esperado.");

    elemento_en_la_raiz = *(int*)heap_extraer_raiz(heap);
    afirmar(elemento_en_la_raiz == 7, "El septimo elemento extraido es el esperado.");

    elemento_en_la_raiz = *(int*)heap_extraer_raiz(heap);
    afirmar(elemento_en_la_raiz == 8, "El octavo elemento extraido es el esperado.");

    elemento_en_la_raiz = *(int*)heap_extraer_raiz(heap);
    afirmar(elemento_en_la_raiz == 9, "El noveno elemento extraido es el esperado");

    elemento_en_la_raiz = *(int*)heap_extraer_raiz(heap);
    afirmar(elemento_en_la_raiz == 10, "El decimo elemento extraido es el esperado.");

    afirmar(heap_vacio(heap), "El heap esta vacio.");

    heap_destruir(heap);
}

void pruebas_extraccion_raiz_memoria_dinamica_heap(){
    int* vector[MAX_VECTOR];
    if (inicializar_vector_dinamico(vector) == ERROR) return;
    
    heap_t* heap = heap_crear(comparar_numeros, destruir_numero);
    if (!heap){
        destruir_vector(vector, MAX_VECTOR);
        return;
    }

    if (insertar_dinamico_en_heap(heap, vector, MAX_VECTOR) == ERROR){
        destruir_vector(vector, MAX_VECTOR);
        heap_destruir(heap);
        return;
    }

    int* elemento_en_la_raiz = (int*)heap_extraer_raiz(heap);
    afirmar(*elemento_en_la_raiz == 1, "El primer elemento extraido es el esperado.");
    free(elemento_en_la_raiz);

    elemento_en_la_raiz = (int*)heap_extraer_raiz(heap);
    afirmar(*elemento_en_la_raiz == 2, "El segundo elemento extraido es el esperado.");
    free(elemento_en_la_raiz);

    elemento_en_la_raiz = (int*)heap_extraer_raiz(heap);
    afirmar(*elemento_en_la_raiz == 3, "El tercer elemento extraido es el esperado.");
    free(elemento_en_la_raiz);

    elemento_en_la_raiz = (int*)heap_extraer_raiz(heap);
    afirmar(*elemento_en_la_raiz == 4, "El cuarto elemento extraido es el esperado.");
    free(elemento_en_la_raiz);

    elemento_en_la_raiz = (int*)heap_extraer_raiz(heap);
    afirmar(*elemento_en_la_raiz == 5, "El quinto elemento extraido es el esperado.");
    free(elemento_en_la_raiz);

    elemento_en_la_raiz = (int*)heap_extraer_raiz(heap);
    afirmar(*elemento_en_la_raiz == 6, "El sexto elemento extraido es el esperado.");
    free(elemento_en_la_raiz);

    elemento_en_la_raiz = (int*)heap_extraer_raiz(heap);
    afirmar(*elemento_en_la_raiz == 7, "El septimo elemento extraido es el esperado.");
    free(elemento_en_la_raiz);

    elemento_en_la_raiz = (int*)heap_extraer_raiz(heap);
    afirmar(*elemento_en_la_raiz == 8, "El octavo elemento extraido es el esperado.");
    free(elemento_en_la_raiz);

    elemento_en_la_raiz = (int*)heap_extraer_raiz(heap);
    afirmar(*elemento_en_la_raiz == 9, "El noveno elemento extraido es el esperado");
    free(elemento_en_la_raiz);

    elemento_en_la_raiz = (int*)heap_extraer_raiz(heap);
    afirmar(*elemento_en_la_raiz == 10, "El decimo elemento extraido es el esperado.");
    free(elemento_en_la_raiz);

    afirmar(heap_vacio(heap), "El heap esta vacio.");

    heap_destruir(heap);
}

int main(){

    system("clear");

    titulo("PRUEBAS CREACION HEAP");
	pruebas_creacion_heap();

    titulo("PRUEBAS INSECION HEAP");
    pruebas_insercion_heap();

    titulo("PRUEBAS INSERCION MEMORIA DINAMICA HEAP");
    pruebas_insercion_memoria_dinamica_heap();

    titulo("PRUEBAS EXTRACION RAIZ HEAP");
    pruebas_extraccion_raiz_heap();

    titulo("PRUEBAS EXTRACION RAIZ MEMORIA DINAMICA HEAP");
    pruebas_extraccion_raiz_memoria_dinamica_heap();

    resumen();

	return 0;
}





















void mostrar_arbol(void** buffer, int n){
	printf("\n");
	int niveles = 0;
	for(int restantes=n;restantes>0;restantes>>=1)
		niveles++;
	
	int n_nodo=0;
	for(int nivel=0;nivel<niveles;nivel++){
		int posicion = 1<<(niveles-nivel-1);
		
		for(int nodo=0;nodo<(1<<nivel);nodo++){
			for(int i=1;i<posicion;i++){
				if(i<=posicion/2-1 || 2*n_nodo+1 >= n || *(int*)buffer[2*n_nodo+1]==0)
					printf("  ");
				else{
					if(i == posicion/2)
						printf(" ┌");
					else printf("――");
				}
			}

			if(n_nodo<n && *(int*)buffer[n_nodo]!=0){
				int valor = *(int*)buffer[n_nodo]<100?*(int*)buffer[n_nodo]:99;
				printf("%2d", valor);
			}
			else{
				printf("  ");
			}
			
			for(int i=0;i<posicion;i++){
				if(i>=posicion/2 || 2*n_nodo+2 >= n ||*(int*)buffer[2*n_nodo+2]==0)
					printf("  ");
				else{
					if(i == posicion/2-1)
						printf("―┐");
					else printf("――");
				}
			}
			n_nodo++;
		}
		printf("\n");
	}
}

void liberar_numero(int* numero){
	free(numero);
}

void destruir_numero(void* numero){
	if (numero)
		liberar_numero((int*)numero);
}

int comparar_numeros(void* nro1, void* nro2){
	if (!nro1 || !nro2) return 0;

	if (*(int*)nro1 > *(int*)nro2) return 1;
	if (*(int*)nro1 < *(int*)nro2) return -1;
	return 0;
}

void imprimir_vector(int vector[], int tope){
    for (int i = 0; i < tope; i++){
		printf("%i", vector[i]);
		if (i < tope-1) printf(" - ");
	}
	printf("\n");
}

/*Perdon por las variables globales me parecieron
la forma mas limpia de contar pruebas y errores.
Entiendo que no es una buena practica*/
int pruebas = 0;
int errores = 0;

void titulo(const char* titulo){
    size_t tam_mensaje = strlen(titulo);

	printf("\n");
    for (size_t i = 0; i < tam_mensaje; i++)
        printf("~");
    printf("\n");

    printf("%s\n", titulo);

    for (size_t i = 0; i < tam_mensaje; i++)
        printf("~");
    printf("\n\n");
}

void afirmar(int condicion, const char* mensaje){
	if (condicion){
        printf("✔ - %s\n", mensaje);
        pruebas++;
    }
    else{
        printf("✘ - %s\n", mensaje);
        pruebas++;
        errores++;
    }
}

void resumen(){
    printf("\n");
    printf("------------------------------------\n");
    printf("%i pruebas realizadas, %i errores.\n", pruebas, errores);
    printf("------------------------------------\n");
}