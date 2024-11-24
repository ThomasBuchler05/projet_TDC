//
// Created by thoma on 20/11/2024.
//
#include "head.h"
//
// Created by black on 17/11/2024.
//
void clearConsole() {
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console, topLeft);
}
void lereste(Graphe graphe){
    show_g(&graphe);
    info_s(&graphe);
    evolution(&graphe, 0);
    system("cls");
}
int menu(Graphe graphe) {
    char choix=' ';
    system("cls");
    printf("Choisir reseau :"
           "\n> Marin : a"
           "\n> Terrestre : b"
           "\n> Jardin : c"
           "\n> Quitter : f");
    while (choix!='f') {
        if (_kbhit()) {
            choix = _getch();
            if(choix=='a'){
                system("cls");
                load_g(&graphe, "marin");
                lereste(graphe);
                menu(graphe);
            }
            else if(choix=='b'){
                system("cls");
                load_g(&graphe, "terre.txt");
                lereste(graphe);
                menu(graphe);
            }
            else if(choix=='c'){
                system("cls");
                load_g(&graphe, "jardin");
                lereste(graphe);
                menu(graphe);
            }
        }
    }
    exit(8);
}