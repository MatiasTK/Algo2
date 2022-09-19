typedef struct{
    int campo1;
    char**** campo2;
}Azul;

void liberar_todo(){
    for(int i = 0; i < 5; i++){
            free(vectores[i]);
        }
        free(v1);
        free(vector1);
}

int main(){
    Azul*  v1 = calloc(1, sizeof(Azul));

    char*** vector1 = calloc(5, sizeof(char**));

    char* caracter_suelto_heap = malloc(sizeof(char));
    char caracter_suelto_stack = 0;

    char** vectores[5];
    bool hubo_error = false;
    for(int i = 0; i < 5; i++){
        vectores[i] = calloc(5, sizeof(char**));
        if(!vectores[i]){
            hubo_error = true;
        }
    }
    if(hubo_error){
        liberar_todo();
    }

    v1->campo2 = &vector1;

    for(int i = 0; i < 5; i++){
        vector1[i] = vectores[i];
        for(int j = 0; j < i+1; j++){
            if(j%2 == 0){
                vectores[i][j] = &caracter_suelto_stack;
            }else{
                vectores[i][j] = caracter_suelto_heap;
            }
        }
    }

    liberar_todo();

    return 0;
}