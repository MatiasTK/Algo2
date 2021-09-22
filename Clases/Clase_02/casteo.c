#include <stdio.h>

//El short compone 2 bytes

int main(){
    short numero = 0x4241; //Escrito en forma hexadecimal
    char byte1,byte2;

    char* pnumero = (char*)&numero;

    byte1 = pnumero[0]; 
    byte2 = pnumero[1];

    printf("Numero: %x, primer byte: %x, segundo byte: %x\n",numero,byte1,byte2);
}