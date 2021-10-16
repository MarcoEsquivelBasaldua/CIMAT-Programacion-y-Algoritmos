/*
*   Nombre del codigo: palindrome.c
*   Autor: Marco Antonio Esquivel Basaldua
*   Fecha: 18/10/2019
*
*   Descripcion del codigo:
*       Este programa toma como entrada una secuencia de caracteres dentro de un archivo de texto .txt
*       que se lee como argumento de entrada del programa. El primer dato de se lee de este archivo es
*       un entero que indica el nùmero de caracteres que seràn leidos dentro del archivo.
*       Al tener la cadena de caracteres como entrada se calcula el tamaño de la mayor secuencia
*       palindromica dentro de la cadena de caracteres.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int,int);                    // Encuentra el màximo entre dos valores
int maxPalindrome(char*,int);

int main(int argc, char* argv[]){
    // Se lee el archivo .txt con la secuencuencia de caracteres
    FILE* fin = NULL;

	fin = fopen(argv[1], "r");
	if(!fin) printf("ERROR: file not open %s\n", argv[1]);

    int n;                  // total de caracteres en la secuencia
    fscanf(fin, "%d", &n);

    char seq[n+1];
    //char *seq = malloc(n * sizeof(char));
    printf("Caracteres leidos:\n");
    fscanf(fin, "%c", &seq[0]); // Se lee y se desecha el salto de linea
    for(int i=0; i<n; i++){
        fscanf(fin, "%c", &seq[i]);
        printf("%c",seq[i]);
    }
    printf("\n");
    fclose(fin);

    int max = maxPalindrome(seq,n);

    printf("\nLa subsecuencia palindromica mas grande tiene %d cracteres\n",max);

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

int maxPalindrome(char *seq, int n){
    // Se crea una matriz para la programación dinámica
    int DP[n][n];
    for(int i=0; i<n; i++) DP[i][i] = 1;

    int p = n-1;
    for(int m=1; m<n; m++){
        int i=0, j=m;

        for(int q=0; q<(n-m); q++){
            if(m == 1){
                if(seq[j] == seq[i]) DP[i][j] = 2;
                else DP[i][j] = 1;
            }
            else{
                if(seq[j] != seq[i]) DP[i][j] = max(DP[i][j-1],DP[i+1][j]);
                else DP[i][j] = DP[i+1][j-1] + 2;
            }

            i++;
            j++;
        }
    }

    /*for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            printf("%d ",DP[i][j]);
        printf("\n");
    }*/

    return DP[0][n-1];
}
