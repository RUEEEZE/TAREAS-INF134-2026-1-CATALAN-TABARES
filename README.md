# Tarea1-Catalan-Tabares

## Integrantes
- Francisca Catalan
- Samuel Tabares

## Descripción
Este proyecto consiste en la implementación de un TDA (Tipo de Dato Abstracto) de Arreglo Extensible en C++, sin el uso de la biblioteca STL.

El arreglo extensible permite almacenar elementos enteros y realizar operaciones como agregar, eliminar, modificar y acceder a elementos, ajustando dinámicamente su tamaño en memoria.

## Funcionalidades implementadas
- append(int v): agrega un elemento al final del arreglo
- remove(): elimina el último elemento
- getValue(unsigned long i): obtiene el valor en una posición
- setValue(unsigned long i, int v): modifica un valor
- size(): retorna la cantidad de elementos

## Compilación
Para compilar el programa se puede usar:

g++ main.cpp -o tarea1 -Wall

O utilizando Makefile:

make

## Ejecución
./tarea1

O con Makefile:

make run

## Uso del programa
1- Al iniciar, el programa solicita el nombre de un archivo de entrada.
2- El archivo debe contener números enteros, uno por línea, terminando con -1.

Ejemplo de archivo:

10
20
30
-1

3- Luego se despliega un menú con las operaciones disponibles:
-Append
-Remove
-Get
-Set
-Size

## Consideraciones
- Se usa memoria dinámica (new/delete)
- Redimensionamiento en potencias de 2
- En caso de acceso inválido, el programa finaliza con exit(1)SS