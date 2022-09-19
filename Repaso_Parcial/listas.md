# <center>Listas</center>
---------
Es un TDA de elementos 

* Creacion
* Insertar(insertAt)
* Vacia(isEmpty)
* Destruir
* Eliminar(deleteAt)
* Ver elemento(find)

## Listas simplemente enlazadas
Son dos cuadraditos, el primero es el elemento y el siguiente es la referencia al siguiente elemento si no hay elemento siguiente es ``NULL``.

Si quiero insertar un elemento en una posicion X entre el medio entonces hago que el elemento que quiero insertar apunte a X+1 y el elemento que esta en X-1 va a apuntar a X.

Para eliminar un elemento X creo un auxiliar que apunte a X, hago que el elemento que esta en X-1 apunte a X+1 y elimino X.

## Listas doblemente enlazadas
Ahora tengo 3 cuadraditos, el primero apunta hacia el nodo anterior, el del medio al dato y el siguiente apunta al nodo siguiente, si no hay anterior o siguiente es ``NULL``.

Si quiero insertar un elemento en una posicion X entre el medio entonces hago que el elemento que quiero insertar apunte a X+1 y X-1 y el emenento que esta en X-1 va a apuntar a X.

Si quiero eliminar un elemento X creo un nodo auxilar apuntando al X, el nodo en X-1 va a apuntar a X+1 y el nodo en X+1 va a apuntar a X-1, finalmente libero el auxiliar.

## Lista circular
Dos cuadraditos el primero es un dato y el segundo apunta hacia el siguiente nodo, pero si es el ultimo nodo este va a apuntar al primero.
Para insertar un elemento en una posicion X entre el medio hago que el elemento que quiero insertar apunte al primer elemento y el elemento de X-1 va a apuntar a X

## Lista circular doblemente enlazadas
Tres cuadraditos -> si es el primer nodo el primero va apuntar al ultimo el del medio es un dato y el tercero va a apuntar al siguiente
Si es el ultimo nodo el primero va apuntar al anterior el del medio al dato y el ultimo al primero