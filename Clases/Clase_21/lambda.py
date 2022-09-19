def sumar_uno(n):
    n += 1

numero = 5
sumar_uno(numero)
print(numero) # NO SE VA A AUMENTAR EL VALOR DE NUMERO, ya que no se pasa por referencia COMO EN C

# Como solucionar esto

def imprimir_elementos_sumando(elemento,extra):
    extra[0] += elemento
    print(elemento)

extra = [0]

# Otra solucion

mi_funcion = lambda elemento, aux: print(elemento)
#A esto se le llama funcion anonima, no puede tener mas de una linea.

mi_funcion_2 = lambda elemento: print(elemento)

mi_funcion(1,2)
mi_funcion_2("Hola")

# Casos de uso

def imprimir_elementos(elementos,algo):
    print(elementos)

recorridos = lista.con_cada_elemento(imprimir_elementos, None)
recorridos = lista.con_cada_elemento8(lambda elemento,aux: print(elemento), None)