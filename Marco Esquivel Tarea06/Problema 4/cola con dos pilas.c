/*
*   Nombre del codigo: cola con dos pilas.c
*   Autor: Marco Antonio Esquivel Basaldua
*   Fecha: 29/09/2019
*
*   Descripcion:
*       Crea el comportamiento de una cola a partir de dos pilas
*       La cola tiene un numero N màximo de datos
*       Se despliega un menù para ingresar un valor, recuperar el primer dato en la cola o terminar la ejecucion
*       Se realiza lo solicitado en el menù
*/
#include <stdlib.h>
#include <stdio.h>

void insert(int*,int*,int);      // Inserta un dato en la cola
int removeFirst(int*,int*);     // Recupera el primer dato en la cola
void showPilas(int*,int*,int); // Muestra el contenido de pila1 y pila2

int main(void){
    int N;                                                    // Cantidad màxima de datos en la cola
    printf("Ingresa el valor màximo de nodos en la cola\n");
    scanf("%d",&N);
    printf("\n");
    int *pila1 = (int *)calloc((N+1),sizeof(int));
    int *pila2 = (int *)calloc((N+1),sizeof(int));

    // Menù para insertar un dato, remover el primer dato en la cola o terminar la ejecucion
    int menu = 0;
    while(menu != 3){
        printf("Presiona\n1 para ingresar un dato a la cola,\n2 para recuperar el primer dato en la cola\n3 para salir del programa\n");
        scanf("%d",&menu);

        int dato;
        if(menu == 1){              // Ingresar un dato a la cola
            if(pila1[0] < N){ // pila1[0] muestra la cantidad de datos en la cola, si es menor que N quiere decir que la cola tiene espacio disponible
                printf("Escribe dato a ingresar\n");
                scanf("%d",&dato);

                insert(pila1,pila2,dato);

                showPilas(pila1,pila2,N);
            }
            else printf("ERROR: Cola llena\n\n");
        }
        else if(menu == 2){         // Remueve el primer dao en la cola y se libera el ùltimo espacio en los arreglos de las pilas
            if(pila1[0] > 0){  // Blindaje por si se intenta extraer un dato de una cola vacia
                int first = removeFirst(pila1,pila2);
                printf("Primer dato en la cola:\n%d\n",first);

                showPilas(pila1,pila2,N);
            }
            else printf("ERROR: Cola vacia\n\n");
        }
        else if(menu ==3);
        else printf("Opcion no vàlida\n\n");
    }

    free(pila1);
    free(pila2);
    return 0;
}

void insert(int* pila1,int* pila2, int dato){
/*
*   Entradas:
*       - int* pila1: pila donde serà ingresado dato
*       - int* pila2: pila donde se vaciarà pila1
*       - int dato: dato a ingresar a pila1 y por tanto a la cola
*/
    int index = pila1[0] + 1;
    pila1[0] = index;
    pila2[0] = index;

    // Se ingresa dato en la posicion index
    pila1[index] = dato;

    // Se vacian los datos de pila1 en pila2
    int index2 = 1;
    for(int i=index; i>=1; i--){
        pila2[index2++] = pila1[i];
    }
}

int removeFirst(int* pila1,int* pila2){
/*
*   Entradas:
*       - int* pila1: pila donde se vaciaràn los datos de pila2
*       - int* pila2: pila de donde se obtendrà su ùltimo valor ingresado, equivalente a el primer elemento en la cola
*
*   Salidas:
*       - int : ùltimo valor en pila2, equivalente a el primer elemento en la cola
*/
    int index = pila2[0];
    int first = pila2[index];

    // Borrar dato en la posicion index de pila1 y pila2
    pila1[index] = 0;
    pila2[index] = 0;

    // Se actualiza index disminuyendo en uno
    index = index -1;

    // Actualizar la cantidad de datos en la cola el pila1[0] y pila2[0]
    pila1[0] = index;
    pila2[0] = index;

    // Se vacian los datos de pila2 en pila1
    int index2 = 1;
    for(int i=index; i>=1; i--){
        pila1[index2++] = pila2[i];
    }
    return first;
}

void showPilas(int *pila1, int *pila2, int N){

    printf("\nActualizacion de pila1\n");
    for(int i=0;i<N+1;i++) printf("%d ",pila1[i]);
    printf("\n");
    printf("\nActualizacion de pila2\n");
    for(int i=0;i<N+1;i++) printf("%d ",pila2[i]);
    printf("\n\n");

}
