#include "src/hospital.h"
#include "src/simulador.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define COLOR_VERDE "\x1b[32m"
#define COLOR_RESET "\x1b[0m"
#define COLOR_ROJO "\x1b[31m"
#define COLOR_AMARILLO "\x1b[33m"
#define COLOR_AZUL "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_NARANJA "\x1b[1;30m"
#define COLOR_GRIS "\x1b[1;37m"
#define COLOR_BLANCO "\x1b[1;37m"

#define PUNTOS_BASE 100

#define BONUS_HARDCORE 60
#define BONUS_PESADILLA 80
#define BONUS_ULTRA_PESADILLA 100

typedef struct{
    simulador_t* simulador;
    bool jugando;
    size_t cantidad_de_dificultades;
}Juego;

/*
* PRE: Recibe un numero.
* POST: Devuelve true si el numero es primo, false en caso contrario.
*/
bool es_numero_primo(int numero){
    if(numero <= 1){
        return false;
    }

    for(int i = 2; i < numero; i++){
        if(numero % i == 0){
            return false;
        }
    }

    return true;
}

/*
* PRE:
* POST: Devuelve 0 si el nivel adivinado es igual al nivel del pokemon, 1 si el nivel del pokemon es primo, 2 si el nivel del pokemon no es primo.
*/
int verificar_nivel_harcore(unsigned nivel_adivinado, unsigned nivel_pokemon){
    if(nivel_adivinado == nivel_pokemon){
        return 0;
    }

    if(es_numero_primo((int)nivel_pokemon)){
        return 1;
    }else{
        return 2;
    }
}

/*
* PRE: 
* POST: Devuelve Exito si el resultado es 0, primo si el resultado es 1, y no primo si el resultado es 2.
*/
const char* verificacion_a_string_hardcore(int resultado_verificacion){
    if(resultado_verificacion == 0){
        return "Felicidades, acertaste!!";
    }else if(resultado_verificacion == 1){
        return "El numero que estas buscando es primo";
    }else if(resultado_verificacion == 2){
        return "El numero que estas buscando no es primo";
    }
    return "ERROR";
}

/*
* PRE:
* POST: Devuelve el puntaje de la dificultad hardcore en base a la cantidad de intentos.
*/
unsigned calcular_puntaje_hardcore(unsigned cantidad_intentos){
    if(cantidad_intentos > PUNTOS_BASE){
        cantidad_intentos = PUNTOS_BASE;
    }

    return (PUNTOS_BASE - cantidad_intentos) + BONUS_HARDCORE;
}

/*
* PRE: Recibe una numero.
* POST: Devuelve true si el numero recibido es un numero perfecto, false en caso contrario.
*/
bool es_numero_perfecto(int numero){
    int suma = 0;

    for(int i = 1; i < numero; i++){
        if(numero % i == 0){
            suma += i;
        }
    }

    return suma == numero;
}

/*
* PRE:
* POST: Devuelve 0 si el nivel adivinado es igual al nivel del pokemon, 1 si el nivel del pokemon es un numero perfecto, 2 si el nivel del pokemon no es un numero perfecto.
*/
int verificar_nivel_pesadilla(unsigned nivel_adivinado, unsigned nivel_pokemon){
    if(nivel_adivinado == nivel_pokemon){
        return 0;
    }

    if(es_numero_perfecto((int)nivel_pokemon)){
        return 1;
    }else{
        return 2;
    }
}

/*
* PRE: 
* POST: Devuelve Exito si el resultado es 0, es numero perfecto si el resultado es 1, y no es numero perfecto si el resultado es 2.
*/
const char* verificacion_a_string_pesadilla(int resultado_verificacion){
    if(resultado_verificacion == 0){
        return "Felicidades, acertaste!!";
    }else if(resultado_verificacion == 1){
        return "El numero que estas buscando es un numero perfecto";
    }else if(resultado_verificacion == 2){
        return "El numero que estas buscando no es un numero perfecto";
    }
    return "ERROR";
}

/*
* PRE:
* POST: Devuelve el puntaje de la dificultad pesadilla en base a la cantidad de intentos.
*/
unsigned calcular_puntaje_pesadilla(unsigned cantidad_intentos){
    if(cantidad_intentos > PUNTOS_BASE){
        cantidad_intentos = PUNTOS_BASE;
    }

    return (PUNTOS_BASE - cantidad_intentos) + BONUS_PESADILLA;
}

