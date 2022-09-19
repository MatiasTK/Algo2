void sift_up(int* vector, int pos_actual){
    if(pos_actual == 0){
        return;
    }
    int padre = (pos_actual-1)/2;
    if(vector[pos_actual] > vector[padre]){
        int aux = vector[padre];
        vector[padre] = vector[pos_actual];
        vector[pos_actual] = aux;
        sift_up(vector, padre);
    }
}