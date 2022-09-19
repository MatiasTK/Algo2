// EJ -> https://i.imgur.com/qefIv1h.png

typedef struct _nodo_b{
    int* claves;
    size_t cantidad_claves;
    struct _nodo_b** hijos;
} _nodo_b;

void recorrer(_nodo_b* nodo, int* claves, size_t* cantidad_claves){
    if(nodo == NULL){
        return;
    }
    for(size_t i = 0; i < nodo->cantidad_claves; i++){
        claves[*cantidad_claves] = nodo->claves[i];
        *cantidad_claves = *cantidad_claves + 1;
    }
    for(size_t i = 0; i < nodo->cantidad_claves + 1; i++){
        recorrer(nodo->hijos[i], claves, cantidad_claves);
    }
}

void recorrer(nodob* nodo){
    if(!nodo || nodo->cantidad_claves == 0){
        return;
    }

    for(int i = 0; i < nodo->cantidad_claves; i++){
        recorrer(nodo->hijos[i]);
        mostrar(nodo->clave[i]);
    }
    recorrer(nodo->hijos[nodo->cantidad_claves - 1]);
}