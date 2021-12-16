#include "simulador.h"
#include "hospital.h"
#include "heap.h"
#include "lista.h"
#include "pa2mm.h"

#include <string.h>

struct _simulador_t{
    hospital_t* hospital;
    EstadisticasSimulacion* estadisticas;
    InformacionPokemon* info_pokemon;
    heap_t* cola_espera;
    size_t id_ultimo_entrenador;
    Intento* intento_actual;
    DatosDificultad* datos_dificultad;
    lista_t* lista_dificultades;
    bool simulacion_finalizada;
    size_t dificultad_siguiente_id_disponible;
};

typedef struct dificultades{
    InformacionDificultad* info_dificultad;
    DatosDificultad* datos_dificultad;
} dificultades_t;


InformacionDificultad* buscar_dificultad_en_uso(lista_t* lista_dificultades){
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
            return dificultad->info_dificultad;
        }

        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);

    return NULL;
}

unsigned calcular_puntaje_hardcore(unsigned cantidad_intentos){
    return cantidad_intentos * 10;
}

int verificar_nivel_hardcore(unsigned nivel_adivinado, unsigned nivel_pokemon){
    if(nivel_adivinado == nivel_pokemon){
        return 0;
    }

    return 1;
}

const char* verificacion_string_hardcore(int resultado_verificacion){
    if(resultado_verificacion == 0){
        return "Correcto";
    }

    return "Incorrecto";
}

// -----------------------------------------------------------------------------

void NoSePuedeCrearUnSimuladorConHospitalNULL(){
    hospital_t* hospital = NULL;

    pa2m_afirmar(!hospital_leer_archivo(hospital,"ejemplos/varios_entrenadores.hospital"),"No se pude leer un archivo con un hospital NULL");

    simulador_t* simulador = simulador_crear(hospital);

    pa2m_afirmar(!simulador,"No se pudo crear un simulador con un hospital NULL");
}

void SePuedeCrearUnSimuladorConHospitalVacio(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital != NULL,"Se pudo crear un hospital");

    pa2m_afirmar(hospital_leer_archivo(hospital,"ejemplos/archivo_vacio.hospital"),"Se pudo leer el archivo vacio");

    simulador_t* simulador = simulador_crear(hospital);

    pa2m_afirmar(simulador != NULL,"Se pudo crear un simulador con un hospital de archivo vacio");

    simulador_destruir(simulador);
}

void SePuedeCrearUnSimuladorConHospitalInvalido(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital != NULL,"Se pudo crear un hospital");

    pa2m_afirmar(hospital_leer_archivo(hospital,"ejemplos/invalido.hospital"),"No se pudo leer el archivo invalido");

    simulador_t* simulador = simulador_crear(hospital);

    pa2m_afirmar(simulador,"Se pudo crear un simulador con un hospital invalido");

    simulador_destruir(simulador);
}

void SePuedeCrearUnSimulador_Correctamente(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital != NULL,"Se pudo crear un hospital");

    pa2m_afirmar(hospital_leer_archivo(hospital,"ejemplos/varios_entrenadores.hospital"),"Se pudo leer el archivo");

    simulador_t* simulador = simulador_crear(hospital);

    pa2m_afirmar(simulador != NULL,"Se pudo crear un simulador");

    simulador_destruir(simulador);
}

void SePuedeObtenerEstadisticas_correctamente(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital != NULL,"Se pudo crear un hospital");

    hospital_leer_archivo(hospital,"ejemplos/varios_entrenadores.hospital");

    simulador_t* simulador = simulador_crear(hospital);

    pa2m_afirmar(simulador != NULL,"Se pudo crear un simulador");

    EstadisticasSimulacion* estadisticas = calloc(1,sizeof(EstadisticasSimulacion));
    if(estadisticas == NULL){
        pa2m_afirmar(false,"No se pudo crear la estadisticas");
    }

    simulador_simular_evento(simulador,ObtenerEstadisticas, estadisticas);

    pa2m_afirmar(estadisticas->entrenadores_totales == hospital_cantidad_entrenadores(hospital),"La cantidad de entrenadores es correcta");
    pa2m_afirmar(estadisticas->pokemon_totales == hospital_cantidad_pokemon(hospital),"La cantidad de pokemon es correcta");
    pa2m_afirmar(estadisticas->entrenadores_atendidos == 0, "La cantidad de entrenadores atendidos es correcta");
    pa2m_afirmar(estadisticas->pokemon_atendidos == 0, "La cantidad de pokemon atendidos es correcta");
    pa2m_afirmar(estadisticas->pokemon_en_espera == 0, "La cantidad de pokemon en espera es correcta");
    pa2m_afirmar(estadisticas->puntos == 0, "La cantidad de puntos es correcta");
    pa2m_afirmar(estadisticas->cantidad_eventos_simulados == 1, "La cantidad de eventos simulados es correcta");

    pa2m_afirmar(simulador_simular_evento(simulador, AtenderProximoEntrenador, NULL),"Se pudo atender al proximo entrenador");

    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerEstadisticas, estadisticas),"Se pudo obtener las estadisticas");

    pa2m_afirmar(estadisticas->entrenadores_atendidos == 1, "La cantidad de entrenadores se actualiza ");
    pa2m_afirmar(estadisticas->pokemon_en_espera == 4 , "La cantidad de pokemon en espera se actualiza ");

    free(estadisticas);
    simulador_destruir(simulador);
}

