#include <stdio.h>

/* 
_Complejidad del algoritmo: no se mide en tiempo, sino en instrucciones -> cuantas veces tiene que ejecutar 
una cierta funcion
_Big O: Describe el comportamiento del algoritmo -> Como se comporta segun el tamaño del problema -> 
Esta siempre por arriba del tiempo de ejecucion -> Es como que te dice mas de esto no va a tardar
_Big Omega: Lo mismo que big o pero en vez de estar por arriba del tiempo de ejecucion esta por abajo
_Big Theta: es la mezcla de big o y big omega
*/

int sumar_numeros_1(int limite){
    int suma = 0;
    for(int i = 0; i < limite; i++){
        suma += i;
    }
    return suma;
}

int sumar_numeros_2(int limite){
    return limite * (limite + 1)/2;
}

int main(){
    int s1 = sumar_numeros_1(10);
    int s2 = sumar_numeros_2(10);

    printf("Suma1: %i , Suma2: %i",s1,s2);

    return 0;
}