#include "definiciones.h"
#include <stdio.h>
#include <stdlib.h>

// COMANDOS
#define FINALIZAR_PARTIDA 'F'
#define REINTENTAR_COMBATE 'R'
#define CAMBIAR_POKEMONES 'C'
#define SIGUIENTE_GIMNASIO 'N'
#define TOMAR_POKEMON 'T'
#define INGRESAR_PERSONAJE 'E'
#define AGREGAR_GIMNASIO 'A'
#define COMENZAR_PARTIDA 'I'
#define SIMULAR_PARTIDA 'S'
#define MOSTRAR_PERSONAJE 'E'
#define MOSTRAR_GIMNASIO 'G'
#define PROXIMA_BATALLA 'B'

#define INPUT_SI_MINUS 's'
#define INPUT_NO_MINUS 'n'
#define INPUT_SI 'S'
#define INPUT_NO 'N'

#define MAX_BONIFICADOR 63


/*
* Pre: memoria es el buffer de memoria que se utilizará, y tam_memoria es su tamaño. 
    tam_memoria tiene en cuenta el \n y el \0 al final del string. Por lo que  si se desea 
    un string de n caracteres, pasar memoria de tamaño n+2 y un tam_memoria de n+2.
* Post: Pide por pantalla un input al usuario y lo devuelve. (Similar a scanf). Descarta
    el sobrante del input, si este es mayor a tam_memoria (contando \n y \0).
*/

char* pedir_input(char* memoria, int tam_memoria) {
    if (!memoria || tam_memoria <= 0) return NULL;
    char* input = NULL;
    input = fgets(memoria, tam_memoria, stdin); // "scanf"
    if (!input) return NULL;

    size_t posicion_cero = strlen(memoria);

    if(posicion_cero == 0 || memoria[posicion_cero-1] != '\n') {
        char descartar[1024]; // Descarto el resto de la línea
        pedir_input(descartar, 1024);
    }

    memoria[posicion_cero-1] = 0;

    int leidos = sscanf(memoria, "%[^\n]", input);
    if (leidos != 1) return NULL;

    return input;
}


funcion_batalla determinar_tipo_batalla(int tipo_batalla) {
    if (tipo_batalla == 1) return funcion_batalla_1;
    if (tipo_batalla == 2) return funcion_batalla_2;
    if (tipo_batalla == 3) return funcion_batalla_3;
    if (tipo_batalla == 4) return funcion_batalla_4;
    if (tipo_batalla == 5) return funcion_batalla_5;
    return determinar_tipo_batalla((rand() % 5) + 1); // Si es otro número, devuelvo una al azar
}

/*
* Pre: El pokemon debe ser válido.
* Post: Aumenta todas las estadísticas del pokémon en 1, a mennos que
    estas hayan alcanzado el MAX_BONIFICADOR. Notifica por pantalla la mejora.
*/
void mejorar_pokemon(pokemon_t* pokemon) {
    if (pokemon->velocidad < MAX_BONIFICADOR)
        (pokemon->velocidad)++;
    if (pokemon->defensa < MAX_BONIFICADOR)
        (pokemon->defensa)++;
    if (pokemon->ataque < MAX_BONIFICADOR)
        (pokemon->ataque)++;
    system("clear");
    printf(VERDE NEGRITA "\n\n\tSe ha mejorado su pokémon! +1\n\n\n" DEFAULT);
}

