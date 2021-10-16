/*
*   Autor: Marco Antonio Esquivel Basaldua
*   Fecha: 4/09/2019
*
*   Descripción del programa:
*       Este programa abre una de las dos imágenes en la carpeta, estas imagenes son: coins_P2.pgm y lena_P5.pgm
*       La diferencia entre ambas es que la primera está en formato P2 y la segunda en formato P5
*       El usuario tendrá la opción de elegir cual de las dos imagenes abrir ingresando por consola
*       el número 1 para la primer opción y 2 para la segunda.
*
*       La imagen leída es registrada en la estructura pgmI de tipo pgmStruct para después ser guardada en una imagen
*       de nombre im_salida.pgm que será una réplica de la imagen leída por el programa.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct pgmStruct{
    char format[3];                  // Se guardará el formato de la imagen, ya sea P2 o P5. se piden 3 bytes de memoria para poder guardar el caracter ´\0´
    char* comment;                  // En este arreglo se guardará el comentario en la imagen en caso de que exista
    int cols;                      // Esta variable indica el número de pixeles en forma horizontal en la imagen
    int rows;                     // Esta variable indica el número de pixeles en forma vertical en la imagen
    int scale;                   // Este es el valor para leer el color blanco en la imagen, por lo regular es 255
    unsigned char **matrix;     // Los valores o caracteres que forman la imagen serán guardados aquí
}pgmImage;

pgmImage leerImagen(int);           // Función para leer la imagen
void escribirImagen(pgmImage);     // Función para guardar la imagen nueva


int main(){

    pgmImage pgmI;         //Estructura donde guardar imagen leída

    // El usuario elige cual de las dos imágenes leer
    // En caso de ingresar un valor diferente de 1 ó 2 el programa muestra un mensaje de error y espera a recibir un valor válido
    int choice = 0;
    while(choice != 1 && choice != 2){
        printf("Ingresa 1 para abrir la imagen coins.pgm\nIngresa 2 para abrir la imagen lena.pgm\n");
        scanf("%d",&choice);

        if(choice == 1 || choice == 2) break;
        else printf("Eror: Opcion no disponible. Ingresa un valor válido\n\n");
    }


    pgmI = leerImagen(choice);      // Se lee y procesa la imagen leída
    escribirImagen(pgmI);           // Se crea una réplica de la imagen

    // Mensaje de fin de ejeccución
    printf("\nLa imágen fue generada\n");


    for(int i=0;i<pgmI.rows;i++) free(pgmI.matrix[i]);      // Se libera la memoria solicitada
    free(pgmI.matrix);
    free(pgmI.comment);

    return 0;
}

pgmImage leerImagen(int choice){
/*
*   Entradas:
*       - int choice: valor aue determina el usuario para trabajar con alguna de las dos imágenes
*
*   Salida
*       - pgmImage pgmI: estructura donde serán guardadas las características de la imagen leída
*/

    pgmImage pgmI;
    int i,j;        // Enteros usados en los ciclos for

    // Nombre de la imagen de acuerdo a lo especificado por la variable choice
    char *nombre;
    if(choice == 1) nombre = "coins_P2.pgm";
    else nombre = "lena_P5.pgm";

    // se abre la imagen para lectura
    FILE* file = NULL;
	file = fopen( nombre, "r" );
	if(  !file  ){
		printf("Error: No se abrio %s\n" , nombre );
	}

    fscanf(file, "%s\n", pgmI.format);      // En la primer línea se lee el formato de la imagen

    // Se toman acciones diferentes ya sea que se trate de un archivo P2 o P5
    if(pgmI.format[1] == '2'){              // Instrucciones para formato P2
        unsigned long memoryName=0;
        pgmI.comment = NULL;
        getline(&(pgmI.comment), &memoryName,file); //Guardar el nombre (comentario) del archivo

        if(pgmI.comment[0] == '#'){             // ´#´ Indica que se trata de un comentario entonces se lee la siguiente linea que tiene el numero de columnas y filas
            fscanf(file, "%d %d", &pgmI.cols, &pgmI.rows);
        }
        else{                                   // Si ´#´ no se lee quiere decir que la imagen no tiene comentario entonces se recupera el numero de columnas y filas de lo que se ha leido y guardado en pgmI.comment
            sscanf(pgmI.comment, "%d %d", &pgmI.cols, &pgmI.rows);    // Esto es en caso de que la imagen no tenga comentario
        }

        fscanf(file, "%d", &pgmI.scale);        // Este es el valor para leer el color blanco en la imagen, por lo regular es 255

        // Se solicita memoria para guardar la imagen
        pgmI.matrix = (unsigned char**)malloc(pgmI.rows * sizeof (*pgmI.matrix));
        if(pgmI.matrix == NULL) printf("No se puede guardar memoria para imagen\n");
        else{
            for (i=0; i<pgmI.rows; i++){
                pgmI.matrix[i] = (unsigned char*)malloc(pgmI.cols * sizeof (*pgmI.matrix[i]));
                if(pgmI.matrix[i] == NULL){
                    printf("No se puede guardar memoria para imagen\n");
                    break;
                }
            }
        }

        int num;                    // este num lee el valor de la imagen para después ser guardado en la matriz de imagen
        for(i=0;i<pgmI.rows;i++){
            for(j=0;j<pgmI.cols;j++){
                fscanf(file, "%d ", &num);
                pgmI.matrix[i][j] = (unsigned char)num;     // Cada pixel es leido como un valor numérico y guardado en la matriz de la estructura
            }
        }
    }
    else if(pgmI.format[1] == '5'){     // Instrucciones para formato P5
        unsigned long memoryName=0;
        pgmI.comment = NULL;
        getline(&(pgmI.comment), &memoryName,file); //Guardar el nombre (comentario) del archivo

        if(pgmI.comment[0] == '#'){         // ´#´ Indica que se trata de un comentario entonces se lee la siguiente linea que tiene el numero de columnas y filas
            fscanf(file, "%d %d", &pgmI.cols, &pgmI.rows);
        }
        else{                               // Si ´#´ no se lee quiere decir que la imagen no tiene comentario entonces se recupera el numero de columnas y filas de lo que se ha leido y guardado en pgmI.comment
            sscanf(pgmI.comment, "%d %d", &pgmI.cols, &pgmI.rows);    // Esto es en caso de que la imagen no tenga comentario
        }

        fscanf(file, "%d", &pgmI.scale);    // Este es el valor para leer el color blanco en la imagen, por lo regular es 255

        // Se solicita memoria para guardar la imagen
        pgmI.matrix = (unsigned char**)malloc(pgmI.rows * sizeof (*pgmI.matrix));
        if(pgmI.matrix == NULL) printf("No se puede guardar memoria para imagen\n");
        else{
            for (i=0; i<pgmI.rows; i++){
                pgmI.matrix[i] = (unsigned char*)malloc(pgmI.cols * sizeof (*pgmI.matrix[i]));
                if(pgmI.matrix[i] == NULL){
                    printf("No se puede guardar memoria para imagen\n");
                    break;
                }
            }
        }


        for(i=0;i<pgmI.rows;i++){
            for(j=0;j<pgmI.cols;j++){
                pgmI.matrix[i][j] = getc(file);   // Cada pixel es leido como un caracter y guardado en la matriz de la estructura
            }
        }
    }
    fclose( file );

    return pgmI;        // Se regresa la estructura con las caracteristicas de la imágen leída
}

