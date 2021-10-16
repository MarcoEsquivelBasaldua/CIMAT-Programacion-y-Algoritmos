#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <fstream>
#include <string>
using namespace std;

double mapeo(int,int,pair<double,double>);
double f_x(double,int);
void Poblacion_Inicial(int,int, int,pair<double,double>,multimap<double,pair<int,double> > &);
void Poblacion_Evolucion(int,int,int,pair<double,double>,multimap<double,pair<int,double> > &,double *);
void crear_probVector(int,int,double*,multimap<double,pair<int,double> >);

int main(void){
    int iter = 10;         // Numero de iteraciones a llevar a cabo
    int tam = 10;         // Tamanio de la poblacion
    int selec = tam*0.5;  // Se selecciona una parte de la poblacion con los individuos mas aptos
    int func = 0;        // Se selecciona una de las dos funciones para encontrar el minimo
    int nbits = 6;     // Indica de cuantos bits se compone un individuo

    // Indica el rango de bùsqueda del minimo
    pair<double,double> rango;
    rango.first = -2.0;
    rango.second = 8.0;

    // Espacio donde se irà guardando el mejor individuo de la poblacion
    pair<double,pair<int,double> > Mejor;
    // La poblacion es un multimapa de Individuos
    multimap<double,pair<int,double> > Poblacion;
    multimap<double,pair<int,double> >::iterator it;

    string fout = "Convergencia.txt";
    ofstream output;
    output.open(fout.c_str(),ios::out);

srand(time(NULL));
    for(int i=1; i<=iter; i++){
        double *probVect;       // En este arreglo se guardan las probabilidades para cada bit

        if(i==1){   // Se crea la poblacion inicial
            Poblacion_Inicial(tam,nbits,func,rango,Poblacion);
            it = Poblacion.begin();
            Mejor = *it;
            output << Mejor.second.second << " " << Mejor.first << endl;

            for(it=Poblacion.begin(); it!=Poblacion.end(); it++)
                cout << (*it).first << " " << (*it).second.first << " " << (*it).second.second << endl;

            cout << endl;
        }
        else{   // Se crea una nueva poblacion
            Poblacion_Evolucion(tam,nbits,func,rango,Poblacion,probVect);
            it = Poblacion.begin();
            Mejor = *it;
            output << Mejor.second.second << " " << Mejor.first << endl;

            for(it=Poblacion.begin(); it!=Poblacion.end(); it++)
                cout << (*it).first << " " << (*it).second.first << " " << (*it).second.second << endl;

            cout << endl;
        }

        //Crear vector de Probabilidades
        probVect = (double*)calloc(nbits,sizeof(double));
        crear_probVector(nbits,selec,probVect,Poblacion);

        free(probVect);
    }
    output.close();

    cout << "El minimo se encuentra en la posicion:" << endl;
    cout << "x = " << Mejor.second.second << ", " << "y = " << Mejor.first << endl;
    cout << "El valor entero de su representacion binaria es " << Mejor.second.first << endl;
    return 0;
}


double mapeo(int nbits, int vbits, pair<double,double> rango){
/*
*   Mapea el valor entero de la representacion binaria de un valor de acuerdo
*   a la cantidad de bits que lo representa y al rango de bùsqueda
*/
    double delta = (rango.second-rango.first)/(pow(2,nbits)-1);

    return rango.first + vbits*delta;
}

double f_x(double x, int func){
/*
*   si func == 0 regresa el valor f(x) = (1-x)^2+1
*   en otro caso regresa el valor f(x) = x^2
*/
    if(func)
        return x*x;
    else
        return (1-x)*(1-x)+1;
}

void crear_probVector(int nbits, int selec, double *probVect, multimap<double,pair<int,double> > Poblacion){
/*
*   Toma los selec individuos mas aptos de la generacion para crear un arreglo de probabilidades
*   del tamanio de la cantidad de bits que forman a un individuo.
*/
    multimap<double,pair<int,double> >::iterator it;
    it = Poblacion.begin();
    for(int i=0; i<selec; i++){
        for(int j=(nbits-1); j>=0; j--){
            if((*it).second.first & int(pow(2,j)))
                probVect[nbits-j-1]++;
        }
        it++;
    }

    for(int j=0; j<nbits; j++)
        probVect[j] /= selec;
}

void Poblacion_Evolucion(int tam,int nbits, int func, pair<double,double> rango, multimap<double,pair<int,double> > &Poblacion, double *probVect){
/*
*   Crea una poblacion nueva de acuerdo al vector de probabilidades y al mejor Individuo de la generacion pasada
*/
    /* Un Individuo es un par cuyo primer elemento es un double que guarda la evaluaion f(x)
        este valor se coloca en la primer posicion para que el multimapa se ordene con respect a él
       El segundo elemento de Individuo es un par cuyo primer elemento es el entero de la
        representacion binaria del valor x en el rango dado
       El segundo elemento es el mapeo al valor real de x */
    pair<double,pair<int,double> > Individuo;

    // Se conserva el mejor Individuo de la generacion pasada
    pair<double,pair<int,double> > Mejor;
    multimap<double,pair<int,double> >::iterator it;
    it = Poblacion.begin();
    Mejor = *it;

    // Se destruye la Poblacion actual para crear una nueva
    Poblacion.clear();
    // Se inserta el mejor individuo de la generacion pasada
    Poblacion.insert(Mejor);


    for(int i=1; i<tam; i++){
        Individuo.second.first = 0;
        for(int j=0; j<nbits; j++){
            // Se crea un numero aleatorio entre 0 y 1
            double prob = rand() % 101;
            prob /= 100;
            // Si la probabilidad es menor o igual al valor correspondiente en probVect se suma el valor correspondiente
            if(prob <= probVect[j])
                Individuo.second.first += int(pow(2,nbits-j-1));
        }

        Individuo.second.second = mapeo(nbits,Individuo.second.first,rango);

        Individuo.first = f_x(Individuo.second.second,func);

        Poblacion.insert(Individuo);
    }
}

void Poblacion_Inicial(int tam,int nbits, int func, pair<double,double> rango, multimap<double,pair<int,double> > &Poblacion){
/*
*   Crea una primer poblacion de forma aleatoria
*/
    pair<double,pair<int,double> > Individuo;

    //srand(time(NULL));
    for(int j=0; j<tam; j++){
        Individuo.second.first = rand();
        // El valor en entero de la representacion binaria de un Individuo es generado de forma eleatoria
        // entre 0 y el valor màs grande posible de acuerdo a la cantidad de bits que forman a un Individuo
        Individuo.second.first = rand()%int((pow(2,nbits)));

        Individuo.second.second = mapeo(nbits,Individuo.second.first,rango);

        Individuo.first = f_x(Individuo.second.second,func);

        Poblacion.insert(Individuo);
    }
}
