#Clase: Fundamentos de programacion      
#Tema: bloques iterativos
#Ejercicio: sumadores de valores posicionales
#Autor: Aracely Verenice Varela Barrera
#Fecha: 2025-05-31
#Estado:Terminado 


while True:
    numeros = input("Ingrese números enteros, ejemplo: 7324: ")

    final = []
    for suma in numeros:
        final.append(int(suma))

    partes = []
    for numero in final:
        partes.append(str(numero))

    paso = " + ".join(partes)
    sumas = sum(final)
    print(f"{paso} = {sumas}")

    while sumas >= 10:
        final = []
        for sumaita in str(sumas):
            final.append(int(sumaita))

        partes = []
        for numero in final:
            partes.append(str(numero))

        paso = " + ".join(partes)
        sumas = sum(final)
        print(f"{paso} = {sumas}")

    if sumas > 1:
        break

print("Resultado final:", sumas)
