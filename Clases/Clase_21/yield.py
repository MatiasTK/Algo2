# EXPLICACIONES FACTORIALES, RECURSION Y YIELD

def factorial(numero):
    if numero == 0:
        return 1
    return numero * factorial(numero-1)

def factoriales(posicion):
    lista = []
    for i in range(posicion):
        lista.append(i)(factorial(i))
    
    return lista

# Como optimizar el algoritmo de arriba

def factoriales_optimizado(posicion):
    factorial_calculado = 1
    lista = []
    for i in range(posicion):
        factorial_calculado *= (i if i != 0 else 1)
        lista.append(factorial_calculado)

    return lista

# Usando yield -> Mas optimizada todavia ya que no tiene que volver a calcular todos los factoriales

def factoriales_yield(posicion):
    factorial_calculado = 1
    for i in range(posicion):
        factorial_calculado *= (i if i != 0 else 1)
        yield factorial_calculado

