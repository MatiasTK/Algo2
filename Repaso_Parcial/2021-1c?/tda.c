//EJ -> https://i.imgur.com/zxx95F0.png
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    double saldo;
    int id;
    Viaje ultimos_viajes[10]; //! IMPORTANTE -> NO PUEDE SER UN INT TIENE QUE SER OTRO STRUCT
    size_t cantidad_viajes;
}SUBE;

typedef struct{
    double costo;
    int linea;
    int interno;
}Viaje;

SUBE* sube_crear(int id){
    SUBE* tarjeta = calloc(1, sizeof(SUBE));
    if(!tarjeta){
        return NULL;
    }
    tarjeta->id = id;
}

int sube_realizar_viaje(SUBE* tarjeta, int linea, int interno, double costo){
    if(!tarjeta){
        return -1;
    }
    if(tarjeta->saldo < costo){
        return -1;
    }
    Viaje v;
    v.costo = costo;
    v.interno = interno;
    v.linea = linea;

    size_t indice = tarjeta->cantidad_viajes % 10; // Modulo -> para ser vector circular

    tarjeta->ultimos_viajes[indice] = v;
    tarjeta->cantidad_viajes++;

    return 0;
}

double consultar_saldo(SUBE* tarjeta){
    return tarjeta->saldo;
}

double cargar_saldo(SUBE* tarjeta, double cantidad){
    tarjeta->saldo += cantidad;
    return tarjeta->saldo;
}

size_t cantidad_viajes_realizados(SUBE* tarjeta){
    return tarjeta->cantidad_viajes;
}

Viaje Sube_consultar_ultimo_viaje(SUBE* tarjeta){
    return tarjeta->ultimos_viajes[tarjeta->cantidad_viajes - 1];
}

void sube_destruir(SUBE* tarjeta){
    free(tarjeta);
}