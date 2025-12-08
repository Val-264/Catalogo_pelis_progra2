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
        
    public:
        struct Resena{
            char titulo[100];
            char resena[500];
            int aprobada; // 0 = no aprobada, 1 = aprobada
        };

        Control c;

    void menuUsuario(){
        int opcion;
        float opc;
        do  {
            SetConsoleTextAttribute(hConsole, CIAN);
            cout << " ------MENU DE USUARIO------  \n";
            SetConsoleTextAttribute(hConsole, BLANCO);
            cout << "0- Salir\n";
            cout << "1- Ver catalogo de peliculas completo\n";
            cout << "2- Ver peliculas mejor valoradas\n";
            cout << "3- Agregar Resena a una pelicula\n";
            cout << "4- Calificar pelicula\n";
            cout << "5- Buscar pelicula\n";
            cout << "Elige una opcion: ";
            cin>>opc;

            // Verificar entrada válida
		    if (cin.fail()){ // Si la entrada no es un numero
			    cin.clear(); // Limpiar estado de error de cin
			    cin.ignore(1000,'\n'); // Descartar la entrada incorrecta hasta mil caracteres o hasta encontrar un salto de linea
                opcion=500;
            }
		    else if (fmod(opc,1)!=0) opcion=500; // Descartar numeros con decimales
		    else opcion=static_cast<int>(opc); // Convertir entrada a enteros si es válida


            system("cls");

            switch (opcion){
                case 0: cout << "Saliendo..."; break;
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
                        SetConsoleTextAttribute(hConsole, ROJO);
                        cout << "Opcion invalida\n";
                        SetConsoleTextAttribute(hConsole, BLANCO);
                        c.limpiarPantalla();
                        break;
            }

            system("cls");
        } while (opcion != 0);
        
    }

    //Funciones del usuario
    void verCatalogoCom(){
        string linea;
        Pelicula p;

        if (p.catalogoVacio()) {
            SetConsoleTextAttribute(hConsole, AMARILLO);
            cout << "\nEl catalogo esta vacio\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
            c.limpiarPantalla();
            return;
        }

        ifstream archivo("catalogo.dat", ios::binary);

        if (!archivo.is_open()) {
            cout << "No se puede abrir el catalogo\n";
            return;
        }

        SetConsoleTextAttribute(hConsole, CIAN);
        cout << "\n------CATALOGO COMPLETO------\n";
        SetConsoleTextAttribute(hConsole, BLANCO);

        while (archivo.read((char*)&p, sizeof(Pelicula)))  {
            if (p.getAnio() == 0) break;
            cout << "--------------------------------\n";
            cout << "Titulo: " << p.getTitulo() << "\n";
            cout << "Director: " << p.getDirector() << "\n";
            cout << "Genero: " << p.getGenero() << "\n";
            cout << "Anio: " << p.getAnio() << "\n";
            cout << "Puntuacion: " << p.getPuntuacion() << "\n";
            p.getSinopsis(p.getTitulo());
            cout << "\nResena: ";
            p.mostrarResena(p.getTitulo());
            cout << "--------------------------------\n";
        }

        archivo.close();
        c.limpiarPantalla();
    }
        
