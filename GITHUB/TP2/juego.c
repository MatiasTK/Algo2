#include "aventura.h"

#define CARGAR_PERSONAJE 'E'
#define CARGAR_GIMNASIO 'A'
#define COMENZAR_PARTIDA 'I'
#define SIMULAR_PARTIDA 'S'
#define MOSTRAR_PERSONAJE 'E'
#define MOSTRAR_GIMNASIO 'G'
#define CAMBIAR_POKEMONES 'C'
#define PROXIMA_BATALLA 'B'
#define PROXIMO_COMBATE 'N'
#define TOMAR_POKEMON_LIDER 'T'
#define PROXIMO_GIMNASIO 'N'
#define REINTENTAR_BATALLA 'R'
#define FINALIZAR_PARTIDA 'F'
#define SEGUIR 'S'
#define SALIR 'X'
#define SI 'S'
#define NO 'N'

#define EN_SIMULACION true
#define NO_EN_SIMULACION false
#define ES_LIDER true
#define NO_ES_LIDER false

/*
 * Se encarga de detener el flujo del programa pidiendo un input al usuario.
 * Devuelve interaccion e impresion por terminal.
 */
void frenar_ejecucion_para_luego_seguir(){
    char eleccion;
    printf("\tIngrese [S] para seguir... ");
    while (leer_input(&eleccion, CARACTER) == ERROR)
        printf("\tIngreselo denuevo: ");
    while (eleccion != SEGUIR){
        printf("\tIngreselo denuevo: ");
        while (leer_input(&eleccion, CARACTER) == ERROR)
            printf("\tIngreselo denuevo: ");
    }
}

/*
 * Busca un pokemon especifico por su nombre en una lista dada.
 * Recibe un puntero a string valido e inicilizado, y un puntero a lista inicializada.
 * Devuelve el pokemon si lo encuentra o NULL en caso de error.
 */
pokemon_t* buscar_pokemon_en_lista(pokemon_t* pokemon_a_buscar, lista_t* lista_donde_buscar){

    pokemon_t* pokemon_encontrado = NULL;
    lista_iterador_t* it_pokelista = lista_iterador_crear(lista_donde_buscar);
    if (!it_pokelista) return NULL;
    bool encontrado = false;

    while (!encontrado && lista_iterador_tiene_siguiente(it_pokelista)){
        pokemon_encontrado = (pokemon_t*)lista_iterador_elemento_actual(it_pokelista);
        if ( (strcmp((*pokemon_a_buscar).nombre, (*pokemon_encontrado).nombre) == 0) && 
             ((*pokemon_a_buscar).velocidad == (*pokemon_encontrado).velocidad) &&
             ((*pokemon_a_buscar).defensa == (*pokemon_encontrado).defensa) && 
             ((*pokemon_a_buscar).ataque == (*pokemon_encontrado).ataque) ){
            
            encontrado = true;
        }
        else{
            lista_iterador_avanzar(it_pokelista);
        }
    }
    lista_iterador_destruir(it_pokelista);

    if (!encontrado) return NULL;

    return pokemon_encontrado;
}

/*
 * Aumenta los atributos del pokemon siempre y cuando estos tengan valor menor a 63.
 * Recibe un puntero a pokemon_t valido.
 * Devuelve los campos del struct pokemon_t actualizados.
 */
void aumentar_atributos(pokemon_t* pokemon){
    
    if ((*pokemon).velocidad < MAX_BONIFICACION)
        (*pokemon).velocidad++;
    
    if ((*pokemon).defensa < MAX_BONIFICACION)
        (*pokemon).defensa++;

    if ((*pokemon).ataque < MAX_BONIFICACION)
        (*pokemon).ataque++;
}

/*
 * Busca el pokemon insertado en la caja del jugador y del party, y aumenta sus atributos.
 * Recibe un puntero a personaje_t valido e inicializado, y un numero entero positivo,
 * Devuelve los pokemones con sus atributos actualizados.
 */
void boostear_pokemon(personaje_t* personaje, size_t pos_en_party){

    pokemon_t* pokemon_en_party = (pokemon_t*)lista_elemento_en_posicion((*personaje).party, pos_en_party);
    if (!pokemon_en_party) return;

    pokemon_t* pokemon_en_caja = buscar_pokemon_en_lista(pokemon_en_party, (*personaje).caja);
    if (!pokemon_en_caja) return;

    aumentar_atributos(pokemon_en_party);
    aumentar_atributos(pokemon_en_caja);
}

