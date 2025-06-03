#Clase: Fundamentos de programacion      
#Tema: Introducción al manejo de datos tabulares con NumPy
#Ejercicio: Cuestionario con NumPy
#Autor: Aracely Verenice Varela Barrera
#Fecha: 2025-06-2
#Estado:Terminado 

import numpy as np

consumo = np.array([
    [12.5, 13.2, 11.9, 14.0, 13.5, 15.0, 14.3],
    [10.1, 10.5, 10.0, 11.2, 11.5, 12.0, 11.8],
    [14.0, 14.2, 13.9, 15.5, 15.1, 16.0, 15.8],
    [9.0, 9.2, 8.9, 9.5, 9.8, 10.0, 9.7],
    [16.2, 16.5, 16.0, 17.1, 17.4, 18.0, 17.8],
    [11.0, 11.3, 11.1, 12.0, 12.4, 12.8, 12.5],
    [13.5, 13.8, 13.2, 14.1, 14.6, 15.0, 14.9],
    [10.8, 11.0, 10.6, 11.5, 11.8, 12.2, 12.0],
    [15.1, 15.5, 15.0, 16.0, 16.4, 17.0, 16.7],
    [8.5, 8.7, 8.4, 9.0, 9.2, 9.5, 9.3],
])

# Exploración inicial de los datos print( "Dimensiones:", , consumo.ndim)
print( "Dimensiones:", consumo.ndim)
print( "Forma:", consumo.shape)
print( "Tipo de datos:", consumo.dtype)
print( "Consumo primer hogar:",consumo [0])
print( "Consumo el miércoles (día 3):", consumo[-3:, -1])

# Promedio de consumo por hogar
promedio_por_hogar = np. mean(consumo, axis=1)
# Promedio de consumo diario de todos los hogares
promedio_por_dia = np. mean (consumo, axis=0)
# Suma total de consumo en la semana de los 10 hogares
total_consumo = np. sum (consumo)
print (promedio_por_hogar)
print( promedio_por_dia)
print(total_consumo )

# Máximo por hogar
maximos = np.max( consumo, axis=1)
# Mínimo por día
minimos = np.min (consumo, axis=0)
# Desviación estándar global
desviacion = np. std (consumo)
print(maximos)
print(minimos)
print(desviacion)
# Suma por hogar (semana)
consumo_total_hogar = np. sum (consumo, axis=1)
# Índice del hogar con mayor consumo
hogar_mayor_consumo = np. argmax( consumo_total_hogar)
# Indice del hogar con mejor consumo
hogar_mas_eficiente = np. argmin (consumo_total_hogar)
print (consumo_total_hogar)
print( hogar_mayor_consumo )
print (hogar_mas_eficiente)
# Suma por hogar (semana )
consumo_total_hogar = np. sum (consumo, axis=1)
print(f"Consumo total de cada hogar durante la semana: {consumo_total_hogar}")
# Compara cada hogar con un valor mayor a 100
altos = consumo_total_hogar > 100
# Filtrando hogares que cumplen la condición:
consumo_mayor_100 = np.where(altos) [0]
print(f"ids de hogares con consumo mayor a 100: {consumo_mayor_100}")
# Aplicando normalización MinMax al conjunto de datos
consumo_normalizado = (consumo - consumo.min()) / (consumo.max() - consumo.min( ))
# Resultado
print( consumo_normalizado)
#Cuestionario.
#1. ¿Cuál es el consumo del hogar 5 el viernes (día 5)?
# El consumo del hogar 5 el viernes es de 17.4 kWh
#2. Usando indexación, muestra el consumo de los últimos 3 hogares el domingo.
# El consumo de los últimos 3 hogares el domingo es de 12kWh(hogar 8), 16.7kWh(hogar 9),  9.3kWh(hogar 10)
#3. Calcula el promedio de consumo los fines de semana (sábado y domingo, columnas 5 y 6).
#El promedio de consumo los fines de semana (sábado y domingo, columnas 5 y 6) es de 13.615kWh
#4. ¿Qué día de la semana tiene la mayor desviación estándar entre hogares? Explica qué indica esto.
#sábado (índice 5) con una desviacion estandar de 2.744 kWh, es decir, algunos hogares consumen mucho más y otros mucho menos, a comparacion de otros dias de la semana.
#5. Identifica los 3 hogares con menor consumo total durante la semana. Muestra sus índices y valores.
#Fueron los hogares 10 (índice 9): 62.6 unidades, hogar 4 (índice 3): 66.1 unidades, y Hogar 2 (índice 1): 77.1 unidades
#6. Si el hogar 3 aumenta su consumo en un 10% cada día, ¿cuál sería su nuevo consumo total semanal?
#Si el hogar 3 consume un 10% más cada día, al final de la semana su consumo total sería de unos 114.95 kWh

