# Cosas de consolas
----

## Comandos utiles

* Las consolas tienen autocompletado -> Hay muchas cosas que si apreto tab me autocompleta con el archivo que quiero.
* mkdir -> Crear un directorio
* ls -> Listar lo que hay en directorio
* cd -> cambiar directorio.
* Nombres especiales ls -> "." es el archivo que hay actualmente si hago ls . me muestra lo que hay en el directorio actual. ".." me muestra lo que hay en un directorio atras.
* Touch -> Si el archivo no existe lo crea, si existe te modifica la fecha de ultima modificacion a la actual.
* Cat -> Muestra por consola lo que contiene un archivo
* Grep -> Sirve para buscar dentro de 1 o mas archivos, EJ: "grep main *" busca en los archivos de texto si alguno tiene la palabra main, el * es para que busque en todo el lugar donde estoy.

## Manejo de errores - Signal
Son eventos que le puedo mandar a un programa. Si el programa no esta programado para manejar un señal aborta directamente.
* Stdin -> lo que entra por teclado o por un archivo.
* Stout -> lo que sale por consola o por un archivo.
* Stderr -> los errores que salen por consola.
* Control + C manda un abort -> Termina el programa con error
* Control + D manda un EOF -> Cierra el archivo stdin y ejecuta lo que falta del programa.
* ./archivo < entrada.txt -> Reemplaza el stdin que es lo que recibe el programa por teclado por lo que tiene el archivo
* ./archivo > salida.txt -> Reemplaza el stdout por el archivo que recibe en vez de imprimir lo que se ejecuto por pantalla lo pone en el archivo.
* Si quiero por ejemplo hacerlo con valgrind necesito el stderr -> 2 > &1
* Control + Z -> Suspende el programa, espera a que yo lo reanude lo deja como en estado de "pausa".
* fg -> manda en primer plano un programa sirve por si lo suspendo y quiero ejecutar otro para volver a este.
* jobs -> Muestra los trabajos corriendo o suspendidos.
* Historial de la cosola -> history muestra todos los comandos ejecutados previamente.
* Control + R -> Buscas en el historial un comando, Ej "control + R, escribo gcc" busca los comandos que tengan la palabra gcc.
* Usar el valor que devuelve el main -> Desde la consola puedo hacer echo $? muestra el numero con el que termino el main.
* ./archivo >> log.txt -> Guarda todo en un log pero deja el log anterior osea si yo ejecuto escribe el log y si vuelvo a ejecutar no borra el log anterior.
