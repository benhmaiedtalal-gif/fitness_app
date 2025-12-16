#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "event.h"
#include "users.h"

GtkWidget *admin_window = NULL;
GtkWidget *membre_window = NULL;
GtkWidget *coach_window = NULL;

Evenement e;
int selected_event_id = -1;
int selected_event_id2 = -1;
int niveaux_choix[3] = {0, 0, 0};
int current_user_id = -1; 
int user_id;

enum {
    COL_ID,
    COL_NOM,
    COL_CATEGORIE,
    COL_LIEU,
    COL_TARIF,
    COL_NIVEAUX,
    COL_ETAT,
    COL_COACH,
    COL_CAPACITE,
    COL_PERIODE,
    COL_DATE,
    N_COLUMNS
};
void initialiser_evenement_global() {
    e.id = -1;
    e.nom[0] = '\0';
    e.categorie[0] = '\0';
    e.lieu[0] = '\0';
    e.tarif = 'G';  /* Par défaut Gratuit */
    e.niveaux[0] = '\0';
    e.etat[0] = '\0';
    e.coach[0] = '\0';
    e.capacite = 0;
    e.periode = 0;
    
    /* INITIALISER LA DATE AVEC AUJOURD'HUI */
    time_t maintenant = time(NULL);
    struct tm *aujourdhui = localtime(&maintenant);
    sprintf(e.date, "%02d/%02d/%d", 
            aujourdhui->tm_mday, 
            aujourdhui->tm_mon + 1, 
            aujourdhui->tm_year + 1900);
}

void
afficher_evenements                     (GtkWidget      *widget_treeview)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    GtkTreeView *treeview;
    GtkTreeModel *model;
    int id;
    char nom[100];
    char categorie[100];
    char lieu[100];
    char tarif;
    char niveaux[100];
    char etat[100];
    char coach[100];
    int capacite;
    int periode; 
    char date[50];
    store=NULL;
    FILE *f;
    treeview =GTK_TREE_VIEW(widget_treeview);
model = gtk_tree_view_get_model(treeview);
  if(model==NULL){
g_print("creation des colonnes");
renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", COL_ID, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", COL_NOM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Catégorie", renderer, "text", COL_CATEGORIE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Lieu", renderer, "text", COL_LIEU, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Tarif", renderer, "text", COL_TARIF, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Niveaux", renderer, "text", COL_NIVEAUX, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Etat", renderer, "text", COL_ETAT, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Coach", renderer, "text", COL_COACH, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Capacite", renderer, "text", COL_CAPACITE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
  
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Periode", renderer, "text", COL_PERIODE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
 
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", COL_DATE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
}
 store = gtk_list_store_new(N_COLUMNS,
        G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
        G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
        G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);

 f = fopen("evenement.txt", "r");
if (f==NULL){
gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        g_object_unref(store);
        return;}
else {
        int ligne_num = 0;
        int res;
        
        // BOUCLE CORRIGÉE : while au lieu de do while
        while ((res = fscanf(f, "%d;%99[^;];%49[^;];%99[^;];%c;%99[^;];%49[^;];%99[^;];%d;%d;%49[^\n]",
                           &id, nom, categorie, lieu, &tarif, niveaux,
                           etat, coach, &capacite, &periode, date)) == 11) {
            
            ligne_num++;
            g_print("Ligne %d: ID=%d, Nom=%s\n", ligne_num, id,nom);
            
            char tarif_str[10];
            if (tarif == 'G') {
                strcpy(tarif_str, "GRATUIT");
            } else {
                strcpy(tarif_str, "PAYE");
            }
            
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                              COL_ID, id,
                              COL_NOM, nom,
                              COL_CATEGORIE, categorie,
                              COL_LIEU, lieu,
                              COL_TARIF, tarif_str,
                              COL_NIVEAUX, niveaux,
                              COL_ETAT, etat,
                              COL_COACH, coach,
                              COL_CAPACITE, capacite,
                              COL_PERIODE, periode,
                              COL_DATE, date,
                              -1);
            
            // IMPORTANT: Consommer le \n
            fgetc(f);
        }
        
        // Vérifier pourquoi on a quitté la boucle
        if (!feof(f)) {
            g_print("ATTENTION: Sortie de boucle avec res=%d (pas EOF)\n", res);
            
            // Lire le reste pour debug
            char buffer[100];
            if (fgets(buffer, sizeof(buffer), f) != NULL) {
                g_print("Reste de la ligne: %s\n", buffer);
            }
        }
        
        g_print("Fichier fermé...\n");
        fclose(f);
    }
gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
g_object_unref(store); 
g_print("fin...");
}
   


