from typing import NewType


class Dog:
    def __init__(self,raza,color,nombre):
        self.raza = raza
        self.color = color
        self.nombre = nombre

    def color(self):
        return self.color
    
    def nombre(self):
        return self.nombre
    
    def raza(self):
        return self.raza
    
    def ladrar(self):
        print("Guau Guau")
    
    def rascar(self):
        print("Grrrrrrrrrrrrr")


MiPerro = Dog("Jack Russel","Marmol","Elsa")
MiPerro.ladrar()
MiPerro.rascar()

# Curiosidad: podes reemplazar el self por cualquier cosa, ejemplo: this.

class Cat:
    def __init__(this,raza,color,nombre):
        this.raza = raza
        this.color = color
        this.nombre = nombre
    
    def raza(this):
        return this.raza
    

MiGato = Cat("Siamés","negro","Michi")

print(MiGato.raza)
