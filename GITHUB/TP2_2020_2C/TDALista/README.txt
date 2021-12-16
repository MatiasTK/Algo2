

												TDA LISTA - README


	El presente trabajo consta de la implementación de algunos Tipos de Dato Abstractos (TDA), es decir, tipos 
de datos no primitivos al lenguaje C, que tienen ciertas funcionalidades acordes a cada tipo de dato. En este caso, el TDA 
presentado es una Lista, pero que además posee funcionalidades de Pila y Cola. También se presenta el tipo de dato abstracto Iterador 
Externo, y un Iterador Interno, ambos para iterar por la lista implementada. Además, se añade una gran cantidad de pruebas, para asegurar
el correcto funcionamiento de todas las estructuras y sus funcionalidades.

	La Lista implementada tiene ciertas funciones primitivas, que corresponden a las operaciones que uno podría hacer con una lista de objetos 
normal. Estas son:
		
		• Crearla 	• Insertar un elemento al final 	• Insertar un elemento en una posición específica

		• Borrar el elemento del final 		• Borrar un elemento de una posición específica

		• Obtener el elemento en una posición específica 	• Obtener el último elemento de la lista

		• Ver si está vacía 	• Saber la cantidad de elementos 	• Destruirla


Además, como se mencionó anteriormente, contiene funcionalidades de Pila, que son:
	
		• Apilar un elemento 	• Desapilar un elemento 	• Obtener el elemento en el tope de la pila

Y también funcionalidades de Cola, que son: 

		• Encolar un elemento 	• Desencolar un elemento 	• Obtener el primer elemento de la cola


Por otra parte, el iterador externo implementado puede:

		• Ser creado 	• Saber si hay más elementos por iterar

		• Avanzar al siguiente elemento 	• Obtener el elemento actual

		• Ser destruido

	Para finalizar, la tarea del iterador interno es recorrer la lista y llamar a una función booleana que el usuario
le pase por parámetro con determinado contexto, que puede ser, por ejemplo, un contador. Esa función va a
determinar si se deben seguir recorriendo elementos o no y también realiza alguna acción con el elemento y el contexto,
como podría ser imprimir el elemento por pantalla con determinado formato y aumentar un contador, por ejemplo.
Finalmente, el iterador interno devuelve cuántos elementos pudo recorrer/iterar.

	Todos estos TDAs tienen sus respectivas pruebas en el archivo lista_pruebas.c



			COMPILACIÓN Y EJECUCIÓN


	En la carpeta del TDA se encuentra un makefile que facilita la compilación y ejecución del mismo y sus pruebas.
Las instrucciones para la utilización del makefile son las siguientes:

	• Para compilar y ejecutar el TDA con las pruebas implementadas:					make / make test
	• Para solo compilar el TDA con las pruebas implementadas: 							make c

	• Para compilar y ejecutar el TDA con las minipruebas propuestas por la cátedra:	make minitest
	• Para solo compilar el TDA con las minipruebas propuestas por la cátedra:			make cmini

	• Con alguna compilación ya hecha, para correr valgrind y ver memory leaks:			make memory
	• Con alguna compilación ya hecha, para correr gdb y debuggear:						make debug

	• Para borrar el archivo compilado lista_se:										make clean


