//EJ -> https://i.imgur.com/rNMT8V2.png

[5,2,9,8,5,1,0,2,4]
Pivote = 8 -> elemento 4
Pos_pivote = 0 -> elemento 5

5 < 4 N
2 < 4 S
[2,5,9,8,5,1,0,2,4]
Pos_p = 1 -> e 5

9 < 4 N
8 < 4 N
5 < 4 N
1 < 4 S
[2,1,9,8,5,5,0,2,4]
pos_p = 2 -> e 9

0 < 4 S
[2,1,0,8,5,5,9,2,4]
pos_p = 3 -> e 8

2 < 4 S
[2,1,0,2,5,5,9,8,4]
ps_p = 4 -> e -> 5

Cambio con pos pivote
[2,1,0,2,4,5,9,8,5]

Divido a la mitad
[2,1,0,2] 4 [5,9,8,5]
v1 = [2,1,0,2]
v2 = [5,9,8,5]

Empiezo por V1
Pivote = 0 -> e 2
ps_p = 3 -> 2

2 < 2 N
0 < 2 S
[2,1,2,0] 
ps_p = 2

1 < 2 S
[2,2,1,0]
ps_p = 1

[2,1,0]
Piv = 2 -> e 0
pos_piv = 0 -> e 2

1 < 2 S
[1,2,0]
pos_piv = 1

[1,0,2]

[1,2]
Piv = 0 -> e 1

1 < 2 S
[2 1]

[1]

[2,2,0,1]

Sigo con V2

Piv = 0 -> e 5
pos_piv = 3 -> 5

5 < 5 N
8 < 5 N
9 < 5 N

[5,9,8,5]

[9,8,5]
Piv = 2 -> e 5
pos_piv = 0 -> 9

8 < 9 S
[8,9,5]

[8,5,9]

[8,9]
Piv = 0 -> e 8

9 < 8 N

[9]

[5,5,8,9]

Los uno 

[2,2,0,1,4,5,5,8,9]
Me quedo el vector armado


El mecanismo de quicksort funciona mediante un pivote y una posicion pivote para poder ir recorriendo el vector como
ya vimos mas arriba, la particularidad de este sort es que logra ser mas eficiente debido a su complejidad promedio de
O(nlogn) y en el peor de los casos O(n^2). Se basa en divide y conquista partiendo el vector en 2 partes y ordenandolas.





