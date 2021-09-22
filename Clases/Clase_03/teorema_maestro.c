#include <stdio.h>

int suma_recursiva(int n){

    int suma = 0, suma2 = 0;

    suma = f(n/2);
    suma2 = f(n/2);

    return suma + suma2;
}
/* 
Como f se llama 2 veces recursivamente -> a = 2
b = 2 ya que divide el problema entre 2
T(n) = 2 * T(n/2) + O(1)
-> n ^ (log_b a) -> n^(0) -> 1 -> O(1)
*/

long factorial(int n){
    
}
/* 
Este no es de formato divide y conquista ya que no divide el problema sino que lo resta
*/


int main(){

    suma_recursiva(10);

    return 0;
}