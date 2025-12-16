#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>
#include "membre.h"

/* ==============================================
   VARIABLES GLOBALES
   ============================================== */
extern int sexe_selectionne;
extern gboolean treeview_initialise;

/* ==============================================
   FONCTIONS UTILITAIRES
   ============================================== */
void initialiser_treeview(GtkWidget *widget);
void afficher_erreur(GtkWidget *parent, const char *message);
void afficher_info(GtkWidget *parent, const char *message);

/* ==============================================
   SIGNALS DE LA FENÊTRE ADMINISTRATION
   ============================================== */
void on_window_admin_show(GtkWidget *widget, gpointer user_data);

/* ==============================================
   SIGNALS POUR LES RADIOBUTTONS
   ============================================== */
void on_dhiaradiosexem_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_dhiaradiosexef_toggled(GtkToggleButton *togglebutton, gpointer user_data);

/* ==============================================
   SIGNALS POUR LES BOUTONS PRINCIPAUX (ADMIN)
   ============================================== */
void on_dhiabuttonajout_clicked(GtkWidget *widget, gpointer user_data);    /* AJOUTER */
void on_button1_clicked(GtkWidget *widget, gpointer user_data);           /* MODIFIER */
void on_button2_clicked(GtkWidget *widget, gpointer user_data);           /* SUPPRIMER */
void on_dhiabuttonrech_clicked(GtkWidget *widget, gpointer user_data);    /* RECHERCHER (admin) */

/* ==============================================
   SIGNALS POUR LES ÉVÉNEMENTS TREEVIEW (ADMIN)
   ============================================== */
void on_dhiatreeview_row_activated(GtkTreeView *treeview, 
                                   GtkTreePath *path, 
                                   GtkTreeViewColumn *column, 
                                   gpointer user_data);

/* ==============================================
   FONCTIONS POUR L'INTERFACE COACHS (NOUVELLE INTERFACE)
   ============================================== */
void charger_coaches(GtkWidget *treeview, const char *nom_filtre);
void init_treeview_columns(GtkWidget *treeview);
void on_window_membre_show(GtkWidget *widget, gpointer user_data);
int get_sexe_selection(GtkWidget *window);

/* SIGNALS POUR L'INTERFACE COACHS */
void on_dhiabuttonrech1_clicked(GtkWidget *widget, gpointer user_data);    /* RECHERCHER (coach) */
void on_dhiabuttonaffiliations_clicked(GtkWidget *widget, gpointer user_data); /* AFFILIATIONS */

/* ==============================================
   SIGNALS POUR LES BOUTONS (AUTRES INTERFACES)
   ============================================== */
void on_eyabuttonajout_clicked(GtkButton *button, gpointer user_data);
void on_talelbuttonrech_clicked(GtkButton *button, gpointer user_data);

/* ==============================================
   FONCTIONS POUR LES MENUS - DÉCLARATIONS
   ============================================== */

/* Menu MEMBRE */
void on_jour2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_item1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_jour3_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_horaire1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_jour1_activate(GtkMenuItem *menuitem, gpointer user_data);

/* Menu ADMINISTRATION - ENTRAINEMENT */
void on_entrainement2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_musculation1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_musculation2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_cardio_training1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_cardio_training2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_cross_training1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_circuit_training1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_circuit_training2_activate(GtkMenuItem *menuitem, gpointer user_data);

/* Menu ADMINISTRATION - BIEN-ÊTRE */
void on_bien_etre1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_yoga1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_yoga2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_pstretching1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_pstretching2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_meditation1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_mediation1_activate(GtkMenuItem *menuitem, gpointer user_data);

/* Menu ADMINISTRATION - COURS COLLECTIFS */
void on_cours_collectifs2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_zumba1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_zumba2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_boxe1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_boxe2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_cycling1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_cycling2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_bootcamp1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_bootcamp4_activate(GtkMenuItem *menuitem, gpointer user_data);

/* Menu ADMINISTRATION - SÉANCES EN GROUPE */
void on_seance_en_groupe1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_sceace_en_groupe1_activate(GtkMenuItem *menuitem, gpointer user_data);

/* Menu ADMINISTRATION - COACHING */
void on_coaching___suivi2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_seance_decouverte1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_sceance_decouverte1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_planification_d_objectifs1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_planification_d_objet1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_coaching_nutritionnel1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_coaching_nutritionnel2_activate(GtkMenuItem *menuitem, gpointer user_data);

