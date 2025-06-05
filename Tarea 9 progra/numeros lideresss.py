#Clase:numero 6  Fundamentos de programacion      
#Tema: bloques iterativos
#Ejercicio: numeros lideres
#Autor: Aracely Verenice Varela Barrera
#Fecha: 2025-06-5
#Estado:Terminado 
entradita= input("Ingrese una lista de números separados por comas: ")
posible=list(entradita.split(","))
listita=[int(x) for x in posible]
print(listita)
final=[]
for iterado in range(len(listita)-1):
    #print(f"{listita[iterado]}", end = " -->")
    numero_lider = True
    for posible in  range(iterado+1,len(listita)):
        #print(f"{listita[posible]}", end = ",")
        if listita[iterado] <= listita[posible]:
            numero_lider = False
            
    if numero_lider == True:
        final.append(listita[iterado])
            
    #print()
    
print (final)