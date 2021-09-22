#include <stdio.h>

typedef struct entrenador {
    char* nombre;
    int cant_vencidos;
} entrenador_t;

void actualizar_victorias(void* entrenador, void* cant_extra){
    if(!entrenador || !cant_extra){
        return;
    }
    int sumar = *(int*)cant_extra;
    if(sumar <= 0){
        return;
    }
    entrenador_t* entrenador_ptr = entrenador;
    entrenador_ptr->cant_vencidos += sumar;
    return;
}

int main(){
    int cantidad_extra = 2;
    void* cant_extra;
    cant_extra = &cantidad_extra;

    entrenador_t entrenador;
    entrenador.cant_vencidos = 20;
    void* entrenador_ptr = &entrenador;

    actualizar_victorias(entrenador_ptr, cant_extra);

    printf("============================================================\n");
    printf("El valor de cant extra es: %i, y el valor final es: %i\n",cantidad_extra,entrenador.cant_vencidos);

    return 0;
}