void
vider_treeview                          (GtkWidget      *widget_treeview)
{
    
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    GtkTreeView *treeview;
    GtkTreeModel *model;
    int id;
    char nom[50];
    char categorie[50];
    char lieu[50];
    char tarif;
    char niveaux[50];
    char etat[50];
    char coach[50];
    int capacite;
    int periode; 
    char date[50];
    store=NULL;
    FILE *f;
    treeview =GTK_TREE_VIEW(widget_treeview);
    model = gtk_tree_view_get_model(treeview);
    if(model==NULL){
renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", COL_ID, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", COL_NOM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Catégorie", renderer, "text", COL_CATEGORIE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Lieu", renderer, "text", COL_LIEU, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Tarif", renderer, "text", COL_TARIF, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Niveaux", renderer, "text", COL_NIVEAUX, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Etat", renderer, "text", COL_ETAT, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Coach", renderer, "text", COL_COACH, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Capacite", renderer, "text", COL_CAPACITE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
  
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Periode", renderer, "text", COL_PERIODE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
 
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", COL_DATE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
}
store = gtk_list_store_new(N_COLUMNS,
        G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
        G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
        G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);    
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);
}

char*
get_combo_entry_text                    (GtkWidget      *combo)
{
    GtkWidget *entry = gtk_bin_get_child(GTK_BIN(combo));
    return (char*)gtk_entry_get_text(GTK_ENTRY(entry));
}

void
set_combo_entry_text                    (GtkWidget      *combo,
                                         char           *text)
{
    GtkWidget *entry = gtk_bin_get_child(GTK_BIN(combo));
    gtk_entry_set_text(GTK_ENTRY(entry), text);
}

void clear_input_fields(GtkWidget *objet_graphique) {
    GtkWidget *id_input = lookup_widget(objet_graphique, "chihebinputid");
    GtkWidget *nom_input = lookup_widget(objet_graphique, "chihebinputnom");
    GtkWidget *lieu_input = lookup_widget(objet_graphique, "chihebinputlieu");
    GtkWidget *coach_input = lookup_widget(objet_graphique, "chihebinputcoach");
    GtkWidget *capacite_scale = lookup_widget(objet_graphique, "chihebscalecapacite");
    GtkWidget *periode_spin = lookup_widget(objet_graphique, "chihebspinperiode");
    GtkWidget *etat_combo = lookup_widget(objet_graphique, "chihebcomboetat");
    GtkWidget *input = lookup_widget(objet_graphique, "chihebinputrecherche");
    gtk_entry_set_text(GTK_ENTRY(input), "");
    gtk_entry_set_text(GTK_ENTRY(id_input), "");
    gtk_entry_set_text(GTK_ENTRY(nom_input), "");
    gtk_entry_set_text(GTK_ENTRY(lieu_input), "");
    gtk_entry_set_text(GTK_ENTRY(coach_input), "");
    gtk_range_set_value(GTK_RANGE(capacite_scale), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(periode_spin), 0);
    
    set_combo_entry_text(etat_combo, "");
    
    GtkWidget *tarif_g = lookup_widget(objet_graphique, "chihebradiotarifg");
    GtkWidget *tarif_p = lookup_widget(objet_graphique, "chihebradiotarifp");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tarif_g), TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tarif_p), FALSE);
    
    GtkWidget *niv_d = lookup_widget(objet_graphique, "chihebcheckniveaudebutant");
    GtkWidget *niv_i = lookup_widget(objet_graphique, "chihebcheckniveauinter");
    GtkWidget *niv_a = lookup_widget(objet_graphique, "chihebcheckniveauavance");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(niv_d), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(niv_i), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(niv_a), FALSE);
    
    e.id = -1;
    e.nom[0] = '\0';
    e.categorie[0] = '\0';
    e.lieu[0] = '\0';
    e.tarif = 'G';
    e.niveaux[0] = '\0';
    e.etat[0] = '\0';
    e.coach[0] = '\0';
    e.date[0] = '\0';
    e.capacite = 0;
    e.periode = 0;
    niveaux_choix[0] = 0;
    niveaux_choix[1] = 0;
    niveaux_choix[2] = 0;
}

void
load_event_to_fields                    (Evenement      event,GtkWidget *objet_graphique)
{
    GtkWidget *id_input = lookup_widget(objet_graphique, "chihebinputid");
    GtkWidget *nom_input = lookup_widget(objet_graphique, "chihebinputnom");
    GtkWidget *lieu_input = lookup_widget(objet_graphique, "chihebinputlieu");
    GtkWidget *coach_input = lookup_widget(objet_graphique, "chihebinputcoach");
    GtkWidget *capacite_scale = lookup_widget(objet_graphique, "chihebscalecapacite");
    GtkWidget *periode_spin = lookup_widget(objet_graphique, "chihebspinperiode");
    GtkWidget *etat_combo = lookup_widget(objet_graphique, "chihebcomboetat");

    char id_str[20];
    sprintf(id_str, "%d", event.id);
    char lieu_text[100];
strcpy(lieu_text, event.lieu);
/* Si le premier caractère est un espace, rendre vide */
if (lieu_text[0] == ' ') {
    lieu_text[0] = '\0';
}

char coach_text[100];
strcpy(coach_text, event.coach);
if (coach_text[0] == ' ') {
    coach_text[0] = '\0';
}

char etat_text[100];
strcpy(etat_text, event.etat);
if (etat_text[0] == ' ') {
    etat_text[0] = '\0';
}

/* Tarif par défaut */
if (e.tarif != 'G' && e.tarif != 'P') {
    e.tarif = 'G';
}
    gtk_entry_set_text(GTK_ENTRY(id_input), id_str);
    gtk_entry_set_text(GTK_ENTRY(nom_input), event.nom);
    gtk_entry_set_text(GTK_ENTRY(lieu_input), lieu_text);
    gtk_entry_set_text(GTK_ENTRY(coach_input), coach_text);
    
    gtk_range_set_value(GTK_RANGE(capacite_scale), (gdouble)event.capacite);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(periode_spin), (gdouble)event.periode);
    
    set_combo_entry_text(etat_combo, etat_text);
    
    GtkWidget *tarif_g = lookup_widget(objet_graphique, "chihebradiotarifg");
    GtkWidget *tarif_p = lookup_widget(objet_graphique, "chihebradiotarifp");
    
    if (event.tarif == 'G') {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tarif_g), TRUE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tarif_p), FALSE);
    } else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tarif_g), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tarif_p), TRUE);
    }
    
    set_niveaux_checkboxes(event.niveaux, 0,objet_graphique);
    e = event;

}



