# Tarea 2 - Estructura Rope

## Integrantes
- Francisca Catalán
- Samuel Tabares

## Descripción
Este proyecto implementa la estructura de datos Rope utilizando árboles binarios para representar y manipular texto de manera eficiente.

La implementación permite realizar distintas operaciones sobre texto, manteniendo una complejidad eficiente en árboles balanceados.

## Funcionalidades Implementadas
- Inserción de caracteres
- Eliminación de caracteres
- Concatenación de líneas
- Inversión del texto
- Impresión del contenido

## Archivos del Proyecto
- `main.cpp` : menú principal e interacción con el usuario
- `Linea.h` : definición de la clase y estructuras
- `Linea.cpp` : implementación de métodos
- `MAKEFILE` : compilación automática
- `RESPUESTAS.md` : respuestas de preguntas teóricas

## Compilación

Para compilar el proyecto:

```bash
make
```

## Ejecución

Para ejecutar el programa:

```bash
./main
```

## Uso General
El programa permite ingresar un texto inicial y un valor `w`, correspondiente al tamaño máximo de caracteres por hoja.

Posteriormente se puede interactuar mediante un menú con las distintas operaciones disponibles.

## Consideraciones
La estructura Rope utiliza nodos internos con pesos, donde cada peso representa la cantidad de caracteres contenidos en el subárbol izquierdo.

Esto permite optimizar operaciones de inserción, eliminación y concatenación respecto a estructuras tradicionales de strings.
