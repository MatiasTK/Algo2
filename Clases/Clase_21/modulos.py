import simple_linked_list

# El include en C copia el contenido de un archivo a otro
# EL import lo que hace es buscar el archivo,crea un modulo llamado lista con ese contenido.

print(simple_linked_list)

""" simple_linked_list = simple_linked_list.SimpleLinkedList()  ESTA MAL! eliminas el modulo lista.""" 

#Forma correcta

MiLista = simple_linked_list.SimpleLinkedList() 

#Otra forma

Modulo_lista = simple_linked_list
simple_linked_list = Modulo_lista.simple_linked_list()

#Otra forma

import simple_linked_list as tdalista

lista = tdalista.SimpleLinkedList()

#Otra forma
from simple_linked_list import Lista

MiLista = Lista()

# Importar desde subdirectorios
import tda.lista