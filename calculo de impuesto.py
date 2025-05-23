#Clase: Fundamentos de programacion      
#Tema: bloque condicional
#Ejercicio: calculo de impuesto
#Autor: Aracely Verenice Varela Barrera
#Fecha: 2025-05-22
#Estado:Terminado 
units=int(input("ingrese sus unidades consumidas: "))
if 0 <= units <= 100:
    print("sin impuestos")
elif 101 <= units <= 200:
    print("impuesto $0.5 por cada unidad")
elif units >= 201:
    print("impuesto $0.7 por cada unidad")