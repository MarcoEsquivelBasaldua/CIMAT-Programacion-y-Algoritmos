/*
*   Nombre del programa: readWords.c
*   Autor: Marco Antonio Esquivel Basaldua
*   Fecha: 16/09/2019
*
*   Descripcion del programa:
*       Lee, guarda y muestra por terminal las primeras n (para cambiar este valor ir a la linea 24) palabras
*       del archivo de entrada.
*       Cada palabra tiene un tamanio màximo de N (para cambiar este valor ir a la linea 17)
*       las palabras son guardadas como un arreglo bidimensional donde las "filas" corresponden a cada palabra leida
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20    // longitud maxima de cada palabra

void readWords(FILE*,int,char[][N+1]);  // Recupera las primeras n palabras del archivo de entrada
char parse_char(char);                 // Transforma un caracter a minusculas y cualquier otra cosa que no sea letra lo pone como espacio

int main( int argc , char* argv[] ){

    int n = 15;     //numero de palabras a leer

    FILE* fin = NULL;
    // File with matrix A is read and displayed
	fin = fopen( argv[ 1 ] , "r" );
	if(  !fin  ){
		printf("Error: No se abrio %s\n" , argv[ 1 ] );
	}

    char palabras[n][N+1];       // En este array bidimensional estàtico se van a guardar las palabras leidas
                                    //las palabras se len por "filas"

    readWords(fin,n,palabras);

    // Se imprimen en la terminal las palabras leídas
    for(int i=0;i<n;i++){
        //int pos = (N+1)*i;
        for(int j=0; j<=N; j++){
            if(palabras[i][j] ==  '\0'){
                printf("\n");
                break;
            }
            else printf("%c",palabras[i][j]);
        }
    }

	fclose( fin );
}

void readWords(FILE* fin, int n,char palabras[][N+1]){
/*
*   Inputs:
*       - FILE* fin: Archivo de texto a leer
*       - int n: numero total de palabras a leer
*
*   Outputs:
*       - char palabras[][N+1]): arreglo con las palabras leidas, las palabras se leen por "filas"
*/
    char c;                     // cada caracter leido sera guardado aqui

    for(int i=0;i<n;i++){       // Este ciclo contarà todas las palabras que se desean leer

        //int pos = (N+1)*i;      // Esta variable ayudarà a colocar cada palabra en su respectiva posicion en el array

        for(int j=0; j<=N; j++){    // Ciclo que recorre los caracteres en el texto de acuerdo al valor de N
            if(j==N) palabras[i][j] = '\0';     // Si se alcanzo el màximo de caracteres por palabra se cierra con el null terminator '\0'

            fscanf(fin, "%c",&c);           // se lee un caracter del texto
            if(c == -61) fscanf(fin, "%c",&c);
            c = parse_char(c);              // esta funcion elimina caracteres que no sean letras y cambia todo a minusculas
            if(c == ' ' && j == 0){           // si se lee un espacio y estamos comenzando el ciclo se trata de una coma, punto, signo de interrogacion...
                i--;                        // No se lee palabra y regresamos i para guardar la sigueinte palabra en la posicion actual
                break;
            }
            else if(c == ' '){              // se lee el fin de una palabra
                palabras[i][j] = '\0';     // se cambia el espacio por el null terminator
                break;
            }
            else  palabras[i][j] = c;        // cada caracter leido se guarda en el array
        }
    }
}



//    Transform a character to lowercase, remove tildes, and transform non alphabetic characters to spaces
char parse_char(char c) {
    // Upercase to lowercase
    if (65 <= c && c <= 90) {
        return c + 32;
    }
    // lowercase
    if (97 <= c && c <= 122) {
        return c;
    }
    // Á or á to a
    if (c == -127 || c == -95) {
        return 'a';
    }
    // É or é to e
    if (c == -119 || c == -87) {
        return 'e';
    }
    // Í or í to i
    if (c == -115 || c == -83) {
        return 'i';
    }
    // Ó or ó to o
    if (c == -109 || c == -77) {
        return 'o';
    }
    // Ú or ú to u
    if (c == -102 || c == -70) {
        return 'u';
    }
    // Ü or ü to u
    if (c == -100 || c == -68) {
        return 'u';
    }

    return ' ';
}
