#include "simulador.h"
#include "hospital.h"
#include "lista.h"
#include "heap.h"
#include "estructura_aux.h"
#include <string.h>

#define EXITO 0
#define ERROR -1
#define NO_EXISTE -2
#define PUNTOS_BASE 100

#define BONUS_NORMAL 20
#define BONUS_DIFICIL 50

#define ID_DIFICULTAD_CUSTOM_INICIAL 3

struct _simulador_t{

    hospital_t* hospital;
    heap_t* cola_espera;

    EstadisticasSimulacion* estadisticas; 
    InformacionPokemon* informacion_pokemon_actual; 
    lista_t* lista_dificultades;

    unsigned int cantidad_intentos;
    size_t dificultad_siguiente_id_disponible;
    bool simulacion_finalizada;
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
* PRE: Recibe cantidad_intentos que tiene que ser un numero entero positivo.
* POST: Devuelve los puntajes calculados en base a la cantidad de intentos en la dificultad facil.
*/
unsigned calcular_puntaje_facil(unsigned cantidad_intentos){
    if(cantidad_intentos > PUNTOS_BASE){
        cantidad_intentos = PUNTOS_BASE;
    }

    return PUNTOS_BASE - cantidad_intentos;
}

/*
* PRE: Recibe cantidad_intentos que tiene que ser un numero entero positivo.
* POST: Devuelve los puntajes calculados en base a la cantidad de intentos en la dificultad normal.
*/
unsigned calcular_puntaje_normal(unsigned cantidad_intentos){
    if(cantidad_intentos > PUNTOS_BASE){
        cantidad_intentos = PUNTOS_BASE;
    }

    return (PUNTOS_BASE - cantidad_intentos) + BONUS_NORMAL;
}

/*
* PRE: Recibe cantidad_intentos que tiene que ser un numero entero positivo.
* POST: Devuelve los puntajes calculados en base a la cantidad de intentos en la dificultad dificil.
*/
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
    }else if(resultado_verificacion == -1){
        return "El numero que estas buscando es mayor";
    }else if(resultado_verificacion == 1){
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
* PRE: Recibe un simulador valido.
* POST: Libera la memoria de un simulador solo en caso de que falle.
*/
void liberar_en_caso_error(simulador_t* simulador){
    free(simulador->informacion_pokemon_actual);
    free(simulador->estadisticas);
    free(simulador->cola_espera);
    free(simulador);
}

simulador_t* simulador_crear(hospital_t* hospital){
    if(!hospital){
        return NULL;
    }

    simulador_t* simulador = calloc(1, sizeof(simulador_t));
    if(simulador == NULL){
        return NULL;
    }

    simulador->hospital = hospital;

    heap_t* heap = heap_crear(comparador_niveles, NULL);
    if(heap == NULL){
        liberar_en_caso_error(simulador);
        return NULL;
    }

    simulador->cola_espera = heap;

    EstadisticasSimulacion* estadisticas = calloc(1, sizeof(EstadisticasSimulacion));
    if(estadisticas == NULL){
        liberar_en_caso_error(simulador);
        return NULL;
    }

    estadisticas->cantidad_eventos_simulados = 0;
    estadisticas->entrenadores_atendidos = 0;
    estadisticas->entrenadores_totales = (unsigned)hospital_cantidad_entrenadores(hospital);
    estadisticas->pokemon_atendidos = 0;
    estadisticas->pokemon_en_espera = 0;
    estadisticas->pokemon_totales = (unsigned)hospital_cantidad_pokemon(hospital);
    estadisticas->puntos = 0;

    simulador->estadisticas = estadisticas;

    InformacionPokemon* info_pokemon = calloc(1, sizeof(InformacionPokemon));
    if(info_pokemon == NULL){
        liberar_en_caso_error(simulador);
        return NULL;
    }

    simulador->informacion_pokemon_actual = info_pokemon;

    lista_t* dificultades = lista_crear();
    if(dificultades == NULL){
        liberar_en_caso_error(simulador);
        lista_destruir(dificultades);
        return NULL;
    }

    simulador->lista_dificultades = dificultades;

    int resultado = crear_dificultades_estandar(simulador->lista_dificultades);
    if(resultado == ERROR){
        liberar_en_caso_error(simulador);
        lista_destruir(dificultades);
        return NULL;
    }

    simulador->cantidad_intentos = 0;
    simulador->dificultad_siguiente_id_disponible = ID_DIFICULTAD_CUSTOM_INICIAL; 
    simulador->simulacion_finalizada = false;

    return simulador;
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
* PRE: Recibe un simulador.
* POST: Agrega los pokemones del siguiente entrenador a la cola de espera. Devuelve la cantidad de pokemones que fueron agregados.
*/
size_t agregar_pokemones_al_heap(simulador_t* simulador){
    if(!simulador){
        return 0;
    }

    size_t cantidad_agregados = 0;
    size_t recorridos = 0;

    lista_iterador_t* iterador = lista_iterador_crear(simulador->hospital->lista_entrenadores);
    if(!iterador){
        return 0;
    }

    while(recorridos != simulador->estadisticas->entrenadores_atendidos){
        lista_iterador_avanzar(iterador);
        recorridos++;
    }

    while(lista_iterador_tiene_siguiente(iterador)){
        entrenador_t* entrenador = lista_iterador_elemento_actual(iterador);

        if(recorridos == simulador->estadisticas->entrenadores_atendidos + 1){
            break;
        }

        lista_iterador_t* iterador_pokemones = lista_iterador_crear(entrenador->lista_pokemones);
        if(!iterador_pokemones){
            lista_iterador_destruir(iterador);
            return 0;
        }

        while(lista_iterador_tiene_siguiente(iterador_pokemones)){
            pokemon_t* pokemon = lista_iterador_elemento_actual(iterador_pokemones);
            if(!pokemon){
                lista_iterador_destruir(iterador_pokemones);
                lista_iterador_destruir(iterador);
                return 0;
            }

            heap_insertar(simulador->cola_espera, pokemon);
            cantidad_agregados++;
            lista_iterador_avanzar(iterador_pokemones);
        }

        lista_iterador_destruir(iterador_pokemones);

        recorridos++;
        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);

    return cantidad_agregados;
}

/*
* PRE: Recibe un simulador.
* POST: Quita un pokemon de la cola de espera y lo transfiere a pokemon en tratamiento. Devuelve -1 en caso de error o 0 en caso de exito.
*/
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

    entrenador_t* entrenador = pokemon_entrenador(pokemon);

    simulador->informacion_pokemon_actual->nombre_pokemon = pokemon_nombre(pokemon);
    simulador->informacion_pokemon_actual->nombre_entrenador = entrenador->nombre;

    simulador->estadisticas->pokemon_en_espera--;

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

    lista_iterador_t* iterador = lista_iterador_crear(simulador->hospital->lista_entrenadores);
    if(!iterador){
        return ERROR;
    }

    while(lista_iterador_tiene_siguiente(iterador)){
        entrenador_t* entrenador = lista_iterador_elemento_actual(iterador);
        if(!entrenador){
            return ERROR;
        }

        lista_iterador_t* iterador_pokemon = lista_iterador_crear(entrenador->lista_pokemones);
        if(!iterador_pokemon){
            lista_iterador_destruir(iterador);
            return ERROR;
        }

        while(lista_iterador_tiene_siguiente(iterador_pokemon)){
            pokemon_t* pokemon = lista_iterador_elemento_actual(iterador_pokemon);
            if(!pokemon){
                lista_iterador_destruir(iterador_pokemon);
                lista_iterador_destruir(iterador);
                return ERROR;
            }

            if(strcmp(pokemon_nombre(pokemon), nombre_pokemon) == 0 && strcmp(entrenador->nombre, nombre_entrenador) == 0){
                lista_iterador_destruir(iterador_pokemon);
                lista_iterador_destruir(iterador);
                return (int)pokemon_nivel(pokemon);
            }

            lista_iterador_avanzar(iterador_pokemon);
        }

        lista_iterador_destruir(iterador_pokemon);

        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);

    return ERROR;
}

/*
* PRE: Recibe un EstadisticasSimulacion* inicializado.
* POST: Llena las estadisticas recibidas con las estadisticas actuales del simulador. Devuelve -1 en caso de error o 0 en caso de exito.
*/
int simulador_obtener_estadisticas(simulador_t* simulador,void* datos){
    if(!simulador || !datos){
        return ERROR;
    }

    EstadisticasSimulacion* estadisticas_recibidas = (EstadisticasSimulacion*)datos;

    simulador->estadisticas->cantidad_eventos_simulados++;

    estadisticas_recibidas->cantidad_eventos_simulados = simulador->estadisticas->cantidad_eventos_simulados;
    estadisticas_recibidas->entrenadores_atendidos = simulador->estadisticas->entrenadores_atendidos;
    estadisticas_recibidas->entrenadores_totales = simulador->estadisticas->entrenadores_totales;
    estadisticas_recibidas->pokemon_atendidos = simulador->estadisticas->pokemon_atendidos;
    estadisticas_recibidas->pokemon_en_espera = simulador->estadisticas->pokemon_en_espera;
    estadisticas_recibidas->pokemon_totales = simulador->estadisticas->pokemon_totales;
    estadisticas_recibidas->puntos = simulador->estadisticas->puntos;


    return EXITO;
}

/*
* PRE: Recibe un simulador.
* POST: Atiende al proximo entrenador en el hospital, transfiere sus pokemones a la cola de espera y si no hay ninguno siendo tratado trata al de menor nivel. Devuelve -1 en caso de error o 0 en caso de exito.
*/
int simulador_atender_proximo_entrenador(simulador_t* simulador){
    if(!simulador){
        return ERROR;
    }

    if(simulador->estadisticas->entrenadores_atendidos == simulador->estadisticas->entrenadores_totales){
        return ERROR;
    }

    size_t cantidad_agregada = agregar_pokemones_al_heap(simulador);

    simulador->estadisticas->pokemon_en_espera += (unsigned int)cantidad_agregada;

    if(simulador->estadisticas->entrenadores_atendidos == 0){
        int resultado = atender_proximo_pokemon(simulador);
        if(resultado == ERROR){
            return ERROR;
        }
    } 

    simulador->estadisticas->entrenadores_atendidos++;

    return EXITO;
}

/*
* PRE: Recibe un InformacionPokemon* inicializado.
* POST: Llena la informacion recibida con la informacion del pokemon actual.En caso de que no haya ninguno llena la estructura con NULL.Devuelve -1 en caso de error o 0 en caso de exito.
*/
int simulador_obtener_informacion_pokemon_en_tratamiento(simulador_t* simulador,void* datos){
    if(!simulador || !datos){
        return ERROR;
    }

    InformacionPokemon* info_pokemon_recibida = (InformacionPokemon*)datos;

    if(simulador->estadisticas->pokemon_totales == simulador->estadisticas->pokemon_atendidos){ 
        info_pokemon_recibida->nombre_pokemon = NULL;
        info_pokemon_recibida->nombre_entrenador = NULL;
        return ERROR;
    }

    info_pokemon_recibida->nombre_entrenador = simulador->informacion_pokemon_actual->nombre_entrenador;
    info_pokemon_recibida->nombre_pokemon = simulador->informacion_pokemon_actual->nombre_pokemon;

    return EXITO;   
}

/*
* PRE: Recibe un Intento* inicializado con el nivel_adivinado.
* POST: Llena las estructura recibida con la informacion del intento actual. Si el intento fue correcto atiende al proximo pokemon. Devuelve -1 en caso de error o 0 en caso de exito.
*/
int simulador_adivinar_nivel_pokemon(simulador_t* simulador,void* datos){
    if(!simulador || !datos){
        return ERROR;
    }

    if(simulador->estadisticas->pokemon_totales == simulador->estadisticas->pokemon_atendidos){
        return ERROR;
    }

    dificultades_t* dificultad_actual = buscar_dificultad_actual(simulador->lista_dificultades);
    if(!dificultad_actual){
        return ERROR;
    }

    Intento* intento_recibido = (Intento*)datos;

    unsigned int nivel_pokemon_en_tratamiento = (unsigned int)buscar_nivel_pokemon(simulador, simulador->informacion_pokemon_actual->nombre_pokemon, simulador->informacion_pokemon_actual->nombre_entrenador);
    if(nivel_pokemon_en_tratamiento == ERROR){
        return ERROR;
    }

    int resultado_verificacion = dificultad_actual->datos_dificultad->verificar_nivel(intento_recibido->nivel_adivinado, nivel_pokemon_en_tratamiento);

    if(resultado_verificacion == 0){
        intento_recibido->es_correcto = true;
    }else{
        intento_recibido->es_correcto = false;
    }

    intento_recibido->resultado_string = dificultad_actual->datos_dificultad->verificacion_a_string(resultado_verificacion);

    if(intento_recibido->es_correcto){
        unsigned int puntos_a_agregar = dificultad_actual->datos_dificultad->calcular_puntaje(simulador->cantidad_intentos);
        simulador->estadisticas->puntos += puntos_a_agregar;
        simulador->estadisticas->pokemon_atendidos++;
        simulador->cantidad_intentos = 1;

        if(simulador->estadisticas->pokemon_en_espera > 0){
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

/*
* PRE: Recibe un string.
* POST: Hace una copia del string en el heap y la devuelve.
*/
char* copiar_string(const char* string_a_copiar){
    if(!string_a_copiar){
        return NULL;
    }

    char* string_copiado = malloc(sizeof(char) * (strlen(string_a_copiar) + 1));
    if(!string_copiado){
        return NULL;
    }

    strcpy(string_copiado, string_a_copiar);

    return string_copiado;
}

/*
* PRE: Recibe un DatosDificultad* inicializado con los datos de la nueva dificultad a agregar.
* POST: Agrega la nueva dificultad al simulador. Devuelve -1 en caso de error o 0 en caso de exito.
*/
int simulador_agregar_dificultad(simulador_t* simulador,void* datos){
    if(!simulador || !datos){
        return ERROR;
    }

    DatosDificultad* datos_dificultad_recibidos = (DatosDificultad*)datos;

    dificultades_t* nueva_dificultad = calloc(1, sizeof(dificultades_t));
    if(!nueva_dificultad){
        return ERROR;
    }

    InformacionDificultad* informacion_dificultad_nueva = calloc(1, sizeof(InformacionDificultad));
    if(!informacion_dificultad_nueva){
        free(nueva_dificultad);
        return ERROR;
    }

    DatosDificultad* datos_dificultad_nueva = calloc(1, sizeof(DatosDificultad));
    if(!datos_dificultad_nueva){
        free(informacion_dificultad_nueva);
        free(nueva_dificultad);
        return ERROR;
    }

    char* nombre_dificultad_nueva = copiar_string(datos_dificultad_recibidos->nombre); 

    informacion_dificultad_nueva->nombre_dificultad = nombre_dificultad_nueva;
    informacion_dificultad_nueva->en_uso = false;
    informacion_dificultad_nueva->id = (int)simulador->dificultad_siguiente_id_disponible;

    datos_dificultad_nueva->nombre = nombre_dificultad_nueva;
    datos_dificultad_nueva->verificar_nivel = datos_dificultad_recibidos->verificar_nivel;
    datos_dificultad_nueva->verificacion_a_string = datos_dificultad_recibidos->verificacion_a_string;
    datos_dificultad_nueva->calcular_puntaje = datos_dificultad_recibidos->calcular_puntaje;

    nueva_dificultad->datos_dificultad = datos_dificultad_nueva;
    nueva_dificultad->info_dificultad = informacion_dificultad_nueva;

    lista_insertar(simulador->lista_dificultades, nueva_dificultad);

    simulador->dificultad_siguiente_id_disponible++;

    return EXITO;
}

/*
* PRE: Recibe un int* inicializado con el id de la dificultad a seleccionar.
* POST: Selecciona la dificultad con el id recibido como activa. Devuelve -1 en caso de error(o si no existe la dificultad) o 0 en caso de exito.
*/
int simulador_seleccionar_dificultad(simulador_t* simulador,void* datos){
    if(!simulador || !datos){
        return ERROR;
    }

    int id_dificultad_nueva = *(int*)datos;

    dificultades_t* dificultad_buscada = buscar_dificultad_por_id(simulador->lista_dificultades, id_dificultad_nueva);
    if(!dificultad_buscada){ //Si no encuentra la dificultad.
        return ERROR;
    }

    dificultades_t* dificultad_actual = buscar_dificultad_actual(simulador->lista_dificultades);
    if(!dificultad_actual){ //Si no hay dificultad activa.
        return ERROR;
    }

    dificultad_actual->info_dificultad->en_uso = false;
    dificultad_buscada->info_dificultad->en_uso = true;

    return EXITO;
}

/*
* PRE: Recibe un InformacionDificultad* inicializado con el id de la dificultad a obtener.
* POST: Llena la estructura con los datos de la dificultad obtenida o en caso de no existir pone el id en -1 y el nombre en NULL. Devuelve -1 en caso de error o 0 en caso de exito.
*/
int simulador_obtener_informacion_dificultad(simulador_t* simulador,void* datos){
    if(!simulador || !datos){
        return ERROR;
    }

    InformacionDificultad* info_dificultad_recibida = (InformacionDificultad*)datos;

    dificultades_t* dificultad_seleccionada = buscar_dificultad_por_id(simulador->lista_dificultades,info_dificultad_recibida->id);
    if(!dificultad_seleccionada){
        info_dificultad_recibida->id = -1;
        info_dificultad_recibida->nombre_dificultad = NULL;
        return ERROR;
    }

    info_dificultad_recibida->en_uso = dificultad_seleccionada->info_dificultad->en_uso;
    info_dificultad_recibida->nombre_dificultad = dificultad_seleccionada->datos_dificultad->nombre;

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

        if(contador >= ID_DIFICULTAD_CUSTOM_INICIAL){ 
            free((char*)(dificultad->info_dificultad->nombre_dificultad));
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
    liberar_dificultades(simulador->lista_dificultades);
    lista_destruir(simulador->lista_dificultades);
    hospital_destruir(simulador->hospital);

    free(simulador->informacion_pokemon_actual);
    free(simulador->estadisticas);
    free(simulador);

    return;
}
