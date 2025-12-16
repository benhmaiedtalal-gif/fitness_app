#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "membre.h"
#include "support.h"

/* Variables globales */
int sexe_selectionne = 1;

/* Fonctions de callback SIMPLIFIÉES */

void on_window_admin_show(GtkWidget *widget, gpointer user_data) {
    g_print("[DEBUG] Fenêtre ouverte\n");
    
    /* Initialiser radiobutton masculin */
    GtkWidget *radio_masculin = lookup_widget(widget, "dhiaradiosexem");
    if (radio_masculin) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_masculin), TRUE);
        sexe_selectionne = 1;
    }
    
    /* Initialiser TreeView */
    GtkWidget *treeview = lookup_widget(widget, "dhiatreeview");
    if (treeview) {
        afficher_membres(GTK_TREE_VIEW(treeview), "membres.txt");
    }
}

void on_dhiaradiosexem_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        sexe_selectionne = 1;
    }
}

void on_dhiaradiosexef_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        sexe_selectionne = 2;
    }
}

void on_button1_clicked(GtkWidget *widget, gpointer user_data) {
    /* SIMPLE : juste un message pour tester */
    g_print("[DEBUG] Bouton AJOUTER cliqué - Fonctionnel !\n");
    
    /* Ici, vous ajouterez le vrai code d'ajout */
}

void on_button2_clicked(GtkWidget *widget, gpointer user_data) {
    g_print("[DEBUG] Bouton SUPPRIMER cliqué\n");
    /* Code de suppression */
}

void on_button_modifier_clicked(GtkWidget *widget, gpointer user_data) {
    g_print("[DEBUG] Bouton MODIFIER cliqué\n");
    /* Code de modification */
}

void on_dhiabuttonrech_clicked(GtkWidget *widget, gpointer user_data) {
    g_print("[DEBUG] Bouton RECHERCHER cliqué\n");
    /* Code de recherche */
}

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

}


void
on_talelbuttonrech1_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

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


void
on_dhiabuttonajout_clicked             (GtkButton       *button,
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

}


void
on_talelbuttonsupp_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

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

}


void
on_talelradioetatd_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_talelradioetatn_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_talelbuttonajout_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

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


void
on_loginbuttonlogin_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

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

