#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "membre.h"
#include "support.h"
#include "callbacks.h"

/* ==============================================
   VARIABLES GLOBALES
   ============================================== */
int sexe_selectionne = 1;  // 1 = masculin, 2 = féminin
gboolean treeview_initialise = FALSE;

/* ==============================================
   FONCTIONS UTILITAIRES
   ============================================== */

/* Fonction utilitaire pour afficher les erreurs */
void afficher_erreur(GtkWidget *parent, const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(parent),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_ERROR,
        GTK_BUTTONS_OK,
        "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

/* Fonction utilitaire pour afficher les infos */
void afficher_info(GtkWidget *parent, const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(parent),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

/* Fonction pour debugger les widgets disponibles */
void debug_widgets(GtkWidget *parent) {
    if (!parent) {
        g_print("\n=== DEBUG Widgets: Parent NULL ===\n");
        return;
    }
    
    g_print("\n=== DEBUG Widgets disponibles ===\n");
    g_print("Parent widget: %s (type: %s)\n", 
            gtk_widget_get_name(parent) ? gtk_widget_get_name(parent) : "no-name",
            G_OBJECT_TYPE_NAME(parent));
    
    /* Obtenir la fenêtre top-level */
    GtkWidget *toplevel = gtk_widget_get_toplevel(parent);
    if (toplevel && toplevel != parent) {
        g_print("Top-level: %s (type: %s)\n", 
                gtk_widget_get_name(toplevel) ? gtk_widget_get_name(toplevel) : "no-name",
                G_OBJECT_TYPE_NAME(toplevel));
    }
    
    /* Liste étendue de widgets à tester */
    const char *test_widgets[] = {
        /* Fenêtres */
        "window1", "window2", "window_admin", "window_membre", "GtkWindow",
        
        /* Entries - tous les noms possibles */
        "dhiainputid", "entry_id", "input_id", "id_entry", "id",
        "dhiainputnom", "entry_nom", "input_nom", "nom_entry", "nom",
        "dhiainputmdp", "dhiainputabonnement", "dhiainputtel", "dhiainputnomc",
        
        /* Spinbuttons - tous les noms possibles */
        "dhiaspinjour", "spin_jour", "jour_spin", "jour",
        "dhiaspinmois", "spin_mois", "mois_spin", "mois", 
        "dhiaspinanne", "dhiaspinannee", "spin_annee", "annee_spin", "annee",
        
        /* TreeViews */
        "dhiatreeview", "treeview", "dhiatreeview1", "treeview1",
        
        /* RadioButtons */
        "dhiaradiosexem", "dhiaradiosexef", "radio_masculin", "radio_feminin",
        
        NULL
    };
    
    int found_count = 0;
    for (int i = 0; test_widgets[i] != NULL; i++) {
        GtkWidget *w = lookup_widget(parent, test_widgets[i]);
        if (w) {
            g_print("✓ Trouvé: %-25s (type: %s)\n", 
                    test_widgets[i], 
                    G_OBJECT_TYPE_NAME(w));
            found_count++;
        }
    }
    
    if (found_count == 0) {
        g_print("✗ Aucun widget de test trouvé depuis ce parent!\n");
        
        /* Essayer depuis top-level */
        if (toplevel && toplevel != parent) {
            g_print("\nEssai depuis top-level:\n");
            for (int i = 0; test_widgets[i] != NULL; i++) {
                GtkWidget *w = lookup_widget(toplevel, test_widgets[i]);
                if (w) {
                    g_print("✓ Trouvé dans top-level: %-25s (type: %s)\n", 
                            test_widgets[i], 
                            G_OBJECT_TYPE_NAME(w));
                }
            }
        }
    }
    
    g_print("=== FIN DEBUG ===\n\n");
}

/* Fonction pour debugger l'état de la TreeView */
void debug_treeview(GtkWidget *treeview) {
    if (!treeview || !GTK_IS_TREE_VIEW(treeview)) {
        g_print("DEBUG TreeView: Widget invalide\n");
        return;
    }
    
    g_print("\n=== DEBUG TreeView ===\n");
    g_print("Nom: %s\n", gtk_widget_get_name(treeview));
    g_print("Type: %s\n", G_OBJECT_TYPE_NAME(treeview));
    
    /* Vérifier le modèle */
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    if (model) {
        g_print("Modèle présent: %s\n", G_OBJECT_TYPE_NAME(model));
        
        /* Compter le nombre de lignes */
        int rows = gtk_tree_model_iter_n_children(model, NULL);
        g_print("Nombre de lignes dans le modèle: %d\n", rows);
    } else {
        g_print("Modèle: AUCUN\n");
    }
    
    /* Vérifier les colonnes */
    GList *columns = gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview));
    int col_count = g_list_length(columns);
    g_print("Nombre de colonnes: %d\n", col_count);
    
    if (col_count > 0) {
        g_print("Colonnes:\n");
        GList *iter = columns;
        int i = 0;
        while (iter != NULL) {
            GtkTreeViewColumn *col = GTK_TREE_VIEW_COLUMN(iter->data);
            const gchar *title = gtk_tree_view_column_get_title(col);
            g_print("  [%d] %s\n", i++, title ? title : "(sans titre)");
            iter = g_list_next(iter);
        }
    }
    g_list_free(columns);
    
    g_print("=== FIN DEBUG TreeView ===\n\n");
}

/* Fonction pour initialiser la TreeView */
void initialiser_treeview(GtkWidget *widget) {
    if (treeview_initialise) {
        return;
    }
    
    GtkWidget *treeview = lookup_widget(widget, "dhiatreeview");
    if (!treeview) {
        g_print("ERREUR: Widget dhiatreeview non trouvé\n");
        return;
    }
    
    treeview_initialise = TRUE;
}

