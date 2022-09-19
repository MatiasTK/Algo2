#ifndef SUBE_INTERNO_H
#define SUBE_INTERNO_H
#include "sube.h"

struct _sube_t{
    unsigned id;
    double saldo;
    unsigned dni;
    bool tiene_beneficio;
    viaje_t viajes[CANTIDAD_MAXIMA_VIAJES];
};

bool saldo_alcanza_para_viaje(sube_t* sube, double saldo);

#endif // !SUBE_INTERNO_H