void on_actualiser_clicked(GtkWidget *objet_graphique, gpointer user_data) {
    GtkWidget *treeview = lookup_widget(objet_graphique, "chihebtreeview");
    vider_treeview(treeview);
    afficher_evenements(treeview);
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
on_horaire1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}





void
on_chihebradiotarifp_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        e.tarif = 'P';
    }
}

void
on_chihebradiotarifg_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        e.tarif = 'G';
    }
}

void
on_chihebcheckniveauxd_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        niveaux_choix[0] = 1;
    else
        niveaux_choix[0] = 0;
}

void
on_chihebcheckniveauxi_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        niveaux_choix[1] = 1;
    else
        niveaux_choix[1] = 0;
}

void
on_chihebcheckniveauxa_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        niveaux_choix[2] = 1;
    else
        niveaux_choix[2] = 0;
}

void
on_jour1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}

void
on_entrainement2_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "ENTRAINEMENT");
}

void
on_musculation1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "MUSCULATION");
}

void
on_cardio_training1_activate           (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "CARDIO_TRAINING");
}

void
on_cross_training1_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "CROSS_TRAINING");
}

void
on_circuit_training1_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "CIRCUIT_TRAINING");
}

void
on_bien_etre1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "BIEN_ETRE");
}

void
on_yoga1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "YOGA");
}

void
on_pstretching1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "PSTRETCHING");
}

void
on_meditation1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "MEDITATION");
}

void
on_cours_collectifs2_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "COURS_COLLECTIFS");
}

void
on_zumba1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "ZUMBA");
}

void
on_boxe1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "BOXE");
}

void
on_cycling1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "CYCLING");
}

void
on_bootcamp1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "BOOTCAMP");
}

void
on_seance_en_groupe1_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "SEANCE_EN_GROUPE");
}

void
on_coaching___suivi2_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "COACHING_SUIVI");
}

void
on_seance_decouverte1_activate         (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "SEANCE_DECOUVERTE");
}

void
on_planification_d_objectifs1_activate (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "PLANIFICATION_OBJECTIFS");
}

void
on_coaching_nutritionnel1_activate     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "COACHING_NUTRITIONNEL");
}

void
on_musculation2_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "MUSCULATION");
}

void
on_cardio_training2_activate           (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "CARDIO_TRAINING");
}

void
on_circuit_training2_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "CIRCUIT_TRAINING");
}

void
on_yoga2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "YOGA");
}

void
on_pstretching2_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "PSTRETCHING");
}

void
on_mediation1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "MEDITATION");
}

void
on_zumba2_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "ZUMBA");
}

void
on_boxe2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "BOXE");
}

void
on_cycling2_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "CYCLING");
}

void
on_bootcamp4_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "BOOTCAMP");
}

void
on_sceace_en_groupe1_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "SEANCE_EN_GROUPE");
}

void
on_sceance_decouverte1_activate        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "SEANCE_DECOUVERTE");
}

void
on_planification_d_objet1_activate     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "PLANIFICATION_OBJECTIFS");
}

void
on_coaching_nutritionnel2_activate     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    strcpy(e.categorie, "COACHING_NUTRITIONNEL");
}

