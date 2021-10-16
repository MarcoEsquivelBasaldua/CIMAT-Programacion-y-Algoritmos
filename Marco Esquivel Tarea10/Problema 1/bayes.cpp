#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;



void training(char*,map<string,double> &,int &,map<string,double> &, int &, vector<string> &);
void cleanLine(string &line);

int main(int argc, char* argv[]){
    if (argc < 2){
        cerr << "no input file's name\n"<< endl;
    }

    map<string,double> map_Spam;        // Diccionario con las palabras encontradas en los spam
    map<string,double> map_Ham;         // Diccionario con las palabras encontradas en los no spam
    int total_spam = 0, total_ham = 0;
    vector<string> prueba;

    training((char*)argv[1],map_Spam,total_spam,map_Ham,total_ham,prueba); // Se leen los pixeles de la imagen

    /*map<string,double>::iterator It;
    for(It = map_Ham.begin(); It != map_Ham.end(); It++){
        cout << It->first << " " << It->second << endl;
    }*/
    /*int total_prueba = prueba.size();
    for(int i=0; i<total_prueba; i++){
        cout <<i<<' '<< prueba[i] << endl;
    }*/

    // Se prueba el clasificador
    int real_spam = 0, found_spam = 0;
    int real_ham = 0, found_ham = 0;
    int no_class = 0;
    string type, word;

    map<string, double>::iterator it_spam;
    map<string, double>::iterator it_ham;

    int total_prueba = prueba.size();
    for(int i=0; i<total_prueba; i++){
        //cout << prueba[i] << endl;
        double prob_spam = 1, prob_ham = 1;
        stringstream line(prueba[i]);
        line >> type;

        while(line >> word){
            it_spam = map_Spam.find(word);
            it_ham = map_Ham.find(word);
            //cout << it_ham->first << endl;
            if(it_ham != map_Ham.end() && it_spam != map_Spam.end()){
                prob_spam *= it_spam->second/total_spam;
                prob_ham *= it_ham->second/total_ham;
            }
        }
        //cout << prob_spam << " " << prob_ham << endl;

        if(type == "spam") real_spam++;
        else if(type == "ham") real_ham++;

        if(prob_spam > prob_ham) found_spam++;
        else if(prob_ham > prob_spam) found_ham++;
        else no_class++;

        if(prob_spam != 1)
            cout << "Correo " << i << ", probabilidad de ser spam = " << prob_spam << endl;
        else
            cout << "Correo " << i << ", no se puede clasificar." << endl;
    }

    cout << endl << "Correos spam ingresados: " << real_spam << endl;
    cout << "Correos spam detectados: " << found_spam << endl;
    cout << "Correos no spam ingresados: " << real_ham << endl;
    cout << "Correos no spam detectados: " << found_ham << endl;
    cout << "Correos sin clasificar " << no_class << endl;

    return 0;
}

void training(char* filename,map<string,double>& map_Spam,int &total_spam, map<string,double>& map_Ham, int &total_ham, vector<string> &prueba){
    string lineaux, type, word;
    ifstream train;
    int rows, cols, scale;

    int n=0;

    train.open(filename);
    if(train.is_open()){

        //while(!train.eof()){
        for(int i=0; i<4460; i++){
            getline(train,lineaux);
            cleanLine(lineaux);
            stringstream line(lineaux);
            line >> type;
            //cout << line << endl;

            if(type == "spam"){
                while(line >> word){
                    total_spam++;
                    map_Spam[word]++;
                }
            }
            else if(type == "ham"){
                while(line >> word){
                    total_ham++;
                    map_Ham[word]++;
                }
            }
        }

        while(!train.eof()){
            getline(train,lineaux);
            cleanLine(lineaux);
            prueba.push_back(lineaux);
        }

        /*map<string,double>::iterator It;
        for(It =map_Spam.begin(); It != map_Spam.end(); It++){
            cout << It->first << " " << It->second << endl;
        }*/

    }
    else
        cout << "ERROR: no se pudo abrir el archivo." << endl;
    train.close();

}

void cleanLine(string &line){
    int tamLine = line.length();

    for(int i=0; i<tamLine; i++){
        if(line[i] == '.' or line[i] == ',' or line[i] == '?' or line[i] == ';' or line[i] == '?'
        or line[i] == ':' or line[i] == '!' or line[i] == '*' or line[i] == '+' or line[i] == '-'
        or line[i] == '\'' or line[i] == '#' or line[i] == '&' or line[i] == '~' or line[i] == '{'
        or line[i] == '(' or line[i] == '_' or line[i] == '\\' or line[i] == '@' or line[i] == ')'
        or line[i] == ']' or line[i] == '}' or line[i] == '/' or line[i] == '"')

        line[i] = ' ';
    }
}
