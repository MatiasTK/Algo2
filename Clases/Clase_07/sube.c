#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "sube.h"


struct _sube_t{
    unsigned id;
    double saldo;
    unsigned dni;
    bool tiene_beneficio;
    viaje_t viajes[CANTIDAD_MAXIMA_VIAJES];
};

sube_t* sube_crear(unsigned id,unsigned dni, bool tiene_beneficio){
    sube_t* sube = calloc(1,sizeof(sube_t));
    if(!sube){
        return NULL;
    }
    sube->dni = dni;
    sube->id = id;
    sube->saldo = 0;
    sube->tiene_beneficio = tiene_beneficio;

    return sube;
}

void sube_destruir(sube_t* sube){
    free(sube);
    return;
}


double sube_cargar_saldo(sube_t* sube, double saldo){
    if(!sube){
        return NAN;
    }
    sube->saldo += saldo;
    return sube->saldo;
}

double sube_consultar_saldo(sube_t* sube){
    if(!sube){
        return NAN;
    }
    return sube->saldo;
}


double sube_pagar_viaje(sube_t* sube,double costo,unsigned transporte){
    return 0;
}

bool sube_habilitar(sube_t* sube){
    return false;
}

bool sube_deshabilitar(sube_t* sube){
    return false;
}

bool sube_transferir_saldo(sube_t* sube,sube_t* otra_sube, double saldo){
    return false;
}   
