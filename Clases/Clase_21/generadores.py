def primeros_cuadrados(n):
    lista = []
    for i in range(n):
        lista.append(i*i)
    return lista

# Otra forma

lista = [i*i for i in range(10)] # Arma una lista ya que esta entre []

print(lista)

generador = (i*i for i in range(10))
# Devuelve un generador.
# Un generador no guarda todos en memoria sino que te los va dando a medida que los necesitas
print(next(generador))
print(next(generador))
print(next(generador))