#ifndef _HERRAMIENTAS_GRAFICAS_H_
#define _HERRAMIENTAS_GRAFICAS_H_

#include <stdbool.h>

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

#define ESPACIO ' '

/*
 * Muestra un mensaje de presentacion en la terminal.
 * Devuelve impresion por terminal.
 */
void presentacion();

/*
 * Muestra el menu de inicio en la terminal.
 * Devuelve impresion por terminal.
 */
void menu_de_inicio();

/*
 * Muestra el menu de gimnasio en la terminal.
 * Devuelve impresion por terminal.
 */
void menu_de_gimnasio();


/*
 * Muestra el menu de victoria en la terminal.
 * Devuelve impresion por terminal.
 */
void menu_de_victoria();

/*
 * Muestra el menu de derrota en la terminal.
 * Devuelve impresion por terminal.
 */
void menu_de_derrota();

/*
 * Muestra la informacion del gimnasio, incluido datos del gimnasio, entrenadores y pokemones.
 * Recibe un puntero generico valido a gimnasio_t y un bool inicilizado.
 * Devuelve impresion por terminal.
 */
void mostrar_info_gimnasio(void* gimnasio, bool en_simulacion);

/*
 * Muestra un informe por terminal segun el mensaje que reciba.
 * Recibe un puntero a string valido.
 * Devuelve impresion por terminal.
 */
void mostrar_informe(const char* mensaje);

/*
 * Muestra al personaje principal junto a sus pokemones.
 * Recibe un puntero generico valido a personaje_t.
 * Devuelve impresion por pantalla.
 */
void mostrar_personaje_con_pokemones(void* personaje);

/*
 * Muestra al entrenador junto a sus pokemones.
 * Recibe un puntero generico valido a entrenador_t, y un bool inicializado.
 * Devuelve impresion por pantalla.
 */
void mostrar_entrenador_con_pokemones(void* entrenador, bool es_lider);

/*
 * Muestra el menu de batalla por terminal.
 * Recibe un puntero generico valido a personaje_t, entrenador_t y pokemon_t.
 * Devuelve impresion por pantalla.
 */
void menu_de_batalla(void* personaje, void* entrenador, void* pkm_personaje, void* pkm_entrenador);

/*
 * Muestra al entrenador ganador de la batalla junto con su pokemon.
 * Recibe dos punteros a string validos.
 * Devuelve impresion por pantalla.
 */
void mostrar_ganador(const char* nombre_entrenador, const char* nombre_pokemon);

/*
 * Le informa al jugador que se convirtio en maestro pokemon luego de ganar todos los gimnasios.
 * Recibe un puntero string valido.
 * Devuelve impresion por pantalla.
 */
void mostrar_mensaje_maestro_pokemon(const char* nombre);

#endif /* _HERRAMIENTAS_GRAFICAS_H_ */