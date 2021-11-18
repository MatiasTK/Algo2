#include "batallas.h"
#include "aventura.h"

int funcion_batalla_1(void* pkm_1, void* pkm_2){
    
    pokemon_t pokemon1 = *(pokemon_t*)pkm_1;
    pokemon_t pokemon2 = *(pokemon_t*)pkm_2;
    //queda feo el casteo por todos lados, lo soluciono así

    int vida_pkm1 = pokemon1.velocidad + pokemon2.defensa;
    int vida_pkm2 = pokemon2.velocidad + pokemon2.defensa;

    int vida_final_pkm1 = vida_pkm1 - pokemon2.ataque;
    int vida_final_pkm2 = vida_pkm2 - pokemon2.ataque;

    if (vida_final_pkm1 > vida_final_pkm2)
        return GANO_PRIMERO;

    return GANO_SEGUNDO;
}

int funcion_batalla_2(void* pkm_1, void* pkm_2){

    pokemon_t pokemon1 = *(pokemon_t*)pkm_1;
    pokemon_t pokemon2 = *(pokemon_t*)pkm_2;
    //queda feo el casteo por todos lados, lo soluciono así

    int poder_total_pkm1 = pokemon1.velocidad + pokemon1.defensa + pokemon1.ataque;
    int poder_total_pkm2 = pokemon2.velocidad + pokemon2.defensa + pokemon2.ataque;

    if (poder_total_pkm1 > poder_total_pkm2)
        return GANO_PRIMERO;

    return GANO_SEGUNDO;
}

int funcion_batalla_3(void* pkm_1, void* pkm_2){

    pokemon_t pokemon1 = *(pokemon_t*)pkm_1;
    pokemon_t pokemon2 = *(pokemon_t*)pkm_2;
    //queda feo el casteo por todos lados, lo soluciono así

    int poder_total_pkm1 = pokemon1.velocidad * pokemon1.defensa * pokemon1.ataque;
    int poder_total_pkm2 = pokemon2.velocidad * pokemon2.defensa * pokemon2.ataque;

    if (poder_total_pkm1 > poder_total_pkm2)
        return GANO_PRIMERO;

    return GANO_SEGUNDO;
}

int funcion_batalla_4(void* pkm_1, void* pkm_2){

    pokemon_t pokemon1 = *(pokemon_t*)pkm_1;
    pokemon_t pokemon2 = *(pokemon_t*)pkm_2;
    //queda feo el casteo por todos lados, lo soluciono así

    int poder_total_pkm1 = (pokemon1.velocidad + pokemon1.defensa) * pokemon1.ataque;
    int poder_total_pkm2 = (pokemon2.velocidad + pokemon2.defensa) * pokemon2.ataque;

    if (poder_total_pkm1 > poder_total_pkm2)
        return GANO_PRIMERO;

    return GANO_SEGUNDO;
}

int funcion_batalla_5(void* pkm_1, void* pkm_2){

    pokemon_t pokemon1 = *(pokemon_t*)pkm_1;
    pokemon_t pokemon2 = *(pokemon_t*)pkm_2;
    //queda feo el casteo por todos lados, lo soluciono así

    int poder_total_pkm1 = (pokemon1.velocidad * pokemon1.defensa) - pokemon1.ataque;
    int poder_total_pkm2 = (pokemon2.velocidad * pokemon2.defensa) - pokemon2.ataque;

    if (poder_total_pkm1 > poder_total_pkm2)
        return GANO_PRIMERO;

    return GANO_SEGUNDO;
}