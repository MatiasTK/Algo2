import math

# Grafo de matriz de adyacencia
class Grafo:
    def __init__(self,n):
        self.matriz = [[math.inf for columna in range(n)] for fila in range(n)]

        """ for fila in range(n):
            nueva_columna = [None for columna in range(n)]
            self.matriz.append(nueva_columna) """

        """ for fila in range(n):
            nueva_columna = []
            for columna in range(n):
                nueva_columna.append(None)
            self.matriz.append(nueva_columna) """
    
    def insertar_arista(self,origen,destino,peso):
        self.matriz[origen][destino] = peso

    def insertar_arista_no_dirigida(self,origen,destino,peso):
        self.insertar_arista(origen,destino,peso)
        self.insertar_arista(destino,origen,peso)

    def borrar_arista(self,origen,destino):
        self.insertar_arista(origen,destino,math.inf)

    def obtener_distancia(self,origen,destino):
        return self.matriz[origen][destino]

    def obtener_adyacentes(self,origen):
        adyacentes = []
        for i in range(len(self.matriz)):
            if self.matriz[origen][i] != math.inf:
                adyacentes.append(i)
        return adyacentes

class Grafo_Alternativo:
    def __init__(self,vertices):
        self.vertices = vertices
        n = len(vertices)
        self.matriz = [[math.inf for columna in range(n)] for fila in range(n)]
    
    def insertar_arista(self,nombreOrigen,nombreDestino,peso):
        origen = self.vertices.index(nombreOrigen) # Index obtiene el indice de un elemento en una lista
        destino = self.vertices.index(nombreDestino)
        self.matriz[origen][destino] = peso
    
    def borrar_arista(self,nombreOrigen,nombreDestino):
        origen = self.vertices.index(nombreOrigen)
        destino = self.vertices.index(nombreDestino)
        self.matriz[origen][destino] = math.inf
    
    def obtener_distancia(self,nombreOrigen,nombreDestino):
        origen = self.vertices.index(nombreOrigen)
        destino = self.vertices.index(nombreDestino)
        return self.matriz[origen][destino]
    
    def obtener_adyacentes(self,nombreOrigen):
        origen = self.vertices.index(nombreOrigen)
        adyacentes = []
        for i in range(len(self.matriz)):
            if self.matriz[origen][i] != math.inf:
                adyacentes.append(self.vertices[i])
        return adyacentes

class Grafo_hash_de_hashes: # Agregar y sacar vertices es muy sencillo pero consume mas memoria. Es mas lento que una matriz de matriz.
    def __init__(self, nombresVertices):
        self.vertices = {}
        for nombre in nombresVertices:
            self.vertices[nombre] = {}
    
    def insertar_arista(self, nombreOrigen, nombreDestino, peso):
        self.vertices[nombreOrigen][nombreDestino] = peso

    def borrar_arista(self, nombreOrigen, nombreDestino):
        pass
    
    def obtener_distancia(self, nombreOrigen, nombreDestino):
        if nombreDestino in self.vertices[nombreOrigen]:
            return self.vertices[nombreOrigen][nombreDestino]
        else:
            return math.inf

    def obtener_adyacentes(self, nombreOrigen):
        pass 
    
    


    