/* ==============================================
   FONCTIONS POUR L'INTERFACE COACHS
   ============================================== */

/* Initialiser les colonnes de la TreeView des coaches */
/* Initialiser les colonnes de la TreeView des coaches */
void init_treeview_columns(GtkWidget *treeview) {
    if (!treeview || !GTK_IS_TREE_VIEW(treeview)) {
        g_print("ERREUR: TreeView invalide pour init_treeview_columns\n");
        return;
    }
    
    g_print("Initialisation des colonnes de la TreeView...\n");
    
    /* D'abord, supprimer toutes les colonnes existantes - Méthode GTK2 */
    GList *columns = gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview));
    GList *iter = columns;
    
    while (iter != NULL) {
        GtkTreeViewColumn *column = GTK_TREE_VIEW_COLUMN(iter->data);
        gtk_tree_view_remove_column(GTK_TREE_VIEW(treeview), column);
        iter = g_list_next(iter);
    }
    
    if (columns) {
        g_list_free(columns);
    }
    
    /* Créer les colonnes */
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    char *titres[] = {"ID", "Nom", "Prénom", "Jour", "Heure", "Sexe"};
    int i;
    
    for (i = 0; i < 6; i++) {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(
            titres[i],        /* Titre de la colonne */
            renderer,         /* Renderer */
            "text", i,        /* Colonne dans le modèle */
            NULL              /* Fin des attributs */
        );
        
        /* Optionnel: définir la largeur */
        gtk_tree_view_column_set_min_width(column, 80);
        gtk_tree_view_column_set_resizable(column, TRUE);
        
        /* Ajouter la colonne à la TreeView */
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        g_print("  Colonne créée: %s (index: %d)\n", titres[i], i);
    }
    
    g_print("Colonnes initialisées avec succès\n");
}

/* Charger les coaches depuis le fichier texte */
void charger_coaches(GtkWidget *treeview, const char *nom_filtre) {
    if (!treeview || !GTK_IS_TREE_VIEW(treeview)) {
        g_print("ERREUR: TreeView invalide pour charger_coaches\n");
        return;
    }
    
    g_print("Chargement des coaches...\n");
    if (nom_filtre) {
        g_print("  Filtre: %s\n", nom_filtre);
    }
    
    FILE *f = fopen("coachs.txt", "r");
    if (!f) {
        g_print("ERREUR: Impossible d'ouvrir coachs.txt\n");
        g_print("  Vérifie que le fichier existe dans le dossier courant\n");
        
        /* Créer un fichier exemple pour les tests */
        g_print("  Création d'un fichier exemple...\n");
        f = fopen("coachs.txt", "w");
        if (f) {
            fprintf(f, "001 Dupont Pierre Lundi 10h M\n");
            fprintf(f, "002 Martin Sophie Mardi 14h F\n");
            fprintf(f, "003 Bernard Jacques Mercredi 16h M\n");
            fclose(f);
            f = fopen("coachs.txt", "r");
        }
    }
    
    if (!f) {
        g_print("ERREUR: Impossible de créer/ouvrir coachs.txt\n");
        return;
    }
    
    /* Créer un nouveau modèle */
    GtkListStore *store = gtk_list_store_new(6,
        G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
        G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    
    GtkTreeIter iter;
    char id[20], nom[30], prenom[30], jour[10], heure[10], sexe[2];
    int count = 0;
    
    while (fscanf(f, "%s %s %s %s %s %s", id, nom, prenom, jour, heure, sexe) != EOF) {
        /* Appliquer le filtre si spécifié */
        int ajouter = 1;
        if (nom_filtre != NULL && strlen(nom_filtre) > 0) {
            if (strstr(nom, nom_filtre) == NULL) {
                ajouter = 0;
            }
        }
        
        if (ajouter) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                0, id,
                1, nom,
                2, prenom,
                3, jour,
                4, heure,
                5, (sexe[0] == 'M') ? "Masculin" : "Féminin",
                -1);
            count++;
            
            g_print("  Coach ajouté: %s %s (%s %s)\n", nom, prenom, jour, heure);
        }
    }
    
    fclose(f);
    
    if (count == 0) {
        g_print("  Aucun coach trouvé");
        if (nom_filtre) {
            g_print(" avec le filtre '%s'", nom_filtre);
        }
        g_print("\n");
    } else {
        g_print("  Total coaches chargés: %d\n", count);
    }
    
    /* Attacher le modèle à la TreeView */
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);  /* La TreeView a maintenant sa propre référence */
    
    g_print("Chargement terminé\n");
}

/* Récupérer le sexe sélectionné */
int get_sexe_selection(GtkWidget *window) {
    GtkWidget *radio_m = lookup_widget(window, "dhiaradiosexm");
    if (radio_m && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_m)))
        return 'M';
    else
        return 'F';
}

/* ==============================================
   SIGNALS POUR LA FENÊTRE ADMINISTRATION
   ============================================== */

void on_window_admin_show(GtkWidget *widget, gpointer user_data) {
    g_print("Fenêtre ADMINISTRATION ouverte\n");
    
    /* Initialiser la TreeView */
    initialiser_treeview(widget);
    
    /* Initialiser le radiobutton masculin comme sélectionné */
    GtkWidget *radio_masculin = lookup_widget(widget, "dhiaradiosexem");
    if (radio_masculin) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_masculin), TRUE);
        sexe_selectionne = 1;
    }
    
    /* Charger les données */
    GtkWidget *treeview = lookup_widget(widget, "dhiatreeview");
    if (treeview) {
        afficher_membres(GTK_TREE_VIEW(treeview), "membres.txt");
    }
}

/* ==============================================
   SIGNALS POUR LES RADIOBUTTONS
   ============================================== */

