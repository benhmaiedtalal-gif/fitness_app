#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "centre.h"
#include "coach.h"

// ============ FONCTIONS VIDE POUR LES CALLBACKS MANQUANTS ============

void on_jour3_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_jour2_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_item1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_horaire1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_jour1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_dhiainputmdp_activate(GtkEntry *entry, gpointer user_data) {}
void on_dhiainputnom_activate(GtkEntry *entry, gpointer user_data) {}
void on_dhiainputid_activate(GtkEntry *entry, gpointer user_data) {}
void on_dhiainputrech_activate(GtkEntry *entry, gpointer user_data) {}
void on_entrainement2_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_musculation1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_cardio_training1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_cross_training1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_circuit_training1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_bien_etre1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_yoga1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_pstretching1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_meditation1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_cours_collectifs2_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_zumba1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_boxe1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_cycling1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_bootcamp1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_seance_en_groupe1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_coaching___suivi2_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_seance_decouverte1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_planification_d_objectifs1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_coaching_nutritionnel1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_musculation2_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_cardio_training2_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_circuit_training2_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_yoga2_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_pstretching2_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_mediation1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_zumba2_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_boxe2_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_cycling2_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_bootcamp4_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_sceace_en_groupe1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_sceance_decouverte1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_planification_d_objet1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_coaching_nutritionnel2_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_avenir_1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_en_cours1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_termine1_activate(GtkMenuItem *menuitem, gpointer user_data) {}
void on_annule1_activate(GtkMenuItem *menuitem, gpointer user_data) {}

void on_ranaspincapacite_changed(GtkEditable *editable, gpointer user_data) {
    // Validation simple de la capacité
    GtkWidget *spin = GTK_WIDGET(editable);
    int valeur = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin));
    if (valeur < 1) {
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin), 1);
    }
}

// Variables globales pour l'interface ADMIN
int propriete_selectionnee = 0; // 0=INDEPENDANT, 1=PARTENARIAT

// Variables globales pour l'interface COACH
int contrat_selectionne = 0; // 0=PRINCIPAL, 1=SECONDAIRE
int alerte_sms = 0;
int masquer_profil = 0;

// ============ FONCTIONS DE DESTRUCTION ============

void on_MEMBRE_destroy(GtkObject *object, gpointer user_data) {
    gtk_main_quit();
}

void on_COACH_destroy(GtkObject *object, gpointer user_data) {
    gtk_main_quit();
}

void on_ADMINISTRATION_destroy(GtkObject *object, gpointer user_data) {
    gtk_main_quit();
}

void on_CONNECTION_destroy(GtkObject *object, gpointer user_data) {
    gtk_main_quit();
}

// ============ CALLBACKS ADMINISTRATION (CENTRES) ============

void on_ranabuttonajout_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *input_id, *input_nom, *input_adresse, *spin_capacite;
    GtkWidget *combo_heure, *radio_independant, *radio_partenariat;
    GtkWidget *treeview;
    Centre c;
    
    // Récupérer les widgets
    input_id = lookup_widget(GTK_WIDGET(button), "ranainputid");
    input_nom = lookup_widget(GTK_WIDGET(button), "ranainputnomc");
    input_adresse = lookup_widget(GTK_WIDGET(button), "ranainputadresse");
    spin_capacite = lookup_widget(GTK_WIDGET(button), "ranaspincapacite");
    combo_heure = lookup_widget(GTK_WIDGET(button), "ranavomboheure");
    radio_independant = lookup_widget(GTK_WIDGET(button), "ranaradioproprieteei");
    radio_partenariat = lookup_widget(GTK_WIDGET(button), "ranaradioproprieteep");
    
    // Récupérer les valeurs
    strcpy(c.id, gtk_entry_get_text(GTK_ENTRY(input_id)));
    strcpy(c.nom, gtk_entry_get_text(GTK_ENTRY(input_nom)));
    strcpy(c.adresse, gtk_entry_get_text(GTK_ENTRY(input_adresse)));
    c.capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_capacite));
    
    // Heure d'ouverture
    gchar *heure = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_heure));
    if (heure) {
        strcpy(c.heure_ouverture, heure);
        g_free(heure);
    } else {
        strcpy(c.heure_ouverture, "08:00");
    }
    
    // Propriété
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_independant))) {
        strcpy(c.propriete, "INDEPENDANT");
        printf("Propriété sélectionnée : INDEPENDANT\n");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_partenariat))) {
        strcpy(c.propriete, "PARTENARIAT");
        printf("Propriété sélectionnée : PARTENARIAT\n");
    } else {
        strcpy(c.propriete, "INDEPENDANT");
        printf("Aucune propriété sélectionnée, défaut: INDEPENDANT\n");
    }
    
    // Vérifier si l'ID existe déjà
    if (verifier_centre_existe(c.id)) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Cet ID existe déjà !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Ajouter le centre
    ajouter_centre(c);
    
    // Afficher message de succès
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Centre ajouté avec succès !");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    // Rafraîchir l'affichage ADMIN
    treeview = lookup_widget(GTK_WIDGET(button), "ranatreeview");
    afficher_centres(treeview);
    
    // Rafraîchir aussi l'interface COACH
    rafraichir_interface_coach();
}

