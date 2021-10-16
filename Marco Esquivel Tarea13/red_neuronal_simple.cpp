#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

void readData(char* filename, vector< vector<double> >& array);   // Funcion para leer los datos del archivo data.dat

class sigmoidNeuron{
    private:
        vector<double> x;
        vector<double> w;
        double bias, output;

    public:
        sigmoidNeuron(vector<double>,vector<double>);
        double get_output();

};

sigmoidNeuron::sigmoidNeuron(vector<double> _x,vector<double> _w){
    x = _x;
    w = _w;

    // El valor de bias es el ùltimo elemento del vector de pesos
    bias = w[w.size()-1];
    //cout << bias << endl;

    // Se obtiene el valor de la salida de la neurona
    double dotprod = 0;
    for(int i=0; i<x.size(); i++)
        dotprod += x[i]*w[i];

    output = 1/(1+exp(-(dotprod+bias)));
    //cout << output << endl;
}

double sigmoidNeuron::get_output(){
    return output;
}

//////////////////////////////////////////////////////////////////////
class Layer{
    private:
        int numNeurons;
        vector<sigmoidNeuron> _Layer;
        vector<double> x;
        vector<vector<double> > w;
        vector<double> outputs;

    public:
        Layer(int, vector<double>, vector<vector<double> >);
        vector<double> get_outputs();

};

Layer::Layer(int _numNeurons, vector<double> _x, vector<vector<double> > _w){
    numNeurons = _numNeurons;
    x = _x;
    w = _w;

    // Se llena la capa con las neuronas solicitadas
    for(int i=0; i<numNeurons; i++){
        sigmoidNeuron n1(x,w[i]);
        // El valor de salida de la neurona actual se guarda en el vector outputs
        outputs.push_back(n1.get_output());

        _Layer.push_back(n1);
    }

}

vector<double> Layer::get_outputs(){
    return outputs;
}

//////////////////////////////////////////////////////////////////////
class Net{
    private:
        vector<Layer> _Net;         //La red es un vector de capas (Layer)
        vector<int> architecture;
        vector<vector<double> > trainData;
        vector<vector<double> > valiData;
        vector<vector<double> > w_final;
        vector<vector<double> > w_current;
        int lastError, currentError;

    public:
        Net(vector<int>,vector<vector<double> >,vector<vector<double> >);
        void Training();                        // Función de entrenamiento de la red
        void Validation();                      // Dados los pesos finales se vaidan los datos
        vector<double> rand_0_1(int);           // Genera un vector de doubles aleatorios entre 0 y 1, el tamaño del vector es el argumento de entrada
        void In_weights();                      // Genera los pesos que serán usados en la red
        void writeOutputs();
};

Net::Net(vector<int> _architecture, vector<vector<double> > _trainData,vector<vector<double> > _validationData){
    architecture = _architecture;
    trainData = _trainData;
    valiData = _validationData;

    lastError = 100;
    currentError = 0;

    Training();
    Validation();
}

void Net::Training(){
    cout << "Entrenando la red..." << endl;
    int iter = 10000;

    for(int i=0; i<iter; i++){
        // Generar los pesos para esta prueba de entrenamiento
        In_weights();

        currentError = 0;

        // Se corre el proceso de feed forward con los pesos generados para los 85 datos de entrenamiento
        for(int j=0; j<85; j++){

            vector<double> x;
            vector<vector<double> > w;
            int count = 0;
            int final_out;

            // Se vacia la red para volverla a crear
            _Net.clear();

            for(int k=0; k<architecture.size(); k++){
                if(k==0){
                    x.clear();
                    x.push_back(trainData[j][0]/1000.0);
                    x.push_back(trainData[j][1]/1000.0);
                    x.push_back(trainData[j][2]/1000.0);
                    x.push_back(trainData[j][3]/1000.0);

                    w.clear();
                    int t;
                    for(t=0; t<architecture[k]; t++){
                        w.push_back(w_current[t+count]);
                    }
                    count = t+count;

                    Layer L1(architecture[k],x,w);
                    _Net.push_back(L1);
                }
                else{
                    x.clear();
                    x = _Net[k-1].get_outputs();

                    w.clear();
                    int t;
                    for(t=0; t<architecture[k]; t++){
                        w.push_back(w_current[t+count]);
                    }
                    count = t+count;

                    Layer L1(architecture[k],x,w);
                    _Net.push_back(L1);
                }
            }

            // Se obtiene el error final
            if((_Net[_Net.size()-1].get_outputs())[0] >= 0.5)
                final_out = 1;
            else
                final_out = 0;
            currentError += abs(trainData[j][4] - final_out);

            //cout << (_Net[_Net.size()-1].get_outputs())[0] << endl;
        }

        if(currentError < lastError){
            w_final = w_current;
            lastError = currentError;
        }
        //cout << lastError << endl;
        if(lastError == 0)
            break;
    }

    // Imprimir los pesos finales (cada linea representa una neurona)
    cout << endl << "Pesos finales para las neuronas (cada fila representa una neurona, el valor final por línea representa el bias):" << endl;
    for(int i=0; i<w_final.size(); i++){
        for(int j=0; j<w_final[i].size(); j++){
            cout << w_final[i][j] << "  ";
        }
        cout << endl;
    }

    cout << endl << "Con estos pesos se logra un error de entrenamiento del " << (lastError/85.0)*100 << "%" << endl;
    writeOutputs();
}