void on_dhiaradiosexem_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        sexe_selectionne = 1;
        g_print("Sexe sélectionné: Masculin\n");
    }
}

void on_dhiaradiosexef_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        sexe_selectionne = 2;
        g_print("Sexe sélectionné: Féminin\n");
    }
}

/* ==============================================
   SIGNALS POUR LES BOUTONS PRINCIPAUX (ADMIN)
   ============================================== */

/* BOUTON AJOUTER */
void on_dhiabuttonajout_clicked(GtkWidget *widget, gpointer user_data) {
    g_print("Bouton AJOUTER cliqué\n");
    
    /* DEBUG : Voir quels widgets sont disponibles */
    debug_widgets(widget);
    
    /* Récupérer la fenêtre parente */
    GtkWidget *window = gtk_widget_get_toplevel(widget);
    if (!window) {
        g_print("ERREUR: Impossible de trouver la fenêtre parente\n");
        return;
    }
    
    /* DEBUG depuis la fenêtre aussi */
    debug_widgets(window);
    
    /* Récupérer les widgets - ESSAYER DIFFÉRENTS NOMS */
    GtkWidget *entry_id = lookup_widget(window, "dhiainputid");
    if (!entry_id) entry_id = lookup_widget(widget, "dhiainputid");
    
    GtkWidget *entry_nom = lookup_widget(window, "dhiainputnom");
    if (!entry_nom) entry_nom = lookup_widget(widget, "dhiainputnom");
    
    GtkWidget *treeview = lookup_widget(window, "dhiatreeview");
    if (!treeview) treeview = lookup_widget(widget, "dhiatreeview");
    
    /* SPINBUTTONS - ESSAYER DIFFÉRENTS NOMS */
    GtkWidget *spin_jour = lookup_widget(window, "dhiaspinjour");
    if (!spin_jour) spin_jour = lookup_widget(widget, "dhiaspinjour");
    
    GtkWidget *spin_mois = lookup_widget(window, "dhiaspinmois");
    if (!spin_mois) spin_mois = lookup_widget(widget, "dhiaspinmois");
    
    GtkWidget *spin_annee = lookup_widget(window, "dhiaspinanne");
    if (!spin_annee) spin_annee = lookup_widget(window, "dhiaspinannee");
    if (!spin_annee) spin_annee = lookup_widget(widget, "dhiaspinanne");
    if (!spin_annee) spin_annee = lookup_widget(widget, "dhiaspinannee");
    
    /* Autres widgets */
    GtkWidget *entry_mdp = lookup_widget(window, "dhiainputmdp");
    GtkWidget *entry_abonnement = lookup_widget(window, "dhiainputabonnement");
    GtkWidget *entry_tel = lookup_widget(window, "dhiainputtel");
    
    /* Vérification CRITIQUE */
    if (!entry_id) g_print("ERREUR: dhiainputid NON TROUVÉ\n");
    if (!entry_nom) g_print("ERREUR: dhiainputnom NON TROUVÉ\n");
    if (!treeview) g_print("ERREUR: dhiatreeview NON TROUVÉ\n");
    if (!spin_jour) g_print("ERREUR: dhiaspinjour NON TROUVÉ\n");
    if (!spin_mois) g_print("ERREUR: dhiaspinmois NON TROUVÉ\n");
    if (!spin_annee) g_print("ERREUR: spin_annee NON TROUVÉ (dhiaspinanne/dhiaspinannee)\n");
    
    if (!entry_id || !entry_nom || !treeview) {
        afficher_erreur(window, "Erreur: widgets critiques non trouvés (voir terminal)");
        return;
    }
    
    /* Récupérer les valeurs avec vérification */
    const char *id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    const char *nom = gtk_entry_get_text(GTK_ENTRY(entry_nom));
    
    /* Gérer les widgets optionnels */
    const char *mdp = "";
    const char *abonnement = "";
    const char *tel = "";
    int jour = 1, mois = 1, annee = 2000;
    
    if (entry_mdp) mdp = gtk_entry_get_text(GTK_ENTRY(entry_mdp));
    if (entry_abonnement) abonnement = gtk_entry_get_text(GTK_ENTRY(entry_abonnement));
    if (entry_tel) tel = gtk_entry_get_text(GTK_ENTRY(entry_tel));
    
    if (spin_jour) jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour));
    if (spin_mois) mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois));
    if (spin_annee) annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee));
    
    /* Valider les champs obligatoires */
    if (strlen(id) == 0 || strlen(nom) == 0) {
        afficher_erreur(window, "L'identifiant et le nom sont obligatoires");
        return;
    }
    
    /* Créer la structure membre */
    membre nouveau_membre;
    strncpy(nouveau_membre.id, id, sizeof(nouveau_membre.id) - 1);
    strncpy(nouveau_membre.motdepasse, mdp, sizeof(nouveau_membre.motdepasse) - 1);
    strncpy(nouveau_membre.nom, nom, sizeof(nouveau_membre.nom) - 1);
    strncpy(nouveau_membre.abonnement, abonnement, sizeof(nouveau_membre.abonnement) - 1);
    strncpy(nouveau_membre.sexe, (sexe_selectionne == 1) ? "Masculin" : "Féminin", 
            sizeof(nouveau_membre.sexe) - 1);
    snprintf(nouveau_membre.date_naiss.jour, sizeof(nouveau_membre.date_naiss.jour), "%d", jour);
    snprintf(nouveau_membre.date_naiss.mois, sizeof(nouveau_membre.date_naiss.mois), "%d", mois);
    snprintf(nouveau_membre.date_naiss.annee, sizeof(nouveau_membre.date_naiss.annee), "%d", annee);
    strncpy(nouveau_membre.telephone, tel, sizeof(nouveau_membre.telephone) - 1);
    
    /* Vérifier si le membre existe déjà */
    char *id_copie = strdup(id);
    if (verifier_existant_membre(id_copie, "membres.txt")) {
        afficher_erreur(window, "Un membre avec cet ID existe déjà");
        free(id_copie);
        return;
    }
    free(id_copie);
    
    /* Ajouter au fichier */
    if (!ajouter_membre(nouveau_membre, "membres.txt")) {
        afficher_erreur(window, "Erreur lors de l'ajout du membre");
        return;
    }
    
    g_print("Membre %s ajouté avec succès\n", id);
    
    /* Vider les champs */
    gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    if (entry_mdp) gtk_entry_set_text(GTK_ENTRY(entry_mdp), "");
    gtk_entry_set_text(GTK_ENTRY(entry_nom), "");
    if (entry_abonnement) gtk_entry_set_text(GTK_ENTRY(entry_abonnement), "");
    if (entry_tel) gtk_entry_set_text(GTK_ENTRY(entry_tel), "");
    if (spin_jour) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_jour), 1);
    if (spin_mois) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mois), 1);
    if (spin_annee) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_annee), 2000);
    
    /* Sélectionner masculin par défaut */
    GtkWidget *radio_masculin = lookup_widget(widget, "dhiaradiosexem");
    if (radio_masculin) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_masculin), TRUE);
        sexe_selectionne = 1;
    }
    
    /* Rafraîchir la TreeView */
    afficher_membres(GTK_TREE_VIEW(treeview), "membres.txt");
}

