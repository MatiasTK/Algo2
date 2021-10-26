# <center>Arbol B </center>
---
## Caracteristicas
* Claves ordenadas
* Cantidad minima de claves es K/2 (Exceptuando raiz) siendo K la cantidad maxima de claves. Se redondea para abajo
* Un nodo con k claves tiene como maximo m = k + 1 desendientes(Punteros)
* La cantidad minima de desendientes es m/2 (Exceptuando hojas y raiz). Se redondea para arriba
* **Todas las hojas tienen que estar al mismo nivel**

**EJ ->** Si tengo k = 5 la cantidad minima va a ser 2, la cantidad max de descendientes es 6, La cantidad minima de descendientes es 3.
## Insercion
La insercion es de manera ordenada, por lo tanto tengo que mover todos los elementos si quiero insertar un elemento menor, los punteros no se cambian de lugar!
La idea seria no usar un nodo osea hasta que el nodo actual no este completamente lleno no creas uno nuevo.
Si el nodo esta lleno voy a agarrar el nodo y lo parto a la mitad dejando el numero del medio como nodo raiz
el punteor anterior a ese nodo raiz va a ser un nuevo nodo con los elementos que estaban antes del 12
El puntero siguiente a ese nodo raiz va a ser un nuevo nodo con los elementos que estaban despues del 12
La prioridad al siempre al **insetar en nodos hoja**
![Insercion](https://i.imgur.com/lD654W0.png)
![Insercion](https://i.imgur.com/SECp3Dp.png)
## Eliminacion
**Underflow** -> Los nodos no pueden tener 1 solo elemento, entonces tengo que **redistribuir**.
Osea a ese elemento que me quedo solito lo acompaño con el siguiente elemento del nodo raiz, y en el nodo raiz pongo el primer elemento del nodo siguiente.
Otra manera es bajar el siguiente elemento del nodo raiz y en vez de poner el primer elemento del nodo siguiente pongo el ultimo elemento del nodo anterior 
HAY QUE ELEGIR UNA DE LAS DOS PARA TODO EL ALGORITMO
![Eliminacion](https://i.imgur.com/YmtUj0s.png)
En caso de no poder usar redistribucion ya que si muevo dejo solo al siguiente entonces tengo que usar **concatenacion**.
Pongo el numero que me quedo solito y el eleemnto despues de este en el nodo siguiente
![Eliminacion](https://i.imgur.com/ry57nre.png)
Si quiero eliminar un elemento de una raiz primero lo tengo que llevar a un nodo hoja, para esto
si intento llevar al nodo de la izquierda y para que no me quede el nodo de la raiz sin elementos lo que voy a hacer es subir el primer elemento del nodo de la derecha

## Machete

![Machete](https://i.imgur.com/Dg1bMQy.png)