void on_ranabuttonrech_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "ranatreeview");
    afficher_centres(treeview);
}

void on_ranabuttonrech1_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "ranatreeview1");
    afficher_centres_coach(treeview);
    printf("Recherche COACH effectuée\n");
}

void on_ranabouttonsup_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *input_sup = lookup_widget(GTK_WIDGET(button), "ranainputsup");
    char id[100];
    strcpy(id, gtk_entry_get_text(GTK_ENTRY(input_sup)));
    
    if (strlen(id) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez entrer un ID à supprimer !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    if (!verifier_centre_existe(id)) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Centre non trouvé !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Demande de confirmation
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Êtes-vous sûr de vouloir supprimer ce centre ?");
    
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    if (response == GTK_RESPONSE_YES) {
        supprimer_centre(id);
        
        GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "ranatreeview");
        afficher_centres(treeview);
        
        // Rafraîchir aussi l'interface COACH
        rafraichir_interface_coach();
        
        GtkWidget *dialog2 = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Centre supprimé avec succès !");
        gtk_dialog_run(GTK_DIALOG(dialog2));
        gtk_widget_destroy(dialog2);
    }
}

void on_ranabouttonmod_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *input_mod = lookup_widget(GTK_WIDGET(button), "ranainputmod");
    GtkWidget *input_id = lookup_widget(GTK_WIDGET(button), "ranainputid");
    GtkWidget *input_nom = lookup_widget(GTK_WIDGET(button), "ranainputnomc");
    GtkWidget *input_adresse = lookup_widget(GTK_WIDGET(button), "ranainputadresse");
    GtkWidget *spin_capacite = lookup_widget(GTK_WIDGET(button), "ranaspincapacite");
    GtkWidget *combo_heure = lookup_widget(GTK_WIDGET(button), "ranavomboheure");
    GtkWidget *radio_independant = lookup_widget(GTK_WIDGET(button), "ranaradioproprieteei");
    GtkWidget *radio_partenariat = lookup_widget(GTK_WIDGET(button), "ranaradioproprieteep");
    
    char id_mod[100];
    strcpy(id_mod, gtk_entry_get_text(GTK_ENTRY(input_mod)));
    
    if (strlen(id_mod) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez entrer un ID à modifier !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    if (!verifier_centre_existe(id_mod)) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Centre non trouvé !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Récupérer les nouvelles valeurs
    Centre c;
    strcpy(c.id, gtk_entry_get_text(GTK_ENTRY(input_id)));
    strcpy(c.nom, gtk_entry_get_text(GTK_ENTRY(input_nom)));
    strcpy(c.adresse, gtk_entry_get_text(GTK_ENTRY(input_adresse)));
    c.capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_capacite));
    
    gchar *heure = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_heure));
    if (heure) {
        strcpy(c.heure_ouverture, heure);
        g_free(heure);
    } else {
        strcpy(c.heure_ouverture, "08:00");
    }
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_independant))) {
        strcpy(c.propriete, "INDEPENDANT");
    } else {
        strcpy(c.propriete, "PARTENARIAT");
    }
    
    // Modifier le centre
    modifier_centre(c);
    
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "ranatreeview");
    afficher_centres(treeview);
    
    // Rafraîchir aussi l'interface COACH
    rafraichir_interface_coach();
    
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Centre modifié avec succès !");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void on_ranatreeview_row_activated(GtkTreeView *treeview, 
                                   GtkTreePath *path, 
                                   GtkTreeViewColumn *column, 
                                   gpointer user_data) {
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *id, *nom, *adresse;
    gint capacite;
    
    model = gtk_tree_view_get_model(treeview);
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(model, &iter,
            0, &id,
            1, &nom,
            2, &adresse,
            3, &capacite,
            -1);
        
        // Remplir les champs avec les données sélectionnées
        GtkWidget *window = gtk_widget_get_parent(GTK_WIDGET(treeview));
        while (!GTK_IS_WINDOW(window)) {
            window = gtk_widget_get_parent(window);
        }
        
        GtkWidget *input_id = lookup_widget(GTK_WIDGET(window), "ranainputid");
        GtkWidget *input_nom = lookup_widget(GTK_WIDGET(window), "ranainputnomc");
        GtkWidget *input_adresse = lookup_widget(GTK_WIDGET(window), "ranainputadresse");
        GtkWidget *spin_capacite = lookup_widget(GTK_WIDGET(window), "ranaspincapacite");
        
        gtk_entry_set_text(GTK_ENTRY(input_id), id);
        gtk_entry_set_text(GTK_ENTRY(input_nom), nom);
        gtk_entry_set_text(GTK_ENTRY(input_adresse), adresse);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_capacite), (gdouble)capacite);
        
        g_free(id);
        g_free(nom);
        g_free(adresse);
    }
}

