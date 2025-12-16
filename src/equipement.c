#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "equipement.h"

// Tableau des catégories disponibles (doit correspondre à ton menu)
const char* categories[] = {
    "MUSCULATION",
    "CARDIO TRAINING", 
    "CROSS TRAINING",
    "CIRCUIT TRAINING",
    "YOGA",
    "PSTRETCHING",
    "MEDITATION",
    "ZUMBA",
    "BOXE",
    "CYCLING",
    "BOOTCAMP",
    "SEANCE EN GROUPE",
    "SEANCE DECOUVERTE",
    "PLANIFICATION D'OBJECTIFS",
    "COACHING NUTRITIONNEL",
    NULL
};

int trouver_index_categorie(const char* categorie) {
    if (categorie == NULL) return -1;
    
    for (int i = 0; categories[i] != NULL; i++) {
        if (strcmp(categories[i], categorie) == 0) {
            return i;
        }
    }
    return -1;
}

void ajouter_equipement(Equipement e) {
    FILE *f = fopen("equipements.txt", "a");
    if (f != NULL) {
        fprintf(f, "%s;%s;%s;%d;%d;%d;%d;%d\n",
                e.id, e.lieu, e.categorie, e.quantite_dispo,
                e.jour_maintenance, e.mois_maintenance, e.annee_maintenance, e.etat);
        fclose(f);
        g_print("Équipement ajouté avec succès: %s\n", e.id);
    } else {
        g_print("Erreur: Impossible d'ouvrir le fichier equipements.txt\n");
    }
}