void SePuedeAtenderEntrenador_Correctamente(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital != NULL,"Se pudo crear un hospital");

    pa2m_afirmar(hospital_leer_archivo(hospital,"ejemplos/varios_entrenadores.hospital"), "Se pudo leer el archivo");

    simulador_t* simulador = simulador_crear(hospital);

    pa2m_afirmar(simulador != NULL,"Se pudo crear un simulador");

    EstadisticasSimulacion* estadisticas = calloc(1,sizeof(EstadisticasSimulacion));
    if(estadisticas == NULL){
        pa2m_afirmar(false,"No se pudo crear la estadisticas");
    }

    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerEstadisticas, estadisticas) == ExitoSimulacion, "Se pudo obtener las estadisticas");

    pa2m_afirmar( simulador_simular_evento(simulador,AtenderProximoEntrenador, NULL) == ExitoSimulacion, "Se pudo atender el proximo entrenador");

    simulador_simular_evento(simulador,ObtenerEstadisticas, estadisticas);

    pa2m_afirmar(heap_cantidad(simulador->cola_espera) == 4, "La cantidad de entrenadores en el heap es correcta");
    pa2m_afirmar(estadisticas->entrenadores_atendidos == 1, "La cantidad de entrenadores atendidos es correcta");
    pa2m_afirmar(estadisticas->pokemon_atendidos == 0, "La cantidad de pokemon atendidos es correcta");
    pa2m_afirmar(estadisticas->cantidad_eventos_simulados == 3, "La cantidad de eventos simulados es correcta");
    pa2m_afirmar(estadisticas->pokemon_en_espera == 4, "La cantidad de pokemon en espera es correcta");

    free(estadisticas);
    simulador_destruir(simulador);
}

void SePuedeObtenerInformacionPokemonEnTratamiento_Correctamente(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital != NULL,"Se pudo crear un hospital");

    pa2m_afirmar(hospital_leer_archivo(hospital,"ejemplos/varios_entrenadores.hospital"), "Se pudo leer el archivo");

    simulador_t* simulador = simulador_crear(hospital);

    pa2m_afirmar(simulador != NULL,"Se pudo crear un simulador");

    InformacionPokemon* informacion = calloc(1,sizeof(InformacionPokemon));
    if(informacion == NULL){
        pa2m_afirmar(false,"No se pudo crear la informacion");
    }

    simulador_simular_evento(simulador,AtenderProximoEntrenador, NULL);
    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerInformacionPokemonEnTratamiento, informacion) == ExitoSimulacion, "Se pudo obtener la informacion");

    pa2m_afirmar(strcmp(informacion->nombre_pokemon,"rampardos")==0, "El pokemon es correcto");
    pa2m_afirmar(strcmp(informacion->nombre_entrenador,"lucas")==0, "El entrenador es correcto");

    free(informacion);
    simulador_destruir(simulador);
}

