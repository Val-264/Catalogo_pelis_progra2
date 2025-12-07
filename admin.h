#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <windows.h> // Para colores 
#include <algorithm>
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
        void ordenarPelicula();     // Ordena peliculas por año o por orden alfabético  
        void ordenar_anio_ascendente(Pelicula* pelis, int totPelis);
        void ordenar_anio_descendente(Pelicula* pelis, int totPelis);
        void ordenar_alfabetico_ascendente(Pelicula* pelis, int totPelis);
        void ordenar_alfabetico_descendente(Pelicula* pelis, int totPelis);
        void aprobarResenias();      // Revisar reseñas para aprobarlas o eliminarlas, va en modificar pelicula 

        
        //-----------FUNCIONES PARA REVISAR EL CATALOGO-----------
        void revisarCatalogo();     // Ver el catalogo de peliculas. Muestra los campos de la pelicula 
};

void Administrador::mostrarMenu(){
    float opc;
    int opcion;
    Control c;
    do{
        SetConsoleTextAttribute(hConsole, AZUL);
        cout << "\n------ACCIONES DEL ADMINISTRADOR-----:";
        SetConsoleTextAttribute(hConsole, BLANCO);
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

        system("cls");
        switch (opcion){
            case 1: crearNuevoCatalogo(); break;
            case 2: modificarCatalogo(); break;
            case 3: revisarCatalogo(); break;
            case 0: cout<<"Saliendo..."; break;
            default: 
                    SetConsoleTextAttribute(hConsole, ROJO);
                    cout<<"Opcion invalida\n";
                    SetConsoleTextAttribute(hConsole, BLANCO);
                    c.limpiarPantalla();
        }

    }while(opcion!=0);
}


//-----------FUNCIONES PARA MODIFICAR EL CATALOGO-----------
void Administrador::crearNuevoCatalogo(){
    // Verificar que no haya un catalogo exitente 
    // Elegir entre conservar el catalogo actual (si ya existía uno) o crear uno nuevo 
    Pelicula p;
    Control c;
    char opc;

    if (!p.catalogoVacio()) {
        do{
            cout << "Ya hay un catalogo existente, deseas conservarlo?(S/N): ";
            cin >> opc;
            opc = toupper(opc);
        } while(opc != 'S' && opc != 'N'); 

        if (opc == 'S') {  
            system("cls"); 
            return;
        }
        else {
            p.cascaronBinario((char*)"catalogo.dat");
            c.cascaronContadores();
            cout << "\nSe creo el catalogo exitosamente\n";
        }
    }
    else {
        p.cascaronBinario((char*)"catalogo.dat");
        c.cascaronContadores();
        cout << "\nSe creo el catalogo exitosamente\n";
    }
    c.limpiarPantalla();
}

