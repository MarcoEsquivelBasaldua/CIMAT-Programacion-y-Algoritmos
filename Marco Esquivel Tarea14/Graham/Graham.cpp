#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <map>
#include <cairo.h>
using namespace std;

#define Pi 3.14159265


void readPGM(char*,vector<pair<int,int> >&,int&,int&);
void writePolygon(vector<pair<int,int> >);
void Graham(vector<pair<int,int> >,vector<pair<int,int> >&);
bool angleCpm(const pair<int, int> &pa,const pair<int, int> &pb);
int orientation(pair<int,int> p1, pair<int,int> p2, pair<int,int> p3);
double dist(pair<int,int> p1, pair<int,int> p2);

void GraphCairo(vector<pair<int,int> >, vector<pair<int,int> >,int,int);


pair<int,int> pivot;

int main(int argc, char* argv[]){
    if (argc < 2){
        cerr << "no input file's name\n"<< endl;
    }

    vector<pair<int,int> > coordinates; // vector con las coordenadas de todos los puntos leídos
    vector<pair<int,int> > polygon;   // Vector con las coordenadas de los puntos que conforman al polígono convexo encontrado
    int rows,cols;

    readPGM((char*)argv[1], coordinates,rows,cols);

    cout << "Total de puntos a envolver: " << coordinates.size() << endl;

    clock_t inicio = clock();
    Graham(coordinates, polygon);
    cout << endl << "Tiempo tomado en la ejecucion del algoritmo" << endl;
    clock_t fin = clock();
    cout << double(1000.0*(fin - inicio)/CLOCKS_PER_SEC) << " miliseconds" << endl;

    GraphCairo(coordinates,polygon,rows,cols);

    writePolygon(polygon);

    return 0;
}


void readPGM(char* filename,vector<pair<int,int> >& coordinates, int &rows, int &cols){
    vector< vector<int> > array;    // Matriz con los pixeles de la imagen leida
    string line;
    ifstream input;
    int scale;

    input.open(filename);
    if(input.is_open()){
        getline(input,line);
        input >> cols >> rows >> scale;
        //cout << cols << endl;
        //cout << rows << endl;

        array.resize(rows, vector<int>(cols));
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                input >> array[i][j];

                if(array[i][j] > 0){
                    pair<int,int> xy;
                    xy.first = j;
                    xy.second = i;
                    coordinates.push_back(xy);
                }/*end if*/
            }/*end for j*/
        }/*end for i*/

    }/*end if open*/
    else
        cout << "ERROR: no se pudo abrir el archivo." << endl;
    input.close();

    // Ordenar los puntos en coordinates

    pivot = coordinates[0];
    sort(coordinates.begin()+1, coordinates.end(), angleCpm);
}

void writePolygon(vector<pair<int,int> > polygon){
    ofstream output;

    // Nombre del archivo
    output.open("Convex Hull Points.txt");
    output << "Puntos en la envolvente convexa" << endl;
    for(int i=0; i<polygon.size()-1; i++){
        output << polygon[i].first << " " << polygon[i].second << endl;
    }

    output.close();
}

void Graham(vector<pair<int,int> > P, vector<pair<int,int> >& polygon){
    int n = P.size();
    polygon.push_back(P[n-1]);
    polygon.push_back(P[0]);
    polygon.push_back(P[1]);

    int i = 2;
    while(i < n){
        int j = polygon.size()-1;
        int o = orientation(polygon[j-1], polygon[j], P[i]);
        if(o == 2)
            polygon.push_back(P[i++]);
        else
            polygon.pop_back();
    }
}


bool angleCpm(const pair<int, int> &pa, const pair<int, int> &pb){
    int o = orientation(pivot,pa,pb);
    if(o == 0)
        return dist(pivot,pa) < dist(pivot,pb);

    double d1x = pa.first - pivot.first, d1y = pa.second - pivot.second;
    double d2x = pb.first - pivot.first, d2y = pb.second - pivot.second;

    return (atan2(d1y,d1x) - atan2(d2y,d2x)) < 0;
}

int orientation(pair<int,int> p1, pair<int,int> p2, pair<int,int> p3){
    // See 10th slides from following link for derivation
    // of the formula
    int val = (p2.second - p1.second) * (p3.first - p2.first) -
              (p2.first - p1.first) * (p3.second - p2.second);

    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

double dist(pair<int,int> p1, pair<int,int> p2){
    return sqrt( (p2.second - p1.second)*(p2.second - p1.second) + (p2.first - p1.first)*(p2.first - p1.first) );
}

void GraphCairo(vector<pair<int,int> > coordinates, vector<pair<int,int> > polygon,int alto, int ancho){
    cairo_surface_t *surface;
    cairo_t *cr,*line;
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,ancho,alto);
    cr = cairo_create (surface);
    line = cairo_create (surface);
    cairo_rectangle (cr,0,0,ancho,alto);
    cairo_set_source_rgb (cr,0,0,0);
    cairo_fill(cr);
    /////////

    for(int i=0; i<coordinates.size(); i++){
        cairo_set_source_rgba (cr,1,1,1,1);
        cairo_rectangle(cr,coordinates[i].first,coordinates[i].second,1,1);
        cairo_fill(cr);
    }

    double xaux, yaux;
    for(int i=0; i<polygon.size(); i++){
        int valx = polygon[i].first;
        int valy = polygon[i].second;

        if(i >= 1){
            cairo_set_source_rgba (line,1,0,0,1.0);
            cairo_set_line_width (line,3);
            cairo_move_to (line,xaux,yaux);
            cairo_line_to (line,valx,valy);
            cairo_stroke (line);
        }
        xaux = valx;
        yaux = valy;
    }

    for(int i=0; i<polygon.size(); i++){
        cairo_set_source_rgba (cr,0,1,0,1);
        cairo_arc(cr,polygon[i].first,polygon[i].second,2,0,2*Pi);
        cairo_fill(cr);
    }
    //////
    cairo_surface_write_to_png (surface,"Convex Hull Graham.png");
    cairo_destroy (cr);
    cairo_destroy (line);
    cairo_surface_destroy (surface);

}
