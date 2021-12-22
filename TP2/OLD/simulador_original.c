#include "simulador.h"
#include "hospital.h"
#include "lista.h"
#include "heap.h"
#include "estructura_aux.h"

#include <stdio.h> //! TESTING
#include <string.h> //! TESTING

#define COLOR_ERROR printf("\033[91m EL ERROR ESTUVO AQUI! \033[0m\n");

#define EXITO 0
#define ERROR -1
#define NO_EXISTE -2
#define PUNTOS_BASE 100

#define BONUS_NORMAL 20
#define BONUS_DIFICIL 50

struct _simulador_t{
    hospital_t* hospital;
    EstadisticasSimulacion* estadisticas; //? No es necesario? -> Este lo estoy usando
    InformacionPokemon* info_pokemon; //? No es necesario? -> Este lo estoy usando
    heap_t* cola_espera;
    size_t id_ultimo_entrenador;
    Intento* intento_actual; //? No es necesario?
    DatosDificultad* datos_dificultad; //? No es necesario?
    lista_t* lista_dificultades;
    bool simulacion_finalizada;
    size_t dificultad_siguiente_id_disponible;
    unsigned int cantidad_intentos;
};

typedef struct dificultades{
    InformacionDificultad* info_dificultad;
    DatosDificultad* datos_dificultad;
} dificultades_t;

