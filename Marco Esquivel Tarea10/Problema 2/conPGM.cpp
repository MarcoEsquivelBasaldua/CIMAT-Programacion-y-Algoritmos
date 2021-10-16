#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <algorithm>
#include <ctime>
using namespace std;

struct elemConex{
    int tam;
    int row, col;
};

void readPGM(char*, vector< vector<int> >&);
void writePGM(int,int, vector< vector<int> >&);
void writetxt(int, vector<elemConex>);
int BFS_search(int,int,int,int,vector< vector<int> >&);
void BFS_fill(int,int,int,int, vector< vector<int> >&);


bool comparator(const elemConex& lhs, const elemConex& rhs) {
   return lhs.tam < rhs.tam;
}


int main(int argc, char* argv[]){
    if (argc < 2){
        cerr << "no input file's name\n"<< endl;
    }

    clock_t inicio = clock();

    vector< vector<int> > array;    // Matriz con los pixeles de la imagen leida
    vector< elemConex > elem;       // Vector con las estructuras de los conjuntos conexos

    readPGM((char*)argv[1], array); // Se leen los pixeles de la imagen
    int rows = array.size();        // Numero de columnas en la imagen
    int cols = array[0].size();     // Numero de filas en la imagen

    int n = 0; // Cuenta los conjuntos de elementos conexos en la imagen
    int m;      //  Cuenta los elementos conexos por conjunto

    // Se recorre el array hasta encontrar un valor que sea mayor que cero
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            if(array[i][j] > 0){
                n++;
                elem.push_back(elemConex());

                m = BFS_search(i,j,rows,cols, array);

                elem[n-1].row = i;
                elem[n-1].col = j;
                elem[n-1].tam = m;
            }
        }
    }

    //priority_queue <elemConex> pq;          // En esta priority_queue se ordenan los elementos encontrados con respecto a su tamaño

    cout << "Cantidad de elementos en la imagen:" << n << endl;

    // Se ordenan los elementos
    sort(elem.begin(), elem.end(), &comparator);

    writetxt(n,elem);


    cout << "El elemento más chico tiene " << elem[0].tam << " componentes." << endl;
    cout << "El elemento más grande tiene " << elem[n-1].tam << " componentes." << endl;

    // Poner a blanco los pixeles de los elementos más grande y más chico
    BFS_fill(elem[0].row,elem[0].col,rows,cols, array);
    BFS_fill(elem[n-1].row,elem[n-1].col,rows,cols, array);

    // Recorrer la matriz y poner a cero todos los valores -2
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            if(array[i][j] == -2)
                array[i][j] = 0;
        }
    }

    // Se crea la imagen de salida
    writePGM(rows,cols,array);

    cout << endl << "Tiempo tomado en la ejecucion del algoritmo" << endl;
    clock_t fin = clock();
    cout << double(fin - inicio)/CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}



void readPGM(char* filename, vector< vector<int> >& array){
    string line;
    ifstream input;
    int rows, cols, scale;

    input.open(filename);
    if(input.is_open()){
        getline(input,line);
        input >> cols >> rows >> scale;
        //cout << cols << endl;
        //cout << rows << endl;

        array.resize(rows, vector<int>(cols));
        //array( rows , vector<int> (cols));
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++)
                input >> array[i][j];
        }
    }
    else
        cout << "ERROR: no se pudo abrir el archivo." << endl;
    input.close();
}

void writePGM(int rows,int cols, vector< vector<int> >& array){
    ofstream output;

    // Nombre del archivo
    output.open("im_salida.pgm");
    output << "P2" << endl;
    output << cols << " " << rows << endl;
    output << 255 << endl;

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            output << array[i][j] << endl;
        }
    }

    output.close();
}

void writetxt(int n, vector<elemConex> elem){
    ofstream output;

    // Nombre del archivo
    output.open("Elementos conexos.txt");

    output << "Cantidad de elementos en la imagen:" << n << endl;
    output << "Los componenetes conectados en cada uno de ellos son:" << endl;

    // Se muestran los elementos conectados y la cantidad de pixeles que los conforman
    for(int i=0; i<n; i++){
        output << "Elemento " << i+1 << " tiene " << elem[i].tam << " componentes." << endl;
    }

    output.close();
}