/*
* Pre: -
* Post: Únicamente imprime por pantalla el menú de derrota.
*/
void imprimir_menu_derrota() {
    system("clear");

    printf(NEGRITA ROJO"\t\t    MENÚ DERROTA"DEFAULT"\n");

    printf("   "AMARILLO FONDO_NEGRO"_.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._"DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO".-'---      - ---     --     ---   -----   - --       ----  ----   -     ---`-."DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(       [C] :  Cambiar Pokémon de batalla                                     )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(       [R] :  Reintentar el Gimnasio                                         )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(       [F] :  Finalizar la partida                                           )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(___       _       _       _       _       _       _       _       _       ___)"DEFAULT"\n");
    printf("    "AMARILLO FONDO_NEGRO"`-._.-' (___ _) `-._.-' `-._.-' `-._.-' `-._.-' `-._.-' (__ _ ) `-._.-'"DEFAULT"\n");
    printf(AMARILLO"            "FONDO_NEGRO"( _ __)"DEFAULT"                                         "AMARILLO FONDO_NEGRO"(_ ___)"DEFAULT"\n");
    printf(AMARILLO"            "FONDO_NEGRO"(__  _)"DEFAULT"                                         "AMARILLO FONDO_NEGRO"(___ _)"DEFAULT"\n");
    printf(AMARILLO"            "FONDO_NEGRO"`-._.-'"DEFAULT"                                         "AMARILLO FONDO_NEGRO"`-._.-'"DEFAULT"\n");
    printf("\n\n\n");
   
}

/*
* Pre: La party debe ser válida.
* Post: Muestra la party recibida, según la cantidad de pokemones de la misma.
*/
void mostrar_party(lista_t* party) {
    if (!party)  {
        printf(ROJO NEGRITA"\nError al mostrar la party\n" DEFAULT);
        return;
    }

    lista_iterador_t* it = lista_iterador_crear(party);
    if (!it) {
        printf(ROJO NEGRITA"\nError al mostrar la party\n" DEFAULT);
        return;
    }
    printf("\n"NEGRITA AMARILLO "\t     PARTY DE POKEMONES DE COMBATE\n" DEFAULT);
    printf(" __| |____________________________________________| |__"DEFAULT"\n");
    printf("(__   ____________________________________________   __)"DEFAULT"\n");
    printf("   | |"FONDO_NEGRO"                                            "DEFAULT"| |"DEFAULT"\n");


    int i = 0;
    for(; lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it)) {
        pokemon_t* pokemon = (pokemon_t*)(lista_iterador_elemento_actual(it));
        if (pokemon) {
            printf("   | |"FONDO_NEGRO"  "AMARILLO"%2i"DEFAULT FONDO_NEGRO"   %20s (%3i/%3i/%3i)   "DEFAULT"| |"DEFAULT"\n", i, pokemon->nombre, pokemon->velocidad, pokemon->defensa, pokemon->ataque);
            if (pokemon != lista_elemento_en_posicion(party, lista_elementos(party))) { 
                for(int j = 0; j < 2; j++) {
                    printf("   | |"FONDO_NEGRO"                                            "DEFAULT"| |"DEFAULT"\n");
                    }
            }
        }
        i++;

    }

    printf(" __| |"FONDO_NEGRO"____________________________________________"DEFAULT"| |__"DEFAULT"\n");
    printf("(__   ____________________________________________   __)"DEFAULT"\n");
    printf("   | |                                            | |"DEFAULT"\n");

    lista_iterador_destruir(it);
}

/*
* Pre: La caja debe ser válida.
* Post: Muestra la caja recibida en forma de lista, enumerando los pokemones desde el 0 en adelante.
*/
void mostrar_caja(lista_t* caja) {
    if (!caja) return;
    printf("\n");
    printf(NEGRITA AMARILLO"\t\t  CAJA DE POKEMONES"DEFAULT"\n\n");
    printf("\t "FONDO_AZUL" N°              Nombre (vel/def/ata)"DEFAULT"\n");
    int i = 0;
    while(i < lista_elementos(caja)) {
        pokemon_t* pokemon = (pokemon_t*)(lista_elemento_en_posicion(caja, (size_t)i));
        printf("\t "FONDO_AZUL NEGRITA AMARILLO"%2i"DEFAULT FONDO_AZUL" %20s (%3i/%3i/%3i)"DEFAULT"\n", i, pokemon->nombre, pokemon->velocidad, pokemon->defensa, pokemon->ataque);
        i++;
    }

}

/*
* Pre: La party y caja deben ser válidas y del mismo personaje. pos debe ser una
    posición válida de un pokémon de la caja.
* Post: Devuelve true si el pokémon en la posición "pos" de la caja está también
    en la party. Sino, devuelve false. Si hay error, asume que está.
*/
bool pokemon_esta_en_party(lista_t* party, lista_t* caja, int pos) {
    if (!party || !caja || pos < 0) return false;
    if (lista_vacia(party)) return false;

    lista_iterador_t* it = lista_iterador_crear(party);
    if (!it) return true; // Asumo que está si hay error

    bool esta_en_party = false;
    pokemon_t* pokemon_caja = (pokemon_t*)(lista_elemento_en_posicion(caja, (size_t)pos));
    while(lista_iterador_tiene_siguiente(it) && !esta_en_party) {
        pokemon_t* buscado = (pokemon_t*)(lista_iterador_elemento_actual(it));
        if (strcmp(buscado->nombre, pokemon_caja->nombre) == 0)
            esta_en_party = true;
        lista_iterador_avanzar(it);
    }

    lista_iterador_destruir(it);
    return esta_en_party;
}

/*
* Pre: La party y la caja deben ser válidas.
* Post: Pide al usuario un pokémon de la caja y lo agrega a la 
    party recibida, reservando memoria para el mismo,  si no está en ella.
    Sino, no lo agrega. Devuelve true hubo algún error,  Sino, devuelve false.
*/
bool agregar_pokemon_a_party(lista_t* party, lista_t* caja) {
    pokemon_t* pokemon = calloc(1, sizeof(pokemon_t));
    if (!pokemon)
        return true;

    bool hay_error = false;    

    char buffer[100];
    char* input;
    int posicion;
    do {
        printf("Seleccione el número de pokémon de su caja a colocar en su party: ");
        input = pedir_input(buffer, 100);
        if (input) 
            posicion = atoi(input);

    } while (!input || posicion >= lista_elementos(caja) || posicion < 0);

    bool esta_en_party = pokemon_esta_en_party(party, caja, posicion);

    if (input && !esta_en_party && posicion < (int)lista_elementos(caja) && posicion >= 0) {
        pokemon_t* pokemon_buscado = (pokemon_t*)(lista_elemento_en_posicion(caja, (size_t)posicion));
        if (pokemon_buscado) {
            strcpy(pokemon->nombre, pokemon_buscado->nombre);
            pokemon->velocidad = pokemon_buscado->velocidad;
            pokemon->defensa = pokemon_buscado->defensa;
            pokemon->ataque = pokemon_buscado->ataque;
            if (lista_insertar(party, pokemon) == ERROR) {
                destructor_pokemones(pokemon);
                hay_error = true;
            }
        } else {
            destructor_pokemones(pokemon);
            hay_error = true;
        }
    } else {
        destructor_pokemones(pokemon);
        hay_error = true;
    }

    return hay_error;
}

