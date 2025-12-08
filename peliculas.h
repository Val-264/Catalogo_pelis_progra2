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
        struct Resena {
            char titulo[100];
            char resena[500];
            int aprobada; // 0=no aprobada, 1=aprobada
        };

        void setSinopsis(const char* tituloSinopsis);
        void getSinopsis(const char* tituloSinopsis);

        //-----------CASCARONES PARA LOS ARCHIVOS BINARIOS-----------
        void cascaronBinario(char* archivo);
        void cascaronResenas(char* archivoResenas);

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
        int elegirTitulos(char* tituloPeli);
        void verTitulos_anio();

        bool catalogoVacio(); // Verificar si el catalogo está vacío 
        bool catalogoExistente(); // Verificar si se ha creado un catalogo

        void generarPelMejoresVal(); // Generar archivo de peliculas mejor valoradas

        

};

void Pelicula::cascaronBinario(char* archivo){
    fstream peliculas;

    peliculas.open(archivo, ios::binary | ios::out | ios::trunc);

    if (!peliculas) {
        peliculas.close();
        SetConsoleTextAttribute(hConsole, ROJO);
        cerr << "\nNo se pudo abrir el archivo de catalogo\n";
        SetConsoleTextAttribute(hConsole, BLANCO);
        return; 
    }

    Pelicula vacio("sin nombre", "sin director", "sin genero", 0, 0); 

    for (int i = 0; i < TOT_PELIS; i++) {
        peliculas.write(reinterpret_cast<char*> (&vacio), sizeof(Pelicula));
    }

    peliculas.close();
}

void Pelicula::cascaronResenas(char* archivoResenas){
    fstream resenas;

    resenas.open(archivoResenas, ios::binary | ios::out | ios::trunc);

    if (!resenas) {
        resenas.close();
        cerr << "\nNo se pudo abrir el archivo de reseñas\n";
        return; 
    }

    Resena rVacia;
    rVacia.aprobada = 0;
    strcpy(rVacia.titulo, " ");
    strcpy(rVacia.resena, " ");

    for (int i = 0; i < TOT_PELIS; i++) {
        resenas.write(reinterpret_cast<char*> (&rVacia), sizeof(Resena));
    }

    resenas.close();
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
        SetConsoleTextAttribute(hConsole, ROJO);
        cerr << "No se pudo abrir el archivo para agregar sinopsis";
        SetConsoleTextAttribute(hConsole, BLANCO);
        return;
    }
    
    cin.ignore();
    cout << "Sinopsis de la pelicula " << tituloSinopsis << ": ";
    cin.getline(sinopsis,TAM);

    sps << sinopsis;

    sps.close();
}

void Pelicula::getSinopsis(const char* tituloSinopsis){
    fstream sps;
    char titSps[TAM];
    strcpy(titSps, tituloSinopsis);
    strcat(titSps,".txt");

    sps.open(titSps, ios::in);

    if(!sps) {
        sps.close();
        SetConsoleTextAttribute(hConsole, ROJO);
        cerr << "No se pudo abrir el archivo para leer la sinopsis";
        SetConsoleTextAttribute(hConsole, BLANCO);
        return;
    }

    stringstream buffer;
    buffer << sps.rdbuf();
    string contenido = buffer.str();

    cout << "\nSinopsis:\n";
    cout << contenido;

    sps.close();
}

void Pelicula::elegirGeneros(char* retorno){ // Si llamada = 0 es del administrador, si llamada = 1es del usuario
    Control c;

    float opc;
    int opcion; 

    bool correcta = false;

    do {
        int i=1;
        SetConsoleTextAttribute(hConsole, CIAN);
        cout << "-----GENEROS-----";
        SetConsoleTextAttribute(hConsole, BLANCO);
        for(auto& g: c.generos) {
        cout << "\n" << i << "-" << g; i++;
        } 
        cout << "\nElige un genero: "; 
        cin >> opc;
        // Verificar entrada válida
		if (cin.fail()){ // Si la entrada no es un numero
			cin.clear(); // Limpiar estado de error de cin
			cin.ignore(1000,'\n'); // Descartar la entrada incorrecta hasta mil caracteres o hasta encontrar un salto de linea
            opcion=500;
            SetConsoleTextAttribute(hConsole, ROJO);
            cout << "\nOpcion invalida\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
            c.limpiarPantalla();
        }
		else if (fmod(opc,1)!=0) { // Descartar numeros con decimales
            opcion=500; 
            SetConsoleTextAttribute(hConsole, ROJO);
            cout << "\nOpcion invalida\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
            c.limpiarPantalla();
        }
		else {
            opcion=static_cast<int>(opc); // Convertir entrada a enteros si es válida
            correcta = true;
        }

    } while(!correcta);

    switch(opcion){
        case 1: strcpy(retorno, c.generos[0]); break;
        case 2: strcpy(retorno, c.generos[1]); break;
        case 3: strcpy(retorno, c.generos[2]); break;
        case 4: strcpy(retorno, c.generos[3]); break;
        case 5: strcpy(retorno, c.generos[4]); break;
        case 6: strcpy(retorno, c.generos[5]); break;
        case 7: strcpy(retorno, c.generos[6]); break;
        case 8: strcpy(retorno, c.generos[7]); break;
    }
}

