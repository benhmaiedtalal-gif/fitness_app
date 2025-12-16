#include "membre.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

/* ==============================================
   FONCTION : Ajouter un membre
   ============================================== */
int ajouter_membre(membre m, char filename[]) {
    FILE *f = fopen(filename, "a");
    if(f != NULL) {
        fprintf(f, "%s %s %s %s %s %s %s %s %s\n", 
                m.id, m.motdepasse, m.nom, m.abonnement, m.sexe,
                m.date_naiss.jour, m.date_naiss.mois, m.date_naiss.annee, 
                m.telephone);
        fclose(f);
        return 1;
    }
    return 0;
}

/* ==============================================
   FONCTION : Modifier un membre
   ============================================== */
int modifier_membre(char id[], membre nouv, char filename[]) {
    int tr = 0;
    membre m;
    FILE *f = fopen(filename, "r");
    FILE *f1 = fopen("temp.txt", "w");
    
    if(f != NULL && f1 != NULL) {
        while(fscanf(f, "%s %s %s %s %s %s %s %s %s", 
                    m.id, m.motdepasse, m.nom, m.abonnement, m.sexe,
                    m.date_naiss.jour, m.date_naiss.mois, m.date_naiss.annee,
                    m.telephone) != EOF) {
            if(strcmp(m.id, id) == 0) {
                fprintf(f1, "%s %s %s %s %s %s %s %s %s\n", 
                       nouv.id, nouv.motdepasse, nouv.nom, nouv.abonnement, nouv.sexe,
                       nouv.date_naiss.jour, nouv.date_naiss.mois, nouv.date_naiss.annee,
                       nouv.telephone);
                tr = 1;
            }
            else {
                fprintf(f1, "%s %s %s %s %s %s %s %s %s\n", 
                       m.id, m.motdepasse, m.nom, m.abonnement, m.sexe,
                       m.date_naiss.jour, m.date_naiss.mois, m.date_naiss.annee,
                       m.telephone);
            }
        }
        fclose(f);
        fclose(f1);
        
        if(tr) {
            remove(filename);
            rename("temp.txt", filename);
        } else {
            remove("temp.txt");
        }
        return tr;
    }
    return 0;
}

/* ==============================================
   FONCTION : Supprimer un membre (version publique)
   ============================================== */
int supprimer_membre(char id[], char filename[]) {
    return supprimer_membre_avec_fichier(id, filename);
}

/* ==============================================
   FONCTION : Supprimer un membre (version interne)
   ============================================== */
int supprimer_membre_avec_fichier(char id[], char filename[]) {
    FILE *f, *temp;
    membre m;
    int trouve = 0;
    
    f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier %s\n", filename);
        return 0;
    }
    
    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erreur: Impossible de créer le fichier temporaire\n");
        fclose(f);
        return 0;
    }
    
    while(fscanf(f, "%s %s %s %s %s %s %s %s %s", 
                m.id, m.motdepasse, m.nom, m.abonnement, m.sexe,
                m.date_naiss.jour, m.date_naiss.mois, m.date_naiss.annee,
                m.telephone) != EOF) {
        if (strcmp(m.id, id) != 0) {
            fprintf(temp, "%s %s %s %s %s %s %s %s %s\n", 
                   m.id, m.motdepasse, m.nom, m.abonnement, m.sexe,
                   m.date_naiss.jour, m.date_naiss.mois, m.date_naiss.annee,
                   m.telephone);
        } else {
            trouve = 1;
        }
    }
    
    fclose(f);
    fclose(temp);
    
    if (trouve) {
        remove(filename);
        rename("temp.txt", filename);
        return 1;
    } else {
        remove("temp.txt");
        return 0;
    }
}

/* ==============================================
   FONCTION : Chercher un membre par ID
   ============================================== */
membre chercher_membre(char x[], char filename[]) {
    membre m;
    FILE *f = fopen(filename, "r");
    
    if(f != NULL) {
        while(fscanf(f, "%s %s %s %s %s %s %s %s %s", 
                    m.id, m.motdepasse, m.nom, m.abonnement, m.sexe,
                    m.date_naiss.jour, m.date_naiss.mois, m.date_naiss.annee,
                    m.telephone) != EOF) {
            if(strcmp(x, m.id) == 0) {
                fclose(f);
                return m;
            }
        }
        fclose(f);
    }
    // Si non trouvé
    strcpy(m.id, "-1");
    return m;
}

/* ==============================================
   FONCTION : Afficher tous les membres dans TreeView
   ============================================== */
