# Implementacion de algoritmos BFS, DFS y DJIKSTRA
import math

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

#! DFS - Depth First Search -> Se usan para redes y esas cosas.

"""  
Recorre en profundidad el grafo, en forma de pila, luego de recorrer profundo recorre lo que le falta.
"""

# Recibimos un vertice inicial cualquiera, añadimos los vecinos a la pila si no estan en visitados
def DFS(grafo, vertice_inicial):
    visitados = []
    pila = []
    
    visitados.append(vertice_inicial)
    pila.append(vertice_inicial)

    while pila:
        vertice = pila.pop()
        for vecino in grafo.obtener_adyacentes(vertice):
            if vecino not in visitados:
                visitados.append(vecino)
                pila.append(vecino)

    return visitados

def DFS_Recursivo(grafo, vertice_inicial):
    visitados = []
    visitados.append(vertice_inicial)

    def dfs_rec(vertice):
        for vecino in grafo.obtener_adyacentes(vertice):
            if vecino not in visitados:
                visitados.append(vecino)
                dfs_rec(vecino)

    dfs_rec(vertice_inicial)

    return visitados

#! BFS - Breadth First Search -> Visita segun la distancia de los nodos.
""" 
Recorre en anchura el grafo, en forma de cola, luego de recorrer anchura recorre lo que le falta.
"""

def BFS(grafo,vertice_inicial):
    visitados = []
    cola = []
    cola.append(vertice_inicial)

    while cola:
        vertice = cola.pop(0)
        for vecino in grafo.obtener_adyacentes(vertice):
            if vecino not in visitados:
                visitados.append(vecino)
                cola.append(vecino)

    return visitados

#! Dijkstra
""" 
Algoritmo de Dijkstra para encontrar el camino mas corto entre dos nodos.
"""


def dijkstra(grafo,vertice_inicial):
    tabla = {}
    visitados = []

    for v in grafo.vertices():
        tabla[v] = {}
        tabla[v]['distancia'] = math.inf
        tabla[v]['anterior'] = None
    
    tabla[vertice_inicial]['distancia'] = 0

    def minimo_no_visitado(tabla):
        """ min(tabla,key=lambda v: tabla[v]['distancia'] if v not in visitados else math.inf) """
        # Recorre el diccionario tabla y le aplica la funcion de buscar el minimo a la tabla de v si v no esta en visitados.
        no_visitados = [v for v in grafo.vertices() if v not in visitados]

        menor = None
        distancia = math.inf

        for v in no_visitados:
            if tabla[v]['distancia'] < distancia:
                menor = v
                distancia = tabla[v]['distancia']
            
        return menor

    while v := minimo_no_visitado(tabla):
        visitados.append(v)
        distancia_actual = tabla[v]['distancia']

        for vecino in grafo.obtener_adyacentes(v):
            distancia_vecino = distancia_actual + grafo.obtener_distancia(v,vecino)
            if distancia_vecino < tabla[vecino]['distancia']:
                tabla[vecino]['distancia'] = distancia_vecino
                tabla[vecino]['anterior'] = v

    return tabla

#! Orden topologico 

def topo(grafo):
    grado = {v:0 for v in grafo.vertices()}
    incidencias = {v: [] for v in grafo.vertices()}

    for v in grafo.vertices():
        for vecino in grafo.obtener_adyacentes(v):
            incidencias[vecino].append(v)
            grado[vecino] += 1

    vertices_grado_cero = []

    for vertice in grado:
        if grado[vertice] == 0:
            vertices_grado_cero.append(vertice)
    
    print(vertices_grado_cero)

    for vertice_a_sacar in vertices_grado_cero:
        for incidencia in incidencias:
            if vertice_a_sacar in incidencias[incidencia]:
                incidencias[incidencia].remove(vertice_a_sacar)
                grado[incidencia] -= 1
    
    return vertices_grado_cero
