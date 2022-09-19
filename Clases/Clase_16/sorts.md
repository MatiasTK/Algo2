# <center>Sorts</center>
---
## Merge sort
### Implementacion
teniendo un vector lo divido a la mitad
y a esos vectores tambien los divido a la mitad hasta que me quede 1 elemento y a partir de ahi empiezo a ordenar.
Empiezo por la izquierda y sigo por la derecha
![Merge](https://i.imgur.com/ODd2qX2.png)

## Quick sort
### Implementacion
Denomino el pivote en el principio,mitad o final del vector.
Denomino la posicion del pivote en la posicion contraria.
Suponiendo que el pivote lo defino al final y la posicion de pivote al inicio, busco los numeros mayores al pivote si son 2 por ejemplo ubico el pivote en la posicion 2.
![QS](https://i.imgur.com/DO6zZRs.png)
Vas cambiando la posicion del pivote  si el numero es mayor a el numero de la posicion del pivote hasta el final.
Ahora el pivote dividio a la mitad el vector, analizo la parte izquierda y luego la derecha.
![QS](https://i.imgur.com/0Hv0V5B.png)
![QS](https://i.imgur.com/HIVsfQf.png)
### Pasos
1. Inicializo pivote y posicion
2. Itero reubicando los mayores al pivote
3. Ubico al pivote
4. Llamo recursivamente a la izquierda y despues derecha.

## Counting sort
### Implementacion
1. Creas un array de 0 a 9
2. Inicializo en 0 todo
3. Itero incrementacndo segun la posicion
Si tengo 2 1 en la posicion 1 voy a tener un 2
4. Al actual le sumo el anterior
![Counting](https://i.imgur.com/gmILLK6.png)
5. Creamos un array en donde ordenar
6. Recorremos el primer array y por cada elemento nos vamos a esa posicion en el array del medio, en ese array del medio el elemento es la posicion del nuevo array y la posicion es el elemento.
![Counting](https://i.imgur.com/7dc2wFU.png)

## Bucket sort
### Implementacion
1. Se crean N bucket vacios
2. Recorro el arreglo original poniendo el elemento correspondiente en el bucket que debe contener
3. Ordeno cada bucket que no esta vacio
4. Visito los bucket en orden y pongo todos los elementos en el arreglo
![Bucket](https://i.imgur.com/b2vYPp6.png)

## Radix Sort
### Implementacion
Me da paja no sirve apra nada
