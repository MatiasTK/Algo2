#include "solucion.h"

bool escribir_pokemon(void* elemento_1, void* elemento_2){
    pokemon_t poke = *(pokemon_t*)elemento_1;

    FILE* archivo = (FILE*)elemento_2;

    fprintf(archivo,"%s;%i;%i;%i;%i\n",poke.nombre,poke.nivel,poke.fuerza,poke.inteligencia,poke.carisma);

    return true;
}

void escribir_pokemones_en_archivo(abb_t* pokemones, FILE* archivo){
    if(!pokemones || !archivo || abb_vacio(pokemones)){
        return;
    }

    abb_con_cada_elemento(pokemones,INORDEN,escribir_pokemon,archivo);
}