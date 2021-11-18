//EJ -> https://i.imgur.com/0K92X9I.png

void invertir_y_mostrar(pila_t pila){
    if(vacia(pila)){
        return;
    }
    int valor = desapilar(pila);
    invertir_y_mostrar(pila);
    printf("%d\n", valor);
}