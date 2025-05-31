#Clase: Fundamentos de programacion      
#Tema: Bloques iterativos
#Ejercicio: generando patrones
#Autor: Aracely Verenice Varela Barrera
#Fecha: 2025-05-31
#Estado:Terminado 

numero_estrellas = [1, 3, 5, 3, 1]
numero_fila = 0

while numero_fila < 5:
    columna = 0
    while columna < 5:
        total = numero_estrellas[numero_fila]
        espacio = (5 - total) // 2
        if columna < espacio or columna >= 5 - espacio:
            print(" ", end="")
        else:
            print("*", end="")
        columna += 1

    columna = 0
    while columna < 5:
        suma = numero_fila + columna
        if suma % 2 == 0:
            print("_", end="")
        else:
            print("-", end="")
        columna += 1

    columna = 0
    while columna < 5:
        total = numero_estrellas[numero_fila]
        espacio = (5 - total) // 2
        if columna < espacio or columna >= 5 - espacio:
            print(" ", end="")
        else:
            print("*", end="")
        columna += 1

    print()
    numero_fila += 1


numero_fila = 0
while numero_fila < 5:
    columna = 0
    while columna < 5:
        suma = numero_fila + columna + 1
        if suma % 2 == 0:
            print("_", end="")
        else:
            print("-", end="")
        columna += 1

    columna = 0
    while columna < 5:
        total = numero_estrellas[numero_fila]
        espacio = (5 - total) // 2
        if columna < espacio or columna >= 5 - espacio:
            print(" ", end="")
        else:
            print("*", end="")
        columna += 1

    columna = 0
    while columna < 5:
        suma = numero_fila + columna + 1
        if suma % 2 == 0:
            print("_", end="")
        else:
            print("-", end="")
        columna += 1

    print()
    numero_fila += 1

