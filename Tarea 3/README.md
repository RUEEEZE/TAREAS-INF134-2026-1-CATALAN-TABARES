# Tarea 3 - Construcción en cadena

## Integrantes
* Francisca Catalán
* Samuel Tabares

## Descripción
Este proyecto implementa la estructura de datos Grafo utilizando listas de adyacencia para representar y calcular de manera eficiente el orden óptimo de construcción de edificios con prerrequisitos. 
La implementación modela un Grafo Dirigido Acíclico (DAG) y permite realizar distintas operaciones de actualización sobre los tiempos y dependencias, manteniendo una complejidad eficiente en el recálculo mediante el Algoritmo de Kahn (Ordenamiento Topológico).

## Funcionalidades Implementadas
* Representación de grafos mediante listas de adyacencia manuales.
* Inserción y eliminación de dependencias (aristas).
* Actualización de tiempos de construcción de nodos.
* Detección de ciclos en la planificación.
* Cálculo de tiempos de inicio y tiempo total del proyecto.
* Algoritmo de ordenamiento estable (Merge Sort) personalizado.
* Cálculo de raíz cuadrada exacta mediante búsqueda binaria.

## Archivos del Proyecto
* `main.cpp` : Código principal que contiene las estructuras, clases, lógica del algoritmo y el bucle de interacción con las consultas.
* `README.md` : Documentación del proyecto.
* `MAKEFILE` : Archivo para la compilación y ejecución automática.
* `Repositorio.txt` : Archivo que contiene el enlace al repositorio privado de GitHub.

## Compilación
Para compilar el proyecto:

```bash
make

Ejecución

Para ejecutar el programa:
Bash

make run
