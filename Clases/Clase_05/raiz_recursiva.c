#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPSILON 0.0001

double absoluto(double n){
    return n>0?n:-n;
}

double raiz_rec(double n, double e){
    double estimacion_cuadrada = e*e;
    double diferencia = absoluto(estimacion_cuadrada - n);

    if(diferencia <= EPSILON){
        return e;
    }
    double nueva_e = (e+n/e)/2.0;

    return raiz_rec(n,nueva_e);
}

double raiz(double n){
    if(n < 0){
        printf("No se puede calcular la raiz de un negativo\n");
        return -1;
    }

    double estimacion_inicial = n/2;

    return raiz_rec(n,estimacion_inicial);
}

int main(int argc, char const *argv[]){
    
    double n = 50;

    double raiz_n = raiz(n);

    printf("La raiz de %f es %f\n",n,raiz_n);

    return 0;
}
