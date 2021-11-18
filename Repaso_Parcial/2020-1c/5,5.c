void invertir_pila(pila_t* pila, pila_t* aux){
    if(pila_cantidad(pila) == 0){
        return;
    }

    pila_apilar(aux, pila_desapilar(pila));
    invertir_pila(pila,aux);
}

void imprimir_recursivamente(pila_t* pila, pila_t* aux){
    if(pila_cantidad(pila) == 0){
        return;
    }

    int tope = pila_desapilar(pila);
    printf("%i",tope);

    invertir_pila(pila,aux);

    imprimir_recursivamente(aux,pila);
}

//! Funcion a implementar
void uno_y_uno(pila_t* pila){
    if(!pila){
        return;
    }

    pila_t* aux = pila_crear();

    imprimir_recursivamente(pila,aux);

    pila_destruir(aux);
}