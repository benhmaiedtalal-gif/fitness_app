#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "equipement.h"

/* ============ FONCTIONS MEMBRE ============ */

void
on_dhiatreeview_row_activated          (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
}

void
on_jour3_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_jour2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_item1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_dhiabuttonrech_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_dhiabuttonaffilations_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_dec7_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_dec8_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_chihebtreeview_row_activated2       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
}

void
on_chihebcheckniveauxi_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
}

void
on_chihebcheckniveauxa_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
}

void
on_chihebbuttonevenements_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_chihebcheckniveauxd_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
}

void
on_chihebbuttonrech_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_chihebradiotarifg_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
}

void
on_chihebradiotarifp_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
}

void
on_dec9_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
}

/* ============ FONCTIONS COACH ============ */

void
on_ghbuttoninscription_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_dec10_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_talelspinnombre_value_changed       (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
}

void
on_talelspinjour1_value_changed        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
}

void
on_talelspinmois1_value_changed        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
}

void
on_talelspinannee1_value_changed       (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
}

void
on_talelbuttonequipement_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    g_print("\n=== COACH: Demande equipement ===\n");
    
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *treeview = lookup_widget(window, "taleltreeview1");
    
    if (!treeview) {
        g_print("COACH ERREUR: TreeView non trouvee\n");
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_OK,
                                                  "Erreur: TreeView non trouvee!");
        gtk_window_set_title(GTK_WINDOW(dialog), "Erreur");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    if (!selection) {
        g_print("COACH: Pas de selection disponible\n");
        return;
    }
    
    GtkTreeModel *model = NULL;
    GtkTreeIter iter;
    gboolean has_selection = gtk_tree_selection_get_selected(selection, &model, &iter);
    
    if (!has_selection || !model) {
        g_print("COACH: Aucun equipement selectionne\n");
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_WARNING,
                                                  GTK_BUTTONS_OK,
                                                  "Veuillez selectionner un equipement dans la liste!");
        gtk_window_set_title(GTK_WINDOW(dialog), "Attention");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    gchar *id = NULL;
    gchar *lieu = NULL;
    gtk_tree_model_get(model, &iter, 0, &id, 1, &lieu, -1);
    
    if (!id) {
        g_print("COACH: Impossible de recuperer l'ID\n");
        return;
    }
    
    g_print("COACH: Equipement selectionne - ID: %s, Lieu: %s\n", id, lieu ? lieu : "N/A");
    
    // Recuperer les autres donnees du coach
    GtkWidget *input_heure = lookup_widget(window, "talelinputheure");
    GtkWidget *input_duree = lookup_widget(window, "talelinputduree");
    GtkWidget *spin_jour1 = lookup_widget(window, "talelspinjour1");
    GtkWidget *spin_mois1 = lookup_widget(window, "talelspinmois1");
    GtkWidget *spin_annee1 = lookup_widget(window, "talelspinannee1");
    GtkWidget *spin_nombre = lookup_widget(window, "talelspinnombre");
    
    gchar *heure = NULL;
    gchar *duree = NULL;
    if (input_heure) {
        const gchar *heure_text = gtk_entry_get_text(GTK_ENTRY(input_heure));
        heure = g_strdup(heure_text);
    }
    if (input_duree) {
        const gchar *duree_text = gtk_entry_get_text(GTK_ENTRY(input_duree));
        duree = g_strdup(duree_text);
    }
    
    gint jour = 0, mois = 0, annee = 0, nombre = 0;
    if (spin_jour1) jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour1));
    if (spin_mois1) mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois1));
    if (spin_annee1) annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee1));
    if (spin_nombre) nombre = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_nombre));
    
    // Afficher la confirmation
    gchar *message = g_strdup_printf(
        "Demande d'equipement enregistree!\n\n"
        "Equipement: %s\n"
        "Lieu: %s\n"
        "Date: %02d/%02d/%04d\n"
        "Heure: %s\n"
        "Duree: %s\n"
        "Nombre d'equipements: %d",
        id, 
        lieu ? lieu : "Non specifie",
        jour, mois, annee,
        heure ? heure : "Non specifie",
        duree ? duree : "Non specifie",
        nombre
    );
    
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                              GTK_DIALOG_DESTROY_WITH_PARENT,
                                              GTK_MESSAGE_INFO,
                                              GTK_BUTTONS_OK,
                                              "%s", message);
    
    gtk_window_set_title(GTK_WINDOW(dialog), "Confirmation");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    // Nettoyer
    g_free(message);
    g_free(id);
    if (lieu) g_free(lieu);
    if (heure) g_free(heure);
    if (duree) g_free(duree);
    
    g_print("COACH: Demande enregistree avec succes\n");
}

