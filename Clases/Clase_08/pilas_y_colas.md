# <center>Pilas y colas</center>
-------
## Pilas
LIFO -> Last in, First out -> Ultimo que entra primero que sale
Es una estructura de datos
Agrupa elementos
### Operaciones
* Crearla
* Apilar(Push) -> Apila algo en el stack
* Tope(Top)  
* Destruir(destroy)
* Desapilar(pop) -> Saca algo del tope
* Chequear si esta vacia(isEmpty)

### Formato
#### Vectores estaticos
```c
    typedef struct pila{
        int tope;
        void* elementos[CAPACIDAD_PILA];
    } pila_t;
```
#### Vectores dinamicos
```c
    void* realloc(
        void* ptr,
        size_t tamanio_nuevo
    );
```
### Nodos
Tienen un dato o puntero a dato y puede indicar cual es el siguiente o anterior puntero o nodo.
No es necesario tener un malloc y realloc ya que apuntan automaticamente al siguiente nodo.

#### Pila de nodos
Estan formadas por 2 cuadraditos
El primero apunta al nodo anterior(NULL SI NO HAY) y el segundo al dato o al puntero al dato

|NULL|55| 
|---|---|

##### Desapilar nodo
Tenes que tener cuidado de no perder la referencia, hay que usar un nodo aux que apunte al nodo a eliminar y mover el tope.

## Cola
FIFO -> First in, First out -> El primero que entra es el primero que sale

### Operaciones
* Crearla -> Moves el fin a la posicion del nuevo elemento
* Destruir -> conviene usar desencolar circular
* Encolar
* Desencolar
* Primero -> Lo que tenes en el primer elemento
* Vacio

#### Vectores estaticos
##### Desencolar circular -> O(1)
Tenes el tope el principio y el fin
El tope va a ser 0, el principio el primer elemento del vector, y el final el ultimo que entro.
Esto siempre y cuando el fin no sea mas grande o igual al tope.
El tope siempre va a estar antes del principio.

#### Vectores Dinamicos con nodos
##### Encolar -> O(1)
Para crear voy a tener 2 nodos principio y final, en su creacion va a apuntar a ``NULL``.
Para agregar un nodo principio y final van a apuntar a ese nodo y el siguiente de ese nodo va a ser NULL.
Si agregamos otro elemento el elemento anterior ya no va apuntar a null sino a este siguiente y el final tambien va a aumentar a este nuevo, el siguiente de este nuevo elemento si va a ser NULL hasta que se agregue uno nuevo.
##### Desencolar -> O(1)
Si quiero sacar un elemento va a tener que ser el primero porque es una cola, entonces me creo una variable auxiliar que guarde un puntero hacia el elemento a liberar, aumento el principio hacia el siguiente elemento y libero el auxiliar.

