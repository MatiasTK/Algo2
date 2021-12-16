#include "TDALista/lista.h"
#include "TDAHeap/heap.h"
#include "batallas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define DEFAULT "\033[0m"
#define NEGRITA "\033[1m"
#define CURSIVA "\033[3m"
#define SUBRAYADO "\033[4m"

#define NEGRO "\033[30m"
#define ROJO "\033[31m"
#define VERDE "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BLANCO "\033[37m"

#define FONDO_NEGRO "\033[40m"
#define FONDO_ROJO "\033[41m"
#define FONDO_VERDE "\033[42m"
#define FONDO_AMARILLO "\033[43m"
#define FONDO_AZUL "\033[44m"
#define FONDO_MAGENTA "\033[45m"
#define FONDO_CYAN "\033[46m"
#define FONDO_BLANCO "\033[47m"
/*

╩ ╚ ╔ ╦ ╠ ═ ╬ ╣ ║ ╗ ╝

█

└ ┴ ┬ ├ ─ ┼ │ ┤ ┐

« »

*/

#define TAM_CARACTER 1
#define MAX_NOMBRE 25
#define MAX_RUTA 100
#define LECTURA "r"

#define ERROR -1
#define EXITO 0

#define GIMNASIO 'G'
#define LIDER 'L'
#define ENTRENADOR 'E'
#define POKEMON 'P'

#define LEIDOS_STDIN 1
#define LEIDOS_ESPERADOS 2
#define CAMPOS_PERSONAJE 1
#define CAMPOS_GIMNASIO 3
#define CAMPOS_ENTRENADOR 1
#define CAMPOS_POKEMON 4

#define IGUAL 0
#define MENOR -1
#define MAYOR 1

#define FORMATO_STDIN "%[^\n]\n"
#define FORMATO_GENERAL "%c;%[^\n]\n"
#define FORMATO_PERSONAJE "%[^\n]\n"
#define FORMATO_GIMNASIO "%[^;];%i;%i\n"
#define FORMATO_ENTRENADOR "%[^\n]\n"
#define FORMATO_POKEMON "%[^;];%i;%i;%i\n"


typedef struct pokemon {
    int velocidad;
    int defensa;
    int ataque;
    char nombre[MAX_NOMBRE];
} pokemon_t;

typedef struct personaje {
    char nombre[MAX_NOMBRE];
    lista_t* party; // Lista de pokemones de combate
    lista_t* caja; // Caja (Lista) de pokemones obtenidos
    size_t cant_pokemon;
} personaje_t;

typedef struct entrenador {
    char nombre[MAX_NOMBRE];
    lista_t* party; // Cola de pokemones de combate
    size_t cant_pokemon;
    bool es_lider;
} entrenador_t;

typedef struct gimnasio {
    char nombre[MAX_NOMBRE];
    int dificultad;
    int tipo_batalla;
    lista_t* entrenadores; // Pila de entrenadores del gimnasio
} gimnasio_t;



#define LIMITE_BUFFER 1024
#define MAX_POKEMONES_BATALLA 6


/*
* Destructor de pokemones. Al ser invocado con un puntero a pokemon,  
*   libera la memoria reservada para el mismo.
*/
void destructor_pokemones(void* pokemon);

/*
* Destructor de entrenadores. Recibe un puntero a un entrenador, y libera
*   la memoria reservada para cada pokemon de su caja. Luego, libera la 
*   memoria reservada para el entrenador.
*/
void destructor_entrenadores(void* entrenador);

/*
* Destructor de gimnasios. Recibe el puntero a un gimnasio y lo destruye, liberando a 
*    cada entrenador y sus pokemones, y luego al gimnasio.
*/
void destructor_gimnasios(void* gimnasio);

/*
* Pre: -
* Post: Destruye el personaje principal recibido y sus pokemones, liberando
    la memoria reservada por estos.
*/
void personaje_destruir(personaje_t* personaje);


/*
* Pre: Los gimnasios recibidos deben ser válidos y estar inicializados con su dificultad
    correspondiente.
* Post: Compara los gimnasios recibidos según su dificultad. Si el primero es menos
    difícil, devuelve MENOR. Sino, si es más difícil devuelve MAYOR, y sino IGUAL.
*/
int comparador_gimnasios (void* g1, void* g2);


/*
* Pre: tam_memoria debe ser > 0.  El archivo debe ser válido y estar abierto en modo LECTURA.
* Post: Lee el primer caracter de la línea del archivo recibido, con el FORMATO_GENERAL y lo almacena en tipo_lectura. Luego, 
        lee el resto de la línea y lo devuelve. Si terminó el archivo se devuelve NULL y hay_error no se modifica. 
        En caso de error se devuelve NULL, y se modifica hay_error a true.
*/
char* leer_linea(char* buffer, size_t tam_memoria, FILE* archivo, char* tipo_lectura, bool* hay_error);


/*
* Pre: La ruta debe ser una ruta de personaje válida.
* Post: Reserva memoria para un personaje, y le carga el personaje de la ruta recibida.
    En caso de error, devuelve NULL, y sino el personaje cargado.
*/
personaje_t* cargar_personaje(char ruta[MAX_RUTA]);

/*
* Pre: La ruta debe ser una ruta de gimnaio válida, al igual que el heap.
* Post: Carga uno o más gimnasios del archivo con la ruta recibida en el heap
    de gimnasios. Devuelve ERROR si hay algún problema o EXITO si se pudo
    cargar el gimnasio.
*/
int cargar_gimnasio(heap_t* heap_gimnasios, char ruta[MAX_RUTA]);