/* BOUTON MODIFIER */
void on_button1_clicked(GtkWidget *widget, gpointer user_data) {
    g_print("Bouton MODIFIER cliqué\n");
    
    GtkWidget *window_admin = lookup_widget(widget, "window_admin");
    if (!window_admin) {
        window_admin = gtk_widget_get_toplevel(widget);
    }
    
    /* Vérifier qu'un membre est sélectionné dans la TreeView */
    GtkWidget *treeview = lookup_widget(widget, "dhiatreeview");
    if (!treeview) {
        afficher_erreur(window_admin, "TreeView non trouvée");
        return;
    }
    
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) {
        afficher_erreur(window_admin, "Veuillez sélectionner un membre à modifier");
        return;
    }
    
    /* Récupérer les nouvelles valeurs des champs */
    GtkWidget *entry_id = lookup_widget(widget, "dhiainputid");
    GtkWidget *entry_mdp = lookup_widget(widget, "dhiainputmdp");
    GtkWidget *entry_nom = lookup_widget(widget, "dhiainputnom");
    GtkWidget *entry_abonnement = lookup_widget(widget, "dhiainputabonnement");
    GtkWidget *entry_tel = lookup_widget(widget, "dhiainputtel");
    GtkWidget *spin_jour = lookup_widget(widget, "dhiaspinjour");
    GtkWidget *spin_mois = lookup_widget(widget, "dhiaspinmois");
    GtkWidget *spin_annee = lookup_widget(widget, "dhiaspinanne");
    
    if (!entry_id || !entry_nom) {
        afficher_erreur(window_admin, "Erreur: champs non trouvés");
        return;
    }
    
    const char *id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    const char *mdp = gtk_entry_get_text(GTK_ENTRY(entry_mdp));
    const char *nouveau_nom = gtk_entry_get_text(GTK_ENTRY(entry_nom));
    const char *nouvel_abonnement = gtk_entry_get_text(GTK_ENTRY(entry_abonnement));
    const char *nouveau_tel = gtk_entry_get_text(GTK_ENTRY(entry_tel));
    int jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour));
    int mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois));
    int annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee));
    
    /* Valider les champs */
    if (strlen(id) == 0 || strlen(nouveau_nom) == 0) {
        afficher_erreur(window_admin, "L'identifiant et le nom sont obligatoires");
        return;
    }
    
    /* Récupérer l'ID original de la ligne sélectionnée */
    gchar *id_original;
    gtk_tree_model_get(model, &iter, 0, &id_original, -1);
    
    /* Créer la structure modifiée */
    membre membre_modifie;
    strncpy(membre_modifie.id, id, sizeof(membre_modifie.id) - 1);
    strncpy(membre_modifie.motdepasse, mdp, sizeof(membre_modifie.motdepasse) - 1);
    strncpy(membre_modifie.nom, nouveau_nom, sizeof(membre_modifie.nom) - 1);
    strncpy(membre_modifie.abonnement, nouvel_abonnement, sizeof(membre_modifie.abonnement) - 1);
    strncpy(membre_modifie.sexe, (sexe_selectionne == 1) ? "Masculin" : "Féminin",
            sizeof(membre_modifie.sexe) - 1);
    snprintf(membre_modifie.date_naiss.jour, sizeof(membre_modifie.date_naiss.jour), "%d", jour);
    snprintf(membre_modifie.date_naiss.mois, sizeof(membre_modifie.date_naiss.mois), "%d", mois);
    snprintf(membre_modifie.date_naiss.annee, sizeof(membre_modifie.date_naiss.annee), "%d", annee);
    strncpy(membre_modifie.telephone, nouveau_tel, sizeof(membre_modifie.telephone) - 1);
    
    /* Modifier dans le fichier */
    if (!modifier_membre(id_original, membre_modifie, "membres.txt")) {
        afficher_erreur(window_admin, "Erreur lors de la modification");
        g_free(id_original);
        return;
    }
    
    g_free(id_original);
    
    /* Rafraîchir la TreeView */
    afficher_membres(GTK_TREE_VIEW(treeview), "membres.txt");
}

