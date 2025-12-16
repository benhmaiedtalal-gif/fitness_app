#ifndef CENTRE_H
#define CENTRE_H

#include <gtk/gtk.h>

typedef struct {
    char id[20];
    char nom[50];
    char adresse[100];
    int capacite;
    char heure_ouverture[10];
    char propriete[20]; // "INDEPENDANT" ou "PARTENARIAT"
} Centre;

void ajouter_centre(Centre c);
void afficher_centres(GtkWidget *treeview);
void supprimer_centre(char *id);
void modifier_centre(Centre c);
Centre chercher_centre(char *id);
int verifier_centre_existe(char *id);

#endif
