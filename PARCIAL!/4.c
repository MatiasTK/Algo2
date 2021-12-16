// EJ -> https://i.imgur.com/QEYG45K.png

struct Jugador{
    char* nombre;
    int puntos;
    int fotos_tomadas;
    int numero_foto;
    Pokemon* fotografiado;
    Multiplicadores* multiplicador;
};

struct Multiplicadores{
    bool hay_multiplicador;
    int multiplicacion;
    int cantidad_de_usos_totales;
    int usos_gastados;
}

struct pokemon{
    char especie[MAX_NOMBRE_POKEMON];
    int puntos;
    bool shiny;
};


// Esta operacion es O(1) ya que solo asigna variables y la complejidad de insertar en una lista doblemente enlazada es O(1) 
void fotografiar_pokemon(lista_t* lista, char* especie, int puntos,bool shiny,char* nombre_jugador){
    Jugador* j;
    j->fotos_tomadas++;
    j->nombre = nombre_jugador;
    j->poke->especie = especie;
    j->poke->puntos = puntos;
    j->poke->shiny = shiny;
    lista_insertar(lista,poke);
}

bool mostrar_pokemones(void* e1, void* e2){
    void* e1 = (Jugador*)j;
    printf("%s",j->elemento->fotografiado->especie);
    return true;
}

// Esta operacion es O(n) ya que tiene que hacer n iteraciones para llegar al final de la lista y recorrer todos los pokemones
void mostrar_listado_pokemones(lista_t* lista){
    lista_con_cada_elemento(lista,mostrar_pokemones);
}

bool contar_puntos(void* e1, void* e2){
    e1 = (Jugador*)j;
    puntos = *(int*)j->puntos;
    e2 = *(int*)puntos_totales;
    
    puntos totales += puntos;
    return true;
}

bool aniadir_a_lista(void* e1, void* e2){
    e1 = (Jugador*)j;
    e2 = (lista_t*)fotografiados;
    
    lista_insertar_en_posicion(fotografiados,j->fotografiado.especie,j->numero_foto);
}

void ordenar_por_numero_foto(nodo_t* nodo){
    if(nodo){
        return;
    }
    
    if(nodo->elemento.numero_foto > nodo->siguiente.elemento.numero_foto){
        char* aux = nodo->elemento.fotografiado.especie;
        nodo->elemento.fotografiado.especie = nodo->siguiente.elemento.fotografiado.especie;
        nodo->siguiente.fotografiado.especie = aux;
    }
    ordenar_por_numero_foto(nodo->siguiente);
}

void ordenar_por_puntaje(nodo_t* nodo){
    if(nodo){
        return;
    }
    if(nodo->elemento.fotografiado.puntos > nodo->siguiente.elemento.fotografiado.puntos){
        char* aux = nodo->elemento.fotografiado.especie;
        nodo->elemento.fotografiado.especie = nodo->siguiente.elemento.fotografiado.especie;
        nodo->siguiente.elemento.fotografiado.especie = aux;
    }
}

void mostrar_l1(nodo_t* n1){
    printf("%s",n1->elemento.fotografiado.especie);
    mostrar_l1(n1->siguiente);
}

void mostrar_l2(nodo_t* n2){
    printf("%s",n2->elemento.fotografiado.especie);
    mostrar_l2(n2->siguiente);
}

void mostrar(int puntos_totales, lista_t* l1, lista_t* l2){
    printf("Puntos totales: %i",puntos_totales);
    mostrar_l1(l1->nodo_inicio);
    mostrar_l2(l2->nodo_inicio);
}

void recorrer(lista_t* lista){
    int puntos_totales = 0;
    size_t recorrido = lista_con_cada_elemento(lista,contar_puntos,&puntos_totales);
    
    lista_t* fotografiados = lista_crear();
    recorrido = lista_con_cada_elemento(lista,aniadir_a_lista,fotografiados);
    ordenar_por_numero_foto(lista->nodo_inicio);
    
    lista_t* fotografiados_por_puntaje = lista_crear();
    recorrido = lista_con_cada_elemento(lista,aniadir_a_lista,fotografiados_por_puntaje);
    ordenar_por_puntaje(lista->nodo_inicio);
    
    mostrar(puntos_totales,fotografiados,fotografiados_por_puntaje);
}

bool multiplicar(void* e1, void* e2){
    e1 = (Jugador*)j;
    if(j->fotografiado->shiny){
        j->fotografiado->puntos *= 100;
    }
    if(j->multiplicador->hay_multiplicador){
        if(j->multiplicador->usos_gastados < j->multiplicador->cantidad_usos_totales){
            j->fotografiado->puntos *= j->multiplicador->multiplicacion;
        }
    }
}

void multiplicar_puntos_shiny_y_aplicar_multiplicador(lista_t* lista){
    size_t recorrido = lista_con_cada_elemento(lista,multiplicar,NULL);
}
