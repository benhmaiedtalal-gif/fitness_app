#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <gtk/gtk.h>

typedef struct {
    char id[20];
    char lieu[50];
    char categorie[50];
    int quantite_dispo;
    int jour_maintenance;
    int mois_maintenance;
    int annee_maintenance;
    int etat; // 1 = disponible, 0 = non disponible
} Equipement;

// Fonctions de gestion des équipements
void ajouter_equipement(Equipement e);
void supprimer_equipement(char* id);
Equipement rechercher_equipement(char* id);
void afficher_equipements(GtkWidget *treeview);
void vider_treeview(GtkWidget *treeview);

// Fonction pour trouver l'index d'une catégorie dans un combo box
int trouver_index_categorie(const char* categorie);

Equipement get_equipement_by_id_from_treeview(GtkWidget *treeview, const char *id_to_find);


#endif
