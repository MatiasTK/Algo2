#include <stdio.h>

int vtrlen(int* vector){
    if(!vector){
        return 0;
    }
    return 1 + (vtrlen(vector+1));
}

void sift_up(int* vector, int pos_actual){
    if(!vector){
        return;
    }
    int size = vtrlen(vector);
    vector[size-2] = pos_actual;
    vector[size-1] = 0;
    return;
}