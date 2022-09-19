// EJ -> https://i.imgur.com/WdEvwzY.png

void liberar(char* c1,char* c2,char* c3,char* c4,char*** v){
    free(c1);
    free(c2);
    free(c3);
    free(c4);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            free(v[i][j]);
        }
        free(v[i]);
    }
    free(v);
}

void llenar_vector(char*** v, int numero_vector,char* c){
    for(int = 0; i < 4; i++){
        v[numero_vector][i] = c[i];
    }
}

int main(){
    
    char* c1 = malloc(sizeof(char)*4);
    if(!c1){
        return -1;
    }
    char* c2 = malloc(sizeof(char)*4);
    if(!c2){
        free(c1);
        return -1;
    }
    char* c3 = malloc(sizeof(char)*4);
    if(!c3){
        free(c1);
        free(c2);
        return -1;
    }
    char* c4 = malloc(sizeof(char)*4);
    if(!c4){
        free(c1);
        free(c2);
        free(c3);
        return -1;
    }
    
    c1[0] = '0';
    c1[1] = '4';
    c1[2] = '8';
    c1[3] = 'C';
    
    c2[0] = '1';
    c2[1] = '5';
    c2[2] = '9';
    c2[3] = '2';
    
    c3[0] = '2';
    c3[1] = '6';
    c3[2] = 'A';
    c3[3] = 'E';
    
    c4[0] = '3';
    c4[1] = '7';
    c4[2] = 'B';
    c4[3] = 'F';
    
    char*** V = calloc(4,sizeof(char**));
    if(!v){
        free(c1);
        free(c2);
        free(c3);
        free(c4);
        return -1;
    }
    
    bool fallo = false;
    
    for(int i = 0; i < 4; i++){
        V[i] = calloc(4,sizeof(char*));
        if(v[i]){
            fallo = true;
        }
    }
    
    if(fallo){
        liberar(c1,c2,c3,c4,v);
        return -1;
    }
    
    llenar_vector(v,0,c1);
    llenar_vector(v,1,c2);
    llenar_vector(v,2,c3);
    llenar_vector(v,3,c4);
    
    liberar(c1,c2,c3,c4,v);
    
    return 0;
}