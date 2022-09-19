# Explicacion para remover con 2 nodos

1. Me centro en el nodo que tengo que remover
2. Voy para el subarbol de la izquierda
3. Busco el mayor de ese subarbol, osea voy tomando los valores de la derecha mientras este no sea NULL
4. Una vez que lo encuentro copio el valor de ese nodo(El mayor del subarbol izquierdo) al nodo que quiero remover
5. Como reemplaze el nodo que quiero remover este ya no existe pero si **Si el nodo con el que lo reemplaze llega a tener un hijo en la izquierda** lo que hago es que al nodo anterior al que voy a intercambiar lo hago apuntar en la derecha hacia el hijo del que voy a intercambiar (Como se que seguro no entendiste un pingo te dejo una foto mejor)
![Eliminar_Nodo_Dos_Hijos](https://i.imgur.com/mNP18N7.png)
7. Finalmente remuevo ese nodo original que intercambie.