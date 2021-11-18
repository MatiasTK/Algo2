// EJ -> https://i.imgur.com/RCEKMHV.png
// DIAGRAMA -> https://i.imgur.com/PnMVOQx.png

#include <stdlib.h>

#define CANTIDAD_COSAS 5

typedef struct cosa_naranja{
    int cantidad;
    struct cosa_azul** puntero_cosas;
    struct cosa_azul* inicio;
}cosa_naranja_t;

typedef struct cosa_azul{
    int numero;
    char letra;
    struct cosa_azul* siguiente;
}cosa_azul_t;

void liberar(cosa_naranja_t* vector){
    for(int i = 0; i < 5; i++){
        free(vector->puntero_cosas[i]);
    }
    free(vector->puntero_cosas);
    free(vector);
}

int main(){
    char letras[] = "ABCDE";
    cosa_naranja_t* v1 = malloc(sizeof(cosa_naranja_t)); // v1 es un puntero a una estructura cosa_naranja_t V1 esta en stack!
    if(!v1){
        return 1;
    }
    v1->cantidad = CANTIDAD_COSAS;

    v1->puntero_cosas = malloc(sizeof(cosa_azul_t*)*CANTIDAD_COSAS);
    if(!v1->puntero_cosas){
        free(v1);
        return 1;
    }
    bool fallo = false;
    for(int i = 0; i < 5; i++){
        v1->puntero_cosas[i] = calloc(1, sizeof(cosa_azul_t));
        if(!v1->puntero_cosas[i]){
            fallo = true;
        }
        v1->puntero_cosas[i]->numero = i+1;
        v1->puntero_cosas[i]->letra = letras[i];
    }
    if(fallo){
        liberar(v1);
        return 1;
    }
    fallo = false;
    v1->inicio = v1->puntero_cosas[0];
    for(int j = 0; j < 4; j++){
        v1->puntero_cosas[j]->siguiente = v1->puntero_cosas[j+1];
    }
    v1->puntero_cosas[4]->siguiente = v1->inicio;
    cosa_azul_t* v2 = v1->puntero_cosas[2];

    liberar(v1);
    return 0;
}

