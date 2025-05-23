#Clase: Fundamentos de programacion      
#Tema: bloque condicional
#Ejercicio: año bisiesto
#Autor: Aracely Verenice Varela Barrera
#Fecha: 2025-05-22
#Estado:Terminado 
numero=int(input("ingrese el año: "))
if numero%4==0:
    print("año bisiesto")
elif numero%100==0 and numero%400==0:
    print("Es año bisiesto")
else:
    print("no es año bisiesto") 