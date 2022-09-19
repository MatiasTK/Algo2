// EJ -> https://i.imgur.com/bYw0G24.png

int burbujeo_recursivo(int* vector, int tope){
    int contador = 0;
    
    if(tope < 2){
        return contador;
    }
 
    if(vector[0] > vector[1]){
        int aux;
        aux = vector[0];
        vector[0] = vector[1];
        vector[1] = aux;
        contador++;
    }
    
    contador += burbujeo_recursivo(vector + 1, tope - 1);
    return contador;
}

void burbujeo(int* vector, size_t tope){
    int contador = burbujeo_recursivo(vector,tope);
    
    if(contador >= 1){
        burbujeo(vector,tope);
    }
}