void SePuedeAdivinarNivelPokemon_Correctamente(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital != NULL,"Se pudo crear un hospital");

    pa2m_afirmar(hospital_leer_archivo(hospital,"ejemplos/varios_entrenadores.hospital"), "Se pudo leer el archivo");

    simulador_t* simulador = simulador_crear(hospital);

    pa2m_afirmar(simulador != NULL,"Se pudo crear un simulador");

    EstadisticasSimulacion* estadisticas = calloc(1,sizeof(EstadisticasSimulacion));
    if(estadisticas == NULL){
        pa2m_afirmar(false,"No se pudo crear la estadisticas");
    }

    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerEstadisticas, estadisticas) == ExitoSimulacion, "Se pudo obtener las estadisticas");

    pa2m_afirmar(estadisticas->entrenadores_atendidos == 0 , "La cantidad de entrenadores atendidos es correcta");
    pa2m_afirmar(estadisticas->entrenadores_totales == 5, "La cantidad de entrenadores es correcta");
    pa2m_afirmar(estadisticas->pokemon_atendidos == 0, "La cantidad de pokemon atendidos es correcta");
    pa2m_afirmar(estadisticas->pokemon_en_espera == 0, "La cantidad de pokemon en espera es correcta");
    pa2m_afirmar(estadisticas->pokemon_totales == 24, "La cantidad de pokemon es correcta");
    pa2m_afirmar(estadisticas->puntos == 0, "La cantidad de puntos es correcta");
    pa2m_afirmar(estadisticas->cantidad_eventos_simulados == 1, "La cantidad de eventos simulados es correcta");

    pa2m_afirmar(simulador_simular_evento(simulador,AtenderProximoEntrenador, NULL) == ExitoSimulacion, "Se pudo atender el proximo entrenador");

    Intento* intento = calloc(1,sizeof(Intento));
    if(intento == NULL){
        pa2m_afirmar(false,"No se pudo crear el intento");
    }

    InformacionDificultad* info_dificultad = calloc(1,sizeof(InformacionDificultad));
    if(info_dificultad == NULL){
        pa2m_afirmar(false,"No se pudo crear la info_dificultad");
    }

    info_dificultad->id = 1;

    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerInformacionDificultad, info_dificultad) == ExitoSimulacion, "Se pudo obtener la dificultad");
    pa2m_afirmar(info_dificultad->en_uso == true, "La dificultad actual es la normal");

    intento->nivel_adivinado = 25;

    pa2m_afirmar(simulador_simular_evento(simulador,AdivinarNivelPokemon,intento) == ErrorSimulacion, "No se pudo adivinar el nivel ya que no hay ningun pokemon siendo atendido");

    InformacionPokemon* info_poke = calloc(1,sizeof(InformacionPokemon));
    if(info_poke == NULL){
        pa2m_afirmar(false,"No se pudo crear la info_poke");
    }

    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerInformacionPokemonEnTratamiento, info_poke) == ExitoSimulacion, "Se pudo obtener la informacion del pokemon");

    pa2m_afirmar(strcmp(info_poke->nombre_pokemon,"rampardos")==0, "El pokemon es correcto");
    pa2m_afirmar(strcmp(info_poke->nombre_entrenador,"lucas")==0, "El entrenador es correcto");

    pa2m_afirmar(simulador_simular_evento(simulador,AtenderProximoEntrenador, NULL) == ExitoSimulacion, "Se pudo atender otro entrenador");
    pa2m_afirmar(simulador_simular_evento(simulador,AtenderProximoEntrenador, NULL) == ExitoSimulacion, "Se pudo atender el proximo entrenador");

    pa2m_afirmar(simulador_simular_evento(simulador,AdivinarNivelPokemon,intento) == ExitoSimulacion, "Se pudo adivinar el nivel");

    pa2m_afirmar(intento->es_correcto == false, "El intento no acerto el nivel");
    printf("%s\n",intento->resultado_string);
 
    intento->nivel_adivinado = 11;

    pa2m_afirmar(simulador_simular_evento(simulador,AdivinarNivelPokemon,intento) == ExitoSimulacion, "Se pudo adivinar el nivel");

    pa2m_afirmar(intento->es_correcto == false, "El intento no acerto el nivel");
    printf("%s\n",intento->resultado_string);

    intento->nivel_adivinado = 10;
    pa2m_afirmar(simulador_simular_evento(simulador,AdivinarNivelPokemon,intento) == ExitoSimulacion, "Se pudo adivinar el nivel");
    pa2m_afirmar(intento->es_correcto == true, "El intento acerto el nivel");
    printf("%s\n",intento->resultado_string);

    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerEstadisticas, estadisticas) == ExitoSimulacion, "Se pudo obtener las estadisticas");
    pa2m_afirmar(estadisticas->entrenadores_atendidos == 3, "La cantidad de entrenadores atendidos es correcta");
    pa2m_afirmar(estadisticas->pokemon_atendidos == 1, "La cantidad de pokemon atendidos es correcta");
    pa2m_afirmar(estadisticas->pokemon_en_espera == 12, "La cantidad de pokemon en espera es correcta");
    pa2m_afirmar(estadisticas->puntos == 117, "La cantidad de puntos es correcta");
    pa2m_afirmar(estadisticas->cantidad_eventos_simulados == 11, "La cantidad de eventos simulados es correcta");

    int nueva_dificultad = 2;
    info_dificultad->id = 2;

    pa2m_afirmar(simulador_simular_evento(simulador,SeleccionarDificultad, &nueva_dificultad) == ExitoSimulacion, "Se pudo cambiar la dificultad");
    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerInformacionDificultad, info_dificultad) == ExitoSimulacion, "Se pudo obtener la dificultad");
    pa2m_afirmar(info_dificultad->en_uso == true, "La dificultad actual es la dificil");
    pa2m_afirmar(strcmp(info_dificultad->nombre_dificultad,"dificil")==0, "La dificultad es correcta");

    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerInformacionPokemonEnTratamiento, info_poke) == ExitoSimulacion, "Se puedo obtener la informacion deun nuevo pokemon");
    pa2m_afirmar(strcmp(info_poke->nombre_pokemon,"venonat")==0, "El pokemon es correcto");
    pa2m_afirmar(strcmp(info_poke->nombre_entrenador,"pucci")==0, "El entrenador es correcto");

    intento->nivel_adivinado = 15;
    pa2m_afirmar(simulador_simular_evento(simulador,AdivinarNivelPokemon,intento) == ExitoSimulacion, "Se pudo adivinar el nivel");
    pa2m_afirmar(intento->es_correcto == false, "El intento no acerto el nivel");
    printf("%s\n",intento->resultado_string);

    intento->nivel_adivinado = 13;
    pa2m_afirmar(simulador_simular_evento(simulador,AdivinarNivelPokemon,intento) == ExitoSimulacion, "Se pudo adivinar el nivel");
    pa2m_afirmar(intento->es_correcto == false, "El intento no acerto el nivel");
    printf("%s\n",intento->resultado_string);

    intento->nivel_adivinado = 14;
    pa2m_afirmar(simulador_simular_evento(simulador,AdivinarNivelPokemon,intento) == ExitoSimulacion, "Se pudo adivinar el nivel");
    pa2m_afirmar(intento->es_correcto == true, "El intento acerto el nivel");
    printf("%s\n",intento->resultado_string);

    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerEstadisticas, estadisticas) == ExitoSimulacion, "Se pudo obtener las estadisticas");
    pa2m_afirmar(estadisticas->pokemon_atendidos == 2, "La cantidad de pokemon atendidos es correcta");
    pa2m_afirmar(estadisticas->pokemon_en_espera == 11, "La cantidad de pokemon en espera es correcta");
    pa2m_afirmar(estadisticas->puntos == 264, "La cantidad de puntos es correcta");
    
    free(intento);
    free(info_dificultad);
    free(info_poke);
    free(estadisticas);
    simulador_destruir(simulador);
}

