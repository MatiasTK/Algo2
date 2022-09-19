void sort_generico(void *vector, int cant_elementos, int tamanio_un_elemento, int (*comparador)(const void *, const void*)){
    if(!comparador){
        return;
    }
    int i, j;
    void *aux;
        for(i = 0; i < cant_elementos; i++){
        for(j = i + 1; j < cant_elementos; j++){
            if(comparador(((char *)vector + i * tamanio_un_elemento), ((char *)vector + j * tamanio_un_elemento)) > 0){
                aux = malloc(tamanio_un_elemento);
                memcpy(aux, ((char *)vector + i * tamanio_un_elemento), tamanio_un_elemento);
                memcpy(((char *)vector + i * tamanio_un_elemento), ((char *)vector + j * tamanio_un_elemento), tamanio_un_elemento);
                memcpy(((char *)vector + j * tamanio_un_elemento), aux, tamanio_un_elemento);
                free(aux);
            }
        }
    }
}