#include <stdio.h>
#include <stdbool.h>

bool buscar_polindromo(const char *cadena, size_t inicio, size_t fin){
    if(inicio >= fin){
        return true;
    }
    if(cadena[inicio] == cadena[fin]){
        return buscar_polindromo(cadena,inicio+1,fin-1);
    }
    return false;
}


int main(){
    
    bool r = buscar_polindromo("anilina",0,6);

    if(r){
        printf("Es verdad");
    }else{
        printf("Es mentira");
    }

    return 0;
}
