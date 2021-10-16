/*
*   Nombre del codigo: knapsack.c
*   Autor: Marco Antonio Esquivel Basaldua
*   Fecha: 16/10/2019
*
*   Descripcion del codigo:
*       Da solucion al problema de knapsack tomando los valores a partir de un archivo de texto .txt
*       En el archivo .txt se obtiene lo siguiente:
*           Capacidad màxima de la mochila (V)
*           Total de objetos disponibles (n)
*           Dos columnas de n valores: la primera de ellas corresponde al volumen de cada objeto,
*           la segunda al valor de cada objeto.
*       En la carpeta compartida se incluyen cuatro ejemplos para este problema.
*
*       A partir de la programacion dinàmica que utiliza una matriz de (n+1)(V+1) se aplica lo siguiente
*       para llenar las casillas de la matriz:
*           f(i,j)= |f(i-1,j)       si volumen(i) > j
*                   |max(f(i-1,j),valores(i)+f(i-1,j-volumen(i)))
*
*       Ya que la formula anterior solo hace uso de la fila i y la fila i-1,
*       En esta aplicaion del problema se remplaza la matriz indicada por dos vectores
*       de tamanio V+1 en los cuales se van guardando los valores de las filas i e i-1
*       correspondientes a la matriz. Estos vectores llevan por nombre new_row[] y old_row[],
*       old_row se inicializa con ceros y al final de cada iteracion de i se actualiza con los
*       valores de new_row.
*       Al hacer este cambio, se pasa de tener una complejidad O(nV) por una complejidad O(V),
*       ya que se tienen dos vectores de tamanio V+1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int,int);                    // Encuentra el màximo entre dos valores
int knapsack(int,int *,int *,int);  // Solucion al problema knapsack

int main(int argc, char* argv[]){
    int V;                                          // Capacidad total de la mochila (en volumen)
    int n ;                                        // Total de objetos en la casa del presidente corrupto
    int *volumes = (int *)malloc(n*sizeof(int));  // Arreglo con el volumen de cada objeto
    int *values = (int *)malloc(n*sizeof(int));  // Arreglo con el valor de cada objeto

    // Archivo .txt con informacion sobre los objetos que se pueden guardar en la mochila
    FILE* fin = NULL;
	fin = fopen(argv[1], "r");
	if(!fin) printf("ERROR: file not open %s\n", argv[1]);

    fscanf(fin, "%d %d", &V, &n);       // Se lee la capacidad total de la mochila y el total de objetos en la casa

    for(int i=0; i<n; i++)              // Se leen los volumenes y los valores de cada objeto
        fscanf(fin, "%d %d", &volumes[i], &values[i]);
    fclose(fin);

    // Solucion al problema de knapsack
    int total = knapsack(V,volumes,values,n);
    printf("Maximo valor de los objetos en la mochila: %d\n",total);

    return 0;
}

int max(int a, int b){
/*
*   Entradas:
*       - int a: primer valor a comparar
*       - int b: segundo valor a comparar
*
*   Salidas:
*       - int: valor màximo entre a y b
*/
    if(a > b) return a;
    else return b;
}

int knapsack(int V,int *volumes,int *values,int n){
/*
*   Entradas:
*       - int V: Volumen màximo de la mochila
*       - int *volumes: Arreglo con el volumen de cada objeto
*       - int *values: Arreglo con el valor de cada objeto
*       - int n: Total de objetos en la casa del presidente corrupto
*
*   Salidas:
*       - int: Màximo valor en la mochila que no rebaza su capacidad
*/
    int new_row[V+1];
    int old_row[V+1];

    for(int i=0; i<=V; i++) old_row[i] = 0;     // Se inicializa el vector old_row con ceros

    new_row[0] = 0;                             // Se inicializa el primer valor de new_row con cero, este valor no cambiarà

    // Aplicacion del algoritmo de resolucion
    for(int i=0; i<n; i++){
        for(int j=1; j<=V; j++){
            if(volumes[i] <= j){
                new_row[j] = max(old_row[j],values[i]+old_row[j-volumes[i]]);
            }
            else new_row[j] = old_row[j];
        }
        memcpy(old_row,new_row,(V+1)*sizeof(int));      // old_row toma los valores de new_row, para la sigueinte iteracion
    }

    return new_row[V];      // Valor de màxima capacidad para la mochila
}
