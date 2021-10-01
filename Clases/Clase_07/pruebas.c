#include "sube.h"
#include "pa2mm.h"
#include "sube_interno.h"

void SeCreaSubeExitosamente(){
    sube_t* sube = sube_crear(0,12345,false);

    pa2m_afirmar(sube != NULL, "La sube se crea correctamente");
    pa2m_afirmar(sube_consultar_saldo(sube) == 0.0, "La sube se crea con saldo 0");
    pa2m_afirmar(sube->dni == 12345,"La sube se crea don dni 12345");

    sube_destruir(sube);
}

void DadoSaldoPositivo_CargarSaldo_SaldoAumenta(){
    sube_t* sube = sube_crear(0,0,false);

    pa2m_afirmar(sube_cargar_saldo(sube,100) == 100.0,"Al cargar 100 de saldo, la tarjeta tiene 100 de saldo");
    pa2m_afirmar(sube_consultar_saldo(sube) == 100.0, "La sube tiene saldo 100");

    sube_destruir(sube);
}

void DadaTarjetaSinSaldoONegativoUsarSaldoNegativo(){

}


int main(){

    pa2m_nuevo_grupo("Pruebas de creacion");
    SeCreaSubeExitosamente();

    pa2m_nuevo_grupo("Pruebas de saldo");
    DadoSaldoPositivo_CargarSaldo_SaldoAumenta();

    pa2m_nuevo_grupo("Pruebas de viajes");
    DadaTarjetaSinSaldoONegativoUsarSaldoNegativo();

    return pa2m_mostrar_reporte();
}