int Pelicula::elegirTitulos(char* tituloPeli) {
    fstream catalogo;
    Pelicula p;
    Control c;
    float ind;
    int indice = 0, cont = 1;
    bool indiceValido = false;

    // Abrir archivo para lectura 
    catalogo.open("catalogo.dat", ios::binary | ios::in);

    if (!catalogo) {
        SetConsoleTextAttribute(hConsole, ROJO);
        cerr << "No se pudo abrir el catalogo\n";
        SetConsoleTextAttribute(hConsole, BLANCO);
        return 0;
    }

    int totalPelis = c.getContador((char*)"Total");
    if (totalPelis <= 0) {
        cout << "No hay peliculas en el catalogo.\n";
        catalogo.close();
        return 0;
    }

    do {
        SetConsoleTextAttribute(hConsole, CIAN);
        cout << "\n-----TITULOS DISPONIBLES-----\n";
        SetConsoleTextAttribute(hConsole, BLANCO);
        for (int i = 0; i < totalPelis; i++) {
            catalogo.seekg(i * sizeof(Pelicula));
            catalogo.read(reinterpret_cast<char*>(&p), sizeof(Pelicula));
            if (p.getAnio() != 0) {
                cout << cont << "- " << p.getTitulo() << "\n";
                cont++;
            }
        }
        
        cout << "\nNumero de la pelicula a elegir: ";
        cin >> ind;
        
        // Verificar entrada válida
		if (cin.fail()){ // Si la entrada no es un numero
			cin.clear(); // Limpiar estado de error de cin
			cin.ignore(1000,'\n'); // Descartar la entrada incorrecta hasta mil caracteres o hasta encontrar un salto de linea
            SetConsoleTextAttribute(hConsole, ROJO);
            cout << "\nOpcion invalida\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
        }
		else if (fmod(ind,1)!=0) { // Descartar numeros con decimales
            SetConsoleTextAttribute(hConsole, ROJO);
            cout << "\nOpcion invalida\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
        }
        else if(ind < 1 || ind > totalPelis) { // Si esta fuera de rango 
            SetConsoleTextAttribute(hConsole, ROJO);
            cout << "\nOpcion invalida\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
        }
		else { // Convertir entrada a enteros si es válida
            indice = static_cast<int>(ind);
            indiceValido = true;
        }
        cont = 1;
        c.limpiarPantalla();
    } while (!indiceValido);

    // Copiar el nombre de la pelicula 
    // Posicionarse dentro del archivo binario 
    catalogo.seekg((indice - 1) * sizeof(Pelicula)); 
    catalogo.read(reinterpret_cast<char*>(&p), sizeof(Pelicula));
    strcpy(tituloPeli, p.getTitulo());

    catalogo.close();
    return indice;
}

void Pelicula::verTitulos_anio() {
    fstream catalogo;
    Pelicula p;
    Control c;

    // Abrir archivo para lectura 
    catalogo.open("catalogo.dat", ios::binary | ios::in);

    if (!catalogo) {
        SetConsoleTextAttribute(hConsole, ROJO);
        cerr << "No se pudo abrir el catalogo para ver los titulos\n";
        SetConsoleTextAttribute(hConsole, BLANCO);
        return;
    }

    int totalPelis = c.getContador((char*)"Total");
    if (totalPelis <= 0) {
        cout << "No hay peliculas en el catalogo.\n";
        catalogo.close();
        return;
    }

    for (int i = 0; i < totalPelis; i++) {
        catalogo.seekg(i * sizeof(Pelicula));
        catalogo.read(reinterpret_cast<char*>(&p), sizeof(Pelicula));
        if (p.getAnio() != 0) {
            cout << "- " << p.getTitulo() << " | " << p.getAnio() << "\n";
        }
    }

    catalogo.close();

}

bool Pelicula::catalogoVacio() {
    Control c;
    int totPelis = c.getContador((char*)"Total");
    if (totPelis < 1) return true;
    return false;
}

bool Pelicula::catalogoExistente() {
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
        SetConsoleTextAttribute(hConsole, ROJO);
        cout << "No se puede abrir uno de los archivos\n";
        SetConsoleTextAttribute(hConsole, BLANCO);
        return;
    }

    vector <Pelicula> peliculas;

}     

#endif