void escribirImagen(pgmImage pgmI){
/*
*   Entradas:
*       - pgmImage pgmI: estructura con las caracteristicas de la imágen leída
*
*   Salidas:
*       - Ninguna
*/

    int i,j;        // Enteros usados en los ciclos for

    char *nombre = "im_salida.pgm";     // Nombre que se le dará a la imagen generada

    FILE* file = NULL;
	file = fopen( nombre, "w" );
	if(  !file  ){
		printf("Error: No se abrio %s\n" , nombre );
	}

    // Se toman acciones diferentes ya sea que se trate de un archivo P2 o P5
    if(pgmI.format[1] == '2'){          // Instrucciones para formato P2

        fprintf(file,"P2\n");                                                           // se conserva el formato
        fprintf(file,"# Imagen replicada por Marco Antonio Esquivel Basaldua\n");      // Comentario en la imagen generada
        fprintf(file,"%d %d\n",pgmI.cols,pgmI.rows);                                  // Tamaño de la imagen
        fprintf(file, "%d\n",pgmI.scale);                                            // Valor para leer el color blanco en la imagen

        // Guardan los valores en los pixeles de la imagen
        for(i=0;i<pgmI.rows;i++){
            for(j=0;j<pgmI.cols;j++){
                fprintf(file, "%d ", pgmI.matrix[i][j]);
            }
            fprintf(file,"\n");
        }
    }
    else if(pgmI.format[1] == '5'){         // Instrucciones para formato P5
        fprintf(file,"P5\n");                                                            // se conserva el formato
        fprintf(file,"# Imagen replicada por Marco Antonio Esquivel Basaldua\n");       // Comentario en la imagen generada
        fprintf(file,"%d %d\n",pgmI.cols,pgmI.rows);                                   // Tamaño de la imagen
        fprintf(file, "%d\n",pgmI.scale);                                             // Valor para leer el color blanco en la imagen

        // Guardan los valores en los pixeles de la imagen
        for(i=0;i<pgmI.rows;i++){
            for(j=0;j<pgmI.cols;j++){
                putc(pgmI.matrix[i][j],file);
            }
        }
    }
    fclose( file );

}
