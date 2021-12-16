// EJ -> https://i.imgur.com/dNk2vQS.png

1.
for(int i = 0; i < n; i++) Hace n iteraciones

for(int j = 0; j < n * n; j++)Hace n iteraciones

ambos if son O(1) ya que en este caso tomo que printf es un algoritmo O(1)

por lo tanto considerando el peor caso el cual es donde entra al if este algoritmo es O(n^2)

2. Tiene la estructura de teorema maestro, lo aplico.
a = 10
b = 3
c = f(n) = n^2

log_3(10) > 2
por lo tanto -> O(n^log_3(10))