Si el usuario no desea usar el makefile puede, en su defecto, correr los siguientes comandos:

	• Compilación con pruebas implementadas: 		gcc lista.c lista_pruebas.c -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -o lista_se

	• Compilación con minipruebas:					gcc lista.c lista_minipruebas.c -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -o lista_se

	• Ejecución: 									./lista_se

	• Chequeo de memory leaks con valgrind:			valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_se	

	• Debuggeo con gdb:								gdb ./lista_se

	• Borrado del archivo lista_se:					rm -rf lista_se



			FUNCIONAMIENTO / IMPLEMENTACIÓN


	Una lista se puede implementar de 3 principales formas, las cuales son:

	1. Como un vector estático: 
			Esto tiene la enorme desventaja de que, como dice su nombre, es estático, lo que quiere decir que tiene un tamaño fijo. 
		Por lo tanto, si mi lista implementada como vector estático tiene un tamaño límite de 10 elementos, no voy a poder 
		agregar más de 10 elementos a la lista. Además, claramente esta implementación requiere memoria contigua para almacenar 
		los N elementos de la lista.

	2. Como un vector dinámico:
			Esta implementación posee la gran ventaja de poder ampliar la lista a medida que agregamos elementos. Sin embargo, 
		esta implementación también requiere memoria contigua, ya que se hace uso de la función realloc para agrandar la lista, 
		la cual agranda o achica un bloque de memoria contigua. Por lo tanto, si mi vector tiene una enorme cantidad de elementos 
		(n), y quiero agregar más elementos, puede ocurrir que la función realloc falle porque no pudo encontrar un bloque de 
		memoria contigua de tamaño n+1.

	3. Como una lista de nodos enlazados:
			La implementación con más ventajas es la de nodos enlazados y es la utilizada en este trabajo práctico. Esta consiste en
		un primer nodo, que contiene un elemento y la dirección de memoria del siguiente nodo. Esa sería una lista simplemente enlazada,
		también existen las listas doblemente enlazadas y las listas circulares, pero no son el objetivo de este trabajo.

		En nustro caso,	la lista se representa con el tipo de dato lista_t, el cual contiene un nodo_inicio, que es el primer nodo de la 
		lista, un nodo_fin, que es el último, y la cantidad de elementos en la lista.

		La ventaja de esta implementación es que la lista se puede ir agrandando a medida que sea necesario, y no se requiere memoria 
		contigua, ya que cada nodo tiene la dirección de memoria del siguiente, que puede ser completamente independiente de la del nodo 
		actual. Por lo tanto, cada vez que se agrande la lista, solo se necesitaría reservar memoria para un nuevo nodo. Por ejemplo, si 
		se lo agrega al final, se modifica la dirección del "siguiente" que almacena el último nodo (nodo_fin), el cuál debería apuntar a 
		NULL, y se coloca allí la dirección de memoria del nodo nuevo. Además, el nodo nuevo pasa a ser el nuevo nodo_fin, y se modifica 
		la cantidad de elementos de la lista.

		Esta última implementación se eligió debido a que se quiere cubrir el peor caso, es decir, en el que se utilice una lista con una gran 
	cantidad de elementos, y de tamaño variable. Si se hubiera utilizado la implementación de lista como vector dinámico, las complejidades
	de insertar elementos y borrarlos, serían O(n), ya que se tiene en cuenta el peor caso, el cual es cuando el realloc no puede ampliar el
	bloque de memoria, y tiene que buscar otra sección de la memoria para copiar todo el bloque allí. En cambio, con la implementación de lista
	con nodos enlazados, esto no ocurre ya que como los nodos están ubicados en la memoria de manera independiente, no se requiere memoria contigua, 
	y, por lo tanto, las operaciones de insertar y borrar pasan a ser de complejidad O(1).


	Además, se cuenta con el TDA iterador, al cual llamamos iterador externo, y una función lista_con_cada_elemento, a la cual 
llamamos iterador interno. El iterador externo consta de un tipo de dato iterador_t que contiene la lista sobre la cual itera, 
y el nodo corriente sobre el cual está iterando. Cabe aclarar que si creo un iterador para una lista, este dejará de ser válido 
si la lista es modificada. En cambio, el iterador interno es una función llamada lista_con_cada_elemento que itera por una lista
con una función y un contexto que el usuario proporciona, como se explicó en la introducción. La utilización de un iterador en si ya
reduce la complejidad de iterar por la lista, en comparación a iterar "manualmente", cuya complejidad puede llegar a ser O(n²). Esto es, 
porque el iterador guarda el nodo corriente, entonces se mantiene el estado de la iteración.



			CONCEPTOS TEÓRICOS


	• ¿Qué es lo que entendés por una lista? ¿Cuáles son las diferencias entre ser simple o doblemente enlazada?

	Una lista es utilizada de forma cotidiana en el día a día de cualquier ser humano. Por ejemplo, al hacer las compras se hace una lista