/*
* PRE:
* POST: Devuelve 0 si el nivel adivinado es igual al nivel del pokemon, 1 si el nivel adivinado fue mayor o -1 si el nivel adivinado fue menor.
*/
int verificar_nivel_ultra_pesadilla(unsigned nivel_adivinado, unsigned nivel_pokemon){
    if(nivel_adivinado == nivel_pokemon){
        return 0;
    }

    if(nivel_adivinado > nivel_pokemon){
        return 1;
    }else{
        return -1;
    }
}

/*
* PRE: 
* POST: Devuelve Exito si el resultado es 0, es numero perfecto si el resultado es 1, y no es numero perfecto si el resultado es 2.
*/
const char* verificacion_a_string_ultra_pesadilla(int resultado_verificacion){
    if(resultado_verificacion == 0){
        return "Felicidades, acertaste!!";
    }

    bool random_bool = rand() % 2;

    if(resultado_verificacion == 1){
        if(random_bool){ //Devuelve la informacion correcta
            return "El numero que estas buscando es mayor";
        }else{ // Devuelve la informacion incorrecta
            return "El numero que estas buscando es menor";
        }
    }

    if(resultado_verificacion == -1){
        if(random_bool){ //Devuelve la informacion correcta
            return "El numero que estas buscando es menor";
        }else{ // Devuelve la informacion incorrecta
            return "El numero que estas buscando es mayor";
        }
    }
    return "ERROR";
}

unsigned calcular_puntaje_ultra_pesadilla(unsigned cantidad_intentos){
    if(cantidad_intentos > PUNTOS_BASE){
        cantidad_intentos = PUNTOS_BASE;
    }

    return (PUNTOS_BASE - cantidad_intentos) + BONUS_ULTRA_PESADILLA;
}

/*
* PRE: Recibe un juego.
* POST: Crea 3 dificultades custom.
* EXPLICACION DIFICULTADES:
*  - Hardcore: Te dice si el numero del pokemon es primo o no.
*  - Pesadilla: Te dice si el numero del pokemon es un numero perfecto o no.
*/
void crear_dificultades_custom(Juego* juego){
    DatosDificultad hardcore;
    hardcore.nombre = "hardcore";
    hardcore.verificar_nivel = verificar_nivel_harcore;
    hardcore.verificacion_a_string = verificacion_a_string_hardcore;
    hardcore.calcular_puntaje = calcular_puntaje_hardcore;
    juego->cantidad_de_dificultades++;

    DatosDificultad pesadilla;
    pesadilla.nombre = "pesadilla";
    pesadilla.verificar_nivel = verificar_nivel_pesadilla;
    pesadilla.verificacion_a_string = verificacion_a_string_pesadilla;
    pesadilla.calcular_puntaje = calcular_puntaje_pesadilla;
    juego->cantidad_de_dificultades++;

    DatosDificultad ultra_pesadilla;
    ultra_pesadilla.nombre = "ultra pesadilla";
    ultra_pesadilla.verificar_nivel = verificar_nivel_ultra_pesadilla;
    ultra_pesadilla.verificacion_a_string = verificacion_a_string_ultra_pesadilla;
    ultra_pesadilla.calcular_puntaje = calcular_puntaje_ultra_pesadilla;
    juego->cantidad_de_dificultades++;

    simulador_simular_evento(juego->simulador, AgregarDificultad, &hardcore);
    simulador_simular_evento(juego->simulador, AgregarDificultad, &pesadilla);
    simulador_simular_evento(juego->simulador, AgregarDificultad, &ultra_pesadilla);
}

Juego* inicializar_juego(hospital_t* hospital){
    Juego* juego = calloc(1, sizeof(Juego));
    if(juego == NULL){
        hospital_destruir(hospital);
        printf("No se pudo reservar memoria para el juego\n");
        exit(EXIT_FAILURE);
    }

    juego->simulador = simulador_crear(hospital);
    if(juego->simulador == NULL){
        hospital_destruir(hospital);
        free(juego);
        printf("No se pudo reservar memoria para el simulador\n");
        exit(EXIT_FAILURE);
    }

    juego->jugando = true; 
    juego->cantidad_de_dificultades = 3; // El simulador empieza con 3 dificultades estandar.

    crear_dificultades_custom(juego);

    return juego;
}

void destruir_juego(Juego* juego){
    simulador_destruir(juego->simulador);
    free(juego);
}

