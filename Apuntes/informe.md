    
![](https://i.imgur.com/P0aqOMI.jpg)

# **TDA n2 — Arboles Binarios de busqueda** 

## [7541/9515] Algoritmos y Programación II


### Segundo cuatrimestre de 2021

|  Alumno: | Vallejos, Matias |
| ----------- | ----------- |
| Número de padrón: | 107924 |
| Email: | matiavallejo@gmail.com |
| Email Institucional: | mvallejos@fi.uba.ar|


#### 1. Introducción

El objetivo de este TDA es implementar una solucion simple al problema de la representacion de jerarquia en estructuras de datos, en este caso vamos a utilizar **Arboles Binarios de Busqueda (ABB)** y asi lograr una estructura de datos util para su utilización y a su vez lograr optimizar la busqueda lineal de este.

#### 2. Teoría

Respuestas a las preguntas teóricas

1. ¿Qué es un arbol, arbol binario y arbol binario de busqueda?
* Un **arbol** es una coleccion de nodos que a su vez estan conectados a otros multiples nodos. Este consiste de un nodo principal normalmente llamado **raiz**
y la cantidad necesaria de **Subarboles** los cuales son nodos que se formar a partir de la raiz. Su estructura se basa en la recursividad ya que esta cuenta con una condicion de corte y llamadas a la funcion. Hay muchos tipos de arboles
como por ejemplo: Arboles binarios, AVL, arbol rojo-negro,etc. Para la implementacion de este trabajo utilizaremos el tipo de arbol binario de busqueda.
* Un **arbol binario** es un tipo de arbol que busca relacionarse con el metodo de busqueda binaria, esto lo logra con la caracteristica de que el nodo raiz esta solamente conectado a dos subarboles permitiendonos asi definir la noción de izquierda y derecha. Este posee las siguientes operaciones: Creacion, destruccion, insertar, borrar, buscar, chequear si esta vacio, recorrer.
* Un **arbol binario de busqueda** es un tipo de arbol binario el cual posee un orden en especifico, para lograr este orden especifico tenemos que comparar los elementos de modo que cada arbol posea un valor o clave unica. Gracias a este orden es que logramos optimizar la busqueda lineal. Las caracteristicas de este arbol que utilizaremos en este proyecto son: Las claves mayores se insertaran en los subarboles de la derecha, las menores en los de la izquierda. Estos subarboles tambien son arboles de busqueda binaria. 
* Es importante diferenciar cada concepto ya que no todos los arboles son binarios ni todos los arboles binarios tienen un ordenamiento especifico.

#### 3. Detalles de implementación


Detalles específicos de la implementación, como compilar, como ejecutar


1. `nodo_insertar` Recibe un arbol, un elemento y un nodo, si el nodo recibido no existe lo crea.Inserta un nuevo nodo en el arbol binario utilizando el comparador es gracias a este que logra compararlo, si en la comparacion el elemento a insertar es menor se inserta a la izquierda, sino a la derecha. En caso de ser iguales lo inserta a la izquierda. Devuelve el nodo insertado.
2. `buscar_nodo_mayor` Busca el nodo de elemento mayor de un arbol mediante recursividad y lo devuelve. Es una funcion auxiliar de `buscar_nodo_mayor_subarbol_izquierdo`
3. `buscar_nodo_mayor_subarbol_izquierdo` Busca el nodo mayor del subarbol izquierdo de la raiz.
4. `nodo_quitar` Recibe un nodo y lo quita del arbol. Si el nodo es hoja(No tiene hijos) hace que el padre apunte a NULL (Ver diagrama 3). Si el nodo tiene un solo hijo hace que el padre apunte al hijo del nodo a remover y finalmente remueve el nodo correspondiente(Ver diagrama 4). Si el nodo tiene dos hijos busca el **Sucesor inmediato**(el menor elemento del subarbol derecho) lo reemplaza por el nodo a remover y si el sucesor inmediato tuviera un hijo este lo linkea con el antiguo padre del sucesor inmediato(Ver diagrama 5). Devuelve el nodo que removio.
5. `buscar_nodo` Recorre el arbol buscando el elemento recibido. Devuelve el nodo que contiene el mismo elemento que estoy buscando.
6. `liberar_nodo` Recorre el arbol destruyendo todo, osea aplicando la funcion destructor y liberando los nodos.
7. `abb_con_cada_elemento_x` es el iterador interno, recorre el arbol con el metodo indicado en el nombre de la funcion ya sea INORDER,PREORDER,POSTORDER. Utiliza la funcion recibida por argumento y si esta devuelve false deja de iterar, aumenta el contador recibido por parametro hasta que deja de iterar.
(Ver explicacion metodos de recorrido y diagrama 2).
8. `abb_recorrer_x` es el iterador externo, recorre el arbol con el metodo indicado en el nombre de la funcion. Recibe un array por parametro y su tamanio y va agregando los elementos leidos a ese array y aumentando su tamaño. Tambien recibe un contador y lo va a aumentando por cada elemento insertado en el array. (Ver explicacion metodos de recorrido y diagrama 2)

##### Metodos de recorridos
Existen 3 metodos de recorridos:
* **Inorder** Este es el mas comun, se utiliza para recorrer de manera ordenada el arbol ya sea numerica o alfabeticamente, consiste en primero visitar los subarboles izquierdo hasta el nodo final, luego el nodo actual (el anterior al nodo del subarbol izquierdo) y finalmente el subarbol derecho.
* **Preorder** Se utiliza para **clonar el arbol** primero se visita el nodo actual partiendo de la raiz, luego el subarbol izquierdo y finalmente el subarbol derecho.
* **Postorder** Se utiliza para **Destruir el arbol** primero se visita el subarbol izquierdo, luego el subarbol derecho y finalmente el nodo actual.

#### 4. Diagramas

1. Diagrama1

    ![Diagrama1](https://i.imgur.com/0L9PeOe.png "Insertar")

    En este caso tenemos un arbol vacio y vamos a ingresar los elementos 3 - 1 - 2 - 4, Empezamos poniendo la raiz(3) y este nodo incialmente va a tener un puntero a un nodo izquierda y derecha NULL, luego ingresamos los siguientes elementos, el 1 como es menor a 3 se va a insertar a la izquierda, luego el 2 como es menor a 3 va la izquierda y como es mayor a 2 va a la derecha y finalmente el 4 como es mayor a 3 va a la derecha. 
    >Nota: Cada vez que se inserta un nodo nuevo este inicialmente en la izquierda y la derecha apunta a NULL hasta que se ingrese algo diferente.


2. Diagrama2

   ![Diagrama2](https://i.imgur.com/4TkGBFy.png "Busqueda")

    En este caso podemos ver como se recorre el arbol mediante sus diferentes metodos. (Ver explicacion de metodos de recorridos). Dado que son bastante similares explicare el inorden, este si vamos a la explicacion vemos que recorre de manera Subarbol izquierdo -> Nodo actual -> subarbol derecho. es por eso que partimos del 3 vamos al izquierdo y nos paramos en 1, como el 1 no tiene izquierdo anotamos el 1, luego vamos al arbol derecho el 2, como este no tiene ni izquierda ni derecha anotamos al 2, ya que finalizamos este subarbol izquierdo volvemos a la raiz, como es el nodo actual lo anoto, me voy al subarbol de la derecha y como este no tiene ni izquierda ni derecha lo anoto.

3. Diagrama3

    ![Diagrama3](https://i.imgur.com/CXw0nsS.png "Eliminar hoja")

    **Metodo de eliminación nodo hoja**
    En este caso vamos a remover el elemento 2, recorremos hasta encontrar el 2 en el arbol, una vez lo hallamos encontrado podemos notar que es un nodo hoja(no tiene hijos) por lo tanto su eliminacion es sencilla, al no tener hijos solo liberamos ese nodo y finalmente el 1 va a apuntar hacia la derecha y izquierda a NULL.

4. Diagrama4

    ![Diagrama4](https://i.imgur.com/VwJkFyG.png "Eliminar 1 hijo")

    **Metodo de eliminación nodo con un hijo**
    En este caso vamos a remover el elemento 1, recorro hasta encontrar el 1 en el arbol, una vez lo hallo puedo notar que este posee 1 solo hijo por lo tanto no puedo removerlo directamente ya que sino pierdo la referencia a su hijo(el elemento 2), es por eso que lo que hago es linkear el padre del nodo a remover a su hijo, en este caso linkeo el 1 al 2, una vez hecho esto ya puedo remover el elemento ya que no pierdo la referencia al 1.

5. Diagrama5

    ![Diagrama5](https://i.imgur.com/SrCdoCU.png "Eliminar 2 hijos")
    **Metodo de eliminación nodo con dos hijos**
    En este caso vamos a remover el elemento raiz 7, recorro solo 1 vez hasta llegar al 7 ya que este es raiz, como tiene dos nodos hijos voy a buscar el **sucesor inmediato** osea el menor elemento del subarbol de la derecha, en este caso es el 12, en caso de que el 12 no tenga hijos simplemente lo reemplazo por el 7 en este caso la raiz, sin embargo en nuestro diagrama tiene un hijo 13 por lo tanto lo que tengo que hacer es asignar al padre del sucesor inmediato(14) al hijo del sucesor inmediato(13). Gracias a este paso que hice no perdi la referencia al hijo del sucesor inmediato y finalmente puedo reemplazar el sucesor por el 7 raiz.
    >Nota: Cada vez que un nodo de dos hijos se reemplaza con el sucesor inmediato este sucesor inmediato debe tener a la izquierda y derecha lo que tenia el elemento que iba a remover.