#include <iostream>
#include <fstream>
using namespace std;

#define TAM 500

class Contadores {
    private:
        struct Contador{
            int total;
            char nom[TAM];
        };

        Contador cont; 
    public:
        Contadores() {
            cont.total = 0;
            strcmp(cont.nom, " ");
        }

        void cascaronContadores() {
            fstream contadores;

            contadores.open("contadores.dat", ios::binary | ios::out | ios::trunc);

            if (!contadores) {
                contadores.close();
                cerr << "\nNo se pudo abrir el archivo de contadores\n";
                return; 
            }

            Contador vacio = {0, "vacio"};

            for (int i = 0; i < 8; i++) {
                contadores.write(reinterpret_cast<char*> (&vacio), sizeof(Contador));
            }

        }

        char generos[7][TAM] = {"Drama", "Accion", "Romance", "Comedia", "Ciencia ficcion", "Terror", "Fantasia"};

        // Aumentar el total de peliculas y el total de un género específico 
        void setContadores(char* total, char* genero) {
            fstream contadores;
            
            // Abrir para escritura
            contadores.open("contadores.dat", ios::binary | ios::out);

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
                    cont.total++;

                    // Posicionarse y escribir los datos actulizados en el registro 
                    contadores.seekp(posicion);
                    contadores.write(reinterpret_cast<char*>(&cont), sizeof(Contador));
                }

                // Aumentar total de un genero específico 
                else if (strcmp(cont.nom, genero) == 0) {
                    posicion = contadores.tellg() - streampos(sizeof(Contador));
                    break;

                    // Actualizar contador
                    cont.total++;
                
                    // Posicionarse y escribir los datos actulizados en el registro 
                    contadores.seekp(posicion);
                    contadores.write(reinterpret_cast<char*>(&cont), sizeof(Contador));
                }
            }

            contadores.close();

        }

        int getContador(char* nomContador) {
            fstream contadores;
            int contador;

            // Abrir archivo para lectura 
            contadores.open("contadores.dat", ios::binary | ios::in);

            if(!contadores) {
                cerr << "\nNo se puedo abrir el archivo de contadores\n";
                return;
            }

            while (contadores.read(reinterpret_cast<char*>(&cont), sizeof(Contador))) {
                int posicion = 0;

                // Retornar el contador si se encuentra 
                if (strcmp(cont.nom, nomContador) == 0) {
                    return cont.total;
                }
            }         

            contadores.close();

            // Regresar el contador 
            return contador;
        }
};