# <center>Arbol Rojo y Negro</center>
----
## ¿Que son?
Es un **ABB auto-balanceado**. Complejidad $O(log(n))$.
Los nodos son **Rojos o negros**. Es eficiente dependiendo del uso que le des.
## Definicion
* La **raiz** del arbol es **negro**
* Las **hojas NULL**(Arboles sin hijos) son **negro**
* Los **nodos rojos** deben tener almenos **dos hijos negros**
* **NO** hay nodos **rojos consecutivos**
* Cualquier camino desde un nodo hacia abajo siempre tiene la **misma cantidad de nodos negros** de cualquiera de los dos lados

Dato no oficial: siempre que insertas un dato nuevo inicialmente antes de analizar todo va a ser rojo

> Las mas importantes es la segunda,cuarta y ultima

## Pagina interactiva
[Arbol Rojo-Negro](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html "Clickeame te va a gustar")




