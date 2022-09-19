#<center>Heap</center>
----
## Caracteristicas
* El **nodo raiz es el maximo**
* Los **padres son mas grandes que los hijos**
* Los hermanos no tienen ninguna relacion
* Es un arbol casi completo
* Si me falta algun nodo **siempre falta del lado derecho**
Este un ejemplo de **Heap Maximal** ya que la raiz es el maximo

## Buscar maximo/minimo
Es el valor de la raiz. Complejidad O(1).

## Insertar
Se insertan los elementos en el primer lugar dispnible. A la derecha del ultimo elemento libre.
Si el elemento insertado es mayor al padre este sube. **Sift Up**. Repito hasta q no pueda subir mas.

## Eliminar maximo/minimo
Lo cambio por el numero que quiero cambiar.
La raiz antigua la hago "bajar" por la rama mas grande las veces necesarias y luego lo elimino.
Complejidad log(n).

## Construccion

### Meotdo basico
Inserto valores en el heap vacio uno a uno. N operaciones Log(N). Complejidad NLog(N)
![Representacion](https://i.imgur.com/X0vH435.png)

### Construir minimal
Seleccionas el ultimo elemento valido, desde ese punto hasta la raiz aplico **Sift Down** (Que se vayan para abajo los elementos mas grandes).

## Heapsort

Para aplicar heapsort tiene que ser un heap.
Extraigo la raiz para saber si es un heap minimal o maximal y reacomodo.
Repetiz el proceso hasta que te queda el vector ordenado. 
O(N LOG N)

## Ej de parcial

Armar un vector mediante heapsort.