void on_ranaradioproprieteei_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        propriete_selectionnee = 0; // INDEPENDANT
        printf("Propriété sélectionnée : INDEPENDANT\n");
    }
}

void on_ranaradioproprieteep_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        propriete_selectionnee = 1; // PARTENARIAT
        printf("Propriété sélectionnée : PARTENARIAT\n");
    }
}

void on_ranabuttoncentres_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "ranatreeview1");
    GtkWidget *spin_duree = lookup_widget(GTK_WIDGET(button), "ranaspinduree1");
    GtkWidget *radio_principal = lookup_widget(GTK_WIDGET(button), "ranaradiocentrecp");
    GtkWidget *radio_secondaire = lookup_widget(GTK_WIDGET(button), "ranaradiocentrecs");
    GtkWidget *check_alerte = lookup_widget(GTK_WIDGET(button), "ranacheckpreferncesr");
    GtkWidget *check_masquer = lookup_widget(GTK_WIDGET(button), "ranacheckpreferncesm");
    
    // Récupérer la sélection du treeview
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez sélectionner un centre !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Récupérer les données du centre sélectionné
    gchar *centre_id, *centre_nom;
    gtk_tree_model_get(model, &iter,
        0, &centre_id,
        1, &centre_nom,
        -1);
    
    // Récupérer les préférences
    DemandeCoach demande;
    strcpy(demande.centre_id, centre_id);
    strcpy(demande.centre_nom, centre_nom);
    demande.duree_candidature = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_duree));
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_principal))) {
        strcpy(demande.type_contrat, "PRINCIPAL");
    } else {
        strcpy(demande.type_contrat, "SECONDAIRE");
    }
    
    demande.alerte_sms = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_alerte)) ? 1 : 0;
    demande.masquer_profil = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_masquer)) ? 1 : 0;
    
    // Enregistrer la demande
    ajouter_demande_coach(demande);
    
    // Message de confirmation
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Demande envoyée avec succès pour le centre %s !", centre_nom);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    g_free(centre_id);
    g_free(centre_nom);
}

void on_ranatreeview1_row_activated(GtkTreeView *treeview, 
                                    GtkTreePath *path, 
                                    GtkTreeViewColumn *column, 
                                    gpointer user_data) {
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *centre_nom;
    
    model = gtk_tree_view_get_model(treeview);
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(model, &iter, 1, &centre_nom, -1);
        
        // Afficher un message
        printf("Centre sélectionné : %s\n", centre_nom);
        
        g_free(centre_nom);
    }
}

void on_ranacheckpreferncesr_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    alerte_sms = gtk_toggle_button_get_active(togglebutton) ? 1 : 0;
}

void on_ranacheckpreferncesm_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    masquer_profil = gtk_toggle_button_get_active(togglebutton) ? 1 : 0;
}

