#include "batallas.h"
#include "definiciones.h"
/*
 * Se deberan implementar las 5 funciones de batalla.
 * Las reglas para decidir al ganador las inventan ustedes
 * 
 * Si el ganador es el primer pokemon, se devolvera 1
 * Si el ganador es el segundo pokemon, se devolvera -1
 * 
 * No habran empates.
 */

int funcion_batalla_1(void* pkm_1, void* pkm_2) {
    if ( ((pokemon_t*)pkm_1)->ataque >= ((pokemon_t*)pkm_2)->defensa ) 
        return GANA_PRIMERO;
    return GANA_SEGUNDO;
}

/*
* Si la velocidad de 1 es mayor (o igual) a la defensa de 2, y además, la defensa de 
    1 es mayor al ataque de 2: GANA_PRIMERO. Sino, GANA_SEGUNDO.
*
*/
int funcion_batalla_2(void* pkm_1, void* pkm_2) {
    if ( (((pokemon_t*)pkm_1)->velocidad >= ((pokemon_t*)pkm_2)->defensa) && (((pokemon_t*)pkm_1)->defensa > ((pokemon_t*)pkm_2)->ataque) )
        return GANA_PRIMERO;
    return GANA_SEGUNDO;
}

int funcion_batalla_3(void* pkm_1, void* pkm_2) {
    int puntos_pkm_1 = (((pokemon_t*)pkm_1)->velocidad) + (((pokemon_t*)pkm_1)->defensa) + (((pokemon_t*)pkm_1)->ataque);
    int puntos_pkm_2 = (((pokemon_t*)pkm_2)->velocidad) + (((pokemon_t*)pkm_2)->defensa) + (((pokemon_t*)pkm_2)->ataque);
    if (puntos_pkm_1 >= puntos_pkm_2)
        return GANA_PRIMERO;
    return GANA_SEGUNDO;
}

int funcion_batalla_4(void* pkm_1, void* pkm_2) {
    int puntos_pkm_1 = (((pokemon_t*)pkm_1)->ataque) + (((pokemon_t*)pkm_1)->defensa);
    int puntos_pkm_2 = (2*(((pokemon_t*)pkm_1)->velocidad));
    if (puntos_pkm_1 >= puntos_pkm_2)
        return GANA_PRIMERO;
    return GANA_SEGUNDO;
}

int funcion_batalla_5(void* pkm_1, void* pkm_2) {
    return GANA_PRIMERO;
}
