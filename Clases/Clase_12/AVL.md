# <center>AVL</center>
----

## ¿Que es un AVL?
> Adelson-Velskii y landis

Es un **ABB** pero es **auto-balanceado**. Compeljidad $O(log(n))$
### Factor de balanceo
Atributo de cada nodo, es la diferencia entre las alturas de los arboles de la izquierda y derecha. Valores permitidos: -1,0,1.
### Rotacion a la derecha
Factor de balanceo: $\text{altura izquierda} - \text{altura derecha}$. Si la cuenta me da algo diferente de -1,0,1 tengo que hacer rotacion a la derecha. 
Rotacion derecha: Se va a rotar el numero que no coincide la cuenta osea, ahora el nodo central va a ser el anterior y el nuevo que no dio la cuenta lo voy a mover a la derecha.
![Rotacion_erecha](https://i.imgur.com/QshzCBm.png "Rotacion derecha")
En el caso en el que la imagen el 13 tenga algo a la derecha lo que hago es:
1. Hago que el 15 en la izquierda apunte hacia eso que habia en la derecha del 13
2. Hago que el 13 en la derecha apunte al 15
3. Notese que si el 15 tiene algo a la derecha tampoco lo va a perder
4. Ya esta =)
### Rotacion a la izquerda
Factor de balanceo : $\text{altura izquierda} - \text{altura derecha}$. Las bases son las mismas que la de rotacion derecha solo que aca cambia la rotacion.
Rotacion izquierda: Analizo igual que la derecha pero esta vez lo muevo a la izquierda
![Rotacion_izquierda](https://i.imgur.com/2Z4pcsF.png "Rotacion izquierda")
### Rotaciones dobles (Izquierda + Derecha)
Factor de balanceo : $\text{altura izquierda} - \text{altura derecha}$. 
![Rotacion_doble](https://i.imgur.com/vkiwSWo.png "Rotacion doble")
#### Con hijos
Hago lo mismo
![Rotaciones_dobles_hijos](https://i.imgur.com/HHFpox1.png "Rotacion doble hijo") 
### Rotaciones dobles (Derecha + Izquierda)
![Rotacion_doble_DI](https://i.imgur.com/qpU0O5W.png "Rotacion doble derecha izquierda")
#### Con hijos
![Rotacion_doble_DI_hijos](https://i.imgur.com/9Qt74GU.png "Rotacion doble derecha izquierda con hijos")

### Resumen
![Resumen](https://i.imgur.com/JXQGQmY.png "Resumen")