void SePuedeAgregarUnaDificultad_Correctamente(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital != NULL,"Se pudo crear un hospital");

    pa2m_afirmar(hospital_leer_archivo(hospital,"ejemplos/varios_entrenadores.hospital"), "Se pudo leer el archivo");

    simulador_t* simulador = simulador_crear(hospital);

    pa2m_afirmar(simulador != NULL,"Se pudo crear un simulador");

    InformacionDificultad* dificultad_actual = buscar_dificultad_en_uso(simulador->lista_dificultades);
    pa2m_afirmar(strcmp(dificultad_actual->nombre_dificultad,"normal")==0, "La dificultad actual es normal");

    DatosDificultad* nueva_dificultad = calloc(1,sizeof(DatosDificultad));
    if(nueva_dificultad == NULL){
        pa2m_afirmar(false,"No se pudo crear la dificultad");
    }

    nueva_dificultad->nombre = "hardcore";
    nueva_dificultad->calcular_puntaje = calcular_puntaje_hardcore;
    nueva_dificultad->verificar_nivel = verificar_nivel_hardcore;
    nueva_dificultad->verificacion_a_string = verificacion_string_hardcore;

    pa2m_afirmar(simulador_simular_evento(simulador,AgregarDificultad,nueva_dificultad) == ExitoSimulacion, "Se pudo agregar la dificultad");

    dificultad_actual = buscar_dificultad_en_uso(simulador->lista_dificultades);
    pa2m_afirmar(strcmp(dificultad_actual->nombre_dificultad,"normal")==0, "La dificultad sigue siendo normal");

    int id_nueva_dificultad = 3;

    pa2m_afirmar(simulador_simular_evento(simulador, SeleccionarDificultad, &id_nueva_dificultad) == ExitoSimulacion, "Se pudo seleccionar la nueva dificultad");

    dificultad_actual = buscar_dificultad_en_uso(simulador->lista_dificultades);
    pa2m_afirmar(strcmp(dificultad_actual->nombre_dificultad,"hardcore")==0, "La dificultad cambio a hardcore");
    pa2m_afirmar(dificultad_actual->en_uso == true, "La dificultad esta en uso");
    pa2m_afirmar(dificultad_actual->id == 3, "El id de la dificultad es correcto");

    InformacionDificultad* dificultad_hardcore = calloc(1,sizeof(InformacionDificultad));
    if(dificultad_hardcore == NULL){
        pa2m_afirmar(false,"No se pudo crear la dificultad hardcore");
    }

    dificultad_hardcore->id = 3;

    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerInformacionDificultad,dificultad_hardcore) == ExitoSimulacion, "Se pudo obtener la dificultad hardcore");

    pa2m_afirmar(strcmp(dificultad_hardcore->nombre_dificultad,"hardcore")==0, "El nombre de la dificultad hardcore es correcto");
    pa2m_afirmar(dificultad_hardcore->en_uso == true, "La dificultad hardcore esta en uso");
 
    free(dificultad_hardcore);
    simulador_destruir(simulador);
}

void SeleccionarDificultad_Correctamente(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital != NULL,"Se pudo crear un hospital");

    pa2m_afirmar(hospital_leer_archivo(hospital,"ejemplos/varios_entrenadores.hospital"), "Se pudo leer el archivo");

    simulador_t* simulador = simulador_crear(hospital);

    pa2m_afirmar(simulador != NULL,"Se pudo crear un simulador");

    InformacionDificultad* dificultad_actual = buscar_dificultad_en_uso(simulador->lista_dificultades);
    
    if(dificultad_actual->en_uso){
        pa2m_afirmar(strcmp(dificultad_actual->nombre_dificultad,"normal")==0,"La dificultad actual es la predeterminada");
    }else{
        pa2m_afirmar(false,"La dificultad actual es incorrecta");
    }

    int cambiar_dif = 2;

    pa2m_afirmar(simulador_simular_evento(simulador,SeleccionarDificultad, &cambiar_dif) == ExitoSimulacion, "Se pudo cambiar la dificultad");

    dificultad_actual = buscar_dificultad_en_uso(simulador->lista_dificultades);
    
    if(dificultad_actual->en_uso){
        pa2m_afirmar(strcmp(dificultad_actual->nombre_dificultad,"dificil")==0,"La dificultad se cambia a dificil");
    }else{
        pa2m_afirmar(false,"La dificultad actual es incorrecta");
    } 

    simulador_destruir(simulador);
}

