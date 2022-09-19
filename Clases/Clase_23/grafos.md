# Grafos
----

## Direccion
* No dirigido -> Las aristas tienen doble direccion, osea van y vinene
* Dirigido -> Las aristas tienen sentido osea puede ir pero no venir

## Peso
* Las aristas tienen pesos asignados

## Orden
* Orden -> Cantidad vertices
* Tamaño -> Cantidad aristas
* Grado -> cantidad de aristas incidentes

## Vacio
* Nulo -> Si no tiene vertices -> Como no tiene vertices tampoco tiene aristas
* Vacio -> no tiene aristas

## Bucles
* Bucle -> Cuando conecte al vertice consigo mismo
* Simple -> No posee bucle ni aristas paralelas
* No simples -> Posee aristas paralelas -> Dos flechitas que van y vienen

![Bucles](https://i.imgur.com/X9du7Pu.png)

## Completitud
* Completo -> Contiene todas las aristas posibles
* Incompleto -> no contiene todas las aristas posibles

![Completitud](https://i.imgur.com/eidUMUV.png)

## Caminos
* En un camino **NO** puede haber vertices repetidos -> exceptuando el ultimo o primero
  
## Ciclos
* Ciclico -> Cuando un camino empieza y termina en el mismo vertice
* Si no posee ciclos -> No se puede terminar de hacer un camino de todos los elementos de la matriz.

## Conexo
* Conexo -> Para cualquier par de vertices existe un camino entre ellos
* No conexo -> Si desde cualquier vertice no puedo llegar a otro es no conexo
  
## Tipos de conexo
* Fuertemente conexo -> Si todos los nodos tienen un camino de ida y vuelta
* Debilmente conexo -> Si para lograr llegar a uno solo tengo que invertir el sentido de una flecha
* No conexo -> Si Hay un nodo que no lo puedo unir con nada

![Conexo](https://i.imgur.com/8pZKfWV.png)

## Arbol
* Grafo es un arbol si es **Conexo y aciclico**

## Recorridos

### En profundidad

**Se piensa como una pila**

1. Apilo un vertice
2. Quito el vertice y lo visito
3. Apilo los vertices adyacentes (A los del alrededor) al actual
4. Repito desde 2

### A lo ancho

**Se piensa como una cola**

1. Encolas un vertice
2. Quitas el vertice de la cola
3. Encolas los vertices adyacentes (A los de alrededor) al actual
4. Repetis desde 2