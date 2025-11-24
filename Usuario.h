#include <iostream>
#include <fstream>
#include <string>
#include"peliculas.h"
using namespace std;

class Usuarios{
    private: 
        char claveUsuario[12];
        char titulo[TAM];
        char director[TAM];
        char genero[TAM];
        char sinopsis[TAM*2];
        int anio;
        float puntuacion;
    public:

    void menuUsuario(){
        int opc;
        do  {
            cout << " --MENU DE USUARIO--  \n";
            cout << "1. Ver catalogo de peliculas completo\n";
            cout << "2. Ver peliculas mejor valoradas\n";
            cout << "3. Agregar Resena a una pelicula\n";
            cout << "4. Calificar pelicula\n";
            cout << "5. Buscar pelicula\n";
            cout << "6. Salir\n";
            cout << "   Selecciona una opcion...    \n";
            cin>>opc;

            switch (opc)
            {
            case 1: 
                break;
            
            default:
                break;
            }
        } while (opc!=6);
        
    }
    //Funciones del usuario
    void verCatalogoCom(){
        ifstream archivo("catalogo.dat", ios::binary);
        string linea;
        Pelicula p;

        if (!archivo.is_open()) {
            cout << "No se puede abrir el catalogo\n";
            return;
        }
        cout << "\n -CATALOGO COMPLETO- \n";

        while (archivo.read((char*)&p, sizeof(Pelicula)))  {
            cout << "--------------------------------\n";
            cout << "Titulo: " << p.getTitulo() << "\n";
            cout << "Director: " << p.getDirector() << "\n";
            cout << "Genero: " << p.getGenero() << "\n";
            cout << "Anio: " << p.getAnio() << "\n";
            cout << "Puntuacion: " << p.getPuntuacion() << "\n";
            cout << "--------------------------------\n";
        }

        archivo.close();
    }
        

    
    void PelMejoresVal(){
        ifstream archivo("catalogo.txt");
        

        if (!archivo.is_open()) {
            cout << "No se puede abrir el catalogo\n";
            return;
        }

    }


    void buscarPeliculas(){
        int opc1;
        ifstream archivo("catalogo.txt");
        

        if (!archivo.is_open()) {
            cout << "No se puede abrir el catalogo\n";
            return;
        }



        do{
            cout << " MENU DE BUSQUEDA \n";
            cout << " 1. Buscar por genero\n ";
            cout << " 2. Buscar por anio\n ";
            cout << " 3. Buscar por titulo\n ";
            cout << " 4. Salir del menu de busqueda\n ";
            cout << " Selecciona tu opcion... ";
            cin >> opc1;
        } while (opc1 !=3);

        
    }
    void setResenas(){

    }

    void calificar();



};
