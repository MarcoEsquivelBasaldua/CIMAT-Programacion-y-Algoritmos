/*
*   Nombre del codigo: arbolTernario.c
*   Autor: Marco Antonio Esquivel Basaldua
*   Fecha: 28/09/2019
*
*   Descripcion:
*       Crea un monticulo ternario (arbol ternario completo)
*       El àrbol tiene un numero N màximo de nodos
*       Se despliega un menù para ingresar un valor, recuperar el màximo o terminar la ejecucion
*       Se realiza lo solicitado en el menù
*/
#include <stdlib.h>
#include <stdio.h>

void insert(int*,int);     // Ingresa un dato al àrbol
int removeMax(int*,int);  // Remueve dato de mayor tamanio del arbol
void swap(int*,int,int); // Intercambia datos de un arreglo
int maxof3(int*,int);   // Encuentra el indice del mayor valor de tres valores contiguos en el arreglo dado

int main(void){
    int N;
    printf("Ingresa el valor màximo de nodos en el àrbol\n");
    scanf("%d",&N);
    printf("\n");
    int *arbolArray = (int *)calloc((N+1),sizeof(int));

    // Menù para insertar un dato, remover el màximo o terminar la ejecucion
    int menu=0;
    while(menu != 3){
        printf("Presiona\n1 para ingresar un dato al arbol,\n2 para recuperar el valor maximo del arbol\n3 para salir del programa\n");
        scanf("%d",&menu);

        int dato;
        if(menu == 1){              // Ingresar un dato al àrbol
            if(arbolArray[0] != N){ // arbolArray[0] muestra la cantidad de datos en em àrbol, si es differente a N quiere decir que el àrbol tiene espacio disponible
                printf("Escribe dato a ingresar\n");
                scanf("%d",&dato);

                insert(arbolArray,dato);
                printf("\nActualizacion del àrbol\n");
                for(int i=0;i<N+1;i++) printf("%d ",arbolArray[i]);
                printf("\n\n");
            }
            else printf("ERROR: Arbol lleno\n");
        }
        else if(menu == 2){         // Remueve el valor màximo y se libera el ùltimo espacio en el arreglo del àrbol
            if(arbolArray[0] > 0){  // Blindaje por si se intenta extraer un dato de un arbol vacio
                int max = removeMax(arbolArray,N);
                printf("Valor màximo recuperado:\n%d\n\n",max);

                printf("\nActualizacion del àrbol\n");
                for(int i=0;i<N+1;i++) printf("%d ",arbolArray[i]);
                printf("\n\n");
            }
            else printf("ERROR: Arbol vacio\n");
        }
        else if(menu ==3);
        else printf("Opcion no vàlida\n\n");
    }

    printf("\nEstado final del àrbol\n");
    for(int i=0;i<N+1;i++) printf("%d ",arbolArray[i]);
    printf("\n\n");

    free(arbolArray);
    return 0;
}

void insert(int *arbolArray, int dato){
/*
*   Entradas:
*       - int *arbolArray: Arreglo con valores del àrbol
*       - int dato: Nuevo valor a ingresar al arbol
*
*   Salida:
*       - int *arbolArray: Arreglo con valores del àrbol con nuevo valor agregado y ordenado, se regresa por redefencia
*/
    int index = arbolArray[0]+1;    // Se aumenta en 1 el valor de arbolArray[0], este representa la cantidad de datos en el àrbol
    arbolArray[0] =index;

    arbolArray[index] = dato;       // Se agrega el dato el final del arreglo

    while(index != 1){
        int indexParent = (index+1)/3;      // Se recupera la posicion del padre del dato presente
        if(arbolArray[index] > arbolArray[indexParent]) swap(arbolArray, indexParent, index); // Se intercambian los valores si el dato presente es màs grande que su padre
        else break;
        index = indexParent;
    }
}

int removeMax(int* arbolArray,int N){
/*
*   Entradas:
*       - int* arbolArray: Arreglo con valores del àrbol
*       - int N: màximo nùmero de nodos en el àrbol
*
*   Salida:
*       - int* arbolArray: Arreglo con valores del àrbol sin valor màs grande y ordenado, se regresa por redefencia
*/
    int totalMax = arbolArray[1];    // El valor màs grande se encuentra en el indice [1] del arreglo arbolArray
    int lastIndex = arbolArray[0];   // Cantidad de valores insertados en el àrbol

    int index = 1;
    arbolArray[index] = arbolArray[lastIndex];  // La raiz toma el valor de la ùltima hoja

    // Se van ordenando los valores en al àrbol
    while(index < lastIndex-1){
        int oldestSon;
        int firstSon = index*3 - 1;
        if(firstSon > lastIndex) break;
        if(firstSon+1 > N){
            oldestSon = firstSon;
            break;
        }
        else if(firstSon+2 > N){
            if(arbolArray[firstSon+1] > arbolArray[firstSon]) oldestSon = firstSon +1;
            else oldestSon = firstSon;
        }
        else oldestSon = maxof3(arbolArray,firstSon);

        swap(arbolArray,index,oldestSon);

        index = oldestSon;
    }

    // Borra el ultimo elemento en el arbol y resta uno a la cantidad de elementos en él
    index = arbolArray[0];
    arbolArray[index] = 0;
    index--;
    if (index < 0) arbolArray[0]=0;
    else arbolArray[0]=index;

    return totalMax;
}

void swap(int* arr,int i, int j){
/*
*   Entradas:
*       - int* arr: arreglo con valores a intercambiar
*       - int i, int j: indices en arr cuyos valores seràn intercambiados
*
*   Salida:
*       - int* arr: arreglo con valores en i y j intercambiados, se pasa por redeferencia
*/
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

// Compara y regresa posicion del mas grande de tres valores contiguos en un arreglo
int maxof3(int *arr, int i){
/*
*   Entradas:
*       - int *arr: arreglo de valores
*       - int i: posicion del primer valor a comparar en el arreglo
*
*   Salida
*       - int : posicion del valor mas grande de entre los tres contiguos comparados
*/
    int index;
    if(arr[i+2] > arr[i] && arr[i+2] > arr[i+1]) index = i+2;
    else if(arr[i+1] > arr[i] && arr[i+1] > arr[i+2]) index = i+1;
    else index = i;

    return index;
}
