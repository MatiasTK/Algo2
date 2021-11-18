#include "aventura.h"

int leer_input(void* variable, char tipo_variable){
    
    char lectura[MAX_LINEA];
    char* linea_leida = fgets(lectura, MAX_LINEA, stdin);
    if (!linea_leida) return ERROR;

    size_t tam_lectura = strlen(lectura);
    if (tam_lectura == 0) return ERROR;

    if (lectura[tam_lectura-1] != '\n')
        leer_input(variable, tipo_variable);
    
    lectura[tam_lectura-1] = 0;

    switch (tipo_variable){
        case NATURAL:
            *(size_t*)variable = strtoul(lectura, NULL, 10);
            break;
        case ENTERO:
            *(int*)variable = atoi(lectura);
            break;
        case RACIONAL:
            *(float*)variable = strtof(lectura, NULL);
            break;
        case CARACTER:
            *(char*)variable = *lectura;
            break;
        case STRING:
            strcpy((char*)variable, lectura);
            break;
        default:
            return ERROR;
    }

    return EXITO;
}

/*
 * Lee una linea del archivo que recibe.
 * Recibe un archivo abierto, un puntero a string, un entero inicializado y un puntero a caracter valido.
 * Devuelve una parte de la linea leida o NULL en caso de error.
 */
char* leer_linea(FILE* archivo, char* buffer, int tam_buffer, char* tipo){
    char* linea = fgets(buffer, tam_buffer, archivo);
    if (linea){
        if (sscanf(linea, FORMATO_INCIAL, tipo, buffer) == DATOS_INICIALES)
            return buffer;
    }
    return NULL;
}

/*
 * Lee los datos del gimnasio que recibe del buffer.
 * Recibe un puntero a string valido inicializado, un vector y punteros a enteros validos.
 * Devuelve la cantidad de elementos que pudo leer.
 */
int leer_gimnasio(char* buffer, char nombre[MAX_NOMBRE], int* dificultad, int* id_funcion){
    return sscanf(buffer, FORMATO_GIMNASIO, nombre, dificultad, id_funcion);
}

/*
 * Lee los datos del entrenador que recibe del buffer.
 * Recibe un puntero a string valido inicializado y un vector.
 * Devuelve la cantidad de elementos que pudo leer.
 */
int leer_entrenador(char* buffer, char nombre[MAX_NOMBRE]){
    int leidos = sscanf(buffer, FORMATO_ENTRENADOR, nombre);
    if (leidos == DATOS_ENTRENADOR){
        size_t tam_nombre = strlen(nombre);
        if (tam_nombre > 0) nombre[tam_nombre-1] = 0; //para que no lea el '\n'
    }
    return leidos;
}

/*
 * Lee los datos del pokemon que recibe del buffer.
 * Recibe un puntero a string valido inicializado, un vector, y punteros a enteros validos.
 * Devuelve la cantidad de elementos que pudo leer.
 */
int leer_pokemon(char* buffer, char nombre[MAX_NOMBRE], int* velocidad, int* defensa, int* ataque){
    return sscanf(buffer, FORMATO_POKEMON, nombre, velocidad, defensa, ataque);
}

/* 
 * Libera la memoria reservada para el tipo de dato 'pokemon_t'.
 * Recibe un puntero valido a pokemon.
 * Devuelve la memoria utilizada liberada.
 */
void liberar_pokemon(pokemon_t* pokemon){
    free(pokemon);
}

void destruir_pokemon(void* pokemon){
    if (pokemon)
        liberar_pokemon((pokemon_t*)pokemon);
}

/* 
 * Libera la memoria reservada par el tipo de dato 'entrenador_t'.
 * Recibe un puntero valido a entrenador.
 * Devuelve la memoria utilizada liberada.
 */
void liberar_entrenador(entrenador_t* entrenador){
    if ((*entrenador).pokemones)
        lista_destruir((*entrenador).pokemones);
    
    free(entrenador);
}

void destruir_entrenador(void* entrenador){
    if (entrenador)
        liberar_entrenador((entrenador_t*)entrenador);
}

