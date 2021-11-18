#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//! El enunciado pide calcularla sin usar while o for

int max(int a, int b){
    return a>b?a:b; // Si a > b retorna a, sino b
}

//* Recordar: la altura es el tamaño desde la raiz hasta la rama mas larga
int calcular_altura_abb(abb_t* abb,){
    if(!abb){
        return 0;
    }
    return 1 + max(calcular_altura_abb(abb->der),calcular_altura_abb(abb->izq))
}

//Costo total por teorema maestro -> n*log(n)
//! Teorema maestro solo sirve para arboles balanceados!
//* completa los campos fe en los nodos del arbol
int completar_factor_equilibrio(abb_t* abb){
    if(!abb){
        return 0;
    }
    //Costo n^(log_2(2)) -> O(n)
    completar_factor_equilibrio(abb->der);
    completar_factor_equilibrio(abb->izq);

    // Costo O(n)
    abb->fe = calcular_altura_abb(abb->der) - calcular_altura_abb(abb->izq);
    return 0;
}

//? Reutilizar codigo en la parte anterior me aumento la complejidad del algoritmo
//O(n)
int completar_factor_equilibrio_2(abb_t* abb){
    if(!abb){
        return 0;
    }
    //nlog^(1) -> O(n)
    int h_der = completar_factor_equilibrio_2(abb->der);
    int h_izq = completar_factor_equilibrio_2(abb->izq);
    // O(1)
    abb->fe = h_der - h_izq;
    return 1 + max(h_izq,h_der);
}
