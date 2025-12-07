#ifndef CONTADOR_H
#define CONTADOR_H

#include <iostream>
#include <fstream>
#include <climits>
#include <cstring>
#include <windows.h>
using namespace std;

#define TAM 500

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
                cerr << "\nNo se pudo abrir el archivo de contadores\n";
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

        static char generos[7][TAM];

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
            cerr << "\nNo se puedo abrir el archivo de contadores\n";
                return;
            }

            // Buscar si el usuario ya existe en el archivo 
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
                cerr << "\nNo se puedo abrir el archivo de contadores\n";
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
};


char Control::generos[7][TAM] = {"Drama", "Accion", "Romance", "Comedia", "Ciencia ficcion", "Terror", "Fantasia"};

#endif