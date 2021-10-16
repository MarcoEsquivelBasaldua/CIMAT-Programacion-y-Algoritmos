/*
*   Nombre del codigo: kosaraju.c
*   Autor: Marco Antonio Esquivel Basaldua
*   Fecha: 12/10/2019

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 11 // Cantidad de vértices en la gràfica

int g[N][N], gt[N][N];  // Se declaran las matrices de adyacencia y su transpuesta
int visitados[N];       // Este arreglo ayuda a saber cuales nodos ya han sido marcados como visitados
int pila[N], pos;       // Pila en que se iràn guardando los vértices después de la primera ejecucion del DFS1

void DFS1(int);
void DFS2(int);

int main(void){
    // Se crea la matriz de adyacencia de acuerdo al ejemplo
    g[0][1] = 1;
    g[1][2] = 1;
    g[2][0] = 1;
    g[2][3] = 1;
    g[3][4] = 1;
    g[4][5] = 1;
    g[5][3] = 1;
    g[6][5] = 1;
    g[6][7] = 1;
    g[7][8] = 1;
    g[8][9] = 1;
    g[9][6] = 1;
    g[9][10] = 1;

    // Se crea la matriz traspuesta de adyacencia de acuerdo al ejemplo
    gt[1][0] = 1;
    gt[2][1] = 1;
    gt[0][2] = 1;
    gt[3][2] = 1;
    gt[4][3] = 1;
    gt[5][4] = 1;
    gt[3][5] = 1;
    gt[5][6] = 1;
    gt[7][6] = 1;
    gt[8][7] = 1;
    gt[9][8] = 1;
    gt[6][9] = 1;
    gt[10][9] = 1;



    printf("Matriz de adyacencia ingresada:\n");
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            printf("%d ",g[i][j]);
        }
        printf("\n");
    }

    // Se recorre la matriz de adyacencia con el DFS1
    for(int i=0; i<N; i++){
        if(!visitados[i]){
            DFS1(i);
        }
    }


    // Se recorre la matriz traspuesta en el orden en que fueron insertados los vértices
    for(int i=0; i<N; i++) visitados[i] = 0;    // Se reinicializa el arreglo visitados[] a cero
    int n_SCC = 0;                              // Nùmero de componenetes fuertemente ligados en la gràfica

    for(int i=pos-1; i>=0; i--){            // Se aplica el algoritmo DFS de acuerdo a los elementos en la pila
        if(!visitados[pila[i]]){            // Cuando se encuentra un elelemento que no se ha visitado se incrementa el contador de componenetes fuertemente ligados
            DFS2(pila[i]);
            n_SCC++;
        }
    }

    printf("\nCantidad de sub-gràficas fuertemente conectadas: %d\n",n_SCC);

    return 0;
}

void DFS1(int node){
    visitados[node] = 1;

    for(int i=0; i<N; i++){
        if(g[node][i] && !visitados[i])
            DFS1(i);
    }

    pila[pos++] = node;
}

void DFS2(int node){
    visitados[node] = 1;

    for(int i=0; i<N; i++){
        if(gt[node][i] && !visitados[i])
            DFS2(i);
    }
}
