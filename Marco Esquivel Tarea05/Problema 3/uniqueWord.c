/*
*   Nombre del programa: uniqueWord.c
*   Autor: Marco Antonio Esquivel Basaldua
*   Fecha: 16/09/2019
*
*   Descripcion del programa:
*       Lee, guarda y muestra ordenadas por terminal las primeras n (para cambiar este valor ir a la linea 26) palabras
*       del archivo de entrada. Solo muestra una palabra en caso de que esta se repita.
*       Cada palabra tiene un tamanio màximo de N (para cambiar este valor ir a la linea 17)
*       las palabras son guardadas como un arreglo bidimensional donde las "filas" corresponden a cada palabra leida
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20    // longitud maxima de cada palabra

void readWords(FILE*,int,char[][N+1]);          // Recupera las primeras n palabras del archivo de entrada
void sortWords(FILE*,int,char[][N+1]);         // Ordena las palabras leidas en la funcion readWords
int uniqueWord(FILE*,int,char[][N+1]);        // Elimina palabras que se repiten a partir de una estructura de palabras dada
char parse_char(char);                       // Transforma un caracter a minusculas y cualquier otra cosa que no sea letra lo pone como espacio

int main( int argc , char* argv[] ){

    int n = 10;     //numero de palabras a leer

    FILE* fin = NULL;
    // File with matrix A is read and displayed
	fin = fopen( argv[ 1 ] , "r" );
	if(  !fin  ){
		printf("Error: No se abrio %s\n" , argv[ 1 ] );
	}

    char palabras[n][N+1];       // En este array bidimensional estàtico se van a guardar las palabras leidas
                                    //las palabras se len por "filas"

    int m = uniqueWord(fin,n,palabras);


    printf("Palabras distintas leidas:\n%d\n",m);
    // Se imprimen en la terminal las palabras leidas
    for(int i=0;i<m;i++){
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

int uniqueWord(FILE* fin,int n, char palabras[][N+1]){
/*
*   Inputs:
*       - FILE* fin: Archivo de texto a leer
*       - int n: numero total de palabras a leer
*
*   Outputs:
*       - char palabras[][N+1]): arreglo con las palabras leidas y ordenadas,
*           solo se muestra una palabra en caso de que se repitan
*           las palabras se leen por "filas"
*/

    int m = 0;                  // Cuenta cuantas palabras diferente se leyeron
    sortWords(fin,n,palabras);  //Se pasa el archivo a leer y el arreglo donde se guardaràn las palabras ordenadas

    int rep=0;
    for(int i=0; i<n-rep; i++){

        int comp = strcmp(palabras[i],palabras[i+1]);       // Comparacion de una palabra con la siguiente

        if(comp == 0){

            for(int j=i; j<n-1; j++){
                char * s = strcpy(palabras[j],palabras[j+1]);//for(int k=0;k<=N;k++) palabras[j][k]=palabras[j+1][k];
            }
            rep++;
            i--;

        }
        else m++;
    }

    return m;
}

void sortWords(FILE* fin,int n, char palabras[][N+1]){
/*
*   Inputs:
*       - FILE* fin: Archivo de texto a leer
*       - int n: numero total de palabras a leer
*
*   Outputs:
*       - char palabras[][N+1]): arreglo con las palabras leidas y ordenadas, las palabras se leen por "filas"
*/

    readWords(fin,n,palabras);  //Se pasa el archivo a leer y el arreglo donde se guardaràn las palabras

    for(int i=0;i<n;i++){
        for(int j=0;j<n-1-i;j++){
            int comp = strcmp(palabras[j],palabras[j+1]);       // Comparacion de una palabra con la siguiente
            if(comp > 0){
                char temp[N+1];
                char * s = strcpy(temp,palabras[j]);//for(int k=0;k<=N;k++) temp[k] = palabras[j][k];
                s = strcpy(palabras[j],palabras[j+1]);//for(int k=0;k<=N;k++) palabras[j][k]=palabras[j+1][k];
                s = strcpy(palabras[j+1],temp);//for(int k=0;k<=N;k++) palabras[j+1][k]=temp[k];
            }
        }
    }

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
            if(j==N)
                palabras[i][j] = '\0';     // Si se alcanzo el màximo de caracteres por palabra se cierra con el null terminator '\0'

            fscanf(fin, "%c",&c);           // se lee un caracter del texto
            if(c == -61) fscanf(fin, "%c",&c);
            c = parse_char(c);              // esta funcion elimina caracteres que no sean letras y cambia todo a minusculas
            if(c == ' ' && j==0){           // si se lee un espacio y estamos comenzando el ciclo se trata de una coma, punto, signo de interrogacion...
                i--;                        // No se lee palabra y regresamos i para guardar la sigueinte palabra en la posicion actual
                break;
            }
            else if(c == ' '){              // se lee el fin de una palabra
                palabras[i][j] = '\0';     // se cambia el espacio por el null terminator
                break;
            }
            else
                palabras[i][j] = c;        // cada caracter leido se guarda en el array
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