void NoSePuedeObtenerDificultadInexistente(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital != NULL,"Se pudo crear un hospital");

    pa2m_afirmar(hospital_leer_archivo(hospital,"ejemplos/varios_entrenadores.hospital"), "Se pudo leer el archivo");

    simulador_t* simulador = simulador_crear(hospital);

    pa2m_afirmar(simulador != NULL,"Se pudo crear un simulador");

    InformacionDificultad* obtener = calloc(1,sizeof(InformacionDificultad));
    if(obtener == NULL){
        pa2m_afirmar(false,"No se pudo crear la informacion");
    }

    obtener->id = 3;

    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerInformacionDificultad, obtener) == ExitoSimulacion, "Se pudo obtener una dificultad inexistente");

    pa2m_afirmar(obtener->nombre_dificultad == NULL, "No se pudo obtener el nombre de la dificultad - Nombre NULL");
    pa2m_afirmar(obtener->id == -1, "No se pudo obtener el id de la dificultad - Id -1");
    pa2m_afirmar(obtener->en_uso == false, "No se pudo obtener el estado de la dificultad - En uso - false");

    free(obtener);
    simulador_destruir(simulador);
}

void SePuedeObtenerDificultad_Correctamente(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital != NULL,"Se pudo crear un hospital");

    pa2m_afirmar(hospital_leer_archivo(hospital,"ejemplos/varios_entrenadores.hospital"), "Se pudo leer el archivo");

    simulador_t* simulador = simulador_crear(hospital);

    pa2m_afirmar(simulador != NULL,"Se pudo crear un simulador");

    InformacionDificultad* obtener = calloc(1,sizeof(InformacionDificultad));
    if(obtener == NULL){
        pa2m_afirmar(false,"No se pudo crear la informacion");
    }

    obtener->id = 0;

    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerInformacionDificultad, obtener) == ExitoSimulacion, "Se pudo obtener una dificultad");

    pa2m_afirmar(strcmp(obtener->nombre_dificultad,"facil")==0, "El nombre de la dificultad es correcto");
    pa2m_afirmar(obtener->id == 0, "El id de la dificultad es correcto");
    pa2m_afirmar(obtener->en_uso == false, "El estado de la dificultad es correcto");

    obtener->id = 1;

    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerInformacionDificultad, obtener) == ExitoSimulacion, "Se pudo obtener una nueva dificultad");
    
    pa2m_afirmar(strcmp(obtener->nombre_dificultad,"normal")==0, "El nombre de la dificultad es correcto");
    pa2m_afirmar(obtener->id == 1, "El id de la dificultad es correcto");
    pa2m_afirmar(obtener->en_uso == true, "El estado de la dificultad es correcto");

    free(obtener);
    simulador_destruir(simulador);
}