void
on_talelbuttonrech1_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    g_print("\n=== COACH: Recherche equipement ===\n");
    
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *input_nom = lookup_widget(window, "talelinputnomce");
    GtkWidget *treeview = lookup_widget(window, "taleltreeview1");
    
    if (!input_nom) {
        g_print("COACH: talelinputnomce non trouve\n");
        return;
    }
    
    if (!treeview) {
        g_print("COACH: taleltreeview1 non trouve\n");
        return;
    }
    
    const gchar *nom_rech = gtk_entry_get_text(GTK_ENTRY(input_nom));
    g_print("COACH: Recherche pour: %s\n", nom_rech);
    
    // Afficher tous les equipements dans la TreeView
    afficher_equipements(treeview);
    
    g_print("COACH: Recherche terminee\n");
}

void
on_dec11_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_ranatreeview1_row_activated         (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
}

void
on_ranabuttonrech1_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_ranabuttoncentres_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_dec12_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
}

/* ============ FONCTIONS ADMINISTRATION ============ */

void
on_dhiatreeview_row_activated_admin    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
}

void
on_dhiabuttonajout_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_dhiabuttonrech_clicked_admin        (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_dec1_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_button1_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_button2_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_ghbouttonsupprimer_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_dec2_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_8h___1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_10h___12h1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_14h___16h1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_16___18h1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_entrainement2_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_musculation1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_cardio_training1_activate           (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_cross_training1_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_circuit_training1_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_bien_etre1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_yoga1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_pstretching1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_meditation1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_cours_collectifs2_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_zumba1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_boxe1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_cycling1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_bootcamp1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_seance_en_groupe1_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_coaching___suivi2_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_seance_decouverte1_activate         (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_planification_d_objectifs1_activate (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_coaching_nutritionnel1_activate     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_eyabuttonsupprimer_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_eyabuttonmodifier_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_dec3_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_musculation2_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_cardio_training2_activate           (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_circuit_training2_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_yoga2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_pstretching2_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_mediation1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_zumba2_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_boxe2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_cycling2_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_bootcamp4_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_sceace_en_groupe1_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_sceance_decouverte1_activate        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_planification_d_objet1_activate     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_coaching_nutritionnel2_activate     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_talelspindispo_value_changed        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
}

void
on_talelspinjour_value_changed         (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
}

void
on_talelspinmois_value_changed         (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
}

void
on_talelspinannee_value_changed        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
}

void
on_talelbuttonmod_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
    g_print("\n=== ADMIN: Modification equipement ===\n");
    
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    // Recuperer les widgets ADMINISTRATION
    GtkWidget *input_id = lookup_widget(window, "talelinputid");
    GtkWidget *input_lieu = lookup_widget(window, "talelinputlieu");
    GtkWidget *optionmenu_categorie = lookup_widget(window, "talelmenucategorie"); // CORRIGÉ: GtkOptionMenu
    GtkWidget *spin_dispo = lookup_widget(window, "talelspindispo");
    GtkWidget *spin_jour = lookup_widget(window, "talelspinjour");
    GtkWidget *spin_mois = lookup_widget(window, "talelspinmois");
    GtkWidget *spin_annee = lookup_widget(window, "talelspinannee");
    GtkWidget *radio_d = lookup_widget(window, "talelradioetatd");
    GtkWidget *radio_n = lookup_widget(window, "talelradioetatn");
    GtkWidget *treeview = lookup_widget(window, "taleltreeview");
    
    if (!input_id) {
        g_print("ADMIN ERREUR: talelinputid non trouve\n");
        return;
    }
    
    const gchar *id = gtk_entry_get_text(GTK_ENTRY(input_id));
    if (strlen(id) == 0) {
        g_print("ADMIN: ID vide\n");
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_WARNING,
                                                  GTK_BUTTONS_OK,
                                                  "Veuillez entrer un ID d'equipement!");
        gtk_window_set_title(GTK_WINDOW(dialog), "Attention");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Verifier si l'equipement existe
    Equipement e = rechercher_equipement((char*)id);
    if (strlen(e.id) == 0) {
        g_print("ADMIN: Equipement non trouve: %s\n", id);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_OK,
                                                  "Equipement non trouve: %s", id);
        gtk_window_set_title(GTK_WINDOW(dialog), "Erreur");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Demander confirmation
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                              GTK_DIALOG_DESTROY_WITH_PARENT,
                                              GTK_MESSAGE_QUESTION,
                                              GTK_BUTTONS_YES_NO,
                                              "Voulez-vous modifier l'equipement %s?", id);
    gtk_window_set_title(GTK_WINDOW(dialog), "Confirmation");
    
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    if (response == GTK_RESPONSE_YES) {
        // Supprimer l'ancien equipement
        supprimer_equipement((char*)id);
        
        // Recuperer les nouvelles valeurs
        if (input_lieu) {
            const gchar *lieu = gtk_entry_get_text(GTK_ENTRY(input_lieu));
            strcpy(e.lieu, lieu);
        }
        
        // Pour GtkOptionMenu, on ne peut pas recuperer directement le texte
        // On le laisse tel quel s'il n'a pas ete change
        if (optionmenu_categorie) {
            // Note: GtkOptionMenu ne donne pas facilement le texte selectionne
            // On va garder l'ancienne categorie
        }
        
        if (spin_dispo) {
            e.quantite_dispo = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_dispo));
        }
        
        if (spin_jour) {
            e.jour_maintenance = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour));
        }
        
        if (spin_mois) {
            e.mois_maintenance = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois));
        }
        
        if (spin_annee) {
            e.annee_maintenance = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee));
        }
        
        if (radio_d && radio_n) {
            e.etat = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_d)) ? 1 : 0;
        }
        
        // Ajouter l'equipement modifie
        ajouter_equipement(e);
        
        // Mettre a jour la TreeView
        if (treeview) {
            afficher_equipements(treeview);
        }
        
        g_print("ADMIN: Equipement modifie avec succes: %s\n", id);
        
        // Afficher confirmation
        dialog = gtk_message_dialog_new(NULL,
                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                       GTK_MESSAGE_INFO,
                                       GTK_BUTTONS_OK,
                                       "Equipement %s modifie avec succes!", id);
        gtk_window_set_title(GTK_WINDOW(dialog), "Succes");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void
