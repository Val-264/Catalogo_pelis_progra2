#include <iostream>
#include <cstring>
#include "admin.h"
#include "usuario.h"
using namespace std;

int main(int argc, const char* argv[]){
    char claveAdmin[175]="Hasta_el_dia_en_que_Dios_se_digne_revelar_el_porvenir_al_hombre,_toda_la_sabiduria_humana_estara_resumida_en_dos_palabras:_Confiar_y_esperar";
    char claveUsuario[12]="papasFritas";

    Administrador admin;
    Usuarios u;

    // Verificar que no haya más de dos elementos y que la clave sea correcta
    if(argc!=2 || (strcmp(argv[1],claveAdmin)!=0 && strcmp(argv[1],claveUsuario)!=0)) cout << "Clave incorrecta";
    // Mostrar menú de usuario o administrador dependiendo de la clave ingresada
    else if(strcmp(argv[1],claveAdmin)==0) admin.mostrarMenu();
    else u.menuUsuario();

    return 0;
}