de los elementos a adquirir y se van tachando a medida que se van añadiendo al carrito de compras. Esta consiste en una secuencia de elementos,
uno tras otro, que queremos guardar todos juntos. 
Sin embargo, en informática se tiene un concepto de lista más complejo, ya que una lista se puede utilizar para almacenar grandes cantidades de 
elementos, y quizás se quieran guardar en posiciones específicas, o borrar, etc. Es por esto que una lista se define como una estructura que agrupa
elementos, cada uno de ellos teniendo un elemento sucesor (excepto el último elemento), y un predecesor (excepto el primer elemento). Además, una 
lista posee las operaciones mencionadas en la introducción.

	Una lista simplemente enlazada consiste en un primer nodo que apunta al siguiente, y este al siguiente, y así hasta el último nodo que apunta
a NULL. Básicamente son nodos con referencias únicamente al siguiente nodo. La lista mantiene una referencia tanto al primer como al último nodo.
En cambio, en una lista doblemente enlazada, cada nodo posee una referencia al nodo anterior y al nodo siguiente (al predecesor y al sucesor). En
este caso, la lista también mantiene una referencia al primer y último nodo. La ventaja de este tipo de lista es que se hace más fácil recorrerla, 
ya que se puede ir tanto al nodo siguiente como al anterior.


• ¿Cuáles son las características fundamentales de las Pilas? ¿Y de las Colas?

	Una pila es un tipo de dato abstracto de tipo "LIFO" (Last in, First out), es decir, que el último elemento que se agrega a la pila
es el primero que se va a eliminar. Un ejemplo muy claro de esto es una pila de ropa, en la que voy siempre apilando elementos uno arriba del otro,
es decir que apilo siempre arriba del último elemento. Al desapilar, no puedo sacar la prenda de ropa que está abajo, ya que se caería todo. Entonces, 
se saca (desapila) primero el último elemento que fue añadido (apilado). En una pila, solo se puede conocer el último elemento, que se llama el "tope" de la pila.

	Una cola es otro tipo de dato abstracto de tipo "FIFO" (First in, First out), lo que quiere decir que el primer elemento que se añade a la cola 
va a ser el primero en eliminarse. Un ejemplo de cola sería justamente la cola/fila del supermercado para pagar las compras. En este caso, el primero
en entrar es el primero que va a pagar e irse con sus compras, ya que se sale por orden de llegada. Claramente, esto quiere decir que los elementos se 
añaden (encolan) por el final de la cola, y se eliminan (desencolan) por el principio de la misma. En una cola, solo se puede conocer el primer 
elemento de la misma.


• ¿Qué es un iterador? ¿Cuál es su función?

	Un iterador es una estructura que recorre secuencialmente los elementos almacenados en un tipo de dato abstracto, en este caso una lista. Este puede 
ser interno o externo. El iterador dispone de las funcionalidades mencionadas en la introducción: 

	• Ser creado 	• Saber si hay más elementos por iterar		• Avanzar al siguiente elemento 	• Obtener el elemento actual 	• Ser destruido


• ¿En qué se diferencia un iterador interno de uno externo?
	
	Un iterador interno permite recorrer todos los elementos de un TDA, en este caso una lista, sin tener que controlar el ciclo para recorrerlo. Es decir,
el usuario no le tendrá que decir que el iterador avance, sino que lo hará solo y de acuerdo a ciertas condiciones. Este iterador consiste en una función que
recibe como parámetro la lista a recorrer, una función booleana que le dice al iterador cuándo dejar de iterar y bajo qué condiciones, y un contexto. 
Ejemplificando para que sea más claro, se podría pasar al iterador una lista de nombres, una función que le diga que deje de recorrer cuando llegue a la letra
W, por ejemplo, y un contador que cuente cuántos nombres comienzan con la letra L. En este caso, el contador sería el "contexto", y se debería especificar en
la función enviada que el contador aumente siempre y cuando el nombre actual comience con L.

	En cambio, un iterador externo es un Tipo de Dato Abstracto (TDA) por si solo. El usuario controla el iterador mediante las primitivas mencionadas más arriba, 
y recorre secuencialmente el TDA (lista) a su gusto. Por lo tanto, es el usuario quien decide cuándo avanzar el iterador. En el caso de la lista, el TDA lista_iterador contiene
la dirección de memoria de la lista sobre la cuál itera, y el nodo_corriente que es el nodo sobre el cual "está parado".
