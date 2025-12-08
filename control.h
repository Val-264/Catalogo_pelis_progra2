#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <fstream>
#include <climits>
#include <cstring>
#include <windows.h>
using namespace std;

#define TOT_PELIS 1000
#define TAM 500
const int anioMinimo = 1888; // La primer película se grabó en 1888, por lo tanto el año mínimo para una película debe ser 1888

enum Accion {DECREMENTAR = 0, INCREMENTAR =  1};

/*
Ejemplo de como poner colores 
SetConsoleTextAttribute(hConsole, VERDE);
*/

// COLORES
enum Colores{AZUL=1, VERDE, CIAN, ROJO, MAGENTA, AMARILLO, BLANCO};

// Obtener manejador de consola
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
class Control {
    private:
        struct Contador{
            int total;
            char nom[TAM];
        };

        Contador cont; 
    public:
        Control() {
            cont.total = 0;
            strcpy(cont.nom, " ");
        }

        void limpiarPantalla() {
            system("pause");
            system("cls");
        }

        void cascaronContadores() {
            fstream contadores;

            contadores.open("contadores.dat", ios::binary | ios::out | ios::trunc);

            if (!contadores) {
                contadores.close();
                SetConsoleTextAttribute(hConsole, ROJO);
                cerr << "\nNo se pudo abrir el archivo de contadores\n";
                SetConsoleTextAttribute(hConsole, BLANCO);
                return; 
            }

            Contador contador;

            for (int i = 0; i < 8; i++) {
                if (i == 0) {
                    contador.total = 0;
                    strcpy(contador.nom,"Total");
                }
                else {
                    contador.total = 0;
                    strcpy(contador.nom, generos[i-1]);
                }
                contadores.write(reinterpret_cast<char*> (&contador), sizeof(Contador));
            }

        }

        static char generos[8][TAM];

        /*
        Aumentar el total de peliculas y el total de un género específico
        @param total: es la palabra total para referise al total de películas
        @param genero: nombre del genero específico 
        @param accion: si es 0, decrementa, si es 1, aumenta 
        */  
        void setContadores(char* total, char* genero, Accion accion) { 
            fstream contadores;
            
            // Abrir para escritura
            contadores.open("contadores.dat", ios::binary | ios::out | ios::in);

            if(!contadores) {
                SetConsoleTextAttribute(hConsole, ROJO);
                cerr << "\nNo se puedo abrir el archivo de contadores\n";
                SetConsoleTextAttribute(hConsole, BLANCO);
                return;
            }

            while (contadores.read(reinterpret_cast<char*>(&cont), sizeof(Contador))) {
                int posicion = 0;

                // Aumengar total de peliculas 
                if (strcmp(cont.nom, total) == 0) {
                    // Posición del registro a modificar = inicio de registro 
                    // La lectura te deja al inicio del siguiente registro, 
                    // puntajes.tellg() es esa posición menos el tamaño del registro = posición del regisrtro que se desea modificar  
                    posicion = contadores.tellg() - streampos(sizeof(Contador));

                    // Actualizar contador
                    if (accion == 1) cont.total++;
                    else if (accion == 0 && cont.total > 0) cont.total--;

                    // Posicionarse y escribir los datos actulizados en el registro 
                    contadores.seekp(posicion);
                    contadores.write(reinterpret_cast<char*>(&cont), sizeof(Contador));
                }

                // Aumentar total de un genero específico 
                else if (strcmp(cont.nom, genero) == 0) {
                    posicion = contadores.tellg() - streampos(sizeof(Contador));

                    // Actualizar contador
                    if (accion == 1) cont.total++;
                    else if (accion == 0 && cont.total > 0) cont.total--;
                
                    // Posicionarse y escribir los datos actulizados en el registro 
                    contadores.seekp(posicion);
                    contadores.write(reinterpret_cast<char*>(&cont), sizeof(Contador));

                    break;
                }
            }

            contadores.close();

        }

        int getContador(char* nomContador) {
            fstream contadores;

            // Abrir archivo para lectura 
            contadores.open("contadores.dat", ios::binary | ios::in);

            if(!contadores) {
                SetConsoleTextAttribute(hConsole, ROJO);
                cerr << "\nNo se puedo abrir el archivo de contadores\n";
                SetConsoleTextAttribute(hConsole, BLANCO);
                return INT_MAX;
            }

            while (contadores.read(reinterpret_cast<char*>(&cont), sizeof(Contador))) {
                // Retornar el contador si se encuentra 
                if (strcmp(cont.nom, nomContador) == 0) {
                    contadores.close();
                    return cont.total; // Regresar contador 
                }
            }       
            
            return -1;
        }

        void dar_formato_a_cadenas(char* cadena) {
            normalizarEspacios(cadena);
            cadena[0] = toupper(cadena[0]);
            for (size_t i = 1; i < strlen(cadena); i++) {
                if (cadena[i-1] == ' ') cadena[i] = toupper(cadena[i]);
                else cadena[i] = tolower(cadena[i]);
            }
        }

        void normalizarEspacios(char* cadena) {
            if (cadena == nullptr || strlen(cadena) == 0) return;
    
            int i = 0, j = 0;
            bool espacioAnterior = false;
    
            // Eliminar espacios iniciales
            while (cadena[i] == ' ' || cadena[i] == '\t') i++;
    
        // Procesar el resto
        while (cadena[i]) {
            if (cadena[i] == ' ' || cadena[i] == '\t') {
                if (!espacioAnterior) {
                    cadena[j++] = ' ';  // Convertir cualquier espacio/tab a un solo espacio
                    espacioAnterior = true;
                }
        } else {
            cadena[j++] = cadena[i];
            espacioAnterior = false;
        }
        i++;
    }
    
    // Eliminar espacio final si hay
    if (j > 0 && cadena[j-1] == ' ') {
        j--;
    }
    
    cadena[j] = '\0';
        }
};


char Control::generos[8][TAM] = {"Drama", "Accion", "Romance", "Comedia", "Ciencia ficcion", "Terror", "Fantasia", "Otro"};

#endif