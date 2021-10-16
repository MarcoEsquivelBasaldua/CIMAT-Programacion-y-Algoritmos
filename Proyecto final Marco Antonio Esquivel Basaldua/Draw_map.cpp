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

#include "Draw_map.hpp"


Draw_map::Draw_map(int _obst_0, int _obst_1, int _obst_15, int _spaces){
    spaces = _spaces;
    obsts_0 = _obst_0 * (spaces*spaces)/100;        // Determina la cantidad de obstaculos de cada tipoen el mapa
    obsts_1 = _obst_1 * (spaces*spaces)/100;
    obsts_15 = _obst_15 * (spaces*spaces)/100;

    fillMapa();
    graphCairo();
}

void Draw_map::fillMapa(){
/*
*   Se llena la cuadricula que representa el mapa
*/
    for(int i=0; i<spaces; i++){
        vector<double> row;
        for(int j=0; j<spaces; j++)
            row.push_back(1);

        mapa.push_back(row);
    }

    // Obtaculos que no dejan pasar
    int total = 0;
    while(total < obsts_0){
        int i = rand() % spaces;
        int j = rand() % spaces;

        if(mapa[i][j] == 1){
            mapa[i][j] = -10;
            total++;
        }
    }

    // Obstàculos que suman 1
    total = 0;
    while(total < obsts_1){
        int i = rand() % spaces;
        int j = rand() % spaces;

        if(mapa[i][j] == 1){
            mapa[i][j] += 1;
            total++;
        }
    }

    // Obstàculos que suman 1.5
    total = 0;
    while(total < obsts_15){
        int i = rand() % spaces;
        int j = rand() % spaces;

        if(mapa[i][j] == 1){
            mapa[i][j] += 1.5;
            total++;
        }
    }
}

void Draw_map::graphCairo(){
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
        }
    }

    //////
    cairo_surface_write_to_png (surface,"Map.png");
    cairo_destroy (cr);
    cairo_destroy (line);
    cairo_surface_destroy (surface);

    cout << endl << "Mapa con los obstàculos generado" << endl << endl;
}

vector<vector<double> > Draw_map::get_mapa(){
    return mapa;
}