void Administrador::modificarCatalogo(){
    Control c;
    Pelicula p;

    if (p.catalogoVacio()) {
        cout << "No se ha creado un catalogo";
        c.limpiarPantalla();
        return;
    }

    float opc;
    int opcion;
    do{
        int totPelis = c.getContador((char*)"Total");
        SetConsoleTextAttribute(hConsole, AZUL);
        cout << "\n------MODIFICACION DE CATALOGO-----:";
        SetConsoleTextAttribute(hConsole, BLANCO);
        cout << "\n0- Salir";
        cout << "\n1- Agregar pelicula"; 
        // Las acciones del 2 al 4 solo se pueden realizar si hay peliculas 
        if (totPelis > 0) {
            cout << "\n2- Modificar pelicula";
            cout << "\n3- Eliminar pelicula";
            cout << "\n4- Ordenar peliculas";
            cout << "\n5- Aprobar resenias";
        }
        cout << "\nElige una opcion: ";
        cin>>opc;

        // Verificar entrada válida
		if(cin.fail()){ // Si la entrada no es un numero
			cin.clear(); // Limpiar estado de error de cin
			cin.ignore(1000,'\n'); // Descartar la entrada incorrecta hasta mil caracteres o hasta encontrar un salto de linea
            opcion=500;
        }
		else if(fmod(opc,1)!=0) opcion=500; // Descartar numeros con decimales
        else if (c.getContador((char*)"Total") < 1 && opc > 1) opcion = 500; 
		else opcion=static_cast<int>(opc); // Convertir entrada a enteros si es válida

        switch(opcion){
            case 1: agregarPelicula(); break;
            case 2: modificarPelicula(); break;
            case 3: eliminarPelicula(); break;
            case 4: ordenarPelicula(); break;
            case 0: cout<<"Saliendo..."; break;
            default: 
                    SetConsoleTextAttribute(hConsole, ROJO);
                    cout<<"Opcion invalida\n";
                    SetConsoleTextAttribute(hConsole, BLANCO);
                    c.limpiarPantalla();
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
        if (aa < anioMinimo) cout << "Intenta de nuevo, en ese anio aun no se habian creado peliculas\n";
    }while(aa < anioMinimo);
    punt = 0;

    Pelicula nuevo(titulo, dir, genero, aa, punt);
    Control c;

    // Agregar sinopsis
    p.setSinopsis(titulo);

    peliculas.open("catalogo.dat", ios::binary | ios::in | ios::out);

    if(!peliculas) {
        peliculas.close();
        SetConsoleTextAttribute(hConsole, ROJO);
        cerr << "No se pudo abrir el archivo para agregar peliculas";
        SetConsoleTextAttribute(hConsole, BLANCO);
        return;
    }

    //-----------Grabar en el archivo binario-----------
    // Obtener total de películas
    int total = c.getContador((char*)"Total");
    if (total < 0) total = 0; // Si es la primera película
    
    // Posicionarse dentro del archivo binario
    peliculas.seekp(total * sizeof(Pelicula), ios::beg); 

    // Escribir en el registro una vez posicionado 
    peliculas.write(reinterpret_cast<char*>(&nuevo), sizeof(Pelicula));
    
    peliculas.close();

    c.setContadores((char*)"Total", genero, INCREMENTAR);
    
    c.limpiarPantalla();
}

void Administrador::modificarPelicula() {
    fstream peliculas;
    Pelicula p;
    Control c;

    peliculas.open("catalogo.dat", ios::binary | ios::in | ios::out);

    if (!peliculas) {
        peliculas.close();
        SetConsoleTextAttribute(hConsole, ROJO);
        cerr << "No se pudo abrir el archivo de catalogo para edicion";
        SetConsoleTextAttribute(hConsole, BLANCO);
        return;
    }

    char titulo[TAM], ti[TAM], dir[TAM];
    char continuar;
    int indice; // posición del registro a modificar 
    int opcion, aa;
    float opc;

    do {
        // Elegir película a modificar
        indice = p.elegirTitulos(titulo);
        
        if (indice <= 0) {
            cout << "No se selecciono pelicula.\n";
            c.limpiarPantalla();
            return;
        }

        // Leer la película seleccionada 
        peliculas.seekg((indice - 1) * sizeof(Pelicula)); // 
        peliculas.read(reinterpret_cast<char*>(&p), sizeof(Pelicula));

        // Preguntar por el campo a modificar 
        do {
            SetConsoleTextAttribute(hConsole, AZUL);
            cout << "\n------CAMPO A MODIFICAR-----:";
            SetConsoleTextAttribute(hConsole, BLANCO);
            cout << "\n0- Volver";
            cout << "\n1- Titulo";
            cout << "\n2- Director";
            cout << "\n3- Genero";
            cout << "\n4- Anio";
            cout << "\nElige una opcion: ";
            cin >> opc;

            // Verificar entrada válida
		    if(cin.fail()){ // Si la entrada no es un numero
		        cin.clear(); // Limpiar estado de error de cin
		        cin.ignore(1000,'\n'); // Descartar la entrada incorrecta hasta mil caracteres o hasta encontrar un salto de linea
                opcion=500;
            }
		    else if(fmod(opc,1)!=0) opcion=500; // Descartar numeros con decimales
		    else opcion=static_cast<int>(opc); // Convertir entrada a enteros si es válida

            // Capturar los cambios 
            switch (opcion) {
                case 0: 
                    break;
                case 1: 
                    cout << "Nuevo Titulo: ";
                    cin.ignore();
                    cin.getline(ti, TAM);
                    ti[0] = toupper(ti[0]);
                    for (size_t i = 1; i < strlen(ti); i++) ti[i] = tolower(ti[i]);
                    // Grabar los cambios 
                    p.setTitulo(ti);
                    break;

                case 2: 
                    cout << "Nuevo Director: ";
                    cin.ignore();
                    cin.getline(dir, TAM);
                    dir[0] = toupper(dir[0]);
                    for (size_t i = 1; i < strlen(dir); i++) dir[i] = tolower(dir[i]);
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
                            cout << "Nuevo Anio: ";
                            cin >> aa;
                            if (aa < anioMinimo) {
                                SetConsoleTextAttribute(hConsole, ROJO);
                                cout << "Intenta de nuevo, en ese anio aun no se habian creado peliculas\n";
                                SetConsoleTextAttribute(hConsole, BLANCO);
                            }
                        }while(aa < anioMinimo);
                        // Grabar los cambios
                        p.setAnio(aa);
                        break;

                default: 
                        SetConsoleTextAttribute(hConsole, ROJO);
                        cout << "Opcion invalida\n";
                        SetConsoleTextAttribute(hConsole, BLANCO);
                        continue;
            }
            
            // Escribir cambios si no es opción 0
            if (opcion != 0) {
                peliculas.seekp((indice - 1) * sizeof(Pelicula)); 
                peliculas.write(reinterpret_cast<char*>(&p), sizeof(Pelicula));
                SetConsoleTextAttribute(hConsole, VERDE);
                cout << "Cambios guardados exitosamente.\n";
                SetConsoleTextAttribute(hConsole, BLANCO);
            }
            
            c.limpiarPantalla();
        } while(opcion != 0); //Terminar de editar una pelicula 

        do{
            cout << "Modificar otra pelicula (S/N): ";
            cin >> continuar;
            continuar = toupper(continuar);
            if (continuar != 'S' && continuar != 'N') { 
                SetConsoleTextAttribute(hConsole, ROJO);
                cout << "\nRespuesta no valida\n";
                SetConsoleTextAttribute(hConsole, BLANCO);
            }
            c.limpiarPantalla();
        }while(continuar != 'S' && continuar != 'N'); 
        
    }while(continuar == 'S'); 

    peliculas.close();
}