/*
* PRE: Recibe dos pokemones validos.
* POST: Devuelve un numero entero positivo si el primer pokemon tiene mas nivel que el segundo, un negativo si el primero tiene menos nivel o 0 si tienen el mismo nivel.
*/
int comparador_niveles(void* p1, void* p2){
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

/*
* PRE: Recibe un simulador valido.
* POST: Libera toda la memoria reservada para el simulador si algo falla.
*/
void liberar_en_caso_error(simulador_t* simulador){
    free(simulador->estadisticas);
    free(simulador->info_pokemon);
    free(simulador->cola_espera);
    free(simulador->intento_actual);
    free(simulador->datos_dificultad);
    free(simulador->hospital);
    free(simulador);
}

unsigned calcular_puntaje_facil(unsigned cantidad_intentos){
    if(cantidad_intentos > PUNTOS_BASE){
        cantidad_intentos = PUNTOS_BASE;
    }

    return PUNTOS_BASE - cantidad_intentos;
}

unsigned calcular_puntaje_normal(unsigned cantidad_intentos){
    if(cantidad_intentos > PUNTOS_BASE){
        cantidad_intentos = PUNTOS_BASE;
    }

    return (PUNTOS_BASE - cantidad_intentos) + BONUS_NORMAL;
}

unsigned calcular_puntaje_dificil(unsigned cantidad_intentos){
    if(cantidad_intentos > PUNTOS_BASE){
        cantidad_intentos = PUNTOS_BASE;
    }

    return (PUNTOS_BASE - cantidad_intentos) + BONUS_DIFICIL;
}

/*
* PRE:
* POST: Devuelve 0 si el nivel_adivinado es igual a nivel pokemon, 1 si es mayor, -1 si es menor.
*/
int verificar_nivel_facil(unsigned nivel_adivinado, unsigned nivel_pokemon){
    if(nivel_adivinado == nivel_pokemon){
        return 0;
    }else if(nivel_adivinado > nivel_pokemon){
        return 1;
    }else{
        return -1;
    }
}

/*
* PRE:
* POST: Devuelve -1 si el nivel avidinado es menor al nivel pokemon-10 o si es mayor a nivel pokemon+10, 0 si son iguales, -1 representa frio, 1 representa caliente.
*/
int verificar_nivel_normal(unsigned nivel_adivinado, unsigned nivel_pokemon){
    if(nivel_adivinado == nivel_pokemon){
        return 0;
    }else if(nivel_adivinado > nivel_pokemon+10 || nivel_adivinado < nivel_pokemon-10){
        return -1;
    }else{
        return 1;
    }
}

/*
* PRE:
* POST: Devuelve 0 si el nivel_adivinado es igual a nivel pokemon, 1 si el nivel_pokemon es par, 2 si el nivel_pokemon es impar.
*/
int verificar_nivel_dificil(unsigned nivel_adivinado, unsigned nivel_pokemon){
    if(nivel_adivinado == nivel_pokemon){
        return 0;
    }else if(nivel_pokemon%2 == 0){
        return 1;
    }else{
        return 2;
    }
}

/*
* PRE:
* POST: Devuelve "Acertaste" si recibe por parametro 0, "el buscado es mayor" si recibe 1, "el buscado es menor" si recibe -1.
*/
const char*verificacion_string_facil(int resultado_verificacion){
    if(resultado_verificacion == 0){
        return "Felicidades, acertaste!!";
    }else if(resultado_verificacion == 1){
        return "El numero que estas buscando es mayor";
    }else if(resultado_verificacion == -1){
        return "El numero que estas buscando es menor";
    }else{
        return "Error";
    }
}

/*
* PRE:
* POST: Devuelve "Acertaste" si recibe por parametro 0, "caliente" si recibe 1 por parametro, "frio" si recibe -1 por parametro.
*/
const char* verificacion_string_normal(int resultado_verificacion){
    if(resultado_verificacion == 0){
        return "Felicidades, acertaste!!";
    }else if(resultado_verificacion == 1){
        return "Caliente!";
    }else if(resultado_verificacion == -1){
        return "Frio!";
    }else{
        return "Error";
    }
}

/*
* PRE:
* POST: Devuelve "Acertaste" si recibe por parametro 0, "par" si recibe 1 por parametro, "impar" si recibe 2 por parametro.
*/
const char* verificacion_string_dificil(int resultado_verificacion){
    if(resultado_verificacion == 0){
        return "Felicidades, acertaste!!";
    }else if(resultado_verificacion == 1){
        return "El numero que estas buscando es par";
    }else if(resultado_verificacion == 2){
        return "El numero que estas buscando es impar";
    }else{
        return "Error";
    }
}

/*
* PRE: Recibe una lista valida.
* POST: Crea las dificultades estandar del simulador y las añade a la lista.
*/
int crear_dificultades_estandar(lista_t* lista){
    if(lista == NULL){
        return ERROR;
    }

    InformacionDificultad* facil_info = calloc(1, sizeof(InformacionDificultad));
    if(facil_info == NULL){
        return ERROR;
    }
    InformacionDificultad* normal_info = calloc(1, sizeof(InformacionDificultad));
    if(normal_info == NULL){
        free(facil_info);
        return ERROR;
    }
    InformacionDificultad* dificil_info = calloc(1, sizeof(InformacionDificultad));
    if(dificil_info == NULL){
        free(facil_info);
        free(normal_info);
        return ERROR;
    }

    DatosDificultad* facil_datos = calloc(1, sizeof(DatosDificultad));
    if(facil_info == NULL){
        free(facil_info);
        free(normal_info);
        free(dificil_info);
        return ERROR;
    }

    DatosDificultad* normal_datos = calloc(1, sizeof(DatosDificultad));
    if(normal_datos == NULL){
        free(facil_info);
        free(normal_info);
        free(dificil_info);
        free(facil_datos);
        return ERROR;
    }

    DatosDificultad* dificil_datos = calloc(1, sizeof(DatosDificultad));
    if(dificil_datos == NULL){
        free(facil_info);
        free(normal_info);
        free(dificil_info);
        free(facil_datos);
        free(normal_datos);
        return ERROR;
    }
    
    facil_info->nombre_dificultad = "facil";
    facil_info->en_uso = false;
    facil_info->id = 0;

    normal_info->nombre_dificultad = "normal";
    normal_info->en_uso = true;
    normal_info->id = 1;

    dificil_info->nombre_dificultad = "dificil";
    dificil_info->en_uso = false;
    dificil_info->id = 2;

    facil_datos->nombre = "facil";
    facil_datos->calcular_puntaje = calcular_puntaje_facil;
    facil_datos->verificar_nivel = verificar_nivel_facil;
    facil_datos->verificacion_a_string = verificacion_string_facil;
    
    normal_datos->nombre = "normal";
    normal_datos->calcular_puntaje = calcular_puntaje_normal;
    normal_datos->verificar_nivel = verificar_nivel_normal;
    normal_datos->verificacion_a_string = verificacion_string_normal;

    dificil_datos->nombre = "dificil";
    dificil_datos->calcular_puntaje = calcular_puntaje_dificil;
    dificil_datos->verificar_nivel = verificar_nivel_dificil;
    dificil_datos->verificacion_a_string = verificacion_string_dificil;
    
    dificultades_t* facil = calloc(1, sizeof(dificultades_t));
    if(facil == NULL){
        free(facil_info);
        free(normal_info);
        free(dificil_info);
        free(facil_datos);
        free(normal_datos);
        free(dificil_datos);
        return ERROR;
    }

    dificultades_t* normal = calloc(1, sizeof(dificultades_t));
    if(normal == NULL){
        free(facil_info);
        free(normal_info);
        free(dificil_info);
        free(facil_datos);
        free(normal_datos);
        free(dificil_datos);
        free(facil);
        return ERROR;
    }

    dificultades_t* dificil = calloc(1, sizeof(dificultades_t));
    if(dificil == NULL){
        free(facil_info);
        free(normal_info);
        free(dificil_info);
        free(facil_datos);
        free(normal_datos);
        free(dificil_datos);
        free(facil);
        free(normal);
        return ERROR;
    }

    facil->info_dificultad = facil_info;
    facil->datos_dificultad = facil_datos;

    normal->info_dificultad = normal_info;
    normal->datos_dificultad = normal_datos;

    dificil->info_dificultad = dificil_info;
    dificil->datos_dificultad = dificil_datos;

    lista_insertar(lista, facil);
    lista_insertar(lista, normal);
    lista_insertar(lista, dificil);

    return EXITO;
}

/*
* PRE:
* POST: Busca el ID del primer entrenador, en caso de error devuelve -1.
*/
int buscar_id_primer_entrenador(simulador_t* simulador){
    lista_iterador_t* iterador = lista_iterador_crear(simulador->hospital->lista_pokemones);
    if(!iterador){
        return ERROR;
    }

    pokemon_t* primer_pokemon = lista_iterador_elemento_actual(iterador);
    if(!primer_pokemon){
        lista_iterador_destruir(iterador);
        return ERROR;
    }

    size_t menor_id = primer_pokemon->entrenador->id;
    
    while(lista_iterador_tiene_siguiente(iterador)){
        pokemon_t* pokemon = lista_iterador_elemento_actual(iterador);
        if(!pokemon){
            return ERROR;
        }
        if(pokemon->entrenador->id < menor_id){
            menor_id = pokemon->entrenador->id;
        }
        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);
    return (int)menor_id;
}

simulador_t* simulador_crear(hospital_t* hospital){
    if(!hospital){
        return NULL;
    }

    simulador_t* simulador = calloc(1,sizeof(simulador_t));
    if(!simulador){
        return NULL;
    }

    simulador->hospital = hospital;

    EstadisticasSimulacion* estadisticas = calloc(1,sizeof(EstadisticasSimulacion));
    if(!estadisticas){
        liberar_en_caso_error(simulador);
        return NULL;
    }

    estadisticas->entrenadores_atendidos = 0;
    estadisticas->entrenadores_totales = (unsigned)hospital_cantidad_entrenadores(hospital);
    estadisticas->pokemon_atendidos = 0;
    estadisticas->pokemon_en_espera = 0;
    estadisticas->pokemon_totales = (unsigned)hospital_cantidad_pokemon(hospital);
    estadisticas->puntos = 0;
    estadisticas->cantidad_eventos_simulados = 0;

    simulador->estadisticas = estadisticas;

    heap_t* heap = heap_crear(comparador_niveles,NULL);
    if(!heap){
        liberar_en_caso_error(simulador);
        return NULL;
    }

    simulador->cola_espera = heap;

    InformacionPokemon* Informacion_pokemon = calloc(1,sizeof(InformacionPokemon));
    if(!Informacion_pokemon){
        liberar_en_caso_error(simulador);
        return NULL;
    }

    simulador->info_pokemon = Informacion_pokemon;

    Intento* intento = calloc(1,sizeof(Intento));
    if(!intento){
        liberar_en_caso_error(simulador);
        return NULL;
    }
    
    simulador->intento_actual = intento;

    DatosDificultad* datos_dificultad = calloc(1,sizeof(DatosDificultad));
    if(!datos_dificultad){
        liberar_en_caso_error(simulador);
        return NULL;
    }

    datos_dificultad->nombre = "Normal";

    simulador->datos_dificultad = datos_dificultad;

    simulador->lista_dificultades = lista_crear();
    if(simulador->lista_dificultades == NULL){
        liberar_en_caso_error(simulador);
        return NULL;
    }

    int resultado = crear_dificultades_estandar(simulador->lista_dificultades);
    if(resultado == ERROR){
        liberar_en_caso_error(simulador);
        return NULL;
    }

    simulador->simulacion_finalizada = false;

    simulador->dificultad_siguiente_id_disponible = 3;
    simulador->cantidad_intentos = 1;

    simulador->id_ultimo_entrenador = (size_t)buscar_id_primer_entrenador(simulador);

    return simulador;
}

/*
* PRE: Recibe una lista de dificultades
* POST: Busca en la lista cual es la dificultad activa y la devuelve. Si no hay ninguna activa o falla devuelve NULL.
*/
dificultades_t* buscar_dificultad_actual(lista_t* lista_dificultades){
    if(!lista_dificultades){
        return NULL;
    }

    lista_iterador_t* iterador = lista_iterador_crear(lista_dificultades);
    if(!iterador){
        return NULL;
    }

    while(lista_iterador_tiene_siguiente(iterador)){

        dificultades_t* dificultad = lista_iterador_elemento_actual(iterador);
        if(!dificultad){
            return NULL;
        }

        if(dificultad->info_dificultad->en_uso == true){
            lista_iterador_destruir(iterador);
            return dificultad;
        }

        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);

    return NULL;
}

/*
* PRE: Recibe una lista de dificultades y un id para buscar la dificultad.
* POST: Busca la dificultad en la lista y la devuelve. En caso de error o no encontrarlo devuelve NULL.
*/
dificultades_t* buscar_dificultad_por_id(lista_t* lista_dificultades, int id_buscado){
    if(!lista_dificultades){
        return NULL;
    }

    lista_iterador_t* iterador = lista_iterador_crear(lista_dificultades);
    if(!iterador){
        return NULL;
    }

    while(lista_iterador_tiene_siguiente(iterador)){

        dificultades_t* dificultad = lista_iterador_elemento_actual(iterador);
        if(!dificultad){
            return NULL;
        }

        if(dificultad->info_dificultad->id == id_buscado){
            lista_iterador_destruir(iterador);
            return dificultad;
        }

        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);

    return NULL;
}

/*
* PRE: Recibe un simulador y un puntero hacia EstadisticasSimulacion
* POST: Carga en el puntero recibido las estadisticas actuales del simulador.
*/
int simulador_obtener_estadisticas(simulador_t* simulador, void* datos){
    if(!simulador || !datos){
        return ERROR;
    }

    EstadisticasSimulacion* estadisticas_datos = (EstadisticasSimulacion*)datos;

    simulador->estadisticas->cantidad_eventos_simulados++;

    estadisticas_datos->cantidad_eventos_simulados = simulador->estadisticas->cantidad_eventos_simulados;
    estadisticas_datos->entrenadores_atendidos = simulador->estadisticas->entrenadores_atendidos;
    estadisticas_datos->entrenadores_totales = simulador->estadisticas->entrenadores_totales;
    estadisticas_datos->pokemon_atendidos = simulador->estadisticas->pokemon_atendidos;
    estadisticas_datos->pokemon_en_espera = simulador->estadisticas->pokemon_en_espera;
    estadisticas_datos->pokemon_totales = simulador->estadisticas->pokemon_totales;
    estadisticas_datos->puntos = simulador->estadisticas->puntos;

    datos = estadisticas_datos;

    return EXITO;
}

/*
* PRE:
* POST: Agrega los pokemones al heap y devuelve la cantidad de pokemones que agrego, devuelve 0 en caso de error.
*/
size_t agregar_pokemones_al_heap(simulador_t* simulador){
    if(!simulador){
        return 0;
    }

    size_t cantidad = 0;

    lista_iterador_t* iterador = lista_iterador_crear(simulador->hospital->lista_pokemones);
    if(!iterador){
        return 0;
    }

    while(lista_iterador_tiene_siguiente(iterador)){
        pokemon_t* pokemon = lista_iterador_elemento_actual(iterador);
        if(!pokemon){
            return 0;
        }
        if(pokemon->entrenador->id == simulador->id_ultimo_entrenador){
            int resultado = heap_insertar(simulador->cola_espera,pokemon);
            if(resultado == ERROR){
                return 0;
            }
            cantidad++;
        }
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);

    return cantidad;
}

int atender_proximo_pokemon(simulador_t* simulador){
    if(!simulador){
        return ERROR;
    }

    if(!simulador->cola_espera){
        return ERROR;
    }

    pokemon_t* pokemon = heap_extraer_raiz(simulador->cola_espera);
    if(!pokemon){
        return ERROR;
    }

    simulador->info_pokemon->nombre_pokemon = pokemon->nombre;
    simulador->info_pokemon->nombre_entrenador = pokemon->entrenador->nombre;

    simulador->estadisticas->pokemon_en_espera--;

    return EXITO;
}

/*
* PRE: Recibe un simulador valido.
* POST: Atiende al proximo entrenador poniendo a sus pokemones en la lista de espera.
*/
int simulador_atender_proximo_entrenador(simulador_t* simulador){
    if(!simulador){
        return ERROR;
    }

    if(simulador->estadisticas->entrenadores_atendidos >= simulador->estadisticas->entrenadores_totales){
        return ERROR;
    }

    size_t cantidad_agregada = agregar_pokemones_al_heap(simulador);
    if(cantidad_agregada == 0){
        return ERROR;
    }

    simulador->estadisticas->pokemon_en_espera += (unsigned)cantidad_agregada;
    simulador->estadisticas->entrenadores_atendidos++;
    simulador->id_ultimo_entrenador++;

    if(!simulador->info_pokemon->nombre_pokemon){
        int resultado = atender_proximo_pokemon(simulador);
        if(resultado == ERROR){
            return ERROR;
        }
    }

    return EXITO;
}

/*
* PRE: Recibe un simulador valido y un puntero a InformacionPokemon* 
* POST: LLena el puntero recibido con la informacion del pokemon que esta siendo tratado.
*/
int simulador_obtener_informacion_pokemon_en_tratamiento(simulador_t* simulador, void* datos){
    if(!simulador || !datos){
        return ERROR;
    }

    if(!simulador->info_pokemon->nombre_pokemon){
        return ERROR;
    }

    InformacionPokemon* informacion = (InformacionPokemon*)datos;

    if(simulador->estadisticas->pokemon_totales == simulador->estadisticas->pokemon_atendidos){
        informacion->nombre_entrenador = NULL;
        informacion->nombre_pokemon = NULL;
        return ERROR;
    }


    informacion->nombre_pokemon = simulador->info_pokemon->nombre_pokemon;
    informacion->nombre_entrenador = simulador->info_pokemon->nombre_entrenador;

    return EXITO;
}

/*
* PRE: Recibe un simulador, un nombre de un pokemon valido,un nombre de entrenador del pokemon, el entrenador puede ser NULL.
* POST: Devuelve el nivel de un pokemon recibido.
*/
int buscar_nivel_pokemon(simulador_t* simulador,const char* nombre_pokemon, const char* nombre_entrenador){
    if(!nombre_pokemon || !simulador){
        return ERROR;
    }

    lista_iterador_t* iterador = lista_iterador_crear(simulador->hospital->lista_pokemones);
    if(!iterador){
        return ERROR;
    }

    while(lista_iterador_tiene_siguiente(iterador)){
        pokemon_t* pokemon = lista_iterador_elemento_actual(iterador);
        if(!pokemon){
            return ERROR;
        }

        if(nombre_entrenador != NULL){
            entrenador_t* entrenador = pokemon_entrenador(pokemon);
            if(strcmp(entrenador->nombre,nombre_entrenador) == 0){
                if(strcmp(pokemon_nombre(pokemon),nombre_pokemon) == 0){
                    lista_iterador_destruir(iterador);
                    return (int)pokemon_nivel(pokemon);
                }
            }
        }else{
            if(strcmp(pokemon_nombre(pokemon),nombre_pokemon) == 0){
                lista_iterador_destruir(iterador);
                return (int)pokemon_nivel(pokemon);
            }
        }
        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);

    return ERROR;
}


int simulador_adivinar_nivel_pokemon(simulador_t* simulador, void* datos){ 
    if(!simulador || !datos){
        return ERROR;
    }

    if(simulador->estadisticas->pokemon_totales == simulador->estadisticas->pokemon_atendidos){
        return ERROR;
    }

    Intento* intento = (Intento*)datos;

    dificultades_t* dificultad_actual = buscar_dificultad_actual(simulador->lista_dificultades);
    if(!dificultad_actual){
        return ERROR;
    }
 
    unsigned int nivel_pokemon = (unsigned int)buscar_nivel_pokemon(simulador,simulador->info_pokemon->nombre_pokemon,simulador->info_pokemon->nombre_entrenador);
    if(nivel_pokemon == ERROR){
        return ERROR;
    }

    int resultado_verificacion = dificultad_actual->datos_dificultad->verificar_nivel(intento->nivel_adivinado,nivel_pokemon);

    if(resultado_verificacion == 0){
        intento->es_correcto = true;
    }else{
        intento->es_correcto = false;
    }

    intento->resultado_string = dificultad_actual->datos_dificultad->verificacion_a_string(resultado_verificacion);

    if(intento->es_correcto){

        simulador->estadisticas->puntos += (unsigned int)dificultad_actual->datos_dificultad->calcular_puntaje(simulador->cantidad_intentos);
        simulador->estadisticas->pokemon_atendidos++;
        simulador->cantidad_intentos = 1;

        if(simulador->estadisticas->pokemon_totales > simulador->estadisticas->pokemon_atendidos){
            int resultado = atender_proximo_pokemon(simulador);
            if(resultado == ERROR){
                return ERROR;
            }
        }

    }else{
        simulador->cantidad_intentos++;
    }

    return EXITO;
}   

int simulador_agregar_dificultad(simulador_t* simulador, void* datos){ 
    if(!simulador || !datos){
        return ERROR;
    }

    DatosDificultad* dificultad_recibida = (DatosDificultad*)datos;

    dificultades_t* dificultad_nueva = calloc(1,sizeof(dificultades_t));
    if(!dificultad_nueva){
        return ERROR;
    }

    InformacionDificultad* dificultad_nueva_info = calloc(1,sizeof(InformacionDificultad));
    if(!dificultad_nueva_info){
        free(dificultad_nueva);
        return ERROR;
    }

    dificultad_nueva_info->nombre_dificultad = dificultad_recibida->nombre;
    dificultad_nueva_info->en_uso = false;
    dificultad_nueva_info->id = (int)simulador->dificultad_siguiente_id_disponible;

    dificultad_nueva->info_dificultad = dificultad_nueva_info;
    dificultad_nueva->datos_dificultad = dificultad_recibida;
    
    lista_insertar(simulador->lista_dificultades,dificultad_nueva);
 
    simulador->dificultad_siguiente_id_disponible++;

    return EXITO;
}

/*
* PRE: Recibe un simulador y un puntero hacia un entero que contiene la dificultad a cambiar.
* POST: Cambia la dificultad activa a la dificultad que se pasa por parametro.
*/
int simulador_seleccionar_dificultad(simulador_t* simulador, void* datos){
    if(!simulador || !datos){
        return ERROR;
    }

    int dificultad_nueva = *(int*)datos;
    dificultades_t* dificultad_buscada = buscar_dificultad_por_id(simulador->lista_dificultades, dificultad_nueva);
    if(!dificultad_buscada){
        return ERROR;
    }

    dificultades_t* dificultad_actual = buscar_dificultad_actual(simulador->lista_dificultades);
    if(!dificultad_actual){
        return ERROR;
    }

    dificultad_actual->info_dificultad->en_uso = false;

    dificultad_buscada->info_dificultad->en_uso = true;

    return EXITO;
}

/*
* PRE: Recibe un simulador y una dificultad inicializada con el id.
* POST: Llena la dificultad enviada por parametros con la informacion correcta. Si no existe cambia el ID a -1 y el nombre a NULL.
*/
int simulador_obtener_informacion_dificultad(simulador_t* simulador, void* datos){
    if(!simulador || !datos){
        return ERROR;
    }

    InformacionDificultad* dificultad_recibida = (InformacionDificultad*)datos;

    dificultades_t* dificultad_buscada = buscar_dificultad_por_id(simulador->lista_dificultades, dificultad_recibida->id);
    if(!dificultad_buscada){
        dificultad_recibida->id = -1;
        dificultad_recibida->nombre_dificultad = NULL;
        return ERROR;
    }

    dificultad_recibida->en_uso = dificultad_buscada->info_dificultad->en_uso;
    dificultad_recibida->nombre_dificultad = dificultad_buscada->info_dificultad->nombre_dificultad;

    return EXITO;
}   

ResultadoSimulacion simulador_simular_evento(simulador_t* simulador, EventoSimulacion evento, void* datos){
    if(!simulador || simulador->simulacion_finalizada){
        return ErrorSimulacion;
    }

    int resultado = NO_EXISTE;

    if(evento == ObtenerEstadisticas){
        resultado = simulador_obtener_estadisticas(simulador, datos);
        simulador->estadisticas->cantidad_eventos_simulados--;
    }else if(evento == AtenderProximoEntrenador){
        resultado = simulador_atender_proximo_entrenador(simulador);
    }else if(evento == ObtenerInformacionPokemonEnTratamiento){
        resultado = simulador_obtener_informacion_pokemon_en_tratamiento(simulador, datos);
    }else if(evento == AdivinarNivelPokemon){
        resultado = simulador_adivinar_nivel_pokemon(simulador, datos);
    }else if(evento == AgregarDificultad){
        resultado = simulador_agregar_dificultad(simulador, datos);
    }else if(evento == SeleccionarDificultad){
        resultado = simulador_seleccionar_dificultad(simulador, datos);
    }else if(evento == ObtenerInformacionDificultad){
        resultado = simulador_obtener_informacion_dificultad(simulador, datos);
    }else if(evento == FinalizarSimulacion){
        simulador->simulacion_finalizada = true;
        resultado = EXITO;
    }

    if(resultado == NO_EXISTE){
        return ErrorSimulacion;
    }

    simulador->estadisticas->cantidad_eventos_simulados++;
    if(resultado == EXITO){
        return ExitoSimulacion;
    }else{
        return ErrorSimulacion;
    }
}

/*
* PRE: Recibe una lista_dificultades
* POST: Libera los elementos dentro de la lista_dificultades.
*/
void liberar_dificultades(lista_t* lista_dificultades){
    if(!lista_dificultades || lista_vacia(lista_dificultades)){
        return;
    }

    lista_iterador_t* iterador = lista_iterador_crear(lista_dificultades);
    if(!iterador){
        return;
    }

    int contador = 0;

    while(lista_iterador_tiene_siguiente(iterador)){
        dificultades_t* dificultad = lista_iterador_elemento_actual(iterador);
        if(!dificultad){
            return;
        }

        if(contador == 3){ //? A partir de 3 son las dificultades creadas de manera externa.
            free(dificultad->info_dificultad);
            free(dificultad);
            lista_iterador_destruir(iterador);
            return;
        }

        free(dificultad->info_dificultad);
        free(dificultad->datos_dificultad);
        free(dificultad);
        lista_iterador_avanzar(iterador);
        contador++;
    }
    lista_iterador_destruir(iterador);
}

void simulador_destruir(simulador_t* simulador){
    if(!simulador){
        return;
    }

    heap_destruir(simulador->cola_espera);
    hospital_destruir(simulador->hospital);
    liberar_dificultades(simulador->lista_dificultades);
    lista_destruir(simulador->lista_dificultades);

    free(simulador->datos_dificultad);
    free(simulador->intento_actual);
    free(simulador->info_pokemon);
    free(simulador->estadisticas);
    free(simulador);
}
