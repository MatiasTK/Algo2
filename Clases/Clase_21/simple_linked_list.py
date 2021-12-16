# Uso en vez de struct clases ya que no existe struct en python

class Nodo:
    def __init__(self, elemento):
        self.elemento = elemento
        self.siguiente = None
    
class Lista:
    def __init__(self):
        self.primero = None
        self.tamaño = 0

    def insertar(self, elemento):
        if self.primero == None:
            self.primero = Nodo(elemento)
        else:
            actual = self.primero
            while(actual.siguiente):
                actual = actual.siguiente
            actual.siguiente = Nodo(elemento)
        self.tamaño += 1

    def __obtener_nodo(self,posicion): # Tiene dos __ al principio ya que es una funcion privada -> No se puede acceder
        if posicion > self.tamaño:
            return self.tamaño-1
        actual = self.primero
        while posicion > 0:
            actual = actual.siguiente
            posicion -= 1
        
        return actual

    def obtener(self, posicion):
        return self.__obtener_nodo(posicion).elemento

    def con_cada_elemento(self,funcion):
        contador = 0
        actual = self.primero
        while actual:
            if funcion(actual.elemento):
                return contador
            actual = actual.siguiente
        return contador
    
    def __iter__(self): # Para indicar como puede iterrar sobre la lista a python -> Iterador interno
        actual = self.primero
        while actual:
            yield actual.elemento # Interrumpe la ejecuccion de la funcion, es como un return pero permite retomar la ejecuccion desde donde estabas. Guarda el estado de la funcion.
            actual = actual.siguiente
    
    def __getitem__(self, posicion): # Es para hacer Lista[0] y que te devuelva algo
        return self.obtener(posicion)

    def __setitem__(self, posicion, valor): # Es para hacer Lista[0] = "Hola" y que lo sobreescriba/inserte en esa posicion
        self.__obtener_nodo(posicion).elemento = valor
   
# Main

MiLista = Lista()
MiLista.insertar(1)
MiLista.insertar(2)
MiLista.insertar(3)
MiLista.insertar(4)
MiLista.insertar(10)


print("Obtengo el elemento en la segunda posicion ->",MiLista.obtener(2))

print("Itero de manera interna la lista")
for item in MiLista:
    print(item)

print("Obtengo un numero de la lista haciendo lista[3] ->",MiLista[3])
print("Sobreescribo el valor en la pos 3")
MiLista[3] = "Hola"
print("Obtengo el valor en la pos 3 ->",MiLista[3])


    