//Funcion para mostrar las peliculas mejor valoradas
    
    void PelMejoresVal(){
        Pelicula p;

        if (p.catalogoVacio()) {
            SetConsoleTextAttribute(hConsole, AMARILLO);
            cout << "\nEl catalogo esta vacio\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
            c.limpiarPantalla();
            return;
        }

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

        c.limpiarPantalla();
    }
        
    void buscarPeliculas(){
        Pelicula p;
        if (p.catalogoVacio()) {
            SetConsoleTextAttribute(hConsole, AMARILLO);
            cout << "\nEl catalogo esta vacio\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
            c.limpiarPantalla();
            return;
        }

        int opcion;
        float opc;
        do{
            SetConsoleTextAttribute(hConsole, CIAN);
            cout << " ------MENU DE BUSQUEDA------ \n";
            SetConsoleTextAttribute(hConsole, BLANCO);
            cout << "0- Salir del menu de busqueda\n ";
            cout << "1- Buscar por genero\n ";
            cout << "2- Buscar por titulo\n ";
            cout << "3- Buscar por anio\n ";
            cout << "Elige una opcion: ";
            cin >> opc;

            // Verificar entrada válida
		    if (cin.fail()){ // Si la entrada no es un numero
		    	cin.clear(); // Limpiar estado de error de cin
			    cin.ignore(1000,'\n'); // Descartar la entrada incorrecta hasta mil caracteres o hasta encontrar un salto de linea
                opcion=500;
            }
		    else if (fmod(opc,1)!=0) opcion=500; // Descartar numeros con decimales
		    else opcion=static_cast<int>(opc); // Convertir entrada a enteros si es válida

            system("cls");
        
            switch (opcion)   {
                case 0: cout << "Saliendo...\n"; break;
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
                            if (anioBuscado < anioMinimo) {
                                cout << "\nAnio no valido\n";
                                c.limpiarPantalla();
                            }
                        } while(anioBuscado < anioMinimo);
                        buscarPorAnio(anioBuscado);
                        break;
                        }   
                    default: 
                            SetConsoleTextAttribute(hConsole, ROJO);
                            cout<< "\nOpcion invalida\n";
                            SetConsoleTextAttribute(hConsole, BLANCO);
                            c.limpiarPantalla();
                            break;
            }   
            
            c.limpiarPantalla();
        }while (opcion !=0); 
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
        int mostrarEncabezado = 0;
        while (archivo.read((char*)&p, sizeof(Pelicula))) {
            if (strcmp(p.getGenero(), generoBuscado) == 0) {
                encontrado = true;
                mostrarEncabezado++;
                if (mostrarEncabezado == 1) {
                    SetConsoleTextAttribute(hConsole, VERDE);
                    cout << "\n----- PELICULA ENCONTRADA -----\n";
                    SetConsoleTextAttribute(hConsole, BLANCO);
                }
                cout << "Titulo: " << p.getTitulo() << "\n";
                cout << "Director: " << p.getDirector() << "\n";
                cout << "Anio: " << p.getAnio() << "\n";
                cout << "Puntuacion: " << p.getPuntuacion();
                p.getSinopsis(p.getTitulo());
                cout << "\nResenia: ";
                p.mostrarResena(p.getTitulo());
                cout << "\n--------------------------------\n";
            }
        }

        if (!encontrado){
            SetConsoleTextAttribute(hConsole, AMARILLO);
            cout << "\nNo se encontraron peliculas con ese genero.\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
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
        int mostrarEncabezado = 0;
        while (archivo.read((char*)&p, sizeof(Pelicula))) {
            if (strcmp(p.getTitulo(), tituloBuscado) == 0) {
                encontrado = true;
                mostrarEncabezado++;
                if (mostrarEncabezado == 1) {
                    SetConsoleTextAttribute(hConsole, VERDE);
                    cout << "\n----- PELICULA ENCONTRADA -----\n";
                    SetConsoleTextAttribute(hConsole, BLANCO);
                }
                cout << "Titulo: " << p.getTitulo() << "\n";
                cout << "Director: " << p.getDirector() << "\n";
                cout << "Genero: " << p.getGenero() << "\n";
                cout << "Anio: " << p.getAnio() << "\n";
                cout << "Puntuacion: " << p.getPuntuacion();
                p.getSinopsis(p.getTitulo());
                cout << "\nResenia: ";
                p.mostrarResena(p.getTitulo());
                cout << "\n--------------------------------\n";
            }
        }

        if (!encontrado) {
            SetConsoleTextAttribute(hConsole, AMARILLO);
            cout << "\nNo se encontro la pelicula con ese titulo.\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
        }
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
        int mostrarEncabezado = 0;
        while (archivo.read((char*)&p, sizeof(Pelicula))) {
            if (p.getAnio() == anioBuscado) {
                encontrado = true;
                mostrarEncabezado++;
                if (mostrarEncabezado == 1) {
                    SetConsoleTextAttribute(hConsole, VERDE);
                    cout << "\n----- PELICULA ENCONTRADA -----\n";
                    SetConsoleTextAttribute(hConsole, BLANCO);
                }
                cout << "Titulo: " << p.getTitulo() << "\n";
                cout << "Director: " << p.getDirector() << "\n";
                cout << "Genero: " << p.getGenero() << "\n";
                cout << "Puntuacion: " << p.getPuntuacion();
                p.getSinopsis(p.getTitulo());
                cout << "\nResenia: ";
                p.mostrarResena(p.getTitulo());
                cout << "\n--------------------------------\n";
            }
        }

        if (!encontrado) {
            SetConsoleTextAttribute(hConsole, AMARILLO);
            cout << "\nNo se encontraron peliculas de ese anio.\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
        }
        archivo.close();
    }

    void setResenas(){
        Pelicula p;
        if (p.catalogoVacio()) {
            SetConsoleTextAttribute(hConsole, AMARILLO);
            cout << "\nEl catalogo esta vacio\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
            c.limpiarPantalla();
            return;
        }

        Resena r;
        r.aprobada = 0; // Inicia no aprobada
        fstream file("resenas.dat", ios::binary | ios::out | ios::app);
        if (!file.is_open()) {
            cout << "No se pudo abrir el archivo de resenias.\n";
            return;
        }

        cout << "\n Ingresa el titulo de la pelicula para la resena: ";
        cin.ignore();
        cin.getline(r.titulo, 100);
        c.dar_formato_a_cadenas(r.titulo);
        // Verificar que la película está en el catálogo
        if (!buscarPeli(r.titulo)) {
            SetConsoleTextAttribute(hConsole, AMARILLO);
            cout << "No se encontro la pelicula\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
            c.limpiarPantalla();
            return;
        }
        cout << "Escribe la resena: ";
        cin.getline(r.resena, 500);

        file.write(reinterpret_cast<char*>(&r), sizeof(Resena));
        file.close();

        SetConsoleTextAttribute(hConsole, VERDE);
        cout << "\n Resena enviada y pendiente de aprobacion.\n"; 
        SetConsoleTextAttribute(hConsole, BLANCO);

        c.limpiarPantalla();
    }

    void calificar(){
        // Verificar si el catálogo está vacío
        Pelicula p;
        if (p.catalogoVacio()) {
            SetConsoleTextAttribute(hConsole, AMARILLO);
            cout << "\nEl catalogo esta vacio\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
            c.limpiarPantalla();
            return;
        }

        char tituloCalificar[TAM];
        float nuevaCalif;

        cout << "\n Ingresa el titulo de la pelicula: ";
        cin.ignore();
        cin.getline(tituloCalificar, TAM);
        c.dar_formato_a_cadenas(tituloCalificar);

        // Verificar que la película está en el catálogo
        if (!buscarPeli(tituloCalificar)) {
            SetConsoleTextAttribute(hConsole, AMARILLO);
            cout << "No se encontro la pelicula\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
            c.limpiarPantalla();
            return;
        }

        // Obtener calificación válida
        bool califValida = false;
        do {
            cout << "Ingresa tu calificacion (0 a 10): ";
            cin >> nuevaCalif;
        
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                SetConsoleTextAttribute(hConsole, ROJO);
                cout << "Calificacion no valida. Debe ser un numero.\n";
                SetConsoleTextAttribute(hConsole, BLANCO);
                c.limpiarPantalla();
            }
            else if (nuevaCalif < 0 || nuevaCalif > 10) {
                SetConsoleTextAttribute(hConsole, ROJO);
                cout << "Calificacion debe estar entre 0 y 10.\n";
                SetConsoleTextAttribute(hConsole, BLANCO);
                c.limpiarPantalla();
            }
            else {
                califValida = true;
            }
        } while(!califValida);

        fstream archivo("catalogo.dat", ios::binary | ios::in | ios::out);
        if (!archivo.is_open()) {
            SetConsoleTextAttribute(hConsole, ROJO);
            cout << "Error al abrir archivo.\n";
            SetConsoleTextAttribute(hConsole, BLANCO);
            return;
        }

        Pelicula peliculaActual;
        streampos posicionActual;

        // Buscar la película específica
        while (archivo.read((char*)&peliculaActual, sizeof(Pelicula))) {
            if (strcmp(peliculaActual.getTitulo(), tituloCalificar) == 0) {
            
                // Calcular nueva puntuación
                float nuevaPuntuacion;
                float puntuacionActual = peliculaActual.getPuntuacion();
            
                if (puntuacionActual > 0) {
                    nuevaPuntuacion = (puntuacionActual + nuevaCalif) / 2;
                } else {
                    nuevaPuntuacion = nuevaCalif;
                }
            
                posicionActual = archivo.tellg();  // Posición después de la lectura
            
                // Retroceder al inicio de esta película
                archivo.seekp(posicionActual - streampos(sizeof(Pelicula)));
            
                // Actualizar la puntuación
                peliculaActual.setPuntuacion(nuevaPuntuacion);
            
                // Escribir la película actualizada
                archivo.write((char*)&peliculaActual, sizeof(Pelicula));
            
                // Verificar si la escritura fue exitosa
                if (archivo.fail()) {
                    SetConsoleTextAttribute(hConsole, ROJO);
                    cout << "\nError: No se pudo guardar la calificacion.\n";
                    SetConsoleTextAttribute(hConsole, BLANCO);
                } 
                else {
                    SetConsoleTextAttribute(hConsole, VERDE);
                    cout << "\nCalificacion guardada exitosamente!\n";
                    cout << "Puntuacion anterior: " << puntuacionActual << "\n";
                    cout << "Tu calificacion: " << nuevaCalif << "\n";
                    cout << "Nueva puntuacion promedio: " << nuevaPuntuacion << "\n";
                    SetConsoleTextAttribute(hConsole, BLANCO);
                }
                break;
            }
        }


        archivo.close();
        c.limpiarPantalla();
    }

    bool buscarPeli(char* tituloBuscado) {
        Pelicula p;
        fstream archivo;

        archivo.open("catalogo.dat", ios::binary | ios::in);

        while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Pelicula))) {
            // Se detiene si encuentra la pelicula o si y arevisó todas las peliuclas registradas
            if (p.getAnio() == 0) break;
            if (strcmp(p.getTitulo(), tituloBuscado) == 0) {
                return true; // Pelicula encontrada
                break;
            }
        }

        archivo.close();

        return false; // Pelicula no encontrada 
    }
 
};

#endif