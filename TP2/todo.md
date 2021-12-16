## Pensamiento

Tengo que implementar un heap minimal para el simulador si o si ya que ahi tengo que meter a los pokemones y atenderlos segun su nivel. Pero se complica hacer el heap minimal para el hospital.c ya que este no se puede recorrer y en varias funciones te piden recorrer los entrenadores con sus pokemones.

**Como decidi plantearlo: Voy a utilizar una lista para el hospital.c, todavia no estoy seguro de si hacer una lista de entrenadores que a su vez cada entrenador posea una lista de pokemones o directamente hago una lista de pokemones donde se indique en el struct cual es su entrenador.
Añadi una nueva funcion a la lista la cual es lista_ordenar para utilizarla en funcion_a_cada_pokemon que me pide mandar a los pokemones en orden alfabetico**

---

### Esto es hasta ahora lo que entiendo que tengo que hacer

- [ ] Hacer adivinar nivel pokemon
- [ ] Hacer Agregar dificultad
- [ ] Agregar 2 dificultades en el main mediante el agregar dificultad
- [ ] Dificultades: facil -> el nivel que estas buscando es mayor/menor, Normal -> Frio/caliente, Dificil -> El nivel que estas buscando es un numero par/impar
