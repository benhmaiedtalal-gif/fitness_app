#ifndef COACH_H
#define COACH_H

#include <gtk/gtk.h>

typedef struct {
    char centre_id[20];
    char centre_nom[50];
    int duree_candidature; 
    char type_contrat[20]; 
    int alerte_sms; // 1 ou 0
    int masquer_profil; // 1 ou 0
} DemandeCoach;

void ajouter_demande_coach(DemandeCoach d);
void afficher_centres_coach(GtkWidget *treeview);

#endif