on_talelbuttonsupp_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
    g_print("\n=== ADMIN: Suppression equipement ===\n");
    
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *input_id = lookup_widget(window, "talelinputid");
    GtkWidget *treeview = lookup_widget(window, "taleltreeview");
    
    if (!input_id) {
        g_print("ADMIN ERREUR: talelinputid non trouve\n");
        return;
    }
    
    const gchar *id = gtk_entry_get_text(GTK_ENTRY(input_id));
    if (strlen(id) == 0) {
        g_print("ADMIN: ID vide\n");
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_WARNING,
                                                  GTK_BUTTONS_OK,
                                                  "Veuillez entrer un ID d'equipement!");
        gtk_window_set_title(GTK_WINDOW(dialog), "Attention");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Verifier si l'equipement existe
    Equipement e = rechercher_equipement((char*)id);
    if (strlen(e.id) == 0) {
        g_print("ADMIN: Equipement non trouve: %s\n", id);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_OK,
                                                  "Equipement non trouve: %s", id);
        gtk_window_set_title(GTK_WINDOW(dialog), "Erreur");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Demander confirmation
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_QUESTION,
                                               GTK_BUTTONS_YES_NO,
                                               "Voulez-vous vraiment supprimer l'equipement %s?", id);
    gtk_window_set_title(GTK_WINDOW(dialog), "Confirmation");
    
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    if (response == GTK_RESPONSE_YES) {
        // Supprimer l'equipement
        supprimer_equipement((char*)id);
        
        // Mettre a jour la TreeView
        if (treeview) {
            afficher_equipements(treeview);
        }
        
        // Nettoyer les champs
        if (input_id) gtk_entry_set_text(GTK_ENTRY(input_id), "");
        
        GtkWidget *input_lieu = lookup_widget(window, "talelinputlieu");
        if (input_lieu) gtk_entry_set_text(GTK_ENTRY(input_lieu), "");
        
        GtkWidget *optionmenu_categorie = lookup_widget(window, "talelmenucategorie");
        if (optionmenu_categorie) gtk_option_menu_set_history(GTK_OPTION_MENU(optionmenu_categorie), 0);
        
        GtkWidget *spin_dispo = lookup_widget(window, "talelspindispo");
        if (spin_dispo) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_dispo), 0);
        
        GtkWidget *spin_jour = lookup_widget(window, "talelspinjour");
        if (spin_jour) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_jour), 1);
        
        GtkWidget *spin_mois = lookup_widget(window, "talelspinmois");
        if (spin_mois) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mois), 1);
        
        GtkWidget *spin_annee = lookup_widget(window, "talelspinannee");
        if (spin_annee) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_annee), 2024);
        
        GtkWidget *radio_d = lookup_widget(window, "talelradioetatd");
        if (radio_d) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_d), TRUE);
        
        GtkWidget *radio_n = lookup_widget(window, "talelradioetatn");
        if (radio_n) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_n), FALSE);
        
        g_print("ADMIN: Equipement supprime: %s\n", id);
        
        // Afficher confirmation
        dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "Equipement %s supprime avec succes!", id);
        gtk_window_set_title(GTK_WINDOW(dialog), "Succes");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void