void on_ranainputrech_activate(GtkEntry *entry, gpointer user_data) {
    // Fonction pour l'activation de l'entrée de recherche
    printf("Entrée de recherche activée\n");
}

// ============ NOUVEAUX CALLBACKS MANQUANTS (FONCTIONS VIDES) ============

// MEMBRE callbacks
void on_dhiatreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {
    printf("dhiatreeview_row_activated\n");
}
void on_dhiabuttonrech_clicked(GtkButton *button, gpointer user_data) {
    printf("dhiabuttonrech_clicked\n");
}
void on_dhiabuttonaffilations_clicked(GtkButton *button, gpointer user_data) {
    printf("dhiabuttonaffilations_clicked\n");
}
void on_dhiabuttonajout_clicked(GtkButton *button, gpointer user_data) {
    printf("dhiabuttonajout_clicked\n");
}
void on_dec7_clicked(GtkButton *button, gpointer user_data) {
    printf("dec7_clicked\n");
}
void on_dec8_clicked(GtkButton *button, gpointer user_data) {
    printf("dec8_clicked\n");
}
void on_dec9_clicked(GtkButton *button, gpointer user_data) {
    printf("dec9_clicked\n");
}

// CHIHEB callbacks
void on_chihebtreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {
    printf("chihebtreeview_row_activated\n");
}
void on_chihebtreeview_row_activated2(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {
    printf("chihebtreeview_row_activated2\n");
}
void on_chihebcheckniveauxi_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    printf("chihebcheckniveauxi_toggled\n");
}
void on_chihebcheckniveauxa_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    printf("chihebcheckniveauxa_toggled\n");
}
void on_chihebcheckniveauxd_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    printf("chihebcheckniveauxd_toggled\n");
}
void on_chihebbuttonevenements_clicked(GtkButton *button, gpointer user_data) {
    printf("chihebbuttonevenements_clicked\n");
}
void on_chihebbuttonrech_clicked(GtkButton *button, gpointer user_data) {
    printf("chihebbuttonrech_clicked\n");
}
void on_chihebradiotarifg_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    printf("chihebradiotarifg_toggled\n");
}
void on_chihebradiotarifp_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    printf("chihebradiotarifp_toggled\n");
}
void on_chihebbuttonrecherche_clicked(GtkButton *button, gpointer user_data) {
    printf("chihebbuttonrecherche_clicked\n");
}
void on_chihebcheckniveauavance_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    printf("chihebcheckniveauavance_toggled\n");
}
void on_chihebbuttonajout_clicked(GtkButton *button, gpointer user_data) {
    printf("chihebbuttonajout_clicked\n");
}
void on_chihebbuttonmodifier_clicked(GtkButton *button, gpointer user_data) {
    printf("chihebbuttonmodifier_clicked\n");
}
void on_chihebbuttonsupprimer_clicked(GtkButton *button, gpointer user_data) {
    printf("chihebbuttonsupprimer_clicked\n");
}
void on_chihebcheckniveaudebutant_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    printf("chihebcheckniveaudebutant_toggled\n");
}
void on_chihebcheckniveauinter_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    printf("chihebcheckniveauinter_toggled\n");
}

// COACH callbacks
void on_ghbuttoninscription_clicked(GtkButton *button, gpointer user_data) {
    printf("ghbuttoninscription_clicked\n");
}
void on_dec10_clicked(GtkButton *button, gpointer user_data) {
    printf("dec10_clicked\n");
}
void on_talelspinnombre_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {
    printf("talelspinnombre_value_changed\n");
}
void on_talelspinjour1_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {
    printf("talelspinjour1_value_changed\n");
}
void on_talelspinmois1_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {
    printf("talelspinmois1_value_changed\n");
}
void on_talelspinannee1_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {
    printf("talelspinannee1_value_changed\n");
}
void on_talelbuttonequipement_clicked(GtkButton *button, gpointer user_data) {
    printf("talelbuttonequipement_clicked\n");
}
void on_talelbuttonrech1_clicked(GtkButton *button, gpointer user_data) {
    printf("talelbuttonrech1_clicked\n");
}
void on_dec11_clicked(GtkButton *button, gpointer user_data) {
    printf("dec11_clicked\n");
}
void on_dec12_clicked(GtkButton *button, gpointer user_data) {
    printf("dec12_clicked\n");
}

