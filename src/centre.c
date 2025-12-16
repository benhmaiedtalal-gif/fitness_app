#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "centre.h"

#define FICHIER_CENTRES "centres.txt"

void ajouter_centre(Centre c) {
    FILE *f = fopen(FICHIER_CENTRES, "a");
    if (f != NULL) {
        fprintf(f, "%s;%s;%s;%d;%s;%s\n", 
                c.id, c.nom, c.adresse, c.capacite, 
                c.heure_ouverture, c.propriete);
        fclose(f);
    }
}

void afficher_centres(GtkWidget *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    FILE *f;
    Centre c;
    
    // Création du modèle
    store = gtk_list_store_new(6, 
        G_TYPE_STRING,  // ID
        G_TYPE_STRING,  // Nom
        G_TYPE_STRING,  // Adresse
        G_TYPE_INT,     // Capacité
        G_TYPE_STRING,  // Heure ouverture
        G_TYPE_STRING   // Propriété
    );
    
    // Lire le fichier
    f = fopen(FICHIER_CENTRES, "r");
    if (f != NULL) {
        while (fscanf(f, "%[^;];%[^;];%[^;];%d;%[^;];%[^\n]\n", 
                      c.id, c.nom, c.adresse, &c.capacite, 
                      c.heure_ouverture, c.propriete) != EOF) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                0, c.id,
                1, c.nom,
                2, c.adresse,
                3, c.capacite,
                4, c.heure_ouverture,
                5, c.propriete,
                -1);
        }
        fclose(f);
    }
    
    // Appliquer le modèle au treeview
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), 
                           GTK_TREE_MODEL(store));
    g_object_unref(store);
    
    // Créer les colonnes si elles n'existent pas
    if (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 0) == NULL) {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Capacité", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Heure", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Propriété", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }
}

Centre chercher_centre(char *id) {
    FILE *f = fopen(FICHIER_CENTRES, "r");
    Centre c, result;
    int trouve = 0;
    
    strcpy(result.id, "NON_TROUVE");
    strcpy(result.nom, "");
    strcpy(result.adresse, "");
    result.capacite = 0;
    strcpy(result.heure_ouverture, "");
    strcpy(result.propriete, "");
    
    if (f != NULL) {
        while (!trouve && fscanf(f, "%[^;];%[^;];%[^;];%d;%[^;];%[^\n]\n", 
                      c.id, c.nom, c.adresse, &c.capacite, 
                      c.heure_ouverture, c.propriete) != EOF) {
            if (strcmp(c.id, id) == 0) {
                result = c;
                trouve = 1;
            }
        }
        fclose(f);
    }
    return result;
}

int verifier_centre_existe(char *id) {
    Centre c = chercher_centre(id);
    return (strcmp(c.id, "NON_TROUVE") != 0);
}

void supprimer_centre(char *id) {
    FILE *f = fopen(FICHIER_CENTRES, "r");
    FILE *temp = fopen("temp.txt", "w");
    Centre c;
    
    if (f != NULL && temp != NULL) {
        while (fscanf(f, "%[^;];%[^;];%[^;];%d;%[^;];%[^\n]\n", 
                      c.id, c.nom, c.adresse, &c.capacite, 
                      c.heure_ouverture, c.propriete) != EOF) {
            if (strcmp(c.id, id) != 0) {
                fprintf(temp, "%s;%s;%s;%d;%s;%s\n", 
                        c.id, c.nom, c.adresse, c.capacite, 
                        c.heure_ouverture, c.propriete);
            }
        }
        fclose(f);
        fclose(temp);
        remove(FICHIER_CENTRES);
        rename("temp.txt", FICHIER_CENTRES);
    }
}

void modifier_centre(Centre c) {
    supprimer_centre(c.id);
    ajouter_centre(c);
}
