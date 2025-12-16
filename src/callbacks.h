#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>
#include "cours.h"

/* Admin page globals */
extern Cours cours_list[100];
extern int cours_count;
extern Cours e;
extern int selected_cours_id;

/* Member page globals */
extern Cours filtered_cours_list[100];
extern int filtered_count;
extern int selected_member_cours_id;

/* Main functions */
void init_database(void);
void populate_cours_treeview(GtkWidget *treeview);
void clear_input_fields(GtkWidget *window);
void save_cours_to_file(void);
void load_cours_to_fields(Cours c, GtkWidget *window);
gchar* get_option_menu_text(GtkWidget *option_menu);
void set_option_menu_by_text(GtkWidget *option_menu, const gchar *text);
void update_button_states(GtkWidget *window, gboolean has_selection);
void fix_cours_entry_visibility(GtkWidget *window);

/* Course management functions */
Cours* find_cours_by_id(int id);
void remove_cours_by_id(int id);

/* Idle callback */
gboolean populate_cours_treeview_idle(gpointer data);

/* TYPE menu functions */
void init_type_menu(GtkWidget *window);
void on_type_menu_item_selected(GtkMenuItem *menuitem, gpointer user_data);
void init_categorie_menu(GtkWidget *window);
void on_categorie_menu_item_selected(GtkMenuItem *menuitem, gpointer user_data);

/* ADMIN PAGE BUTTON CALLBACKS */
void on_eyabuttonajout_clicked(GtkButton *button, gpointer user_data);
void on_eyabuttonmodifier_clicked(GtkButton *button, gpointer user_data);
void on_eyabuttonsupprimer_clicked(GtkButton *button, gpointer user_data);
void on_eyatreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path,
                                  GtkTreeViewColumn *column, gpointer user_data);
void on_eyaactualiser_clicked(GtkButton *button, gpointer user_data);
void on_eyabuttonrech_clicked(GtkButton *button, gpointer user_data);

/* MEMBER PAGE FUNCTIONS */
void init_member_window(GtkWidget *window);
void filter_courses_by_criteria(const gchar *jour, const gchar *horaire, const gchar *type);
void filter_courses_by_criteria_new(const gchar *date_str, const gchar *type);
void populate_member_treeview(GtkWidget *treeview);
void register_member_for_course(int member_id, int course_id);

/* Member page callbacks */
void on_member_recherche_clicked(GtkButton *button, gpointer user_data);
void on_member_treeview_row_activated(GtkTreeView *treeview, GtkTreePath *path,
                                      GtkTreeViewColumn *column, gpointer user_data);
void on_eyabuttoncours_clicked(GtkButton *button, gpointer user_data);
void on_member_clear_filters_clicked(GtkButton *button, gpointer user_data);
void unselect_all_type_radios(GtkWidget *window);
void on_member_treeview_selection_changed(GtkTreeSelection *selection, gpointer user_data);

/* Member page spin button callbacks */
void on_eyaspinjour_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_eyaspinmois_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_eyaspinanee_value_changed(GtkSpinButton *spinbutton, gpointer user_data);

/* Member page filter reset */
void reset_member_filters(GtkWidget *window);

/* Inscription functions */
int save_inscription_to_file(Inscription ins);
void load_inscriptions_from_file(Inscription inscriptions[], int *count);
int is_member_registered(int member_id, int course_id);

/* MENU CALLBACKS */
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

void on_feminin1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_masculin1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_mixte1_activate(GtkMenuItem *menuitem, gpointer user_data);

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

void on_avenir_1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_en_cours1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_termine1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_annule1_activate(GtkMenuItem *menuitem, gpointer user_data);

/* Day/Time menu callbacks */
void on_jour3_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_jour2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_jour1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_item1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_horaire1_activate(GtkMenuItem *menuitem, gpointer user_data);

/* RADIO BUTTON CALLBACKS */
void on_eyaradiostatutd_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_eyaradiostatuta_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_eyaradiotypem_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_eyaradiotypef_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_eyaradiotypeh_toggled(GtkToggleButton *togglebutton, gpointer user_data);

/* MISSING CALLBACKS */
void on_dhiatreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path,
                                  GtkTreeViewColumn *column, gpointer user_data);
