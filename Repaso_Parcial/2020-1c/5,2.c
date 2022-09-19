typedef struct nodo{
    struct nodo* izq;
    struct nodo* der;
} nodo_t;

int contar_hojas(nodo_t* nodo){
    if(!nodo){
        return 0;
    }
    if(!nodo->izq && !nodo->der){
        return 1;
    }
    return contar_hojas(nodo->izq) + contar_hojas(nodo->der);
}

int contar_nodos_con_dos_hijos(nodo_t* nodo){
    if(!nodo){
        return 0;
    }
    if(nodo->izq && nodo->der){
        return 1 + contar_nodos_con_dos_hijos(nodo->izq) + contar_nodos_con_dos_hijos(nodo->der);
    }
}