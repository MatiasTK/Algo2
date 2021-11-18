#include "herramientas_graficas.h"
#include "aventura.h"

void presentacion(){

    system("clear");

    printf(AZUL);
    printf("\t ____    _                                         _       _                            \n");
    printf("\t|  _ \\  (_)                                       (_)     | |                          \n");
    printf("\t| |_) |  _    ___   _ __   __   __   ___   _ __    _    __| |   ___       __ _          \n");
    printf("\t|  _ <  | |  / _ \\ | '_ \\  \\ \\ / /  / _ \\ | '_ \\  | |  / _` |  / _ \\     / _` |  \n");
    printf("\t| |_) | | | |  __/ | | | |  \\ V /  |  __/ | | | | | | | (_| | | (_) |   | (_| |        \n");
    printf("\t|____/  |_|  \\___| |_| |_|   \\_/    \\___| |_| |_| |_|  \\__,_|  \\___/     \\__,_|   \n");

    sleep(1);

    printf("\t\t                                   _                                    \n");
    printf("\t\t    /\\                            | |                                  \n");
    printf("\t\t   /  \\    __   __   ___   _ __   | |_   _   _   _ __    __ _          \n");
    printf("\t\t  / /\\ \\   \\ \\ / /  / _ \\ | '_ \\  | __| | | | | | '__|  / _` |    \n");
    printf("\t\t / ____ \\   \\ V /  |  __/ | | | | | |_  | |_| | | |    | (_| |        \n");
    printf("\t\t/_/    \\_\\   \\_/    \\___| |_| |_|  \\__|  \\__,_| |_|     \\__,_|   \n");

    sleep(1);

    printf("\t\t _____            _                                                 \n");
    printf("\t\t|  __ \\          | |                                               \n");
    printf("\t\t| |__) |   ___   | | __   ___   _ __ ___     ___    _ __            \n");
    printf("\t\t|  ___/   / _ \\  | |/ /  / _ \\ | '_ ` _ \\   / _ \\  | '_ \\      \n");
    printf("\t\t| |      | (_) | |   <  |  __/ | | | | | | | (_) | | | | |          \n");
    printf("\t\t|_|       \\___/  |_|\\_\\  \\___| |_| |_| |_|  \\___/  |_| |_|     \n");
    printf(DEFAULT);

    sleep(2);
}

