#Clase: Fundamentos de programacion      
#Tema: Matriz
#Ejercicio:10.3 Matriz diagonal principal y secundaria
#Autor: Aracely Verenice Varela Barrera
#Fecha: 2025-07-05
#Estado:Terminado 
n=int(input())
l=[]
diagonal_secundario=[]
diagonal_principal=[]
for i in range(n):
    temp=list(map(int, input().split()))
    l.append(temp)

for i in range(len([l])):
    for j in range(len([i])):
        if i==j:
         diagonal_principal.append({l[i][j]})
    if i+j==len(l)-1:
        diagonal_secundario.append({l[i][j]})
        print(f"valoren la posicion({i}{j}):")