void on_calendar2_day_selected(GtkCalendar *calendar, gpointer user_data)
{
    guint year, month, day;
    
    /* Récupérer la date sélectionnée */
    gtk_calendar_get_date(calendar, &year, &month, &day);
    
    /* Stocker dans e.date */
    sprintf(e.date, "%02d/%02d/%d", day, month + 1, year);
}
void initialiser_date_par_defaut() {
    time_t maintenant = time(NULL);
    struct tm *aujourdhui = localtime(&maintenant);
    
    /* Formater la date dans e.date */
    sprintf(e.date, "%02d/%02d/%d", 
            aujourdhui->tm_mday, 
            aujourdhui->tm_mon + 1, 
            aujourdhui->tm_year + 1900);
}
void verifier_et_corriger_date() {
    /* Si e.date est vide ou invalide, mettre date du jour */
    if (strlen(e.date) == 0) {
        initialiser_date_par_defaut();
    }
}
void
on_chihebbuttonrecherche_clicked       (GtkWidget *objet_graphique,
                                        gpointer         user_data)
{

    GtkWidget *input;
    char text[100];
    int id;
    
    input = lookup_widget(objet_graphique, "chihebinputrecherche");
    strcpy(text, gtk_entry_get_text(GTK_ENTRY(input)));
    
    if (strlen(text) == 0) {
        return;
    }
        e = chercher_simple("evenement.txt", text);
    if (e.id != -1) {
        load_event_to_fields(e, objet_graphique);
    }
GtkWidget *btn_supprimer = lookup_widget(objet_graphique,"chihebbuttonsupprimer");
        if (btn_supprimer) {
            gtk_widget_hide(btn_supprimer);
        }
GtkWidget *btn_modifier = lookup_widget(objet_graphique, "chihebbuttonmodifier");
        if (btn_modifier) {
            gtk_widget_hide(btn_modifier);
        }
}

void
on_chihebbuttonajout_clicked           (GtkWidget *objet_graphique,
                                        gpointer         user_data)
{   
    GtkWidget *id_input = lookup_widget(objet_graphique, "chihebinputid");
    GtkWidget *nom_input = lookup_widget(objet_graphique, "chihebinputnom");
    GtkWidget *lieu_input = lookup_widget(objet_graphique, "chihebinputlieu");
    GtkWidget *coach_input = lookup_widget(objet_graphique, "chihebinputcoach");
    GtkWidget *capacite_scale = lookup_widget(objet_graphique, "chihebscalecapacite");
    GtkWidget *periode_spin = lookup_widget(objet_graphique, "chihebspinperiode");
    GtkWidget *etat_combo = lookup_widget(objet_graphique, "chihebcomboetat");
    GtkWidget *tarif_g = lookup_widget(objet_graphique, "chihebradiotarifg");
    GtkWidget *tarif_p = lookup_widget(objet_graphique, "chihebradiotarifp");
    char id_text[100];
    strcpy(id_text, gtk_entry_get_text(GTK_ENTRY(id_input)));
    if(id_text[0]=='\0')
	return;

    char nom_text[100];
    strcpy(nom_text, gtk_entry_get_text(GTK_ENTRY(nom_input)));
    if(nom_text[0]=='\0')
	return;
    char lieu_text[100];
    strcpy(lieu_text, gtk_entry_get_text(GTK_ENTRY(lieu_input)));
    if(lieu_text[0]=='\0')
	strcpy(lieu_text," ");
    char coach_text[100];
    strcpy(coach_text, gtk_entry_get_text(GTK_ENTRY(coach_input)));
    if(coach_text[0]=='\0')
	strcpy(coach_text," ");
    char etat_text[100];
    strcpy(etat_text, gtk_combo_box_get_active_text(GTK_COMBO_BOX(etat_combo)));
    if(etat_text[0]=='\0')
	strcpy(etat_text," ");
    if (e.tarif != 'G' && e.tarif != 'P') {
        e.tarif = 'G';  /* Par défaut: Gratuit */
    }
    if (strlen(id_text) !=4 || strlen(nom_text) == 0) {
        return;
    }
    char niveaux_text[100];
    construire_niveaux(niveaux_choix, niveaux_text);
    if(niveaux_text[0]=='\0')
	strcpy(niveaux_text," ");
    strcpy(e.niveaux, niveaux_text);
    e.id = atoi(id_text);
    strcpy(e.nom, nom_text);
    strcpy(e.lieu, lieu_text);
    strcpy(e.coach, coach_text);
    strcpy(e.etat, etat_text);
    e.capacite = (int)gtk_range_get_value(GTK_RANGE(capacite_scale));
    e.periode = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(periode_spin));
    if (strlen(e.categorie) == 0) {
        strcpy(e.categorie, " ");
    }
    int success;
    success = ajouter("evenement.txt", e);
 
    
    if (success==1) {
        GtkWidget *treeview = lookup_widget(objet_graphique, "chihebtreeview");
        vider_treeview(treeview);
        afficher_evenements(treeview);
        clear_input_fields(objet_graphique);
        
    }
}

void
on_chihebcheckniveaudebutant_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        niveaux_choix[0] = 1;
    else
        niveaux_choix[0] = 0;
}

void
on_chihebcheckniveauinter_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        niveaux_choix[1] = 1;
    else
        niveaux_choix[1] = 0;
}

void
on_chihebcheckniveauavance_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        niveaux_choix[2] = 1;
    else
        niveaux_choix[2] = 0;
}

