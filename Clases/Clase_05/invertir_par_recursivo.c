#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void invertir_de_a_dos(const char* string){
    if(!string){
        return;
    }

    char a = string[0];
    char b = string[1];

    if(!b){
        return;
    }

    printf("%c%c",b,a);
    invertir_de_a_dos(string+2);
}

int main(int argc, char const *argv[]){
    
    char* string = "ABCDE"; // Deberia dar BADC

    invertir_de_a_dos(string);

    return 0;
}
