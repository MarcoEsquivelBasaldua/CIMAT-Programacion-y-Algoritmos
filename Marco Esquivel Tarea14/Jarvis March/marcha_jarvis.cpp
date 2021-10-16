#include <iostream>
#include <map>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <cairo.h>
#include <ctime>
using namespace std;

#define Pi 3.14159265

void readCoordinates(char*,vector<pair<double,double> >&);
void generateCoordinates(int, vector<pair<double,double> >&);
double rand_1010();
void Jarvis(vector<pair<double,double> >, vector<pair<double,double> >&);
void writePolygon(vector<pair<double,double> >);

void GraphCairo(vector<pair<double,double> >, vector<pair<double,double> >);
double max_x(vector<pair<double,double> >);
double max_y(vector<pair<double,double> >);
double min_x(vector<pair<double,double> >);
double min_y(vector<pair<double,double> >);

int main(void){
    vector<pair<double,double> > vect_coord; // vector con las coordenadas de todos los puntos leídos
    vector<pair<double,double> > polygon;   // Vector con las coordenadas de los puntos que conforman al polígono convexo encontrado
    int n;
    //readCoordinates((char*)argv[1], vect_coord); // Lee las coordenadas de los puntos en el archivo de texto

    cout << "Ingrese la cantidad de puntos a graficar" << endl;
    cin >> n;
    generateCoordinates(n, vect_coord);

    clock_t inicio = clock();

    Jarvis(vect_coord,polygon);

    cout << endl << "Tiempo tomado en la ejecucion del algoritmo" << endl;
    clock_t fin = clock();
    cout << double(1000.0*(fin - inicio)/CLOCKS_PER_SEC) << " miliseconds" << endl;

    writePolygon(polygon);
    GraphCairo(vect_coord,polygon);

    return 0;
}

void generateCoordinates(int n, vector<pair<double,double> >& vect_coord){
    multimap<double,double> coordinates;
    double x,y;

    srand(time(NULL));
    for(int i=0; i<n; i++){
        // Generar un valor entre -10 y 10 y guardarlo en x
        x =rand_1010();
        y = rand_1010();

        coordinates.insert({y,x});
    }

    pair<double,double> xy;
    multimap<double,double>::iterator itr;
    int i=0;
    for(itr = coordinates.begin(); itr != coordinates.end(); itr++){
        xy.first = (*itr).second;
        xy.second = (*itr).first;
        vect_coord.push_back(xy);
        i++;
    }

}

double rand_1010(){
    double value = rand() % 2001;
    value -= 1000.0;
    value = value/100.0;

    return value;
}

void writePolygon(vector<pair<double,double> > polygon){
    ofstream output;

    // Nombre del archivo
    output.open("Convex Hull Points.txt");
    output << "Puntos en la envolvente convexa" << endl;
    for(int i=0; i<polygon.size()-1; i++){
        output << polygon[i].first << " " << polygon[i].second << endl;
    }

    output.close();
}


void readCoordinates(char* filename,vector<pair<double,double> >& vect_coord){
    multimap<double,double> coordinates;
    ifstream input;
    double x,y;

    input.open(filename);
    if(input.is_open()){
        while(input >> x >> y){
            //input >> x >> y;
            coordinates.insert({y,x});
        }
    }
    else
        cout << "ERROR: no se pudo abrir el archivo." << endl;
    input.close();

    // Se convierte el mapa en un vector
    pair<double,double> xy;
    multimap<double,double>::iterator itr;
    int i=0;
    for(itr = coordinates.begin(); itr != coordinates.end(); itr++){
        xy.first = (*itr).second;
        xy.second = (*itr).first;
        vect_coord.push_back(xy);
        i++;
    }
}

// Marcha de Jarvis
void Jarvis(vector<pair<double,double> > vect_coord, vector<pair<double,double> >& polygon){
    pair<double,double> xy;

    // Se agrega el primer elemento de vect_coord en polygon
    xy.first = vect_coord[0].first;
    xy.second = vect_coord[0].second;
    polygon.push_back(xy);

    double lastAngle = 10.0;
    double currentAngle;
    double cumulateAngle = 0;
    double totalAngle = 0;
    while(true){
        int pos;
        lastAngle = 100.0;

        for(int i=0; i<vect_coord.size(); i++){
            // Obtener el angulo formado con el último elemento de polygon y el actual elemento de coordinates
            if(vect_coord[i].second != polygon[polygon.size()-1].second or vect_coord[i].first != polygon[polygon.size()-1].first){
                currentAngle = atan2(vect_coord[i].second - polygon[polygon.size()-1].second, vect_coord[i].first - polygon[polygon.size()-1].first);

                if(currentAngle < 0)
                    currentAngle += 2*3.14159265;

                if(totalAngle > Pi/2.0 and currentAngle < Pi/2)
                    currentAngle = 100.0;

                if(totalAngle > Pi and currentAngle < Pi)
                    currentAngle = 100.0;
                if(totalAngle > Pi*(3.0/2.0) and currentAngle <Pi*(3.0/2.0))
                    currentAngle = 100.0;

                if(currentAngle < lastAngle){
                    lastAngle = currentAngle;
                    pos = i;
                }
            }
        }
        totalAngle = lastAngle;

        xy.first = vect_coord[pos].first;
        xy.second = vect_coord[pos].second;
        polygon.push_back(xy);


        // El bucle se detiene si el punto incial y final en polygon son iguales
        if(polygon[0].first == polygon[polygon.size()-1].first and polygon[0].second == polygon[polygon.size()-1].second)
            break;

        if(polygon[polygon.size()-1].first == polygon[polygon.size()-3].first and polygon[polygon.size()-1].second == polygon[polygon.size()-3].second){
            polygon.pop_back();
            xy.first = vect_coord[0].first;
            xy.second = vect_coord[0].second;
            polygon.push_back(xy);

            break;
        }
    }
}

