# Respuestas Preguntas teoricas

---

### Pregunta 1: Complejidad de la Inserción
**Respuesta:** La complejidad para insertar un carácter en la estructura *Rope* es O(log N) en un árbol balanceado.
Esto ocurre porque para realizar la inserción primero se debe localizar la posición correspondiente dentro del texto, recorriendo el árbol desde la raíz hasta donde se encuentre el caracter, lo cual sera a lo mas una hoja. En un árbol balanceado, la altura máxima es proporcional a log N, por lo que la búsqueda toma tiempo logarítmico.
Posteriormente, la operación de división y actualización de nodos también mantiene un costo proporcional a la altura del árbol, conservando así la complejidad total O(log N)

---

### Pregunta 2: Complejidad de la Eliminación
**Respuesta:** La complejidad de eliminar es O(log N). 
Al igual que la inserción, la eliminación requiere primero encontrar la posición exacta del elemento dentro de la estructura, lo cual implica recorrer el árbol desde la raíz hasta una hoja. Como la altura del árbol balanceado es log N, la búsqueda tambien tiene costo logarítmico.

Luego, las operaciones de unión o reajuste de nodos después de la eliminación también dependen de la altura del árbol, manteniendo la complejidad total en O(log N).

---

### Pregunta 3: Impacto del valor w
**Respuesta:** El valor de w representa el tamaño máximo de texto almacenado en cada hoja del Rope, por lo que influye directamente tanto en el uso de memoria como en el rendimiento de las operaciones.

Si w es muy pequeño, existirán más nodos en el árbol, aumentando el consumo de memoria y la altura del árbol. Esto puede provocar más recorridos y mayor costo en las operaciones.
Si w es muy grande, habrá menos nodos y menor altura, pero las operaciones internas sobre cada hoja (como inserciones o divisiones de cadenas) serán más costosas, ya que cada bloque contendrá más caracteres.

Por lo tanto, elegir un valor adecuado para w implica buscar un equilibrio entre cantidad de nodos, uso de memoria y eficiencia de procesamiento.

---

### Pregunta 4: Inserciones a un solo lado (Árbol degenerado)
**Respuesta:** Si el árbol no se balancea y todas las inserciones se realizan constantemente en un mismo extremo, el árbol puede degenerarse en una estructura similar a una lista enlazada.
En este caso, la altura del árbol deja de ser logarítmica y pasa a ser proporcional a N. Como consecuencia, operaciones como búsqueda, inserción y eliminación dejan de ejecutarse en O(log N) y pasan a tener complejidad O(N).
Esto reduce considerablemente la eficiencia de la estructura, por lo que mantener el árbol balanceado es fundamental para asegurar un buen rendimiento.

**En ese caso no necesitamos usar fuentes, ya que las preguntas se respondian con los conocimientos adquiridos en las clases**

