#Clase: Fundamentos de programacion      
#Tema: Matriz
#Ejercicio:10.3.3 Numeros vecinos
#Autor: Aracely Verenice Varela Barrera
#Fecha: 2025-07-05
#Estado:Terminado 
matriz = []
for i in range(3):
    fila = input()
    numeros = list(map(int, fila.strip().split(",")))
    matriz.append(numeros)

valor_centro = matriz[1][1]

contador = 0
for i in range(3):
    for j in range(3):
        if i == 1 and j == 1:
            continue 
        if matriz[i][j] == valor_centro:
            contador += 1
print("Cantidad de vecinos iguales al centro:", contador)
