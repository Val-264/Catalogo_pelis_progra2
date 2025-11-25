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
        string resenas[TAM*2];
        int anio;
        float puntuacion;
    public:

    void menuUsuAaio(){
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
        


//Funcion para mostrar las peliculas mejor valoradas

    
    void PelMejoresVal(){
        ifstream archivo("catalogo.txt");
        

        if (!archivo.is_open()) {
            cout << "No se puede abrir el catalogo\n";
            return;
        }

    }

    void buscarPeliculas(){
        int opc1;
 
        do{
            cout << " MENU DE BUSQUEDA \n";
            cout << " 0. Salir del menu de busqueda\n ";
            cout << " 1. Buscar por genero\n ";
            cout << " 2. Buscar por titulo\n ";//buscar por anio
            cout << " Selecciona tu opcion... ";
            cin >> opc1;
        } while (opc1 !=0);

        switch (opc1)   {
            case 1: //´pedit titulo
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                break;
        }
    }
    //Funciones para las opciones de buscar del menu
    void buscarPorGenero(){
        char generoBuscado[TAM];
        bool encontrado = false;

        cout << "\n Ingresa el genero a buscar: ";
        cin.ignore();
        cin.getline(generoBuscado, TAM);
        
    }
    
    void buscarPorTitulo(){
        char 
    }

    void setResenas(){

    }

    void calificar();



};
