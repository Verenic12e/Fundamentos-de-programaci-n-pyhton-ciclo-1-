#Clase: Fundamentos de programacion      
#Tema: Bloques iterativos
#Ejercicio: Adivina el numero
#Autor: Aracely Verenice Varela Barrera
#Fecha: 2025-05-31
#Estado:Terminado 
import random


numero_aleatorio = random.randint(1, 100)
intentos = numero_aleatorio

while intentos:
    posible_numero = int(input("Ingrese un número entero entre 1 y 100: "))

    if posible_numero == numero_aleatorio:
        print("¡Felicidades! Has adivinado el número secreto.")
        break
    elif posible_numero < numero_aleatorio:
        print(f"El número secreto es mayor")
    else:
        print(f"El número secreto es menor")
print("Fin del juego")