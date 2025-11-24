#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
using namespace std;

#define TAM 500
#define TOT_PELIS 1000

class Pelicula{
    private:
        char titulo[TAM];
        char director[TAM];
        char genero[TAM];
        char sinopsis[TAM*2];
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

        void setSinopsis(char* tituloSinopsis, Pelicula nuevo);
        void getSinopsis(char* tituloSinopsis, Pelicula nuevo);

        //-----------NOMBRES DE LOS ARCHIVOS-----------
        char catalogo[13] = "catalogo.dat";
        char tempBin[9] = "temp.dat"; // Para cuando borren una pelicula 

        //-----------CASCARONES PARA LOS ARCHIVOS BINARIOS-----------
        void cascaronesBinarios();

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
        char generos[7][TAM] = {"Drama", "Accion", "Romance", "Comedia", "Ciencia ficcion", "Terror", "Fantasia"};


        bool catalogoVacio(); // Verificar si el catalogo está vacío 

        //-----------CONTADORES DE PELICULAS-----------
        static int totPeliculas; // total de peliculas

        // Contador de peliculas por genero
        static int totDrama;
        static int totAccion;
        static int totRomance;
        static int totComedia;
        static int totCienciaFiccion;
        static int totTerror;
        static int totFantasia;
        static int totOtros;    // Otros se pone como genero "no disponible"

        static int getTotPeliculas(){return totPeliculas;}
        static int getTotDrama(){return totDrama;}
        static int getTotAccion(){return totAccion;}
        static int getTotRomance(){return totRomance;}
        static int getTotComedia(){return totComedia;}
        static int getTotCienciaFiccion(){return totCienciaFiccion;}
        static int getTotTerror(){return totTerror;}
        static int getTotFantasia(){return totFantasia;}
        static int getTotOtros(){return totOtros;}
};

int Pelicula::totPeliculas = 0;
int Pelicula::totDrama  = 0;
int Pelicula::totAccion  = 0;
int Pelicula::totRomance  = 0;
int Pelicula::totComedia = 0;
int Pelicula::totCienciaFiccion = 0;
int Pelicula::totTerror = 0;
int Pelicula::totFantasia = 0;
int Pelicula::totOtros = 0;    

void Pelicula::cascaronesBinarios(){
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

void Pelicula::setSinopsis(char* tituloSinopsis, Pelicula nuevo){
    fstream sps;

    sps.open(tituloSinopsis, ios::out | ios::trunc);

    if(!sps) {
        sps.close();
        cerr << "No se pudo abrir el archivo para agregar sinopsis";
        return;
    }

    cout << "Sinopsis de la pelicula " << tituloSinopsis << ": ";
    cin.getline(nuevo.sinopsis,TAM);

    strcat(tituloSinopsis,".txt");

    sps << nuevo.sinopsis;

    sps.close();
}

void Pelicula::getSinopsis(char* tituloSinopsis, Pelicula nuevo){
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

    float opc;
    int opcion; 

    int i=1;
    cout << "Generos de pelicula";
    for(auto& g: generos) {
        cout << "\n" << i << "-" << g; i++;
    } 
    cout << "\n8- Otro";
    cin >> opc;

    // Para administrador: asignar un genero a una pelicula  
    if(llamada == 0) {
        switch(opcion){
            case 1: strcmp(retorno,generos[0]); 
                    totDrama++;
                    break;
            case 2: strcmp(retorno, generos[1]); 
                    totAccion++;
                    break;
            case 3: strcmp(retorno, generos[2]); 
                    totRomance++;
                    break;
            case 4: strcmp(retorno, generos[3]); 
                    totComedia++;
                    break;
            case 5: strcmp(retorno, generos[4]); 
                    totCienciaFiccion++;
                    break;
            case 6: strcmp(retorno, generos[5]); 
                    totTerror++;
                    break;
            case 7: strcmp(retorno, generos[6]); 
                    totFantasia++;
                    break;
            case 8: strcmp(retorno, "No disponible"); 
                    totOtros++;
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

        