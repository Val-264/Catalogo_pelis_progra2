#ifndef ADMIN_H
#define ADMIN_H

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
        int elegirTitulos(char* tituloPeli);
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
            case 1: crearNuevoCatalogo(); break;
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
    Contadores c;
    char opc;

    if (!p.catalogoVacio()) {
        do{
            cout << "Ya hay un catalogo existente, deseas conservarlo?(S/N)";
            cin >> opc;
            opc = toupper(opc);
        } while(opc != 'S' || opc != 'N');

        if (opc == 'S') return;
        else {
            p.cascaronCatalogo();
            c.cascaronContadores();
        }

    }
    else {
        p.cascaronCatalogo();
        c.cascaronContadores();
    }
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
    
    cin.ignore();
    cout << "Titulo: "; cin.getline(titulo,TAM);
    cout << "Director: "; cin.getline(dir,TAM);
    cout << "Genero:\n"; 
    p.elegirGeneros(genero);
    do{
        cout << "Anio: "; 
        cin >> aa;
        if (aa < p.anioMinimo) cout << "Intenta de nuevo, en ese anio aun no se habian creado peliculas\n";
    }while(aa < p.anioMinimo);
    punt = 0;

    Pelicula nuevo(titulo, dir, genero, aa, punt);
    Contadores c;

    // Agregar sinopsis
    p.setSinopsis(titulo);

    peliculas.open("catalogo.dat", ios::binary | ios::in | ios::out);

    if(!peliculas) {
        peliculas.close();
        cerr << "No se pudo abrir el archivo para agregar peliculas";
        return;
    }

    //-----------Grabar en el archivo binario-----------
    // Posicionarse dentro del archivo binario
    peliculas.seekp((c.getContador((char*)"Total") - 1) * sizeof(Pelicula), ios::beg);

    // Escribir en el registro una vez posicionado 
    peliculas.write(reinterpret_cast<char*>(&nuevo), sizeof(Pelicula));
    
    peliculas.close();
}

void Administrador::eliminarPelicula() {

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

        peliculas.open("catalogo.dat", ios::binary | ios::in);

        if (!peliculas) {
            peliculas.close();
            cerr << "No se pudo abrir el catalogo para revision";
            return;
        }
        char opc; 
        do {
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
        
            cout << "\n\n";
            do {
                cout << "\nFinalizar revision? (S/N)";
                cin >> opc;
                opc = toupper(opc);
                if (opc != 'S' || opc != 'N') cout << "\nOpcion invalida\n";
                system("pause");
                system("cls");
            }while(opc != 'S' || opc != 'N');
        }while (opc != 'N');

        peliculas.close();
    }
    
}