void supprimer_equipement(char* id) {
    FILE *f = fopen("equipements.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    
    if (f == NULL || temp == NULL) {
        g_print("Erreur: Impossible d'ouvrir les fichiers\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }
    
    char ligne[256];
    int trouve = 0;
    
    while (fgets(ligne, sizeof(ligne), f)) {
        char current_id[20];
        sscanf(ligne, "%[^;]", current_id);
        
        if (strcmp(current_id, id) != 0) {
            fprintf(temp, "%s", ligne);
        } else {
            trouve = 1;
            g_print("Équipement supprimé: %s\n", id);
        }
    }
    
    fclose(f);
    fclose(temp);
    
    if (trouve) {
        remove("equipements.txt");
        rename("temp.txt", "equipements.txt");
    } else {
        remove("temp.txt");
        g_print("Équipement non trouvé pour suppression: %s\n", id);
    }
}

Equipement rechercher_equipement(char* id) {
    FILE *f = fopen("equipements.txt", "r");
    Equipement e = {"", "", "", 0, 0, 0, 0, 0};
    
    if (f != NULL) {
        char ligne[256];
        while (fgets(ligne, sizeof(ligne), f)) {
            char temp[256];
            strcpy(temp, ligne);
            
            char *token = strtok(temp, ";");
            if (token && strcmp(token, id) == 0) {
                // ID trouvé, parser toute la ligne
                sscanf(ligne, "%[^;];%[^;];%[^;];%d;%d;%d;%d;%d",
                       e.id, e.lieu, e.categorie, &e.quantite_dispo,
                       &e.jour_maintenance, &e.mois_maintenance, &e.annee_maintenance, &e.etat);
                g_print("Équipement trouvé: %s\n", e.id);
                break;
            }
        }
        fclose(f);
    } else {
        g_print("Fichier equipements.txt non trouvé\n");
    }
    
    return e;
}

void vider_treeview(GtkWidget *treeview) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    if (model != NULL) {
        GtkListStore *store = GTK_LIST_STORE(model);
        gtk_list_store_clear(store);
    }
}

void afficher_equipements(GtkWidget *treeview) {
    if (treeview == NULL) {
        g_print("Erreur: TreeView est NULL\n");
        return;
    }
    
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    GtkListStore *store = NULL;
    
    if (model == NULL) {
        // Créer un nouveau modèle
        store = gtk_list_store_new(8,
                                   G_TYPE_STRING, // ID (0)
                                   G_TYPE_STRING, // Lieu (1)
                                   G_TYPE_STRING, // Catégorie (2)
                                   G_TYPE_INT,    // Quantité (3)
                                   G_TYPE_INT,    // Jour (4)
                                   G_TYPE_INT,    // Mois (5)
                                   G_TYPE_INT,    // Année (6)
                                   G_TYPE_STRING  // État (7)
                                   );
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        
        // Ajouter les colonnes au TreeView si elles n'existent pas déjà
        GtkCellRenderer *renderer;
        GtkTreeViewColumn *column;
        
        // Colonne ID
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        // Colonne Lieu
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Lieu", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        // Colonne Catégorie
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Catégorie", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        // Colonne Quantité
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Quantité", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        // Colonne Jour Maintenance
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        // Colonne Mois Maintenance
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        // Colonne Année Maintenance
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Année", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        // Colonne État
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("État", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        g_object_unref(store);
    } else {
        store = GTK_LIST_STORE(model);
    }
    
    if (store == NULL) {
        g_print("Erreur: Impossible de créer ou obtenir le modèle\n");
        return;
    }
    
    // Vider le modèle existant
    gtk_list_store_clear(store);
    
    // Lire le fichier et remplir le modèle
    FILE *f = fopen("equipements.txt", "r");
    if (f == NULL) {
        // Fichier n'existe pas, on crée un fichier vide
        f = fopen("equipements.txt", "w");
        if (f) {
            fclose(f);
            g_print("Fichier equipements.txt créé (vide)\n");
        }
        return;
    }
    
    char ligne[256];
    GtkTreeIter iter;
    
    while (fgets(ligne, sizeof(ligne), f)) {
        Equipement e;
        // Nettoyer la ligne (enlever le \n)
        ligne[strcspn(ligne, "\n")] = 0;
        
        if (sscanf(ligne, "%[^;];%[^;];%[^;];%d;%d;%d;%d;%d",
                   e.id, e.lieu, e.categorie, &e.quantite_dispo,
                   &e.jour_maintenance, &e.mois_maintenance, &e.annee_maintenance, &e.etat) == 8) {
            
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, e.id,
                               1, e.lieu,
                               2, e.categorie,
                               3, e.quantite_dispo,
                               4, e.jour_maintenance,
                               5, e.mois_maintenance,
                               6, e.annee_maintenance,
                               7, (e.etat == 1) ? "DISPONIBLE" : "NON DISPONIBLE",
                               -1);
        }
    }
    
    fclose(f);
    g_print("TreeView mise à jour avec les équipements\n");
}
// Fonction utilitaire pour récupérer les données d'un équipement par son ID
Equipement get_equipement_by_id_from_treeview(GtkWidget *treeview, const char *id_to_find) {
    Equipement e = {"", "", "", 0, 0, 0, 0, 0};
    
    if (!treeview || !id_to_find) return e;
    
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    if (!model) return e;
    
    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(model, &iter);
    
    while (valid) {
        gchar *id = NULL;
        gtk_tree_model_get(model, &iter, 0, &id, -1);
        
        if (id && strcmp(id, id_to_find) == 0) {
            // ID trouvé, récupérer toutes les données
            gchar *lieu = NULL;
            gchar *categorie = NULL;
            gchar *quantite_str = NULL;
            
            gtk_tree_model_get(model, &iter,
                              1, &lieu,
                              2, &categorie,
                              3, &quantite_str,
                              4, &e.jour_maintenance,
                              5, &e.mois_maintenance,
                              6, &e.annee_maintenance,
                              -1);
            
            if (id) {
                strcpy(e.id, id);
                g_free(id);
            }
            
            if (lieu) {
                strcpy(e.lieu, lieu);
                g_free(lieu);
            }
            
            if (categorie) {
                strcpy(e.categorie, categorie);
                g_free(categorie);
            }
            
            if (quantite_str) {
                e.quantite_dispo = atoi(quantite_str);
                g_free(quantite_str);
            }
            
            // L'état n'est pas nécessaire pour le coach
            e.etat = 1;
            
            g_print("Équipement trouvé dans TreeView: %s - %s\n", e.id, e.lieu);
            return e;
        }
        
        if (id) g_free(id);
        valid = gtk_tree_model_iter_next(model, &iter);
    }
    
    return e;
}
