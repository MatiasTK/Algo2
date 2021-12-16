# Algoritmo floyd, prim y kruskal
----
## Algoritmo de floyd - No es spanning tree
Armo una matriz de distancias
![](https://i.imgur.com/4ftW9S5.png)

Recorro cada vertice y por cada vertice tomo el resto de vertices de a pares osea si tengo 4 voy a agarrar
1-2, 2-3, 1-3, 3-1, 3-2, 2-1 y comparo que es menos costoso si ir directo o desviarme por esos vertices

![](https://i.imgur.com/aXjrMZW.png)
.
![](https://i.imgur.com/6Q2d7Ne.png)
Actualizo la matriz

El vertice original casi no se modifica
De 2 a 1 lo mas barato es 7 y no desviarme por ejemplo.
De 4 a 2 dice infinito pero si voy a 1 y de 1 a 2 me cuesta 10 lo cual es mas barato por lo tanto lo cambio
![](https://i.imgur.com/arywLoz.png)
Vuelvo a actualizar
como de 3 a 1 era infinito pero pasando de 3 a 2 y de 2 a 1 es 8 lo cual es menor lo reemplazo.
![](https://i.imgur.com/BWunmcN.png)

## Algoritmo de PRIM
Es un arbol con la menor cantidad de aristas posibles, con este algoritmo gasta lo menos posible para llegar a esos vertices del arbol.
Es un algoritmo GREEDY busca lo minimo inmediato.
![](https://i.imgur.com/TEnhkmO.png)
Si empiezo por el 4 la arista de menor coste es de 3 asi que voy a ir al 9.
En la siguiente iteracion el menor es 1 asi que añado el 10.
En la siguiente es el 3 añado el 5.
En la siguiente NO puedo tomar el 4 ya que me lleva al 4 que ya lo tengo añadido entonces voy a tomar el 5 del 10 para ir al 13.
![](https://i.imgur.com/6s1rV98.png)
![](https://i.imgur.com/90c0AiO.png)
![](https://i.imgur.com/aJ3pdTn.png)
Aca es donde NO se toma el 4 ya que el 4 ya esta recorrido, en este caso voy a tomar el 5 para llegar al 13.
![](https://i.imgur.com/uZNV47G.png)
Como tengo en dos oportunidades 7 agarro cualquiera por ejemplo 1
![](https://i.imgur.com/QQAbNo5.png)
![](https://i.imgur.com/MxKeTEl.png)
Aca no puedo tomar el 3 porque genero un ciclo voy a tener que agarrar el 4.

Con esto generamos un spanning tree minimo.

## Algoritmo de kruskal
Tambien es un spanning tree. 
Es un algoritmo GREEDY.
Toma cada vertice como un grafo, por lo tanto tiene como "un conjunto de arboles".
Sirve para conseguir un spanning tree minimo tambien.
![](https://i.imgur.com/YYMZuol.png)
Las ordeno de menor a mayor y las voy recorriendo de menor a mayor y voy agregando y uniendo arboles.
Entre 1 y 2 se unen dos arboles distintos me lo quedo, lo mismo con el 9-10,, lo mismo con 3-7, lo mismo con 7-8.
Pero 3 y 8 NO! porque forman parte del mismo arbol.