void SePuedeOperarConHospitalVacio_Correctamente(){
    hospital_t* hospital = hospital_crear();

    hospital_leer_archivo(hospital,"ejemplos/archivo_vacio.hospital");

    simulador_t* simulador = simulador_crear(hospital);

    pa2m_afirmar(simulador != NULL,"Puedo crear un simulador con un hospital vacío");

    EstadisticasSimulacion* estadisticas = calloc(1,sizeof(EstadisticasSimulacion));
    if(estadisticas == NULL){
        pa2m_afirmar(false,"No se pudo crear la estadisticas");
    }

    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerEstadisticas, estadisticas) == ExitoSimulacion, "Obtener estadísticas devuelve ExitoSimulacion");
    pa2m_afirmar(estadisticas->cantidad_eventos_simulados == 1, "La cantidad de eventos simulados es 1");
    pa2m_afirmar(estadisticas->entrenadores_totales == 0, "La cantidad de entrenadores totales es 0");
    pa2m_afirmar(estadisticas->entrenadores_atendidos == 0 ,"La cantidad de entrenadores atendidos es 0");
    pa2m_afirmar(estadisticas->pokemon_totales == 0, "La cantidad de pokemon totales es 0");
    pa2m_afirmar(estadisticas->pokemon_atendidos == 0, "La cantidad de pokemon atendidos es 0");
    pa2m_afirmar(estadisticas->pokemon_en_espera == 0 ,"La cantidad de pokemon en espera es 0");
    pa2m_afirmar(estadisticas->puntos == 0, "La cantidad de puntos 0");

    pa2m_afirmar(simulador_simular_evento(simulador,AtenderProximoEntrenador, NULL) == ErrorSimulacion, "Atender proximo entrenador daevuelve ErrorSimulación (no hay entrenadores)");

    InformacionPokemon* info = calloc(1,sizeof(InformacionPokemon));
    if(info == NULL){
        pa2m_afirmar(false,"No se pudo crear la informacion");
    }

    pa2m_afirmar(simulador_simular_evento(simulador,ObtenerInformacionPokemonEnTratamiento,info)== ErrorSimulacion, "Obtener la informacion del pokemon devuelve ErrorSimulacion (no hay pokemon)");

    InformacionDificultad* dificultad = calloc(1,sizeof(InformacionDificultad));
    if(dificultad == NULL){
        pa2m_afirmar(false,"No se pudo crear la informacion");
    }

    dificultad->id = 0;

    pa2m_afirmar(simulador_simular_evento(simulador, ObtenerInformacionDificultad,dificultad) == ExitoSimulacion,"Obtener la informacion de la dificultad 0 devuelve ExitoSimulacion");

    dificultad->id = 1;

    pa2m_afirmar(simulador_simular_evento(simulador, ObtenerInformacionDificultad,dificultad) == ExitoSimulacion,"Obtener la informacion de la dificultad 1 devuelve ExitoSimulacion");

    dificultad->id = 2;

    pa2m_afirmar(simulador_simular_evento(simulador, ObtenerInformacionDificultad,dificultad) == ExitoSimulacion,"Obtener la informacion de la dificultad 2 devuelve ExitoSimulacion");

    dificultad->id = 3;

    pa2m_afirmar(simulador_simular_evento(simulador, ObtenerInformacionDificultad,dificultad) == ErrorSimulacion,"Obtener la informacion de la dificultad 3 devuelve ErrorSimulacion");
    pa2m_afirmar(dificultad->id == -1, "El id de la dificultad es correcto");
    pa2m_afirmar(dificultad->nombre_dificultad == NULL, "El nombre de la dificultad es correcto");



    int seleccionar_dificultad = 3;

    pa2m_afirmar(simulador_simular_evento(simulador, SeleccionarDificultad, &seleccionar_dificultad) == ErrorSimulacion, "Al seleccionar una dificultad inexistente, obtengo ErrorSimulacion")

    seleccionar_dificultad = 2;

    pa2m_afirmar(simulador_simular_evento(simulador, SeleccionarDificultad, &seleccionar_dificultad) == ExitoSimulacion, "Al seleccionar una dificultad existente, obtengo ExitoSimulacion");

    dificultad->id = 2;
    simulador_simular_evento(simulador, ObtenerInformacionDificultad, dificultad);

    pa2m_afirmar(dificultad->en_uso, "Obtengo los datos de la dificultad selecionada y en_uso es true");

    dificultad->id = 1;
    simulador_simular_evento(simulador, ObtenerInformacionDificultad, dificultad);

    pa2m_afirmar(!dificultad->en_uso, "Obtengo los datos de la dificultad selecionada y en_uso es false");

    pa2m_afirmar(simulador_simular_evento(simulador, ObtenerEstadisticas, estadisticas) == ExitoSimulacion, "Vuelvo a obtener estadísticas, devuelve ExitoSimulacion");
    pa2m_afirmar(estadisticas->cantidad_eventos_simulados == 12, "La cantidad de eventos simulados es 12");

    pa2m_afirmar(simulador_simular_evento(simulador, FinalizarSimulacion, NULL) == ExitoSimulacion, "Finalizar simulacion retorna ExitoSimulacion");

    pa2m_afirmar(simulador_simular_evento(simulador, FinalizarSimulacion, NULL) == ErrorSimulacion, "Finalizar simulacion otra vez retorna ErrorSimulacion");

    pa2m_afirmar(simulador_simular_evento(simulador, ObtenerEstadisticas, estadisticas) == ErrorSimulacion, "Simular otro evento válido retorna ErrorSimulacion");

    free(estadisticas);
    free(info);
    free(dificultad);
    simulador_destruir(simulador);
}

void SePuedeOperarConHospitalConUnEntrenador_Correctamente(){
    hospital_t* hospital = hospital_crear();

    hospital_leer_archivo(hospital,"ejemplos/un_entrenador.hospital");

    simulador_t* simulador = simulador_crear(hospital);

    EstadisticasSimulacion* estadisticas = calloc(1,sizeof(EstadisticasSimulacion));
    if(estadisticas == NULL){
        pa2m_afirmar(false,"No se pudo crear la informacion");
    }

    pa2m_afirmar(simulador_simular_evento(simulador, ObtenerEstadisticas, estadisticas) == ExitoSimulacion, "Obtener estadísticas devuelve ExitoSimulacion");
    pa2m_afirmar(estadisticas->cantidad_eventos_simulados == 1, "La cantidad de eventos simulados es 1");
    pa2m_afirmar(estadisticas->entrenadores_totales == 1, "La cantidad de entrenadores totales es 1");
    pa2m_afirmar(estadisticas->entrenadores_atendidos == 0 , "La cantidad de entrenadores atendidos es 0");
    pa2m_afirmar(estadisticas->pokemon_totales == 3, "La cantidad de pokemones totales es 3");
    pa2m_afirmar(estadisticas->pokemon_atendidos == 0, "La cantidad de pokemones atendidos es 0");
    pa2m_afirmar(estadisticas->pokemon_en_espera == 0 , "La cantidad de pokemones en espera es 0");
    pa2m_afirmar(estadisticas->puntos == 0 , "La cantidad de puntos es 0");

    pa2m_afirmar(simulador_simular_evento(simulador, AtenderProximoEntrenador, NULL) == ExitoSimulacion, "Atender el proximo entrenador devuelve ExitoSimulacion");

    InformacionPokemon* info = calloc(1,sizeof(InformacionPokemon));
    if(info == NULL){
        pa2m_afirmar(false,"No se pudo crear la informacion");
    }

    pa2m_afirmar(simulador_simular_evento(simulador, ObtenerInformacionPokemonEnTratamiento, info) == ExitoSimulacion, "Obtener la informacion del pokemon devuelve ExitoSimulacion");

    free(estadisticas);
    free(info);
    simulador_destruir(simulador);
}

