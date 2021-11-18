extern void sift_up(int* vector, int tope);
extern void sift_down(int* vector, int tope, int pos_actual);

void swap(int* vector, int inicial, int final){
    int aux = vector[inicial];
    vector[inicial] = vector[final];
    vector[final] = aux;
}

void reverse_array(int* array, int inicio, int final){
    int i = inicio;
    int j = final;
    while(i < j){
        swap(array, i, j);
        i++;
        j--;
    }
}

void heap_sort_recursivo(int* numeros,int tope){
    if(tope <= 1){
        return;
    }

    swap(numeros, 0, tope - 1);
    tope--;
    sift_down(numeros, tope, 0);
    heap_sort(numeros, tope, ascendente);
}

void heap_sort(int* numeros, int tope, bool ascendente){
    heap_sort_recursivo(numeros, tope);
    if(!ascendente){
        reverse_array(numeros, 0, tope - 1);
    }
}

