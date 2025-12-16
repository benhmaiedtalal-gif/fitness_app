#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>
#include "event.h"

/* Global variables */
extern Evenement e;
extern int modification_mode;
extern int selected_event_id;
extern int niveaux_choix[3];

/* Helper functions */
void afficher_evenements(GtkWidget *treeview);
void vider_treeview(GtkWidget *treeview);
char* get_combo_entry_text(GtkWidget *combo);
void set_combo_entry_text(GtkWidget *combo, char *text);
void clear_input_fields(GtkWidget *objet_graphique);
void load_event_to_fields(Evenement event, GtkWidget *objet_graphique);
void set_niveaux_checkboxes(char *niveaux_str, int n, GtkWidget *objet_graphique);
void construire_niveaux(int choix[], char texte[]);

/* Callback functions */
void on_chihebtreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_actualiser_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_jour3_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_jour2_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_item1_activate(GtkMenuItem *menuitem, gpointer user_data);
void on_horaire1_activate(GtkMenuItem *menuitem, gpointer user_data);
gboolean on_chihebtreeview_popup_menu(GtkWidget *widget, gpointer user_data);
void on_chihebbuttonrech_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_chihebradiotarifp_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebradiotarifg_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebcheckniveauxd_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebcheckniveauxi_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebcheckniveauxa_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebbuttonevenements_clicked(GtkButton *button, gpointer user_data);
void on_jour1_activate(GtkMenuItem *menuitem, gpointer user_data);
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
void on_calendar2_day_selected(GtkCalendar *calendar, gpointer user_data);
void on_chihebbuttonrecherche_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_chihebbuttonajout_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_chihebcheckniveaudebutant_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebcheckniveauinter_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_chihebcheckniveauavance_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_loginbuttonlogin_clicked(GtkWidget *objet_graphique, gpointer user_data);
void
on_chihebbuttonsupprimer_clicked       (GtkButton       *objet_graphique,
                                        gpointer         user_data);

void
on_chihebbuttonmodifier_clicked        (GtkButton       *objet_graphique,
                                        gpointer         user_data);
void verifier_et_corriger_date();
void initialiser_date_par_defaut();
void initialiser_evenement_global();
void
on_chihebtreeview_row_activated2        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);
void
on_dhiatreeview_row_activated          (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_dhiabuttonrech_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_dhiabuttonaffilations_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_dec7_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_dec8_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_dec9_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_ghbuttoninscription_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_dec10_clicked                       (GtkButton       *button,
                                        gpointer         user_data);

void
on_talelspinnombre_value_changed       (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_talelspinjour1_value_changed        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_talelspinmois1_value_changed        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_talelspinannee1_value_changed       (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_talelbuttonequipement_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_talelbuttonrech1_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_dec11_clicked                       (GtkButton       *button,
                                        gpointer         user_data);

void
on_ranatreeview1_row_activated         (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_ranabuttonrech1_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_ranabuttoncentres_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_dec12_clicked                       (GtkButton       *button,
                                        gpointer         user_data);

void
on_dhiabuttonajout_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_button1_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button2_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_dec1_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_ghtreeview_row_activated            (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_ghbouttonsupprimer_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_8h___1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_10h___12h1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_14h___16h1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_16___18h1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_dec2_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_eyabuttonsupprimer_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_eyabuttonmodifier_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_dec3_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_talelspindispo_value_changed        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_talelspinjour_value_changed         (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_talelspinmois_value_changed         (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_talelspinannee_value_changed        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_talelbuttonmod_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_talelbuttonsupp_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_talelmenucategorie_changed          (GtkOptionMenu   *optionmenu,
                                        gpointer         user_data);

void
on_talelradioetatd_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_talelradioetatn_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_talelbuttonajout_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_dec4_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_ranaspincapacite_changed            (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_ranatreeview_row_activated          (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_ranaradioproprieteei_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_ranaradioproprieteep_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_ranabuttonrech_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_ranabouttonmod_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_ranabouttonsup_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_ranabuttonajout_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_dec5_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_dec6_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

#endif /* CALLBACKS_H */






void
on_eyabuttonajout_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_talelbuttonrech_clicked             (GtkButton       *button,
                                        gpointer         user_data);
