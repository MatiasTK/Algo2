#define MAX_NOMBRE 500

typedef struct ciudad {
    char nombre[MAX_NOMBRE];
    int habitantes;
    struct ciudad *proxima;
    struct ciudad* anterior;
} ciudad_t;

typedef struct mapa{
    ciudad_t* origen;
}mapa_t;

int agregar_ciudad(mapa_t* mapa, ciudad_t* ciudad_nueva, ciudad_t* ciudad_anterior){
    if(!mapa){
        return -1;
    }
    if(mapa->origen->anterior == ciudad_anterior){
        mapa->origen->proxima
    }
}

int intercambiar_extremos(mapa_t* mapa){
    if(!mapa){
        return -1;
    }
    if(mapa->origen->anterior == NULL){
        ciudad_t* extremo_inicial = mapa->origen;
    }
    if(mapa->origen->proxima == NULL){
        ciudad_t* extremo_final = mapa->origen;
    }
    return intercambiar_extremos(mapa->origen->proxima);
    
}