// ADMIN callbacks
void on_dec1_clicked(GtkButton *button, gpointer user_data) {
    printf("dec1_clicked\n");
}
void on_button1_clicked(GtkButton *button, gpointer user_data) {
    printf("button1_clicked\n");
}
void on_button2_clicked(GtkButton *button, gpointer user_data) {
    printf("button2_clicked\n");
}
void on_ghbouttonsupprimer_clicked(GtkButton *button, gpointer user_data) {
    printf("ghbouttonsupprimer_clicked\n");
}
void on_dec2_clicked(GtkButton *button, gpointer user_data) {
    printf("dec2_clicked\n");
}
void on_8h___1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    printf("8h___1_activate\n");
}
void on_10h___12h1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    printf("10h___12h1_activate\n");
}
void on_14h___16h1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    printf("14h___16h1_activate\n");
}
void on_16___18h1_activate(GtkMenuItem *menuitem, gpointer user_data) {
    printf("16___18h1_activate\n");
}
void on_eyabuttonsupprimer_clicked(GtkButton *button, gpointer user_data) {
    printf("eyabuttonsupprimer_clicked\n");
}
void on_eyabuttonmodifier_clicked(GtkButton *button, gpointer user_data) {
    printf("eyabuttonmodifier_clicked\n");
}
void on_dec3_clicked(GtkButton *button, gpointer user_data) {
    printf("dec3_clicked\n");
}
void on_talelspindispo_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {
    printf("talelspindispo_value_changed\n");
}
void on_talelspinjour_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {
    printf("talelspinjour_value_changed\n");
}
void on_talelspinmois_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {
    printf("talelspinmois_value_changed\n");
}
void on_talelspinannee_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {
    printf("talelspinannee_value_changed\n");
}
void on_talelbuttonmod_clicked(GtkButton *button, gpointer user_data) {
    printf("talelbuttonmod_clicked\n");
}
void on_talelbuttonsupp_clicked(GtkButton *button, gpointer user_data) {
    printf("talelbuttonsupp_clicked\n");
}
void on_dec4_clicked(GtkButton *button, gpointer user_data) {
    printf("dec4_clicked\n");
}
void on_talelmenucategorie_changed(GtkComboBox *combobox, gpointer user_data) {
    printf("talelmenucategorie_changed\n");
}
void on_talelradioetatd_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    printf("talelradioetatd_toggled\n");
}
void on_talelradioetatn_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    printf("talelradioetatn_toggled\n");
}
void on_talelbuttonajout_clicked(GtkButton *button, gpointer user_data) {
    printf("talelbuttonajout_clicked\n");
}
void on_dec5_clicked(GtkButton *button, gpointer user_data) {
    printf("dec5_clicked\n");
}
void on_calendar2_day_selected(GtkCalendar *calendar, gpointer user_data) {
    printf("calendar2_day_selected\n");
}
void on_dec6_clicked(GtkButton *button, gpointer user_data) {
    printf("dec6_clicked\n");
}

// CONNECTION callbacks
void on_loginbuttonlogin_clicked(GtkButton *button, gpointer user_data) {
    printf("loginbuttonlogin_clicked\n");
}

// ============ FONCTION POUR RAFRAÎCHIR COACH ============

void rafraichir_interface_coach() {
    // Trouver la fenêtre COACH
    GtkWidget *coach_window = NULL;
    GList *windows = gtk_window_list_toplevels();
    GList *iter;
    
    for (iter = windows; iter != NULL; iter = iter->next) {
        GtkWidget *window = GTK_WIDGET(iter->data);
        gchar *name = (gchar*)g_object_get_data(G_OBJECT(window), "glade-widget-name");
        if (name && strcmp(name, "COACH") == 0) {
            coach_window = window;
            break;
        }
    }
    g_list_free(windows);
    
    if (coach_window) {
        // Trouver le treeview COACH et le rafraîchir
        GtkWidget *treeview_coach = lookup_widget(coach_window, "ranatreeview1");
        if (treeview_coach) {
            afficher_centres_coach(treeview_coach);
            printf("Interface COACH rafraîchie après modification ADMIN\n");
        }
    }
}

void
on_eyabuttonajout_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_talelbuttonrech_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}

