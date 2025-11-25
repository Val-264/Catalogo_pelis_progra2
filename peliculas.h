#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

#define TAM 500
#define TOT_PELIS 1000

class Pelicula{
    private:
        struct Campos_Pelicula{
            char titulo[TAM];
            char director[TAM];
            char genero[TAM];
            int anio;
            float puntuacion;
        };
        char sinopsis[TAM*2];
        Campos_Pelicula campos;     
    public: 

        Pelicula(){}
        Pelicula(char* t, char*dir, char*gen, int aa, int punt){
            strcpy(campos.titulo,t);
            strcpy(campos.director,dir);
            strcpy(campos.genero,gen);
            campos.anio = aa;
            campos.puntuacion = punt;
        }

        Campos_Pelicula getCamposPelicula() const {return campos;};

        void setSinopsis(char* tituloSinopsis, Pelicula nuevo);
        void getSinopsis(char* tituloSinopsis, Pelicula nuevo);

        //-----------NOMBRES DE LOS ARCHIVOS-----------
        char catalogo[13] = "catalogo.dat";
        char tempBin[9] = "temp.dat"; // Para cuando borren una pelicula 

        //-----------CASCARONES PARA LOS ARCHIVOS BINARIOS-----------
        void cascaronesBinarios();

        //-----------FUNCIONES-----------
        void setTitulo(char *t){ strcpy(campos.titulo, t); }
        void setDirector(char *d){ strcpy(campos.director, d); }
        void setGenero(char *g){ strcpy(campos.genero, g); }
        void setAnio(int a){ campos.anio = a; }
        void setPuntuacion(float p){ campos.puntuacion = p; }

        char* getTitulo() {return campos.titulo;}
        char* getDirector(){return campos.director;}
        char* getGenero(){ return campos.genero; }
        int getAnio(){ return campos.anio; }
        float getPuntuacion(){ return campos.puntuacion; }

        char* elegirGeneros(int llamada);
        char generos[7][TAM] = {"Drama", "Accion", "Romance", "Comedia", "Ciencia ficcion", "Terror", "Fantasia"};


        bool catalogoVacio(); // Verificar si el catalogo está vacío 

        void generarPelMejoresVal(); // Generar archivo de peliculas mejor valoradas

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

        const int anioMinimo = 1888; // La primer película se grabó en 1888, por lo tanto el año mínimo para una película debe ser 1888
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
    cin.getline(nuevo.sinopsis,TAM*2);

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
        bool opc_valida = false;

        float opc;
        int opcion; 

    do{
        int i=1;
        cout << "Generos de pelicula";
        for(auto& g: generos) {
            cout << "\n" << i << "-" << g; i++;
        } 
        cout << "\n8- Otro";
        cin >> opc;
        // Verificar entrada válida
        if(cin.fail()){ // Si la entrada no es un numero
		    cin.clear(); // Limpiar estado de error de cin
			cin.ignore(1000,'\n'); // Descartar la entrada incorrecta hasta mil caracteres o hasta encontrar un salto de linea
            opcion=500;
        }
		else if(fmod(opc,1)!=0) opcion=500; // Descartar numeros con decimales
		else{
             opcion=static_cast<int>(opc); // Convertir entrada a enteros si es válida
             opc_valida = true;
        }
    } while (!opc_valida);    

    // Para administrador: asignar un genero a una pelicula  
    if(llamada == 0) {
        switch(opcion){
            case 1: strcpy(retorno,generos[0]); 
                    totDrama++;
                    break;
            case 2: strcpy(retorno, generos[1]); 
                    totAccion++;
                    break;
            case 3: strcpy(retorno, generos[2]); 
                    totRomance++;
                    break;
            case 4: strcpy(retorno, generos[3]); 
                    totComedia++;
                    break;
            case 5: strcpy(retorno, generos[4]); 
                    totCienciaFiccion++;
                    break;
            case 6: strcpy(retorno, generos[5]); 
                    totTerror++;
                    break;
            case 7: strcpy(retorno, generos[6]); 
                    totFantasia++;
                    break;
            case 8: strcpy(retorno, "No disponible"); 
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
    fstream peliculas;

    peliculas.open(catalogo, ios::binary | ios::in); // Abrir archivo para lectura 

    if (!peliculas) {
        peliculas.close();
        cerr << "No se pudo abrir el catalogo para verificar si está vacío";
        return true;
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