void
on_loginbuttonlogin_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
    GtkWidget *id_input = lookup_widget(objet_graphique, "logininputid");
    GtkWidget *mdp_input = lookup_widget(objet_graphique, "logininputmdp");
    
    char id_text[100];
    strcpy(id_text, gtk_entry_get_text(GTK_ENTRY(id_input)));
    char mdp_text[100];
    strcpy(mdp_text, gtk_entry_get_text(GTK_ENTRY(mdp_input)));
    
    char type[20];
    
    g_print("=== TENTATIVE DE CONNEXION ===\n");
    g_print("ID saisi: '%s'\n", id_text);
    g_print("MDP saisi: '%s'\n", mdp_text);
    

    
    if (verifier_utilisateur("users.txt", id_text, mdp_text, type)) {        
        GtkWidget *login_window = lookup_widget(objet_graphique, "CONNECTION");
        gtk_widget_hide(login_window);
        
        if (strcmp(type, "admin") == 0) {
	    user_id=atoi(id_text);
	    membre_window = create_MEMBRE();
            if (membre_window && GTK_IS_WIDGET(membre_window)) {
                gtk_widget_show_all(membre_window);
                GtkWidget *treeview2 = lookup_widget(membre_window, "chihebtreeview2");
                if (treeview2) {
                    initialiser_evenement_global();
                    afficher_evenements(treeview2);}}
	    coach_window = create_COACH();
            if (coach_window && GTK_IS_WIDGET(coach_window)) {
                gtk_widget_show_all(coach_window);}

            admin_window = create_ADMINISTRATION();
            if (admin_window && GTK_IS_WIDGET(admin_window)) {
                gtk_widget_show_all(admin_window);
                GtkWidget *treeview = lookup_widget(admin_window, "chihebtreeview");
                if (treeview) {
                    initialiser_evenement_global();
                    afficher_evenements(treeview);
                    GtkWidget *btn_supprimer = lookup_widget(admin_window,"chihebbuttonsupprimer");
        	    if (btn_supprimer) {
            		gtk_widget_hide(btn_supprimer);
        }
		    GtkWidget *btn_modifier = lookup_widget(admin_window, "chihebbuttonmodifier");
        	    if (btn_modifier) {
                 	gtk_widget_hide(btn_modifier);
        }
                }
            }
        }
        else if (strcmp(type, "coach") == 0) {
            g_print("Ouverture fenêtre COACH...\n");
            GtkWidget *coach_window = create_COACH();
            if (coach_window && GTK_IS_WIDGET(coach_window)) {
                g_print("Fenêtre COACH créée\n");
                gtk_widget_show_all(coach_window);
            }
        }
        else if (strcmp(type, "membre") == 0) {
            g_print("Ouverture fenêtre MEMBRE...\n");
            GtkWidget *membre_window = create_MEMBRE();
            if (membre_window && GTK_IS_WIDGET(membre_window)) {
                g_print("Fenêtre MEMBRE créée\n");
                gtk_widget_show_all(membre_window);
            }
        }
        else {
            g_print("ERREUR: Type inconnu '%s'\n", type);
            // Réafficher la fenêtre de connexion
            gtk_widget_show(login_window);
            return;
        }
        
        // Vider les champs de saisie
        gtk_entry_set_text(GTK_ENTRY(id_input), "");
        gtk_entry_set_text(GTK_ENTRY(mdp_input), "");
        
    } else {
        g_print("=== ÉCHEC DE CONNEXION ===\n");
        g_print("ID ou mot de passe incorrect\n");
        
     gtk_entry_set_text(GTK_ENTRY(id_input), "");
        gtk_entry_set_text(GTK_ENTRY(mdp_input), "");
    }
}

void construire_niveaux(int choix[], char texte[])
{
    /* Initialiser le texte à vide */
    texte[0] = '\0';
    
    int premier = 1;  /* Flag pour savoir si c'est le premier niveau */
    
    if (choix[0] == 1) {  /* DÉBUTANT */
        if (!premier) {
            strcat(texte, ",");
        }
        strcat(texte, "DEBUTANT");
        premier = 0;
    }
    
    if (choix[1] == 1) {  /* INTERMÉDIAIRE */
        if (!premier) {
            strcat(texte, ",");
        }
        strcat(texte, "INTERMEDIAIRE");
        premier = 0;
    }
    
    if (choix[2] == 1) {  /* AVANCÉ */
        if (!premier) {
            strcat(texte, ",");
        }
        strcat(texte, "AVANCE");
        premier = 0;
    }
    
    if (premier) {
        strcpy(texte, " ");
    }
}
void set_niveaux_checkboxes(char *niveaux_str, int n, GtkWidget *objet_graphique)
{
    niveaux_choix[0] = 0;
    niveaux_choix[1] = 0;
    niveaux_choix[2] = 0;
    
    GtkWidget *check_debutant = NULL;
    GtkWidget *check_inter = NULL;
    GtkWidget *check_avance = NULL;
    
    if (n == 0) {
        check_debutant = lookup_widget(objet_graphique, "chihebcheckniveaudebutant");
        check_inter = lookup_widget(objet_graphique, "chihebcheckniveauinter");
        check_avance = lookup_widget(objet_graphique, "chihebcheckniveauavance");
    } else if (n == 1) {
        check_debutant = lookup_widget(objet_graphique, "chihebcheckniveaud");
        check_inter = lookup_widget(objet_graphique, "chihebcheckniveaui");
        check_avance = lookup_widget(objet_graphique, "chihebcheckniveaua");
    }
    
    /* Réinitialiser */
    if (check_debutant != NULL) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_debutant), FALSE);
    if (check_inter != NULL) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_inter), FALSE);
    if (check_avance != NULL) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_avance), FALSE);
    
    /* Vérifier les combinaisons */
    if (strstr(niveaux_str, "DEBUTANT") != NULL) {
        niveaux_choix[0] = 1;
        if (check_debutant != NULL) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_debutant), TRUE);
    }
    
    if (strstr(niveaux_str, "INTERMEDIAIRE") != NULL) {
        niveaux_choix[1] = 1;
        if (check_inter != NULL) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_inter), TRUE);
    }
    
    if (strstr(niveaux_str, "AVANCE") != NULL) {
        niveaux_choix[2] = 1;
        if (check_avance != NULL) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_avance), TRUE);
    }
}