char leer_comando(){
    char linea[100];
    char* leido;
    leido = fgets(linea, 100, stdin);
    if(!leido)
        return 0;
    while(*leido == ' ')
        leido++;
    return (char)tolower(*leido);
}

void mostrar_estadisticas(Juego* juego){
    EstadisticasSimulacion e;
    simulador_simular_evento(juego->simulador, ObtenerEstadisticas, &e);

    printf("Estas son tus estadisticas actuales!\n");
    printf("Cantidad de entrenadores atendidos: %d\n", e.entrenadores_atendidos);
    printf("Cantidad de entrenadores totales: %d\n", e.entrenadores_totales);
    printf("Cantidad de pokemon atendidos: %d\n", e.pokemon_atendidos);
    printf("Cantidad de pokemon en espera: %d\n", e.pokemon_en_espera);
    printf("Cantidad de pokemon totales: %d\n", e.pokemon_totales);
    printf("Cantidad de puntos: %d\n", e.puntos);

}

void mostrar_pokemon_tratado(Juego* juego){
    InformacionPokemon info;
    simulador_simular_evento(juego->simulador, ObtenerInformacionPokemonEnTratamiento, &info);

    if(info.nombre_pokemon == NULL || info.nombre_entrenador == NULL){
        printf("¡Lo siento! No hay ningun pokemon en tratamiento\n");
        return;
    }

    printf("El pokemon que esta en tratamiento es: %s\n", info.nombre_pokemon);
    printf("El entrenador del pokemon es: %s\n", info.nombre_entrenador);
}

void mostrar_intento(Juego* juego){
    Intento intento;
    printf("Intenta adivinar el nivel del pokemon!, ingresa un numero: ");
    scanf(" %i", &intento.nivel_adivinado);
    getchar();

    if(simulador_simular_evento(juego->simulador, AdivinarNivelPokemon, &intento) == ErrorSimulacion){
        printf("¡Lo siento! No se pudo adivinar el nivel del pokemon\n");
        printf("Intenta cargar otro entrenador\n");
        return;
    }
    printf("%s\n", intento.resultado_string);

    if(intento.es_correcto){
        printf("Atendiendo al proximo pokemon..\n");
    }
}

void imprimir_bienvenida(){
    FILE* bienvenida = fopen("ejemplos/bienvenida.txt", "r");

    char string[128];

    printf(COLOR_VERDE);
    while(fgets(string,sizeof(string),bienvenida) != NULL){
        printf("%s", string);
    }
    printf(COLOR_RESET);

    fclose(bienvenida);
}

void imprimir_despedida(){
    FILE* despedida = fopen("ejemplos/despedida.txt", "r");

    char string[128];

    printf(COLOR_ROJO);
    while(fgets(string,sizeof(string),despedida) != NULL){
        printf("%s", string);
    }
    printf(COLOR_RESET);

    fclose(despedida);
}

void chequear_juego_finalizado(Juego* juego){
    EstadisticasSimulacion e;
    simulador_simular_evento(juego->simulador, ObtenerEstadisticas, &e);

    if(e.pokemon_atendidos == e.pokemon_totales){
        system("clear");
        imprimir_despedida();
        printf("¡Felicitaciones! Has terminado el juego\n");
        printf("Estas son tus estadisticas finales!\n");
        printf("Cantidad de entrenadores atendidos: %d\n", e.entrenadores_atendidos);
        printf("Cantidad de entrenadores totales: %d\n", e.entrenadores_totales);
        printf("Cantidad de pokemon atendidos: %d\n", e.pokemon_atendidos);
        printf("Cantidad de pokemon en espera: %d\n", e.pokemon_en_espera);
        printf("Cantidad de pokemon totales: %d\n", e.pokemon_totales);
        printf("Cantidad de puntos: %d\n", e.puntos);
        simulador_simular_evento(juego->simulador, FinalizarSimulacion, NULL);
        juego->jugando = false;
    }
}

