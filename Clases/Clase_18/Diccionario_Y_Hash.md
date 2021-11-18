#<center> Diccionarios y Hash </center>
-------

## Diccionario
* Coleccion de pares (Clave,valor)
* Accedo a un elemento o lo establezco mediante su clave.
* La clave funciona como un indice para un array.

**¿Porque usarlo?**
* Performance para acceder al dato
* No hay duplicados

**¿Como se implementa?**
Con tablas de hash
* Es una estructura que contiene valores
* Puede hallar un valor a partir de una clave
![Hash](https://i.imgur.com/f395VaW.png)

**Colisiones**
* Pueden haber mas claves que espacios en la tabla de hash
![Hash](https://i.imgur.com/wgfqY8h.png)

**Tipos de hash**
Direccionamiento cerrado -> Hash abierto
Direccionamiento abierto -> Hash cerrado

**Hash abierto**
* Si hay una colision igualmente vamos a ir a esa dirrecion de memoria
![Hash_abierto](https://i.imgur.com/FcdMGuu.png)
* Esta colision se resuelve mediante listas simplemente enlazadas por orden en como se insertan los valores
* Ya que los cuadraditos de valores van a contener listas no punteros a claves entonces no tengo problema en añadir.
* Se dice abierto porque la informacion se guarda "afuera" de la tabla de hash
* El direccionamiento es cerrado ya que la clave siempre va a estar en el indice que devuelve el hash, no va a estar en otro lugar.
* Complejidad buscando un valor -> O(n) siendo n la cantidad de elementos que colisionaron y en lista enlazada. Pero depende del TDA

**Hast cerrado**
* Todos los valores se guardan adentro de la misma tabla.
* El tamaño de la tabla >= numero de claves.
* En caso de colision lo que se hace es poner el valor en el elemento libre mas proximo.
* Direccionamiento abierto -> ya que puede estar en otra posicion que no medio el hash
* Hash cerrado -> Guardo todos los valores en la misma tabla.
![Hash_cerrado](https://i.imgur.com/cPbj7FY.png)

**Tipos de busqueda hash cerrado**
* **Probing lineal** -> Busca el siguiente espacio libre inmediato.
* Probing cuadratico -> Cuando trata de indexar y esta ocupado busca la siguiente posicion en un polinomio
* Hash doble -> aplicar otra hash a la clave cuando colisionan

**Factor de carga**
$ \alpha = \frac{n}{m}$
n -> numero de claves almacenadas
m -> capacidad tabla de hash
* Indica el grado de ocupacion de la tabla de hash y su probabilidad de colision.
* Esta entre 0 y 1.

**Rehash**
* Cuando $\alpha$ >= 0.75 hay que rehashear
* La capacidad de la tabla deberia aumentar
![Rehash](https://i.imgur.com/Z51pqa0.png)

**Operaciones hash**
* Crear
* Insertar
* Obtener
* Cantidad
* Destruir
* Quitar
* Contiene

**Insertar - Hash cerrado**
Se calcula el hash mediante 
Hash = Clave % tamaño de tabla
![Insertar](https://i.imgur.com/o75Y4E1.png)
Como el 40 tiene hash 0 pero esta ocupado busca la siguiente posicion vacia y lo ocupa. Si esta ocupada esa poicion busca la siguiente.

**Insertar existente - Hash cerrado**
Si cuando esta recorriendo se encuentra la clave que quiere insertar significa que tendria que duplicar pero como en hash no hay duplicados lo que va a  hacer es borrar el valor de esa clave ya insertada y poner el nuevo.
P = (P + 1) % Tamaño de tabla
![Insertar_existente](https://i.imgur.com/z8G3aZO.png)
Como el 26 ya existia con otro valor lo que se va a hacer es actualizar con el ultimo valor.

**Rehash - Hash cerrado**
![Rehash](https://i.imgur.com/0YAgJLk.png)

**Obtener - Hash**
* Complejidad O(1)
Busco en el valor de Hash, si no esta ahi osea hay otra cosa sigo buscando hasta que lo encuentre o encuentre un espacio vacio. 
![obtener](https://i.imgur.com/Mi5Gg4w.png)
En el peor de los casos O(n) pero es un caso muy dificil ya que significa que rehasheaste mal. El promedio es O(1).
![Obtener_inexistente](https://i.imgur.com/uGPIM2e.png)
Si intento obtener una clave que no existe va a encontrar un espacio vacio y se va a a ir.

**Quitar - Hash**
voy a la posicion de hash, si tienen la misma clave lo borro y la flaggeo (Marco que anteriormente estuvo ocupada).
Otra opcion es reemplazar el espacio que acabamos de vaciar con el siguiente.
Quitar con reemplazo es la mejor opcion ya que flaggear actua diferente con cada hash.

**Quitar con reemplazo - Hash**
Busco el proximo que este mal ubicado osea que su hash no coincida con su posicion.
![Quitar_Hash_Reemplazo](https://i.imgur.com/9iyUg24.png)
Como el 40 tiene hash 0 esta en la posicion 2 podemos subirlo una posicion.
Hacemos lo mismo con esta nueva posicion desocupada, el 2.
![Quitar_Hash_Reemplazo](https://i.imgur.com/QHMRc4n.png)
Como las dos siguientes claves estan bien en posicion no las muevo y como encontre un espacio vacio dejo de iterar.