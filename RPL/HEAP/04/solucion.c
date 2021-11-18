extern void sift_down(int* vector, int tope, int pos_actual);

int heap_extraer_raiz(int* vector, int* tope){
    if(*tope == 0){
        return vector[0];
    }
    int raiz = vector[0];

    (*tope)--;
    vector[0] = vector[*tope];

    if(*tope > 0){
        sift_down(vector, *tope, 0);
    }

    return raiz;
}