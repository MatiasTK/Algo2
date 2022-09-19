//EJ -> https://i.imgur.com/wr5k4K5.png

typedef struct nodo{
    int factor_equlibrio;
    struct nodo* izq;
    struct nodo* der;
}nodo_t;

int max(int i, int j){
    return i > j ? i : j; // Devuelve el mayor de los dos.
}

int calcular_altura(nodo_t* raiz){
    if(!raiz){
        return 0;
    }
    int altura_izq = calcular_altura(raiz->izq);
    int altura_der = calcular_altura(raiz->der);
    return max(altura_izq, altura_der) + 1;
}

int completar_factor_de_equilibrio(nodo_t* raiz){
    if(!raiz){
        return 0;
    }
    raiz->factor_equlibrio = calcular_altura(raiz->izq) - calcular_altura(raiz->der) ; // Es como AVL. Izquierda - derecha.
    completar_factor_de_equilibrio(raiz->izq);
    completar_factor_de_equilibrio(raiz->der);
    return 0;
}