/*
 * Intercambia los pokemones de pelea del jugador segun las posiciones dadas.
 * Recibe dos punteros a lista validos e inicializados, y dos numeros enteros positivos.
 * Devuelve 0 si pudo intercambiar los pokemones, o -1 si no pudo.
 */
int swapear_pokemones(lista_t* caja, lista_t* party, size_t pos_en_party, size_t pos_en_caja){

    pokemon_t* pokemon_en_caja = (pokemon_t*)lista_elemento_en_posicion(caja, pos_en_caja);
    if (!pokemon_en_caja) return ERROR;

    pokemon_t* pokemon_repetido = buscar_pokemon_en_lista(pokemon_en_caja, party);
    if (pokemon_repetido) return ERROR;

    if (lista_borrar_de_posicion(party, pos_en_party) == ERROR)
        return ERROR;
    
    pokemon_t* pokemon_a_insertar = crear_pokemon_copiado(pokemon_en_caja);
    if (!pokemon_a_insertar) return ERROR;

    if (lista_insertar_en_posicion(party, pokemon_a_insertar, pos_en_party) == ERROR){
        free(pokemon_a_insertar);
        return ERROR;
    }

    return EXITO;
}

/*
 * Le consulta al usuario las posiciones de los pokemones que desea intercambiar, y luego los
 * intercambia.
 * Recibe un puntero a personaje_t valido e inicializado.
 * Devuelve 0 si pudo intercambiar a los pokemones, o -1 si no pudo.
 */
int cambiar_pokemones(personaje_t* personaje){

    if (!personaje) return ERROR;
    if (lista_elementos((*personaje).caja) <= MAX_POKEMONES_BATALLA) return ERROR;

    size_t pos_en_party, pos_en_caja;
    
    printf("Ingrese la posicion del pokemon de pelea que desea cambiar: ");
    while (leer_input(&pos_en_party, NATURAL) == ERROR)
        printf("Ingreselo denuevo: ");
    while (pos_en_party >= lista_elementos((*personaje).party)){
        printf("Ingreselo denuevo: ");
        while (leer_input(&pos_en_party, NATURAL) == ERROR)
            printf("Ingreselo denuevo: ");
    }

    printf("Ingrese la posicion del pokemon obtenido con el que desea reemplazar: ");
    while (leer_input(&pos_en_caja, NATURAL) == ERROR)
        printf("Ingreselo denuevo: ");
    while (pos_en_caja >= lista_elementos((*personaje).caja)){
        printf("Ingreselo denuevo: ");
        while (leer_input(&pos_en_caja, NATURAL) == ERROR)
            printf("Ingreselo denuevo: ");
    }

    if (swapear_pokemones((*personaje).caja, (*personaje).party, pos_en_party, pos_en_caja) == ERROR)
        return ERROR;

    system("clear");
    mostrar_personaje_con_pokemones(personaje);
    printf("\tAsí quedaron organizados tus pokemones.\n");
    frenar_ejecucion_para_luego_seguir();

    return EXITO;
}

/*
 * Le consulta al usuario la ruta de un archivo.
 * Recibe un vector.
 * Devuelve el vector inicializado.
 */
void consultar_ruta_archivo(char ruta_archivo[MAX_RUTA]){

    printf("\tIngrese la ruta del archivo: ");
    while (leer_input(ruta_archivo, STRING) == ERROR)
        printf("\tIngreselo denuevo: ");
}

/*
 * Muestra los datos del gimnasio junto a sus entrenadores.
 * Recibe un puntero a gimnasio_t valido e inicializado.
 * Devuelve impresion por terminal.
 */
void mostrar_gimnasio(gimnasio_t* gimnasio){
    
    lista_iterador_t* it_entrenadores = NULL;
    int i = 0;

    for (it_entrenadores = lista_iterador_crear((*gimnasio).entrenadores);
        lista_iterador_tiene_siguiente(it_entrenadores);
        lista_iterador_avanzar(it_entrenadores)){
        entrenador_t* entrenador = (entrenador_t*)lista_iterador_elemento_actual(it_entrenadores);

        system("clear");

        mostrar_info_gimnasio(gimnasio, NO_EN_SIMULACION);

        if (i == 0)
            mostrar_entrenador_con_pokemones(entrenador, ES_LIDER);
        else 
            mostrar_entrenador_con_pokemones(entrenador, NO_ES_LIDER);
            
        frenar_ejecucion_para_luego_seguir();
        i++;
    }

    lista_iterador_destruir(it_entrenadores);
}