void
on_chihebtreeview_row_activated(GtkTreeView    *treeview,
                                GtkTreePath    *path,
                                GtkTreeViewColumn *column,
                                gpointer         user_data)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    int event_id;
    int verif;
    
    model = gtk_tree_view_get_model(treeview);
GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(treeview));
                
                if (window && GTK_IS_WINDOW(window)) {    
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(model, &iter, 0, &event_id, -1);
        
        if (event_id != -1) {
            verif = chercher_id("evenement.txt", event_id);
            if(verif==1){
g_print("verif=%d",verif);
			selected_event_id=event_id;}
                    
                }
            }}
GtkWidget *btn_supprimer = lookup_widget(window, "chihebbuttonsupprimer");
        if (btn_supprimer) {
            gtk_widget_show(btn_supprimer);
        }
GtkWidget *btn_modifier = lookup_widget(window, "chihebbuttonmodifier");
        if (btn_modifier) {
            gtk_widget_show(btn_modifier);
        }
        }



void
on_chihebbuttonsupprimer_clicked       (GtkButton       *objet_graphique,
                                        gpointer         user_data)
{

if (selected_event_id != -1) {
        if (supprimer("evenement.txt", selected_event_id)) {
            GtkWidget *widget = GTK_WIDGET(objet_graphique);
	    GtkWidget *treeview = lookup_widget(widget, "chihebtreeview");
            vider_treeview(treeview);
            afficher_evenements(treeview);

GtkWidget *btn_modifier = lookup_widget(widget, "chihebbuttonmodifier");
        if (btn_modifier) {
            gtk_widget_hide(btn_modifier);
        }
gtk_widget_hide(widget);
    
        selected_event_id = -1;

            }
    }
}
void
on_chihebbuttonmodifier_clicked        (GtkButton       *objet_graphique,
                                        gpointer         user_data)
{
if (selected_event_id != -1) {
        e = chercher("evenement.txt", selected_event_id);
        if (e.id != -1) {
            GtkWidget *widget = GTK_WIDGET(objet_graphique);
	    load_event_to_fields(e, widget);
            supprimer("evenement.txt", selected_event_id);
            gtk_widget_hide(widget);
GtkWidget *btn_supprimer = lookup_widget(widget, "chihebbuttonsupprimer");
        if (btn_supprimer) {
            gtk_widget_hide(btn_supprimer);
        }
	    char lieu_text[100];
            }
}}