void Net::Validation(){
    cout << endl <<"Validación de datos." << endl;
    cout << "X1 " << "X2 " << "X3 " << "X4 " << "Y(calculada) " << "Y(real)" << endl;
    currentError = 0;

    for(int j=0; j<15; j++){
        vector<double> x;
        vector<vector<double> > w;
        int count = 0;
        int final_out;

        // Se vacia la red para volverla a crear
        _Net.clear();

        for(int k=0; k<architecture.size(); k++){
            if(k==0){
                x.clear();
                x.push_back(valiData[j][0]/1000.0);
                x.push_back(valiData[j][1]/1000.0);
                x.push_back(valiData[j][2]/1000.0);
                x.push_back(valiData[j][3]/1000.0);

                w.clear();
                int t;
                for(t=0; t<architecture[k]; t++){
                    w.push_back(w_final[t+count]);
                }
                count = t+count;

                Layer L1(architecture[k],x,w);
                _Net.push_back(L1);
            }
            else{
                x.clear();
                x = _Net[k-1].get_outputs();

                w.clear();
                int t;
                for(t=0; t<architecture[k]; t++){
                    w.push_back(w_final[t+count]);
                }
                count = t+count;

                Layer L1(architecture[k],x,w);
                _Net.push_back(L1);
            }
        }

        // Se obtiene el error final
        if((_Net[_Net.size()-1].get_outputs())[0] >= 0.5)
            final_out = 1;
        else
            final_out = 0;
        currentError += abs(valiData[j][4] - final_out);


        cout << valiData[j][0] << "  " << valiData[j][1] << "  " << valiData[j][2] << "  " << valiData[j][3] << "  " << final_out << "  " << valiData[j][4] << endl;
    }

    cout << endl << "Se logra un error de validación del " << (currentError/15.0)*100 << "%" << endl << endl;
}

vector<double> Net::rand_0_1(int vect_size){        // Genera un vector de doubles aleatorios entre 0 y 1 de tamaño vect_size
    vector<double> vect_values;
    for(int i=0; i<vect_size; i++){
        double value = rand() % 2001;
        value -= 1000.0;
        value = value/1000.0;
        vect_values.push_back(value);
    }

    return vect_values;
}

void Net::In_weights(){
    w_current.clear();
    for(int capa=0; capa<architecture.size(); capa++){
        if(capa==0){
            for(int j=0; j<architecture[capa]; j++)
                w_current.push_back(rand_0_1(5));
        }
        else{
            for(int j=0; j<architecture[capa]; j++)
                w_current.push_back(rand_0_1(architecture[capa-1] + 1));
        }
    }
}

void Net ::writeOutputs(){
    ofstream output;

    // Nombre del archivo
    output.open("Salida.txt");

    output << "Arquitectura de la red neuronal" << endl;
    output << "La red presenta " << architecture.size() << " capas." << endl;
    output << "Las neuronas por capa son:" << endl;
    for(int i=0; i<architecture.size(); i++)
        output << architecture[i] << "  ";
    output << endl;

    output << endl << "Pesos finales para las neuronas (cada fila representa una neurona, el valor final por línea representa el bias):" << endl;
    for(int i=0; i<w_final.size(); i++){
        for(int j=0; j<w_final[i].size(); j++){
            output << w_final[i][j] << "  ";
        }
        output << endl;
    }

    output << endl << "Con estos pesos se logra un error de entrenamiento del " << (lastError/85.0)*100 << "%" << endl;
    output.close();

}

////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]){
    if (argc < 2){
        cerr << "no input file's name\n"<< endl;
    }

    // Leer y guardar los datos de entrenamiento y validacion
    vector< vector<double> > trainData;    // Matriz con los datos
    readData((char*)argv[1], trainData);

    // Se separan los datos en 85 para entrenamiento y 15 para validacion
    vector<vector<double> > valiData;

    for(int i=1; i<=15; i++){
        vector<double> temp;
        temp = trainData[100-i];
        valiData.push_back(temp);
        trainData.pop_back();
    }

    cout << "Datos de entrenamiento" << endl;
    cout << "X1 " << "X2 " << "X3 " << "X4 " << "Y" << endl;
    for(int i=0; i<85; i++){
            for(int j=0; j<5; j++){
                cout << trainData[i][j] << "  ";
            }
            cout << endl;
    }
    cout <<endl;

    cout << "Datos de validacion" << endl;
    cout << "X1 " << "X2 " << "X3 " << "X4 " << "Y" << endl;
    for(int i=0; i<15; i++){
            for(int j=0; j<5; j++){
                cout << valiData[i][j] << "  ";
            }
            cout << endl;
    }
    cout << endl << endl;

    vector<int> architecture = {4,8,1};
    cout << "Arquitectura de la red neuronal" << endl;
    cout << "La red presenta " << architecture.size() << " capas." << endl;
    cout << "Las neuronas por capa son:" << endl;
    for(int i=0; i<architecture.size(); i++)
        cout << architecture[i] << "  ";
    cout << endl << endl;

    Net net1(architecture,trainData,valiData);

    return 0;
}


void readData(char* filename, vector< vector<double> >& array){
    string line;
    ifstream input;
    int rows=100, cols=5;

    input.open(filename);
    if(input.is_open()){
        getline(input,line);

        array.resize(rows, vector<double>(cols));
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++)
                input >> array[i][j];
        }

        // Se reordenan las filas de forma aleatoria
        srand(time(NULL));
        int seed = rand() % 101;
        shuffle(array.begin(), array.end(), default_random_engine(seed));
    }
    else
        cout << "ERROR: no se pudo abrir el archivo." << endl;
    input.close();
}
