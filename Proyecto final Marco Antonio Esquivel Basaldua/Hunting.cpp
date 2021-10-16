#include <iostream>
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

#include "Hunting.hpp"
using namespace std;


Hunting::Hunting(vector<vector<double> > _mapa, pair<int,int> _hunter, pair<int,int> _prey){
    hunter = _hunter;
    prey = _prey;
    mapa = _mapa;
    mapaNew = _mapa;

    found = 0;

    A_star();
    graphCairo();
}

void Hunting::A_star(){
    // La posicion del cazador se inicaliza con 0 el de la presa con -4
    mapaNew[hunter.first][hunter.second] = 0;
    mapaNew[prey.first][prey.second] = -4;

    // Se revisan los vecinos del cazador y se ig++ A_star_Marco_Esquivel.cpp Draw_map.cpp Hunting.cpp $(pkg-config --cflags --libs cairo)ntroducen en la cola de prioridad
    int x = hunter.second, xcurrent;
    int y = hunter.first, ycurrent;
    double dist;

    xcurrent = x-1;
    ycurrent = y-1;
    if(ycurrent >= 0 and xcurrent >= 0){
        if(mapaNew[ycurrent][xcurrent] == -4){
            found = 1;
            pathCost = mapaNew[y][x];
        }
        else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
            first_search(x,y,ycurrent,xcurrent);
    }

    xcurrent = x;
    ycurrent = y-1;
    if(ycurrent >= 0){
        if(mapaNew[ycurrent][xcurrent] == -4){
            found = 1;
            pathCost = mapaNew[y][x];
        }
        else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
            first_search(x,y,ycurrent,xcurrent);
    }

    xcurrent = x+1;
    ycurrent = y-1;
    if(ycurrent >= 0 and xcurrent < mapaNew.size()){
        if(mapaNew[ycurrent][xcurrent] == -4){
            found = 1;
            pathCost = mapaNew[y][x];
        }
        else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
            first_search(x,y,ycurrent,xcurrent);
    }

    xcurrent = x-1;
    ycurrent = y;
    if(xcurrent >= 0){
        if(mapaNew[ycurrent][xcurrent] == -4){
            found = 1;
            pathCost = mapaNew[y][x];
        }
        else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
            first_search(x,y,ycurrent,xcurrent);
    }

    xcurrent = x+1;
    ycurrent = y;
    if(xcurrent < mapaNew.size()){
        if(mapaNew[ycurrent][xcurrent] == -4){
            found = 1;
            pathCost = mapaNew[y][x];
        }
        else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
            first_search(x,y,ycurrent,xcurrent);
    }

    xcurrent = x-1;
    ycurrent = y+1;
    if(ycurrent < mapaNew.size() and xcurrent >= 0){
        if(mapaNew[ycurrent][xcurrent] == -4){
            found = 1;
            pathCost = mapaNew[y][x];
        }
        else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
            first_search(x,y,ycurrent,xcurrent);
    }

    xcurrent = x;
    ycurrent = y+1;
    if(ycurrent < mapaNew.size()){
        if(mapaNew[ycurrent][xcurrent] == -4){
            found = 1;
            pathCost = mapaNew[y][x];
        }
        else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
            first_search(x,y,ycurrent,xcurrent);
    }

    xcurrent = x+1;
    ycurrent = y+1;
    if(ycurrent < mapaNew.size() and xcurrent < mapaNew.size()){
        if(mapaNew[ycurrent][xcurrent] == -4){
            found = 1;
            pathCost = mapaNew[y][x];
        }
        else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
            first_search(x,y,ycurrent,xcurrent);
    }

    // Se busca la presa en el espacio de dos dimensiones
    while(!searching.empty() and !found){
        x = searching.top().second.second;
        y = searching.top().second.first;

        searching.pop();

        xcurrent = x-1;
        ycurrent = y-1;
        if(ycurrent >= 0 and xcurrent >= 0){
            if(mapaNew[ycurrent][xcurrent] == -4){
                found = 1;
                pathCost = mapaNew[y][x];
                break;
            }
            else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
                second_search(x,y,ycurrent,xcurrent);
        }

        xcurrent = x;
        ycurrent = y-1;
        if(ycurrent >= 0){
            if(mapaNew[ycurrent][xcurrent] == -4){
                found = 1;
                pathCost = mapaNew[y][x];
                break;
            }
            else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
                second_search(x,y,ycurrent,xcurrent);
        }

        xcurrent = x+1;
        ycurrent = y-1;
        if(ycurrent >= 0 and xcurrent < mapaNew.size()){
            if(mapaNew[ycurrent][xcurrent] == -4){
                found = 1;
                pathCost = mapaNew[y][x];
                break;
            }
            else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
                second_search(x,y,ycurrent,xcurrent);
        }

        xcurrent = x-1;
        ycurrent = y;
        if(xcurrent >= 0){
            if(mapaNew[ycurrent][xcurrent] == -4){
                found = 1;
                pathCost = mapaNew[y][x];
                break;
            }
            else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
                second_search(x,y,ycurrent,xcurrent);
        }

        xcurrent = x+1;
        ycurrent = y;
        if(xcurrent < mapaNew.size()){
            if(mapaNew[ycurrent][xcurrent] == -4){
                found = 1;
                pathCost = mapaNew[y][x];
                break;
            }
            else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
                second_search(x,y,ycurrent,xcurrent);
        }

        xcurrent = x-1;
        ycurrent = y+1;
        if(ycurrent < mapaNew.size() and xcurrent >= 0){
            if(mapaNew[ycurrent][xcurrent] == -4){
                found = 1;
                pathCost = mapaNew[y][x];
                break;
            }
            else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
                second_search(x,y,ycurrent,xcurrent);
        }

        xcurrent = x;
        ycurrent = y+1;
        if(ycurrent < mapaNew.size()){
            if(mapaNew[ycurrent][xcurrent] == -4){
                found = 1;
                pathCost = mapaNew[y][x];
                break;
            }
            else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
                second_search(x,y,ycurrent,xcurrent);
        }

        xcurrent = x+1;
        ycurrent = y+1;
        if(ycurrent < mapaNew.size() and xcurrent < mapaNew.size()){
            if(mapaNew[ycurrent][xcurrent] == -4){
                found = 1;
                pathCost = mapaNew[y][x];
                break;
            }
            else if(mapaNew[ycurrent][xcurrent] == 1 or mapaNew[ycurrent][xcurrent] == 2 or mapaNew[ycurrent][xcurrent] == 2.5)
                second_search(x,y,ycurrent,xcurrent);
        }
    }

    // esto es necesario para encontrar el camino del cazador
    for(int i=0; i<mapaNew.size(); i++){
        for(int j=0; j<mapaNew.size(); j++){
            if(mapaNew[i][j] == 2 or mapaNew[i][j] == 2.5 or mapaNew[i][j] == 1)
                mapaNew[i][j] = -mapaNew[i][j];
        }
    }

    if(found){
        // Se registran las posiciones que debe seguir el cazador
        vector<pair<int,int> > path;

        pathCost += mapa[prey.first][prey.second];
        cout << "La presa fue localizada" << endl;
        cout << "Costo del camino para llegar a ella: " << pathCost << endl;

        // Encontrar el camino que debe seguir el cazador
        x = prey.second;
        y = prey.first;
        mapaNew[y][x] = pathCost;
        mapaNew[hunter.first][hunter.second] = 0.5;

        while(mapaNew[y][x] != 0.5){
            path.push_back(make_pair(y,x));

            if(y-1 >= 0 and x-1 >= 0 and (mapaNew[y-1][x-1] < pathCost and mapaNew[y-1][x-1] > 0)){
                pathCost = mapaNew[y-1][x-1];
                xcurrent = x-1;
                ycurrent = y-1;
            }

            if(y-1 >= 0 and (mapaNew[y-1][x] < pathCost and mapaNew[y-1][x] > 0)){
                pathCost = mapaNew[y-1][x];
                xcurrent = x;
                ycurrent = y-1;
            }

            if(y-1 >= 0 and x+1 < mapa.size() and (mapaNew[y-1][x+1] < pathCost and mapaNew[y-1][x+1] > 0)){
                pathCost = mapaNew[y-1][x+1];
                xcurrent = x+1;
                ycurrent = y-1;
            }

            if(x-1 >= 0 and (mapaNew[y][x-1] < pathCost and mapaNew[y][x-1] > 0)){
                pathCost = mapaNew[y][x-1];
                xcurrent = x-1;
                ycurrent = y;
            }

            if(x+1 < mapa.size() and (mapaNew[y][x+1] < pathCost and mapaNew[y][x+1] > 0)){
                pathCost = mapaNew[y][x+1];
                xcurrent = x+1;
                ycurrent = y;
            }

            if(y+1 < mapa.size() and x-1 >= 0 and (mapaNew[y+1][x-1] < pathCost and mapaNew[y+1][x-1] > 0)){
                pathCost = mapaNew[y+1][x-1];
                xcurrent = x-1;
                ycurrent = y+1;
            }

            if(y+1 < mapa.size() and (mapaNew[y+1][x] < pathCost and mapaNew[y+1][x] > 0)){
                pathCost = mapaNew[y+1][x];
                xcurrent = x;
                ycurrent = y+1;
            }

            if(y+1 < mapa.size() and x+1 < mapa.size() and (mapaNew[y+1][x+1] < pathCost and mapaNew[y+1][x+1] > 0)){
                pathCost = mapaNew[y+1][x+1];
                xcurrent = x+1;
                ycurrent = y+1;
            }

            mapaNew[y][x] = -3;

            x = xcurrent;
            y = ycurrent;
        }

        writePath(path);

        mapaNew[prey.first][prey.second] = -4;
        mapaNew[hunter.first][hunter.second] = 0;
    }
    else
        cout << endl << "La presa no puede ser alcanzada" << endl;
}