void Administrador::eliminarPelicula() {
    char titPeli[TAM];
    Control c;
    Pelicula p;
    
    // Elegir título (solo una vez)
    cout << "Elige el titulo de la pelicula a eliminar:\n";
    int indice = p.elegirTitulos(titPeli);
    
    if (indice <= 0) {
        cout << "No se selecciono ninguna pelicula.\n";
        c.limpiarPantalla();
        return;
    }
    
    fstream catalogo;
    fstream temporal; 
    
    // Crear archivo temporal 
    p.cascaronBinario((char*)"temp.dat");

    catalogo.open("catalogo.dat", ios::binary | ios::in); // Abrir catalogo para lectura 
    if(!catalogo) {
        SetConsoleTextAttribute(hConsole, ROJO);
        cerr << "\nNo se puedo abrir el catalogo para eliminar pelicula\n";
        SetConsoleTextAttribute(hConsole, BLANCO);
        c.limpiarPantalla();
        return;
    }
    
    temporal.open("temp.dat", ios::binary | ios::out | ios::app); // Abrir archivo temporal para escritura
    if(!temporal) {
        SetConsoleTextAttribute(hConsole, ROJO);
        cerr << "\nNo se puedo abrir el archivo temporal para eliminar pelicula\n";
        SetConsoleTextAttribute(hConsole, BLANCO);
        catalogo.close();
        c.limpiarPantalla();
        return;
    }

    int cont = 1;
    int totPermanecen = 0;
    Pelicula peliculaActual;
    char generoEliminado[TAM];
    bool encontrada = false;
    
    int totalPelis = c.getContador((char*)"Total");
    
    // Recorrer todas las películas
    for (int i = 0; i < totalPelis; i++) {
        catalogo.seekg(i * sizeof(Pelicula));
        catalogo.read(reinterpret_cast<char*>(&peliculaActual), sizeof(Pelicula));
        
        // Verificar si es la película a eliminar
        if (strcmp(peliculaActual.getTitulo(), titPeli) == 0) {
            encontrada = true;
            strcpy(generoEliminado, peliculaActual.getGenero());
            cout << "Pelicula: " << peliculaActual.getTitulo() << " eliminada\n";
            strcat(titPeli,".txt");
            remove(titPeli);
        }
        else { // Si no es la pelicula pasarla al temporal
            // Posicionarse dentro del archivo binario 
            temporal.seekp(totPermanecen * sizeof(Pelicula));
            // Escribir en el archivo binario 
            temporal.write(reinterpret_cast<char*>(&peliculaActual), sizeof(Pelicula));
            totPermanecen++;
        }
        cont++;
    }

    catalogo.close();
    temporal.close();

    if (encontrada) {
        // Disminuir contadores 
        c.setContadores((char*)"Total", generoEliminado, DECREMENTAR);

        remove("catalogo.dat"); // Borrar el catalogo anterior
        rename("temp.dat", "catalogo.dat"); // Renombrar el temporal como nuevo catalogo
        cout << "\nPelicula eliminada exitosamente. Peliculas restantes: " << totPermanecen << endl;
    } else {
        remove("temp.dat"); // Eliminar archivo temporal si no se encontró la película
        cout << "\nNo se encontro la pelicula: " << titPeli << endl;
    }

    c.limpiarPantalla();
}