int BFS_search(int i, int j, int rows, int cols, vector< vector<int> >& array){
    int m = 1;      // Cantidad de elementos conectados
    queue <pair<int,int>> q;

    q.push(make_pair(i,j));

    // -1 significa que está eb la cola, -2 significa que fue visitado y contabilizado
    while(!q.empty()){
        array[i][j] = -2;
        if(i-1 >= 0 && j-1 >= 0){
            if(array[i-1][j-1] > 0){
                m++;
                q.push(make_pair(i-1,j-1));
                array[i-1][j-1] = -1;
            }
        }
        if(j-1 >= 0){
            if(array[i][j-1] > 0){
                m++;
                q.push(make_pair(i,j-1));
                array[i][j-1] = -1;
            }
        }
        if(i+1 < rows && j-1 >= 0){
            if(array[i+1][j-1] > 0){
                m++;
                q.push(make_pair(i+1,j-1));
                array[i+1][j-1] = -1;
            }
        }
        if(i-1 >= 0){
            if(array[i-1][j] > 0){
                m++;
                q.push(make_pair(i-1,j));
                array[i-1][j] = -1;
            }
        }
        if(i+1 < rows){
            if(array[i+1][j] > 0){
                m++;
                q.push(make_pair(i+1,j));
                array[i+1][j] = -1;
            }
        }
        if(i-1 >= 0 && j+1 < cols){
            if(array[i-1][j+1] > 0){
                m++;
                q.push(make_pair(i-1,j+1));
                array[i-1][j+1] = -1;
            }
        }
        if(j+1 < cols){
            if(array[i][j+1] > 0){
                m++;
                q.push(make_pair(i,j+1));
                array[i][j+1] = -1;
            }
        }
        if(i+1 < rows && j+1 < rows){
            if(array[i+1][j+1] > 0){
                m++;
                q.push(make_pair(i+1,j+1));
                array[i+1][j+1] = -1;
            }
        }

        i = q.front().first;
        j = q.front().second;
        q.pop();
    }

    array[i][j] = -2;


    return m;
}

void BFS_fill(int i, int j, int rows, int cols, vector< vector<int> >& array){
    queue <pair<int,int>> q;

    q.push(make_pair(i,j));

    // -1 significa que está en la cola, 255 significa que fue visitado y se convierte en un pixel blanco
    while(!q.empty()){
        array[i][j] = 255;
        if(i-1 >= 0 && j-1 >= 0){
            if(array[i-1][j-1] == -2){
                q.push(make_pair(i-1,j-1));
                array[i-1][j-1] = -1;
            }
        }
        if(j-1 >= 0){
            if(array[i][j-1] == -2){

                q.push(make_pair(i,j-1));
                array[i][j-1] = -1;
            }
        }
        if(i+1 < rows && j-1 >= 0){
            if(array[i+1][j-1] == -2){

                q.push(make_pair(i+1,j-1));
                array[i+1][j-1] = -1;
            }
        }
        if(i-1 >= 0){
            if(array[i-1][j] == -2){

                q.push(make_pair(i-1,j));
                array[i-1][j] = -1;
            }
        }
        if(i+1 < rows){
            if(array[i+1][j] == -2){

                q.push(make_pair(i+1,j));
                array[i+1][j] = -1;
            }
        }
        if(i-1 >= 0 && j+1 < cols){
            if(array[i-1][j+1] == -2){

                q.push(make_pair(i-1,j+1));
                array[i-1][j+1] = -1;
            }
        }
        if(j+1 < cols){
            if(array[i][j+1] == -2){

                q.push(make_pair(i,j+1));
                array[i][j+1] = -1;
            }
        }
        if(i+1 < rows && j+1 < rows){
            if(array[i+1][j+1] == -2){

                q.push(make_pair(i+1,j+1));
                array[i+1][j+1] = -1;
            }
        }

        i = q.front().first;
        j = q.front().second;
        q.pop();
    }
    array[i][j] = 255;

}
