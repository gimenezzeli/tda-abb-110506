# TDA ABB

## Repositorio de Marlene Elizabeth Gimenez Gauto - 110506 - gimenezzeli@gmail.com

- Para compilar:

```bash
gcc src/*.c --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g -o abb
```

- Para ejecutar:

```bash
./abb
```

- Para ejecutar con valgrind:
```bash
make valgrind-chanutron
```
---
##  Funcionamiento
Funcion crear_nodo:
Crea un nodo a partir del dato que se le pasa como parametro y devuelve el puntero al nodo creado.

Funcion insertar_rec:
Inserta un elemento en el arbol binario creado, utilizando recursividad. Comparando el elemento con el elemento en el nodo, se fija si insertarlo a la izquierda o la de derecha.

Funcion buscar_predecesor:
Busca el predecesor, devolviendo el valor.

Funcion quitar_rec:
Quita un elemento del arbol binario de forma recursiva, dependiendo de si tiene o no hijos hago diferentes cosas; si tiene 0 o 1 hijo, creo un nuevo_hijo con raiz->izquierda pero si este es NULL nuevo_hijo pasa a ser raiz->derecha, libero el nodo y reduzco el tamaño del abb; pero si tiene dos hijos tengo que buscar el predecesor con la funcion buscar_predecesor en raiz->izquierda y hacer el intercambio.

Funcion buscar_rec:
Busca en el arbol el elemento pasado por parametro, con el comparador, va comparando si es el elemento correcto devuelve el elemento, si la comparacion da menor a 0 debe buscar por raiz->izquierda si da mayor a 0 tiene que buscar por raiz->derecha.

Funcion destruir_todo_rec:
Destruye todos los nodos de forma recursiva, si el destructor pasado por parametro es distinto de NULL, destruye tambien los elementos de los nodos.

Funcion abb_recorrer_preorden:
Recorre el arbol en preorden de forma recursiva. Primero guarda el elemento en el array pasado por parametro y despues recorre por raiz->izquierda y luego una vez finalizado recorre por raiz->derecha. Devolviendo la cantidad de elementos guardados en el array.

Funcion abb_recorrer_inorden:
Recorre el arbol en inorden de forma recursiva. Primero recorre por raiz->izquierda y despues guarda el elemento en el array pasado por parametro y luego una vez finalizado recorre por raiz->derecha. Devolviendo la cantidad de elementos guardados en el array.

Funcion abb_recorrer_postorden:
Recorre el arbol en postorden de forma recursiva. Primero recorre por raiz->izquierda y despues recorre por raiz->derecha y luego una vez finalizado guarda el elemento en el array pasado por parametro. Devolviendo la cantidad de elementos guardados en el array.

## Respuestas a las preguntas teóricas

Un "árbol" es una estructura de datos que organiza información jerárquicamente en forma de árbol, donde cada elemento se conecta a uno o más elementos secundarios, creando una estructura en forma de un árbol. Estos árboles son útiles para el almacenamiento de información, la búsqueda y la optimización. Hay varios tipos de árboles, como los siguientes:

ÁRBOL BINARIO: Un árbol binario es una estructura de datos en la que cada nodo tiene, como máximo, dos hijos: un hijo izquierdo y un hijo derecho. Los nodos en un árbol binario están organizados de manera que hay un nodo raíz que actúa como nodo principal, y desde este nodo raíz, se ramifican los nodos hijos, que a su vez pueden tener sus propios nodos hijos.

ÁRBOL BINARIO DE BÚSQUEDA: Un tipo especial de árbol binario en el que los valores en los nodos están organizados de manera que los valores más pequeños se encuentran a la izquierda y los valores más grandes a la derecha. Esto facilita la búsqueda eficiente de datos.


COMPLEJIDADES:
Búsqueda: En promedio O(log n) en un árbol equilibrado, pero puede ser O(n) en un árbol desequilibrado.
Inserción: En promedio O(log n) en un árbol equilibrado, pero puede ser O(n) en un árbol desequilibrado.
Eliminación: En promedio O(log n) en un árbol equilibrado, pero puede ser O(n) en un árbol desequilibrado.
Recorrido (inorden, preorden, postorden): O(n) en el peor caso.