/* BOUTON SUPPRIMER */
void on_button2_clicked(GtkWidget *widget, gpointer user_data) {
    g_print("Bouton SUPPRIMER cliqué\n");
    
    GtkWidget *window_admin = lookup_widget(widget, "window_admin");
    if (!window_admin) {
        window_admin = gtk_widget_get_toplevel(widget);
    }
    
    GtkWidget *treeview = lookup_widget(widget, "dhiatreeview");
    if (!treeview) {
        afficher_erreur(window_admin, "TreeView non trouvée");
        return;
    }
    
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) {
        afficher_erreur(window_admin, "Veuillez sélectionner un membre à supprimer");
        return;
    }
    
    /* Récupérer l'ID */
    gchar *id;
    gtk_tree_model_get(model, &iter, 0, &id, -1);
    
    g_print("Suppression du membre: %s\n", id);
    
    /* Confirmation */
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window_admin),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Voulez-vous vraiment supprimer le membre %s ?", id);
    
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    if (response != GTK_RESPONSE_YES) {
        g_free(id);
        return;
    }
    
    /* Supprimer du fichier */
    if (!supprimer_membre(id, "membres.txt")) {
        afficher_erreur(window_admin, "Erreur lors de la suppression");
        g_free(id);
        return;
    }
    
    /* Supprimer de la TreeView */
    if (gtk_list_store_remove(GTK_LIST_STORE(model), &iter)) {
        /* Rafraîchir la TreeView */
        afficher_membres(GTK_TREE_VIEW(treeview), "membres.txt");
    } 
    
    g_free(id);
}

