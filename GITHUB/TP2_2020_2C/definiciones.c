
#include "definiciones.h"

// FUNCIÓN PÚBLICA
void destructor_pokemones(void* pokemon) {
    free(pokemon);
}

// FUNCIÓN PÚBLICA
void destructor_entrenadores(void* entrenador) {
    if (!entrenador) return;
    if ( ((entrenador_t*)entrenador)->party ) {
        lista_destruir(((entrenador_t*)entrenador)->party);
    }
    free(entrenador); // Una vez que está vacía la cola de pokemones, se libera el entrenador.
}

// FUNCIÓN PÚBLICA
void destructor_gimnasios(void* gimnasio) {
    if (!gimnasio) return;
    if (((gimnasio_t*)gimnasio)->entrenadores)
        lista_destruir(((gimnasio_t*)gimnasio)->entrenadores);    // Llamo a lista_destruir(gimnasio->entrenadores) y esa función se encarga de todo
    free(gimnasio);
}

// FUNCIÓN PÚBLICA
void personaje_destruir(personaje_t* personaje) {
    if(!personaje) return;
    lista_destruir(personaje->caja);
    lista_destruir(personaje->party);
    free(personaje);
}


/*
* Pre: -
* Post: Compara los gimnasios recibidos por dificultad.
*/
int comparador_gimnasios (void* g1, void* g2) {
    if (!g1 && !g2) return IGUAL;
    if (!g1) return MENOR;
    if (!g2) return MAYOR;

    gimnasio_t gimnasio1 = *(gimnasio_t*)g1;
    gimnasio_t gimnasio2 = *(gimnasio_t*)g2;
    if (gimnasio1.dificultad < gimnasio2.dificultad)
        return MENOR;
    
    if (gimnasio1.dificultad > gimnasio2.dificultad)
        return MAYOR;

    return IGUAL;
}


/*
* Pre: El archivo debe ser válido y estar abierto en modo LECTURA. tam_memoria debe ser el tamaño del
    buffer recibido.
* Post: Lee el primer caracter de la línea del archivo recibido, con el FORMATO_GENERAL y lo almacena en tipo_lectura. Luego, 
    lee el resto de la línea y lo devuelve. En caso de error se devuelve NULL. tam_memoria es el tamaño de lo que leerá.
*/
char* leer_linea(char buffer[100], size_t tam_memoria, FILE* archivo, char* tipo_lectura, bool* hay_error) {
    char* linea = fgets(buffer, (int)tam_memoria, archivo);
    if (!linea)
        return NULL;

    int leidos = sscanf(buffer, FORMATO_GENERAL, tipo_lectura, linea); // Leo un caracter y el resto lo dejo en buffer
    if (leidos != 2) {
        (*hay_error) = true;
        return NULL;
    }

    return linea;
}

/*
* Pre: El gimnasio recibido debe ser válido. buffer debe ser una línea del archivo de gimnasios 
    con el FORMATO_GIMNASIO.
* Post: Asigna los campos correspondientes al gimnasio recibido, y devuelve la cantidad
    de campos leidos del buffer (debería devolver CAMPOS_GIMNASIO, en otro caso hubo error).
*/
int asignar_campos_gimnasio(gimnasio_t* gimnasio, char* buffer) {
    int leidos = sscanf(buffer, FORMATO_GIMNASIO, gimnasio->nombre, 
        &(gimnasio->dificultad), &(gimnasio->tipo_batalla));
    return leidos;
}

/*
* Pre: El entrenador recibido debe ser válido. linea debe ser una línea del archivo de gimnasios 
    con el FORMATO_ENTREANDOR.
* Post: Asigna los campos correspondientes al entrenador recibido, y devuelve la cantidad
    de campos leidos de la línea (debería devolver CAMPOS_ENTRENADOR, en otro caso hubo error).
*/
int asignar_campos_entrenador(entrenador_t* entrenador, char* linea, char tipo_lectura, bool pila_vacia) {
    int leidos = sscanf(linea, FORMATO_ENTRENADOR, entrenador->nombre);
    if (tipo_lectura == LIDER && pila_vacia)
        entrenador->es_lider = true;
    else
        entrenador->es_lider = false;
    return leidos;
}

/*
* Pre: El pokemon debe ser válido, y el buffer es la línea del archivo de gimnasios/personaje 
    con el FORMATO_POKEMON.
* Post: Asigna los campos correspondientes al pokemon recibido, y devuelve la cantidad
    de campos leidos del buffer (debería devolver CAMPOS_POKEMON, en otro caso hubo error).
*/
int asignar_campos_pokemon(pokemon_t* pokemon, char* buffer) {
    int leidos = sscanf(buffer, FORMATO_POKEMON, pokemon->nombre, &(pokemon->velocidad), 
        &(pokemon->defensa), &(pokemon->ataque));

    return leidos;
}

