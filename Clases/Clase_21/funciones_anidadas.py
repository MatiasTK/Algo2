def crear_funcion():
    def funcion_aux(n):
        return n*2
    
    return funcion_aux

# La unica manera de acceder a funcion auxiliar es por crear funcion

mi_funcion = crear_funcion()
print(mi_funcion(2))

# Para que me sirve

contador = 0

def incrementar():
    global contador
    contador += 1

def crear_incrementador(n):

    """  def incrementar(): COMO n no forma parte de incrementar tira error
        n += 1
        return n
    """

    # Solucion
    def incrementar():
        nonlocal n
        n += 1
        return n
    
    def obtener():
        return n

    return [obtener,incrementar]


[obt1,inc1] = crear_incrementador(10)

print(obt1())
print(inc1())