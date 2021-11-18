// EJ -> https://i.imgur.com/syVDkd2.png
#include <stdio.h>
#include <string.h>

void mostrar(char string[]){
    printf("%s",string);
}

void invertir_de_a_pares(char* string){
    if(!string || !*string){
        return;
    }
    if(string[1] == '\0'){
        return;
    }

    //swap
    char aux = string[0];
    string[0] = string[1];
    string[1] = aux;

    invertir_de_a_pares(string+2);
}

//EJ -> https://i.imgur.com/n9tAfZz.png

int proxima_potencia_de_dos_rec(int n, int actual){
    if(actual == n){
        return actual;
    }
    if(actual > n){
        return actual;
    }
    return proxima_potencia_de_dos_rec(n,actual*2);
}

int proxima_potencia_de_dos(int n){
    if(n == 1){
        return 1;
    }
    return proxima_potencia_de_dos_rec(n,1);
}

int main(){

    char p_string[] = "ABCDE";
    invertir_de_a_pares(p_string);
    mostrar(p_string);

    /* mostrar_n(proxima_potencia_de_dos(7)); */

    return 0;
}