#ifndef SUBE_H_
#define SUBE_H_

#define CANTIDAD_MAXIMA_VIAJES 10
#define SALDO_MINIMO -100
#include <stdbool.h>

typedef struct{
    double latitud;
    double longitud;
}posicion_t;

typedef struct{
    double costo;
    unsigned long timestamp;
    unsigned transporte;
}viaje_t;

typedef struct _sube_t sube_t;

sube_t* sube_crear(unsigned id,unsigned dni, bool tiene_beneficio);

void sube_destruir(sube_t* sube);

//Devuelve NaN si hay error
double sube_cargar_saldo(sube_t* sube, double saldo);

double sube_consultar_saldo(sube_t* sube);

//Devuelve lo que paso o NaN
double sube_pagar_viaje(sube_t* sube,double costo,unsigned transporte);

bool sube_habilitar(sube_t* sube);

bool sube_deshabilitar(sube_t* sube);

bool sube_transferir_saldo(sube_t* sube,sube_t* otra_sube, double saldo);

#endif // !SUBE_H_