void Hunting::graphCairo(){
    int spaces = mapa.size();
    int ancho = spaces*30;
    int alto = ancho;
    cairo_surface_t *surface;
    cairo_t *cr,*line;
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,ancho,alto);
    cr = cairo_create (surface);
    line = cairo_create (surface);
    cairo_rectangle (cr,0,0,ancho,alto);
    cairo_set_source_rgb (cr,1,1,1);
    cairo_fill(cr);
    /////////

    // Draw grid
    for(int i=1; i<spaces; i++){
        cairo_set_source_rgba (line,0,0,0,1.0);
        cairo_set_line_width (line,2);
        cairo_move_to (line,ancho/spaces*i,0);
        cairo_line_to (line,ancho/spaces*i,ancho);
        cairo_stroke (line);

        cairo_set_source_rgba (line,0,0,0,1.0);
        cairo_set_line_width (line,2);
        cairo_move_to (line,0,ancho/spaces*i);
        cairo_line_to (line,alto,ancho/spaces*i);
        cairo_stroke (line);
    }

    // Obstaculos
    for(int i=0; i<spaces; i++){
        for(int j=0; j<spaces; j++){
            // Los que no dejan pasar
            if(mapa[i][j] == -10){
                cairo_set_source_rgba (cr,0,0,0,1);
                cairo_rectangle(cr,ancho/spaces*j,ancho/spaces*i,30,30);
                cairo_fill(cr);
            }

            // Los que suman 1 adicional
            if(mapa[i][j] == 2){
                cairo_set_source_rgba (cr,0,0,0,0.3);
                cairo_rectangle(cr,ancho/spaces*j,ancho/spaces*i,30,30);
                cairo_fill(cr);
            }

            // Los que suman 1.5 adicional
            if(mapa[i][j] == 2.5){
                cairo_set_source_rgba (cr,0,0,0,0.6);
                cairo_rectangle(cr,ancho/spaces*j,ancho/spaces*i,30,30);
                cairo_fill(cr);
            }

            // Llenar con el camino del cazador
            if(mapaNew[i][j] == 0){
                cairo_set_source_rgba (cr,1,0,0,1);
                cairo_rectangle(cr,ancho/spaces*j,ancho/spaces*i,30,30);
                cairo_fill(cr);
            }
            if(mapaNew[i][j] == -4){
                cairo_set_source_rgba (cr,0,1,0,1);
                cairo_rectangle(cr,ancho/spaces*j,ancho/spaces*i,30,30);
                cairo_fill(cr);
            }
            if(mapaNew[i][j] == -3){
                cairo_set_source_rgba (cr,0,1,1,0.5);
                cairo_rectangle(cr,ancho/spaces*j,ancho/spaces*i,30,30);
                cairo_fill(cr);
            }
            if(mapaNew[i][j] > 1){
                cairo_set_source_rgba (cr,1,0,0,0.3);
                cairo_rectangle(cr,ancho/spaces*j,ancho/spaces*i,30,30);
                cairo_fill(cr);
            }
        }
    }
    //////
    cairo_surface_write_to_png (surface,"Map.png");
    cairo_destroy (cr);
    cairo_destroy (line);
    cairo_surface_destroy (surface);
}

