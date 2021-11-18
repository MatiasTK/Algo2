//!1

typedef struct{
    void* punteros[3];
} Azul;

int main(){

    Azul* cosa;

    char* texto = "ABCDE" //! ESTO ESTA MAL; NO ESTA EN EL HEAP

    char* texto = malloc(5*sizeof(char));
    if(!texto){
        return -1;
    }

    azul* azules[7];
    azules[5] = NULL;
    azules[6] = NULL; //? PARA CASOS ULTIMOS ESPECIALES
    bool hubo_error = false;

    for(int i = 0; i < 5; i++){
        azules[i] = calloc(sizeof(azul)); //! NO ESTOY CREANDO UN VECTOR ESTOY CREANDO 5 AZULES DIFERENTES
        if(azules[i]){
            hubo_error = true;
        }
    }

    if(hubo_error){
        for(int i = 0; i < 5; i++){
            free(azules[i]);
        }
        free(texto);
        return -1;
    }

    texto[0] = 'A';
    texto[1] = 'B';
    texto[2] = 'C';
    texto[3] = 'D';
    texto[4] = 'E';

    strcpy(texto, "ABCDE"); //! ESTO TAMBIEN ESTA MAL! PORQUE PONE EL \0

    for(int i = 0; i < 5 ; i++){
        azules[i].punteros[2] = azules[i+1];
        azules[i].punteros[0] = texto+4-i;
        azules[i].punteros[i] = azules[i+2];
    }

    for(int i = 0; i < 5 ; i++){
        free(azules[i]);
    }
    free(texto);


    return 0;
}