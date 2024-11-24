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
=======
//travialle
>>>>>>> 485067daa9e5816c0aac11a349bee62de9458e53
