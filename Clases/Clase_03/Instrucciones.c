#include <stdio.h>

// 2 instrucciones y 1 instruccion que se repite n veces -> 1 + n + 1 -> O(n)
int sumar_numeros_1(int limite){
    int suma = 0;
    for(int i = 0; i < limite; i++){
        suma += i;
    }
    return suma;
}

// 1 Instruccion -> O(1)
int sumar_numeros_2(int limite){
    return limite * (limite + 1)/2;
}

//4 instrucciones -> O(4 * 1) -> O(1) ya que 4 es constante
int sumar_numeros_3(int limite){
    int suma = limite;
    suma = suma * (limite+1);
    suma /= 2;
    return suma;
}

int main(){
    int s1 = sumar_numeros_1(10);
    int s2 = sumar_numeros_2(10);

    printf("Suma1: %i , Suma2: %i",s1,s2);

    return 0;
}