/* BOUTON RECHERCHER (ADMIN) */
void on_dhiabuttonrech_clicked(GtkWidget *widget, gpointer user_data) {
    g_print("Bouton RECHERCHER (admin) cliqué\n");
    
    GtkWidget *entry_id = lookup_widget(widget, "dhiainputid");
    GtkWidget *treeview = lookup_widget(widget, "dhiatreeview");
    
    if (!entry_id || !treeview) {
        g_print("ERREUR: Widgets non trouvés\n");
        return;
    }
    
    char *id_recherche = (char*)gtk_entry_get_text(GTK_ENTRY(entry_id));
    
    g_print("Recherche du membre avec ID: %s\n", id_recherche);
    
    if (strlen(id_recherche) == 0) {
        g_print("ERREUR: ID de recherche vide\n");
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(widget),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez entrer un identifiant à rechercher");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    /* Recherche dans le fichier */
    g_print("Recherche dans le fichier membres.txt...\n");
    membre found = chercher_membre(id_recherche, "membres.txt");
    
    if (strcmp(found.id, "-1") != 0) {
        g_print("SUCCÈS: Membre trouvé: ID=%s, Nom=%s\n", found.id, found.nom);
        
        /* Remplir les champs avec les données */
        GtkWidget *entry_mdp = lookup_widget(widget, "dhiainputmdp");
        GtkWidget *entry_nom = lookup_widget(widget, "dhiainputnom");
        GtkWidget *entry_abonnement = lookup_widget(widget, "dhiainputabonnement");
        GtkWidget *entry_tel = lookup_widget(widget, "dhiainputtel");
        GtkWidget *spin_jour = lookup_widget(widget, "dhiaspinjour");
        GtkWidget *spin_mois = lookup_widget(widget, "dhiaspinmois");
        GtkWidget *spin_annee = lookup_widget(widget, "dhiaspinanne");
        
        gtk_entry_set_text(GTK_ENTRY(entry_id), found.id);
        if (entry_mdp) gtk_entry_set_text(GTK_ENTRY(entry_mdp), found.motdepasse);
        if (entry_nom) gtk_entry_set_text(GTK_ENTRY(entry_nom), found.nom);
        if (entry_abonnement) gtk_entry_set_text(GTK_ENTRY(entry_abonnement), found.abonnement);
        if (entry_tel) gtk_entry_set_text(GTK_ENTRY(entry_tel), found.telephone);
        if (spin_jour) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_jour), atoi(found.date_naiss.jour));
        if (spin_mois) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mois), atoi(found.date_naiss.mois));
        if (spin_annee) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_annee), atoi(found.date_naiss.annee));
        
        g_print("Champs remplis avec les données du membre\n");
        
        /* Sélectionner le bon radiobutton */
        GtkWidget *radio_masculin = lookup_widget(widget, "dhiaradiosexem");
        GtkWidget *radio_feminin = lookup_widget(widget, "dhiaradiosexef");
        
        if (radio_masculin && radio_feminin) {
            if (strcmp(found.sexe, "Masculin") == 0) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_masculin), TRUE);
                sexe_selectionne = 1;
                g_print("Radiobutton Masculin sélectionné\n");
            } else {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_feminin), TRUE);
                sexe_selectionne = 2;
                g_print("Radiobutton Féminin sélectionné\n");
            }
        }
        
        g_print("Opération de recherche terminée avec succès\n");
        
    } else {
        g_print("ERREUR: Membre non trouvé: ID=%s\n", id_recherche);
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(widget),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Membre %s non trouvé", id_recherche);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

/* ==============================================
   SIGNALS POUR L'INTERFACE COACHS (NOUVELLE INTERFACE)
   ============================================== */

/* Afficher les coaches au démarrage de la fenêtre membre */
void on_window_membre_show(GtkWidget *widget, gpointer user_data) {
    g_print("\n=== on_window_membre_show ===\n");
    
    /* DEBUG des widgets disponibles */
    debug_widgets(widget);
    
    /* Chercher la TreeView coachs */
    GtkWidget *treeview = lookup_widget(widget, "dhiatreeview");
    if (!treeview) {
        treeview = lookup_widget(widget, "treeview1");
    }
    if (!treeview) {
        treeview = lookup_widget(widget, "treeview");
    }
    
    if (!treeview) {
        g_print("ERREUR: Aucune TreeView trouvée\n");
        return;
    }
    
    g_print("TreeView trouvée: %s\n", gtk_widget_get_name(treeview));
    
    /* DEBUG de l'état actuel de la TreeView */
    debug_treeview(treeview);
    
    /* Initialiser les colonnes */
    init_treeview_columns(treeview);
    
    /* DEBUG après initialisation */
    debug_treeview(treeview);
    
    /* Charger les données */
    charger_coaches(treeview, NULL);
    
    /* DEBUG final */
    debug_treeview(treeview);
    
    g_print("=== FIN on_window_membre_show ===\n\n");
}

/* RECHERCHER UN COACH */
void on_dhiabuttonrech1_clicked(GtkWidget *widget, gpointer user_data) {
    g_print("Bouton RECHERCHER (coach) cliqué\n");
    
    /* DEBUG d'abord */
    debug_widgets(widget);
    
    /* Chercher les widgets avec plusieurs noms possibles */
    GtkWidget *entry = lookup_widget(widget, "dhiainputnomc");
    if (!entry) {
        g_print("ERREUR: Entry dhiainputnomc non trouvé\n");
        return;
    }
    
    /* Chercher la TreeView - ESSAYER DIFFÉRENTS NOMS */
    GtkWidget *treeview = lookup_widget(widget, "dhiatreeview");  /* 1. dhiatreeview */
    if (!treeview) treeview = lookup_widget(widget, "treeview1");  /* 2. treeview1 */
    if (!treeview) treeview = lookup_widget(widget, "treeview");   /* 3. treeview */
    
    /* Si pas trouvé, chercher depuis la fenêtre parente */
    if (!treeview) {
        GtkWidget *window = gtk_widget_get_toplevel(widget);
        if (window && window != widget) {
            treeview = lookup_widget(window, "dhiatreeview");
            if (!treeview) treeview = lookup_widget(window, "treeview1");
            if (!treeview) treeview = lookup_widget(window, "treeview");
        }
    }
    
    if (!treeview) {
        g_print("ERREUR CRITIQUE: TreeView non trouvée pour recherche coach\n");
        g_print("Noms essayés: dhiatreeview, treeview1, treeview\n");
        
        GtkWidget *window = gtk_widget_get_toplevel(widget);
        if (window) {
            afficher_erreur(window, 
                "TreeView non trouvée pour la recherche coach.\n"
                "Vérifiez dans Glade le nom de la TreeView.");
        }
        return;
    }
    
    g_print("SUCCÈS: Entry et TreeView trouvés pour recherche coach\n");
    
    /* Récupérer le nom à rechercher */
    const char *nom = gtk_entry_get_text(GTK_ENTRY(entry));
    
    if (strlen(nom) > 0) {
        g_print("Recherche coach par nom: %s\n", nom);
        charger_coaches(treeview, nom);
    } else {
        g_print("Chargement de tous les coaches (nom vide)\n");
        charger_coaches(treeview, NULL);
    }
}

/* AFFILIER UN COACH */
void on_dhiabuttonaffiliations_clicked(GtkWidget *widget, gpointer user_data) {
    g_print("Bouton AFFILIATIONS cliqué\n");
    
    /* DEBUG d'abord */
    debug_widgets(widget);
    
    /* Chercher la TreeView par différents noms possibles */
    GtkWidget *treeview = NULL;
    
    /* Essayer depuis le widget lui-même */
    treeview = lookup_widget(widget, "dhiatreeview1");
    if (!treeview) treeview = lookup_widget(widget, "treeview1");
    if (!treeview) treeview = lookup_widget(widget, "dhiatreeview");
    if (!treeview) treeview = lookup_widget(widget, "treeview");
    
    /* Si pas trouvé, essayer depuis la fenêtre parente */
    if (!treeview) {
        GtkWidget *window = gtk_widget_get_toplevel(widget);
        if (window && window != widget) {
            treeview = lookup_widget(window, "dhiatreeview1");
            if (!treeview) treeview = lookup_widget(window, "treeview1");
            if (!treeview) treeview = lookup_widget(window, "dhiatreeview");
            if (!treeview) treeview = lookup_widget(window, "treeview");
        }
    }
    
    if (!treeview) {
        g_print("ERREUR CRITIQUE: TreeView non trouvée. Noms essayés:\n");
        g_print("  dhiatreeview1, treeview1, dhiatreeview, treeview\n");
        
        GtkWidget *window = gtk_widget_get_toplevel(widget);
        afficher_erreur(window, 
            "TreeView non trouvée.\n"
            "Vérifiez dans Glade que la TreeView a un nom (propriété 'Name').\n"
            "Le nom est probablement différent de 'dhiatreeview1'.");
        return;
    }
    
    g_print("SUCCÈS: TreeView trouvée: %s\n", gtk_widget_get_name(treeview));
    
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        char *id, *nom, *prenom, *jour, *heure, *sexe;
        
        gtk_tree_model_get(model, &iter,
                           0, &id,
                           1, &nom,
                           2, &prenom,
                           3, &jour,
                           4, &heure,
                           5, &sexe,
                           -1);
        
        g_print("Coach affilié : %s %s - Disponible le %s à %s (%s)\n", 
                nom, prenom, jour, heure, sexe);
        
        /* Afficher une boîte de dialogue de confirmation */
        GtkWidget *window = gtk_widget_get_toplevel(widget);
        GtkWidget *dialog = gtk_message_dialog_new(
            GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Coach affilié avec succès:\n%s %s\nDisponible le %s à %s",
            nom, prenom, jour, heure);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        
        g_free(id);
        g_free(nom);
        g_free(prenom);
        g_free(jour);
        g_free(heure);
        g_free(sexe);
    } else {
        g_print("Aucun coach sélectionné.\n");
        GtkWidget *window = gtk_widget_get_toplevel(widget);
        afficher_erreur(window, "Veuillez sélectionner un coach dans la liste");
    }
}

