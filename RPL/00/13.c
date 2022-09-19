#include <stdio.h>
#include <string.h>
#define MAX_NOMBRE 30

typedef struct pokemon{
    char nombre[MAX_NOMBRE];
    int b_ganadas;
    int b_perdidas;
    int b_empatadas;
} pokemon_t;

pokemon_t pokemon_con_mas_batallas(FILE* archivo){
    pokemon_t pokemon;
    int leer = fscanf(archivo,"%[^;];\n%i;%i;%i;\n",pokemon.nombre,&(pokemon.b_ganadas),&(pokemon.b_perdidas),&(pokemon.b_empatadas));
    int mas_jugadas = (pokemon.b_ganadas + pokemon.b_perdidas + pokemon.b_empatadas);
    printf("Nombre del pokemon: %s, Ganadas: %i, Perdidas: %i, Empatadas: %i, Jugadas totales: %i",pokemon.nombre,pokemon.b_ganadas,pokemon.b_perdidas,pokemon.b_perdidas,mas_jugadas);
    pokemon_t ganador = pokemon;
    while(leer > 0){
        if((pokemon.b_ganadas + pokemon.b_perdidas + pokemon.b_empatadas) > mas_jugadas){
            mas_jugadas = (pokemon.b_ganadas + pokemon.b_perdidas + pokemon.b_empatadas);
            pokemon_t ganador = pokemon;
        }
        leer = fscanf(archivo,"%[^;];\n%i;%i;%i;\n",pokemon.nombre,&(pokemon.b_ganadas),&(pokemon.b_perdidas),&(pokemon.b_empatadas));
    }
    return ganador;
}

int main(){
    FILE * archivo = fopen("pokemon.txt","r");
    if(!archivo){
        printf("No se pudo abrir pokemon.txt");
    }
    pokemon_con_mas_batallas(archivo);
    fclose(archivo);
}