void Administrador::modificarPelicula() {
    fstream peliculas;
    Pelicula p;
    Contadores c;

    peliculas.open("catalogo.dat", ios::binary | ios::in | ios::out);

    if (!peliculas) {
        peliculas.close();
        cerr << "No se pudo abrir el archivo de catalogo para edicion";
        return;
    }

    char titulo[TAM], ti[TAM], dir[TAM];
    char continuar;
    int indice; // posición del registro a modificar 
    int opcion, aa;
    float opc;

    do {


        indice = elegirTitulos(titulo);

        // Preguntar por el campo a modificar 
        do {
            cout << "\n------CAMPO A MODIFICAR-----:";
            cout << "\n0- Volver";
            cout << "\n1- Titulo";
            cout << "\n2- Director";
            cout << "\n3- Genero";
            cout << "\n4- Anio";
            cout << "Elige una opcion: ";
            cin >> opc;

            // Verificar entrada válida
		    if(cin.fail()){ // Si la entrada no es un numero
		        cin.clear(); // Limpiar estado de error de cin
		        cin.ignore(1000,'\n'); // Descartar la entrada incorrecta hasta mil caracteres o hasta encontrar un salto de linea
                opcion=500;
            }
		    else if(fmod(opc,1)!=0) opcion=500; // Descartar numeros con decimales
            else if(opc < 0 || opc > 4) opcion = 500; // Fuera de rango 
		    else opcion=static_cast<int>(opc); // Convertir entrada a enteros si es válida

            // Posicionarse dentro del archivo binario 
            peliculas.seekp(indice * sizeof(Pelicula));

            // Escribir en el regsitro una vez posicionado  
            peliculas.write(reinterpret_cast<char*>(&p),sizeof(Pelicula));

            // Capturar los cambios 
            switch (opcion) {
                case 0: break;
                case 1: cout << "Titulo: ";
                        cin.getline(ti,TAM);

                        ti[0] = toupper(ti[0]);
                        for (size_t i = 1; i < sizeof(ti); i++) ti[i] = tolower(ti[i]);

                        // Grabar los cambios 
                        p.setTitulo(ti);

                        break;

                case 2: cout << "Director: ";
                        cin.getline(dir,TAM);

                        dir[0] = toupper(dir[0]);
                        for (size_t i = 1; i < sizeof(dir); i++) dir[i] = tolower(dir[i]);
                        // Grabar los cambios
                        p.setDirector(dir);

                        break;

                case 3: { // Grabar los cambios
                        char retorno[TAM];
                        p.elegirGeneros(retorno);
                        p.setGenero(retorno);

                        break;
                        }
                case 4: 
                        do{
                            cout << "Anio: ";
                            cin >> aa;
                            if (aa < p.anioMinimo) cout << "Intenta de nuevo, en ese anio aun no se habian creado peliculas\n";
                        }while(aa < p.anioMinimo);

                        // Grabar los cambios
                        p.setAnio(aa);

                        break;

                default: cout << "Opcion invalida\n";
            }
            
            system("pause");
            system("cls");
        } while(opcion != 0); //Terminar de editar una pelicula 

        do{
            cout << "Modificar otra pelicula (S/N): ";
            cin >> continuar;
            continuar = toupper(continuar);
            if (continuar != 'S' || continuar != 'N') {
                cout << "\nRespuesta no valida\n";
                system("pause");
                system("cls");
            }
        }while(continuar != 'S' || continuar != 'N');

        system("cls");
    }while(continuar != 'N'); // Terminar de editar los campos de las peliculas 

    peliculas.close();
}

int Administrador::elegirTitulos(char* tituloPeli) {
    fstream catalogo;
    Pelicula p;
    Contadores c;
    float ind;
    int indice = 0, cont = 1;
    bool indiceValido = false;

    // Abrir archivo para lectura 
    catalogo.open("catalogo.dat", ios::binary | ios::in);

    do {
        cout << "-----TITULOS-----";
        while(catalogo.read(reinterpret_cast<char*>(&p), sizeof(Pelicula))) {
            cout << "\n" << cont << "- " << p.getTitulo();
            if (cont == c.getContador((char*)"Total")) break;
            cont++;
        }
        cout << "Numero de la pelicula a elegir: ";
        cin >> ind;
        // Verificar entrada válida
		if (cin.fail()){ // Si la entrada no es un numero
			cin.clear(); // Limpiar estado de error de cin
			cin.ignore(1000,'\n'); // Descartar la entrada incorrecta hasta mil caracteres o hasta encontrar un salto de linea
            cout << "\nOpcion invalida\n";
        }
		else if (fmod(ind,1)!=0) { // Descartar numeros con decimales
            cout << "\nOpcion invalida\n";
        }
        else if(ind < 1 || ind > c.getContador((char*)"Total")) { // Si esta fuera de rango 
            cout << "\nOpcion invalida\n";
        }
		else { // Convertir entrada a enteros si es válida
            indice = static_cast<int>(ind);
            indiceValido = true;
        }

        system("pause");
        system("cls");
    }while (!indiceValido);

    catalogo.close();

    return indice;
}

#endif