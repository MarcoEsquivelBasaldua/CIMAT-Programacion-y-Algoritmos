/*
*   Nombre del codigo: PumasvsAmer.c
*   Autor: Marco Antonio Esquivel Basaldua
*   Fecha: 21/10/2019
*
*   Descripción del código:
*       A partir de un archivo de texto .txt que se lee como argumento de entrada se toman los valores en el siguiente orden:
*           n: cantidad de partidos que deben ganar los Pumas para ganar el campeonato
*           p: partidos ganados por los Pumas hasta el momento
*           a: partidos ganados por las Águilas hasta el momento
*       Se calcula la probabilidad de que los Pumas ganen el campeonato a partir de los datos anteriores y suponiendo que
*       en cada enfrentamiento cada equipo tiene la misma probabilidad de ganarlo (0.5)
*       El usuario puede modificar este archivo para probar con distintos de n,p y a.
*/
#include <stdio.h>
#include <stdlib.h>

double pumasWin(int,int,int);

int main(int argc, char* argv[]){
    // Se lee el archivo .txt con los valores n, p, a
    FILE* fin = NULL;

	fin = fopen(argv[1], "r");
	if(!fin) printf("ERROR: file not open %s\n", argv[1]);

    int n, p, a;
    fscanf(fin, "%d %d %d", &n,&p,&a);
    fclose(fin);

    if(a != p){
        double win = pumasWin(n,p,a);
        printf("\nHabiendo ganado %d partidos y su contrincante, las Águilas, %d\nla probabilidad de los Pumas para ganar el campeonato es de %lf\nlo que significa que será el primero en ganar %d partidos\n",p,a,win,n);
    }
    else
        printf("ERROR: a y p no pueden tener el mismo valor\n");
}

double pumasWin(int n, int p, int a){
    double table[n+1][n+1];

    // Llenar la diagonal con 0.5
    for(int i=0; i<n; i++){
        table[i][i] = 0.5;
        table[n][i] = 0;
        table[i][n] = 1;
    }

    for(int j=(n-1); j>=0; j--){
        for(int i=(j-1); i>=0; i--){

            table[i][j] = 0.5*table[i][j+1] + 0.5*table[i+1][j];
            table[j][i] = 1-table[i][j];
        }
    }

    table[n][n] = -1.0;

    printf("Tabla generada con programación dinámica. Las columnas hacen referencia a los partidos ganados por el Pumas, las filas a las Águilas.\n");
    printf("La intersección (i,j), es la probabilidad para los Pumas de ganar el campeonato dado que los pumas ya ganaron j partidos y las Águilas i partidos\n");
    printf("El tamaño de la tabla es n+1 donde n es el total de partidos que debe ganar alguno de los dos partidos paara ganar el campeonato.\n");
    for(int i=0; i<=n; i++){
        for(int j=0; j<=n; j++)
            printf("%lf ",table[i][j]);

        printf("\n");
    }

    return table[a][p];
}
