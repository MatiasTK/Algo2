#include "pa2mm.h"
#include "src/hospital.h"
#include "src/lista.h"

#include "string.h"
#include <stdbool.h>
#include <stdio.h>

/* No intenten esto en sus casas */
/* Ya vamos a ver como evitar esto en el TDA Lista */
struct{
    pokemon_t* pokemon[500];
    size_t cantidad;
} acumulados;

// Copia de structs para poder hacer pruebas
struct _hospital_pkm_t{
    lista_t* lista_entrenadores;
    size_t cantidad_pokemon;
    size_t cantidad_entrenador;
};

struct _pkm_t{
    char* nombre;
    size_t nivel;
    entrenador_t* entrenador;
};

struct _entrenador_t{
    char* nombre;
    lista_t* lista_pokemones;
    size_t id;
};

bool imprimir_entrenador_y_nivel(pokemon_t* pokemon){

    printf("Pokemon: %s, Nivel: %ld, Entrenador: %s\n", pokemon_nombre(pokemon), pokemon_nivel(pokemon),pokemon->entrenador->nombre);

    return true;
}

// -----------------------------------------------------------------------------

bool ignorar_pokemon(pokemon_t* p){
    p = p;
    return true;
}

void resetear_acumulados(){
    acumulados.cantidad = 0;
}

bool acumular_pokemon(pokemon_t* p){
    printf("Acumulando %s\n", pokemon_nombre(p));
    acumulados.pokemon[acumulados.cantidad] = p;
    acumulados.cantidad++;
    return true;
}

bool acumular_pokemon_hasta_miltank(pokemon_t* p){
    acumulados.pokemon[acumulados.cantidad] = p;
    acumulados.cantidad++;
    return strcmp(pokemon_nombre(p), "miltank");
}

bool acumulados_en_orden_correcto(){
    if(acumulados.cantidad < 2)
        return true;
    pokemon_t* anterior = acumulados.pokemon[0];
    for(int i=1;i<acumulados.cantidad;i++){
        pokemon_t* actual =  acumulados.pokemon[i];
        if(strcmp(pokemon_nombre(anterior), pokemon_nombre(actual)) > 0)
            return false;
    }
    return true;
}

/* Pruebas */

