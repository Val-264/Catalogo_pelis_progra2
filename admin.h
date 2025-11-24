#include<iostream>
#include<math.h>
#include <fstream>
#include "peliculas.h"
using namespace std;


class Administrador{
    public:
        // Control getControlador(){return c;}
        void mostrarMenu();         // Mostrar menu de acciones del administrador

        
        //-----------FUNCIONES PARA MODIFICAR EL CATALOGO-----------
        void crearNuevoCatalogo(); // Crea un nuevo catalogo 
        void agregarPelicula();     // Agregar una pelicula al catalogo
        void modificarCatalogo();  // Muestra un menu para elegir modificar o eleminar una pelicula del catálogo
        void modificarPelicula();  // Modificar datos de alguna pelicula
        void eliminarPelicula();    // Eliminar pelicula
        void ordenarPelicula();     // Ordena peliculas cada que se agrega una nueva 
        void revisarResenias();      // Revisar reseñas para aprobarlas o eliminarlas, va en modificar pelicula 

        
        //-----------FUNCIONES PARA REVISAR EL CATALOGO-----------
        void revisarCatalogo();     // Ver el catalogo de peliculas. Muestra los campos de la pelicula 
};

void Administrador::mostrarMenu(){
    float opc;
    int opcion;
    do{
        cout << "\n------ACCIONES DEL ADMINISTRADOR-----:";
        cout << "\n0- Salir";
        cout << "\n1- Crear nuevo catalogo";
        cout << "\n2- Modificar catalogo"; 
        cout << "\n3- Revisar catalogo"; 
        cout << "\nElige una opcion: ";
        cin >> opc;

        // Verificar entrada válida
		if (cin.fail()){ // Si la entrada no es un numero
			cin.clear(); // Limpiar estado de error de cin
			cin.ignore(1000,'\n'); // Descartar la entrada incorrecta hasta mil caracteres o hasta encontrar un salto de linea
            opcion=500;
        }
		else if (fmod(opc,1)!=0) opcion=500; // Descartar numeros con decimales
		else opcion=static_cast<int>(opc); // Convertir entrada a enteros si es válida

        switch (opcion){
            case 1: crearNuevoCatalogo();
            case 2: modificarCatalogo(); break;
            case 3: revisarCatalogo(); break;
            case 0: cout<<"Saliendo...";
            default: cout<<"Opcion invalida\n";
        }

    }while(opcion!=0);
}


//-----------FUNCIONES PARA MODIFICAR EL CATALOGO-----------
void Administrador::crearNuevoCatalogo(){
    // Verificar que no haya un catalogo exitente 
    // Elegir entre conservar el catalogo actual (si ya existía uno) o crear uno nuevo 
    Pelicula p;
    char opc;
    if (!p.catalogoVacio()) {
        do{
            cout << "Ya hay un catalogo existente, deseas conservarlo?(S/N)";
            cin >> opc;
            opc = toupper(opc);
        } while(opc != 'S' || opc != 'N');

        if (opc == 'S') return;
        else p.cascaronesBinarios();

    }
    else p.cascaronesBinarios();
}

void Administrador::modificarCatalogo(){
    float opc;
    int opcion;
    do{
        cout << "\n------MODIFICACION DE CATALOGO-----:";
        cout << "\n0- Salir";
        cout << "\n1- Agregar pelicula"; 
        cout << "\n2- Modificar pelicula";
        cout << "\n3- Eliminar pelicula";
        cout << "\nElige una opcion: ";
        cin>>opc;

        // Verificar entrada válida
		if(cin.fail()){ // Si la entrada no es un numero
			cin.clear(); // Limpiar estado de error de cin
			cin.ignore(1000,'\n'); // Descartar la entrada incorrecta hasta mil caracteres o hasta encontrar un salto de linea
            opcion=500;
        }
		else if(fmod(opc,1)!=0) opcion=500; // Descartar numeros con decimales
		else opcion=static_cast<int>(opc); // Convertir entrada a enteros si es válida

        switch(opcion){
            case 1: agregarPelicula(); break;
            case 2: modificarPelicula(); break;
            case 3: eliminarPelicula(); break;
            case 0: cout<<"Saliendo...";
            default: cout<<"Opcion invalida\n";
        }

    }while(opcion!=0);
}

void Administrador::agregarPelicula(){
    char titulo[TAM], dir[TAM], genero[TAM];
    int aa, punt;
    Pelicula p;

    fstream peliculas;  
    
    cout << "Titulo: "; cin.getline(titulo,TAM);
    cout << "Director: "; cin.getline(dir,TAM);
    cout << "Genero:\n"; 
    strcmp(genero, p.elegirGeneros(0));
    do{
        cout << "Anio: "; 
        cin >> aa;
        if (aa < 1888) cout << "Intenta de nuevo, en ese anio aun no se habian creado peliculas\n";
    }while(aa < 1888);
    punt = 0;

    Pelicula nuevo(titulo, dir, genero, aa, punt);

    // Agregar sinopsis
    p.setSinopsis(titulo,nuevo);

    p.totPeliculas++;

    peliculas.open(p.catalogo, ios::binary | ios::in | ios::out);

    if(!peliculas) {
        peliculas.close();
        cerr << "No se pudo abrir el archivo para agregar peliculas";
        return;
    }

    //-----------Grabar en el archivo binario-----------
    // Posicionarse dentro del archivo binario
    peliculas.seekp((p.totPeliculas-1) * sizeof(Pelicula), ios::beg);

    // Escribir en el registro una vez posicionado 
    peliculas.write(reinterpret_cast<char*>(&nuevo), sizeof(Pelicula));
    
    peliculas.close();
}

//-----------FUNCIONES PARA REVISAR EL CATALOGO-----------
void Administrador::revisarCatalogo(){
    Pelicula p;

    if (p.catalogoVacio()) {
        cout << "No hay peliculas registradas, el catalogo esta vacio";
        return;
    }
    else {
        fstream peliculas;

        peliculas.open(p.catalogo, ios::binary | ios::in);

        if (!peliculas) {
            peliculas.close();
            cerr << "No se pudo abrir el catalogo para revision";
            return;
        }

        cout << "Peliculas existentes en el catalogo:\n";
        cout << "--------------------------------";
        Pelicula registro;
        for (int i = 0; i < TOT_PELIS; i++) {
            // Posicionarse dentro del archivo binario
            peliculas.seekg(i*sizeof(Pelicula));

            // Extraer la cantidad de bytes de sizeof y colocarlos en el registro
            peliculas.read(reinterpret_cast<char*>(&registro), sizeof(Pelicula));

            if (registro.getAnio() == 0) break; // Terminar si el año es cero (no hay películas con año = 0)
            
            cout << "\nTitulo: " << registro.getTitulo();
            cout << "\nDirector: " << registro.getDirector();
            cout << "\nGenero: " << registro.getGenero();
            cout << "\nAnio: " << registro.getAnio();
            cout << "\nPuntuacion: "  << registro.getPuntuacion();
            cout << "\n--------------------------------\n";
        }
        
        char opc;
        cout << "\n\n";
        do {
            cout << "\nFinalizar revision? (S)";
            cin >> opc;
            opc = toupper(opc);
        }while(opc != 'S');

        peliculas.close();
    }
    
}