/* Fonction avec faute de frappe (1 'f') - pour compatibilité avec Glade */
void on_dhiabuttonaffilations_clicked(GtkWidget *widget, gpointer user_data) {
    g_print("Bouton AFFILATIONS (ancien nom) cliqué - Redirection vers nouvelle fonction\n");
    
    /* Appelle simplement la fonction correcte */
    on_dhiabuttonaffiliations_clicked(widget, user_data);
}

/* ==============================================
   SIGNALS POUR LES ÉVÉNEMENTS TREEVIEW
   ============================================== */

void on_dhiatreeview_row_activated(GtkTreeView *treeview, 
                                   GtkTreePath *path, 
                                   GtkTreeViewColumn *column, 
                                   gpointer user_data) {
    g_print("Ligne de la TreeView (admin) activée\n");
    
    /* Récupérer le modèle et l'itérateur */
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    GtkTreeIter iter;
    
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        /* Récupérer les valeurs de la ligne */
        gchar *id, *nom, *abonnement, *tel;
        gtk_tree_model_get(model, &iter,
            0, &id,
            1, &nom,
            2, &abonnement,
            3, &tel,
            -1);
        
        g_print("Ligne sélectionnée: ID=%s, Nom=%s\n", id, nom);
        
        /* Trouver la fenêtre parente */
        GtkWidget *window = GTK_WIDGET(user_data);
        if (!window) {
            window = gtk_widget_get_toplevel(GTK_WIDGET(treeview));
        }
        
        /* Remplir les champs avec les données */
        if (window) {
            GtkWidget *entry_id = lookup_widget(window, "dhiainputid");
            GtkWidget *entry_mdp = lookup_widget(window, "dhiainputmdp");
            GtkWidget *entry_nom = lookup_widget(window, "dhiainputnom");
            GtkWidget *entry_abonnement = lookup_widget(window, "dhiainputabonnement");
            GtkWidget *entry_tel = lookup_widget(window, "dhiainputtel");
            
            if (entry_id) gtk_entry_set_text(GTK_ENTRY(entry_id), id);
            if (entry_nom) gtk_entry_set_text(GTK_ENTRY(entry_nom), nom);
            if (entry_abonnement) gtk_entry_set_text(GTK_ENTRY(entry_abonnement), abonnement);
            if (entry_tel) gtk_entry_set_text(GTK_ENTRY(entry_tel), tel);
            
            /* Rechercher les informations complètes pour remplir les autres champs */
            membre m = chercher_membre(id, "membres.txt");
            if (strcmp(m.id, "-1") != 0) {
                GtkWidget *spin_jour = lookup_widget(window, "dhiaspinjour");
                GtkWidget *spin_mois = lookup_widget(window, "dhiaspinmois");
                GtkWidget *spin_annee = lookup_widget(window, "dhiaspinanne");
                GtkWidget *radio_masculin = lookup_widget(window, "dhiaradiosexem");
                GtkWidget *radio_feminin = lookup_widget(window, "dhiaradiosexef");
                
                if (entry_mdp) gtk_entry_set_text(GTK_ENTRY(entry_mdp), m.motdepasse);
                if (spin_jour) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_jour), atoi(m.date_naiss.jour));
                if (spin_mois) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mois), atoi(m.date_naiss.mois));
                if (spin_annee) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_annee), atoi(m.date_naiss.annee));
                
                if (radio_masculin && radio_feminin) {
                    if (strcmp(m.sexe, "Masculin") == 0) {
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_masculin), TRUE);
                        sexe_selectionne = 1;
                    } else {
                        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_feminin), TRUE);
                        sexe_selectionne = 2;
                    }
                }
            }
        }
        
        /* Libérer la mémoire */
        g_free(id);
        g_free(nom);
        g_free(abonnement);
        g_free(tel);
    }
}

/* ==============================================
   FONCTIONS POUR LES MENUS - IMPLÉMENTATIONS BASIQUES
   ============================================== */

void on_jour2_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Jour2 activé\n");
}

void on_item1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Item1 activé\n");
}

void on_jour3_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Jour3 activé\n");
}

void on_horaire1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Horaire1 activé\n");
}

void on_jour1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Jour1 activé\n");
}

void on_entrainement2_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Entrainement2 activé\n");
}

void on_musculation1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Musculation1 activé\n");
}

void on_musculation2_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Musculation2 activé\n");
}

void on_cardio_training1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Cardio Training1 activé\n");
}

void on_cardio_training2_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Cardio Training2 activé\n");
}

void on_cross_training1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Cross Training1 activé\n");
}

void on_circuit_training1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Circuit Training1 activé\n");
}

void on_circuit_training2_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Circuit Training2 activé\n");
}

void on_bien_etre1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Bien-être1 activé\n");
}

void on_yoga1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Yoga1 activé\n");
}

void on_yoga2_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Yoga2 activé\n");
}

void on_pstretching1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu PStretching1 activé\n");
}

void on_pstretching2_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu PStretching2 activé\n");
}

void on_meditation1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Meditation1 activé\n");
}

void on_mediation1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Médiation1 activé\n");
}

void on_cours_collectifs2_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Cours Collectifs2 activé\n");
}

void on_zumba1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Zumba1 activé\n");
}

void on_zumba2_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Zumba2 activé\n");
}

void on_boxe1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Boxe1 activé\n");
}

void on_boxe2_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Boxe2 activé\n");
}

void on_cycling1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Cycling1 activé\n");
}

void on_cycling2_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Cycling2 activé\n");
}

