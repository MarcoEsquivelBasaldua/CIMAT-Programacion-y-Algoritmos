/*
*   Nombre del codigo: red_black_tree.c
*   Autor: Marco Antonio Esquivel Basaldua
*   Fecha: 04/10/2019
*
*   Descripcion:
*       Crea un árbol rojo-negro a partir de datos ingresados en el programa.
*       Una vez creado el árbol, se muestran los resultados en el siguiente formato para cada nodo:
*           (llave) (color) (padre) (hijo izquierdo) (hijo derecho)
*
*       (llave): es el valor ingresado en el nodo correspondiente
*       (color): 'B' para negro, 'R' para rojo
*       (padre): llave del nodo del padre, si se tata de la raíz se muestra 'nan'
*       (hijo izquierdo): llave del nodo del hijo izquierdo, si no existe se muestra '-'
*       (hijo derecho): llave del nodo del hijo derecho, si no existe se muestra '-'
*
*       Dado el valor de la variable int n, se busca en el árbol generado y se muestra un mensaje
*       anunciando si se encontró el valor o no.
*
*       En esta implementación se presentan dos ejemplos de inserción y búsqueda de árboles rojo-negro
*
*       Para las funciones "leftRotate", "rightRotate", "insert" y "insertFixUp" se utilizó como base
*       el pseudocódigo de la siguiente liga: http://software.ucv.ro/~mburicea/lab8ASD.pdf al cual se le hicieron las
*       modificaciones necesarias para el correcto funcionamiento del algoritmo.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Estructura de un nodo
struct node{
    int data;
    char color;
    struct node *left, *right, *parent;
};

void leftRotate(struct node **, struct node *);         // Rotación izquierda
void rightRotate(struct node **, struct node *);       // Rotación derecha
void insert(struct node **, int);                     // Inserta datos en un árbol binario normal
void insertFixUp(struct node **, struct node *);     // Reconfigura la posición de los nodos para crear un árbol rojo-negro
void show(struct node *);                           // Muestra la información de los nodos una vez creado el árbol
int search(struct node *,int);                     // Busca un valor a partir de una raíz dada


int main(void){
    struct node *root = NULL;

    //////////////////////
    // Primer ejemplo de ejecución
    printf("Primer jemplo de insercion:\n");
    insert(&root,10);
    insert(&root,20);
    insert(&root,-10);
    insert(&root,15);
    insert(&root,17);
    insert(&root,40);
    insert(&root,50);
    insert(&root,60);

    show(root);
    printf("\n");

    int n = -10;
    printf("Se busca el número %d\n",n);
    int found = search(root,n);
    if(found) printf("%d se encuentra en el árbol\n",n);
    else printf("%d NO se encuentra en el árbol\n",n);
    printf("\n");

    n = 22;
    printf("Se busca el número %d\n",n);
    found = search(root,n);
    if(found) printf("%d se encuentra en el árbol\n",n);
    else printf("%d NO se encuentra en el árbol\n",n);
    printf("\n");


    /////////////////////////////////
    // Segundo ejemplo de ejecución
    root = NULL;

    printf("Segundo jemplo de insercion:\n");
    insert(&root,4);
    insert(&root,7);
    insert(&root,12);
    insert(&root,15);
    insert(&root,3);
    insert(&root,5);
    insert(&root,14);
    insert(&root,18);
    insert(&root,16);
    insert(&root,17);

    show(root);
    printf("\n");

    n = 13;
    printf("Se busca el número %d\n",n);
    found = search(root,n);
    if(found) printf("%d se encuentra en el árbol\n",n);
    else printf("%d NO se encuentra en el árbol\n",n);
    printf("\n");

    n = 18;
    printf("Se busca el número %d\n",n);
    found = search(root,n);
    if(found) printf("%d se encuentra en el árbol\n",n);
    else printf("%d NO se encuentra en el árbol\n",n);
    printf("\n");

    return 0;
}


void leftRotate(struct node **root, struct node *x){
/*
*   Entradas:
*       - struct node **root: puntero a la raíz del árbol
*       - struct node *x: nodo causante de la rotación
*/
    struct node *y = x->right;

    x->right = y->left;

    if (x->right != NULL) x->right->parent = x;

    y->parent = x->parent;

    if(x->parent == NULL) *root = y;
    else{
        if(x == x->parent->left) x->parent->left = y;

        else x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void rightRotate(struct node **root, struct node *x){
/*
*   Entradas:
*       - struct node **root: puntero a la raíz del árbol
*       - struct node *x: nodo causante de la rotación
*/
    struct node *y = x->left;

    x->left = y->right;

    if (x->right != NULL) x->right->parent = x;

    y->parent = x->parent;

    if(x->parent == NULL) *root = y;
    else{
        if(x == x->parent->right) x->parent->right = y;

        else x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

void insert(struct node **root, int data){
/*
*   Entradas:
*       - struct node **root: puntero a la raíz del árbol
*       - int data: dato a ingresar al árbol
*
*   Esta función crea un árbol binario no necesariamente balanceado.
*   La función insertFixUp(root,z) al final de la función
*   arregla el árbol para convertirlo a rojo-negro
*/
    struct node *z = (struct node*)malloc(sizeof(struct node));
    z->data = data;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;

    //if root es NULL z se convierte en la raíz
    if (*root == NULL){
        z->color = 'B';
        *root = z;
    }
    else{

        struct node *y = NULL;
        struct node *x = *root;

        while(x != NULL){
            y = x;

            if(z->data < x->data) x = x->left;
            else x = x->right;
        }

        z->parent = y;

        if(y == NULL) *root = z;
        else if(z->data < y->data) y->left = z;
        else y->right = z;

        z->color = 'R';
        insertFixUp(root,z);
    }
}

void insertFixUp(struct node **root, struct node *z){
/*
*   Entradas:
*       - struct node **root: puntero a la raíz del árbol
*       - struct node *z: estructura al nuevo nodo ingresado
*
*   root es la raíz de un árbol binario. Esta función convierte ese árbol
*   binario en un árbol rojo-negro
*/
    while (z != *root && z->parent->color == 'R'){
        struct node *y = NULL;

        if(z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
            if(y != NULL && y->color == 'R'){
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->right){
                z = z->parent;
                leftRotate(root,z);
                }

                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(root,z->parent->parent);
            }
        }
        else{
            y = z->parent->parent->left;
            if(y != NULL && y->color == 'R'){
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->left){
                z = z->parent;
                rightRotate(root,z);
                }

                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                leftRotate(root,z->parent->parent);
            }
        }
    }
    (*root)->color = 'B';
}

void show(struct node *root){
/*
*   Entradas:
*       struct node *root: raíz del árbol a mostrar
*/
    float parent;
    int right, left;
    if(root->parent == NULL) parent = NAN;
    else parent = root->parent->data;

    if(root->left == NULL && root->right == NULL){
        printf("%d %c %.0f %c %c\n",root->data,root->color,parent,'-','-');
    }
    else if(root->left == NULL){
        printf("%d %c %.0f %c %d\n",root->data,root->color,parent,'-',root->right->data);
        show(root->right);
    }
    else if(root->right == NULL){
        printf("%d %c %.0f %d %c\n",root->data,root->color,parent,root->left->data,'-');
        show(root->left);
    }
    else{
        printf("%d %c %.0f %d %d\n",root->data,root->color,parent,root->left->data,root->right->data);
        show(root->left);
        show(root->right);
    }

}

int search(struct node *root, int x){
/*
*   Entradas:
*       - struct node *root: raíz del árbol a mostrar
*       - int x: número a buscar en el árbol
*
*   Salidas:
*       - int : 1 si se locañizó x, 0 si no
*/
    int found = 0;

    if(root->data == x) found = 1;
    else if(root->left == NULL && root->right == NULL) found = 0;
    else if(root->left == NULL) found = search(root->right,x);
    else if(root->right == NULL) found = search(root->left,x);
    else{
        found = search(root->left,x);
        if(found == 0) found = search(root->right,x);
    }

    return found;
}