void on_dhiabuttonrech_clicked(GtkButton *button, gpointer user_data);
void on_dhiabuttonaffilations_clicked(GtkButton *button, gpointer user_data);
void on_dec7_clicked(GtkButton *button, gpointer user_data);
void on_dec8_clicked(GtkButton *button, gpointer user_data);
void on_chihebtreeview_row_activated2(GtkTreeView *treeview, GtkTreePath *path,
                                     GtkTreeViewColumn *column, gpointer user_data);
void on_chihebcheckniveauxi_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebcheckniveauxa_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebbuttonevenements_clicked(GtkButton *button, gpointer user_data);
void on_chihebcheckniveauxd_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebbuttonrech_clicked(GtkButton *button, gpointer user_data);
void on_chihebradiotarifg_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebradiotarifp_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_dec9_clicked(GtkButton *button, gpointer user_data);

/* COACH window callbacks */
void on_ghbuttoninscription_clicked(GtkButton *button, gpointer user_data);
void on_dec10_clicked(GtkButton *button, gpointer user_data);
void on_talelspinnombre_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelspinjour1_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelspinmois1_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelspinannee1_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelbuttonequipement_clicked(GtkButton *button, gpointer user_data);
void on_talelbuttonrech1_clicked(GtkButton *button, gpointer user_data);
void on_dec11_clicked(GtkButton *button, gpointer user_data);
void on_ranatreeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path,
                                   GtkTreeViewColumn *column, gpointer user_data);
void on_ranabuttonrech1_clicked(GtkButton *button, gpointer user_data);
void on_ranabuttoncentres_clicked(GtkButton *button, gpointer user_data);
void on_dec12_clicked(GtkButton *button, gpointer user_data);

/* ADMINISTRATION window callbacks */
void on_dhiabuttonajout_clicked(GtkButton *button, gpointer user_data);
void on_dec1_clicked(GtkButton *button, gpointer user_data);
void on_button1_clicked(GtkButton *button, gpointer user_data);
void on_button2_clicked(GtkButton *button, gpointer user_data);
void on_ghbouttonsupprimer_clicked(GtkButton *button, gpointer user_data);
void on_dec2_clicked(GtkButton *button, gpointer user_data);
void on_8h___1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_10h___12h1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_14h___16h1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_16___18h1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_dec3_clicked(GtkButton *button, gpointer user_data);
void on_talelspindispo_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelspinjour_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelspinmois_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelspinannee_value_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_talelbuttonmod_clicked(GtkButton *button, gpointer user_data);
void on_talelbuttonsupp_clicked(GtkButton *button, gpointer user_data);
void on_dec4_clicked(GtkButton *button, gpointer user_data);
void on_talelmenucategorie_changed(GtkWidget *widget, gpointer user_data);
void on_talelradioetatd_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_talelradioetatn_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_talelbuttonajout_clicked(GtkButton *button, gpointer user_data);
void on_ranaspincapacite_changed(GtkWidget *widget, gpointer user_data);
void on_ranatreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path,
                                  GtkTreeViewColumn *column, gpointer user_data);
void on_ranabuttonrech_clicked(GtkButton *button, gpointer user_data);
void on_ranabouttonmod_clicked(GtkButton *button, gpointer user_data);
void on_ranabouttonsup_clicked(GtkButton *button, gpointer user_data);
void on_ranabuttonajout_clicked(GtkButton *button, gpointer user_data);
void on_dec5_clicked(GtkButton *button, gpointer user_data);
void on_ranaradioproprieteei_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_ranaradioproprieteep_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_calendar2_day_selected(GtkCalendar *calendar, gpointer user_data);
void on_chihebbuttonrecherche_clicked(GtkButton *button, gpointer user_data);
void on_chihebcheckniveauavance_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebbuttonajout_clicked(GtkButton *button, gpointer user_data);
void on_chihebbuttonmodifier_clicked(GtkButton *button, gpointer user_data);
void on_chihebbuttonsupprimer_clicked(GtkButton *button, gpointer user_data);
void on_chihebcheckniveaudebutant_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebcheckniveauinter_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_dec6_clicked(GtkButton *button, gpointer user_data);
void on_chihebtreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path,
                                    GtkTreeViewColumn *column, gpointer user_data);

/* CONNECTION window callbacks */
void on_loginbuttonlogin_clicked(GtkButton *button, gpointer user_data);

#endif
