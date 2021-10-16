/*
*
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;

void READ(char*,vector<pair<double, double> >&);
void write(string, vector<pair<double,double> >&);
double A_Heron(pair<double, double>, pair<double, double>, pair<double, double>);
double distance(pair<double, double>, pair<double, double>);
double A_poligone(vector<pair<double,double> >);
void Visvalingam(vector<pair<double,double> >&, double);


int main(int argc, char* argv[]){
    if (argc < 2){
        cerr << "no input file's name\n"<< endl;
    }

    vector<pair<double, double> >coordinates;
    vector<pair<double, double> >coordinates_Vis;
    READ((char*)argv[1], coordinates);

    coordinates_Vis = coordinates;

    double toler = 3.4e-4;
    Visvalingam(coordinates_Vis,toler);

    // Métricas de simpificacion
    double Aoriginal = A_poligone(coordinates);
    double Areduced = A_poligone(coordinates_Vis);
    double pointsOriginal = coordinates.size();
    double pointsReduced = coordinates_Vis.size();
    cout <<endl;
    cout << "Total de vértices en la imagen original" << " " << pointsOriginal <<endl;
    cout << "Total de vértices en la imagen simplificada" << " " << pointsReduced <<endl;


    cout <<endl;
    cout << "Métricas de simplificacion:" << endl;
    cout << "Porcentaje de compresion: " << (pointsReduced/pointsOriginal)*100 << endl;
    cout << "Coeficiente de Jaccart: " << 2*Areduced/(Areduced+Aoriginal) << endl;
    cout <<endl;


    string original = "Original.txt";
    string reduced = "Reduced.txt";

    write(original,coordinates);
    write(reduced,coordinates_Vis);

    return 0;
}


void READ(char* filename, vector<pair<double,double> >&coordinates){
/*
*   Descripción:
*       Lee un archivo de texto y registra los datos leidos como coordenadas (x,y) en un vector de pares
*
*   Entradas:
*       - char* filename: nombre del archivo de texto que será leído
*       - vector<pair<double,double> >&coordinates: referencia al vector de pares donde las coordenadas leídas del archivo de texto serán guardadas
*
*   Salidas:
*       - ninguna
*/
    //ifstream trazo;
    string line;

    ifstream trazo(filename, ios::in);

    //trazo.open(filename);
    pair<double, double> xy;

    while(!trazo.eof()){
        trazo >> xy.first;
        trazo >> xy.second;
        coordinates.push_back(xy);
    }
}

void write(string fout, vector<pair<double,double> >&coordinates){
/*
*   Descripción:
*       Guarda en un archivo de texto los datos como coordenadas (x,y) de un vector de pares
*
*   Entradas:
*       - string fout: nombre del archivo de texto donde se guardan los datos
*       - vector<pair<double,double> >&coordinates: referencia al vector de pares donde las coordenadas ron recuperadas
*
*   Salidas:
*       - ninguna
*/
    ofstream output;
    output.open(fout.c_str(),ios::out);

    for(int i=0; i<coordinates.size(); i++){
        output << coordinates[i].first << " " << coordinates[i].second << endl;
    }

    output << coordinates[0].first << " " << coordinates[0].second << endl;

    output.close();
}

double A_Heron(pair<double, double> x1, pair<double, double> x2, pair<double, double> x3){
/*
*   Descripción:
*       Calcula el área de un triángulo usando la fórmula de Herón
*
*   Entradas:
*       - pair<double, double> x1: par con las coordenadas del primer punto
*       - pair<double, double> x2: par con las coordenadas del segundo punto
*       - pair<double, double> x3: par con las coordenadas del tercer punto
*
*   Salidas:
*       - double: área del triángulo
*/
    double a,b,c,s;

    a = distance(x1,x2);
    b = distance(x2,x3);
    c = distance(x1,x3);

    s = (a + b + c)/2;

    return sqrt(s*(s-a)*(s-b)*(s-c));
}

double distance(pair<double, double> p1, pair<double, double> p2){
/*
*   Descrpción:
*       Calcula la distancia euclideana entre dos puntos
*
*   Entradas:
*       - pair<double, double> p1: par con las coordenadas del primer punto
*       - pair<double, double> p2: par con las coordenadas del segundo punto
*
*   Salidas:
*       - double: distancia entre p1 y p2
*/
    return sqrt(pow(p2.first - p1.first,2) + pow(p2.second - p1.second,2));
}

double A_poligone(vector<pair<double,double> >coordinates){
/*
*   Descripción:
*       Calcula el área de un polígono dadas las coordenadas de sus vértices usando el método del determinante
*
*   Entradas:
*       - vector<pair<double,double> >coordinates: vector de pares con las coordenadas de los vértices del polígono
*
*   Salidas:
*       - double: área del polígono ingresado
*/
    coordinates.push_back(coordinates[0]);      // Se agregan las coordenadas del primer punto al final del vector
    double prod1 = 0, prod2 = 0;

    for(int i =0; i<coordinates.size()-1; i++){
        prod1 += coordinates[i].first * coordinates[i+1].second;
        prod2 += coordinates[i].second * coordinates[i+1].first;
    }

    return fabs(0.5*(prod1-prod2));
}

void Visvalingam(vector<pair<double,double> >&coordinates, double toler){
/*
*   Descripción:
*       Realiza la simplificacion de líneas de una figura cerrada dadas las coordenadas de sus vértices
*
*   Entradas:
*       - vector<pair<double,double> >&coordinates: vector de pares con las coordenadas de la figura a simplificar
*       - double toler: mínima área de tolerancia en la figura
*
*   Salida:
*       - vector<pair<double,double> >&coordinates: vector de pares con los puntos de la nueva figura, se actualiza el vector de entrada (salida por referncia)
*/
    double Amin = toler-1,Aaux;
    int pos;

    while(true){
        pos = 0;
        Amin = A_Heron(coordinates[(int)coordinates.size()-1],coordinates[0],coordinates[1]);

        int i;
        for(i=1; i < (int)coordinates.size(); i++){
            if(i != (int)coordinates.size()-1){
                Aaux = A_Heron(coordinates[i-1],coordinates[i],coordinates[i+1]);
            }

            if(Aaux < Amin){
                Amin = Aaux;
                pos = i;
            }
        }

        if(Amin < toler) coordinates.erase(coordinates.begin()+pos);
        else break;
    }
}