double Hunting::dist_eucl(pair<int,int> start){
    int y = prey.first - start.first;
    int x = prey.second - start.second;

    return sqrt(x*x + y*y);
}

void Hunting::first_search(int x, int y, int ycurrent, int xcurrent){
    double dist = - (dist_eucl(make_pair(ycurrent,xcurrent)) + mapaNew[ycurrent][xcurrent]);

    pair<int,int> pos;
    pos.first = ycurrent;
    pos.second = xcurrent;

    searching.push(make_pair(dist,pos));
    mapaNew[ycurrent][xcurrent] += mapaNew[y][x] + 0.1;
}

void Hunting::second_search(int x, int y, int ycurrent, int xcurrent){
    double dist = - (dist_eucl(make_pair(ycurrent,xcurrent)) + mapaNew[ycurrent][xcurrent]);

    pair<int,int> pos;
    pos.first = ycurrent;
    pos.second = xcurrent;

    searching.push(make_pair(dist,pos));
    mapaNew[ycurrent][xcurrent] += mapaNew[y][x];
}

void Hunting::writePath(vector<pair<int,int> > path){
    ofstream output;

    // Nombre del archivo
    output.open("Path Direction.txt");
    output << "Puntos que debe seguir el cazador" << endl;
    for(int i=path.size()-1; i>=0; i--){
        output << path[i].first << " " << path[i].second << endl;
    }

    output.close();
}
