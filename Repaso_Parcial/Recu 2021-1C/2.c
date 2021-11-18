// EJ -> https://i.imgur.com/tvBKiyL.png

#include <stdlib.h>
#include <stdbool.h>

#define NUMERO 4
#define CANTIDAD_LETRAS 4

typedef struct Azul{
    char* letra;
    struct Azul* siguiente;
}Azul_t;

typedef struct {
    int numero;
    Azul_t* primero;
}Verde_t;

typedef struct{
    int numero;
    char** letras;
}Rosa_t;

void liberar_azules(Azul_t* azul){
    if(azul != NULL){
        liberar_azules(azul->siguiente);
        free(azul->letra);
        free(azul);
    }
}

void liberar(char* texto, Verde_t* p_verde, Azul_t* azul){
    free(texto);
    free(p_verde->primero);
    free(p_verde);
    liberar_azules(azul);
}

void hacer_azules(Azul_t* azul, int contador,bool fallo, char* texto, int posicion){
    if(contador == 3){
        return;
    }

    azul->letra = &texto[posicion];
    posicion++;

    azul->siguiente = malloc(sizeof(Azul_t));
    if(!azul->siguiente){
        fallo = true;
        return;
    }
    return hacer_azules(azul->siguiente, contador + 1, fallo,texto,posicion);
}

int main(){
    char* texto = malloc(sizeof(char) * CANTIDAD_LETRAS);
    if(!texto){
        return -1;
    }
    texto[0] = 'C';
    texto[1] = 'O';
    texto[2] = 'S';
    texto[3] = 'A';

    Verde_t* p_verde = malloc(sizeof(Verde_t));
    if(!p_verde){
        free(texto);
        return -1;
    }
    p_verde->numero = NUMERO;
    p_verde->primero = malloc(sizeof(Azul_t));
    if(!p_verde->primero){
        free(texto);
        free(p_verde);
        return -1;
    }
    
    bool fallo = false;
    hacer_azules(p_verde->primero,0,fallo,texto,0);
    if(fallo){
        liberar(texto,p_verde,p_verde->primero);
        return -1;
    }

    Rosa_t* p_rosa = malloc(sizeof(Rosa_t));
    if(!p_rosa){
        liberar(texto,p_verde,p_verde->primero);
        return -1;
    }
    p_rosa->numero = NUMERO;

    p_rosa->letras = malloc(sizeof(char*) * CANTIDAD_LETRAS);
    if(!p_rosa->letras){
        liberar(texto,p_verde,p_verde->primero);
        free(p_rosa);
        return -1;
    }
    for(int i = 0; i < 4; i++){
        p_rosa->letras[i] = &texto[i];
    }

    liberar(texto,p_verde,p_verde->primero);
    return 0;
}