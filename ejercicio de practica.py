#Clase: Fundamentos de programacion      
#Tema: Variables, tipos, entradas y salidas
#Ejercicio: Automatizando el cálculo de la propina
#Autor: Aracely Verenice Varela Barrera
#Fecha: 2025-05-22
#Estado:Terminado 
total_gastado=int(input("ingrese la cantidad gastada: "))
porcentaje_de_propina=int(input("ingrese la cantidad de la propina por ejemplo: 10, 15, 20: "))
cantidad_total_a_pagar_de_propina=total_gastado*(porcentaje_de_propina/100)
pago_total=total_gastado+cantidad_total_a_pagar_de_propina
print(f"La cuenta es: ${total_gastado}")
print(f"La propina es:  ${cantidad_total_a_pagar_de_propina}")
print(f"Total de la cuenta con propina({porcentaje_de_propina}%): ${pago_total}")