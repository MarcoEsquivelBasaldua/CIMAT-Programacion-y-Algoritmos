/*
*   Nombre del codigo: red_black_tree.c
*   Autor: Marco Antonio Esquivel Basaldua
*   Fecha: 04/10/2019
*
*   Descripcion:
*       Crea un árbol rojo-negro a partir de datos ingresados en el programa.
*       Una vez creado el árbol, se muestran los resultados en el siguiente formato para cada nodo:
*           (llave) (color) (padre) (hijo izquierdo) (hijo derecho)
*
*       (llave): es el valor ingresado en el nodo correspondiente
*       (color): 'B' para negro, 'R' para rojo
*       (padre): llave del nodo del padre, si se tata de la raíz se muestra 'nan'
*       (hijo izquierdo): llave del nodo del hijo izquierdo, si no existe se muestra '-'
*       (hijo derecho): llave del nodo del hijo derecho, si no existe se muestra '-'
*
*       Dado el valor de la variable int n, se busca en el árbol generado y se muestra un mensaje
*       anunciando si se encontró el valor o no.
*
*       En esta implementación se presentan dos ejemplos de inserción y búsqueda de árboles rojo-negro
*
*       Para las funciones "leftRotate", "rightRotate", "insert" y "insertFixUp" se utilizó como base
*       el pseudocódigo de la siguiente liga: http://software.ucv.ro/~mburicea/lab8ASD.pdf al cual se le hicieron las
*       modificaciones necesarias para el correcto funcionamiento del algoritmo.
*/


/*
*   Instruccines de compilación:
*	- Posicionarse en la carpeta que contiene el archivo red_black_tree.c, usar el compilador gcc:
*		red_black_tree.c
*	- Para ejecutar:
*		./a.out
*	- Resultados:
*		Son mostrad0s por la ventana de la terminal
