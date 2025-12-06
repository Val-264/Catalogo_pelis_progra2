#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
#include<vector>
#include "contador.h"
using namespace std;

#define TAM 500
#define TOT_PELIS 1000

class Pelicula{
    private:
        char titulo[TAM];
        char director[TAM];
        char genero[TAM];
        int anio;
        float puntuacion;                
    public: 

        Pelicula(){}
        Pelicula(char* t, char*dir, char*gen, int aa, int punt){
            strcpy(titulo,t);
            strcpy(director,dir);
            strcpy(genero,gen);
            anio=aa;
            puntuacion = punt;
        }

        void setSinopsis(char* tituloSinopsis);
        void getSinopsis(char* tituloSinopsis);

        //-----------NOMBRES DE LOS ARCHIVOS-----------
        char catalogo[13] = "catalogo.dat";
        char tempBin[9] = "temp.dat"; // Para cuando borren una pelicula 

        //-----------CASCARONES PARA LOS ARCHIVOS BINARIOS-----------
        void cascaronCatalogo();

        //-----------FUNCIONES-----------
        void setTitulo(char *t){ strcpy(titulo, t); }
        void setDirector(char *d){ strcpy(director, d); }
        void setGenero(char *g){ strcpy(genero, g); }
        void setAnio(int a){ anio = a; }
        void setPuntuacion(float p){ puntuacion = p; }

        char* getTitulo(){return titulo;}
        char* getDirector(){return director;}
        char* getGenero(){ return genero; }
        int getAnio(){ return anio; }
        float getPuntuacion(){ return puntuacion; }

        char* elegirGeneros(int llamada);

        bool catalogoVacio(); // Verificar si el catalogo está vacío 

        void generarPelMejoresVal(); // Generar archivo de peliculas mejor valoradas

        const int anioMinimo = 1888; // La primer película se grabó en 1888, por lo tanto el año mínimo para una película debe ser 1888
};

void Pelicula::cascaronCatalogo(){
    fstream peliculas;

    peliculas.open(catalogo, ios::binary | ios::out | ios::trunc);

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

void Pelicula::setSinopsis(char* tituloSinopsis){
    fstream sps;
    char sinopsis[TAM * 2];

    sps.open(tituloSinopsis, ios::out | ios::trunc);

    if(!sps) {
        sps.close();
        cerr << "No se pudo abrir el archivo para agregar sinopsis";
        return;
    }

    cout << "Sinopsis de la pelicula " << tituloSinopsis << ": ";
    cin.getline(sinopsis,TAM);

    strcat(tituloSinopsis,".txt");

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

char* Pelicula::elegirGeneros(int llamada){ // Si llamada = 0 es del administrador, si llamada = 1es del usuario
    char retorno[TAM];
    char otro[TAM];
    Contadores c;

    float opc;
    int opcion; 

    int i=1;
    cout << "Generos de pelicula";
    for(auto& g: c.generos) {
        cout << "\n" << i << "-" << g; i++;
    } 
    cout << "\n8- Otro";
    cin >> opc;

    // Para administrador: asignar un genero a una pelicula  
    if(llamada == 0) {
        switch(opcion){
            case 1: strcmp(retorno, c.generos[0]); 
                    c.setContadores("Total", c.generos[0]);
                    break;
            case 2: strcmp(retorno, c.generos[1]); 
                    c.setContadores("Total", c.generos[1]);
                    break;
            case 3: strcmp(retorno, c.generos[2]); 
                    c.setContadores("Total", c.generos[2]);
                    break;
            case 4: strcmp(retorno, c.generos[3]); 
                    c.setContadores("Total", c.generos[3]);
                    break;
            case 5: strcmp(retorno, c.generos[4]); 
                    c.setContadores("Total", c.generos[4]);
                    break;
            case 6: strcmp(retorno, c.generos[5]); 
                    c.setContadores("Total", c.generos[5]);
                    break;
            case 7: strcmp(retorno, c.generos[6]); 
                    c.setContadores("Total", c.generos[6]);
                    break;
            case 8: strcmp(retorno, "No disponible"); 
                    c.setContadores("Total", "Otros");
                    break;
        }
    }

    // Para usuario: elegir un genro para buscar 
    else {

    }

    return retorno;
}


bool Pelicula::catalogoVacio() {
    bool vacio;

    fstream peliculas;

    peliculas.open(catalogo, ios::binary | ios::in); // Abrir archivo para lectura 

    if (!peliculas) {
        peliculas.close();
        cerr << "No se pudo abrir el catalogo para verificar si está vacío";
        return;
    }

    Pelicula registro;

    for (int i = 0; i < TOT_PELIS; i++) {
        // Posicionarse en una localidad
        peliculas.seekg(i*sizeof(Pelicula));

        // extraer la cantidad bytes de sizeof y colocarlo en el registro 
        peliculas.read(reinterpret_cast<char*>(&registro), sizeof(Pelicula));

        // Los años tienen que ser mínimo 1888, por lo tanto no son 0
        if(registro.getAnio() != 0) {
           peliculas.close();
           return false; 
        }
    }

    peliculas.close();

    return true;
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