/* 
 * Libera la memoria reservada para el tipo de dato 'gimnasio_t'
 * Recibe un puntero valido a gimnasio.
 * Devuelve la memoria utilizada liberada.
 */
void liberar_gimnasio(gimnasio_t* gimnasio){
    
    if ((*gimnasio).entrenadores)
        lista_destruir((*gimnasio).entrenadores);

    free(gimnasio);
}


void destruir_gimnasio(void* gimnasio){
    if (gimnasio)
        liberar_gimnasio((gimnasio_t*)gimnasio);
}

/* 
 * Libera la memoria reservada para el tipo de dato 'personaje_t'
 * Recibe un puntero valido a personaje.
 * Devuelve la memoria utilizada liberada.
 */
void liberar_personaje(personaje_t* personaje){
    
    if ((*personaje).caja)
        lista_destruir((*personaje).caja);

    if ((*personaje).party)
        lista_destruir((*personaje).party);

    free(personaje);
}

void destruir_personaje(void* personaje){
    if (personaje)
        liberar_personaje((personaje_t*)personaje);
}

int comparar_gimnasios(void* gim1, void* gim2){
    if (!gim1 || !gim2) return 0;
    
    if ((*(gimnasio_t*)gim1).dificultad > (*(gimnasio_t*)gim2).dificultad)
        return 1;
    
    if ((*(gimnasio_t*)gim1).dificultad < (*(gimnasio_t*)gim2).dificultad)
        return -1;
    
    return 0;
}

gimnasio_t* crear_gimnasio(){
    gimnasio_t* gimnasio = malloc(sizeof(gimnasio_t));
    if (gimnasio){
        (*gimnasio).id_funcion = 0;
        (*gimnasio).dificultad = 0;
        (*gimnasio).entrenadores = NULL;
        (*gimnasio).funcion_de_batalla = NULL;
    }
    return gimnasio;
}

entrenador_t* crear_entrenador(){
    entrenador_t* entrenador = malloc(sizeof(entrenador_t));
    if (entrenador)
        (*entrenador).pokemones = NULL;
    return entrenador;
}

pokemon_t* crear_pokemon(){
    pokemon_t* pokemon = malloc(sizeof(pokemon_t));
    if (pokemon){
        (*pokemon).velocidad = 0;
        (*pokemon).defensa = 0;
        (*pokemon).ataque = 0;
    }
    return pokemon;
}

personaje_t* crear_personaje(){
    personaje_t* personaje = malloc(sizeof(personaje_t));
    if (personaje){
        (*personaje).caja = NULL;
        (*personaje).party = NULL;
    }
    return personaje;
}

/*
 * Inicializa el vector con las funciones de batalla.
 * Recibe un vector de tipo funcion_batalla.
 * Devuelve el vector inicializado.
 */
void definir_funciones_batalla(funcion_batalla funciones[MAX_FUNCIONES]){
    funciones[0] = funcion_batalla_1;
    funciones[1] = funcion_batalla_2;
    funciones[2] = funcion_batalla_3;
    funciones[3] = funcion_batalla_4;
    funciones[4] = funcion_batalla_5;
}

