// EJ -> https://i.imgur.com/MLlBh9G.png

#include <stdlib.h>

typedef struct naranja{
    int n;
    struct naranja* vector[3];
} naranja_t;

int asignar_naranja(int n, naranja_t* naranja){
    for(int i = 0; i < 3; i++){
        naranja->vector[i] = calloc(1, sizeof(naranja_t));
        if(!naranja->vector[i]){
            return -1;
        }
        naranja->vector[i]->n = n;
    }
    return 0;
}

void liberar(naranja_t* naranja){
    for(int i = 0; i < 3; i++){
        free(naranja->vector[i]);
    }
}

int main(){
    naranja_t* cosa = malloc(sizeof(naranja_t)); 
    if(!cosa){
        return -1;
    }

    cosa->n = 2;
    int devuelto;
    devuelto = asignar_naranja(1, cosa);
    if(devuelto == -1){
        liberar(cosa);
        return -1;
    }
    for(int j = 0; j < 3; j++){
        devuelto = asignar_naranja(0, cosa->vector[j]);
        if(!devuelto){
            liberar(cosa);
            return -1;
        }
    }
    liberar(cosa);

    return 0;
}