void SePuedeAvidinarElNivel_Correctamente(){
    hospital_t* hospital = hospital_crear();

    hospital_leer_archivo(hospital,"ejemplos/un_entrenador.hospital");

    simulador_t* simulador = simulador_crear(hospital);

    simulador_simular_evento(simulador, AtenderProximoEntrenador, NULL);

    Intento* intento = calloc(1,sizeof(Intento));
    if(intento == NULL){
        pa2m_afirmar(false,"No se pudo crear el intento");
    }

    intento->nivel_adivinado = 1;

    pa2m_afirmar(simulador_simular_evento(simulador, AdivinarNivelPokemon, intento) == ExitoSimulacion, "Intento adivinar el nivel del pokemon atendido con un numero bajo y devuelve ExitoSimulacion");

    pa2m_afirmar(!intento->es_correcto, "El nivel no es el correcto");
    pa2m_afirmar(intento->resultado_string != NULL, "El string con la descripcion del resultado no es null");

    intento->nivel_adivinado = 500;

    pa2m_afirmar(simulador_simular_evento(simulador, AdivinarNivelPokemon, intento) == ExitoSimulacion, "Intento adivinar el nivel del pokemon atendido con un numero alto y devuelve ExitoSimulacion");

    pa2m_afirmar(!intento->es_correcto, "El nivel no es el correcto");
    pa2m_afirmar(intento->resultado_string != NULL, "El string con la descripcion del resultado no es null");

    intento->nivel_adivinado = 31;

    pa2m_afirmar(simulador_simular_evento(simulador, AdivinarNivelPokemon, intento) == ExitoSimulacion, "Intento adivinar el nivel del pokemon atendido con un numero cercano y devuelve ExitoSimulacion");

    pa2m_afirmar(!intento->es_correcto, "El nivel no es el correcto");
    pa2m_afirmar(intento->resultado_string != NULL, "El string con la descripcion del resultado no es null");

    intento->nivel_adivinado = 37;

    pa2m_afirmar(simulador_simular_evento(simulador, AdivinarNivelPokemon, intento) == ExitoSimulacion, "Intento adivinar el nivel del pokemon atendido con un numero aún mas cercano y devuelve ExitoSimulacion");

    pa2m_afirmar(!intento->es_correcto, "El nivel no es el correcto");
    pa2m_afirmar(intento->resultado_string != NULL, "El string con la descripcion del resultado no es null");

    intento->nivel_adivinado = 39;

    pa2m_afirmar(simulador_simular_evento(simulador, AdivinarNivelPokemon, intento) == ExitoSimulacion, "Intento adivinar el nivel del pokemon atendido con un numero menos del correcto y devuelve ExitoSimulacion");

    pa2m_afirmar(!intento->es_correcto, "El nivel no es el correcto");
    pa2m_afirmar(intento->resultado_string != NULL, "El string con la descripcion del resultado no es null");

    intento->nivel_adivinado = 40;

    pa2m_afirmar(simulador_simular_evento(simulador, AdivinarNivelPokemon, intento) == ExitoSimulacion, "Intento adivinar el nivel del pokemon atendido con el numero correcto y devuelve ExitoSimulacion");

    pa2m_afirmar(intento->es_correcto, "El nivel es el correcto");
    pa2m_afirmar(intento->resultado_string != NULL, "El string con la descripcion del resultado es null");

    InformacionPokemon* info = calloc(1,sizeof(InformacionPokemon));
    if(info == NULL){
        pa2m_afirmar(false,"No se pudo crear la informacion");
    }

    pa2m_afirmar(simulador_simular_evento(simulador, ObtenerInformacionPokemonEnTratamiento,info) == ExitoSimulacion, "Obtener la informacion del pokemon devuelve ExitoSimulacion");
    pa2m_afirmar(strcmp(info->nombre_pokemon, "pikachu") == 0, "El pokemon que está siendo atendido es el de menor nivel (pikachu)");
    pa2m_afirmar(strcmp(info->nombre_entrenador, "Mariano") == 0, "El entrenador de pikachu es Mariano");

    EstadisticasSimulacion* estadisticas = calloc(1,sizeof(EstadisticasSimulacion));
    if(estadisticas == NULL){
        pa2m_afirmar(false,"No se pudo crear la estadisticas");
    }

    pa2m_afirmar(simulador_simular_evento(simulador, ObtenerEstadisticas, estadisticas) == ExitoSimulacion, "Obtener las estadisticas devuelve ExitoSimulacion");
    pa2m_afirmar(estadisticas->cantidad_eventos_simulados == 9, "La cantidad de eventos simulados es 9");
    pa2m_afirmar(estadisticas->entrenadores_totales == 1, "La cantidad de entrenadores es 1");
    pa2m_afirmar(estadisticas->entrenadores_atendidos == 0, "La cantidad de entrenadores atendidos es 0"); //! FIX ME
    pa2m_afirmar(estadisticas->pokemon_totales == 3, "La cantidad de pokemon totales es 3");
    pa2m_afirmar(estadisticas->pokemon_atendidos == 1, "La cantidad de pokemon atendidos es 1");
    pa2m_afirmar(estadisticas->pokemon_en_espera == 1, "La cantidad de pokemon en espera es 1 (uno está en el consultorio)");
    pa2m_afirmar(estadisticas->puntos > 0, "La cantidad de puntos es mayor a 0");

    unsigned int guardar_estado_puntos = estadisticas->puntos;

    intento->nivel_adivinado = 50;

    pa2m_afirmar(simulador_simular_evento(simulador, AdivinarNivelPokemon, intento) == ExitoSimulacion, "Adivino el nivel del próximo pokemon y devuelve ExitoSimulacion");
    pa2m_afirmar(intento->es_correcto == true, "El nivel es el correcto");

    intento->nivel_adivinado = 101;

    pa2m_afirmar(simulador_simular_evento(simulador, AdivinarNivelPokemon, intento) == ExitoSimulacion, "Adivino el nivel del último pokemon devuelve ExitoSimulacion");
    pa2m_afirmar(intento->es_correcto == true, "El nivel es el correcto");

    intento->nivel_adivinado = 0;

    pa2m_afirmar(simulador_simular_evento(simulador, AdivinarNivelPokemon, intento) == ErrorSimulacion, "Adivino el nivel de un pokemon inexistente y devuelve ErrorSimulacion");

    pa2m_afirmar(simulador_simular_evento(simulador, ObtenerInformacionPokemonEnTratamiento,info) == ErrorSimulacion, "Obtener la informacion del pokemon devuelve ErrorSimulacion ya que no hay mas pokemones");
    pa2m_afirmar(info->nombre_pokemon == NULL, "El nombre del pokemon es NULL");
    pa2m_afirmar(info->nombre_entrenador == NULL, "El nombre del entrenador es NULL");

    pa2m_afirmar(simulador_simular_evento(simulador, ObtenerEstadisticas, estadisticas) == ExitoSimulacion, " Obtener estadísticas devuelve ExitoSimulacion");
    pa2m_afirmar(estadisticas->cantidad_eventos_simulados == 14, "La cantidad de eventos simulados es 14");
    pa2m_afirmar(estadisticas->entrenadores_totales == 1, "La cantidad de entrenadores es 1");
    pa2m_afirmar(estadisticas->entrenadores_atendidos == 0, "La cantidad de entrenadores atendidos es 0");
    pa2m_afirmar(estadisticas->pokemon_totales == 3, "La cantidad de pokemon totales es 3");
    pa2m_afirmar(estadisticas->pokemon_atendidos == 1, "La cantidad de pokemon atendidos es 1");
    pa2m_afirmar(estadisticas->pokemon_en_espera == 0, "La cantidad de pokemon en espera es 0");
    pa2m_afirmar(estadisticas->puntos > guardar_estado_puntos, "La cantidad de puntos es mayor que antes");

    pa2m_afirmar(simulador_simular_evento(simulador, FinalizarSimulacion, NULL) == ExitoSimulacion, "Finalizar la simulación devuelve ExitoSimulacion");

    free(intento);
    free(info);
    free(estadisticas);
    simulador_destruir(simulador);
}