on_dec4_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_talelmenucategorie_changed          (GtkOptionMenu   *optionmenu,
                                        gpointer         user_data)
{
    g_print("ADMIN: Menu categorie change\n");
}

void
on_talelradioetatd_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        g_print("ADMIN: Etat change a: DISPONIBLE\n");
    }
}

void
on_talelradioetatn_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        g_print("ADMIN: Etat change a: NON DISPONIBLE\n");
    }
}

void
on_talelbuttonajout_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    g_print("\n=== ADMIN: Ajout equipement ===\n");
    
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    // Recuperer tous les widgets ADMINISTRATION
    GtkWidget *input_id = lookup_widget(window, "talelinputid");
    GtkWidget *input_lieu = lookup_widget(window, "talelinputlieu");
    GtkWidget *optionmenu_categorie = lookup_widget(window, "talelmenucategorie"); // CORRIGÉ: GtkOptionMenu
    GtkWidget *spin_dispo = lookup_widget(window, "talelspindispo");
    GtkWidget *spin_jour = lookup_widget(window, "talelspinjour");
    GtkWidget *spin_mois = lookup_widget(window, "talelspinmois");
    GtkWidget *spin_annee = lookup_widget(window, "talelspinannee");
    GtkWidget *radio_d = lookup_widget(window, "talelradioetatd");
    GtkWidget *radio_n = lookup_widget(window, "talelradioetatn");
    GtkWidget *treeview = lookup_widget(window, "taleltreeview");
    
    // Verifier les widgets essentiels
    if (!input_id || !input_lieu || !optionmenu_categorie) {
        g_print("ADMIN ERREUR: Widgets non trouves\n");
        return;
    }
    
    // Creer la structure Equipement
    Equipement e;
    
    // Recuperer les valeurs
    const gchar *id = gtk_entry_get_text(GTK_ENTRY(input_id));
    const gchar *lieu = gtk_entry_get_text(GTK_ENTRY(input_lieu));
    
    if (strlen(id) == 0) {
        g_print("ADMIN ERREUR: ID vide\n");
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_OK,
                                                  "L'ID est obligatoire!");
        gtk_window_set_title(GTK_WINDOW(dialog), "Erreur");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    if (strlen(lieu) == 0) {
        g_print("ADMIN ERREUR: Lieu vide\n");
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_OK,
                                                  "Le lieu est obligatoire!");
        gtk_window_set_title(GTK_WINDOW(dialog), "Erreur");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    strcpy(e.id, id);
    strcpy(e.lieu, lieu);
    
    // Recuperer la categorie (GtkOptionMenu)
    if (optionmenu_categorie) {
        gint active = gtk_option_menu_get_history(GTK_OPTION_MENU(optionmenu_categorie));
        const gchar *cats[] = {"MUSCULATION", "CARDIO TRAINING", "CROSS TRAINING", 
                              "CIRCUIT TRAINING", "YOGA", "PSTRETCHING", "MEDITATION",
                              "ZUMBA", "BOXE", "CYCLING", "BOOTCAMP", "SEANCE EN GROUPE",
                              "SEANCE DECOUVERTE", "PLANIFICATION D'OBJECTIFS", 
                              "COACHING NUTRITIONNEL"};
        
        if (active >= 0 && active < 15) {
            strcpy(e.categorie, cats[active]);
            g_print("ADMIN: Categorie selectionnee: %s\n", cats[active]);
        } else {
            strcpy(e.categorie, "MUSCULATION");
            g_print("ADMIN: Categorie par defaut: MUSCULATION\n");
        }
    } else {
        strcpy(e.categorie, "MUSCULATION");
    }
    
    // Recuperer les valeurs numeriques
    if (spin_dispo) {
        e.quantite_dispo = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_dispo));
    } else {
        e.quantite_dispo = 0;
    }
    
    if (spin_jour) {
        e.jour_maintenance = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour));
    } else {
        e.jour_maintenance = 1;
    }
    
    if (spin_mois) {
        e.mois_maintenance = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois));
    } else {
        e.mois_maintenance = 1;
    }
    
    if (spin_annee) {
        e.annee_maintenance = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee));
    } else {
        e.annee_maintenance = 2024;
    }
    
    // Determiner l'etat
    if (radio_d && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_d))) {
        e.etat = 1;
    } else if (radio_n && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_n))) {
        e.etat = 0;
    } else {
        e.etat = 1; // Par defaut disponible
    }
    
    // Verifier les valeurs
    if (e.jour_maintenance < 1 || e.jour_maintenance > 31) {
        g_print("ADMIN ERREUR: Jour de maintenance invalide: %d\n", e.jour_maintenance);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_OK,
                                                  "Jour de maintenance invalide (1-31)!");
        gtk_window_set_title(GTK_WINDOW(dialog), "Erreur");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    if (e.mois_maintenance < 1 || e.mois_maintenance > 12) {
        g_print("ADMIN ERREUR: Mois de maintenance invalide: %d\n", e.mois_maintenance);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_OK,
                                                  "Mois de maintenance invalide (1-12)!");
        gtk_window_set_title(GTK_WINDOW(dialog), "Erreur");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    if (e.annee_maintenance < 2000 || e.annee_maintenance > 2100) {
        g_print("ADMIN ERREUR: Annee de maintenance invalide: %d\n", e.annee_maintenance);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_OK,
                                                  "Annee de maintenance invalide (2000-2100)!");
        gtk_window_set_title(GTK_WINDOW(dialog), "Erreur");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Verifier si l'ID existe deja
    Equipement existing = rechercher_equipement((char*)id);
    if (strlen(existing.id) > 0) {
        g_print("ADMIN ERREUR: ID existe deja: %s\n", id);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_OK,
                                                  "L'ID %s existe deja!", id);
        gtk_window_set_title(GTK_WINDOW(dialog), "Erreur");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Ajouter l'equipement
    ajouter_equipement(e);
    
    // Mettre a jour la TreeView
    if (treeview) {
        afficher_equipements(treeview);
    }
    
    g_print("ADMIN: Equipement ajoute avec succes: %s\n", e.id);
    
    // Nettoyer les champs apres ajout
    gtk_entry_set_text(GTK_ENTRY(input_id), "");
    gtk_entry_set_text(GTK_ENTRY(input_lieu), "");
    
    if (spin_dispo) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_dispo), 0);
    if (spin_jour) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_jour), 1);
    if (spin_mois) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mois), 1);
    if (spin_annee) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_annee), 2024);
    
    if (optionmenu_categorie) gtk_option_menu_set_history(GTK_OPTION_MENU(optionmenu_categorie), 0);
    
    if (radio_d) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_d), TRUE);
    if (radio_n) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_n), FALSE);
    
    // Afficher confirmation
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                              GTK_DIALOG_DESTROY_WITH_PARENT,
                                              GTK_MESSAGE_INFO,
                                              GTK_BUTTONS_OK,
                                              "Equipement %s ajoute avec succes!", e.id);
    gtk_window_set_title(GTK_WINDOW(dialog), "Succes");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void
