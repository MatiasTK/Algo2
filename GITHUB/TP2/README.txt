¿Que es lo entregado?

El siguiente trabajo se trata de un juego llamado "Aventura pokemon"
el cual se basa en un jugador con una cierta cantidad de pokemones,
y un conjunto de gimnasios con entrenadores y 1 lider, a los cuales
el jugador se tendra que enfrentar.
Una vez haya ganado todos los gimnasios, este jugador pasara a ser
un maestro pokemon.

Se brinda un archivo de gimnasios y uno de jugador para la ejecucion del juego.

----------------------------------------------------------------------------

COMPILACION Y EJECUCION:

[SOLO CORRE DE MANERA CORRECTA EN UNA TERMINAL DE LINUX QUE TENGA GCC, MAKEFILE Y VALGRIND INSTALADOS]

Para la compilacion y ejecucion se ofrece un archivo makefile:

    •lINEA DE COMANDO PARA EJECUTAR EL JUEGO:
        -> make ejecutar_juego
    
    •LINEA DE COMANDO PARA EJECUTAR EL JUEGO JUNTO CON VALGRIND:
        -> make valgrind_juego
    
    •LINEA DE COMANDO PARA EJECUTAR EL DEBUG DEL JUEGO:
        -> make debug_juego

------------------------------------------------------------------------------

TIPOS DE DATO ABSTRACTO UTILIZADOS EN EL TRABAJO:
-Lista simplemente enlazada.
-Heap.

•Justificacion de utilizacion de heap para almacenar gimnasios:
Utilizo un heap para almacenar gimnasios ya que, al ser minimal,
el elemento de la raiz siempre sera el de menor dificultad, lo que
permite llevar un flujo de juego ordenado de menor dificultad a mayor
difucltad.

•Justificacion de utilizacion de lista simplemente enlazada para almancenar entrenadores:
Utilizo una lista para almacenar entrenadores debido a que en ciertas
situaciones me veo en la obligacion de recorrer esta lista, cosa que en
otros tipos de datos generaria un mayor uso de memoria, ademas de aumentar
la complejidad del programa en general.
Por ejemplo, con una pila tendria que utilizar una pila auxiliar, y luego reservar mas
memoria para almacenar los datos de la pila antigua ya que estos se liberan con el
destructor.

•Justificacion de utilizacion de lista simplemente enlazada para almancenar pokemones de entrenadores:
Utilizo una lista para almacenar pokemones de entrenadores debido a que en
ciertas situaciones me veo en la obligacion de recorrer esta lista, cosa que en
otros tipos de datos generaria un mayor uso de memoria, ademas de aumentar
la complejidad del programa en general.
Por ejemplo, con una pila tendria que utilizar una pila auxiliar, y luego reservar mas
memoria para almacenar los datos de la pila antigua ya que estos se liberan con el
destructor.

•Justificacion de utilizacion de lista simplemente enlazada para almacenar pokemones de pelea y obtenidos
del jugador:
Utilizo una lista para almacenar pokemones de pelea y obtenidos del jugador; primero, porque
se da la situacion de tener que recorrerlos; segundo, porque al momento de ofrecerle al jugador
cambiar la lista de pokemones de pelea, tengo que intercambiar posiciones de las listas especificas,
por lo que necesito utilizar las primitas 'lista_elemento_en_posicion' y 'lista_borrar_de_posicion'.

-----------------------------------------------------------------------

ACLARACIONES:

•Lectura y formato del archivo de gimnasio:
Para que el archivo de gimnasio sea cargado correctamente, éste debe respetar
al pie de la letra el formato que el codigo espera leer, de lo contrario, no solo
no se cargara el/los gimnasio/s sino que se borraran gimnasios que se hayan cargado
anteriormente. Esto se hace para evitar tanto perdidas de memoria como datos mal
cargados.

Formato del archivo de gimnasio:

Si la dificultad del gimnasio es negativa, se tomara como error y no se leera el archivo.
Si el ID funcion no esta en el rango de 0 a 4 incluido, se tomara como error y no se leera el archivo.
Un gimnasio sin lider o que no este despues de los datos del gimnasio sera tomado como error y no se
leera el archivo.
Un lider o entrenador sin pokemones sera tomado como error y no se leera el archivo.

G;Nombre del gimnasio;Dificultad del gimnasio;ID funcion del gimnasio
L;Nombre del lider
P;Nombre pokemon 1 del lider 1;Velocidad del pokemon;Defensa del pokemon;Ataque del pokemon
/*a partir de aca se escriben la cantidad que quiera de pokemones del lider, pero 
el limite de pokemones de pelea es 6, por lo tanto se cargaran solo 6*/
P;Nombre pokemon n del lider 1;Velocidad del pokemon;Defensa del pokemon;Ataque del pokemon
E;Nombre del entrenador 1
P;Nombre del pokemon 1 del entrenador 1;Velocidad del pokemon;Defensa del pokemon;Ataque del pokemon
/*la cantidad de pokemones que quiera, pero se cargaran maximo 6*/
P;Nombre del pokemon n del entrenador 1;Velocidad del pokemon;Defensa del pokemon;Ataque del pokemon
E;Nombre del entrenador n
P;Nombre del pokemon 1 del entrenador n;Velocidad del pokemon;Defensa del pokemon;Ataque del pokemon
/*la cantidad de pokemones que quiera, pero se cargaran maximo 6*/
/*se puede cargar la cantidad de entrenadores que quiera, no hay limite ahi (trate de no escribir 100, es mucho)*/
P;Nombre del pokemon n del entrenador n;Velocidad del pokemon;Defensa del pokemon;Ataque del pokemon

/*Si quiere escribir otro gimnasio en un mismo archivo lo puede hacer, solo debe respetar el formato
antes mencionado*/


•Utilizacion de 'return' dentro de 'while':
Si bien se que no es una buena practica, considero que aporta legibilidad a codigo y ahorra
lineas de codigo. Ademas se tiene en cuenta tanto la apertura del archivo como la memoria
reservada antes de salir de la funcion.
