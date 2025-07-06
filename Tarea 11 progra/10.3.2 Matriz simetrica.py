#Clase: Fundamentos de programacion      
#Tema: Matriz
#Ejercicio:10.3.2 Matriz simeetrica
#Autor: Aracely Verenice Varela Barrera
#Fecha: 2025-07-05
#Estado:Terminado 
n=int(input())
l=[]
matriz_simetrica=True
for i in range(0, n):
    my_file=list(map(int,input().split(",")))
    l.append(my_file)
print(i)
for i in range(0,len(l)):
    for j in range(0,len(l)):
        print(f"recorriendo posicion({i}{j})")
        if i==j:
         continue
        if l[i][j]!=l[j][i]:
            matriz_simetrica=False
if matriz_simetrica:
    print("Simetrica")
else:
    print("No es simetrica({i}{j}, {j}{i})")