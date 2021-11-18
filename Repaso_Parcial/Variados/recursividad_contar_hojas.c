// EJ -> https://i.imgur.com/O7BTYYl.png

typedef struct nodo{
    struct nodo* izq;
    struct nodo* der;
} nodo_t;

int contar_hojas(nodo_t* raiz){
    if(!raiz){
        return 0;
    }
    if(!raiz->izq && !raiz->der){
        return 1;
    }
    return contar_hojas(raiz->izq) + contar_hojas(raiz->der);
}

int contar_nodos_con_dos_hojas(nodo_t* raiz){
    if(!raiz){
        return 0;
    }
    if(raiz->izq && raiz->der){
        return 1;
    }
    return contar_nodos_con_dos_hojas(raiz->izq) + contar_nodos_con_dos_hojas(raiz->der);
}

