// EJ -> https://i.imgur.com/6jw9xJQ.png

typedef struct{
    bool devuelta;
    bool hay_moneda;
}Moneda;

typedef struct{
    bool llave_entregada;
}Llave;

typedef struct{
    void* elemento;
    bool ocupado;
    Moneda* moneda;
    Llave* llave;
}Casillero;

typedef struct{
    Casillero* casilleros;
    size_t cantidad;
}Locker;

Locker locker_crear(size_t cantidad){
    Locker* locker = calloc(1, sizeof(Locker)*cantidad);
    if(!locker){
        return NULL;
    }
    locker->cantidad = cantidad;
    return locker;
}

void iniciar_casilleros(Locker* locker){
    for(int i = 0; i < locker->cantidad; i++){
        locker->casilleros[i].ocupado = false;
        locker->casilleros[i].Moneda.hay_moneda = false;
        Locker->casilleros[i].Llave.llave_entregada = false;
    }
}

Casillero obtener_casillero_vacio(Locker* locker, size_t indice){
    for(int i = 0; i < locker->cantidad; i++){
        if(locker->casilleros[i].ocupado == false){
            if(locker->casilleros->moneda->hay_moneda == false){
                return locker->casilleros[i];
            }
        }
    }
}

Locker* insertar_elemento_en_locker(Locker* locker, void* elemento, Moneda moneda){
    if(!locker || !Moneda){
        return NULL;
    }
    Casillero casillero = obtener_casillero_vacio(locker, locker->cantidad);
    casillero.elemento = elemento;
    casillero.moneda = &moneda;
    casillero.ocupado = true;
    return locker;
}

size_t cantidad_de_casilleros(Locker* locker){
    if(!locker){
        return 0;
    }
    return locker->cantidad;
}

void destruir_locker(Locker* locker){
    for(int i = 0; i < locker->cantidad; i++){
        if(locker->casilleros[i].ocupado){
            free(locker->casilleros[i].elemento);
        }
    }
    free(locker->casilleros);
    free(locker);
}