void afficher_membres(GtkTreeView *treeview, char filename[]) {
    GtkListStore *store;
    FILE *file;
    char date_complete[100];
    char id[20], motdepasse[20], nom[20], abonnement[30], sexe[10];
    char jour[10], mois[10], annee[10], telephone[15];
    
    file = fopen(filename, "r");
    if (!file) {
        printf("Fichier %s non trouvé\n", filename);
        return;
    }

    // Créer le ListStore avec les bonnes colonnes
    store = gtk_list_store_new(COLUMNS, 
                              G_TYPE_STRING,  // ID
                              G_TYPE_STRING,  // Mot de passe
                              G_TYPE_STRING,  // Nom
                              G_TYPE_STRING,  // Abonnement
                              G_TYPE_STRING,  // Sexe
                              G_TYPE_STRING,  // Date Naissance
                              G_TYPE_STRING); // Téléphone

    while(fscanf(file, "%s %s %s %s %s %s %s %s %s", 
                id, motdepasse, nom, abonnement, sexe, 
                jour, mois, annee, telephone) != EOF) {
        
        // Construire la date complète
        snprintf(date_complete, sizeof(date_complete), "%s/%s/%s", jour, mois, annee);
        
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 
                          COL_ID, id,
                          COL_MOTDEPASSE, motdepasse, 
                          COL_NOM, nom,
                          COL_ABONNEMENT, abonnement,
                          COL_SEXE, sexe,
                          COL_DATE_NAISSANCE, date_complete,
                          COL_TELEPHONE, telephone,
                          -1);
    }
    fclose(file);

    // Configurer les colonnes seulement si elles n'existent pas
    if (gtk_tree_view_get_columns(treeview) == NULL) {
        GtkTreeViewColumn *column;
        GtkCellRenderer *renderer;

        // Colonne ID
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", COL_ID, NULL);
        gtk_tree_view_column_set_fixed_width(column, 80);
        gtk_tree_view_append_column(treeview, column);

        // Colonne Nom
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", COL_NOM, NULL);
        gtk_tree_view_column_set_fixed_width(column, 120);
        gtk_tree_view_append_column(treeview, column);

        // Colonne Abonnement
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Abonnement", renderer, "text", COL_ABONNEMENT, NULL);
        gtk_tree_view_column_set_fixed_width(column, 100);
        gtk_tree_view_append_column(treeview, column);

        // Colonne Sexe
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", COL_SEXE, NULL);
        gtk_tree_view_column_set_fixed_width(column, 80);
        gtk_tree_view_append_column(treeview, column);

        // Colonne Date Naissance
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date Naissance", renderer, "text", COL_DATE_NAISSANCE, NULL);
        gtk_tree_view_column_set_fixed_width(column, 120);
        gtk_tree_view_append_column(treeview, column);

        // Colonne Téléphone
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Téléphone", renderer, "text", COL_TELEPHONE, NULL);
        gtk_tree_view_column_set_fixed_width(column, 100);
        gtk_tree_view_append_column(treeview, column);
    }

    // Appliquer le modèle au TreeView
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
    g_object_unref(store);  // Décrémenter le compteur de référence
}

/* ==============================================
   FONCTION : Vérifier si un membre existe
   ============================================== */
int verifier_existant_membre(char id[], char filename[]) {
    int verif = 0;
    membre m;
    FILE *f = fopen(filename, "r");
    
    if (f != NULL) {
        while (fscanf(f, "%s %s %s %s %s %s %s %s %s", 
                     m.id, m.motdepasse, m.nom, m.abonnement, m.sexe,
                     m.date_naiss.jour, m.date_naiss.mois, m.date_naiss.annee,
                     m.telephone) != EOF) {
            if (strcmp(id, m.id) == 0) {
                verif = 1;
                break;
            }
        }
        fclose(f);
    }
    return verif;
}

/* ==============================================
   FONCTION : Vérifier la connexion
   ============================================== */
int verifier_connexion(char id[], char mdp[], char filename[]) {
    FILE *f;
    int userExists = 0;
    char test_id[20], test_mdp[20];

    f = fopen(filename, "r");
    if (f != NULL) {
        // Lire seulement ID et mot de passe
        while (fscanf(f, "%s %s", test_id, test_mdp) != EOF) {
            // Lire le reste de la ligne sans l'utiliser
            char reste[200];
            fgets(reste, sizeof(reste), f);
            
            if (strcmp(test_id, id) == 0 && strcmp(test_mdp, mdp) == 0) {
                userExists = 1;
                break;
            }
        }
        fclose(f);
    }
    return userExists;
}