int cargar_gimnasio(heap_t* gimnasios, const char* arch_gimnasio){

    if (!gimnasios || !arch_gimnasio) return ERROR;

    FILE* archivo = fopen(arch_gimnasio, "r");
    if (!archivo) return ERROR;

    funcion_batalla funciones[MAX_FUNCIONES];
    definir_funciones_batalla(funciones);

    char lectura[MAX_LINEA], tipo;
    bool leyo_lider = false;

    char* leido = leer_linea(archivo, lectura, MAX_LINEA, &tipo);
    if (!leido){
        fclose(archivo);
        return ERROR;
    }
    while (leido){

        if (tipo != GIMNASIO){
            fclose(archivo);
            return ERROR;
            /* aclaracion: a este punto, en caso de hacer una 2da iteracion, toda la memoria
            reservada esta guardada en el heap, por eso solo cierro el archivo. En caso de error
            puedo liberar la memoria fuera de la funcion ya que las referencias estan guardadas. */
        }
        
        gimnasio_t* gimnasio = crear_gimnasio();
        if (!gimnasio){
            fclose(archivo);
            return ERROR;
        }
        
        lista_t* entrenadores = lista_crear(destruir_entrenador);
        if (!entrenadores){
            fclose(archivo);
            free(gimnasio);
            return ERROR;
        }
        if (leer_gimnasio(leido, (*gimnasio).nombre, &(*gimnasio).dificultad, &(*gimnasio).id_funcion) != DATOS_GIMNASIO){
            fclose(archivo);
            free(gimnasio);
            lista_destruir(entrenadores);
            return ERROR;
        }
        if ((*gimnasio).dificultad < 0){
            fclose(archivo);
            free(gimnasio);
            lista_destruir(entrenadores);
            return ERROR;
        }

        if ((*gimnasio).id_funcion < MAX_FUNCIONES && (*gimnasio).id_funcion >= 0){
            (*gimnasio).funcion_de_batalla = funciones[(*gimnasio).id_funcion];
        }
        else {
            fclose(archivo);
            free(gimnasio);
            lista_destruir(entrenadores);
            return ERROR;
        }

        leido = leer_linea(archivo, lectura, MAX_LINEA, &tipo);
        while (leido && (tipo == ENTRENADOR || tipo == LIDER)){

            if (tipo == LIDER && lista_vacia(entrenadores)){
                leyo_lider = true;
            }    

            entrenador_t* entrenador = crear_entrenador();
            if (!entrenador){
                fclose(archivo);
                free(gimnasio);
                lista_destruir(entrenadores);
                return ERROR;
            }

            lista_t* pokemones = lista_crear(destruir_pokemon);
            if (!pokemones){
                fclose(archivo);
                free(gimnasio);
                lista_destruir(entrenadores);
                free(entrenador);
                return ERROR;
            }

            if (leer_entrenador(leido, (*entrenador).nombre) != DATOS_ENTRENADOR){
                fclose(archivo);
                free(gimnasio);
                lista_destruir(entrenadores);
                free(entrenador);
                lista_destruir(pokemones);
                return ERROR;
            }
            leido = leer_linea(archivo, lectura, MAX_LINEA, &tipo);
            while (leido && tipo == POKEMON){
                pokemon_t* pokemon = crear_pokemon();
                if (!pokemon){
                    fclose(archivo);
                    free(gimnasio);
                    lista_destruir(entrenadores);
                    free(entrenador);
                    lista_destruir(pokemones);
                    return ERROR;
                }

                if (leer_pokemon(leido, (*pokemon).nombre, &(*pokemon).velocidad, &(*pokemon).defensa,
                    &(*pokemon).ataque) != DATOS_POKEMON){
                        
                    fclose(archivo);
                    free(gimnasio);
                    lista_destruir(entrenadores);
                    free(entrenador);
                    lista_destruir(pokemones);
                    free(pokemon);
                    return ERROR;
                }
                if (lista_insertar(pokemones, pokemon) == ERROR){
                    fclose(archivo);
                    free(gimnasio);
                    lista_destruir(entrenadores);
                    free(entrenador);
                    lista_destruir(pokemones);
                    free(pokemon);
                    return ERROR;
                }

                if (lista_elementos(pokemones) == MAX_POKEMONES_BATALLA){
                    while (leido && tipo == POKEMON)
                        leido = leer_linea(archivo, lectura, MAX_LINEA, &tipo);
                    //un entrenador o lider no puede tener mas pokemones de pelea que el personaje principal
                }
                else {
                    leido = leer_linea(archivo, lectura, MAX_LINEA, &tipo);
                }
            }
            if (lista_vacia(pokemones)){
                fclose(archivo);
                free(gimnasio);
                lista_destruir(entrenadores);
                free(entrenador);
                lista_destruir(pokemones);
                return ERROR;
            }
            (*entrenador).pokemones = pokemones;
            if (lista_insertar(entrenadores, entrenador) == ERROR){
                fclose(archivo);
                free(gimnasio);
                lista_destruir(entrenadores);
                free(entrenador);
                lista_destruir(pokemones);
                return ERROR;
            }
        }
        if (!leyo_lider){
            fclose(archivo);
            free(gimnasio);
            lista_destruir(entrenadores);
            return ERROR;
        }
        if (lista_vacia(entrenadores) || lista_elementos(entrenadores) < MIN_ENTRENADORES){
            fclose(archivo);
            free(gimnasio);
            lista_destruir(entrenadores);
            return ERROR;
        }
        (*gimnasio).entrenadores = entrenadores;
        if (heap_insertar(gimnasios, gimnasio) == ERROR){
            fclose(archivo);
            free(gimnasio);
            lista_destruir(entrenadores);
            return ERROR;
        }
        leyo_lider = false; //por si lee un nuevo gimnasio
    }

    fclose(archivo);
    return EXITO;
}