void on_bootcamp1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Bootcamp1 activé\n");
}

void on_bootcamp4_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Bootcamp4 activé\n");
}

void on_seance_en_groupe1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Séance en Groupe1 activé\n");
}

void on_sceace_en_groupe1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Sceace en Groupe1 activé (probablement 'Séance')\n");
}

void on_coaching___suivi2_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Coaching & Suivi2 activé\n");
}

void on_seance_decouverte1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Séance Découverte1 activé\n");
}

void on_sceance_decouverte1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Sceance Découverte1 activé (probablement 'Séance')\n");
}

void on_planification_d_objectifs1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Planification d'Objectifs1 activé\n");
}

void on_planification_d_objet1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Planification d'Objet1 activé\n");
}

void on_coaching_nutritionnel1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Coaching Nutritionnel1 activé\n");
}

void on_coaching_nutritionnel2_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Coaching Nutritionnel2 activé\n");
}

void on_avenir_1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Avenir1 activé\n");
}

void on_en_cours1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu En Cours1 activé\n");
}

void on_termine1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Terminé1 activé\n");
}

void on_annule1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("Menu Annulé1 activé\n");
}

/* ==============================================
   IMPLÉMENTATIONS VIDES POUR LES AUTRES SIGNALS
   ============================================== */

void on_dec7_clicked(GtkButton *button, gpointer user_data) {}
void on_dec8_clicked(GtkButton *button, gpointer user_data) {}
void on_chihebtreeview_row_activated2(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {}
void on_chihebcheckniveauxi_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_chihebcheckniveauxa_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_chihebbuttonevenements_clicked(GtkButton *button, gpointer user_data) {}
void on_chihebcheckniveauxd_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_chihebbuttonrech_clicked(GtkButton *button, gpointer user_data) {}
void on_chihebradiotarifg_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_chihebradiotarifp_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_dec9_clicked(GtkButton *button, gpointer user_data) {}
void on_ghbuttoninscription_clicked(GtkButton *button, gpointer user_data) {}
void on_dec10_clicked(GtkButton *button, gpointer user_data) {}
void on_talelspinnombre_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {}
void on_talelspinjour1_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {}
void on_talelspinmois1_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {}
void on_talelspinannee1_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {}
void on_talelbuttonequipement_clicked(GtkButton *button, gpointer user_data) {}
void on_talelbuttonrech1_clicked(GtkButton *button, gpointer user_data) {}
void on_dec11_clicked(GtkButton *button, gpointer user_data) {}
void on_ranatreeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {}
void on_ranabuttonrech1_clicked(GtkButton *button, gpointer user_data) {}
void on_ranabuttoncentres_clicked(GtkButton *button, gpointer user_data) {}
void on_dec12_clicked(GtkButton *button, gpointer user_data) {}
void on_dec1_clicked(GtkButton *button, gpointer user_data) {}
void on_ghbouttonsupprimer_clicked(GtkButton *button, gpointer user_data) {}
void on_dec2_clicked(GtkButton *button, gpointer user_data) {}
void on_8h___1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_10h___12h1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_14h___16h1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_16___18h1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_eyabuttonsupprimer_clicked(GtkButton *button, gpointer user_data) {}
void on_eyabuttonmodifier_clicked(GtkButton *button, gpointer user_data) {}
void on_dec3_clicked(GtkButton *button, gpointer user_data) {}
void on_talelspindispo_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {}
void on_talelspinjour_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {}
void on_talelspinmois_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {}
void on_talelspinannee_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {}
void on_talelbuttonmod_clicked(GtkButton *button, gpointer user_data) {}
void on_talelbuttonsupp_clicked(GtkButton *button, gpointer user_data) {}
void on_dec4_clicked(GtkButton *button, gpointer user_data) {}
void on_talelmenucategorie_changed(GtkOptionMenu *optionmenu, gpointer user_data) {}
void on_talelradioetatd_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_talelradioetatn_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_talelbuttonajout_clicked(GtkButton *button, gpointer user_data) {}
void on_ranaspincapacite_changed(GtkEditable *editable, gpointer user_data) {}
void on_ranatreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {}
void on_ranabuttonrech_clicked(GtkButton *button, gpointer user_data) {}
void on_ranabouttonmod_clicked(GtkButton *button, gpointer user_data) {}
void on_ranabouttonsup_clicked(GtkButton *button, gpointer user_data) {}
void on_ranabuttonajout_clicked(GtkButton *button, gpointer user_data) {}
void on_dec5_clicked(GtkButton *button, gpointer user_data) {}
void on_ranaradioproprieteei_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_ranaradioproprieteep_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_calendar2_day_selected(GtkCalendar *calendar, gpointer user_data) {}
void on_chihebtreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {}
void on_chihebbuttonrecherche_clicked(GtkButton *button, gpointer user_data) {}
void on_chihebcheckniveauavance_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_chihebbuttonajout_clicked(GtkButton *button, gpointer user_data) {}
void on_chihebbuttonmodifier_clicked(GtkButton *button, gpointer user_data) {}
void on_chihebbuttonsupprimer_clicked(GtkButton *button, gpointer user_data) {}
void on_chihebcheckniveaudebutant_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_chihebcheckniveauinter_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_dec6_clicked(GtkButton *button, gpointer user_data) {}
void on_loginbuttonlogin_clicked(GtkButton *button, gpointer user_data) {}
void on_eyabuttonajout_clicked(GtkButton *button, gpointer user_data) {
    g_print("[DEBUG] Bouton EYA AJOUTER cliqué\n");
}

void on_talelbuttonrech_clicked(GtkButton *button, gpointer user_data) {
    g_print("[DEBUG] Bouton TALEL RECHERCHER cliqué\n");
}
