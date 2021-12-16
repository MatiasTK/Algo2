# <center>Resumen parcial ALGO2</center>
-------

## Recursividad 
**Friendly reminder**
Podes hacer calloc tanto para crear un struct como para crear un vector ej
![D](https://i.imgur.com/KUT6nTM.png)

Malloc se utiliza para crear elementos separados como nose algo perdido en el heap
char* caracter_suelto_heap = malloc(sizeof(char));

Creas v1 en el heap como Azul* v1 = calloc(1,sizeof(azul)) ya que es un struct
Y para crear el vector hacia a donde apunta v2 podes hacer
char** vectores[5]
for(int i = 0; i < 5; i++){
    vectores[i] = calloc(5,sizeof(char**))
}

## Complejidad
Big O -> utilizo el peor caso ejemplo

```c
for(...){ -> n * n + n
    for(...){
        suma += 1  -> n * n
    }
    suma +=1 -> n
}

return suma -> 1
```
Resultado -> O(n^2) el peor caso.

![EJ](https://i.imgur.com/F7o2IpN.png)

**Teorema maestro** -> Solo si se "divide el problema"
T(n) = aT(n/b) + f(n)
a -> veces que se llama a la misma funcion dentro de la misma.
b -> en cuanto se divide el problema por ejemplo si parto el vector a la mitad se divide en 2
f(n) -> es el resto suele ser O(1) -> se le llama "C"

IMPORTANTE: SI F(N) es negativa no se puede
o si a y b es menor a 1

- Calculo log_b(a) = C y tengo 3 casos:
1. Es menor -> T(n) = O(n^C) -> 1 < n 
2. Igual -> O(n^c log(n)) 
3. Mayor -> O(n^log_b(A))


**Casos teorema maestro**
Quicksort -> T(n) = O(nlogn) -> O(n^2) (**Peor caso**)
Mergesort -> O(n logn)
Heapsort -> O(n logn)
Bubblesort -> O(n^2)
Busqueda binaria -> T(n) = O(log n)

![Complex](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fdzone.com%2Fstorage%2Ftemp%2F13847346-1597432231216.png&f=1&nofb=1)

->El teorema maestro devuelve un Big Theta con reglas:
1) f(n) < nlog(base b)^a -> T(n) = Tita(n^((log_b)^a))
2) f(n) = nlog(base b)^a -> T(n) = Tita(n^((log_b)^a)l g n)
3) f(n) > nlog(base b)^a -> T(n) = Tita(f(n))

**Ejemplo extremo -> Si aplico busqueda binaria a una lista doblemente enlazada**
* Explicacion: como tengo que ir a la mitad de la lista y no puedo llegar con O(1) tengo que recorrer los elementos eso va a ser O(n/2) -> O(n).
* Solucion: Se soluciona con un iterador bidireccional para no tener que recorrer siempre desde el principio.

## Arbol rojo-negro

* La **raiz** del arbol es **negro**
* Las **hojas NULL**(Arboles sin hijos) son **negro**
* Los **nodos rojos** deben tener almenos **dos hijos negros**
* **NO** hay nodos **rojos consecutivos**
* Cualquier camino desde un nodo hacia abajo siempre tiene la **misma cantidad de nodos negros** de cualquiera de los dos lados

Dato no oficial: siempre que insertas un dato nuevo inicialmente antes de analizar todo va a ser rojo

## Arbol B
* K es la cantidad maxima de claves
* Las claves tienen que estar **Ordenadas**
* **Cantidad minima de claves** es k/2 sin contar raiz
* nodo tiene como maximo **MAX = k+1** descendientes
* **Cantidad minima descendientes** es m/2 excepto hoja y raiz.

## Arbol AVL
* Valores permitidos -> -1,0,1.
* Factor balanceo: altura izquierda - altura derecha.

## Heap
* El **nodo raiz es el maximo**
* Los **padres son mas grandes que los hijos**
* Los hermanos no tienen ninguna relacion
* Es un arbol casi completo
* Si me falta algun nodo **siempre falta del lado derecho**
Este un ejemplo de **Heap Maximal** ya que la raiz es el maximo

## Heapify y heap sort
**Sift**
* Down -> Comparo con los hijos y me hundo para el lado que este el mayor/menor de los dos hijos.
* Up -> Suben los mayores en el maximal, comparo el elemento insertado con el padre, los intercambio y repito recursivamente. Si esta lleno se crea un nuevo nodo a la izquierda.

**Heapify**
* In place -> Destapo uno a uno los elementos desde posicion 0 e hago inserccion.
* No in place -> Empiezo desde el final, busco el padre del ultimo elemento aplico sift down y voy hacia el inicio del vector.

**Heap sort**
1. Aplico heapify -> bajo por el lado menor. y acomodo.
2. Extraigo raiz -> intercambio con el ultimo y acomodo con sift down.
3. Repito.


## Quicksort
1. Inicializas pivote y posicion de pivote. El pivote puede ser el principio el final o el medio o cualquier valor, si el pivote es el ultimo por ejemplo la posicion pivote es el principio.
2. Iteras comparando mayores desde la posicion, osea si el elemento que esta en la posicion es mayor al elemento pivote swapeas el elemento de la posicion pivote con el elemento mayor Y AUMENTAS en 1 la posicion pivote.
3. Ubicas al pivote
4. Llamas Recursivamente a la izquierda y derecha (Se divide el vector en 2)
5. Aplicas las mismas operaciones
6. Te quedan todos los subvectores ordenados y pordenas por el pivote

## Mergesort
1. Dividis el vector a la mitad
2. llamas con izquierda y derecha
3. Repetis en subvectores
4. Haces merge

- Explicacion: Tengo un heap, extraigo un elemento, lo mando al final del vector, reacomodo el heap y repito mientras me queden elementos.
**Para que el vector sea heap hay que armarlo con heapify**

## Listas
**Vector estatico**
* Crear -> O(1)
* Destruir -> O(n) para eliminar cada elemento, O(1) para eliminar la lista
* Insertar -> O(1)
* Quitar -> O(1)
**Vector dinamico**
* Crear -> O(1)
* Destruir -> O(n) para eliminar cada elemento, O(1) para eliminar lista
* Insertar -> O(n) porque hay que hacer realloc de todos los elementos
* Quitar -> O(n) porque hay que liberar todos los elementos
**Nodos enlazados**
* Crear -> O(1)
* Destruir -> O(n) hay que recorrer cada nodo y destruirlos
* Insertar -> O(1) 
* Quitar -> O(1)

## Cola

**Vector estatico**

* Encolar -> O(1)
* Desencolar -> O(1)
* Desencolar desplazando elementos -> O(n)
* Desencolar cola circulas -> O(1)

**Nodos enlazados**
* Encolar -> O(1)
* Desencolar -> O(1)

## ABB
* Buscar -> O(n)
* Insertar -> O(n)
* Borrar -> O(n)
