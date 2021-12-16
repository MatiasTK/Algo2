import simple_linked_list

lista = simple_linked_list.Lista()
lista.insertar(1)
lista.insertar(2)
lista.insertar(3)
lista.insertar(5)
lista.insertar(10)
    
def crear_acmulador():
    acumulado = 0

    def acumular(n):
        nonlocal acumulado
        acumulado += n

    def obtener():
        nonlocal acumulado
        return acumulado
    
    return [acumular,obtener]

[acumulador,obtener_valor] = crear_acmulador()

resultado = lista.con_cada_elemento(acumulador)

obtener_valor()
