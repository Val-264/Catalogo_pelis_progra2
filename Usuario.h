#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "peliculas.h"
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

        struct Resena{
            char titulo[100];
            char resena[500];
            int aprobada; // 0 = no aprobada, 1 = aprobada
        };
        
    public:
        Control c;

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

            c.limpiarPantalla();

            switch (opc){
            case 1: verCatalogoCom();
                    break;
            case 2: PelMejoresVal();
                    break;
            case 3: setResenas();
                    break;
            case 4: calificar();
                    break;
            case 5: buscarPeliculas();
                    break;                 
            default:
                break;
            }
        } while (opc!=6);
        
    }

    //Funciones del usuario
    void verCatalogoCom(){
        c.limpiarPantalla();
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
        c.limpiarPantalla();
        Pelicula p;
        ifstream archivo("catalogo.dat", ios::binary );
        
        if (!archivo.is_open()) {
            cout << "No se puede abrir el catalogo\n";
            return;
        }

        //vector para almacenar las mejores peliculas
        vector<pair<string, float>> lista;

        //Leer las peliculas 
        while(archivo.read((char*)&p, sizeof(Pelicula))) {
            string titulo = p.getTitulo();
            float puntuacion = p.getPuntuacion();
            
            lista.push_back(make_pair(titulo, puntuacion));
        }
        archivo.close();

        if (lista.empty()) {
        cout << "No hay peliculas registradas.\n";
        return;
        }
        
        //Ordenar la lista de mayor a menor
        sort(lista.begin(), lista.end(), 
            [](const pair<string, float>& a, const pair<string, float>& b) {
            return a.second > b.second;
        }
        );

        //Crear archivo para las mejores peliculas
        ofstream archivoMejores("mejoresPel.dat", ios::binary | ios::trunc);
        if (!archivoMejores.is_open()) {
            cout << "No se pudo crear mejoresPel.dat\n";
            return;
        }

        for(auto &pel : lista ) {
            int tam =pel.first.size();
            archivoMejores.write((char*)&tam, sizeof(int));
            archivoMejores.write(pel.first.c_str(), tam);
            archivoMejores.write((char*)&pel.second, sizeof(float));
        }
        archivoMejores.close();

        //Mostrar las mejores peliculas
        cout << "\n--- MEJORES PELICULAS ---\n";
        for (auto &pel : lista) {
            cout << "-----------------------------\n";
            cout << "Titulo: " << pel.first << "\n";
            cout << "Puntuacion: " << pel.second << "\n";
        }
        cout << "-----------------------------\n";
    }
        
    void buscarPeliculas(){
        int opc1;
        Pelicula p;
        c.limpiarPantalla();
 
        do{
            cout << " MENU DE BUSQUEDA \n";
            cout << " 0. Salir del menu de busqueda\n ";
            cout << " 1. Buscar por genero\n ";
            cout << " 2. Buscar por titulo\n ";
            cout << " 3. Buscar por anio\n ";
            cout << " Selecciona tu opcion... ";
            cin >> opc1;

            c.limpiarPantalla();
        
            switch (opc1)   {
                case 1: {
                        char generoBuscado[TAM];
                        cout << "Genero buscado: ";
                        cin.ignore();
                        cin.getline(generoBuscado,TAM);
                        c.dar_formato_a_cadenas(generoBuscado);
                        buscarPorGenero(generoBuscado);
                        break;
                        }
                case 2: {
                        char tituloBuscado[TAM];
                        cout <<"Titulo buscado: ";
                        cin.ignore();
                        cin.getline(tituloBuscado,TAM);
                        c.dar_formato_a_cadenas(tituloBuscado);
                        buscarPorTitulo(tituloBuscado);
                        break;
                        }
                case 3: {
                        float anio;
                        int anioBuscado;
                        do {
                            cout << "\n Ingresa el anio a buscar: ";
                            cin >> anio; 
                            // Verificar entrada válida
		                    if(cin.fail()){ // Si la entrada no es un numero
		                        cin.clear(); // Limpiar estado de error de cin
		                        cin.ignore(1000,'\n'); // Descartar la entrada incorrecta hasta mil caracteres o hasta encontrar un salto de linea
                                anioBuscado=500;
                            }
		                    else if(fmod(anio,1)!=0) anioBuscado=500; // Descartar numeros con decimales
		                    else anioBuscado=static_cast<int>(anio); // Convertir entrada a enteros si es válida
                            if (anioBuscado < 1888) {
                                cout << "\nAnio no valido\n";
                                c.limpiarPantalla();
                            }
                        } while(anioBuscado < 1888);
                        buscarPorAnio(anioBuscado);
                        break;
                        }   
                    default: cout<< "\nOpcion invalida\n";
                            break;
            }        
        }while (opc1 !=0); 
    }

    //Funciones para las opciones de buscar del menu
    void buscarPorGenero(char* generoBuscado){
        bool encontrado = false;

        ifstream archivo("catalogo.dat", ios::binary);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo.\n";
            return;
        }

        Pelicula p;
        while (archivo.read((char*)&p, sizeof(Pelicula))) {
            if (strcmp(p.getGenero(), generoBuscado) == 0) {
                encontrado = true;
                cout << "\n----- PELICULA ENCONTRADA -----\n";
                cout << "Titulo: " << p.getTitulo() << "\n";
                cout << "Director: " << p.getDirector() << "\n";
                cout << "Año: " << p.getAnio() << "\n";
                cout << "Puntuacion: " << p.getPuntuacion() << "\n";
            }
        }

        if (!encontrado){
            cout << "\nNo se encontraron peliculas con ese genero.\n";
        }
        archivo.close();        
    }
    
    void buscarPorTitulo(char* tituloBuscado){
        bool encontrado = false;

        ifstream archivo("catalogo.dat", ios::binary);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo.\n";
            return;
        }

        Pelicula p;
        while (archivo.read((char*)&p, sizeof(Pelicula))) {
            if (strcmp(p.getTitulo(), tituloBuscado) == 0) {
                encontrado = true;
                cout << "\n----- PELICULA ENCONTRADA -----\n";
                cout << "Titulo: " << p.getTitulo() << "\n";
                cout << "Director: " << p.getDirector() << "\n";
                cout << "Genero: " << p.getGenero() << "\n";
                cout << "Año: " << p.getAnio() << "\n";
                cout << "Puntuacion: " << p.getPuntuacion() << "\n";
            }
        }

        if (!encontrado)
            cout << "\nNo se encontro la pelicula con ese titulo.\n";

        archivo.close();
         
    }

    void buscarPorAnio(int anioBuscado){
        bool encontrado = false;

        ifstream archivo("catalogo.dat", ios::binary);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo.\n";
            return;
        }

        Pelicula p;
        while (archivo.read((char*)&p, sizeof(Pelicula))) {
            if (p.getAnio() == anioBuscado) {
                encontrado = true;
                cout << "\n----- PELICULA ENCONTRADA -----\n";
                cout << "Titulo: " << p.getTitulo() << "\n";
                cout << "Director: " << p.getDirector() << "\n";
                cout << "Genero: " << p.getGenero() << "\n";
                cout << "Puntuacion: " << p.getPuntuacion() << "\n";
            }
        }

        if (!encontrado)
            cout << "\nNo se encontraron peliculas de ese año.\n";

        archivo.close();
    }

    void setResenas(){
        c.limpiarPantalla();
        Resena r;
        r.aprobada = 0; // Inicia no aprobada
        fstream file("resenas.dat", ios::binary | ios::out | ios::app);
        if (!file.is_open()) {
            cout << "No se pudo abrir el archivo de reseñas.\n";
            return;
        }

        cout << "\n Ingresa el titulo de la pelicula para la resena: ";
        cin.ignore();
        cin.getline(r.titulo, 100);
        cout << "Escribe la resena: ";
        cin.getline(r.resena, 500);

        file.write(reinterpret_cast<char*>(&r), sizeof(Resena));
        file.close();

        cout << "\n Resena enviada y pendiente de aprobacion.\n"; 
    }

    void calificar(){
        c.limpiarPantalla();
        char tituloCalificar[TAM];
        bool encontrado = false;
        float nuevaCalif;

        cout << "\n Ingresa el titulo de la pelicula: ";
        cin.ignore();
        cin.getline(tituloCalificar, TAM);

        cout << "Ingresa tu calificacion (0 a 10): ";
        cin >> nuevaCalif;

        fstream archivo("catalogo.dat", ios::binary | ios::in | ios::out);
        if (!archivo.is_open()) {
            cout << "Error al abrir archivo.\n";
            return;
        }

        Pelicula p;
        while (archivo.read((char*)&p, sizeof(Pelicula))) {
            if (strcmp(p.getTitulo(), tituloCalificar) == 0) {
                encontrado = true;

                float prom = (p.getPuntuacion() + nuevaCalif) / 2;
                p.setPuntuacion(prom);

                archivo.seekp(-sizeof(Pelicula), ios::cur);
                archivo.write((char*)&p, sizeof(Pelicula));

                cout << "\nCalificacion guardada.\n";
                break;
            }
        }

        if (!encontrado)
            cout << "\nNo se encontro la pelicula.\n";

        archivo.close();
    }
 
};








#endif
