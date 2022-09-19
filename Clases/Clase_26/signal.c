#include <stdio.h>

int main(int argc, char* argv[]){

    char linea[100];
    char* s;

    while(s = fgets(linea,100,stdin)){ //stdin es la entrada. teclado.
        printf("Escribiste %s",linea);
    }

    int edad;

    printf("Ingrese su edad: "); 
    scanf("%d",&edad); // No me deja ingresar la edad con control+D. Ya que control D mata al stdin.

    printf("\nSu edad es %d\n",edad);

    printf("Dejo de leer\n");

    /* 
    Explicacion: Copia lo escrito por terminal. Con control+c aborta el programa, no imprime la ultima linea. Control+d termina el programa, imprime la ultima linea.
    */

    return 0;
}