/*
* Pre: El personaje debe ser válido, y el buffer es la línea del archivo de personaje con el
    FORMATO_PERSONAJE.
* Post:
*/
int asignar_campos_personaje(personaje_t* personaje, char* buffer) {
    int leidos = sscanf(buffer, FORMATO_PERSONAJE, personaje->nombre);
    return leidos;
}

/*
* Pre: -
* Post: Carga un personaje del archivo de personajes con la ruta recibida y lo devuelve. En caso
    de error devuelve NULL.
*/
personaje_t* cargar_personaje(char ruta[MAX_RUTA]) {
    if (!ruta) return NULL;

    FILE* archivo_personaje = fopen(ruta, LECTURA);
    if (!archivo_personaje) return NULL;

    personaje_t* personaje = calloc(1, sizeof(personaje_t));
    if (!personaje) return NULL;

    char buffer[LIMITE_BUFFER]; // Supongo que no va a haber algo mayor
    char tipo_lectura;
    bool hay_error = false;
    
    char* linea = leer_linea(buffer, LIMITE_BUFFER, archivo_personaje, &tipo_lectura, &hay_error); // Leo el personaje
    if (!linea || hay_error || tipo_lectura != ENTRENADOR) {
        return NULL;
        free(personaje);
    }
    if (asignar_campos_personaje(personaje, linea) != CAMPOS_PERSONAJE) {
        free(personaje);
        return NULL;
    }

    lista_t* party = lista_crear(destructor_pokemones); // Lista de pokemones de combate
    lista_t* caja = lista_crear(destructor_pokemones); // Lista de pokemones obtenidos
    linea = leer_linea(buffer, LIMITE_BUFFER, archivo_personaje, &tipo_lectura, &hay_error); // Leo el primer pokémon
    if (!linea || hay_error || !party || !caja)  {
        fclose(archivo_personaje);
        lista_destruir(party);
        lista_destruir(caja);
        free(personaje);
        return NULL;
    }
    // Reservo memoria distinta para los pokemones de la caja y los de la party.
    //   para evitar errores con los destructores.
    pokemon_t* pokemon_caja = NULL;
    pokemon_t* pokemon_party = NULL;
    while(linea && !hay_error && tipo_lectura == POKEMON) {  
        bool se_asigno = true; // Si se asignaron correctamente los campos del pokémon.
        pokemon_caja = calloc(1, sizeof(pokemon_t));
        if (pokemon_caja) {
            if (asignar_campos_pokemon(pokemon_caja, linea) != CAMPOS_POKEMON) {
                free(pokemon_caja); // Libero el pokémon actual y sigo con el siguiente
                se_asigno = false;
            } else {
                if (personaje->cant_pokemon < MAX_POKEMONES_BATALLA) {
                    pokemon_party = calloc(1, sizeof(pokemon_t));
                    if (pokemon_party) {
                        if (asignar_campos_pokemon(pokemon_party, linea) == CAMPOS_POKEMON) {
                            if (lista_insertar(party, pokemon_party) == ERROR) // Inserto en la party si tengo < 6
                                hay_error = true;  
                        } else {
                            free(pokemon_party);
                            free(pokemon_caja); // Libero el pokémon actual y sigo con el siguiente
                            se_asigno = false;
                        }
                    } else {
                        hay_error = true;
                    }
                }
                if (se_asigno && !hay_error && lista_insertar(caja, pokemon_caja) == ERROR) // Inserto siempre en la caja
                    hay_error = true;
                else if (se_asigno && !hay_error)
                    (personaje->cant_pokemon)++;
            }
            linea = leer_linea(buffer, LIMITE_BUFFER, archivo_personaje, &tipo_lectura, &hay_error);
        } else {
            hay_error = true;
        }
    }
    if (hay_error || lista_vacia(party))  {
        fclose(archivo_personaje);
        destructor_pokemones(pokemon_party);
        destructor_pokemones(pokemon_caja);
        lista_destruir(party);
        lista_destruir(caja);
        free(personaje);
        return NULL;
    }

    personaje->party = party;
    personaje->caja = caja;    
    
    fclose(archivo_personaje);

    return personaje;
}


