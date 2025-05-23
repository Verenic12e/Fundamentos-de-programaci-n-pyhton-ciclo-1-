#Clase: Fundamentos de programacion      
#Tema: Variables, tipos, entradas y salidas
#Ejercicio: generador de correo key
#Autor: Aracely Verenice Varela Barrera
#Fecha: 2025-05-22
#Estado:Terminado 
nombre=str(input("ingrese su nombre completo: "))
nombre_completo=nombre.split()
primer_nombre=nombre_completo[0]
primer_apellido=nombre_completo[2]
terminal_de_correo="@keyinstitute.edu.sv"
print(f"Su correo es: {primer_nombre}.{primer_apellido}{terminal_de_correo}")