void puedoCrearYDestruirUnHospital(){
    hospital_t* h=NULL;

    pa2m_afirmar((h=hospital_crear()), "Crear un hospital devuelve un hospital");

    pa2m_afirmar(hospital_cantidad_entrenadores(h)==0, "Un hospital se crea con cero entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h)==0, "Un hospital se crea con cero pokemon");

    pa2m_afirmar(hospital_a_cada_pokemon(h, ignorar_pokemon)==0, "Recorrer los pokemon resulta en 0 pokemon recorridos");

    hospital_destruir(h);
}

void dadoUnHospitalNULL_lasPuedoAplicarLasOperacionesDelHospitalSinProblema(){
    hospital_t* h=NULL;

    pa2m_afirmar(hospital_cantidad_entrenadores(h)==0, "Un hospital NULL tiene cero entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h)==0, "Un hospital NULL tiene cero pokemon");

    pa2m_afirmar(hospital_a_cada_pokemon(h, ignorar_pokemon)==0, "Recorrer los pokemon de un hospital NULL resulta en 0 pokemon recorridos");

    hospital_destruir(h);
}

void dadoUnArchivoVacio_NoSeAgreganPokemonAlHospital(){
    hospital_t* h=hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/archivo_vacio.hospital"), "Puedo leer un archivo vacío");

    pa2m_afirmar(hospital_cantidad_entrenadores(h)==0, "Un hospital vacío tiene cero entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h)==0, "Un hospital vacío tiene tiene cero pokemon");

    pa2m_afirmar(hospital_a_cada_pokemon(h, ignorar_pokemon)==0, "Recorrer los pokemon resulta en 0 pokemon recorridos");

    hospital_destruir(h);
}

void dadoUnArchivoConUnEntrenador_SeAgregaElEntrenadorYSusPokemonAlHospital(){
    hospital_t* h=hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/un_entrenador.hospital"), "Puedo leer un archivo con un entrenador");

    pa2m_afirmar(hospital_cantidad_entrenadores(h)==1, "El hospital tiene 1 entrenador");
    pa2m_afirmar(hospital_cantidad_pokemon(h)==3, "El hospital tiene 3 pokemon");

    resetear_acumulados();
    pa2m_afirmar(hospital_a_cada_pokemon(h, acumular_pokemon)==3, "Recorrer los pokemon resulta en 3 pokemon recorridos");
    pa2m_afirmar(acumulados_en_orden_correcto(), "Los pokemon se recorrieron en orden alfabetico");

    hospital_destruir(h);
}

void dadoUnArchivoConVariosEntrenadores_SeAgreganLosEntrenadoresYSusPokemonAlHospital(){
    hospital_t* h=hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/varios_entrenadores.hospital"), "Puedo leer un archivo con varios entrenadores");

    pa2m_afirmar(hospital_cantidad_entrenadores(h)==5, "El hospital tiene 5 entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h)==24, "El hospital tiene 24 pokemon");

    resetear_acumulados();
    pa2m_afirmar(hospital_a_cada_pokemon(h, acumular_pokemon)==24, "Recorrer los pokemon resulta en 24 pokemon recorridos");
    pa2m_afirmar(acumulados_en_orden_correcto(), "Los pokemon se recorrieron en orden alfabetico");

    hospital_destruir(h);
}

void dadosVariosArchivos_puedoAgregarlosTodosAlMismoHospital(){
    hospital_t* h=hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/varios_entrenadores.hospital"), "Puedo leer un archivo con varios entrenadores");
    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/varios_entrenadores.hospital"), "Puedo leer otro archivo con varios entrenadores");
    pa2m_afirmar(hospital_leer_archivo(h, "ejemplos/varios_entrenadores.hospital"), "Puedo leer un tercer archivo con varios entrenadores");

    pa2m_afirmar(hospital_cantidad_entrenadores(h)==15, "El hospital tiene 15 entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h)==72, "El hospital tiene 72 pokemon");

    resetear_acumulados();
    pa2m_afirmar(hospital_a_cada_pokemon(h, acumular_pokemon)==72, "Recorrer los pokemon resulta en 72 pokemon recorridos");
    resetear_acumulados();
    pa2m_afirmar(acumulados_en_orden_correcto(), "Los pokemon se recorrieron en orden alfabetico");

    hospital_destruir(h);
}

void DadoUnArchivoConXEntrenador_SeAgregaElEntrenadorYSusPokemonAlHospital(){
    hospital_t* h=hospital_crear();
    hospital_t* hl=hospital_crear();
    hospital_t* h1=hospital_crear();
    hospital_t* h2=hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(h,"ejemplos/no_existe.hospital") == false,"No puedo leer un archivo que no existe");
    pa2m_afirmar(hospital_leer_archivo(h1,"ejemplos/test_corto.hospital"),"Puedo leer un archivo con varios entrenadores");
    pa2m_afirmar(hospital_leer_archivo(h2,"ejemplos/test2.hospital"),"Puedo leer un archivo con varios entrenadores en otro hospital");
    pa2m_afirmar(hospital_leer_archivo(hl,"ejemplos/test.hospital"),"Puedo leer un archivo con strings largas");

    pa2m_afirmar(hospital_cantidad_entrenadores(h1)==8, "El hospital 1 tiene 8 entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h1)==30, "El hospital 1 tiene 30 pokemon");

    pa2m_afirmar(hospital_cantidad_entrenadores(h2)==5, "El hospital 2 tiene 5 entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(h2)==24, "El hospital 2 tiene 24 pokemon");

    pa2m_afirmar(hospital_cantidad_entrenadores(hl)==8, "El hospital de string largas tiene 8 entrenadores");
    pa2m_afirmar(hospital_cantidad_pokemon(hl)==30, "El hospital de string largas tiene 30 pokemon");

    resetear_acumulados();
    pa2m_afirmar(hospital_a_cada_pokemon(h1, NULL)==0, "Recorrer los pokemon con funcion NULL resulta 0 pokemon recorridos");

    resetear_acumulados();
    pa2m_afirmar(hospital_a_cada_pokemon(h1, acumular_pokemon_hasta_miltank)==18, "Recorrer los pokemon del hospital 1 hasta miltank resulta en 18 pokemon recorridos");
    pa2m_afirmar(acumulados_en_orden_correcto(), "Los pokemon se recorrieron en orden alfabetico");

    resetear_acumulados();
    pa2m_afirmar(hospital_a_cada_pokemon(h2, acumular_pokemon_hasta_miltank)==13, "Recorrer los pokemon del hospital 2 hasta miltank resulta en 13 pokemon recorridos");
    pa2m_afirmar(acumulados_en_orden_correcto(), "Los pokemon se recorrieron en orden alfabetico");

    resetear_acumulados();
    pa2m_afirmar(hospital_a_cada_pokemon(hl, acumular_pokemon)==30, "Recorrer los pokemon del hospital de string largas resulta en 30 pokemon recorridos");
    pa2m_afirmar(acumulados_en_orden_correcto(), "Los pokemon se recorrieron en orden alfabetico");

    hospital_destruir(h); 
    hospital_destruir(hl);
    hospital_destruir(h1);
    hospital_destruir(h2);
}

void dadoUnArchivoConVariosEntrenadores_PuedoObtenerSusDatos(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(hospital, "ejemplos/varios_entrenadores.hospital"), "Puedo leer un archivo con varios entrenadores");

    pa2m_afirmar(hospital_cantidad_entrenadores(hospital)==5, "El hospital tiene 5 entrenadores");

    pa2m_afirmar(hospital_guardar_archivo(hospital, "ejemplos/PuedoGuardar.hospital"), "Puedo guardar el hospital");

    pa2m_afirmar(hospital_a_cada_pokemon(hospital, acumular_pokemon)== 24, "Recorrer los pokemon con funcion NULL resulta 24 pokemon recorridos - deberian imprimirse en orden alfabetico");

    hospital_destruir(hospital);
}

void PuedoGuardarUnArchivoVacio(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(hospital, "ejemplos/archivo_vacio.hospital"), "Puedo leer un archivo vacio");
    pa2m_afirmar(!hospital_guardar_archivo(hospital, "ejemplos/PuedoGuardar_Vacio.hospital"), "No puedo guardar un archivo vacio");

    hospital_destruir(hospital);
}

void PuedoGuardarUnArchivoInvalido(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(hospital, "ejemplos/invalido.hospital"), "Puedo leer un archivo invalido");
    pa2m_afirmar(!hospital_guardar_archivo(hospital, "ejemplos/PuedoGuardar_Invalido.hospital"), "No puedo guardar un archivo invalido");

    hospital_destruir(hospital);
}

void PuedoObtenerDatosDelPokemon(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(hospital, "ejemplos/varios_entrenadores.hospital"), "Puedo leer un archivo con varios entrenadores");

    pa2m_afirmar(hospital_cantidad_entrenadores(hospital)==5, "El hospital tiene 5 entrenadores");

    pa2m_afirmar(hospital_a_cada_pokemon(hospital,imprimir_entrenador_y_nivel)==24, "Puedo los pokemones con sus niveles y entrenadores");

    hospital_destruir(hospital);
}

void imprimir_lista_entrenadores(hospital_t* hospital){

    lista_iterador_t* iterador = lista_iterador_crear(hospital->lista_entrenadores);

    while(lista_iterador_tiene_siguiente(iterador)){
        entrenador_t* entrenador = lista_iterador_elemento_actual(iterador);
        printf("ID: %ld - NOMBRE: %s\n",entrenador->id,entrenador->nombre);
        lista_iterador_avanzar(iterador);
    }

    lista_iterador_destruir(iterador);
}

void LaListaDeEntrenadoresSeCarga_Correctamente(){
    hospital_t* hospital = hospital_crear();

    pa2m_afirmar(hospital_leer_archivo(hospital, "ejemplos/varios_entrenadores.hospital"), "Puedo leer un archivo con varios entrenadores");

    pa2m_afirmar(hospital_cantidad_entrenadores(hospital)==5, "El hospital tiene 5 entrenadores");

    printf("Los entrenadores son:\n");

    imprimir_lista_entrenadores(hospital);

    hospital_destruir(hospital);
}

int main(){

    pa2m_nuevo_grupo("Pruebas de creación y destrucción");
    puedoCrearYDestruirUnHospital();

    pa2m_nuevo_grupo("Pruebas con NULL");
    dadoUnHospitalNULL_lasPuedoAplicarLasOperacionesDelHospitalSinProblema();

    pa2m_nuevo_grupo("Pruebas con un archivo vacío");
    dadoUnArchivoVacio_NoSeAgreganPokemonAlHospital();  

    pa2m_nuevo_grupo("Pruebas con un archivo de un entrenador");
    dadoUnArchivoConUnEntrenador_SeAgregaElEntrenadorYSusPokemonAlHospital();

    pa2m_nuevo_grupo("Pruebas con un archivo de varios entrenadores");
    dadoUnArchivoConVariosEntrenadores_SeAgreganLosEntrenadoresYSusPokemonAlHospital();

    pa2m_nuevo_grupo("Pruebas con mas de un archivo");
    dadosVariosArchivos_puedoAgregarlosTodosAlMismoHospital(); 

    pa2m_nuevo_grupo("Pruebas extras");
    DadoUnArchivoConXEntrenador_SeAgregaElEntrenadorYSusPokemonAlHospital(); 

    pa2m_nuevo_grupo("Pruebas de modificaciones para el TP2");
    dadoUnArchivoConVariosEntrenadores_PuedoObtenerSusDatos();
    PuedoGuardarUnArchivoVacio(); 
    PuedoGuardarUnArchivoInvalido();
    PuedoObtenerDatosDelPokemon();
    LaListaDeEntrenadoresSeCarga_Correctamente();

    return pa2m_mostrar_reporte();
}
