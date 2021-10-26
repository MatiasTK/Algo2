#include "pa2mm.h"
#include "abb.h"
#include <stdbool.h>
#include <string.h>

typedef struct{
    int dni;
    char* nombre;
    double promedio;
}alumno_t;

int comparar_alumnos(void* _a1,void* _a2){
    alumno_t* a1 = _a1;
    alumno_t* a2 = _a2;
    return a1->dni - a2->dni;
}

struct datos_aux{
    alumno_t** alumnos;
    int indice;
}

void expulsar_alumno(void* a){
    alumno_t* alumno = a;

    printf("Expulso al alumno: %s",alumno->nombre);
}

bool guardar_alumno(void* a,void* aux){
    alumno_t* alumno = a;
    
    struct datos_aux *datos = aux;

    datos->alumnos[datos->indice] = alumno;
    datos->indice++;

    return true;
}

void pruebas(){
    abb_t* abb = abb_crear();

    alumno_t carlos = {.dni=2341,.nombre="Carlos",.promedio=9.5};
    alumno_t victor = {.dni=4321,.nombre="Victor",.promedio=9.75};
    alumno_t ignacio = {.dni=1234,.nombre="Ignacio",.promedio=9.25};
    alumno_t maria = {.dni=4312,.nombre="Maria",.promedio=9.95};

    abb = abb_insertar(abb,&carlos,comparar_alumnos);
    abb = abb_insertar(abb,&victor,comparar_alumnos);
    abb = abb_insertar(abb,&ignacio,comparar_alumnos);
    abb = abb_insertar(abb,&maria,comparar_alumnos);

    alumno_t alumno_a_buscar = {.dni=1234,.nombre="",.promedio=0};
    pa2m_afirmar(&ignacio == abb_buscar(abb,&alumno_a_buscar,comparar_alumnos),"Al buscar");

    alumno_t* alumnos_inorden[5];
    struct datos_aux datos;
    datos.alumnos = alumnos_inorden;
    datos.indice = 0;

    abb_con_cada_elemento(abb,INORDEN,guardar_alumno,&datos);

    pa2m_afirmar(alumnos_inorden[0]==&ignacio,"El primer elemento inorden es ignacio");
    pa2m_afirmar(alumnos_inorden[1]==&carlos,"El segundo elemento inorden es ignacio");
    pa2m_afirmar(alumnos_inorden[2]==&maria,"El tercer elemento inorden es ignacio");
    pa2m_afirmar(alumnos_inorden[3]==&victor,"El cuarto elemento inorden es ignacio");

    abb_quitar(abb,&ignacio,comparar_alumnos,expulsar_alumno);

   /*  abb_destruir(abb); */
    abb_destruir_todo(abb,expulsar_alumno);
}

int main(){
    pa2m_nuevo_grupo("Pruebas");
    pruebas();

    return pa2m_mostrar_reporte();
}