/*
* Pre: La ruta debe ser una ruta de gimnaio válida, al igual que el heap.
* Post: Carga uno o más gimnasios del archivo con la ruta recibida en el heap
    de gimnasios. Devuelve ERROR si hay algún problema o EXITO si se pudo
    cargar el gimnasio.
*/
int cargar_gimnasio(heap_t* heap_gimnasios, char ruta[MAX_RUTA]) {
    if (!heap_gimnasios || !ruta) return ERROR;

    FILE* archivo_gimnasios = fopen(ruta, LECTURA);
    if (!archivo_gimnasios) return ERROR;

    char buffer[LIMITE_BUFFER]; // Supongo que no va a haber algo mayor
    char tipo_lectura;
    bool hay_error = false;
    char* linea = leer_linea(buffer, LIMITE_BUFFER, archivo_gimnasios, &tipo_lectura, &hay_error);
    if (!linea || hay_error) {
        fclose(archivo_gimnasios);
        return ERROR;
    }

    gimnasio_t* gimnasio_actual = NULL;

    while(linea && !hay_error) { // Si termina el archivo o lee mal, linea es NULL
        if (tipo_lectura == GIMNASIO) {
            gimnasio_actual = calloc(1, sizeof(gimnasio_t));
            if (!gimnasio_actual) hay_error = true;

            if (!hay_error && asignar_campos_gimnasio(gimnasio_actual, linea) == CAMPOS_GIMNASIO) {
                lista_t* pila_entrenadores = lista_crear(destructor_entrenadores);
                if (!pila_entrenadores) hay_error = true;
                else gimnasio_actual->entrenadores = pila_entrenadores;

                linea = leer_linea(buffer, LIMITE_BUFFER, archivo_gimnasios, &tipo_lectura, &hay_error);
                if (!linea) {
                    hay_error = true;
                }

                while(linea && !hay_error && (tipo_lectura == ENTRENADOR || tipo_lectura == LIDER)) {

                    entrenador_t* entrenador_actual = calloc(1, sizeof(entrenador_t));
                    if (!entrenador_actual) hay_error = true;

                    if (!hay_error && asignar_campos_entrenador(entrenador_actual, linea, tipo_lectura, lista_vacia(pila_entrenadores)) == CAMPOS_ENTRENADOR) {
                        lista_t* lista_pokemones = lista_crear(destructor_pokemones);
                        if (!lista_pokemones) hay_error = true;
                        else entrenador_actual->party = lista_pokemones;

                        linea = leer_linea(buffer, LIMITE_BUFFER, archivo_gimnasios, &tipo_lectura, &hay_error);
                        if (!linea || hay_error) {
                            destructor_entrenadores(entrenador_actual);
                            hay_error = true;
                        }

                        while(linea && !hay_error && tipo_lectura == POKEMON) {

                            pokemon_t* pokemon_actual = calloc(1, sizeof(pokemon_t));
                            if (!pokemon_actual) {
                                destructor_entrenadores(entrenador_actual); // Todavía no fue apilado
                                hay_error = true;
                            } else {
                                if (asignar_campos_pokemon(pokemon_actual, linea) != CAMPOS_POKEMON) {
                                    destructor_pokemones(pokemon_actual);
                                    // Libero solo el pokemon y sigo leyendo, aprovechando el resto de los pokemones si están bien formateados.
                                } else if (entrenador_actual->cant_pokemon < MAX_POKEMONES_BATALLA) {
                                        lista_insertar(lista_pokemones, pokemon_actual);
                                        // Error insertar
                                        (entrenador_actual->cant_pokemon)++;
                                } else { // Ya tiene 6 pokemones
                                    destructor_pokemones(pokemon_actual);
                                }
                            }
                            linea = leer_linea(buffer, LIMITE_BUFFER, archivo_gimnasios, &tipo_lectura, &hay_error);
                        }

                        if (!lista_vacia(lista_pokemones) && !hay_error)
                            lista_apilar(pila_entrenadores, entrenador_actual); 
                        else    
                            destructor_entrenadores(entrenador_actual);
                    } else {
                        destructor_entrenadores(entrenador_actual);
                        hay_error = true;
                    }
                }

                if (lista_vacia(pila_entrenadores)) // El gimnasio no tiene entrenadores
                    hay_error = true;
            } else {
                hay_error = true;
            }

            if(!hay_error) {
                if (heap_insertar(heap_gimnasios, gimnasio_actual) == ERROR)
                    hay_error = true;
            }

            if (hay_error)
                destructor_gimnasios(gimnasio_actual);
        } else { // TIPO_LECTURA != GIMNASIO
            hay_error = true; // Error en el formato del archivo
        }
    }

    fclose(archivo_gimnasios);
    
    if (hay_error) {
        return ERROR;
    }
    return EXITO;
}