int cargar_personaje(personaje_t* personaje, const char* arch_personaje){
    
    if (!personaje || !arch_personaje) return ERROR;

    FILE* archivo = fopen(arch_personaje, "r");
    if (!archivo) return ERROR;

    char lectura[MAX_LINEA], tipo;

    char* leido = leer_linea(archivo, lectura, MAX_LINEA, &tipo);
    if (!leido){
        fclose(archivo);
        return ERROR;
    }
    else {

        if (tipo != ENTRENADOR){
            fclose(archivo);
            return ERROR;
        }

        if (leer_entrenador(leido, (*personaje).nombre) != DATOS_ENTRENADOR){
            fclose(archivo);
            return ERROR;
        }

        lista_t* caja = lista_crear(destruir_pokemon);
        if (!caja){
            fclose(archivo);
            return ERROR;
        }

        lista_t* party = lista_crear(destruir_pokemon);
        if (!party){
            fclose(archivo);
            lista_destruir(caja);
            return ERROR;
        }

        int i = 0;
        leido = leer_linea(archivo, lectura, MAX_LINEA, &tipo);
        while (leido && tipo == POKEMON){
            
            pokemon_t* pokemon = crear_pokemon();
            if (!pokemon){
                fclose(archivo);
                lista_destruir(caja);
                lista_destruir(party);
                return ERROR;
            }

            if (leer_pokemon(leido, (*pokemon).nombre, &(*pokemon).velocidad, &(*pokemon).defensa,
                &(*pokemon).ataque) != DATOS_POKEMON){
                
                fclose(archivo);
                lista_destruir(caja);
                lista_destruir(party);
                free(pokemon);
                return ERROR;
            }
 
            if (i < MAX_POKEMONES_BATALLA){
                pokemon_t* pokemon_aux = crear_pokemon_copiado(pokemon);
                if (!pokemon_aux){
                    fclose(archivo);
                    lista_destruir(caja);
                    lista_destruir(party);
                    free(pokemon);
                    return ERROR;
                }
                if (lista_insertar(party, pokemon_aux) == ERROR){
                    fclose(archivo);
                    lista_destruir(caja);
                    lista_destruir(party);
                    free(pokemon);
                    free(pokemon_aux);
                    return ERROR;
                }
            }
            if (lista_insertar(caja, pokemon) == ERROR){
                fclose(archivo);
                lista_destruir(caja);
                lista_destruir(party);
                free(pokemon);
                return ERROR;
            }
            i++;

            leido = leer_linea(archivo, lectura, MAX_LINEA, &tipo);
        }
        if (lista_vacia(party)){
            lista_destruir(caja);
            lista_destruir(party);
            return ERROR;
        }
        (*personaje).caja = caja;
        (*personaje).party = party;
    }

    fclose(archivo);
    return EXITO;
}

pokemon_t* crear_pokemon_copiado(pokemon_t* pokemon_a_copiar){

    pokemon_t* pokemon = crear_pokemon();
    if (pokemon){
        strcpy((*pokemon).nombre, (*pokemon_a_copiar).nombre);
        (*pokemon).velocidad = (*pokemon_a_copiar).velocidad;
        (*pokemon).defensa = (*pokemon_a_copiar).defensa;
        (*pokemon).ataque = (*pokemon_a_copiar).ataque;
    }
    return pokemon;
}