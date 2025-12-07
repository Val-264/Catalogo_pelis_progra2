#ifndef PELICULAS_H
#define PELICULAS_H

#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <windows.h> // Para colores 
#include "control.h"
using namespace std;

#define TOT_PELIS 1000
const int anioMinimo = 1888; // La primer película se grabó en 1888, por lo tanto el año mínimo para una película debe ser 1888

        //-----------NOMBRES DE LOS ARCHIVOS-----------
        // char catalogo[13] = "catalogo.dat";
        // char tempBin[9] = "temp.dat"; // Para cuando borren una pelicula 

class Pelicula{
    private:
        char titulo[TAM];
        char director[TAM];
        char genero[TAM];
        int anio;
        float puntuacion;                
    public: 

        Pelicula(){}
        Pelicula(const char* t, const char*dir, const char*gen, int aa, int punt){
            strcpy(titulo,t);
            strcpy(director,dir);
            strcpy(genero,gen);
            anio=aa;
            puntuacion = punt;
        }

        void setSinopsis(const char* tituloSinopsis);
        void getSinopsis(char* tituloSinopsis);

        //-----------CASCARONES PARA LOS ARCHIVOS BINARIOS-----------
        void cascaronBinario(char* archivo);

        //-----------FUNCIONES-----------
        void setTitulo(char *t){ strcpy(titulo, t); }
        void setDirector(char *d){ strcpy(director, d); }
        void setGenero(char *g){ strcpy(genero, g); }
        void setAnio(int a){ anio = a; }
        void setPuntuacion(float p){ puntuacion = p; }

        const char* getTitulo() const {return titulo;}
        const char* getDirector() const {return director;}
        const char* getGenero() const { return genero; }
        const int getAnio() const { return anio; }
        const float getPuntuacion() const { return puntuacion; }

        void elegirGeneros(char* retonro);

        bool catalogoVacio(); // Verificar si el catalogo está vacío 

        void generarPelMejoresVal(); // Generar archivo de peliculas mejor valoradas

        

};

void Pelicula::cascaronBinario(char* archivo){
    fstream peliculas;

    peliculas.open(archivo, ios::binary | ios::out | ios::trunc);

    if (!peliculas) {
        peliculas.close();
        cerr << "\nNo se pudo abrir el archivo de catalogo\n";
        return; 
    }

    Pelicula vacio("sin nombre", "sin director", "sin genero", 0, 0); 

    for (int i = 0; i < TOT_PELIS; i++) {
        peliculas.write(reinterpret_cast<char*> (&vacio), sizeof(Pelicula));
    }

    peliculas.close();
}

void Pelicula::setSinopsis(const char* tituloSinopsis){
    fstream sps;
    char sinopsis[TAM * 2];

    char tituloSps[TAM];
    strcpy(tituloSps, tituloSinopsis);
    strcat(tituloSps,".txt");

    sps.open(tituloSps, ios::out | ios::trunc);

    if(!sps) {
        sps.close();
        cerr << "No se pudo abrir el archivo para agregar sinopsis";
        return;
    }
    
    cin.ignore();
    cout << "Sinopsis de la pelicula " << tituloSinopsis << ": ";
    cin.getline(sinopsis,TAM);

    sps << sinopsis;

    sps.close();
}

void Pelicula::getSinopsis(char* tituloSinopsis){
    fstream sps;

    strcat(tituloSinopsis,".txt");

    sps.open(tituloSinopsis, ios::in);

    if(!sps) {
        sps.close();
        cerr << "No se pudo abrir el archivo para leer la sinopsis";
        return;
    }

    stringstream buffer;
    buffer << sps.rdbuf();
    string contenido = buffer.str();

    cout << "\n--------SINOPSIS--------\n";
    cout << contenido;

    sps.close();
}

void Pelicula::elegirGeneros(char* retorno){ // Si llamada = 0 es del administrador, si llamada = 1es del usuario
    Contadores c;

    float opc;
    int opcion; 

    bool correcta = false;

    do {
        int i=1;
        cout << "-----GENEROS-----";
        for(auto& g: c.generos) {
        cout << "\n" << i << "-" << g; i++;
        } 
        cout << "\n8- Otro";
        cout << "\nElige un genero: "; 
        cin >> opc;
        // Verificar entrada válida
		if (cin.fail()){ // Si la entrada no es un numero
			cin.clear(); // Limpiar estado de error de cin
			cin.ignore(1000,'\n'); // Descartar la entrada incorrecta hasta mil caracteres o hasta encontrar un salto de linea
            opcion=500;
            cout << "\nOpcion invalida\n";
            c.limpiarPantalla();
        }
		else if (fmod(opc,1)!=0) { // Descartar numeros con decimales
            opcion=500; 
            cout << "\nOpcion invalida\n";
            c.limpiarPantalla();
        }
		else {
            opcion=static_cast<int>(opc); // Convertir entrada a enteros si es válida
            correcta = true;
        }

    } while(!correcta);

    switch(opcion){
        case 1: strcpy(retorno, c.generos[0]); 
                c.setContadores((char*)"Total", c.generos[0], INCREMENTAR);
                break;
        case 2: strcpy(retorno, c.generos[1]); 
                c.setContadores((char*)"Total", c.generos[1], INCREMENTAR);
                break;
        case 3: strcpy(retorno, c.generos[2]); 
                c.setContadores((char*)"Total", c.generos[2], INCREMENTAR);
                break;
        case 4: strcpy(retorno, c.generos[3]); 
                c.setContadores((char*)"Total", c.generos[3], INCREMENTAR);
                break;
        case 5: strcpy(retorno, c.generos[4]); 
                c.setContadores((char*)"Total", c.generos[4], INCREMENTAR);
                break;
        case 6: strcpy(retorno, c.generos[5]); 
                c.setContadores((char*)"Total", c.generos[5], INCREMENTAR);
                break;
        case 7: strcpy(retorno, c.generos[6]); 
                c.setContadores((char*)"Total", c.generos[6], INCREMENTAR);
                break;
        case 8: strcpy(retorno, "No disponible"); 
                c.setContadores((char*)"Total", (char*)"Otros", INCREMENTAR);
                break;
    }
}

bool Pelicula::catalogoVacio() {

    fstream peliculas;

    peliculas.open("catalogo.dat", ios::binary | ios::in); // Abrir archivo para lectura 

    if (!peliculas) {
        peliculas.close();
        return true;
    }
    peliculas.close();
    return false;
}

//Funcion para generar las peliculas mejor valoradas

void Pelicula::generarPelMejoresVal(){
    fstream catalogo, mejores;
    catalogo.open("catalogo.dat", ios::binary | ios::in);
    mejores.open("mejorValoradas.dat", ios::binary | ios::out | ios::trunc);
    
    Pelicula p;
    if (!catalogo.is_open() || !mejores.is_open()) {
        cout << "No se puede abrir uno de los archivos\n";
        return;
    }

    vector <Pelicula> peliculas;

}     

#endif