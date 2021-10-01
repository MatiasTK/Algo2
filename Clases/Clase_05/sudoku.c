#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//                          OBVIAMENTE NO ESTA COMPLETO ES ILUSTRATIVO
// BACKTRACKING

#define SE_PUDO 1
#define NO_SE_PUDO 0

int resolver_proximo_casillero(Sudoku* sudoku){
    int x,y;
    if(proximo_casillero_libre(sudoku,&x,&y)){
        for(int valor = 1; valor <= 9; valor++){

            cambiar_casillero(sudoku,x,y,valor,0);

            if(validar_casillero(sudoku,x,y)){ // Si es valido paso al proximo casillero
                int pude_resolverlo = resolver_proximo_casillero(sudoku);
                if(pude_resolverlo){
                    return SE_PUDO;
                }
            }
        }
        cambiar_casillero(sudoku,x,y,0,0); //Borro los intentos que anote

        return NO_SE_PUDO;
    }else{
        return SE_PUDO;
    }
}

int main(int argc, char const *argv[]){
    
    Sudoku* sudoku = crear_sudoku();
    if(!sudoku){
        perror("No se pudo crear el tablero");
        return -1;
    }

    //Pistas
    cambiar_casillero(sudoku,4,0,2,1);
    cambiar_casillero(sudoku,2,1,5,1);
    cambiar_casillero(sudoku,6,5,8,1);
    cambiar_casillero(sudoku,3,7,3,1);
    cambiar_casillero(sudoku,1,2,2,1);
    cambiar_casillero(sudoku,8,6,7,1);
    cambiar_casillero(sudoku,4,3,1,1);
    cambiar_casillero(sudoku,5,3,2,1);

    mostrar(sudoku);

    if(!resolver_proximo_casillero(sudoku)){
        printf("No se pudo resolver\n");
    }else{
        printf("Se pudo resolver\n");
    }

    mostrar(sudoku);

    return 0;
}
