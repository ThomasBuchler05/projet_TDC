//
// Created by black on 20/11/2024.
//

#ifndef PROJET_TDC_HEAD_H
#define PROJET_TDC_HEAD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#ifndef PROJET_V0_HEAD_H
#define PROJET_V0_HEAD_H

#endif //PROJET_V0_HEAD_H





#define MAXA 100 //max arc
#define MAXS 100 // max somet

// Struct sommet  espèce
typedef struct {
    char nom[50];
    int id;
    float pop; //population
    float tc; //taux croissance
    int nt; // niveau trophique
} Sommet;

typedef struct {
    int source;
    int to; // destination
    float ci; // coefficient interaction
} arc;

// Struct res troph
typedef struct {
    Sommet sommets[MAXS];
    arc arcs[MAXA];
    int ns; // nb sommets
    int na; // nb arcs
} Graphe;



int new_s(Graphe *graphe, char *nom, float population, float taux_croissance, int niveau_trophique);// nouveau sommet
void show_g(Graphe *graphe);// affiche graph console
void load_g(Graphe *graphe, const char *filename);// charge depuis fichier
int findus_char(Graphe *graphe, char* nom) ;// trouver sommet
int findus_int(Graphe *graphe,int nom) ;// trouver sommet
void info_s(Graphe *graphe); // afficher info sommet
void evolution(Graphe *graphe, int choixx);
int menu(Graphe graphe);
void clearConsole();
void lereste(Graphe *graphe);
int fdde(Graphe *graphe, int sid);
int fdds(Graphe *graphe, int sid);
#endif //PROJET_TDC_HEAD_H
