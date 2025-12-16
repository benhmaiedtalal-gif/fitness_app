#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "coach.h"
#include "centre.h"

#define FICHIER_DEMANDES "demandes_coach.txt"

void ajouter_demande_coach(DemandeCoach d) {
    FILE *f = fopen(FICHIER_DEMANDES, "a");
    if (f != NULL) {
        fprintf(f, "%s;%s;%d;%s;%d;%d\n", 
                d.centre_id, d.centre_nom, d.duree_candidature,
                d.type_contrat, d.alerte_sms, d.masquer_profil);
        fclose(f);
    }
}

void afficher_centres_coach(GtkWidget *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    FILE *f;
    Centre c;
    
    store = gtk_list_store_new(4, 
        G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
    
    f = fopen("centres.txt", "r");
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
                -1);
        }
        fclose(f);
    }
    
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), 
                           GTK_TREE_MODEL(store));
    g_object_unref(store);
    
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
    }
}