void
on_chihebtreeview_row_activated2        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    int event_id;
    int verif;
    
    g_print("=== CLIC SUR TREEVIEW2 ===\n");
    
    model = gtk_tree_view_get_model(treeview);
    if (model == NULL) {
        g_print("ERREUR: modèle NULL\n");
        return;
    }
    
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(model, &iter, 0, &event_id, -1);
        g_print("Event ID récupéré: %d\n", event_id);
        
        if (event_id != -1) {
            verif = chercher_id("evenement.txt", event_id);
            g_print("Vérification dans fichier: %d\n", verif);
            
            if(verif == 1) {
                selected_event_id2 = event_id;
                g_print("selected_event_id2 mis à jour: %d\n", selected_event_id2);
            } else {
                g_print("ERREUR: Événement non trouvé dans fichier\n");
            }
        } else {
            g_print("ERREUR: event_id = -1\n");
        }
    } else {
        g_print("ERREUR: Impossible de récupérer l'itérateur\n");
    }
}
void
on_chihebbuttonevenements_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
    
    g_print("=== TENTATIVE D'INSCRIPTION ===\n");
    g_print("User ID: %d\n", user_id);
    g_print("selected_event_id2: %d\n", selected_event_id2);
    g_print("e.id (global): %d\n", e.id);
    
    /* Utilisez selected_event_id2 qui est mis à jour par on_chihebtreeview_row_activated2 */
    if (selected_event_id2 != -1) {
        int resultat = inscrit("inscriptions.txt", user_id, selected_event_id2);
        
        if (resultat) {
            g_print("SUCCÈS: Inscription réussie pour user %d à event %d\n", 
                   user_id, selected_event_id2);
            
            /* Message de succès */
            GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_INFO,
                GTK_BUTTONS_OK,
                "Inscription réussie!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            
            /* Réinitialiser la sélection */
            selected_event_id2 = -1;
        } else {
            g_print("ÉCHEC: Déjà inscrit pour user %d à event %d\n", 
                   user_id, selected_event_id2);
            
            /* Message d'erreur */
            GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_WARNING,
                GTK_BUTTONS_OK,
                "Vous êtes déjà inscrit à cet événement.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    } else {
        g_print("ERREUR: Aucun événement sélectionné (selected_event_id2 = -1)\n");
        
        /* Message d'erreur - aucun événement sélectionné */
        GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez d'abord sélectionner un événement dans la liste.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}
void
on_chihebbuttonrech_clicked            (GtkWidget *objet_graphique,
                                        gpointer         user_data)
{
    GtkWidget *treeview = lookup_widget(objet_graphique, "chihebtreeview2");
    GtkWidget *input_lieu = lookup_widget(objet_graphique, "chihebinputlieu");
    GtkWidget *radio_gratuit = lookup_widget(objet_graphique, "chihebradiotarifg");
    GtkWidget *radio_paye = lookup_widget(objet_graphique, "chihebradiotarifp");
    GtkWidget *check_debutant = lookup_widget(objet_graphique, "chihebcheckniveauxd");
    GtkWidget *check_inter = lookup_widget(objet_graphique, "chihebcheckniveauxi");
    GtkWidget *check_avance = lookup_widget(objet_graphique, "chihebcheckniveauxa");
    GtkWidget *input_rech = lookup_widget(objet_graphique, "chihebinputrech");
    
    /* Récupérer les valeurs des champs */
    char lieu[100], recherche[100];
    
    /* Lieu */
    if (input_lieu) {
        const char *lieu_text = gtk_entry_get_text(GTK_ENTRY(input_lieu));
        strcpy(lieu, lieu_text);
    } else {
        strcpy(lieu, "");
    }
    
    /* Recherche texte - peut contenir ID, nom, etc. */
    if (input_rech) {
        const char *rech_text = gtk_entry_get_text(GTK_ENTRY(input_rech));
        strcpy(recherche, rech_text);
    } else {
        strcpy(recherche, "");
    }
    
    /* Tarif */
    char tarif = ' ';
    if (radio_gratuit && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_gratuit))) {
        tarif = 'G';
    }
    if (radio_paye && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_paye))) {
        tarif = 'P';
    }
    
    /* Niveaux - utilise la variable GLOBALE niveaux_choix */
    
    /* Vérifier si tous les critères sont vides */
    int tous_vides = (strlen(lieu) == 0 && 
                     strlen(recherche) == 0 && tarif == ' ' && 
                     niveaux_choix[0] == 0 && niveaux_choix[1] == 0 && niveaux_choix[2] == 0);
    
    /* Si tous vides, afficher tous les événements */
    if (tous_vides) {
        vider_treeview(treeview);
        afficher_evenements(treeview);
        return;
    }
    
    /* Ouvrir le fichier */
    FILE *f = fopen("evenement.txt", "r");
    if (f == NULL) {
        vider_treeview(treeview);
        return;
    }
    
    /* Créer les colonnes */
    vider_treeview(treeview);
    
    /* Créer un nouveau store */
    GtkListStore *store = gtk_list_store_new(N_COLUMNS,
        G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
        G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
        G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);
    
    GtkTreeIter iter;
    char ligne[300];
    int nb_resultats = 0;
    
    /* Lire et filtrer les événements avec logique AND (tous les critères doivent correspondre) */
    while (fgets(ligne, sizeof(ligne), f)) {
        /* Ignorer les lignes vides */
        if (strlen(ligne) <= 1) continue;
        
        /* Supprimer le saut de ligne */
        ligne[strcspn(ligne, "\n")] = 0;
        
        Evenement ev;
        int res = sscanf(ligne, "%d;%99[^;];%49[^;];%99[^;];%c;%99[^;];%49[^;];%99[^;];%d;%d;%49[^\n]",
                        &ev.id, ev.nom, ev.categorie, ev.lieu, &ev.tarif, ev.niveaux,
                        ev.etat, ev.coach, &ev.capacite, &ev.periode, ev.date);
        
        if (res == 11) {
            int correspond = 1;  /* Par défaut, correspond (logique AND) */
            
            /* 1. Vérifier Lieu (si spécifié) */
            if (strlen(lieu) > 0) {
                if (strstr(ev.lieu, lieu) == NULL) {
                    correspond = 0;
                }
            }
            
            /* 2. Vérifier Recherche texte (si spécifiée) */
            if (correspond && strlen(recherche) > 0) {
                /* Chercher dans tous les champs importants */
                /* Pour AND: doit trouver dans au moins un champ */
                
                /* Vérifier d'abord si c'est un ID numérique */
                int recherche_id = -1;
                if (sscanf(recherche, "%d", &recherche_id) == 1) {
                    /* C'est un nombre, vérifier si c'est l'ID */
                    if (ev.id == recherche_id) {
                        /* Correspond à l'ID, on garde */
                    } else {
                        /* Pas l'ID, vérifier les autres champs */
                        if (strstr(ev.nom, recherche) == NULL &&
                            strstr(ev.categorie, recherche) == NULL &&
                            strstr(ev.lieu, recherche) == NULL &&
                            strstr(ev.date, recherche) == NULL &&
                            strstr(ev.niveaux, recherche) == NULL) {
                            correspond = 0;
                        }
                    }
                } else {
                    /* Ce n'est pas un nombre, chercher dans les champs texte */
                    if (strstr(ev.nom, recherche) == NULL &&
                        strstr(ev.categorie, recherche) == NULL &&
                        strstr(ev.lieu, recherche) == NULL &&
                        strstr(ev.date, recherche) == NULL &&
                        strstr(ev.niveaux, recherche) == NULL) {
                        correspond = 0;
                    }
                }
            }
            
            /* 3. Vérifier Tarif (si spécifié) */
            if (correspond && tarif != ' ') {
                if (ev.tarif != tarif) {
                    correspond = 0;
                }
            }
            
            /* 4. Vérifier Niveaux (si spécifiés) - UTILISE niveaux_choix GLOBAL */
            if (correspond && (niveaux_choix[0] || niveaux_choix[1] || niveaux_choix[2])) {
                /* Pour les niveaux, on vérifie que l'événement contient AU MOINS UN des niveaux sélectionnés */
                int niveau_trouve = 0;
                
                if (niveaux_choix[0] && strstr(ev.niveaux, "DEBUTANT") != NULL) {
                    niveau_trouve = 1;
                }
                if (niveaux_choix[1] && strstr(ev.niveaux, "INTERMEDIAIRE") != NULL) {
                    niveau_trouve = 1;
                }
                if (niveaux_choix[2] && strstr(ev.niveaux, "AVANCE") != NULL) {
                    niveau_trouve = 1;
                }
                
                if (!niveau_trouve) {
                    correspond = 0;
                }
            }
            
            /* Si l'événement correspond, l'ajouter au TreeView */
            if (correspond) {
                char tarif_str[10];
                if (ev.tarif == 'G') {
                    strcpy(tarif_str, "GRATUIT");
                } else {
                    strcpy(tarif_str, "PAYE");
                }
                
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                    COL_ID, ev.id,
                    COL_NOM, ev.nom,
                    COL_CATEGORIE, ev.categorie,
                    COL_LIEU, ev.lieu,
                    COL_TARIF, tarif_str,
                    COL_NIVEAUX, ev.niveaux,
                    COL_ETAT, ev.etat,
                    COL_COACH, ev.coach,
                    COL_CAPACITE, ev.capacite,
                    COL_PERIODE, ev.periode,
                    COL_DATE, ev.date,
                    -1);
                
                nb_resultats++;
            }
        }
    }
    
    fclose(f);
    
    /* Mettre à jour le TreeView */
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);
    
    /* Si aucun résultat, afficher un message */
    if (nb_resultats == 0) {
        /* Correction: cast vers GtkWindow */
        GtkWidget *window = gtk_widget_get_toplevel(objet_graphique);
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Aucun événement ne correspond aux critères de recherche.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}


