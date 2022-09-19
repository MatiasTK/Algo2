#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inicial_primo = 0; // 0 para si, 1 para no

int devuelve_siempre_numero_primo(size_t cantidad_ingresada) {
    if(cantidad_ingresada == 1){
        inicial_primo = 1;
        return devuelve_siempre_numero_primo(cantidad_ingresada+1);
    }
    int encontre = 0; // 0 si encontre, 1 si no encontre
    for(size_t i = 2; i <= (cantidad_ingresada / 2); i++){
        if(cantidad_ingresada % i == 0){
            encontre = 1;
            break;
        }
    }
    if(encontre == 0){
        if(inicial_primo == 1){
            return (int)cantidad_ingresada;
        }else if(inicial_primo == 0){
            return 0;
        }
    }else{
        inicial_primo = 1;
        return devuelve_siempre_numero_primo(cantidad_ingresada+1);
    }
}


int main(int argc, char const *argv[]){
    
    int r = devuelve_siempre_numero_primo(11);

    printf("El numero primo es: %i",r);

    return 0;
}
