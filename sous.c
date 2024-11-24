#include "head.h"
//
// Created by black on 20/11/2024.
//
void evolution(Graphe *graphe, int choixx) {
    if(choixx==1){
        system("cls");
    }
    int choix;
    printf("\nCombien d'etapes d'evolution :\n>");
    scanf("%d",&choix);
    system("cls");
    for (int step = 0; step < choix; step++) {


        float new_populations[MAXS] = {0}; // Tableau temporaire pour calculer les nouvelles populations.

        // Calcul des contributions (proies/predateurs).
        for (int i = 0; i < graphe->na; i++) {
            arc arc = graphe->arcs[i];
            Sommet *source = &graphe->sommets[arc.source];
            Sommet *destination = &graphe->sommets[arc.to];

            // Influence de la proie sur le prédateur
            new_populations[arc.to] += source->pop * arc.ci;

            // Réduction de la population de la proie
            new_populations[arc.source] -= source->pop * arc.ci;
        }
        if(choixx==1 || step+1==choix || step==0){
            // Mise à jour des populations en tenant compte du taux de croissance
            printf("\n--- Etape %d ---\n", step + 1);
            for (int i = 0; i < graphe->ns-2; i++) {
                Sommet *s = &graphe->sommets[i];
                float croissance = s->pop * s->tc; // Croissance intrinsèque
                s->pop += croissance + new_populations[i];

                // Empêcher les populations négatives
                if (s->pop < 0) {
                    s->pop = 0;
                }
                printf("Espece %s: Population = %.2f\n", s->nom, s->pop);
            }
        }
    }
    printf("\n> Voir toute les etapes : a"
           "\n> Quitter : b");
    while (choixx!='b') {
        if (_kbhit()) {
            choixx = _getch();
            if (choixx=='a')(evolution(graphe,1));
        }
    }
}
int fdde(Graphe *graphe, int sid){
    int count=0;
    for (int i = 0; i < graphe->na; i++) {
        if (graphe->arcs[i].to == sid) {
            count++;
        }
    }
    return count;
}
int fdds(Graphe *graphe, int sid){
    int count=0;
    for (int i = 0; i < graphe->na; i++) {
        if (graphe->arcs[i].source == sid) {
            count++;
        }
    }
    return count;
}

void info_s(Graphe *graphe) {
    int nom;
    printf("\nEntrez l'ID du sommet a explorer : ");
    scanf("%d", &nom);

    int sid = findus_int(graphe, nom); // Trouver l'ID
    if (sid == -1) {
        printf("Sommet avec l'ID %d introuvable\n", nom);
        return;
    }

    Sommet s = graphe->sommets[sid];
    printf("\n=== Informations du sommet '%s' ===\n", s.nom);
    printf("ID               : %d\n", s.id);
    printf("Population       : %.2f\n", s.pop);
    printf("Taux de Croissance : %.2f\n", s.tc);
    printf("Niveau Trophique : %d\n", s.nt);
    printf("Demi-degres entrant : %d\n", fdde(graphe,sid));
    printf("Demi-degres sortant : %d\n", fdds(graphe,sid));

    printf("\n--- Predecesseurs - Proies ---\n");
    printf("%-15s %-10s\n", "Nom", "Coefficient");
    printf("----------------------------\n");

    for (int i = 0; i < graphe->na; i++) {
        if (graphe->arcs[i].to == sid) {
            int source_id = graphe->arcs[i].source;
            printf("%-15s %-10.2f\n",
                   graphe->sommets[source_id].nom, graphe->arcs[i].ci);
        }
    }

    printf("\n--- Successeurs - Predateurs ---\n");
    printf("%-15s %-10s\n", "Nom", "Coefficient");
    printf("----------------------------\n");

    for (int i = 0; i < graphe->na; i++) {
        if (graphe->arcs[i].source == sid) {
            int dest_id = graphe->arcs[i].to;
            printf("%-15s %-10.2f\n",
                   graphe->sommets[dest_id].nom, graphe->arcs[i].ci);
        }
    }
}


int new_s(Graphe *graphe, char *nom, float population, float taux_croissance, int niveau_trophique) {
    if (graphe->ns>=MAXS) return -1;
    Sommet newSommet;
    strcpy(newSommet.nom,nom);
    newSommet.pop= population;
    newSommet.tc= taux_croissance;
    newSommet.nt= niveau_trophique;
    newSommet.id= graphe->ns;
    graphe->sommets[graphe->ns++] =newSommet;
    return newSommet.id;
}
void load_g(Graphe *graphe, const char *filename) {
    FILE *file=fopen(filename, "r");
    if (!file){
        perror("Erreur d'ouverture du fichier");
        return;
    }
    char line[100];
    int mode = 0;  // 0 = sommets 1 = arcs
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#') {
            mode++;
            continue;
        }

        if (mode == 1) {  // Chargement des sommets
            char nom[50];
            float pop,tc;
            int nt;
            sscanf(line, "%s %f %f %d", nom, &pop, &tc, &nt);
            new_s(graphe, nom, pop, tc, nt);
        } else if (mode == 2) {  // Chargement des arcs
            char source[50], to[50];
            float coef;
            sscanf(line, "%s %s %f", source, to, &coef);

            int src_id = findus_char(graphe, source);
            int dest_id = findus_char(graphe, to);

            if (src_id!=-1 && dest_id!=-1) {
                if (graphe->na >=MAXA) return;
                arc newArc = {src_id, dest_id, coef};
                graphe->arcs[graphe->na++] = newArc;
            }
        }
    }
    fclose(file);
}
int findus_char(Graphe *graphe, char* nom) {
    for (int i=0;i<graphe->ns;i++) {
        if (strcmp(graphe->sommets[i].nom,nom)==0) {
            return i;
        }
    }
    return -1;
}
int findus_int(Graphe *graphe, int nom) {
    for (int i=0;i<graphe->ns;i++) {
        if (graphe->sommets[i].id == nom) {
            return i;
        }
    }
    return -1;
}
void show_g(Graphe *graphe) {
    printf("\n=== Liste des Sommets ===\n");
    printf("%-5s %-15s %-10s %-10s %-15s\n", "ID", "Nom", "Population", "Croissance", "Niveau Trophique");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < graphe->ns-2; i++) {
        Sommet s = graphe->sommets[i];
        printf("%-5d %-15s %-10.2f %-10.2f %-15d\n",
               s.id, s.nom, s.pop, s.tc, s.nt);
    }

    printf("\n=== Liste des Arcs ===\n");
    printf("%-10s %-15s %-10s\n", "Source", "Destination", "Coefficient");
    printf("---------------------------------------\n");

    for (int i = 0; i < graphe->na-1; i++) {
        arc a = graphe->arcs[i];
        char *source_nom = graphe->sommets[a.source].nom;
        char *dest_nom = graphe->sommets[a.to].nom;

        printf("%-15s %-15s %-10.2f\n",source_nom, dest_nom, a.ci);
    }
}