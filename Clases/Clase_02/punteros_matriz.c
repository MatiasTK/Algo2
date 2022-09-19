#include <stdio.h>

int main(){
    int matriz[5][5];
    int* matriz2 = malloc(5*5*sizeof(int));

    memset((void*)matriz,0,5*5*sizeof(int));
    memset(matriz2,0,5*5*sizeof(int));

    matriz[3][2] = matriz2[];
}