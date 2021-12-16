# Aventura_Pokemon_TP2

*Trabajo práctico para la materia Algoritmos y Programación 2 [75.41 - 95.15] - FIUBA, Cátedra Méndez - 2c2020*


## Compilación y ejecución:

### Compilación
	gcc juego.c definiciones.c batallas.c TDAHeap/heap.c TDALista/lista.c -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -o juego

### Debug de memoria con valgrind
    valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./juego

### Makefile
En la carpeta del TP se encuentra un makefile que facilita la compilación y ejecución del mismo y sus pruebas.
Las instrucciones para la utilización del makefile son las siguientes:

• Para compilar y ejecutar el TP: ```make / make test```

• Para solo compilar el TP: ```make c```

• Para correr valgrind y ver memory leaks: ```make memory```

• Para correr gdb y debuggear: ```make debug```

• Para borrar el archivo compilado juego: ```clean```

## Elección de TDAs:

Utilicé una lista para los pokemones de batalla del personaje, para poder acceder de forma más fácil a los pokemones. Es decir, es necesario recorrer las listas de pokemones varias veces durante el transcurso del juego. De esta forma, se recorre de manera más sencilla con el iterador de la lista, en vez de tener que crear pilas/colas auxiliares en el caso de usar estas, ya que en ese caso habría que desapilar/desencolar constantemente para acceder a los pokemones.

Lo mismo para los pokemones obtenidos (caja), que pueden ir desordenados, por lo que una lista resulta óptima.

También utilicé una lista para los pokemones de cada entrenador, por los mismos motivos mencionados anteriormente.

Para los entrenadores utilicé una pila, ya que se pelea contra ellos en el orden inverso al leído del archivo.

Para los gimnasios se utilizó un heap minimal ordenado por dificultad, como indica la consigna.

## Modificaciones a TDAs:
- Agregué un destructor a la lista, para facilitar el manejo de memoria. El destructor fue añadido a todas las funciones que borran elementos de la lista, 
    incluyendo a las de pila y cola, y a la función de lista_destruir.

## Consideraciones:

- Agregué este tipo de dato para el puntero a función de batalla:
    
    ```typedef int (*funcion_batalla)(void*, void*); ```

- Si la función de batalla para el gimnasio en el archivo no está entre 1 y 5, se utiliza una aleatoria.

- En la función leer_linea: 
    - Salgo y borro todo si el sscanf no puede leer ```"letra;texto\n"```. 
    - En otro caso, si lee un pokemon mal, por ejemplo, 
```"P;aadasdadasd;"``` ignora ese pokemon y sigue con el resto, si los hay, pero intenta preservar el archivo lo más posible en cuanto a los pokemones.