/*
* Pre: El personaje debe ser válido.
* Post: Muestra el menú de cambio de pokemones del personaje y le pregunta al personaje si quiere
    hacer cambios en su party. Si así lo quiere, realiza los cambios. Sino, no hace nada.
    Si ocurre algún error, sale y deja la party como estaba.
*/
void mostrar_menu_cambio_pokemones(personaje_t* personaje) {
    char buffer[100];
    char* input;
    char accion;

    system("clear");
    printf("\n"NEGRITA AZUL"\t      MENÚ DE CAMBIO DE POKEMONES"DEFAULT"\n\n");
    printf("Desea cambiar sus pokémones de batalla? [S/N]: ");
    do {
        input = pedir_input(buffer, 100);
        if (input)
            accion = buffer[0];
    } while( !input || ((accion != INPUT_SI) && (accion != INPUT_NO) && (accion != INPUT_SI_MINUS) && (accion != INPUT_NO_MINUS)) );
    
    if (accion == INPUT_SI || accion == INPUT_SI_MINUS) {
        lista_t* party_nueva = lista_crear(destructor_pokemones);
        if (!party_nueva) {
            printf("Ocurrió un error al editar su party. Conservará su party anterior.\n\n");
            return;
        }

        bool hay_error = false;
        bool quiere_agregar_pokemon = true;

        do {
            mostrar_caja(personaje->caja);
            mostrar_party(party_nueva);

            do {
                printf("Quiere agreegar un pokémon a la party? [S/N]: ");
                input = pedir_input(buffer, 100);
                if (input)
                    accion = input[0];
            } while( !input || ((accion != INPUT_SI) && (accion != INPUT_NO) && (accion != INPUT_SI_MINUS) && (accion != INPUT_NO_MINUS)) );

            if (accion == INPUT_SI || accion == INPUT_SI_MINUS) {
                hay_error = agregar_pokemon_a_party(party_nueva, personaje->caja);
            } else {
                quiere_agregar_pokemon = false;
            }
        } while( (!hay_error && quiere_agregar_pokemon && lista_elementos(party_nueva) < MAX_POKEMONES_BATALLA));

        if (hay_error) {
            printf("Ocurrió un error al editar su party. Conservará su party anterior.\n\n");
            lista_destruir(party_nueva);
            return;
        }
        if (!lista_vacia(party_nueva)) {
            lista_destruir(personaje->party);
            personaje->party = party_nueva;
        } else {
            lista_destruir(party_nueva);
        }
    }
    // Sino, no hago nada.
}

/*
* Pre: El personaje debe ser válido.
* Post: Muestra el menú de derrota y pide por pantalla la siguiente acción a realizar.
*/
char mostrar_menu_derrota(personaje_t* personaje) {
    char accion;
    char* input;
    do {
        system("clear");
        imprimir_menu_derrota();
        char buffer[100];
        input = pedir_input(buffer, 100);
        if (input)
            accion = input[0];
        if (input && accion == CAMBIAR_POKEMONES)
            mostrar_menu_cambio_pokemones(personaje);
    } while (!input || (accion != REINTENTAR_COMBATE && accion != FINALIZAR_PARTIDA));

    return accion;
}