int main(){

    pa2m_nuevo_grupo("Pruebas de creacion y destruccion de simulador");
    NoSePuedeCrearUnSimuladorConHospitalNULL();
    SePuedeCrearUnSimuladorConHospitalVacio();
    SePuedeCrearUnSimuladorConHospitalInvalido();
    SePuedeCrearUnSimulador_Correctamente();

    pa2m_nuevo_grupo("Pruebas de inicializacion de obtenerEstadisticas");
    SePuedeObtenerEstadisticas_correctamente();

    pa2m_nuevo_grupo("Pruebas de atender entrenador");
    SePuedeAtenderEntrenador_Correctamente();

    pa2m_nuevo_grupo("Pruebas de ObtenerInformacionPokemonEnTratamiento");
    SePuedeObtenerInformacionPokemonEnTratamiento_Correctamente();

    pa2m_nuevo_grupo("Pruebas completas y de AdivinarNivelPokemon");
    SePuedeAdivinarNivelPokemon_Correctamente();

    pa2m_nuevo_grupo("Pruebas de AgregarDificultad");
    SePuedeAgregarUnaDificultad_Correctamente();

    pa2m_nuevo_grupo("Pruebas de SeleccionarDificultad");
    SeleccionarDificultad_Correctamente();

    pa2m_nuevo_grupo("Pruebas de ObtenerDificultad");
    NoSePuedeObtenerDificultadInexistente();
    SePuedeObtenerDificultad_Correctamente();

    pa2m_nuevo_grupo("Pruebas con hospital vacio - Recreacion Chanutron");
    SePuedeOperarConHospitalVacio_Correctamente();

    pa2m_nuevo_grupo("Pruebas con hospital con 1 entrenador - Recreacion Chanutron");
    SePuedeOperarConHospitalConUnEntrenador_Correctamente();

    pa2m_nuevo_grupo("Pruebas de avidinar el nivel - Recreacion Chanutron");
    SePuedeAvidinarElNivel_Correctamente();

    return pa2m_mostrar_reporte();
}