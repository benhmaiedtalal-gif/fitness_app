#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>

// ============ FONCTIONS DE DESTRUCTION ============
void on_MEMBRE_destroy(GtkObject *object, gpointer user_data);
void on_COACH_destroy(GtkObject *object, gpointer user_data);
void on_ADMINISTRATION_destroy(GtkObject *object, gpointer user_data);
void on_CONNECTION_destroy(GtkObject *object, gpointer user_data);

// ============ CALLBACKS MENUS ============
void on_jour3_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_jour2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_item1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_horaire1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_jour1_activate(GtkMenuItem *menuitem, gpointer user_data);

// ============ CALLBACKS ENTREES ============
void on_dhiainputmdp_activate(GtkEntry *entry, gpointer user_data);
void on_dhiainputnom_activate(GtkEntry *entry, gpointer user_data);
void on_dhiainputid_activate(GtkEntry *entry, gpointer user_data);
void on_dhiainputrech_activate(GtkEntry *entry, gpointer user_data);

// ============ CALLBACKS MENUS CATEGORIES ============
void on_entrainement2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_musculation1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_cardio_training1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_cross_training1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_circuit_training1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_bien_etre1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_yoga1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_pstretching1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_meditation1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_cours_collectifs2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_zumba1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_boxe1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_cycling1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_bootcamp1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_seance_en_groupe1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_coaching___suivi2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_seance_decouverte1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_planification_d_objectifs1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_coaching_nutritionnel1_activate(GtkMenuItem *menuitem, gpointer user_data);

// ============ CALLBACKS MENUS CATEGORIES (AUTRES) ============
void on_musculation2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_cardio_training2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_circuit_training2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_yoga2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_pstretching2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_mediation1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_zumba2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_boxe2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_cycling2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_bootcamp4_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_sceace_en_groupe1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_sceance_decouverte1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_planification_d_objet1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_coaching_nutritionnel2_activate(GtkMenuItem *menuitem, gpointer user_data);

// ============ CALLBACKS ETATS EVENEMENTS ============
void on_avenir_1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_en_cours1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_termine1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_annule1_activate(GtkMenuItem *menuitem, gpointer user_data);

// ============ CALLBACKS ADMINISTRATION ============
void on_ranaspincapacite_changed(GtkEditable *editable, gpointer user_data);
void on_ranainputrech_activate(GtkEntry *entry, gpointer user_data);
void on_ranaradioproprieteep_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_ranaradioproprieteei_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_ranatreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_ranabuttonajout_clicked(GtkButton *button, gpointer user_data);
void on_ranabouttonsup_clicked(GtkButton *button, gpointer user_data);
void on_ranabouttonmod_clicked(GtkButton *button, gpointer user_data);
void on_ranabuttonrech_clicked(GtkButton *button, gpointer user_data);

// ============ CALLBACKS COACH ============
void on_ranatreeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_ranabuttonrech1_clicked(GtkButton *button, gpointer user_data);
void on_ranabuttoncentres_clicked(GtkButton *button, gpointer user_data);
void on_ranacheckpreferncesr_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_ranacheckpreferncesm_toggled(GtkToggleButton *togglebutton, gpointer user_data);

// ============ NOUVEAUX CALLBACKS MANQUANTS (AJOUTÉS POUR ÉVITER LES ERREURS) ============

// MEMBRE callbacks
void on_dhiatreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_dhiabuttonrech_clicked(GtkButton *button, gpointer user_data);
void on_dhiabuttonaffilations_clicked(GtkButton *button, gpointer user_data);
void on_dhiabuttonajout_clicked(GtkButton *button, gpointer user_data);
void on_dec7_clicked(GtkButton *button, gpointer user_data);
void on_dec8_clicked(GtkButton *button, gpointer user_data);
void on_dec9_clicked(GtkButton *button, gpointer user_data);

// CHIHEB callbacks
void on_chihebtreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_chihebtreeview_row_activated2(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_chihebcheckniveauxi_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebcheckniveauxa_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebcheckniveauxd_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebbuttonevenements_clicked(GtkButton *button, gpointer user_data);
void on_chihebbuttonrech_clicked(GtkButton *button, gpointer user_data);
void on_chihebradiotarifg_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebradiotarifp_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebbuttonrecherche_clicked(GtkButton *button, gpointer user_data);
void on_chihebcheckniveauavance_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebbuttonajout_clicked(GtkButton *button, gpointer user_data);
void on_chihebbuttonmodifier_clicked(GtkButton *button, gpointer user_data);
void on_chihebbuttonsupprimer_clicked(GtkButton *button, gpointer user_data);
void on_chihebcheckniveaudebutant_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebcheckniveauinter_toggled(GtkToggleButton *togglebutton, gpointer user_data);

// COACH callbacks
void on_ghbuttoninscription_clicked(GtkButton *button, gpointer user_data);
void on_dec10_clicked(GtkButton *button, gpointer user_data);
void on_talelspinnombre_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelspinjour1_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelspinmois1_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelspinannee1_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelbuttonequipement_clicked(GtkButton *button, gpointer user_data);
void on_talelbuttonrech1_clicked(GtkButton *button, gpointer user_data);
void on_dec11_clicked(GtkButton *button, gpointer user_data);
void on_dec12_clicked(GtkButton *button, gpointer user_data);

// ADMIN callbacks
void on_dec1_clicked(GtkButton *button, gpointer user_data);
void on_button1_clicked(GtkButton *button, gpointer user_data);
void on_button2_clicked(GtkButton *button, gpointer user_data);
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
void on_talelmenucategorie_changed(GtkComboBox *combobox, gpointer user_data);
void on_talelradioetatd_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_talelradioetatn_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_talelbuttonajout_clicked(GtkButton *button, gpointer user_data);
void on_dec5_clicked(GtkButton *button, gpointer user_data);
void on_calendar2_day_selected(GtkCalendar *calendar, gpointer user_data);
void on_dec6_clicked(GtkButton *button, gpointer user_data);

// CONNECTION callbacks
void on_loginbuttonlogin_clicked(GtkButton *button, gpointer user_data);

// Fonction pour rafraîchir l'interface coach
void rafraichir_interface_coach(void);

#endif

void
on_eyabuttonajout_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_talelbuttonrech_clicked             (GtkButton       *button,
                                        gpointer         user_data);
