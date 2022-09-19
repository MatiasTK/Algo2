void sift_down(int* vector, int tope, int pos_actual){
    int pos_izquierda = 2*pos_actual + 1;
    int pos_derecha = 2*pos_actual + 2;
    int pos_a_intercambiar;

    if(pos_izquierda > tope){
        return;
    }

    if(pos_derecha > tope){
        pos_derecha = pos_izquierda;
    }

    int elemento = vector[pos_actual];
    int izquierdo = vector[pos_izquierda];
    int derecho = vector[pos_derecha];

    if(derecho > izquierdo){
        pos_a_intercambiar = pos_derecha;
    }else{
        pos_a_intercambiar = pos_izquierda;
    }

    if(vector[pos_a_intercambiar] > elemento){
        int aux = vector[pos_actual];
        vector[pos_actual] = vector[pos_a_intercambiar];
        vector[pos_a_intercambiar] = aux;
        sift_down(vector, tope, pos_a_intercambiar);
    }
}