/*
 * Le muestra al usuario el menu de derrota para que éste decida que hacer.
 * Recibe un caracter inicializado, un puntero a personaje_t valido e inicializado, y 3 punteros a bool validos.
 * Devuelve interaccion e impresion por terminal.
 */
void interactuar_menu_derrota(char eleccion, personaje_t* personaje, bool* permanecer_en_menu_gimnasio, bool* perdio_batalla,
    bool* permanecer_en_menu_derrota){

    system("clear");

    switch(eleccion){

        case CAMBIAR_POKEMONES:
            mostrar_personaje_con_pokemones(personaje);
            if (cambiar_pokemones(personaje) == ERROR){
                system("clear");
                mostrar_informe("Error al cambiar pokemones de batalla.");
                frenar_ejecucion_para_luego_seguir();
            }
            break;
        
        case REINTENTAR_BATALLA:
            *perdio_batalla = false;
            *permanecer_en_menu_derrota = false;
            break;
        
        case FINALIZAR_PARTIDA:
            *permanecer_en_menu_gimnasio = false;
            *permanecer_en_menu_derrota = false;
            break;
        
        default:
            mostrar_informe("Error, caracter ingresado invalido.");
            frenar_ejecucion_para_luego_seguir();
            break;
    }
}

/*
 * Se encarga del flujo de batalla de cada gimnasio.
 * Recibe un puntero a gimnasio_t valido e inicializado, un puntero a personaje_t valido e inicializado,
 * y dos punteros a bool validos.
 * Devuelve interaccion e impresion por terminal.
 */
void batallar(gimnasio_t* gimnasio, personaje_t* personaje, bool* permanecer_en_menu_gimnasio,
    bool* gano_gimnasio){
    
    entrenador_t* entrenador = (entrenador_t*)lista_ultimo((*gimnasio).entrenadores);
    pokemon_t* pokemon_entrenador = NULL;
    pokemon_t* pokemon_personaje = NULL;
    bool perdio_batalla = false;
    bool gano_lider = false;
    char eleccion;
    size_t i;

    while (!perdio_batalla && entrenador && !gano_lider){

        i = 0;
        pokemon_personaje = (pokemon_t*)lista_elemento_en_posicion((*personaje).party, i);
        pokemon_entrenador = (pokemon_t*)lista_elemento_en_posicion((*entrenador).pokemones, i);

        while (!perdio_batalla && (pokemon_entrenador && pokemon_personaje)){
            system("clear");

            if (lista_elementos((*gimnasio).entrenadores) == 1)
                printf("\t\t¡HORA DE PELEAR CON EL LIDER!");

            menu_de_batalla(personaje, entrenador, pokemon_personaje, pokemon_entrenador);
            
            if ((*gimnasio).funcion_de_batalla(pokemon_personaje, pokemon_entrenador) > 0){
                
                mostrar_ganador((*personaje).nombre, (*pokemon_personaje).nombre);
                boostear_pokemon(personaje, i);

                printf("\n\t[N] » Proximo combate. ");
                while (leer_input(&eleccion, CARACTER) == ERROR)
                    printf("Ingreselo denuevo: ");
                while (eleccion != PROXIMO_COMBATE){
                    printf("\tIngreselo denuevo: ");
                    while (leer_input(&eleccion, CARACTER) == ERROR)
                        printf("Ingreselo denuevo: ");
                }

                i++;
                pokemon_personaje = (pokemon_t*)lista_elemento_en_posicion((*personaje).party, i);
                pokemon_entrenador = (pokemon_t*)lista_elemento_en_posicion((*entrenador).pokemones, i);
            }
            else {
                mostrar_ganador((*entrenador).nombre, (*pokemon_entrenador).nombre);
                printf("\n");
                frenar_ejecucion_para_luego_seguir();
                perdio_batalla = true;
            }
        }
        
        if (perdio_batalla){
            bool permanecer_en_menu_derrota = true;
            while (permanecer_en_menu_derrota){
                system("clear");
                menu_de_derrota();
                while(leer_input(&eleccion, CARACTER) == ERROR)
                    printf("\tIngreselo denuevo: ");
                interactuar_menu_derrota(eleccion, personaje, permanecer_en_menu_gimnasio, &perdio_batalla, &permanecer_en_menu_derrota);
            }
        }
        else {
            if (lista_elementos((*gimnasio).entrenadores) > 1){
                lista_borrar((*gimnasio).entrenadores);
                entrenador = (entrenador_t*)lista_ultimo((*gimnasio).entrenadores);
            }
            else {
                gano_lider = true;
                *gano_gimnasio = true;
            }
        }
    }
}

