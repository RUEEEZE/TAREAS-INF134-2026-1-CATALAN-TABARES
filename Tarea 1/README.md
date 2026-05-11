# Tarea1-Catalan-Tabares

## Integrantes
- Francisca Catalan
- Samuel Tabares

## Descripción
Este proyecto consiste en la implementación de un TDA (Tipo de Dato Abstracto) de Arreglo Extensible en C++.

El arreglo extensible permite almacenar elementos enteros y realizar operaciones como agregar, eliminar, modificar y acceder a elementos, ajustando dinámicamente su tamaño en memoria.

## Implementacion 
El arreglo extensible está implementado mediante una clase llamada ArregloExtensible, la cual utiliza:

- Un puntero dinámico B para almacenar los elementos
- Una variable n para la cantidad de elementos actuales
- Una variable capacidad que representa el tamaño del arreglo base

Además, se utiliza una función auxiliar:

siguiente_potencia(x): calcula la menor potencia de 2 mayor o igual a x, utilizada para definir el tamaño del arreglo base

## Funcionalidades 
El programa permite realizar las siguientes operaciones
- append(int v): agrega un elemento al final del arreglo
- remove(): elimina el último elemento
- getValue(unsigned long i): obtiene el valor en una posición
- setValue(unsigned long i, int v): modifica un valor
- size(): retorna la cantidad de elementos

## Lectura de archivo
El programa incluye una función leerArchivo que permite cargar datos desde un archivo de texto.

Formato del archivo:

- Un número entero por línea
- Termina con -1

Ejemplo:

10
20
30
-1

Los valores se agregan automáticamente al arreglo usando append.

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
Al ejecutar el programa, se solicita el nombre del archivo de entrada.
Luego se carga el contenido del archivo.
Se despliega un menú interactivo con las siguientes opciones:
1. Append
2. Remove
3. Get
4. Set
5. Size
6. Salir

El usuario puede interactuar con el arreglo mediante estas opciones.

## Acotacion 
El arreglo base utiliza tamaños en potencias de 2.

- Si el arreglo se llena, su capacidad se duplica
- Si el arreglo queda con pocos elementos, su capacidad se reduce a la mitad

Esto permite un uso más eficiente de la memoria.

## Consideraciones
- Se usa memoria dinámica (new/delete)
- Redimensionamiento en potencias de 2
- En caso de acceso inválido, el programa finaliza

## Esctructura tarea
main.cpp: implementación completa del programa
README.md: documentación del proyecto
Makefile: compilación y ejecución (opcional)