#ifndef __BATALLAS_H__
#define __BATALLAS_H__

#define GANA_PRIMERO 1
#define GANA_SEGUNDO -1

/*
 * Se deberan implementar las 5 funciones de batalla.
 * Las reglas para decidir al ganador las inventan ustedes
 * 
 * Si el ganador es el primer pokemon, se devolvera 1
 * Si el ganador es el segundo pokemon, se devolvera -1
 * 
 * No habran empates.
 */

typedef int (*funcion_batalla)(void*, void*); // Agrego tipo de dato para el puntero a función de batalla

int funcion_batalla_1(void* pkm_1, void* pkm_2);

int funcion_batalla_2(void* pkm_1, void* pkm_2);

int funcion_batalla_3(void* pkm_1, void* pkm_2);

int funcion_batalla_4(void* pkm_1, void* pkm_2);

int funcion_batalla_5(void* pkm_1, void* pkm_2);


#endif /* __BATALLAS_H__ */