void menu_de_inicio(){
    printf("\n\n\n");
    printf(FONDO_VERDE NEGRO"\t\t╔═════════════════════════════════════════════════════╗"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                                                     ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                    MENU DE INICIO                   ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                                                     ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [E] » Ingresar el archivo del entrenador principal. ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [A] » Agregar gimnasios.                            ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [I] » Comenzar a jugar.                             ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [S] » Simular una partida.                          ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [X] » Salir del juego.                              ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                                                     ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t╚═════════════════════════════════════════════════════╝"DEFAULT"\n");
}

void menu_de_gimnasio(){
    printf("\n\n\n");
    printf(FONDO_VERDE NEGRO"\t\t╔═════════════════════════════════════════════════════╗"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                                                     ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                   MENU DE GIMNASIO                  ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                                                     ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [E] » Mostrar entrenador principal y sus pokemones. ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [G] » Mostrar informacion del gimnasio.             ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [C] » Cambiar pokemones de batalla.                 ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [B] » Comenzar la proxima batalla.                  ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [X] » Salir de la partida.                          ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                                                     ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t╚═════════════════════════════════════════════════════╝"DEFAULT"\n");
}

void menu_de_victoria(){
    printf("\n\n\n");
    printf(FONDO_VERDE NEGRO"\t\t╔═════════════════════════════════════════════════════╗"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                                                     ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                   MENU DE VICTORIA                  ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                                                     ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [T] » Tomar un pokemon del lider.                   ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [C] » Cambiar pokemones de batalla.                 ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [N] » Proximo gimnasio.                             ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                                                     ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t╚═════════════════════════════════════════════════════╝"DEFAULT"\n");
}

void menu_de_derrota(){
    printf("\n\n\n");
    printf(FONDO_VERDE NEGRO"\t\t╔═════════════════════════════════════════════════════╗"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                                                     ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                   MENU DE DERROTA                   ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                                                     ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [C] » Cambiar pokemones de batalla.                 ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [R] » Reintentar batalla anterior.                  ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║ [F] » Finalizar partida.                            ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t║                                                     ║"DEFAULT"\n");
    printf(FONDO_VERDE NEGRO"\t\t╚═════════════════════════════════════════════════════╝"DEFAULT"\n");
}

/*
 * Imprime caracteres especiales segun la cantidad que se le pase.
 * Recibe un numero entero positivo.
 * Devuelve impresion por pantalla.
 */
void imprimir_techo(size_t cant_imp){
    printf(FONDO_AZUL NEGRO"\t╔");
    for (size_t i = 0; i <= cant_imp; i++)
        printf("═");
    printf("╗"DEFAULT"\n");
}

/*
 * Imprime caracteres especiales segun la cantidad que se le pase.
 * Recibe un numero entero positivo.
 * Devuelve impresion por pantalla.
 */
void imprimir_piso(size_t cant_imp){
    printf(FONDO_AZUL NEGRO"\t╚");
    for (size_t i = 0; i <= cant_imp; i++)
        printf("═");
    printf("╝"DEFAULT"\n");
}

/*
 * Imprime caracteres especiales segun la cantidad que se le pase.
 * Recibe un numero entero positivo.
 * Devuelve impresion por pantalla.
 */
void imprimir_espacios(size_t cant_imp){
    printf(FONDO_AZUL NEGRO"\t║");
    for (size_t i = 0; i <= cant_imp; i++)
        printf("%c", ESPACIO);
    printf("║"DEFAULT"\n");
}

/*
 * Imprime caracteres especiales segun la cantidad que se le pase.
 * Recibe un numero entero positivo.
 * Devuelve impresion por pantalla.
 */
void imprimir_diferencia(size_t dif){
    for (size_t i = 0; i <= dif; i++)
        printf("%c", ESPACIO);
    printf("║"DEFAULT"\n");
}

/*
 * Imprime caracteres especiales segun la cantidad que se le pase.
 * Recibe dos numeros enteros positivos.
 * Devuelve impresion por pantalla.
 */
void imprimir_doble_techo(size_t cant_imp_1, size_t cant_imp_2){

    printf(FONDO_AZUL NEGRO"\t╔");
    
    for (size_t i = 0; i <= cant_imp_1; i++)
        printf("═");

    printf("╗"DEFAULT"%4c"FONDO_AZUL NEGRO"╔", ESPACIO);

    for (size_t i = 0; i <= cant_imp_2; i++)
        printf("═");

    printf("╗"DEFAULT"\n");
}

/*
 * Imprime caracteres especiales segun la cantidad que se le pase.
 * Recibe dos numeros enteros positivos.
 * Devuelve impresion por pantalla.
 */
void imprimir_doble_espacios(size_t cant_imp_1, size_t cant_imp_2){
    printf(FONDO_AZUL NEGRO"\t║");

    for (size_t i = 0; i <= cant_imp_1; i++)
        printf("%c", ESPACIO);

    printf("║"DEFAULT"%4c"FONDO_AZUL NEGRO"║", ESPACIO);

    for (size_t i = 0; i <= cant_imp_2; i++)
        printf("%c", ESPACIO);

    printf("║"DEFAULT"\n");
}

/*
 * Imprime caracteres especiales segun la cantidad que se le pase.
 * Recibe un numero entero positivo y un bool inicializado.
 * Devuelve impresion por pantalla.
 */
void imprimir_diferencia_intermedia(size_t cant_imp, bool con_versus){
    for (size_t i = 0; i <= cant_imp; i++)
        printf("%c", ESPACIO);
    
    if (con_versus)
        printf("║"DEFAULT AZUL" VS "FONDO_AZUL NEGRO);
    else
        printf("║"DEFAULT"%4c"FONDO_AZUL NEGRO, ESPACIO);
}

/*
 * Imprime caracteres especiales segun la cantidad que se le pase.
 * Recibe dos numeros enteros positivos.
 * Devuelve impresion por pantalla.
 */
void imprimir_doble_piso(size_t cant_imp_1, size_t cant_imp_2){
    printf(FONDO_AZUL NEGRO"\t╚");
    
    for (size_t i = 0; i <= cant_imp_1; i++)
        printf("═");

    printf("╝"DEFAULT"%4c"FONDO_AZUL NEGRO"╚", ESPACIO);

    for (size_t i = 0; i <= cant_imp_2; i++)
        printf("═");

    printf("╝"DEFAULT"\n");
}

void mostrar_info_gimnasio(void* gimnasio, bool en_simulacion){

    gimnasio_t* gimnasio_aux = (gimnasio_t*)gimnasio;
    // queda feo el casteo por todos lados, lo soluciono así

    size_t tam_nombre = strlen((*gimnasio_aux).nombre);
    size_t cant_imp = 16;
    size_t total = tam_nombre+11;
    size_t dif1 = 0;
    size_t dif2 = 0;

    if (total > 16){
        cant_imp = total;
        dif1 = total-16;
    }
    else {
        dif2 = 16-total;
    }

    printf("\n\t");
    if (!en_simulacion) printf("\t");
    imprimir_techo(cant_imp);

    if (!en_simulacion) printf("\t");
    printf(FONDO_AZUL NEGRO"\t\t║ Gimnasio: %s", (*gimnasio_aux).nombre);
    imprimir_diferencia(dif2);

    if (!en_simulacion) printf("\t");
    printf("\t");
    imprimir_espacios(cant_imp);

    if (!en_simulacion) printf("\t");
    printf(FONDO_AZUL NEGRO"\t\t║ Dificultad:%4i", (*gimnasio_aux).dificultad);
    imprimir_diferencia(dif1);

    if (!en_simulacion) printf("\t");
    printf("\t");
    imprimir_espacios(cant_imp);

    if (!en_simulacion) printf("\t");
    printf(FONDO_AZUL NEGRO"\t\t║ Id Funcion:%4i", (*gimnasio_aux).id_funcion);
    imprimir_diferencia(dif1);

    if (!en_simulacion) printf("\t");
    printf("\t");
    imprimir_piso(cant_imp);
    printf("\n");
}

/*
 * Muestra el nombre del jugador por la terminal.
 * Recibe un puntero a string valido.
 * Devuelve impresion por terminal.
 */
void mostrar_jugador(const char* nombre){
    size_t tam_nombre = strlen(nombre);
    size_t total = tam_nombre+10;

    printf("\t\t");
    imprimir_techo(total);

    printf(FONDO_AZUL NEGRO"\t\t\t║ Jugador: %s", nombre);
    imprimir_diferencia(0);

    printf("\t\t");
    imprimir_piso(total);
    printf("\n");
}

/*
 * Muestra el nombre del entrenador por terminal.
 * Recibe un puntero a string valido, y un bool inicializado.
 * Devuelve impresion por terminal.
 */
void mostrar_entrenador(const char* nombre, bool es_lider){
    size_t tam_nombre = strlen(nombre);
    size_t total;

    if (es_lider)
        total = tam_nombre+8;
    else
        total = tam_nombre+13;

    printf("\t\t");
    imprimir_techo(total);

    if (es_lider)
        printf(FONDO_AZUL NEGRO"\t\t\t║ Lider: %s", nombre);
    else 
        printf(FONDO_AZUL NEGRO"\t\t\t║ Entrenador: %s", nombre);
    
    imprimir_diferencia(0);

    printf("\t\t");
    imprimir_piso(total);
    printf("\n");
}

void mostrar_informe(const char* mensaje){

    size_t tamanio_msj = strlen(mensaje);
    size_t total = tamanio_msj+1;

    printf("\n\n\n\t");
    imprimir_techo(total);
    printf(FONDO_AZUL NEGRO"\t\t║ %s", mensaje);
    imprimir_diferencia(0);
    printf("\t");
    imprimir_piso(total);
    printf("\n");
}

/*
 * Muestra a los pokemones que se enfrentan en la batalla.
 * Recibe dos punteros genericos a pokemon_t validos.
 * Devuelve impresion por terminal.
 */
void mostrar_pokecontrincantes(void* pokemon1, void* pokemon2){

    pokemon_t* pokemon1_aux = (pokemon_t*)pokemon1;
    pokemon_t* pokemon2_aux = (pokemon_t*)pokemon2;
    // queda feo el casteo por todos lados, lo soluciono así

    size_t tam_nombre1 = strlen((*pokemon1_aux).nombre);
    size_t tam_nombre2 = strlen((*pokemon2_aux).nombre);
    size_t cant_imp1 = 15;
    size_t cant_imp2 = 15;
    size_t total1 = tam_nombre1 + 10;
    size_t total2 = tam_nombre2 + 10;
    size_t dif1 = 0, dif2 = 0, dif3 = 0, dif4 = 0;

    if (total1 > 15){
        cant_imp1 = total1;
        dif1 = total1-15;
    }
    else{
        dif2 = 15-total1;
    }

    if (total2 > 15){
        cant_imp2 = total2;
        dif3 = total2-15;
    }
    else{
        dif4 = 15-total2;
    }

    imprimir_doble_techo(cant_imp1, cant_imp2);
    printf(FONDO_AZUL NEGRO"\t║ Pokemon: %s", (*pokemon1_aux).nombre);
    imprimir_diferencia_intermedia(dif2, false);

    printf(FONDO_AZUL NEGRO"║ Pokemon: %s", (*pokemon2_aux).nombre);
    imprimir_diferencia(dif4);

    imprimir_doble_espacios(cant_imp1, cant_imp2);

    printf(FONDO_AZUL NEGRO"\t║ Velocidad:%4i", (*pokemon1_aux).velocidad);
    imprimir_diferencia_intermedia(dif1, true);

    printf(FONDO_AZUL NEGRO"║ Velocidad:%4i", (*pokemon2_aux).velocidad);
    imprimir_diferencia(dif3);

    printf(FONDO_AZUL NEGRO"\t║ Defensa:%4i", (*pokemon1_aux).defensa);
    imprimir_diferencia_intermedia(dif1+2, false);

    printf(FONDO_AZUL NEGRO"║ Defensa:%4i", (*pokemon2_aux).defensa);
    imprimir_diferencia(dif3+2);

    printf(FONDO_AZUL NEGRO"\t║ Ataque:%4i", (*pokemon1_aux).ataque);
    imprimir_diferencia_intermedia(dif1+3, false);

    printf(FONDO_AZUL NEGRO"║ Ataque:%4i", (*pokemon2_aux).ataque);
    imprimir_diferencia(dif3+3);

    imprimir_doble_piso(cant_imp1, cant_imp2);
    printf("\n");
}

/*
 * Muestra los entrenadores que se enfrentan en la batalla.
 * Recibe dos punteros a string validos.
 * Devuelve impresion por pantalla.
 */
void mostrar_contrincantes(const char* nombre1, const char* nombre2){
    
    size_t tam_nombre1 = strlen(nombre1);
    size_t tam_nombre2 = strlen(nombre2);

    printf("\n\n\t");
    imprimir_doble_techo(tam_nombre1+1, tam_nombre2+1);

    printf(FONDO_AZUL NEGRO"\t\t║ %s", nombre1);
    imprimir_diferencia_intermedia(0, true);

    printf("║ %s", nombre2);
    imprimir_diferencia(0);

    printf("\t");
    imprimir_doble_piso(tam_nombre1+1, tam_nombre2+1);
    printf("\n\n");
}

/*
 * Muestra una lista de pokemones por terminal.
 * Recibe un puntero a lista_t valido.
 * Devuelve impresion por terminal.
 */
void mostrar_lista_pokemones(lista_t* pokemones){
    
    lista_iterador_t* it_pokelista = NULL;
    int i = 0;

    printf(FONDO_AZUL NEGRO SUBRAYADO"\t╔════════════╦════════════════════╦═════════╦═══════╦══════╗"DEFAULT"\n");
    printf(FONDO_AZUL NEGRO SUBRAYADO"\t║POS EN LISTA║       NOMBRE       ║VELOCIDAD║DEFENSA║ATAQUE║"DEFAULT"\n");
    for (it_pokelista = lista_iterador_crear(pokemones);
        lista_iterador_tiene_siguiente(it_pokelista);
        lista_iterador_avanzar(it_pokelista)){
        
        pokemon_t* pokemon = (pokemon_t*)lista_iterador_elemento_actual(it_pokelista);
        printf(FONDO_AZUL NEGRO SUBRAYADO"\t║%-12i║%-20s║%-9i║%-7i║%-6i║"DEFAULT"\n", i, (*pokemon).nombre,
            (*pokemon).velocidad, (*pokemon).defensa, (*pokemon).ataque);

        i++;
    }
    printf(FONDO_AZUL NEGRO"\t╚════════════╩════════════════════╩═════════╩═══════╩══════╝"DEFAULT"\n\n");

    lista_iterador_destruir(it_pokelista);
}

void mostrar_personaje_con_pokemones(void* personaje){

    personaje_t* personaje_aux = (personaje_t*)personaje;
    // queda feo el casteo por todos lados, lo soluciono así

    mostrar_jugador((*personaje_aux).nombre);

    printf("\t\t\tPOKEMONES EN CAJA\n");
    mostrar_lista_pokemones((*personaje_aux).caja);

    printf("\n\t\t\tPOKEMONES EN PARTY\n");
    mostrar_lista_pokemones((*personaje_aux).party);
}

void mostrar_entrenador_con_pokemones(void* entrenador, bool es_lider){

    entrenador_t* entrenador_aux = (entrenador_t*)entrenador;
    // queda feo el casteo por todos lados, lo soluciono así

    mostrar_entrenador((*entrenador_aux).nombre, es_lider);

    printf("\t\t\tLISTA DE POKEMONES\n");
    mostrar_lista_pokemones((*entrenador_aux).pokemones);
}

void menu_de_batalla(void* personaje, void* entrenador, void* pkm_personaje, void* pkm_entrenador){

    personaje_t* personaje_aux = (personaje_t*)personaje;
    entrenador_t* entrenador_aux = (entrenador_t*)entrenador;
    pokemon_t* pokemon_personaje = (pokemon_t*)pkm_personaje;
    pokemon_t* pokemon_entrenador = (pokemon_t*)pkm_entrenador;
    // queda feo el casteo por todos lados, lo soluciono así

    mostrar_contrincantes((*personaje_aux).nombre, (*entrenador_aux).nombre);
    mostrar_pokecontrincantes(pokemon_personaje, pokemon_entrenador);
}

void mostrar_ganador(const char* nombre_entrenador, const char* nombre_pokemon){

    size_t tam_nombre1 = strlen(nombre_entrenador);
    size_t tam_nombre2 = strlen(nombre_pokemon);
    size_t total = tam_nombre1+tam_nombre2+22;

    imprimir_techo(total);
    printf(FONDO_AZUL NEGRO"\t║ Ganó %s con su pokemon %s", nombre_entrenador, nombre_pokemon);
    imprimir_diferencia(0);
    imprimir_piso(total);
}

void mostrar_mensaje_maestro_pokemon(const char* nombre){

    size_t tam_nombre = strlen(nombre);
    size_t total = tam_nombre+41;

    printf("\n\n\t");
    imprimir_techo(total);
    printf(FONDO_AZUL NEGRO"\t\t║ FELICITACIONES %s, SOS UN MAESTRO POKEMON!", nombre);
    imprimir_diferencia(0);
    printf("\t");
    imprimir_piso(total);
    printf("\n");
}