/* Menu ADMINISTRATION - STATUT */
void on_avenir_1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_en_cours1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_termine1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_annule1_activate(GtkMenuItem *menuitem, gpointer user_data);

/* ==============================================
   IMPLÉMENTATIONS VIDES (pour éviter erreurs de compilation)
   ============================================== */
void on_dec7_clicked(GtkButton *button, gpointer user_data);
void on_dec8_clicked(GtkButton *button, gpointer user_data);
void on_chihebtreeview_row_activated2(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_chihebcheckniveauxi_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebcheckniveauxa_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebbuttonevenements_clicked(GtkButton *button, gpointer user_data);
void on_chihebcheckniveauxd_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebbuttonrech_clicked(GtkButton *button, gpointer user_data);
void on_chihebradiotarifg_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebradiotarifp_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_dec9_clicked(GtkButton *button, gpointer user_data);
void on_ghbuttoninscription_clicked(GtkButton *button, gpointer user_data);
void on_dec10_clicked(GtkButton *button, gpointer user_data);
void on_talelspinnombre_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelspinjour1_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelspinmois1_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelspinannee1_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelbuttonequipement_clicked(GtkButton *button, gpointer user_data);
void on_talelbuttonrech1_clicked(GtkButton *button, gpointer user_data);
void on_dec11_clicked(GtkButton *button, gpointer user_data);
void on_ranatreeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_ranabuttonrech1_clicked(GtkButton *button, gpointer user_data);
void on_ranabuttoncentres_clicked(GtkButton *button, gpointer user_data);
void on_dec12_clicked(GtkButton *button, gpointer user_data);
void on_dec1_clicked(GtkButton *button, gpointer user_data);
void on_ghbouttonsupprimer_clicked(GtkButton *button, gpointer user_data);
void on_dec2_clicked(GtkButton *button, gpointer user_data);
void on_8h___1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_10h___12h1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_14h___16h1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_16___18h1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_eyabuttonsupprimer_clicked(GtkButton *button, gpointer user_data);
void on_eyabuttonmodifier_clicked(GtkButton *button, gpointer user_data);
void on_dec3_clicked(GtkButton *button, gpointer user_data);
void on_talelspindispo_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelspinjour_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelspinmois_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelspinannee_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelbuttonmod_clicked(GtkButton *button, gpointer user_data);
void on_talelbuttonsupp_clicked(GtkButton *button, gpointer user_data);
void on_dec4_clicked(GtkButton *button, gpointer user_data);
void on_talelmenucategorie_changed(GtkOptionMenu *optionmenu, gpointer user_data);
void on_talelradioetatd_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_talelradioetatn_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_talelbuttonajout_clicked(GtkButton *button, gpointer user_data);
void on_ranaspincapacite_changed(GtkEditable *editable, gpointer user_data);
void on_ranatreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_ranabuttonrech_clicked(GtkButton *button, gpointer user_data);
void on_ranabouttonmod_clicked(GtkButton *button, gpointer user_data);
void on_ranabouttonsup_clicked(GtkButton *button, gpointer user_data);
void on_ranabuttonajout_clicked(GtkButton *button, gpointer user_data);
void on_dec5_clicked(GtkButton *button, gpointer user_data);
void on_ranaradioproprieteei_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_ranaradioproprieteep_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_calendar2_day_selected(GtkCalendar *calendar, gpointer user_data);
void on_chihebtreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_chihebbuttonrecherche_clicked(GtkButton *button, gpointer user_data);
void on_chihebcheckniveauavance_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebbuttonajout_clicked(GtkButton *button, gpointer user_data);
void on_chihebbuttonmodifier_clicked(GtkButton *button, gpointer user_data);
void on_chihebbuttonsupprimer_clicked(GtkButton *button, gpointer user_data);
void on_chihebcheckniveaudebutant_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebcheckniveauinter_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_dec6_clicked(GtkButton *button, gpointer user_data);
void on_loginbuttonlogin_clicked(GtkButton *button, gpointer user_data);
void on_dhiabuttonaffilations_clicked(GtkWidget *widget, gpointer user_data);  /* Note: 1 'f' */
void on_eyabuttonajout_clicked(GtkButton *button, gpointer user_data) ;

void on_talelbuttonrech_clicked(GtkButton *button, gpointer user_data) ;
void debug_widgets(GtkWidget *parent);
#endif /* CALLBACKS_H */
