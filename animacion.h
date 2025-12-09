#ifndef ANIMACION_H
#define ANIMACION_H

#include <iostream>
#include <windows.h>

using namespace std;
#define ESP 300

#define ROJOS 4
#define BLANCOS 7
#define CIANS 3

void animacionInicial() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hConsole, ROJOS);
    system("cls");
    string cGrande[] {
    "        CCCCCCCCCCCCCCC        ",
    "     CCCCCCCCCCCCCCCCCCCC      ",
    "   CCCCCCCCCCCCCCCCCCCCCCCC    ",
    "  CCCCCCCCC         CCCCCCCC   ",
    " CCCCCCC              CCCCCCC  ",
    "CCCCCCC                        ",
    "CCCCCC                         ",
    "CCCCCC                         ",
   "CCCCCC                         ",
   "CCCCCC                         ",
    "CCCCCC                         ",
    "CCCCCC                         ",
    " CCCCCCC                       ",
    " CCCCCCC              CCCCCCC  ",
    "  CCCCCCC         CCCCCCCC   ",
    "   CCCCCCCCCCCCCCCCCCCCCCCC    ",
    "     CCCCCCCCCCCCCCCCCCCC      ",
    "        CCCCCCCCCCCCCCC        "
    };

    for (int i = 0; i < 18; i++) {
        cout << "                               " << cGrande[i] << endl;
        Sleep(50);
    }

    Sleep (800);
    SetConsoleTextAttribute(hConsole, CIANS);
    system("cls");

    cout << "\n        CCCCCCCCCCCCCCC                                    ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                   ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                 ";
    cout << "\n  CCCCCCCCC         CCCCCCCC                                ";
    cout << "\n CCCCCCC              CCCCCCC                                ";
    cout << "\n CCCCCCC                                                ";
    cout << "\nCCCCCC                                           ";
    cout << "\nCCCCCC                                     ";
    cout << "\n CCCCCCC                                      ";
    cout << "\n CCCCCCC                                    ";
    cout << "\n CCCCCCC              CCCCCCC                              ";
    cout << "\n  CCCCCCC         CCCCCCCC                                 ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                  ";
    cout << "\n        CCCCCCCCCCCCCCC                                    ";



    Sleep(ESP);
    system("cls");

    cout << "\n        CCCCCCCCCCCCCCC                                    ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                   ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                 ";
    cout << "\n  CCCCCCCCC         CCCCCCCC                                ";
    cout << "\n CCCCCCC              CCCCCCC                                ";
    cout << "\n CCCCCCC                             aaa                      ";
    cout << "\nCCCCCC                              aa aa                      ";
    cout << "\nCCCCCC                             aa   aa                   ";
    cout << "\n CCCCCCC                          aaaaaaaaa                   ";
    cout << "\n CCCCCCC                         aa       aa                   ";
    cout << "\n CCCCCCC              CCCCCCC                              ";
    cout << "\n  CCCCCCC         CCCCCCCC                                 ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                  ";
    cout << "\n        CCCCCCCCCCCCCCC                                    ";

    Sleep(ESP);
    system("cls");

    cout << "\n        CCCCCCCCCCCCCCC                                    ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                   ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                 ";
    cout << "\n  CCCCCCCCC         CCCCCCCC                                ";
    cout << "\n CCCCCCC              CCCCCCC                                ";
    cout << "\n CCCCCCC                             aaa      tttttttttt                ";
    cout << "\nCCCCCC                              aa aa         tt             ";
    cout << "\nCCCCCC                             aa   aa        tt           ";
    cout << "\n CCCCCCC                          aaaaaaaaa       tt            ";
    cout << "\n CCCCCCC                         aa       aa      tt             ";
    cout << "\n CCCCCCC              CCCCCCC                              ";
    cout << "\n  CCCCCCC         CCCCCCCC                                 ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                  ";
    cout << "\n        CCCCCCCCCCCCCCC                                    ";

    Sleep(ESP);
    system("cls");

    cout << "\n        CCCCCCCCCCCCCCC                                    ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                   ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                 ";
    cout << "\n  CCCCCCCCC         CCCCCCCC                                ";
    cout << "\n CCCCCCC              CCCCCCC                                ";
    cout << "\n CCCCCCC                             aaa      tttttttttt       aaa         ";
    cout << "\nCCCCCC                              aa aa         tt          aa aa  ";
    cout << "\nCCCCCC                             aa   aa        tt         aa   aa";
    cout << "\n CCCCCCC                          aaaaaaaaa       tt        aaaaaaaaa";
    cout << "\n CCCCCCC                         aa       aa      tt       aa       aa";
    cout << "\n CCCCCCC              CCCCCCC                              ";
    cout << "\n  CCCCCCC         CCCCCCCC                                 ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                  ";
    cout << "\n        CCCCCCCCCCCCCCC                                    ";

    Sleep(ESP);
    system("cls");

    cout << "\n        CCCCCCCCCCCCCCC                                    ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                   ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                 ";
    cout << "\n  CCCCCCCCC         CCCCCCCC                                ";
    cout << "\n CCCCCCC              CCCCCCC                                ";
    cout << "\n CCCCCCC                             aaa      tttttttttt       aaa       ll     ";
    cout << "\nCCCCCC                              aa aa         tt          aa aa      ll      ";
    cout << "\nCCCCCC                             aa   aa        tt         aa   aa     ll      ";
    cout << "\n CCCCCCC                          aaaaaaaaa       tt        aaaaaaaaa    ll       ";
    cout << "\n CCCCCCC                         aa       aa      tt       aa       aa   llllllll             ";
    cout << "\n CCCCCCC              CCCCCCC                              ";
    cout << "\n  CCCCCCC         CCCCCCCC                                 ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                  ";
    cout << "\n        CCCCCCCCCCCCCCC                                    ";

    Sleep(ESP);
    system("cls");

    cout << "\n        CCCCCCCCCCCCCCC                                    ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                   ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                 ";
    cout << "\n  CCCCCCCCC         CCCCCCCC                                ";
    cout << "\n CCCCCCC              CCCCCCC                                ";
    cout << "\n CCCCCCC                             aaa      tttttttttt       aaa       ll             ooooo    ";
    cout << "\nCCCCCC                              aa aa         tt          aa aa      ll           oo     oo   ";
    cout << "\nCCCCCC                             aa   aa        tt         aa   aa     ll          oo       oo   ";
    cout << "\n CCCCCCC                          aaaaaaaaa       tt        aaaaaaaaa    ll           oo     oo   ";
    cout << "\n CCCCCCC                         aa       aa      tt       aa       aa   llllllll       ooooo     ";
    cout << "\n CCCCCCC              CCCCCCC                              ";
    cout << "\n  CCCCCCC         CCCCCCCC                                 ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                  ";
    cout << "\n        CCCCCCCCCCCCCCC                                    ";

    Sleep(ESP);
    system("cls");
    

    cout << "\n        CCCCCCCCCCCCCCC                                    ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                   ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                 ";
    cout << "\n  CCCCCCCCC         CCCCCCCC                                ";
    cout << "\n CCCCCCC              CCCCCCC                                ";
    cout << "\n CCCCCCC                             aaa      tttttttttt       aaa       ll             ooooo         gggggg  ";
    cout << "\nCCCCCC                              aa aa         tt          aa aa      ll           oo     oo     gg     gg  ";
    cout << "\nCCCCCC                             aa   aa        tt         aa   aa     ll          oo       oo    gg           ";
    cout << "\n CCCCCCC                          aaaaaaaaa       tt        aaaaaaaaa    ll           oo     oo      gg    gggg  ";
    cout << "\n CCCCCCC                         aa       aa      tt       aa       aa   llllllll       ooooo          gggggg    ";
    cout << "\n CCCCCCC              CCCCCCC                              ";
    cout << "\n  CCCCCCC         CCCCCCCC                                 ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                  ";
    cout << "\n        CCCCCCCCCCCCCCC                                    ";

    Sleep(ESP);
    system("cls");
    

    cout << "\n        CCCCCCCCCCCCCCC                                    ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                   ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                 ";
    cout << "\n  CCCCCCCCC         CCCCCCCC                                ";
    cout << "\n CCCCCCC              CCCCCCC                                ";
    cout << "\n CCCCCCC                          aaa    tttttttttt     aaa     ll          ooooo       gggggg        ooooo   ";
    cout << "\nCCCCCC                           aa aa       tt        aa aa    ll        oo     oo   gg     gg     oo     oo ";
    cout << "\nCCCCCC                          aa   aa      tt       aa   aa   ll       oo       oo  gg           oo       oo ";
    cout << "\n CCCCCCC                       aaaaaaaaa     tt      aaaaaaaaa  ll        oo     oo    gg    gggg   oo     oo  ";
    cout << "\n CCCCCCC                      aa       aa    tt     aa       aa llllllll    ooooo        gggggg       ooooo ";
    cout << "\n CCCCCCC              CCCCCCC                              ";
    cout << "\n  CCCCCCC         CCCCCCCC                                 ";
    cout << "\n   CCCCCCCCCCCCCCCCCCCCCCCC                                ";
    cout << "\n     CCCCCCCCCCCCCCCCCCCC                                  ";
    cout << "\n        CCCCCCCCCCCCCCC                                    ";




    SetConsoleTextAttribute(hConsole, BLANCOS);
    cout << endl;
    system("pause");
    system("cls");
}

#endif 