void Administrador::ordenarPelicula() {
    Control c;

    int totPelis = c.getContador((char*)"Total");
    if (totPelis < 2) {
        cout << "Hay " << c.getContador((char*)"Total") << "peliculas.\n"
            << "No necesitas ordenar\n";
        c.limpiarPantalla();
        return;
    }
    
    fstream catalogo;
    Pelicula *pelis = new Pelicula[totPelis];  

    int opcion;
    float opc;
    
    catalogo.open("catalogo.dat", ios::binary | ios::in);
    if(!catalogo) {
        SetConsoleTextAttribute(hConsole, ROJO);
        cerr << "\nNo se pudo abrir el catalogo para ordenarlo\n";
        SetConsoleTextAttribute(hConsole, BLANCO);
        delete[] pelis;  // Liberar memoria en caso de error
        c.limpiarPantalla();
        return;
    }

    // Guardar las peliculas en el vector
    for (int i = 0; i < totPelis; i++) {
        catalogo.read(reinterpret_cast<char*>(&pelis[i]), sizeof(Pelicula));
    }
    catalogo.close();  // Cerrar archivo después de leer
    
    do{
        SetConsoleTextAttribute(hConsole, AZUL);
        cout << "\n------ORDENAR PELICULAS-----:";
        SetConsoleTextAttribute(hConsole, BLANCO);
        cout << "\n0- Salir";
        cout << "\nPOR ANIO:";
        cout << "\n1- De la más antigua a la más reciente (ascendente)";
        cout << "\n2- De la más reciente a la más antigua (descendente)";
        cout << "\nPOR ORDEN ALFABETICO"; 
        cout << "\n3- De la A a la Z"; 
        cout << "\n4- De la Z a la A";
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
            case 1: 
                ordenar_anio_ascendente(pelis, totPelis); 
                cout << "\nPeliculas ordenadas por año (ascendente)\n";
                break;
            case 2: 
                ordenar_anio_descendente(pelis, totPelis); 
                cout << "\nPeliculas ordenadas por año (descendente)\n";
                break;
            case 3: 
                ordenar_alfabetico_ascendente(pelis, totPelis); 
                cout << "\nPeliculas ordenadas alfabeticamente (A-Z)\n";
                break;
            case 4: 
                ordenar_alfabetico_descendente(pelis, totPelis); 
                cout << "\nPeliculas ordenadas alfabeticamente (Z-A)\n";
                break;
            case 0: 
                cout<<"Saliendo..."; 
                break;
            default: 
                SetConsoleTextAttribute(hConsole, ROJO);
                cout<<"Opcion invalida\n";
                SetConsoleTextAttribute(hConsole, BLANCO);
        }

        // Guardar cambios si se ordenó 
        if (opcion >= 1 && opcion <= 4) {
            catalogo.open("catalogo.dat", ios::binary | ios::out);  // Abrir para escritura
            if(!catalogo) {
                SetConsoleTextAttribute(hConsole, ROJO);
                cerr << "\nError al guardar cambios en el catalogo\n";
                SetConsoleTextAttribute(hConsole, BLANCO);
            }
            else {
                // Grabar los datos acomodados
                for (int i = 0; i < totPelis; i++) {
                    catalogo.write(reinterpret_cast<char*>(&pelis[i]), sizeof(Pelicula));            
                }
                catalogo.close();  
                cout << "Cambios guardados exitosamente.\n";
            }
        }
        revisarCatalogo();
        
    } while(opcion != 0);

    delete[] pelis; // Liberar memoria
}

