#include <stdio.h>

//A partir del 4 byte -> en realidad el 5 -> lo castea a int y le suma el byte 05
modificar_algo(char* byte){
    (*(int*)byte) += 0x05050505;
}

int main(){
    char vector[9];

    for(int i = 0; i < 9; i++){
        vector[i] = 'A' + i;
    }

    modificar_algo((vector)+4); //Agarro el 5to elemento elemento del vector

    printf("a= %c, b = %c, c = %c, d = %c, e = %c, f = %c, g = %c, h = %c, i = %c\n",vector[0],vector[1],vector[2],vector[3],vector[4],vector[5],vector[6],vector[7],vector[8],vector[9]);

    return 0;
}