/*
 * Le muestra al usuario el menu de gimnasio para que éste decida que hacer.
 * Recibe un puntero a gimnasio_t valido e inicializadom un puntero a personaje_t valido e inicializado,
 * y dos punteros a bool validos.
 * Devuelve interaccion e impresion por terminal.
 */
void interactuar_menu_gimnasio(gimnasio_t* gimnasio, personaje_t* personaje, char eleccion, bool* permanecer_en_menu_gimnasio,
    bool* gano_gimnasio){

    system("clear");

    switch(eleccion){

        case MOSTRAR_PERSONAJE:
            mostrar_personaje_con_pokemones(personaje);
            frenar_ejecucion_para_luego_seguir();
            break;
        
        case MOSTRAR_GIMNASIO:
            mostrar_gimnasio(gimnasio);
            break;
        
        case CAMBIAR_POKEMONES:
            mostrar_personaje_con_pokemones(personaje);
            if (cambiar_pokemones(personaje) == ERROR){
                system("clear");
                mostrar_informe("Error al cambiar pokemones de batalla.");
                frenar_ejecucion_para_luego_seguir();
            }
            break;
        
        case PROXIMA_BATALLA:
            batallar(gimnasio, personaje, permanecer_en_menu_gimnasio, gano_gimnasio);
            break;
        
        case SALIR:
            *permanecer_en_menu_gimnasio = false;
            break;

        default:
            mostrar_informe("Error, caracter ingresado invalido.");
            frenar_ejecucion_para_luego_seguir();
            break;
    }
}

/*
 * Le permite al usuario tomar un pokemon del lider del gimnasio.
 * Recibe un puntero a entrenador_t valido e inicializado y un puntero a personaje_t valido e inicializado.
 * Devuelve 0 si pudo tomar el pokemon, o -1 si no pudo.
 */
int tomar_pokemon_del_lider(entrenador_t* lider, personaje_t* personaje){

    size_t posicion;
    pokemon_t* pokemon_a_tomar = NULL;
    pokemon_t* pokemon_a_insertar = NULL;

    mostrar_entrenador_con_pokemones(lider, ES_LIDER);
    printf("Ingrese la posicion del pokemon que desea tomar: ");
    while (leer_input(&posicion, NATURAL) == ERROR)
        printf("\tIngreselo denuevo: ");

    while (posicion >= lista_elementos((*lider).pokemones)){
        printf("Ingreselo denuevo: ");
        while (leer_input(&posicion, NATURAL) == ERROR)
            printf("\tIngreselo denuevo: ");
    }

    pokemon_a_tomar = (pokemon_t*)lista_elemento_en_posicion((*lider).pokemones, posicion);
    if (!pokemon_a_tomar) return ERROR;

    pokemon_a_insertar = crear_pokemon_copiado(pokemon_a_tomar);
    if (!pokemon_a_insertar) return ERROR;

    if (lista_insertar((*personaje).caja, pokemon_a_insertar) == ERROR){
        free(pokemon_a_insertar);
        return ERROR;
    }
    if (lista_elementos((*personaje).party) < MAX_POKEMONES_BATALLA){
        pokemon_t* pokemon_a_insertar2 = crear_pokemon_copiado(pokemon_a_tomar);
        if (!pokemon_a_insertar2){
            if (lista_borrar((*personaje).caja) == ERROR)
                return ERROR;
        }
        if (lista_insertar((*personaje).party, pokemon_a_insertar2) == ERROR){
            free(pokemon_a_insertar2);
            if (lista_borrar((*personaje).caja) == ERROR)
                return ERROR;
        }
    }

    return EXITO;
}

/*
 * Le muestra el menu de victoria al usuario para que este decida que hacer.
 * Recibe un caracter inicializado, dos punteros a bool validos, un puntero a gimnasio_t valido e inicializado,
 * y un puntero a personaje_t valido e inicializado.
 * Devuelve interaccion e impresion por terminal.
 */