/*
* Pre: -
* Post: Únicamente imprime por pantalla el menú de victoria.
*/
void imprimir_menu_victoria() {
    printf("   "AMARILLO FONDO_NEGRO"_.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._"DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO".-'---      - ---     --     ---   -----   - --       ----  ----   -     ---`-."DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(       [T] :  Tomar 'prestado' Pokémon del líder                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(       [C] :  Cambiar los Pokémon de batalla                                 )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(       [N] :  Avanzar al próximo gimnasio                                    )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(___       _       _       _       _       _       _       _       _       ___)"DEFAULT"\n");
    printf("    "AMARILLO FONDO_NEGRO"`-._.-' (___ _) `-._.-' `-._.-' `-._.-' `-._.-' `-._.-' (__ _ ) `-._.-'"DEFAULT"\n");
    printf(AMARILLO"            "FONDO_NEGRO"( _ __)"DEFAULT"                                         "AMARILLO FONDO_NEGRO"(_ ___)"DEFAULT"\n");
    printf(AMARILLO"            "FONDO_NEGRO"(__  _)"DEFAULT"                                         "AMARILLO FONDO_NEGRO"(___ _)"DEFAULT"\n");
    printf(AMARILLO"            "FONDO_NEGRO"`-._.-'"DEFAULT"                                         "AMARILLO FONDO_NEGRO"`-._.-'"DEFAULT"\n");
    printf("\n\n\n");
}

/*
* Pre: -
* Post: Únicamente imprime por pantalla el menú de victoria sin la opción de tomar prestado
    un pokémon del líder.
*/
void imprimir_menu_victoria_sin_tomar_pokemon() {
    system("clear");
    printf("   "AMARILLO FONDO_NEGRO"_.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._"DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO".-'---      - ---     --     ---   -----   - --       ----  ----   -     ---`-."DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(       [C] :  Cambiar los Pokémon de batalla                                 )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")      [N] :  Avanzar al próximo gimnasio                                   ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(___       _       _       _       _       _       _       _       _       ___)"DEFAULT"\n");
    printf("    "AMARILLO FONDO_NEGRO"`-._.-' (___ _) `-._.-' `-._.-' `-._.-' `-._.-' `-._.-' (__ _ ) `-._.-'"DEFAULT"\n");
    printf(AMARILLO"            "FONDO_NEGRO"( _ __)"DEFAULT"                                         "AMARILLO FONDO_NEGRO"(_ ___)"DEFAULT"\n");
    printf(AMARILLO"            "FONDO_NEGRO"(__  _)"DEFAULT"                                         "AMARILLO FONDO_NEGRO"(___ _)"DEFAULT"\n");
    printf(AMARILLO"            "FONDO_NEGRO"`-._.-'"DEFAULT"                                         "AMARILLO FONDO_NEGRO"`-._.-'"DEFAULT"\n");
    printf("\n\n\n");
}

/*
* Pre: El líder debe ser válido.
* Post: Muestra la party de pokemones del líder recibido.
*/
void mostrar_pokemones_lider(entrenador_t* lider) {
    system("clear");
    printf(NEGRITA VERDE"\n\n\t\t    Pokemones lider\n\n" DEFAULT);
    mostrar_party(lider->party);
}

/*
* Pre: El personaje y el líder deben ser válidos.
* Post: Toma un Pokémon del líder y lo incorpora en los Pokémon obtenidos del jugador.
*/
void tomar_pokemon_lider(personaje_t* personaje, entrenador_t* lider) {
    char* input;
    int eleccion;
    int leidos = 0;
    do {
        mostrar_pokemones_lider(lider);
        printf("Seleccione el pokémon del líder que desea tomar prestado, eligiendo el número\n\n");
        char buffer[100];
        input = pedir_input(buffer, 100);
        if (input) {
            leidos = sscanf(input, "%[^\n]\n", buffer);
            if (leidos == LEIDOS_STDIN)
                eleccion = atoi(buffer);
        }

    } while(leidos != LEIDOS_STDIN || !input || (eleccion >= lista_elementos(lider->party)) || (eleccion < 0));

    pokemon_t* pokemon_tomado = ((pokemon_t*)lista_elemento_en_posicion(lider->party, (size_t)eleccion));
    pokemon_t* pokemon_nuevo = calloc(1, sizeof(pokemon_t));
    if (!pokemon_nuevo) {
        printf(ROJO NEGRITA "Se produjo un error al guardar el pokemon en la caja.\n");
        return;
    }
    strcpy(pokemon_nuevo->nombre, pokemon_tomado->nombre);
    pokemon_nuevo->velocidad = pokemon_tomado->velocidad;
    pokemon_nuevo->defensa = pokemon_tomado->defensa;
    pokemon_nuevo->ataque = pokemon_tomado->ataque;

    lista_insertar(personaje->caja, pokemon_nuevo);

    printf(VERDE NEGRITA"Se ha 'tomado prestado' el pokémon %s con éxito!"DEFAULT, pokemon_tomado->nombre);
    printf("\n[Enter] Para avanzar ");

    getchar();
}

/*
* Pre: El personaje debe ser válido, y el líder debe ser el líder del gimnasio que se acaba 
    de ganar.
* Post: Muestra el menú de victoria del personaje, pidiendo al usuario que realice una de las acciones
    que se muestran.
*/
void mostrar_menu_victoria(personaje_t* personaje, entrenador_t* lider) {

    char* input;
    char accion;
    bool pokemon_tomado = false;
    do {
        system("clear");
        if (!pokemon_tomado) 
            imprimir_menu_victoria();
        else 
            imprimir_menu_victoria_sin_tomar_pokemon();
        char buffer[100];
        printf("-> ");
        input = pedir_input(buffer, 100);

        if (input) {
            accion = input[0];
            if (accion == CAMBIAR_POKEMONES) {
                mostrar_menu_cambio_pokemones(personaje);
            }
            if (accion == TOMAR_POKEMON && !pokemon_tomado) {
                printf("Hola\n\n");
                tomar_pokemon_lider(personaje, lider);
                pokemon_tomado = true;
            }
            
        }

    } while(!input || accion != SIGUIENTE_GIMNASIO);
}


/*
* Pre: -
* Post: Imprime el menú de gimnasio con sus opciones.
*/
void imprimir_menu_gimnasio() {
    system("clear");
    printf(NEGRITA ROJO"\t\t  MENÚ DE GIMNASIO"DEFAULT"\n\n");
    printf("   "AMARILLO FONDO_NEGRO"_.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._"DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO".-'---      - ---     --     ---   -----   - --       ----  ----   -     ---`-."DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")       [E] : Mostrar personaje principal                                 ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(          [G] : Mostrar información del gimnasio                              )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")       [C] : Cambiar pokemones de batalla                                  ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(          [B] : Próxima batalla                                              )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(___       _       _       _       _       _       _       _       _       ___)"DEFAULT"\n");
    printf("    "AMARILLO FONDO_NEGRO"`-._.-' (___ _) `-._.-' `-._.-' `-._.-' `-._.-' `-._.-' (__ _ ) `-._.-'"DEFAULT"\n");
    printf(AMARILLO"            "FONDO_NEGRO"( _ __)"DEFAULT"                                         "AMARILLO FONDO_NEGRO"(_ ___)"DEFAULT"\n");
    printf(AMARILLO"            "FONDO_NEGRO"(__  _)"DEFAULT"                                         "AMARILLO FONDO_NEGRO"(___ _)"DEFAULT"\n");
    printf(AMARILLO"            "FONDO_NEGRO"`-._.-'"DEFAULT"                                         "AMARILLO FONDO_NEGRO"`-._.-'"DEFAULT"\n");
    printf("\n\n");
}

/*
* Pre: El personaje debe ser válido.
* Post: Muestra por pantalla el personaje recibido, con su respectiva party y caja.
*/
void mostrar_personaje(personaje_t* personaje) {
    system("clear");
    printf(NEGRITA "\t\t    PERSONAJE: %-25s"DEFAULT"\n\n", personaje->nombre);
    mostrar_party(personaje->party);
    mostrar_caja(personaje->caja);
    printf("[Enter] Para avanzar ");
    getchar();
}

/*
* Pre: El gimnasio debe ser válido.
* Post: Muestra el gimnasio recibido, de a un entrenador por vez, con sus 
    respectivos pokemones.
*/
void mostrar_gimnasio(gimnasio_t* gimnasio) {
    system("clear");

    lista_iterador_t* it = lista_iterador_crear(gimnasio->entrenadores);

    for(; lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it)) {
        printf(NEGRITA ROJO"\t\t    GIMNASIO: %-25s"DEFAULT"\n\n", gimnasio->nombre);
        printf(NEGRITA"\t\t    Dificultad: %3i"DEFAULT"\n\n", gimnasio->dificultad);
        entrenador_t* entrenador = (entrenador_t*)(lista_iterador_elemento_actual(it));
        if (entrenador) {
            printf(NEGRITA AZUL "\t\t    Entrenador: %-25s" DEFAULT"\n", entrenador->nombre);
            mostrar_party(entrenador->party);
        }
        printf("[Enter] Para avanzar ");
        getchar();
        printf("\n\n");
    }

    lista_iterador_destruir(it);
}

/*
* Pre: El personaje y gimnasio puede ser válido.
* Post: Muestra el menú del gimnasio y le pide un comando al usuario.
*/
void mostrar_menu_gimnasio(gimnasio_t* gimnasio, personaje_t* personaje) {

    char accion;
    char* input;
    do {
        system("clear");
        imprimir_menu_gimnasio();
        char buffer[100];
        input = pedir_input(buffer, 100);
        if (input) {
            accion = input[0];
            if (accion == MOSTRAR_PERSONAJE)   
                mostrar_personaje(personaje);
            if (accion == MOSTRAR_GIMNASIO)
                mostrar_gimnasio(gimnasio);
            if (accion == CAMBIAR_POKEMONES)
                mostrar_menu_cambio_pokemones(personaje);
        }
    } while (!input || (accion != PROXIMA_BATALLA));
}

/*
* Pre: -
* Post: Muestra el ganador recibido por pantalla, junto al nombre del pokémon con el que ganó la batalla.
*/
void mostrar_ganador(char nombre_ganador[MAX_NOMBRE], char nombre_pokemon[MAX_NOMBRE]) {
    system("clear");
    printf("\n\n\n");
    printf(CYAN"███████ ██           ██████   █████  ███    ██  █████  ██████   ██████  ██████      ███████ ███████          "DEFAULT"\n");
    printf(CYAN"██      ██          ██       ██   ██ ████   ██ ██   ██ ██   ██ ██    ██ ██   ██     ██      ██               "DEFAULT"\n");
    printf(CYAN"█████   ██          ██   ███ ███████ ██ ██  ██ ███████ ██   ██ ██    ██ ██████      █████   ███████          "DEFAULT"\n");
    printf(CYAN"██      ██          ██    ██ ██   ██ ██  ██ ██ ██   ██ ██   ██ ██    ██ ██   ██     ██           ██          "DEFAULT"\n");
    printf(CYAN"███████ ███████      ██████  ██   ██ ██   ████ ██   ██ ██████   ██████  ██   ██     ███████ ███████ ██ ██ ██ "DEFAULT"\n");
    printf("\n\n");

    printf(NEGRITA AMARILLO"%-25s"DEFAULT"\n", nombre_ganador);
    printf("Con el pokémon %-25s""\n", nombre_pokemon);
    printf("\n\n\n");
}

/*
* Pre: Los entrenadores y pokemones recibidos deben ser válidos.
* Post: Muestra el menú previo a una batalla
*/
void mostrar_menu_batalla(personaje_t* personaje, pokemon_t* pokemon_personaje, entrenador_t* entrenador, 
pokemon_t* pokemon_entrenador, char nombre_gimnasio[MAX_NOMBRE]) {
    printf("\n\n\n");
    printf(AZUL"██████   █████  ████████  █████  ██      ██       █████      ██████   ██████  ██   ██ ███████ ███    ███  ██████  ███    ██ "DEFAULT"\n");
    printf(AZUL"██   ██ ██   ██    ██    ██   ██ ██      ██      ██   ██     ██   ██ ██    ██ ██  ██  ██      ████  ████ ██    ██ ████   ██ "DEFAULT"\n");
    printf(AZUL"██████  ███████    ██    ███████ ██      ██      ███████     ██████  ██    ██ █████   █████   ██ ████ ██ ██    ██ ██ ██  ██ "DEFAULT"\n");
    printf(AZUL"██   ██ ██   ██    ██    ██   ██ ██      ██      ██   ██     ██      ██    ██ ██  ██  ██      ██  ██  ██ ██    ██ ██  ██ ██ "DEFAULT"\n");
    printf(AZUL"██████  ██   ██    ██    ██   ██ ███████ ███████ ██   ██     ██       ██████  ██   ██ ███████ ██      ██  ██████  ██   ████ "DEFAULT"\n");    
    printf("\n\n\n");


    printf(CYAN NEGRITA"\t\t\t\tNombre Gimnasio: %-25s"DEFAULT"\n", nombre_gimnasio);
    printf("\n\n\n");

    if (entrenador->es_lider)
        printf(NEGRITA AMARILLO"\t\t\t\tTe estás enfrentando al líder!\n\n"DEFAULT);

    printf(NEGRITA"\t\t\t\t\t%-25s"DEFAULT"\n", personaje->nombre);
    printf("\n\n");

    printf(AMARILLO"\t\t\t\t\t%-25s"DEFAULT"\n", pokemon_personaje->nombre);
    printf("\t\t\t\t\tVelocidad: %-3i\n", pokemon_personaje->velocidad);
    printf("\t\t\t\t\tDefensa: %-3i\n", pokemon_personaje->defensa);
    printf("\t\t\t\t\tAtaque: %-3i\n", pokemon_personaje->ataque);

    printf("\n\n");

    printf("\t\t\t\t"AZUL NEGRITA"   (¯`·.¸¸.·´¯`·.¸¸.·´¯)"DEFAULT"\n");
    printf("\t\t\t\t"AZUL NEGRITA"  ( \\                 / )"DEFAULT"\n");
    printf("\t\t\t\t"AZUL NEGRITA" ( \\ )               ( / )"DEFAULT"\n");
    printf("\t\t\t\t"AZUL NEGRITA"( ) (        "CYAN"VS"DEFAULT AZUL"       ) ( )"DEFAULT"\n");
    printf("\t\t\t\t"AZUL NEGRITA" ( / )               ( \\ )"DEFAULT"\n");
    printf("\t\t\t\t"AZUL NEGRITA"  ( /                 \\ )"DEFAULT"\n");
    printf("\t\t\t\t"AZUL NEGRITA"   (_.·´¯`·.¸¸.·´¯`·.¸_)"DEFAULT"\n");

    printf("\n\n");

    printf("\t\t\t\t\tAtaque: %-3i\n", pokemon_entrenador->ataque);
    printf("\t\t\t\t\tDefensa: %-3i\n", pokemon_entrenador->defensa);
    printf("\t\t\t\t\tVelocidad: %-3i\n", pokemon_entrenador->velocidad);
    printf(AMARILLO"\t\t\t\t\t%-25s"DEFAULT"\n", pokemon_entrenador->nombre);
    printf("\n\n");
    printf(NEGRITA"\t\t\t\t\t%-25s"DEFAULT"\n", entrenador->nombre);

    printf("\n\n\n\nPulse enter para avanzar: ");


}

/*
* Pre: Los nombres recibidos deben ser válidos.
* Post: Muestra el menú de derrota cuando se está simulando una partida.
*/
void mostrar_menu_derrota_simulacion(char nombre_gimnasio[MAX_NOMBRE], char nombre_personaje[MAX_NOMBRE], char pokemon_personaje[MAX_NOMBRE], 
    char nombre_entrenador[MAX_NOMBRE], char pokemon_entrenador[MAX_NOMBRE] ) {
    printf(ROJO NEGRITA"Hasta acá llegaste %s...\n\n" DEFAULT, nombre_personaje);
    printf("Perdiste en el "NEGRITA"Gimnasio %s"DEFAULT"\n\n", nombre_gimnasio);
    printf("Tu %s perdió contra el %s de %s\n\n", pokemon_personaje, pokemon_entrenador, nombre_entrenador);
}


/*
* Pre: El personaje y heap de gimnasios deben ser válidos.
* Post: Juega la aventura pokemon.
*/
int jugar_aventura(personaje_t* personaje, heap_t* heap_gimnasios, bool simular) {
    bool hay_error = false;
    bool en_juego = true;
    entrenador_t* lider = NULL;

    while(!hay_error && en_juego) { // Gimnasio

        gimnasio_t* gimnasio = heap_extraer_raiz(heap_gimnasios);
        funcion_batalla batalla;
        if (gimnasio) {
            batalla = determinar_tipo_batalla(gimnasio->tipo_batalla);
            if (!simular)
                mostrar_menu_gimnasio(gimnasio, personaje);
        } else {
             en_juego = false;
        }
        while(!hay_error && en_juego && lista_tope(gimnasio->entrenadores) != lider && gimnasio) { // Entrenador

            entrenador_t* entrenador = lista_tope(gimnasio->entrenadores);
            if (!entrenador) 
                hay_error = true;

            lista_iterador_t* it_pokemones_personaje;
            lista_iterador_t* it_pokemones_entrenador;
            if (entrenador) {
                if (entrenador->es_lider)
                    lider = entrenador;

                it_pokemones_personaje = lista_iterador_crear(personaje->party);
                if (!it_pokemones_personaje) hay_error = true;
                it_pokemones_entrenador = lista_iterador_crear(entrenador->party);
                if (!it_pokemones_entrenador) hay_error = true;
            }
            while (!hay_error && en_juego && lista_iterador_tiene_siguiente(it_pokemones_entrenador) && lista_iterador_tiene_siguiente(it_pokemones_personaje)) { // Pokemones

                pokemon_t* pokemon_entrenador = lista_iterador_elemento_actual(it_pokemones_entrenador);
                pokemon_t* pokemon_personaje = lista_iterador_elemento_actual(it_pokemones_personaje);
                if (pokemon_entrenador && pokemon_personaje) { // El que primero se quede sin pokemones
                    system("clear");
                    mostrar_menu_batalla(personaje, pokemon_personaje, entrenador, pokemon_entrenador, gimnasio->nombre);
                    getchar();
                    int resultado_batalla = batalla(pokemon_personaje, pokemon_entrenador);
                    if (resultado_batalla == GANA_PRIMERO) {
                        mostrar_ganador(personaje->nombre, pokemon_personaje->nombre);
                        getchar();
                        mejorar_pokemon(pokemon_personaje);
                        lista_iterador_avanzar(it_pokemones_personaje);
                        lista_iterador_avanzar(it_pokemones_entrenador);
                    } else { // Perdió
                        mostrar_ganador(entrenador->nombre, pokemon_entrenador->nombre);
                        getchar();
                        lista_iterador_destruir(it_pokemones_personaje);
                        lista_iterador_destruir(it_pokemones_entrenador);
                        if (!simular) {
                            char accion = mostrar_menu_derrota(personaje);
                            if (accion == REINTENTAR_COMBATE) {
                                it_pokemones_personaje = lista_iterador_crear(personaje->party);
                                it_pokemones_entrenador = lista_iterador_crear(entrenador->party);
                            } else { // FINALIZAR_PARTIDA
                                en_juego = false;
                            }
                        } else {
                            mostrar_menu_derrota_simulacion(gimnasio->nombre, personaje->nombre, pokemon_personaje->nombre, 
                                entrenador->nombre, pokemon_entrenador->nombre);
                            en_juego = false;
                        }
                    }
                } else {
                    hay_error = true;
                }
            } // Pokemon
            if (en_juego && !hay_error) {
                if (!(entrenador->es_lider))
                    lista_desapilar(gimnasio->entrenadores); // No quiero desapilar al líder, así "tomo prestado" un pokémon de él
                lista_iterador_destruir(it_pokemones_personaje);
                lista_iterador_destruir(it_pokemones_entrenador);
            }
        } // Entrenador
        if (en_juego && !hay_error) {
            if (!simular)
                mostrar_menu_victoria(personaje, lider); // Avanzo al siguiente gimnasio
        }
        if (gimnasio)
            destructor_gimnasios(gimnasio);
    } // Gimnasio

    if (hay_error)
        return ERROR;

    return EXITO;
}




/*
* Pre: -
* Post: Imprime el menú de inicio.
*/
void imprimir_menu_inicio() {
    printf("   "AMARILLO FONDO_NEGRO"_.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._"DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO".-'---      - ---     --     ---   -----   - --       ----  ----   -     ---`-."DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")       [E] : Ingresar archivo de personaje                                 ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(          [A] : Ingresar archivo de gimnasio(s)                              )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")       [I] : Comenzar Partida                                              ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(                                                                             )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(          [S] : Simular partida                                              )"DEFAULT"\n");
    printf(" "AMARILLO FONDO_NEGRO")                                                                           ("DEFAULT"\n");
    printf(AMARILLO FONDO_NEGRO"(___       _       _       _       _       _       _       _       _       ___)"DEFAULT"\n");
    printf("    "AMARILLO FONDO_NEGRO"`-._.-' (___ _) `-._.-' `-._.-' `-._.-' `-._.-' `-._.-' (__ _ ) `-._.-'"DEFAULT"\n");
    printf(AMARILLO"            "FONDO_NEGRO"( _ __)"DEFAULT"                                         "AMARILLO FONDO_NEGRO"(_ ___)"DEFAULT"\n");
    printf(AMARILLO"            "FONDO_NEGRO"(__  _)"DEFAULT"                                         "AMARILLO FONDO_NEGRO"(___ _)"DEFAULT"\n");
    printf(AMARILLO"            "FONDO_NEGRO"`-._.-'"DEFAULT"                                         "AMARILLO FONDO_NEGRO"`-._.-'"DEFAULT"\n");
    printf("\n\n");
    printf(ROJO NEGRITA "Ambos archivos deben estar cargados para comenzar o simular una partida!\n\n"DEFAULT);

}

/*
* Pre: -
* Post: Pide la ruta del personaje al usuario y carga un personaje con el archivo
    de la ruta. Devuelve el personaje, si hay error devuelve NULL.
*/
personaje_t* ingresar_archivo_personaje() {
    char buffer[MAX_RUTA];
    printf(NEGRITA "Ingrese la ruta del archivo de personaje: " DEFAULT);
    char* ruta_personaje = pedir_input(buffer, MAX_RUTA);
    if (!ruta_personaje) return NULL;

    personaje_t* personaje = cargar_personaje(ruta_personaje);
    if (!personaje) return NULL;

    return personaje;
}

/*
* Pre: El heap debe ser válido.
* Post: Pide la ruta de gimnasio(s) al usuario y carga uno o más gimnasios con el archivo
    de la ruta. Si lo(s) puede cargar, devuelve EXITO. Si hay error devuelve ERROR.
*/
int ingresar_archivo_gimnasio(heap_t* heap_gimnasios) {
    char buffer[MAX_RUTA];
    printf(NEGRITA "Ingrese la ruta del archivo de gimnasio: " DEFAULT);
    char* ruta_gimnasio = pedir_input(buffer, MAX_RUTA);
    if (!ruta_gimnasio) return ERROR;
    if (cargar_gimnasio(heap_gimnasios, ruta_gimnasio) == ERROR)
        return ERROR;

    return EXITO;
}


/*
* Pre: El nombre debe ser el nombre del personaje principal.
* Post: Informa al usuario que se ha convertido en un maestro pokémon.
*/
void mostrar_mensaje_maestro_pokemon(char nombre[MAX_NOMBRE]) {
    system("clear");
    printf(VERDE NEGRITA"\n\nEnhorabuena %s! Te has convertido en un MAESTRO POKÉMON."DEFAULT"\n\n", nombre);
}


/*
* Pre: El personaje y el heap de gimnasios deben ser válidos.
* Post: Muestra el menú de inicio, pidiendo un comando al usuario. Ejecuta una acción 
    según el comando recibido.
*/
int mostrar_menu_inicio(heap_t* heap_gimnasios) {

    
    char buffer[100];
    char* input;
    char comando;
    personaje_t* personaje = NULL;
    bool gimnasio_cargado = false;

    do {
        system("clear");
        imprimir_menu_inicio();
        input = pedir_input(buffer, 100);
        if (input) {
            comando = input[0];
            if (!personaje && comando == INGRESAR_PERSONAJE) {
                personaje = ingresar_archivo_personaje();
                if (!personaje) {
                    printf(ROJO NEGRITA"Error al cargar el archivo, inténtelo de nuevo"DEFAULT"\n\n");
                    printf("[Enter] Para continuar ");
                    getchar();
                }
            } else if (comando == AGREGAR_GIMNASIO) {
                if (ingresar_archivo_gimnasio(heap_gimnasios) == EXITO)
                    gimnasio_cargado = true;
                else {
                    printf(ROJO NEGRITA"Error al cargar el archivo, inténtelo de nuevo"DEFAULT"\n\n");     
                    printf("[Enter] Para continuar ");
                    getchar();
                }
            }
        }
    } while(!input || ((comando != SIMULAR_PARTIDA && comando != COMENZAR_PARTIDA) || !personaje || !gimnasio_cargado));

    bool simular = false;
    if (comando == SIMULAR_PARTIDA)
        simular = true;
    
    if (jugar_aventura(personaje, heap_gimnasios, simular) == ERROR) {
        personaje_destruir(personaje);
        return ERROR;
    }

    if (heap_vacio(heap_gimnasios))
        mostrar_mensaje_maestro_pokemon(personaje->nombre);

    personaje_destruir(personaje);

    return EXITO;
}

int main() {
    

    srand((unsigned)time(NULL));
    heap_t* heap_gimnasios = heap_crear(comparador_gimnasios, destructor_gimnasios);
    if (!heap_gimnasios) return ERROR;

    int resultado_partida = mostrar_menu_inicio(heap_gimnasios);
    if (resultado_partida == ERROR) {
        heap_destruir(heap_gimnasios);
        return ERROR;
    }
    
    heap_destruir(heap_gimnasios);

    return 0;
}