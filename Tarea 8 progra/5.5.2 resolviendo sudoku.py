#Clase: Fundamentos de programacion      
#Tema: Bloques iterativos
#Ejercicio: Resolviendo suduko
#Autor: Aracely Verenice Varela Barrera
#Fecha: 2025-05-31
#Estado:Terminado 
sudoku = []

for numero_fila in range(9):
    while True:
        entrada = input()
        fila = entrada.split()


        if len(fila) != 9:
            print("¡Solo deben ser 9 números!")
            continue

        fila_correcta = True
        for numero in fila:
            if not numero.isdigit() or int(numero) < 1 or int(numero) > 9:
                fila_correcta = False
                break

        if not fila_correcta:
            print("Solo se pueden usar números del 1 al 9.")
            continue

      
        fila_como_numeros = [int(numero) for numero in fila]
        sudoku.append(fila_como_numeros)
        break


for una_fila in sudoku:
    usados = [0] * 10  
    for numero in una_fila:
        if usados[numero] == 1:
            print("Inválido")
            exit()
        usados[numero] = 1

for numero_columna in range(9):
    usados = [0] * 10
    for numero_fila in range(9):
        numero = sudoku[numero_fila][numero_columna]
        if usados[numero] == 1:
            print("Inválido")
            exit()
        usados[numero] = 1


for fila_inicio in [0, 3, 6]:
    for columna_inicio in [0, 3, 6]:
        usados = [0] * 10
        for fila_extra in range(3):
            for columna_extra in range(3):
                numero = sudoku[fila_inicio + fila_extra][columna_inicio + columna_extra]
                if usados[numero] == 1:
                    print("Inválido")
                    exit()
                usados[numero] = 1

print("Válido")