on_talelbuttonrech_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
    g_print("\n=== ADMIN: Recherche equipement ===\n");
    
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    // Recuperer le champ de recherche
    GtkWidget *input_rech = lookup_widget(window, "talelinputrech");
    if (!input_rech) {
        g_print("ADMIN ERREUR: talelinputrech non trouve\n");
        return;
    }
    
    const gchar *id_rech = gtk_entry_get_text(GTK_ENTRY(input_rech));
    if (strlen(id_rech) == 0) {
        g_print("ADMIN: ID de recherche vide\n");
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_WARNING,
                                                  GTK_BUTTONS_OK,
                                                  "Veuillez entrer un ID a rechercher!");
        gtk_window_set_title(GTK_WINDOW(dialog), "Attention");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Rechercher l'equipement
    Equipement e = rechercher_equipement((char*)id_rech);
    
    if (strlen(e.id) > 0) {
        // Remplir les champs avec les donnees trouvees
        GtkWidget *input_id = lookup_widget(window, "talelinputid");
        GtkWidget *input_lieu = lookup_widget(window, "talelinputlieu");
        GtkWidget *optionmenu_categorie = lookup_widget(window, "talelmenucategorie");
        GtkWidget *spin_dispo = lookup_widget(window, "talelspindispo");
        GtkWidget *spin_jour = lookup_widget(window, "talelspinjour");
        GtkWidget *spin_mois = lookup_widget(window, "talelspinmois");
        GtkWidget *spin_annee = lookup_widget(window, "talelspinannee");
        GtkWidget *radio_d = lookup_widget(window, "talelradioetatd");
        GtkWidget *radio_n = lookup_widget(window, "talelradioetatn");
        
        if (input_id) gtk_entry_set_text(GTK_ENTRY(input_id), e.id);
        if (input_lieu) gtk_entry_set_text(GTK_ENTRY(input_lieu), e.lieu);
        
        if (optionmenu_categorie) {
            int index = trouver_index_categorie(e.categorie);
            if (index >= 0) {
                gtk_option_menu_set_history(GTK_OPTION_MENU(optionmenu_categorie), index);
            } else {
                gtk_option_menu_set_history(GTK_OPTION_MENU(optionmenu_categorie), 0);
            }
        }
        
        if (spin_dispo) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_dispo), e.quantite_dispo);
        if (spin_jour) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_jour), e.jour_maintenance);
        if (spin_mois) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mois), e.mois_maintenance);
        if (spin_annee) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_annee), e.annee_maintenance);
        
        if (radio_d && radio_n) {
            if (e.etat == 1) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_d), TRUE);
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_n), FALSE);
            } else {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_d), FALSE);
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_n), TRUE);
            }
        }
        
        g_print("ADMIN: Equipement trouve et affiche: %s\n", e.id);
    } else {
        g_print("ADMIN: Equipement non trouve: %s\n", id_rech);
        
        // Afficher message d'erreur
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_OK,
                                                  "Equipement non trouve: %s", id_rech);
        gtk_window_set_title(GTK_WINDOW(dialog), "Non trouve");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void
