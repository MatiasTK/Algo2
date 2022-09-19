#include <stdio.h>

int main(){

    int numero = 5;
    int* p_numero; // No conviene asignarle numeros exceptuando 0

    p_numero = &numero;
    p_numero[0] = 10;

    printf("La direccion de memoria de numero es: %p\n",&numero);
    printf("El valor almacenado en p_numero es: %p\n",p_numero);
    printf("El numero es %i\n",numero);

    return 0;
}