void
on_dhiatreeview_row_activated          (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
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
on_dec1_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_ghtreeview_row_activated            (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_ghbouttonsupprimer_clicked          (GtkButton       *button,
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
on_dec2_clicked                        (GtkButton       *button,
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
on_dec4_clicked                        (GtkButton       *button,
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
on_dec6_clicked(GtkButton *button, gpointer user_data)
{
    g_print("=== DÉCONNEXION - CACHE TOUTES LES FENÊTRES ===\n");
    
    /* Cacher ADMINISTRATION si elle existe et est visible */
    if (admin_window != NULL && gtk_widget_get_visible(admin_window)) {
        g_print("Cache ADMINISTRATION\n");
        gtk_widget_hide(admin_window);
        admin_window = NULL; /* Optionnel: libérer la référence */
    }
    
    /* Cacher MEMBRE si elle existe et est visible */
    if (membre_window != NULL && gtk_widget_get_visible(membre_window)) {
        g_print("Cache MEMBRE\n");
        gtk_widget_hide(membre_window);
        membre_window = NULL; /* Optionnel: libérer la référence */
    }
    
    /* Cacher COACH si elle existe et est visible */
    if (coach_window != NULL && gtk_widget_get_visible(coach_window)) {
        g_print("Cache COACH\n");
        gtk_widget_hide(coach_window);
        coach_window = NULL; /* Optionnel: libérer la référence */
    }
    
    /* Réouvrir la connexion */
    GtkWidget *login_window = create_CONNECTION();
    if (login_window) {
        gtk_widget_show_all(login_window);
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