void interactuar_menu_victoria(char eleccion, bool* permanecer_en_menu_victoria, gimnasio_t* gimnasio, personaje_t* personaje,
    bool* tiene_pokemon_lider){

    entrenador_t* lider = (entrenador_t*)lista_ultimo((*gimnasio).entrenadores);
    system("clear");

    switch(eleccion){
        case TOMAR_POKEMON_LIDER:
            if (*tiene_pokemon_lider){
                mostrar_informe("Ya tiene un pokemon del lider.");
                frenar_ejecucion_para_luego_seguir();
            }
            else {
                if (tomar_pokemon_del_lider(lider, personaje) == ERROR){
                    system("clear");
                    mostrar_informe("Error al tomar pokemon del lider.");
                    frenar_ejecucion_para_luego_seguir();
                }
                *tiene_pokemon_lider = true;
            }
            break;
        case CAMBIAR_POKEMONES:
            mostrar_personaje_con_pokemones(personaje);
            if (cambiar_pokemones(personaje) == ERROR){
                system("clear");
                mostrar_informe("Error al cambiar pokemones de batalla.");
                frenar_ejecucion_para_luego_seguir();
            }
            break;
        case PROXIMO_GIMNASIO:
            *permanecer_en_menu_victoria = false;
            break;
        default:
            mostrar_informe("Error, caracter ingresado invalido.");
            frenar_ejecucion_para_luego_seguir();
    }
}

/*
 * Se encarga de jugar la partida hasta que se decida dejar de jugar o
 * no haya gimnasios que enfrentar.
 * Recibe un puntero a juego_t valido e inicializado.
 * Devuelve la jugabilidad completa de la partida.
 */
void jugar_partida(juego_t* juego){

    char eleccion;
    bool permanecer_en_menu_gimnasio = true;
    bool gano_gimnasio = false;
    bool tiene_pokemon_lider = false;

    gimnasio_t* gimnasio = (gimnasio_t*)heap_extraer_raiz((*juego).gimnasios);
    if (!gimnasio) return;

    while (permanecer_en_menu_gimnasio){

        system("clear");
        menu_de_gimnasio();
        while (leer_input(&eleccion, CARACTER) == ERROR)
            printf("\tIngreselo denuevo: ");
        interactuar_menu_gimnasio(gimnasio, (*juego).personaje, eleccion, &permanecer_en_menu_gimnasio, &gano_gimnasio);

        if (gano_gimnasio){
            bool permanecer_en_menu_victoria = true;
            while (permanecer_en_menu_victoria){
                system("clear");
                menu_de_victoria();
                while (leer_input(&eleccion, CARACTER) == ERROR)
                    printf("\tIngreselo denuevo: ");
                interactuar_menu_victoria(eleccion, &permanecer_en_menu_victoria, gimnasio, (*juego).personaje, &tiene_pokemon_lider);
            }
            permanecer_en_menu_victoria = false;
            tiene_pokemon_lider = false;
            
            destruir_gimnasio(gimnasio);
            gimnasio = (gimnasio_t*)heap_extraer_raiz((*juego).gimnasios);
            
            if (gimnasio){
                gano_gimnasio = false;
            }
            else {
                permanecer_en_menu_gimnasio = false;
            }
        }
    }

    if (heap_vacio((*juego).gimnasios) && gano_gimnasio){
        system("clear");
        mostrar_mensaje_maestro_pokemon((*(*juego).personaje).nombre);
        frenar_ejecucion_para_luego_seguir();
    }

    if (gimnasio) destruir_gimnasio(gimnasio);
}

/*
 * Se encarga de la simulacion del juego. Para que este sea ejecutada debe
 * haberse cargado el archivo del jugador y de los gimnasios.
 * Recibe un puntero valido a juego_t
 * Devuelve interaccion con el usuario e impresion por terminal.
 */
