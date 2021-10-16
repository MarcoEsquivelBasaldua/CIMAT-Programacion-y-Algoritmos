Nombre del codigo: knapsack.c
Autor: Marco Antonio Esquivel Basaldua
Fecha: 16/10/2019

Descripcion del codigo:
       Da solucion al problema de knapsack tomando los valores a partir de un archivo de texto .txt
       En el archivo .txt se obtiene lo siguiente:
           Capacidad màxima de la mochila (V)
           Total de objetos disponibles (n)
           Dos columnas de n valores: la primera de ellas corresponde al volumen de cada objeto,
           la segunda al valor de cada objeto.
       En la carpeta compartida se incluyen cuatro ejemplos para este problema.

       A partir de la programacion dinàmica que utiliza una matriz de (n+1)(V+1) se aplica lo siguiente
       para llenar las casillas de la matriz:
           f(i,j)= |f(i-1,j)       si volumen(i) > j
                   |max(f(i-1,j),valores(i)+f(i-1,j-volumen(i)))

       Ya que la formula anterior solo hace uso de la fila i y la fila i-1,
       En esta aplicaion del problema se remplaza la matriz indicada por dos vectores
       de tamanio V+1 en los cuales se van guardando los valores de las filas i e i-1
       correspondientes a la matriz. Estos vectores llevan por nombre new_row[] y old_row[],
       old_row se inicializa con ceros y al final de cada iteracion de i se actualiza con los
       valores de new_row.
       Al hacer este cambio, se pasa de tener una complejidad O(nV) por una complejidad O(V),
       ya que se tienen dos vectores de tamanio V+1.



Instruccines de compilación:
    - Posicionarse en la carpeta que contiene el archivo knapsack.c, usar el compilador gcc:
        gcc knapsack.c
    - Para ejecutar:
        ./a.out (nombre del archivo .txt)
    - Resultados:
        Son mostrados por la ventana de la terminal
