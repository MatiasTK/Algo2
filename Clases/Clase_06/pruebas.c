#include "leer_linea.h"
#include <stdbool.h>
#include "pa2mm.h" // Framework de testing

void DadoUnArchivoVacioAlLeerUnaLineaDevuelveNULL(){
    FILE* archivo = fopen("vacio.txt","r");
    if(!archivo){
        pa2m_afirmar(false,"No se puede abrir el archivo de prueba");
    }

    char* linea_leida = NULL;

    pa2m_afirmar((leer_linea(archivo)) == NULL,"No puedo leer lineas en un archivo vacio");

    fclose(archivo);
}

void DadoUnArchivoNoVacioAlLeerUnaLineaDevuelvePrimerLinea(){
    FILE* archivo = fopen("prueba_corta.txt","r");
    if(!archivo){
        pa2m_afirmar(false,"No se puede abrir el archivo de prueba");
    }

    char* linea = leer_linea(archivo);

    pa2m_afirmar(linea != NULL, "Leer lineas es un archivo no vacio resulta en diferente de NULL");
    pa2m_afirmar(strcmp(linea,"linea1\n") == 0, "La linea leida es correcta");

    free(linea);

    fclose(archivo);
}

void DadoUnArchivoNoVacioLargoAlLeerUnaLineaDevuelvePrimerLinea(){
    FILE* archivo = fopen("prueba_larga.txt","r");
    if(!archivo){
        pa2m_afirmar(false,"No se puede abrir el archivo de prueba");
    }

    char* linea = leer_linea(archivo);

    pa2m_afirmar(linea != NULL, "Leer lineas largo es un archivo no vacio resulta en diferente de NULL");
    pa2m_afirmar(strcmp(linea,"Esto es una prueba larga para ver si pasa el test, si lee esto correctamente deberia de poder pasar el test\n") == 0, "La linea larga leida es correcta");

    free(linea);

    fclose(archivo);
}

void DadoUnArchivoNoVacioConVariasLineasDevuelveVariasLineas(){
    FILE* archivo = fopen("prueba_corta.txt","r");
    if(!archivo){
        pa2m_afirmar(false,"No se puede abrir el archivo de prueba");
    }

    char* linea = leer_linea(archivo);

    pa2m_afirmar(linea != NULL, "Leer lineas es un archivo no vacio resulta en diferente de NULL");
    pa2m_afirmar(strcmp(linea,"linea1\n") == 0, "La linea 1 leida es correcta");
    free(linea);
    pa2m_afirmar(strcmp(linea,"linea2\n") == 0, "La linea 2 leida es correcta");
    free(linea);
    pa2m_afirmar(strcmp(linea,"linea2\n") == 0, "La linea 3 leida es correcta");
    free(linea);

    fclose(archivo);
}


int main(){

    pa2m_nuevo_grupo("Pruebas de leer archivos vacios");
    DadoUnArchivoVacioAlLeerUnaLineaDevuelveNULL();

    pa2m_nuevo_grupo("Pruebas de leer archivos no vacios");
    DadoUnArchivoNoVacioAlLeerUnaLineaDevuelvePrimerLinea();
    DadoUnArchivoNoVacioLargoAlLeerUnaLineaDevuelvePrimerLinea();

    pa2m_nuevo_grupo("Pruebas de leer varias lineas de archivos no vacios");
    DadoUnArchivoNoVacioConVariasLineasDevuelveVariasLineas();

    return pa2m_mostrar_reporte();
}