void simular_partida(juego_t* juego){
    
    gimnasio_t* gimnasio = NULL;
    entrenador_t* entrenador = NULL;
    pokemon_t* pokemon_personaje = NULL;
    pokemon_t* pokemon_entrenador = NULL;
    bool seguir_jugando = true;
    bool gano_gimnasio = false;
    size_t i = 0;
    char eleccion;

    while (seguir_jugando){
        gimnasio = (gimnasio_t*)heap_extraer_raiz((*juego).gimnasios);
        if (!gimnasio){
            seguir_jugando = false;
            gano_gimnasio = true;
        }
        while (gimnasio && seguir_jugando){
            entrenador = (entrenador_t*)lista_ultimo((*gimnasio).entrenadores);
            
            while(entrenador && seguir_jugando){
                pokemon_entrenador = (pokemon_t*)lista_elemento_en_posicion((*entrenador).pokemones, i);
                pokemon_personaje = (pokemon_t*)lista_elemento_en_posicion((*(*juego).personaje).party, i);

                while ((pokemon_personaje && pokemon_entrenador) && seguir_jugando){
                    system("clear");
                    
                    mostrar_info_gimnasio(gimnasio, EN_SIMULACION);
                    
                    if (lista_elementos((*gimnasio).entrenadores) == 1)
                        printf("\t\t¡HORA DE PELEAR CON EL LIDER!");

                    menu_de_batalla((*juego).personaje, entrenador, pokemon_personaje, pokemon_entrenador);
                    
                    if ((*gimnasio).funcion_de_batalla(pokemon_personaje, pokemon_entrenador) > 0){
                        mostrar_ganador((*(*juego).personaje).nombre, (*pokemon_personaje).nombre);
                        printf("\n\t[N] » Proximo combate. ");
                        while (leer_input(&eleccion, CARACTER) == ERROR)
                            printf("\tIngreselo denuevo: ");
                        while (eleccion != PROXIMO_COMBATE){
                            printf("\tIngreselo denuevo: ");
                            while (leer_input(&eleccion, CARACTER) == ERROR)
                                printf("\tIngreselo denuevo: ");
                        }
                        i++;
                        pokemon_entrenador = (pokemon_t*)lista_elemento_en_posicion((*entrenador).pokemones, i);
                        pokemon_personaje = (pokemon_t*)lista_elemento_en_posicion((*(*juego).personaje).party, i);
                    }
                    else {
                        mostrar_ganador((*entrenador).nombre, (*pokemon_entrenador).nombre);
                        printf("\n");
                        frenar_ejecucion_para_luego_seguir();
                        seguir_jugando = false;
                    }
                }
                lista_borrar((*gimnasio).entrenadores);
                entrenador = (entrenador_t*)lista_ultimo((*gimnasio).entrenadores);
                i = 0;
            }
            destruir_gimnasio(gimnasio);
            gimnasio = NULL;
        }
    }
    if (heap_vacio((*juego).gimnasios) && gano_gimnasio){
        system("clear");
        mostrar_mensaje_maestro_pokemon((*(*juego).personaje).nombre);
        frenar_ejecucion_para_luego_seguir();
    }
    if (gimnasio) destruir_gimnasio(gimnasio);
}

/*
 * Dependediendo del valor de 'eleccion' realizara una de las acciones
 * detalladas en el menu de inicio.
 * Recibe un puntero valido a juego_t, un caracter y un puntero a bool valido.
 * Devuelve interaccion con el usuario e impresion por terminal.
 */
