# <center>Arboles y Arboles binarios de busqueda</center>
------------
## Arboles
* **¿Que son?**
Son colecciones de nodos que pueden estar conectados a otros nodos, tienen ramificaciones, el nodo principal llamado r y subarboles T1, T2, Tn
* **¿Porque se crean?**
Representa una jerarquia de los datos para optimizar la busqueda, se busca hacer algo similar a la busqueda binaria
### Tipos de arboles
1. Arboles N-arios o generales
2. Arboles Binarios
3. Arboles binarios de busqueda
4. AVL
5. Arbol Rojo-Negro
6. Arboles B,B+,B*
7. Otros
### Estructura (Recursividad)
Tienen una estrcutura parecida a la recursividad
* **Condicion de corte**
* **Llamada a la funcion**
### Definiciones
Son colecciones de nodos, los nodos son elementos del arbol.
Raiz $\to$ 1er nivel del arbol
Subarbol $\to$  Son los arboles debajo de los nodos
Nodos padres $\to$  Son los arboles superiores a los nodos
Nodos hijos $\to$  Son los arboles inferiores a los nodos
Hojas $\to$  Son los nodos que **NO** tienen hijos
## Arboles binarios
Se relacionan con operaciones de busqueda binaria, la **raiz solo esta conectada a dos subarboles** lo cual nos permite definir la nocion de izquierda y derecha
### Operaciones
* Crear
* Destruir
* Insertar
* Borrar
* Buscar
* Preguntar si esta vacio
* Recorrer
* Preguntar si tiene hijos y cuantos
### Recorridos
Pasamos por cada uno de los nodos. Para recorrerlo tenemos 3 elementos:
* El nodo actual $\to$  N
* El nodo derecho $\to$  D
* El nodo izquierdo $\to$  I
#### Posibles recorridos
* **Preorder** $\to$  Primero se visita el nodo actual, despues el subarbol izquierdo y luego el derecho, se usa para **clonar el arbol**.
* **Inorder** $\to$  Primero se visita el subarbol izquierdo, despues el nodo actual y luego el subarbol derecho.
![Inorder](https://i.imgur.com/sS1eJKd.png "In order")
* **Postorder** $\to$  Primero se visita el subarbol izquierdo, despues el subarbol derecho y por ultimo al nodo actual, se usa para **destruir el arbol**.
![Postorder](https://i.imgur.com/vn6C1yq.png "Post Order")
## Arbol binario de busqueda 
Tienen un orden y cada nodo **posee claves.**
* Las claves mayores se insertan en los subarboles derechos
* Las claves menores se insertan en los subarboles izquierdos
* Ambos son subarboles de busqueda binaria
### Busqueda
Comenzando en el nodo raiz
1. Se compara con el nodo raiz si las claves son iguales se detiene
2. Si es mayor la busqueda se reanuda en el subarbol derecho
3. Si es menor la busqueda se reanuda en el subarbol izquierdo
4. Si encuentra la clave en algun subarbol se detiene la busqueda
### Insertar
1. Comparo la clave con la clave del nodo raiz, si es mayor avanzo al subarbol derecho si es menor al izquierdo
2. Repito el proceso 1 hasta encontrar un elemento con clave igual o llegar al final de algun subarbol.
3. Cuando llego al final creo un nuevo nodo, asignando NULL a los punteros izquierda y derecha, luego coloco el nuevo nodo como hizo o izquierdo dependiendo si es menor o mayor que el nodo anterior.
4. Opcional! si decidi aceptar duplicados entonces el duplicado lo voy a poner a la izquierda
### Borrar
1. Entro por la raiz y comparo, si es mayor voy a la derecha, si es menor a la izquierda
2. Repito el 1 hasta llegar al numero que quiero borrar
3. Si no encuentro el elemento salgo
4. Si lo encontre y acepte tener duplicados tengo que abarcar esa posibilidad
5. Si lo encontre si no tiene nada a la izquierda y derecha es un **nodo hoja** por lo tanto lo borras(Creo q lo haces null)
6. Si lo encontre y tiene algo a la izquierda o derecha es un **nodo con un hijo** añado el hijo que tiene el que quiero borrar al padre del que yo quiero borrar (Se utilizan punteros auxiliares)
7. Si lo encontre y tiene dos cosas algo a la izquierda y derecha es un **nodo con dos hijos** Busco el succesor del nodo a borrar (el que esta a la derecha) y de ahi bajo por los izquierdos hasta el final, con eso consigo el **Sucesor inmediato** el cual es el numero mayor mas cercano al que voy a borrar y ahi inserto los subarboles de el nodo que voy a eliminar, si el sucesor inmediato tiene un nodo a la derecha lo asigno al padre a la derecha del sucesor inmediato

### Recorridos aplicados a ABB
* **Preorden** $\to$  Sirve para **clonar** una ABB
* **Inorden** $\to$  Sirve para **recorrer ordenadamente** (menor a mayor)
* **Posorder** $\to$ : Sirve para **destruir** una ABB

### Aplicaciones de los arboles
* Para conformar indices con uno o multiples niveles
* Mejoran algoritmos de busqueda
* Matienen ordenados streams de informacion entrante
* Estructuran datos como TreeMap y TreeSet se implementan como ABB balanceados
* Se usan en colas de prioridad doble

## Machete

![Machete](https://i.imgur.com/s4veOJ1.png "Machete Arboles")

## Pagina interactiva
[Pagina interactiva](https://www.cs.usfca.edu/~galles/visualization/BST.html "Esto te va a servir una locura para el TDA")
