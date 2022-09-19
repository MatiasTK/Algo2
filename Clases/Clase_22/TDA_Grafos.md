# TDA Grafos
---
## Que es?
Es como un abb pero donde se conocen todos con todos no hay hijos ni padres ni eso.
G = (V,E) -> V es el conjunto de vertices, E el conjunto de aristas.

## Para que sirve?
Para llegar a un punto especifico llegando por el lugar mas corto posible?

## Direccion
**No dirigido:** Aristas bidireccionales, osea que se pueden recorrer entre dos direcciones
![Nodirigido](https://i.imgur.com/HSSNuYG.png)
**Dirigido:** Al menos una de sus aristas es unidireccional(PUEDEN HABER BIDIRECCIONALES)
![Dirigido](https://i.imgur.com/ZwUrFBc.png)

## Pesos
Las aristas tienen un valor que simboliza el costo para transitar de un vertice a otro
![Peso](https://i.imgur.com/jnF6nCv.png)

## Clasificacion
* Grafo dirigido con peso
* Grafo dirigido sin peso
* Grado no dirigido con peso
* Grafo no dirigido sin peso

## Grafo simple
**No posee aristas multiples ni lazos**. En un par de vertices solo hay una arista.
![Simple](https://i.imgur.com/rUlIj2M.png)

## Densidad
Un grafo denso es uno que su numero esta myu cerca al valor maximo de aristas que puede tener.
**Calculo -> D = 2|E|/|V|(|V|-1)** Siendo D densidad, E edges(Aristas) y V vertices

## Ciclos
**Ciclo:** Recorrido de aristas adyacentes y terminan en el mismo lugar pasando una vez por cada arista.
![Ciclos](https://i.imgur.com/bh9v1af.png)
La segunda imagen seria un grafo aciclico ya que no podes "cerrar el camino".

## Caminos
Es el recorrido a traves de un grafo.
### Caminos simples
Es un camino pero que pasa **Solo una vez** por cada vertice.

## Componente conexa
Conjunto de vertices donde existe un camino de un vertice a otro
**Solo funciona para grafos no dirigidos**
![Conexa](https://i.imgur.com/eXfEXyJ.png)
Es como un intermediario que los une, sin ese intermediario no se puede llegar entonces no es conexo.
La conexa es un conjunto no el grafo entero.
Solamente los vertices.

## Grados
**Grados de entrada:** Cantidad de aristas que entran al vertice.
**Grados de salida:** Cantidad de aristas que salen del vertice
**Grafos no dirigidos -> Grados iguales**
![grados](https://i.imgur.com/UhgVaVw.png)

## Primitivas
* Grafo_crear()
* Grafo_insertar(grafo,elemento)
* Grafo_insertar_arista(grafo,arista)
* Grafo_borrar(grafo,elemento) -> Si elimino un elemento su arista debe desaparecer
* Grafo_borrar_arista(grafo,arista)
* Grafo_destruir(grafo)

**No hay aristas que no conecten a nada, si vertices que no conecten a nada**

## Matriz de adyacencia - Grafo no dirigido

1. Me paro en un vertice
2. Me fijo cuantas aristas de longitud 1 conecta con otro vertice
3. Completo la matriz!

![Adyacencia](https://i.imgur.com/xNMT4Cb.png)
Ejemplo de v2 a v1 conecta con 1 de v4 a v1 con 2, de V3 a a V4 no lo conecta nada por ejemplo entonces 0.
Es simetrica porque es de entrada y salida.

## Matriz adyacencia - Grafo dirigido
Solo se cuentan las flechitas no de idea y vuelta.
![Adyacencia_Dirigido](https://i.imgur.com/nWr81bI.png)
En los dos casos la diagonal son los lazos.

## Matriz adyacencia - Pesos
En vez de poner 1 pones el peso en el valor
![Adyacencia_pesos](https://i.imgur.com/R6DIH9J.png)

## Lista de adyacencia
Cada arista posee una lista simplemente enlazada de a que vertices esta unida.
![Lista_adyacencia](https://i.imgur.com/7bcpiEb.png)
Si quiero argregar cantidad ejemplo con v1 con v4 se conecta 2 veces lo agrego en la cantidad de la lista.
![Lista_adyacencia_final](https://i.imgur.com/Gy7zD1v.png)

## Lista adyacencia - Grafos dirigidos
Solo lo agregas si cumple la direccion
![lista_adyacencia_dirigida](https://i.imgur.com/E1aYF3o.png)

##  Lista adyacencia - Dirigida con peso
![Lista_adyacencia_peso](https://i.imgur.com/Hfadd1g.png)
Si hay dos flechas por ejemplo si de V1 habria dos flechas a V4 nos conviene agregarlo dos veces a la lista.

## Matriz de incidencia
Marco los vertices que son conectados por la arista.
E -> son las aristas.
![Matriz_incidencia](https://i.imgur.com/0pcy3qJ.png)

## Matriz de incidencia dirigida
Se pone -1 si sale del vertice y 1 si entra al vertice.
![Matriz_indicencia_dirigida](https://i.imgur.com/zsICu0g.png)
En el caso del e7 como es un lazo es un +- 1, en el codigo esto puede ser representado como un flag o lo que se te ocurra, un 2 por ejemplo.

## Matriz de indicidencia dirigida por pesos
Lo mismo que lo de arriba pero en entrada se pone el peso.
![Matriz_incidencia_pesos](https://i.imgur.com/bvd4Clt.png)

## Recorridos -> Interesante
**Es uno de los motivos principales por el cual existe este TDA**

* Visitar: Marcar como visitado al nodo.
* Explorar: Vamos a definir como se comporta el algoritmo (Explorar vecinos,hijos,etc).

## Tipos de recorridos

* **En anchura BFS(Breadth First Search):** Primero visitamos los hermanos/vecinos antes de visitar los hijos. Se utiliza la lista-cola
* **En profundidad DFS(Depth First Search):** Se visitan los nodos hijos primero hasta que no se pueda continuar, luego volves hasta un hijo donde se tienen mas camino y se vuelve a usar esa logica.

## Orden topologico
Se procesa todos los vertices de un grafo **Aciclico** de forma que si un grafo contiene la arista dirigida uv entonces el nodo u aparece antes que el nodo v.
![topologico](https://i.imgur.com/8Oj5TUg.png)
Serie de pasos para llegar a un objetivo. y lo ordenamos en una lista, podes hacerlo en el orden que quieras mientras tenga logica las flechas.
![topologico](https://i.imgur.com/xFO3gko.png)
Tienen una dependencia, no se puede llegar al objetivo final sin hacer los pasos anteriores.

## Dijkstra
Es el camino menos costoso a recorrer.

Es un algoritmo para determinar el camino mas corto dado un vertice de origen hacia el resto de vertices en un grafo que tiene pesos en cada arista.

Luego de obtener el camino mas corto el algoritmo se detiene.

**No funciona en grafos con aristas de pesos negativos.**

1. Se elige el vertice V sobre el cual aplicar el algoritmo.
2. Se crean dos listas de nodos, una lista de nodos visitados y otra lista de nodos NO visitados que contiene a todos los nodos del grafo.
3. Se crea una tabla con 3 columnas, vertice, distancia minima V, y el nodo anterior por el cual se llego.
4. Se toma el vertice V como vertice inicial y se calcula su distancia a si mismo, la cual es 0.
5. Se actualiza la tabla en la cual todas las distancias de los demas vertices a V se marcan como infinito(O un indicador).
6. Se visita el vertice no visitado con menor distancia conocida desde el vertice V, osea el nodo con distancia 0.
7. Se calcula la distancia entre los vertices sumando los pesos de cada uno con la distancia V.
8. Si la distancia es menor a la que esta en la tabla se van a actualizar los valores de la tabla y tambien los valores por el cual se llego.
9. Se pasa el vertice V a la lista de vertices visitados.
10. Se continua con el vertice no visita con menor distancia desde ese.
11. Repito todo.

![Inicial](https://i.imgur.com/1WMkY3k.png)
Tengo la tabla inicial con el grafo y la lista de visitados y no visitados.
![1](https://i.imgur.com/8bKQ2yR.png)
La distancia a A la marco como 0 y todos los demas los "marco" como infinito -> Esto son los primeros 5 pasos
![2](https://i.imgur.com/EcRQQxA.png)
Como desde A conecta con B(Vale 5) y D(Vale 6), como 5 y 6 es menor a infinito actualizo en la tabla la distancia y el vertice anterior. El vertice anterior es A ya que vengo desde ahi. Como entre B y D es mas barato ir por B voy a elegir a B.
![3](https://i.imgur.com/dAEYCZH.png)
B es mi nuevo nodo. El costo no lo cambio, va a ser 5. Desde B puedo ir a C(Coste 9) o D(Coste 4). Como 9 + 5 = 14 y 14 < Infinito lo reemplazo en la tabla, el vertice anterior es B. en cuanto a D me cuesta 5+4=9 Pero como 9 no es menor a 6 no lo cambio. Elijo mi nuevo vertice, en este caso va a ser D ya que es el que tiene menor distancia desde donde estoy parado (Coste 4 vs coste 9).
![4](https://i.imgur.com/tPo1Cm3.png)
Ahora estoy parado en el nodo D. Los caminos posibles son F(Coste 4+5+2) Y E(Coste 4+5+6). El camino mas corto hasta F es 11 por lo tanto en la tabla como 11 < inf pongo 11 como distancia y vertice anterior D. El camino mas corto hasta E es 15 como 15 < inf lo reemplazo en la tabla. No quedan mas caminos.
Elegis un nuevo vertice en este caso va a ser el F ya que es el mas barato para moverte D vale 6 entonces 6+2 = 8 y 6+6=12 como el 8 es del F es mas barato F.
![5](https://i.imgur.com/FMSmGCQ.png)
Ahora estoy parado en el Nodo F. Los caminos posibles son C (8+7)
y E(8+3), de F a C cuesta 15 como C vale 14 y 15 NO es menor a 14 no cambio nada, de F a E vale 14 como E vale 11 y como 11 es menor a 12 lo reemplazo en la tabla con su vertice anterior. Como me es mas barato moverme para E voy hacia E.
![6](https://i.imgur.com/vsTgzrz.png)
Ahora estoy parado en E. el unico camino posible es C (11+1)
12 < 14 reemplazo en tabla distancia y v anterior, te moves a la C ya que es el unico camino y el mas chico.
Finalmente marcas el ultimo como visitado y ya esta!

**Armo una tabla final**
De A hasta A -> no hago ningun camino
De A hasta B -> Vengo de A
De A hasta C -> Vengo de E -> Vengo de F -> Vengo de D -> Vengo de A
De A hasta D -> vengo de A
De A hasta E -> Vengo de F -> vengo de D -> Vengo de A
De A hasta F -> Vengo de D -> Vengo de A

**El orden del vector visitados es el camino mas corto desde A hasta el que vos quieras.**

## Aplicaciones
* Redes sociales -> amigos de facebook,instagram
* GPS -> El mapa hace el camino minimo
* Compiladores/Interpretes -> Por ejemplo para encontrar una linea en la que nunca la llegas a ejecutar ya sea por salir con un return antes por ejemplo o un vertice aislado.
* Redes de computadoras(servidores) -> El peso del grafo es el trafico que recibe el servidor.
* Rutas