void cambiar_dificultad(Juego* juego){
    printf("Dificultades disponibles: \n");

    int ultimo_id = -1;

    for(int i = 0; i < juego->cantidad_de_dificultades; i++){
        InformacionDificultad info_dificultad;
        info_dificultad.id = i;
        simulador_simular_evento(juego->simulador, ObtenerInformacionDificultad, &info_dificultad);
        printf("ID: %d - ",info_dificultad.id);
        printf("%s",info_dificultad.nombre_dificultad);
        if(info_dificultad.en_uso){
            printf(" (en uso)");
        }
        printf("\n");
        ultimo_id = info_dificultad.id;
    }

    int id_nueva_dificultad = 20;

    printf("Ingresa el ID de la dificultad nueva: ");
    scanf(" %d", &id_nueva_dificultad);
    while(id_nueva_dificultad > ultimo_id){
        printf("\n¡Lo siento! Ese ID no exite, vuelve a intentarlo: ");
        scanf(" %d", &id_nueva_dificultad);
    }

    if(simulador_simular_evento(juego->simulador, SeleccionarDificultad, &id_nueva_dificultad) == ExitoSimulacion){
        printf("Se cambio la dificultad correctamente\n");
    }else{
        printf("¡Lo siento! No se pudo cambiar la dificultad\n");
    }
    getchar();
}

void imprimir_about(){
    system("clear");
    printf("Creado por: Matias Vallejos\n");
    printf("Creado para: Catedra Mendez - Algoritmos y Programacion II\n");
    printf("Año: 2021\n");
}

void ejecutar_comando(Juego *juego, char comando){
    switch (comando) {
        case 'q': //Salir del juego
            system("clear");
            imprimir_despedida();
            juego->jugando = false;
            break;
        case 'e':
            mostrar_estadisticas(juego);
            break;
        case 'p':
            if(simulador_simular_evento(juego->simulador, AtenderProximoEntrenador, NULL) == ErrorSimulacion){
                printf("¡Ya no quedan mas entrenadores!\n");
            }else{
                printf("Se atendio al proximo entrenador!\n");
            }
            break;
        case 'i':
            mostrar_pokemon_tratado(juego);
            break;
        case 'a':
            mostrar_intento(juego);
            chequear_juego_finalizado(juego);
            break;
        case 'd':
            cambiar_dificultad(juego);
            break;
        case 'u':
            imprimir_about();
            break;
        default: //el resto de las cosas
            break;
    }

    printf("Presiona enter para continuar..");
    getchar();
}

int main(int argc, char *argv[]) {

    srand ((unsigned int)time(NULL));

    printf("Bievenido al hospital pokemon!\n");
    system("sleep 1");

    hospital_t* hospital = hospital_crear();
    if(hospital_leer_archivo(hospital, "ejemplos/varios_entrenadores.hospital") == false){
        printf("No se pudo leer el archivo\n");
        return -1;
    }
    printf("Abriendo las puertas del hospital...\n");
    system("sleep 2");

    Juego* juego = inicializar_juego(hospital);
    printf("Llamando a las enfermeras pokemon...\n");
    system("sleep 2");

    system("clear");

    do{
        imprimir_bienvenida();
        printf("Bienvenido jugador!\n");
        printf("¿Que deseas hacer?\n");
        printf(" ____ \n");
        printf("||E || %sMostrar Estadisticas%s\n",COLOR_AZUL,COLOR_RESET);
        printf("||__||\n");
        printf("|/__%c|\n", 92);
        printf(" ____ \n");
        printf("||P || %sAtender entrenador%s\n",COLOR_AMARILLO,COLOR_RESET);
        printf("||__||\n");
        printf("|/__%c|\n", 92);
        printf(" ____ \n");
        printf("||I || %sMostrar Pokemon Actual en tratamiento%s\n",COLOR_MAGENTA,COLOR_RESET);
        printf("||__||\n");
        printf("|/__%c|\n", 92);
        printf(" ____ \n");
        printf("||A || %sAdivinar el nivel del pokemon en tratamiento%s\n",COLOR_CYAN,COLOR_RESET);
        printf("||__||\n");
        printf("|/__%c|\n", 92);
        printf(" ____ \n");
        printf("||D || %sCambiar dificultad%s\n",COLOR_ROJO,COLOR_RESET);
        printf("||__||\n");
        printf("|/__%c|\n", 92);
        printf(" ____ \n");
        printf("||U || %sInformacion sobre el programa%s\n",COLOR_NARANJA,COLOR_RESET);
        printf("||__||\n");
        printf("|/__%c|\n", 92);
        printf(" ____ \n");
        printf("||Q || %sSalir%s\n",COLOR_BLANCO,COLOR_RESET);
        printf("||__||\n");
        printf("|/__%c|\n", 92);
        printf("\n%s> %s", COLOR_VERDE, COLOR_RESET);
        char c = leer_comando();
        ejecutar_comando(juego, c);
        system("clear");
    }while(juego->jugando);
 
    destruir_juego(juego);

    return 0;
}