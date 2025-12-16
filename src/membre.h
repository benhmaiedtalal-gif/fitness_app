#ifndef MEMBRE_H_INCLUDED
#define MEMBRE_H_INCLUDED
#include <gtk/gtk.h>

typedef struct {
    char jour[10];
    char mois[10];
    char annee[10];
} date_naissance;

typedef struct {
    char id[20];
    char motdepasse[20];
    char nom[20];
    char abonnement[30];
    char sexe[10];
    date_naissance date_naiss;
    char telephone[15];
} membre;

// Enum pour les colonnes du TreeView
enum {
    COL_ID = 0,
    COL_MOTDEPASSE, 
    COL_NOM,
    COL_ABONNEMENT,
    COL_SEXE,
    COL_DATE_NAISSANCE,
    COL_TELEPHONE,
    COLUMNS
};

// Déclarations des fonctions
int ajouter_membre(membre m, char filename[]);
int modifier_membre(char id[], membre nouv, char filename[]);
int supprimer_membre(char id[], char filename[]);
membre chercher_membre(char x[], char filename[]);
void afficher_membres(GtkTreeView *treeview, char filename[]);
int verifier_existant_membre(char id[], char filename[]);
int verifier_connexion(char id[], char mdp[], char filename[]);
int supprimer_membre_avec_fichier(char id[], char filename[]);  // Déclaration ajoutée

#endif // MEMBRE_H_INCLUDED
