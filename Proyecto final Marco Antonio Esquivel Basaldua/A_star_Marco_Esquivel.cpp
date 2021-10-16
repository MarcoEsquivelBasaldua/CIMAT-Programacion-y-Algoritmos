#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <cairo.h>
#include <ctime>
#include <utility>
#include <cstdlib>
#include <queue>

#include "Draw_map.hpp"
#include "Hunting.hpp"
using namespace std;

void interactive(vector<vector<double> >&, pair<int,int>, pair<int,int>);


int main(void){
    srand(time(NULL));

    int obsts_0, obsts_1, obsts_15, spaces;
    vector<vector<double> > mapa;

    cout << "El mapa de búsqueda es un cuadrado" << endl;
    cout << "Ingrese el tamaño de uno de sus lados" << endl;
    cin >> spaces;
    cout << "Ingrese en porcentaje la cantidad de obstáculos tipo 0, tipo 1 y tipo 1.5 separados por un espacio" << endl;
    cin >> obsts_0 >> obsts_1 >> obsts_15;

    // Blindar las entradas para que no se pase del 100%
    while ((obsts_0 + obsts_1 + obsts_15) >= 100){
        cout << "Asegurate que la suma de los porcentajes no exeda 100%" << endl;
        cout << "Vuelve a ingresar los porcentajes de los obstáculos" << endl;
        cin >> obsts_0 >> obsts_1 >> obsts_15;
    }

    Draw_map map1(obsts_0,obsts_1,obsts_15,spaces);

    mapa = map1.get_mapa();

    pair<int,int> hunter;
    pair<int,int> prey;

    cout << "Ingrese las coordenadas (tipo matriz) del cazador separados por un espacio" << endl;
    cin >> hunter.first >> hunter.second;
    while(mapa[hunter.first][hunter.second] != 1 or mapa[hunter.first][hunter.second] < 0 or mapa[hunter.first][hunter.second] >= mapa.size()){
        cout << "Ubicación inválida para el cazador. Vuelva a ingresar las coordenadas" << endl;
        cin >> hunter.first >> hunter.second;
    }

    cout << "Ingrese las coordenadas (tipo matriz) de la presa separados por un espacio" << endl;
    cin >> prey.first >> prey.second;
    while(mapa[prey.first][prey.second] != 1 or mapa[prey.first][prey.second] < 0 or mapa[prey.first][prey.second] >= mapa.size()){
        cout << "Ubicación inválida para el cazador. Vuelva a ingresar las coordenadas" << endl;
        cin >> prey.first >> prey.second;
    }

    Hunting h1(mapa,hunter,prey);

    // Bucle para hacer interactiva
    interactive(mapa, hunter, prey);

    return 0;
}


void interactive(vector<vector<double> >& mapa, pair<int,int> hunter, pair<int,int> prey){

    int command = -1;

    while(command != 0){
        cout << endl << "Utiliza el teclado numérico para mover la presa" << endl << endl;
        cin >> command;
        int y = prey.first;
        int x = prey.second;
        int possible;

        if(command == 0){
            cout << endl << "Saliendo de la ejecucion" << endl;
            break;
        }
        else if(command == 1 and y+1 < mapa.size() and x-1 >= 0 and mapa[y+1][x-1] != 0){
            y = y+1;
            x = x-1;
            possible = 1;
        }
        else if(command == 2 and y+1 < mapa.size() and mapa[y+1][x] != 0){
            y = y+1;
            possible = 1;
        }
        else if(command == 3 and y+1 < mapa.size() and x+1 < mapa.size() and mapa[y+1][x+1] != 0){
            y = y+1;
            x = x+1;
            possible = 1;
        }
        else if(command == 4 and x-1 >= 0 and mapa[y][x-1] != 0){
            x = x-1;
            possible = 1;
        }
        else if(command == 6 and x+1 < mapa.size() and mapa[y][x+1] != 0){
            x = x+1;
            possible = 1;
        }
        else if(command == 7 and y-1 >= 0 and x-1 >= 0 and mapa[y-1][x-1] != 0){
            y = y-1;
            x = x-1;
            possible = 1;
        }
        else if(command == 8 and y-1 >= 0 and mapa[y-1][x] != 0){
            y = y-1;
            possible = 1;
        }
        else if(command == 9 and y-1 >= 0 and x+1 < mapa.size() and mapa[y-1][x+1] != 0){
            y = y-1;
            x = x+1;
            possible = 1;
        }
        else
            possible = 0;


        if(possible){
            prey.first = y;
            prey.second = x;
            Hunting h1(mapa,hunter,prey);
        }
        else
            cout << "Posicion invàlida" << endl;

    }
}