void GraphCairo(vector<pair<double,double> > coordinates, vector<pair<double,double> > polygon){

    // Multiplicar los elementos de coordinates y polygon por un factor de 10 para una mejor visualización
    for(int i=0; i<coordinates.size(); i++){
        coordinates[i].first = 80*coordinates[i].first;
        coordinates[i].second = 80*coordinates[i].second;
    }

    for(int i=0; i<polygon.size(); i++){
        polygon[i].first = 80*polygon[i].first;
        polygon[i].second = 80*polygon[i].second;
    }

    double xmax = max_x(coordinates);
    double ymax = max_y(coordinates);
    double xmin = min_x(coordinates);
    double ymin = min_y(coordinates);
    int alto = (ymax-ymin)+(ymax-ymin)/8;
    int ancho = (xmax-xmin)+(xmax-xmin)/8;

    cairo_surface_t *surface;
    cairo_t *cr,*line;
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,ancho,alto);
    cr = cairo_create (surface);
    line = cairo_create (surface);
    cairo_rectangle (cr,0,0,ancho,alto);
    cairo_set_source_rgb (cr,1,1,1);
    cairo_fill(cr);
    /////////

    double xaux, yaux;
    for(int i=0; i<coordinates.size(); i++){
        // Esta es mi ecuación de la recta
        int valx = coordinates[i].first - xmin + (xmax-xmin)/16;
        int valy = coordinates[i].second - ymin + (ymax-ymin)/16;
        valy = alto - valy;

        cairo_set_source_rgba (cr,0.3,0.4,0.3,1.0);
        cairo_arc(cr,valx,valy,10,0,2*Pi);
        cairo_fill(cr);
    }

    for(int i=0; i<polygon.size(); i++){
        // Esta es mi ecuación de la recta
        int valx = polygon[i].first - xmin + (xmax-xmin)/16;
        int valy = polygon[i].second - ymin + (ymax-ymin)/16;
        valy = alto -valy;

        if(i >= 1){
            cairo_set_source_rgba (line,0,0,0,1.0);
            cairo_set_line_width (line,5);
            cairo_move_to (line,xaux,yaux);
            cairo_line_to (line,valx,valy);
            cairo_stroke (line);
        }
        xaux = valx;
        yaux = valy;
    }

    // Trazar eje x
    xaux = (xmax-xmin)/16 - xmin;
    cairo_set_source_rgba (line,0.2,0.3,0.4,1.0);
    cairo_set_line_width (line,3);
    cairo_move_to (line,xaux,0);
    cairo_line_to (line,xaux,alto);
    cairo_stroke (line);

    // Trazar eje y
    yaux = - ymin + (ymax-ymin)/16;
    yaux = alto - yaux;
    cairo_set_source_rgba (line,0.2,0.3,0.4,1.0);
    cairo_set_line_width (line,3);
    cairo_move_to (line,0,yaux);
    cairo_line_to (line,ancho,yaux);
    cairo_stroke (line);

    //////
    cairo_surface_write_to_png (surface,"Convex Hull Jarvis.png");
    cairo_destroy (cr);
    cairo_destroy (line);
    cairo_surface_destroy (surface);

}

double max_x(vector<pair<double,double> >coordinates){
    double xmax = 0;

    for(int i=0; i<coordinates.size(); i++){
        if(coordinates[i].first > xmax) xmax = coordinates[i].first;
    }

    return xmax;
}

double max_y(vector<pair<double,double> >coordinates){
    double ymax = 0;

    for(int i=0; i<coordinates.size(); i++){
        if(coordinates[i].second > ymax) ymax = coordinates[i].second;
    }

    return ymax;
}

double min_x(vector<pair<double,double> >coordinates){
    double xmin = coordinates[0].first;

    for(int i=1; i<coordinates.size(); i++){
        if(coordinates[i].first < xmin) xmin = coordinates[i].first;
    }

    return xmin;
}

double min_y(vector<pair<double,double> >coordinates){
    double ymin = coordinates[0].second;

    for(int i=1; i<coordinates.size(); i++){
        if(coordinates[i].second < ymin) ymin = coordinates[i].second;
    }

    return ymin;
}
