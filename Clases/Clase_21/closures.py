contador = 0

def incrementar():
    global contador # Setear como variable global!
    contador += 1

print(contador)
incrementar()
print(contador)