on_ranaspincapacite_changed            (GtkEditable     *editable,
                                        gpointer         user_data)
{
}

void
on_ranatreeview_row_activated          (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
}

void
on_ranabuttonrech_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_ranabouttonmod_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_ranabouttonsup_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_ranabuttonajout_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_dec5_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_ranaradioproprieteei_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
}

void
on_ranaradioproprieteep_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
}

void
on_calendar2_day_selected              (GtkCalendar     *calendar,
                                        gpointer         user_data)
{
}

void
on_chihebtreeview_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
}

void
on_chihebbuttonrecherche_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_chihebcheckniveauavance_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
}

void
on_chihebbuttonajout_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_chihebbuttonmodifier_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_chihebbuttonsupprimer_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_chihebcheckniveaudebutant_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
}

void
on_chihebcheckniveauinter_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
}

void
on_dec6_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
}

/* ============ FONCTION CONNEXION ============ */

void
on_loginbuttonlogin_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
}

/* ============ FONCTIONS D'INITIALISATION ============ */

// Fonction pour initialiser la TreeView des equipements ADMINISTRATION
gboolean initialiser_treeview_delayed(gpointer user_data)
{
    GtkWidget *window = (GtkWidget *)user_data;
    GtkWidget *treeview = lookup_widget(window, "taleltreeview");
    
    if (treeview) {
        afficher_equipements(treeview);
        g_print("ADMIN: TreeView initialisee avec succes\n");
    } else {
        g_print("ADMIN: TreeView non trouvee\n");
    }
    
    return FALSE;
}

// Fonction pour initialiser la TreeView des equipements COACH
gboolean initialiser_treeview_coach_delayed(gpointer user_data)
{
    GtkWidget *window = (GtkWidget *)user_data;
    GtkWidget *treeview = lookup_widget(window, "taleltreeview1");
    
    if (treeview) {
        afficher_equipements(treeview);
        g_print("COACH: TreeView (taleltreeview1) initialisee avec succes\n");
    } else {
        g_print("COACH ERREUR: taleltreeview1 non trouvee\n");
    }
    
    return FALSE;
}

void
on_eyabuttonajout_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}

