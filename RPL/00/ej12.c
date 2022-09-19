#include <stdio.h>

int numero_mas_grande(FILE* archivo){
    int n1,n2,n3;
    int leer = fscanf(archivo,"%i;%i;%i;\n",&n1,&n2,&n3);

    printf("%i,%i,%i",n1,n2,n3);

    int mayor = n1;

    while(leer == 3){
        if(n1 == -20 or n2 == -20 or n3 == -20){
            return -20;
        }

        if(n1 > mayor){
            mayor = n1;
        }
        if(n2 > mayor){
            mayor = n2;
        }
        if(n3 > mayor){
            mayor = n3;
        }
        leer = fscanf(archivo,"%i;%i;%i;\n",&n1,&n2,&n3);
    }
    return mayor;
}

int main(){

    FILE* archivo = fopen("archivo.txt","r");
    if(!archivo){
        printf("No se pudo abrir el archivo");
        return 0;
    }

    int a = numero_mas_grande(archivo);

    fclose(archivo);

    printf("\nRespuesta: %i",a);

    return 0;
}