void interactuar_menu_inicio(juego_t* juego, char eleccion, bool* permanecer_en_menu_inicio){

    char ruta_archivo[MAX_RUTA], eleccion_aux;

    system("clear");

    switch(eleccion){

        case CARGAR_PERSONAJE:
            if ((*juego).personaje){
                mostrar_informe("Ya hay un personaje cargado.");
                frenar_ejecucion_para_luego_seguir();
            }
            else {
                (*juego).personaje = crear_personaje();
                if (!(*juego).personaje){
                    mostrar_informe("Error al cargar personaje.");
                    frenar_ejecucion_para_luego_seguir();
                    return;
                }
                consultar_ruta_archivo(ruta_archivo);
                if (cargar_personaje((*juego).personaje, ruta_archivo) == ERROR){
                    destruir_personaje((*juego).personaje);
                    (*juego).personaje = NULL;
                    system("clear");
                    mostrar_informe("Error al cargar personaje.");
                    frenar_ejecucion_para_luego_seguir();
                }
            }
            break;

        case CARGAR_GIMNASIO:
            mostrar_informe("ATENCION: si tiene gimnasios cargados y hay un error, seran borrados.");
            frenar_ejecucion_para_luego_seguir();
            if (!(*juego).gimnasios){
                (*juego).gimnasios = heap_crear(comparar_gimnasios, destruir_gimnasio);
                if (!(*juego).gimnasios){
                    system("clear");
                    mostrar_informe("Error al cargar gimnasio/s.");
                    frenar_ejecucion_para_luego_seguir();
                    break;
                }
            }
            system("clear");
            consultar_ruta_archivo(ruta_archivo);
            if (cargar_gimnasio((*juego).gimnasios, ruta_archivo) == ERROR){
                heap_destruir((*juego).gimnasios);
                (*juego).gimnasios = NULL;
                system("clear");
                mostrar_informe("Error al cargar gimnasio/s.");
                frenar_ejecucion_para_luego_seguir();
                /*¿Por qué hago esto? porque yo le digo al usuario que hubo un error pero
                puede ser que se hayan cargado, por ejemplo, 2 de 5 gimnnasios que habia
                en el archivo, pero eso significa que no hubo 100% error. Por lo tanto
                prefiero borrar todo asi soy consistente con el informe de error.*/
            }
            break;

        case COMENZAR_PARTIDA:
            if (!(*juego).gimnasios && !(*juego).personaje){
                mostrar_informe("No se puede iniciar la partida sin gimnasio/s ni personaje.");
                frenar_ejecucion_para_luego_seguir();
            }
            else if (!(*juego).gimnasios){
                mostrar_informe("No se puede iniciar la partida sin gimnasio/s.");
                frenar_ejecucion_para_luego_seguir();
            }
            else if (!(*juego).personaje){
                mostrar_informe("No se puede iniciar la partida sin personaje.");
                frenar_ejecucion_para_luego_seguir();
            }
            else {
                jugar_partida(juego);
                *permanecer_en_menu_inicio = false;
            }
            break;

        case SIMULAR_PARTIDA:
            if (!(*juego).gimnasios && !(*juego).personaje){
                mostrar_informe("No se puede simular la partida sin gimnasio/s ni personaje.");
                frenar_ejecucion_para_luego_seguir();
            }
            else if (!(*juego).gimnasios){
                mostrar_informe("No se puede simular la partida sin gimnasio/s.");
                frenar_ejecucion_para_luego_seguir();
            }
            else if (!(*juego).personaje){
                mostrar_informe("No se puede simular la partida sin personaje.");
                frenar_ejecucion_para_luego_seguir();
            }
            else {
                mostrar_informe("ATENCION: una vez terminada la simulacion se borraran los gimnasios.");
                printf("\t\t¿Desea continuar con la simulacion?\n");
                printf("\t\t[S] » Si / [N] » No ");
                while (leer_input(&eleccion_aux, CARACTER) == ERROR)
                    printf("Ingreselo denuevo: ");
                while (eleccion_aux != SI && eleccion_aux != NO){
                    printf("Ingreselo denuevo: ");
                    while (leer_input(&eleccion_aux, CARACTER) == ERROR)
                        printf("Ingreselo denuevo: ");
                }
                if (eleccion_aux == SI){
                    simular_partida(juego);
                    heap_destruir((*juego).gimnasios);
                    (*juego).gimnasios = NULL;
                }
            }
            break;

        case SALIR:
            *permanecer_en_menu_inicio = false;
            break;

        default:
            mostrar_informe("ERROR, caracter ingresado invalido.");
            frenar_ejecucion_para_luego_seguir();
            break;
    }
}

/*
 * Se encarga de interactuar con el usuario mediante el menú de inicio, de lo cual
 * van a derivar los siguientes menúes (gimnasio, batalla, victoria, derrota). Carga
 * todos los datos para el correcto funcionamiento del juego. También se hace cargo
 * del flujo del juego.
 * Devuelve interaccion con el usuario e impresion por terminal.
 */
void interactuar_con_usuario(){

    juego_t juego;
    juego.gimnasios = NULL;
    juego.personaje = NULL;
    
    char eleccion;
    bool permanecer_en_menu_inicio = true;

    while (permanecer_en_menu_inicio){
        
        system("clear");
        menu_de_inicio();
        while (leer_input(&eleccion, CARACTER) == ERROR)
            printf("\tIngreselo denuevo: ");
        interactuar_menu_inicio(&juego, eleccion, &permanecer_en_menu_inicio);
    }

    if (juego.gimnasios) heap_destruir(juego.gimnasios);
    if (juego.personaje) destruir_personaje(juego.personaje);
}

int main(){

    presentacion();
    interactuar_con_usuario();

    return 0;
}