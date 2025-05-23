#Clase: Fundamentos de programacion      
#Tema: Bloque condicional
#Ejercicio: Division con presision
#Autor: Aracely Verenice Varela Barrera
#Fecha: 2025-05-22
#Estado: Terminado 
contraseñita = input("ingrese la posible contraseña: ")
numero = False      
mayuscula = False   


for caracter in contraseñita:
    if caracter.isdigit():  
        numero = True 
    if caracter.isupper(): 
        mayuscula = True 
    


if len(contraseñita) >= 8 and numero and mayuscula:
    print("Contraseña segura")
else:
    print("Contraseña no segura")