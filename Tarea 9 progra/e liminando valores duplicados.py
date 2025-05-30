entrada = input()
lista = entrada.split()

final=[]
for i in lista:
    if i not in final:
        final.append(i)
resultado = " ".join(final)
print(resultado)