// Ordenar del año más pequeño al más grande
void Administrador::ordenar_anio_ascendente(Pelicula* pelis, int totPelis) { 
    sort(pelis, (pelis +  totPelis), 
        [](const Pelicula& a, const Pelicula& b) {
            return a.getAnio() < b.getAnio();
        });
}

// Ordenar del año más grande al más pequeño 
void Administrador::ordenar_anio_descendente(Pelicula* pelis, int totPelis) {
    sort(pelis, (pelis +  totPelis), 
        [](const Pelicula& a, const Pelicula& b) {
            return a.getAnio() > b.getAnio();
        });
}

// Ordenar de A - Z por título 
void Administrador::ordenar_alfabetico_ascendente(Pelicula* pelis, int totPelis) {
    sort(pelis, (pelis +  totPelis), 
        [](const Pelicula& a, const Pelicula& b) {
            return strcmp(a.getTitulo(), b.getTitulo()) < 0;
        });
}

// Ordenar de Z - A por título
void Administrador::ordenar_alfabetico_descendente(Pelicula* pelis, int totPelis) {
    sort(pelis, (pelis +  totPelis), 
        [](const Pelicula& a, const Pelicula& b) {
            return strcmp(a.getTitulo(), b.getTitulo()) > 0;
        });
}

void Administrador::aprobarResenias() { 
    Control c;
    cout << "\nLa funcion aprobar resenias no ha sido implementada\n";
    c.limpiarPantalla();
}

//-----------FUNCIONES PARA REVISAR EL CATALOGO-----------
void Administrador::revisarCatalogo(){
    Pelicula p;
    Control c;

    if (p.catalogoVacio()) {
        cout << "No se ha creado un catalogo para revisar\n";
        c.limpiarPantalla();
        return;
    }

    if (c.getContador((char*)"Total") < 1) {
        cout << "No hay peliculas registradas para revisar\n";
        c.limpiarPantalla();
        return;
    }

    else {
        fstream peliculas;

        peliculas.open("catalogo.dat", ios::binary | ios::in);

        if (!peliculas) {
            peliculas.close();
            SetConsoleTextAttribute(hConsole, ROJO);
            cerr << "No se pudo abrir el catalogo para revision";
            SetConsoleTextAttribute(hConsole, BLANCO);
            c.limpiarPantalla();
            return;
        }
        
        SetConsoleTextAttribute(hConsole, AZUL);
        cout << "\nPeliculas existentes en el catalogo:\n";
        SetConsoleTextAttribute(hConsole, BLANCO);
        cout << "--------------------------------";
        Pelicula registro;
        int totalPelis = c.getContador((char*)"Total");
            
        for (int i = 0; i < totalPelis; i++) {
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
        c.limpiarPantalla();
        peliculas.close();
    }
}

#endif