#include "abb.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


struct _abb_t{
    void* elemento;
    struct _abb_t* izquierdo;
    struct _abb_t* derecho;
};

abb_t* abb_crear(){
    return NULL;
}

abb_t* abb_insertar(abb_t* abb,void* elemento,int (comparador)(void*,void*)){
    if(!comparador){
        return NULL;
    }
    if(!abb){
        abb_t* nuevo = calloc(1,sizeof(abb_t));
        if(!nuevo){
            return NULL;
        }
        nuevo->elemento = elemento;
        return nuevo;
    }
    int comparacion = comparador(elemento,abb->elemento);
    if(comparacion <= 0){
        abb->izquierdo = abb_insertar(abb->izquierdo,elemento,comparador);
    }else{
        abb->derecho = abb_insertar(abb->derecho,elemento,comparador);
    }
    return abb;
}

abb_t abb_buscar(abb_t* abb,void* elemento,int (comparador)(void*,void*)){
    bool encontrado = false;
    while(abb && !encontrado){
        int comparacion = comparador(elemento,abb->elemento);
        if(comparacion == 0){
            encontrado = true;
        }else if(comparacion < 0){
            abb = abb->izquierdo;
        }else{
            abb = abb->derecho;
        }
    }
    if(encontrado){
        return abb;
    }
    return NULL;
}

abb_t* abb_quitar(abb_t* abb,void* elemento,int (comparador)(void*,void*),void (*destruir_elemento)(void*)){
    if(!abb){
        return NULL;
    }
    int comparacion = comparador(elemento,abb->elemento);
    if(comparacion == 0){
        if(abb->derecho && abb->izquierdo){ //Si tengo 2 hijos
            abb_t* predecesor;
            extraer_nodo_mas_derecho(abb->izquierdo,&predecesor);

            predecesor->derecho = abb->derecho;
            predecesor->izquierdo = abb->izquierdo;

            if(destruir_elemento){
                destruir_elemento(abb->elemento);
            }
            free(abb);
        }else if(abb->derecho || abb->izquierdo){ // Si tengo 1 o 0 hijos
            abb_t* hijo = abb->derecho?abb->derecho:abb->izquierdo; //Operador ternario si tengo derecho elijo el derecho sino izquierdo
            if(destruir_elemento){
                destruir_elemento(abb->elemento);
            }
            free(abb);
            return hijo;
        }else{ //Si no tengo hijos
            if(destruir_elemento){
                destruir_elemento(abb->elemento);
            }   
            free(abb);
            return NULL;
        }
    }else if(comparacion < 0){
        abb->izquierdo = abb_quitar(abb->izquierdo,elemento,comparador,destruir_elemento);
    }else{
        abb->derecho = abb_quitar(abb->derecho,elemento,comparador,destruir_elemento);
    }

    return abb;
}

size_t abb_con_cada_elemento_inorden(abb_t* abb, recorrido_abb_t recorrido, bool(*funcion)(void*,void*),void* aux){
    if(!abb){
        return 0;
    }
    size_t contador = 1;

    contador += abb_con_cada_elemento_inorden(abb->izquierdo,funcion,aux);
    
    bool retorno = funcion(abb->elemento,aux);

    contador += abb_con_cada_elemento_inorden(abb->derecho,funcion,aux);

    return contador;
}

size_t* abb_con_cada_elemento(abb_t* abb, recorrido_abb_t recorrido, bool(*funcion)(void*,void*),void* aux){
    if(recorrido = INORDEN){
        return abb_con_cada_elemento_inorden(abb,funcion,aux);
    }
    return 0;
}

void abb_destruir(abb_t* abb){
    /* if(!abb){
        return NULL;
    }
    abb_destruir(abb->izquierdo);
    abb_destruir(abb->derecho);
    free(abb); */
    abb_destruir_todo(abb,NULL);
}

void abb_destruir_todo(abb_t* abb,void (*destruir_elemento)(void)){
    if(abb){
        abb_destruir_todo(abb->izquierdo,destruir_elemento);
        abb_destruir_todo(abb->derecho,destruir_elemento);
        if(destruir_elemento){
            destruir_elemento(abb->elemento);
        }
        free(abb);
    }
    return NULL;
}