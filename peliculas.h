#include<iostream>
#include<string.h>
#include<vector>
using namespace std;

#define TAM 500

class Pelicula{
    private:
        char titulo[TAM];
        char director[TAM];
        char genero[TAM];
        char sinopsis[TAM*2];
        int anio;
        float puntuacion;
    public: 
        Pelicula(){}
        Pelicula(char* t, char*dir, char*gen, int aa, char*sps){
            strcpy(titulo,t);
            strcpy(director,dir);
            strcpy(genero,gen);
            anio=aa;
            strcpy(sinopsis,sps);
        }

        //-----------NOMBRES DE LOS ARCHIVOS-----------
        char catalogo[13] = "catalogo.dat";

        //-----------FUNCIONES-----------
        void setTitulo(char *t){ strcpy(titulo, t); }
        void setDirector(char *d){ strcpy(director, d); }
        void setGenero(char *g){ strcpy(genero, g); }
        void setAnio(int a){ anio = a; }
        void setPuntuaxion(float p){ puntuacion = p; }

        char* getTitulo(){return titulo;}
        char* getDirector(){return director;}
        char* getGenero(){ return genero; }
        int getAnio(){ return anio; }
        float getPuntuacion(){ return puntuacion; }

        char* elegirGeneros(int llamada);
        
};

char* Pelicula::elegirGeneros(int llamada){ // Si llamada = 0 es del administrador, si llamada = 1es del usuario
    char retorno[TAM];
    char otro[TAM];
    vector<char[TAM]> generos;
    generos.emplace_back("Drama");
    generos.emplace_back("Accion");
    generos.emplace_back("Romance");
    generos.emplace_back("Comedia");
    generos.emplace_back("Ciencia ficcion");
    generos.emplace_back("Terror");
    generos.emplace_back("Fantasia");

    float opc;
    int opcion; 

    int i=1;
    cout << "Generos de pelicula";
    for(auto& g: generos) {
        cout << "\n" << i << "-" << g; i++;
    } 
    cout << "\n8- Otro";
    cin >> opc;

    // Para administrador: asignar un genero a una pelicula  
    if(llamada == 0) {
        if(opcion == 8) {
            cout << "Otro genero: "; cin.getline(otro,TAM);

            int tamOtro = strlen(otro);
            otro[0]=toupper(otro[0]);
            for(int i=1; i < tamOtro; i++) tolower(otro[i]);
                
            // Verificar que no sea un genero de los ya disponibles 
            bool cambio = false;
            do{
                for (auto& g: generos) {
                    if (strcmp(g,otro) == 0){
                        char cambio;
                        cout << "Ese genero ya esta definido en las opciones, lo puedes sonservar"
                            << "\nO quieres agregar uno nuevo? (s/n)";
                        cin >> cambio;
                        cambio = tolower(cambio);
                        if (cambio == 's') {
                            cout << "Otro genero: "; cin.getline(otro,TAM);
                        } 
                        else (strcpy(otro,g)); 
                    }
                }
            }while (!cambio);
        }

        switch(opcion){
            case 1: strcmp(retorno,generos[0]); break;
            case 2: strcmp(retorno, generos[1]); break;
            case 3: strcmp(retorno, generos[2]); break;
            case 4: strcmp(retorno, generos[3]); break;
            case 5: strcmp(retorno, generos[4]); break;
            case 6: strcmp(retorno, generos[5]); break;
            case 7: strcmp(retorno, generos[6]); break;
            case 8: strcmp(retorno, otro); break;
        }
    }

    // Para usuario: elegir un genro para buscar 
    else {

    }

    return retorno;
}

        