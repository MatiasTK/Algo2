#include "hospital.h"
#include "split.h"

struct _hospital_pkm_t{
    size_t cantidad_pokemon;
    pokemon_t* vector_pokemones;
};

struct _pkm_t{
    char* nombre;
    size_t nivel;
};

hospital_t* hospital_crear(){
    return NULL;
}

bool hospital_leer_archivo(hospital_t* hospital, const char* nombre_archivo){
    return false;
}

size_t hospital_cantidad_pokemon(hospital_t* hospital){
    return 0;
}

size_t hospital_cantidad_entrenadores(hospital_t* hospital){
    return 0;
}

size_t hospital_a_cada_pokemon(hospital_t* hospital, bool (*funcion)(pokemon_t* p)){
    return 0;
}

void hospital_destruir(hospital_t* hospital){

}

size_t pokemon_nivel(pokemon_t* pokemon){
    return 0;
}

const char* pokemon_nombre(pokemon_t* pokemon){
    return NULL;
}
