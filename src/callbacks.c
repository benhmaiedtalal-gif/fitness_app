#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>   
#include <gtk/gtk.h>
#include "callbacks.h"
#include "support.h"
#include "cours.h"

gchar* get_option_menu_text(GtkWidget *option_menu) {
    GtkWidget *menu = gtk_option_menu_get_menu(GTK_OPTION_MENU(option_menu));
    GtkWidget *active = gtk_menu_get_active(GTK_MENU(menu));
    if (active && GTK_BIN(active)->child && GTK_IS_LABEL(GTK_BIN(active)->child)) {
        return (gchar*)gtk_label_get_text(GTK_LABEL(GTK_BIN(active)->child));
    }
    return NULL;
}

void set_option_menu_by_text(GtkWidget *option_menu, const gchar *text) {
    if (!text) return;
    GtkWidget *menu = gtk_option_menu_get_menu(GTK_OPTION_MENU(option_menu));
    GList *children = gtk_container_get_children(GTK_CONTAINER(menu));
    int index = 0;
    for (GList *l = children; l; l = l->next, index++) {
        GtkWidget *child = GTK_WIDGET(l->data);
        if (GTK_BIN(child)->child && GTK_IS_LABEL(GTK_BIN(child)->child)) {
            const gchar *label = gtk_label_get_text(GTK_LABEL(GTK_BIN(child)->child));
            if (strcmp(label, text) == 0) {
                gtk_option_menu_set_history(GTK_OPTION_MENU(option_menu), index);
                break;
            }
        }
    }
    g_list_free(children);
}

void init_type_menu(GtkWidget *window) {
    if (!window) return;
    
    GtkWidget *type_menu = lookup_widget(window, "eyamenutype");
    if (!type_menu) return;
    
    if (!GTK_IS_OPTION_MENU(type_menu)) return;
    
    GtkWidget *menu = gtk_menu_new();
    const char *type_items[] = {"Mixte", "Féminin", "Masculin"};
    
    for (int i = 0; i < 3; i++) {
        GtkWidget *menu_item = gtk_menu_item_new_with_label(type_items[i]);
        gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);
        gtk_widget_show(menu_item);
        
        g_signal_connect(G_OBJECT(menu_item), "activate",
                        G_CALLBACK(on_type_menu_item_selected), 
                        (gpointer)type_items[i]);
    }
    
    gtk_option_menu_set_menu(GTK_OPTION_MENU(type_menu), menu);
    gtk_option_menu_set_history(GTK_OPTION_MENU(type_menu), 0);
}

void init_categorie_menu(GtkWidget *window) {
    if (!window) return;
    
    GtkWidget *cat_menu = lookup_widget(window, "eyamenucategorie");
    if (!cat_menu) return;
    
    if (!GTK_IS_OPTION_MENU(cat_menu)) return;
    
    GtkWidget *main_menu = gtk_menu_new();
    
    GtkWidget *entrainement_item = gtk_menu_item_new_with_label("ENTRAINEMENT");
    GtkWidget *entrainement_submenu = gtk_menu_new();
    const char *entrainement_items[] = {"MUSCULATION", "CARDIO TRAINING", "CIRCUIT TRAINING"};
    
    for (int i = 0; i < 3; i++) {
        GtkWidget *sub_item = gtk_menu_item_new_with_label(entrainement_items[i]);
        gtk_menu_shell_append(GTK_MENU_SHELL(entrainement_submenu), sub_item);
        gtk_widget_show(sub_item);
        g_signal_connect(G_OBJECT(sub_item), "activate",
                        G_CALLBACK(on_categorie_menu_item_selected), 
                        (gpointer)entrainement_items[i]);
    }
    
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(entrainement_item), entrainement_submenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(main_menu), entrainement_item);
    gtk_widget_show(entrainement_item);
    
    GtkWidget *bienetre_item = gtk_menu_item_new_with_label("BIEN ETRE");
    GtkWidget *bienetre_submenu = gtk_menu_new();
    const char *bienetre_items[] = {"YOGA", "PSTRETCHING", "MEDIATION"};
    
    for (int i = 0; i < 3; i++) {
        GtkWidget *sub_item = gtk_menu_item_new_with_label(bienetre_items[i]);
        gtk_menu_shell_append(GTK_MENU_SHELL(bienetre_submenu), sub_item);
        gtk_widget_show(sub_item);
        g_signal_connect(G_OBJECT(sub_item), "activate",
                        G_CALLBACK(on_categorie_menu_item_selected), 
                        (gpointer)bienetre_items[i]);
    }
    
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(bienetre_item), bienetre_submenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(main_menu), bienetre_item);
    gtk_widget_show(bienetre_item);
    
    GtkWidget *collectes_item = gtk_menu_item_new_with_label("COURS COLLECTES");
    GtkWidget *collectes_submenu = gtk_menu_new();
    const char *collectes_items[] = {"ZUMBA", "BOXE", "CYCLING", "BOOTCAMP", "SEEACE EN GROUPE"};
    
    for (int i = 0; i < 5; i++) {
        GtkWidget *sub_item = gtk_menu_item_new_with_label(collectes_items[i]);
        gtk_menu_shell_append(GTK_MENU_SHELL(collectes_submenu), sub_item);
        gtk_widget_show(sub_item);
        g_signal_connect(G_OBJECT(sub_item), "activate",
                        G_CALLBACK(on_categorie_menu_item_selected), 
                        (gpointer)collectes_items[i]);
    }
    
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(collectes_item), collectes_submenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(main_menu), collectes_item);
    gtk_widget_show(collectes_item);
    
    GtkWidget *coaching_item = gtk_menu_item_new_with_label("COACHING & SUIVIE");
    GtkWidget *coaching_submenu = gtk_menu_new();
    const char *coaching_items[] = {"SEEANCE DECOUVEI", "PLANIFICATION D'O", "COACHING NUTRITI"};
    
    for (int i = 0; i < 3; i++) {
        GtkWidget *sub_item = gtk_menu_item_new_with_label(coaching_items[i]);
        gtk_menu_shell_append(GTK_MENU_SHELL(coaching_submenu), sub_item);
        gtk_widget_show(sub_item);
        g_signal_connect(G_OBJECT(sub_item), "activate",
                        G_CALLBACK(on_categorie_menu_item_selected), 
                        (gpointer)coaching_items[i]);
    }
    
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(coaching_item), coaching_submenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(main_menu), coaching_item);
    gtk_widget_show(coaching_item);
    
    gtk_option_menu_set_menu(GTK_OPTION_MENU(cat_menu), main_menu);
    gtk_option_menu_set_history(GTK_OPTION_MENU(cat_menu), 0);
}

void on_categorie_menu_item_selected(GtkMenuItem *menuitem, gpointer user_data) {
    const char *categorie = (const char*)user_data;
    strcpy(e.categorie, categorie);
}

void on_type_menu_item_selected(GtkMenuItem *menuitem, gpointer user_data) {
    const char *type = (const char*)user_data;
    strcpy(e.type, type);
}

void fix_cours_entry_visibility(GtkWidget *window) {
    GtkWidget *cours_entry = lookup_widget(window, "eyainputcours");
    if (cours_entry && GTK_IS_ENTRY(cours_entry)) {
        gtk_entry_set_visibility(GTK_ENTRY(cours_entry), TRUE);
        gtk_entry_set_invisible_char(GTK_ENTRY(cours_entry), 0);
    }
}

void update_button_states(GtkWidget *window, gboolean has_selection) {
    GtkWidget *modifier_button = lookup_widget(window, "eyabuttonmodifier");
    GtkWidget *delete_button = lookup_widget(window, "eyabuttonsupprimer");
    
    if (selected_cours_id != -1) {
        has_selection = TRUE;
    }
    
    if (modifier_button) {
        gtk_widget_set_sensitive(modifier_button, has_selection);
    }
    
    if (delete_button) {
        gtk_widget_set_sensitive(delete_button, has_selection);
    }
}

void save_cours_to_file(void) {
    FILE *file = fopen("cours.txt", "w");
    if (!file) return;
    
    for (int i = 0; i < cours_count; i++) {
        ajouter_cours("cours.txt", cours_list[i]);
    }
    
    fclose(file);
}

void load_cours_from_file(void) {
    FILE *file = fopen("cours.txt", "r");
    if (!file) return;
    
    cours_count = 0;
    char line[500];
    
    while (fgets(line, sizeof(line), file) && cours_count < 100) {
        line[strcspn(line, "\n")] = 0;
        
        char *token;
        char *tokens[10];
        int token_count = 0;
        
        token = strtok(line, "|");
        while (token && token_count < 10) {
            tokens[token_count++] = token;
            token = strtok(NULL, "|");
        }
        
        if (token_count == 10) {
            cours_list[cours_count].id = atoi(tokens[0]);
            strcpy(cours_list[cours_count].nom_cours, tokens[1]);
            strcpy(cours_list[cours_count].coach, tokens[2]);
            strcpy(cours_list[cours_count].date_heure, tokens[3]);
            strcpy(cours_list[cours_count].lieu, tokens[4]);
            strcpy(cours_list[cours_count].categorie, tokens[5]);
            strcpy(cours_list[cours_count].type, tokens[6]);
            strcpy(cours_list[cours_count].statut, tokens[7]);
            cours_list[cours_count].duree = atoi(tokens[8]);
            cours_list[cours_count].capacite_max = atoi(tokens[9]);
            
            cours_count++;
        }
    }
    
    fclose(file);
}

int save_inscription_to_file(Inscription ins) {
    FILE *file = fopen("inscriptions.txt", "a");
    if (!file) return 0;
    
    fprintf(file, "%d|%d|%s|%s|%s|%s\n",
            ins.member_id,
            ins.course_id,
            ins.member_name,
            ins.course_name,
            ins.date_heure,
            ins.inscription_date);
    
    fclose(file);
    return 1;
}

void load_inscriptions_from_file(Inscription inscriptions[], int *count) {
    FILE *file = fopen("inscriptions.txt", "r");
    if (!file) {
        *count = 0;
        return;
    }
    
    *count = 0;
    char line[500];
    
    while (fgets(line, sizeof(line), file) && *count < 100) {
        line[strcspn(line, "\n")] = 0;
        char *tokens[6];
        int token_count = 0;
        
        tokens[token_count++] = strtok(line, "|");
        while (token_count < 6) {
            tokens[token_count++] = strtok(NULL, "|");
        }
        
        if (token_count == 6) {
            inscriptions[*count].member_id = atoi(tokens[0]);
            inscriptions[*count].course_id = atoi(tokens[1]);
            strcpy(inscriptions[*count].member_name, tokens[2]);
            strcpy(inscriptions[*count].course_name, tokens[3]);
            strcpy(inscriptions[*count].date_heure, tokens[4]);
            strcpy(inscriptions[*count].inscription_date, tokens[5]);
            (*count)++;
        }
    }
    
    fclose(file);
}

int is_member_registered(int member_id, int course_id) {
    Inscription inscriptions[100];
    int inscription_count = 0;
    
    load_inscriptions_from_file(inscriptions, &inscription_count);
    
    for (int i = 0; i < inscription_count; i++) {
        if (inscriptions[i].member_id == member_id && 
            inscriptions[i].course_id == course_id) {
            return 1;
        }
    }
    
    return 0;
}

void init_database(void) {
    load_cours_from_file();
    
    if (cours_count == 0) {
        Cours c1 = {1, "Cardio Training", "Coach Ahmed", "2024-12-10 10:00", "Salle A", "Fitness", "Mixte", "DISPONIBLE", 60, 20};
        Cours c2 = {2, "Yoga", "Coach Fatima", "2024-12-10 14:00", "Salle B", "Bien-être", "Féminin", "DISPONIBLE", 45, 15};
        Cours c3 = {3, "Musculation", "Coach Karim", "2024-12-11 09:00", "Salle C", "Fitness", "Masculin", "DISPONIBLE", 90, 10};

        cours_list[cours_count++] = c1;
        cours_list[cours_count++] = c2;
        cours_list[cours_count++] = c3;
        
        save_cours_to_file();
    }
}

Cours* find_cours_by_id(int id) {
    return trouver_cours_par_id(cours_list, cours_count, id);
}

void remove_cours_by_id(int id) {
    supprimer_cours_de_liste(cours_list, &cours_count, id);
}

void populate_cours_treeview(GtkWidget *treeview) {
    static GtkListStore *store = NULL;
    GtkTreeIter iter;
    
    if (store == NULL) {
        store = gtk_list_store_new(10,
            G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
            G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
            G_TYPE_INT, G_TYPE_INT);
        
        if (gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)) == NULL) {
            const char *titles[] = {"ID", "Cours", "Coach", "Date/Heure", "Lieu", 
                                    "Catégorie", "Type", "Statut", "Durée", "Capacité"};
            GtkCellRenderer *renderer;
            GtkTreeViewColumn *column;
            
            for (int i = 0; i < 10; i++) {
                renderer = gtk_cell_renderer_text_new();
                column = gtk_tree_view_column_new_with_attributes(titles[i], renderer, "text", i, NULL);
                gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
            }
            
            gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        }
    }
 
    gtk_list_store_clear(store);
    
    for (int i = 0; i < cours_count; i++) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
            0, cours_list[i].id,
            1, cours_list[i].nom_cours,
            2, cours_list[i].coach,
            3, cours_list[i].date_heure,
            4, cours_list[i].lieu,
            5, cours_list[i].categorie,
            6, cours_list[i].type,
            7, cours_list[i].statut,
            8, cours_list[i].duree,
            9, cours_list[i].capacite_max,
            -1);
    }
}

gboolean populate_cours_treeview_idle(gpointer data) {
    GtkWidget *treeview = GTK_WIDGET(data);
    populate_cours_treeview(treeview);
    return FALSE;
}

void clear_input_fields(GtkWidget *window) {
    fix_cours_entry_visibility(window);
    GtkWidget *w;
    w = lookup_widget(window, "eyainputid"); gtk_entry_set_text(GTK_ENTRY(w), "");
    w = lookup_widget(window, "eyainputcours"); gtk_entry_set_text(GTK_ENTRY(w), "");
    w = lookup_widget(window, "eyainputcoach"); gtk_entry_set_text(GTK_ENTRY(w), "");
    w = lookup_widget(window, "eyainputdateheure"); gtk_entry_set_text(GTK_ENTRY(w), "");
    w = lookup_widget(window, "eyainputlieu"); gtk_entry_set_text(GTK_ENTRY(w), "");
    w = lookup_widget(window, "eyaspinduree"); gtk_spin_button_set_value(GTK_SPIN_BUTTON(w), 30);
    w = lookup_widget(window, "eyaspincapacite"); gtk_spin_button_set_value(GTK_SPIN_BUTTON(w), 10);
    w = lookup_widget(window, "eyaradiostatutd"); gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(w), TRUE);
    w = lookup_widget(window, "eyaradiostatuta"); gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(w), FALSE);
    gtk_option_menu_set_history(GTK_OPTION_MENU(lookup_widget(window, "eyamenucategorie")), 0);
    gtk_option_menu_set_history(GTK_OPTION_MENU(lookup_widget(window, "eyamenutype")), 0);
    selected_cours_id = -1;
    memset(&e, 0, sizeof(e));
    e.id = -1;
}

void load_cours_to_fields(Cours c, GtkWidget *window) {
    fix_cours_entry_visibility(window);
    char id_str[20];
    sprintf(id_str, "%d", c.id);
    GtkWidget *w;
    w = lookup_widget(window, "eyainputid"); gtk_entry_set_text(GTK_ENTRY(w), id_str);
    w = lookup_widget(window, "eyainputcours"); gtk_entry_set_text(GTK_ENTRY(w), c.nom_cours);
    w = lookup_widget(window, "eyainputcoach"); gtk_entry_set_text(GTK_ENTRY(w), c.coach);
    w = lookup_widget(window, "eyainputdateheure"); gtk_entry_set_text(GTK_ENTRY(w), c.date_heure);
    w = lookup_widget(window, "eyainputlieu"); gtk_entry_set_text(GTK_ENTRY(w), c.lieu);
    w = lookup_widget(window, "eyaspinduree"); gtk_spin_button_set_value(GTK_SPIN_BUTTON(w), c.duree);
    w = lookup_widget(window, "eyaspincapacite"); gtk_spin_button_set_value(GTK_SPIN_BUTTON(w), c.capacite_max);
    if (strcmp(c.statut, "ANNULÉ") == 0) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(lookup_widget(window, "eyaradiostatuta")), TRUE);
    } else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(lookup_widget(window, "eyaradiostatutd")), TRUE);
    }
    set_option_menu_by_text(lookup_widget(window, "eyamenucategorie"), c.categorie);
    set_option_menu_by_text(lookup_widget(window, "eyamenutype"), c.type);
    e = c;
    selected_cours_id = c.id;
}

void on_eyabuttonajout_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "ADMINISTRATION");
    if (!window) return;
    
    GtkWidget *id_entry = lookup_widget(window, "eyainputid");
    GtkWidget *nom_entry = lookup_widget(window, "eyainputcours");
    
    if (!id_entry || !nom_entry) return;
    
    const gchar *id_text = gtk_entry_get_text(GTK_ENTRY(id_entry));
    const gchar *nom = gtk_entry_get_text(GTK_ENTRY(nom_entry));
    
    if (strlen(id_text) == 0 || strlen(nom) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez remplir l'ID et le nom du cours!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    int id = atoi(id_text);
    Cours *existing = find_cours_by_id(id);
    if (existing) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Un cours avec l'ID %d existe déjà!", id);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    Cours new_cours;
    memset(&new_cours, 0, sizeof(Cours));
    
    new_cours.id = id;
    strncpy(new_cours.nom_cours, nom, sizeof(new_cours.nom_cours) - 1);
    
    GtkWidget *coach_entry = lookup_widget(window, "eyainputcoach");
    GtkWidget *date_entry = lookup_widget(window, "eyainputdateheure");
    GtkWidget *lieu_entry = lookup_widget(window, "eyainputlieu");
    
    if (coach_entry) {
        const gchar *coach = gtk_entry_get_text(GTK_ENTRY(coach_entry));
        strncpy(new_cours.coach, coach ? coach : "", sizeof(new_cours.coach) - 1);
    }
    
    if (date_entry) {
        const gchar *date = gtk_entry_get_text(GTK_ENTRY(date_entry));
        strncpy(new_cours.date_heure, date ? date : "", sizeof(new_cours.date_heure) - 1);
    }
    
    if (lieu_entry) {
        const gchar *lieu = gtk_entry_get_text(GTK_ENTRY(lieu_entry));
        strncpy(new_cours.lieu, lieu ? lieu : "", sizeof(new_cours.lieu) - 1);
    }
    
    GtkWidget *radio_annule = lookup_widget(window, "eyaradiostatuta");
    if (radio_annule && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_annule))) {
        strcpy(new_cours.statut, "ANNULÉ");
    } else {
        strcpy(new_cours.statut, "DISPONIBLE");
    }
    
    GtkWidget *spin_duree = lookup_widget(window, "eyaspinduree");
    GtkWidget *spin_capacite = lookup_widget(window, "eyaspincapacite");
    
    if (spin_duree) {
        new_cours.duree = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_duree));
    } else {
        new_cours.duree = 60;
    }
    
    if (spin_capacite) {
        new_cours.capacite_max = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_capacite));
    } else {
        new_cours.capacite_max = 10;
    }
    
    if (strlen(e.categorie) > 0) {
        strncpy(new_cours.categorie, e.categorie, sizeof(new_cours.categorie) - 1);
    } else {
        GtkWidget *cat_menu = lookup_widget(window, "eyamenucategorie");
        if (cat_menu) {
            gchar *cat_text = get_option_menu_text(cat_menu);
            if (cat_text) {
                strncpy(new_cours.categorie, cat_text, sizeof(new_cours.categorie) - 1);
                g_free(cat_text);
            } else {
                strcpy(new_cours.categorie, "ENTRAINEMENT");
            }
        } else {
            strcpy(new_cours.categorie, "ENTRAINEMENT");
        }
    }
    
    if (strlen(e.type) > 0) {
        strncpy(new_cours.type, e.type, sizeof(new_cours.type) - 1);
    } else {
        GtkWidget *type_menu = lookup_widget(window, "eyamenutype");
        if (type_menu) {
            gchar *type_text = get_option_menu_text(type_menu);
            if (type_text) {
                strncpy(new_cours.type, type_text, sizeof(new_cours.type) - 1);
                g_free(type_text);
            } else {
                strcpy(new_cours.type, "Mixte");
            }
        } else {
            strcpy(new_cours.type, "Mixte");
        }
    }
    
    if (ajouter_cours_a_liste(cours_list, &cours_count, new_cours, 100)) {
        ajouter_cours("cours.txt", new_cours);
        
        GtkWidget *treeview = lookup_widget(window, "eyatreeview");
        if (treeview) {
            populate_cours_treeview(treeview);
            g_idle_add((GSourceFunc)populate_cours_treeview_idle, treeview);
        }
        
        clear_input_fields(window);
        update_button_states(window, FALSE);
        
        GtkWidget *success_dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Cours '%s' (ID: %d) ajouté avec succès!",
            new_cours.nom_cours, new_cours.id);
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
        
    } else {
        GtkWidget *error_dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Erreur: Impossible d'ajouter le cours!");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
}

void on_eyabuttonmodifier_clicked(GtkButton *button, gpointer user_data) {
    if (selected_cours_id == -1) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez d'abord sélectionner un cours à modifier!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "ADMINISTRATION");
    Cours *c = find_cours_by_id(selected_cours_id);
    
    if (!c) return;
    
    strcpy(c->nom_cours, gtk_entry_get_text(GTK_ENTRY(lookup_widget(window, "eyainputcours"))));
    strcpy(c->coach, gtk_entry_get_text(GTK_ENTRY(lookup_widget(window, "eyainputcoach"))));
    strcpy(c->date_heure, gtk_entry_get_text(GTK_ENTRY(lookup_widget(window, "eyainputdateheure"))));
    strcpy(c->lieu, gtk_entry_get_text(GTK_ENTRY(lookup_widget(window, "eyainputlieu"))));
    strcpy(c->statut, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lookup_widget(window, "eyaradiostatuta"))) ? "ANNULÉ" : "DISPONIBLE");
    c->duree = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(lookup_widget(window, "eyaspinduree")));
    c->capacite_max = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(lookup_widget(window, "eyaspincapacite")));
    
    if (e.categorie[0]) strcpy(c->categorie, e.categorie);
    if (e.type[0]) strcpy(c->type, e.type);
    
    modifier_cours("cours.txt", selected_cours_id, *c);
    
    GtkWidget *treeview = lookup_widget(window, "eyatreeview");
    if (treeview) {
        g_idle_add((GSourceFunc)populate_cours_treeview_idle, treeview);
    }
    
    clear_input_fields(window);
    update_button_states(window, FALSE);
}

void on_eyabuttonsupprimer_clicked(GtkButton *button, gpointer user_data) {
    if (selected_cours_id == -1) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez d'abord sélectionner un cours à supprimer!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    Cours *c = find_cours_by_id(selected_cours_id);
    if (!c) return;
    
    GtkWidget *confirm_dialog = gtk_message_dialog_new(NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Êtes-vous sûr de vouloir supprimer le cours '%s' (ID: %d)?",
        c->nom_cours, selected_cours_id);
    
    gint response = gtk_dialog_run(GTK_DIALOG(confirm_dialog));
    gtk_widget_destroy(confirm_dialog);
    
    if (response == GTK_RESPONSE_YES) {
        int id_to_remove = selected_cours_id;
        
        supprimer_cours("cours.txt", id_to_remove);
        remove_cours_by_id(id_to_remove);
        
        GtkWidget *window = lookup_widget(GTK_WIDGET(button), "ADMINISTRATION");
        
        GtkWidget *treeview = lookup_widget(window, "eyatreeview");
        if (treeview) {
            g_idle_add((GSourceFunc)populate_cours_treeview_idle, treeview);
        }
        
        clear_input_fields(window);
        update_button_states(window, FALSE);
        
        GtkWidget *success_dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Cours supprimé avec succès!");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
    }
}

void on_eyabuttonrech_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "ADMINISTRATION");
    const gchar *id_text = gtk_entry_get_text(GTK_ENTRY(lookup_widget(window, "eyainputrech")));
    
    if (strlen(id_text) == 0) {
        GtkWidget *treeview = lookup_widget(window, "eyatreeview");
        if (treeview) populate_cours_treeview(treeview);
        
        GtkWidget *rech_entry = lookup_widget(window, "eyainputrech");
        if (rech_entry) gtk_entry_set_text(GTK_ENTRY(rech_entry), "");
        
        update_button_states(window, FALSE);
        return;
    }
    
    int search_id = atoi(id_text);
    Cours *c = find_cours_by_id(search_id);
    
    if (c) {
        load_cours_to_fields(*c, window);
        
        GtkWidget *treeview = lookup_widget(window, "eyatreeview");
        if (treeview) {
            GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
            if (model && GTK_IS_LIST_STORE(model)) {
                GtkListStore *store = GTK_LIST_STORE(model);
                gtk_list_store_clear(store);
                
                GtkTreeIter iter;
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                    0, c->id,
                    1, c->nom_cours,
                    2, c->coach,
                    3, c->date_heure,
                    4, c->lieu,
                    5, c->categorie,
                    6, c->type,
                    7, c->statut,
                    8, c->duree,
                    9, c->capacite_max,
                    -1);
            }
        }
        
        update_button_states(window, TRUE);
        
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Cours avec ID %d non trouvé!", search_id);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        
        GtkWidget *rech_entry = lookup_widget(window, "eyainputrech");
        if (rech_entry) gtk_entry_set_text(GTK_ENTRY(rech_entry), "");
        
        update_button_states(window, FALSE);
        
        GtkWidget *treeview = lookup_widget(window, "eyatreeview");
        if (treeview) populate_cours_treeview(treeview);
    }
}

void on_eyatreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path,
                                  GtkTreeViewColumn *column, gpointer user_data) {
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    
    if (model == NULL) return;
    
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        int id;
        gtk_tree_model_get(model, &iter, 0, &id, -1);
        
        Cours *c = find_cours_by_id(id);
        if (c) {
            GtkWidget *window = NULL;
            window = lookup_widget(GTK_WIDGET(treeview), "ADMINISTRATION");
            if (!window) window = gtk_widget_get_toplevel(GTK_WIDGET(treeview));
            
            if (window) {
                load_cours_to_fields(*c, window);
                selected_cours_id = c->id;
                update_button_states(window, TRUE);
            }
        }
    }
}

void on_eyaactualiser_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "ADMINISTRATION");
    if (!window) return;
    GtkWidget *treeview = lookup_widget(window, "eyatreeview");
    if (!treeview) return;
    
    g_idle_add((GSourceFunc)populate_cours_treeview_idle, treeview);
}

char* my_strcasestr(const char *haystack, const char *needle) {
    if (!*needle) return (char*)haystack;
    
    for (; *haystack; haystack++) {
        if (tolower((unsigned char)*haystack) == tolower((unsigned char)*needle)) {
            const char *h = haystack;
            const char *n = needle;
            
            while (*h && *n && tolower((unsigned char)*h) == tolower((unsigned char)*n)) {
                h++;
                n++;
            }
            
            if (!*n) return (char*)haystack;
        }
    }
    return NULL;
}

void unselect_all_type_radios(GtkWidget *window) {
    GtkWidget *radio_m = lookup_widget(window, "eyaradiotypem");
    GtkWidget *radio_f = lookup_widget(window, "eyaradiotypef");
    GtkWidget *radio_h = lookup_widget(window, "eyaradiotypeh");
    
    if (radio_m) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_m), FALSE);
    if (radio_f) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_f), FALSE);
    if (radio_h) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_h), FALSE);
}

void populate_member_treeview(GtkWidget *treeview) {
    GtkListStore *store = gtk_list_store_new(6,
        G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
        G_TYPE_STRING, G_TYPE_STRING);
    
    gtk_list_store_clear(store);
    
    for (int i = 0; i < filtered_count; i++) {
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
            0, filtered_cours_list[i].id,
            1, filtered_cours_list[i].nom_cours,
            2, filtered_cours_list[i].date_heure,
            3, filtered_cours_list[i].type,
            4, filtered_cours_list[i].coach,
            5, filtered_cours_list[i].lieu,
            -1);
    }
    
    GtkTreeModel *current_model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    if (!current_model) {
        GList *columns = gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview));
        while (columns) {
            gtk_tree_view_remove_column(GTK_TREE_VIEW(treeview), 
                                       (GtkTreeViewColumn*)columns->data);
            columns = g_list_next(columns);
        }
        
        const char *titles[] = {"Cours", "Date/Heure", "Type", "Coach", "Lieu"};
        for (int i = 0; i < 5; i++) {
            GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
            GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
                titles[i], renderer, "text", i + 1, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        }
        
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    } else {
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    }
    
    g_object_unref(store);
}

void init_member_window(GtkWidget *window) {
    filtered_count = 0;
    for (int i = 0; i < cours_count; i++) {
        if (strcmp(cours_list[i].statut, "DISPONIBLE") == 0) {
            filtered_cours_list[filtered_count] = cours_list[i];
            filtered_count++;
        }
    }
    
    GtkWidget *treeview = lookup_widget(window, "eyatreeview");
    if (treeview) {
        populate_member_treeview(treeview);
        
        GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
        if (selection) {
            g_signal_connect(selection, "changed", 
                           G_CALLBACK(on_member_treeview_selection_changed), 
                           window);
            gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);
            gtk_tree_selection_unselect_all(selection);
        }
        
        GtkWidget *inscrire_button = lookup_widget(window, "eyabuttoncours");
        if (inscrire_button) gtk_widget_set_sensitive(inscrire_button, FALSE);
    }
}

void reset_member_filters(GtkWidget *window) {
    GtkWidget *nom_entry = lookup_widget(window, "eyainputrech");
    if (nom_entry && GTK_IS_ENTRY(nom_entry)) {
        gtk_entry_set_text(GTK_ENTRY(nom_entry), "");
    }
    
    GtkWidget *spin_jour = lookup_widget(window, "eyaspinjour");
    GtkWidget *spin_mois = lookup_widget(window, "eyaspinmois");
    GtkWidget *spin_annee = lookup_widget(window, "eyaspinanee");
    
    if (spin_jour) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_jour), 1);
    if (spin_mois) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mois), 1);
    if (spin_annee) gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_annee), 2024);
    
    unselect_all_type_radios(window);
}

void on_member_clear_filters_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "MEMBRE");
    if (!window) return;
    
    reset_member_filters(window);
    
    filtered_count = 0;
    for (int i = 0; i < cours_count; i++) {
        if (strcmp(cours_list[i].statut, "DISPONIBLE") == 0) {
            filtered_cours_list[filtered_count] = cours_list[i];
            filtered_count++;
        }
    }
    
    GtkWidget *treeview = lookup_widget(window, "eyatreeview");
    if (treeview) populate_member_treeview(treeview);
}

void on_member_recherche_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "MEMBRE");
    if (!window) return;
    
    const gchar *nom_cours = gtk_entry_get_text(GTK_ENTRY(lookup_widget(window, "eyainputrech")));
    
    GtkWidget *spin_jour = lookup_widget(window, "eyaspinjour");
    GtkWidget *spin_mois = lookup_widget(window, "eyaspinmois");
    GtkWidget *spin_annee = lookup_widget(window, "eyaspinanee");
    
    char jour_str[10] = "", mois_str[10] = "", annee_str[10] = "";
    char date_search[20] = "";
    
    if (spin_jour && GTK_IS_SPIN_BUTTON(spin_jour)) {
        int jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour));
        sprintf(jour_str, "%02d", jour);
    }
    
    if (spin_mois && GTK_IS_SPIN_BUTTON(spin_mois)) {
        int mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois));
        sprintf(mois_str, "%02d", mois);
    }
    
    if (spin_annee && GTK_IS_SPIN_BUTTON(spin_annee)) {
        int annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee));
        sprintf(annee_str, "%04d", annee);
    }
    
    if (strlen(annee_str) > 0 && strlen(mois_str) > 0 && strlen(jour_str) > 0) {
        sprintf(date_search, "%s-%s-%s", annee_str, mois_str, jour_str);
    } else {
        date_search[0] = '\0';
    }
    
    gchar *type = NULL;
    GtkWidget *radio_m = lookup_widget(window, "eyaradiotypem");
    GtkWidget *radio_f = lookup_widget(window, "eyaradiotypef");
    GtkWidget *radio_h = lookup_widget(window, "eyaradiotypeh");
    
    if (radio_m && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_m))) {
        type = "Mixte";
    } else if (radio_f && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_f))) {
        type = "Féminin";
    } else if (radio_h && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_h))) {
        type = "Masculin";
    }
    
    gboolean any_filter_active = 
        (nom_cours && nom_cours[0] != '\0') || 
        (date_search[0] != '\0') || 
        (type && type[0] != '\0');
    
    filtered_count = 0;
    
    if (!any_filter_active) {
        for (int i = 0; i < cours_count; i++) {
            if (strcmp(cours_list[i].statut, "DISPONIBLE") == 0) {
                filtered_cours_list[filtered_count] = cours_list[i];
                filtered_count++;
            }
        }
    } else {
        for (int i = 0; i < cours_count; i++) {
            int match = 1;
            
            if (strcmp(cours_list[i].statut, "DISPONIBLE") != 0) continue;
            
            if (nom_cours && nom_cours[0] != '\0') {
                if (my_strcasestr(cours_list[i].nom_cours, nom_cours) == NULL) match = 0;
            }
            
            if (date_search[0] != '\0') {
                if (strstr(cours_list[i].date_heure, date_search) == NULL) match = 0;
            }
            
            if (type && type[0] != '\0') {
                if (strcmp(cours_list[i].type, type) != 0) match = 0;
            }
            
            if (match) {
                filtered_cours_list[filtered_count] = cours_list[i];
                filtered_count++;
            }
        }
    }
    
    GtkWidget *treeview = lookup_widget(window, "eyatreeview");
    if (treeview) {
        populate_member_treeview(treeview);
        
        if (filtered_count == 0 && any_filter_active) {
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_INFO,
                GTK_BUTTONS_OK,
                "Aucun cours disponible avec les critères sélectionnés.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            
            filtered_count = 0;
            for (int i = 0; i < cours_count; i++) {
                if (strcmp(cours_list[i].statut, "DISPONIBLE") == 0) {
                    filtered_cours_list[filtered_count] = cours_list[i];
                    filtered_count++;
                }
            }
            populate_member_treeview(treeview);
        }
    }
    
    reset_member_filters(window);
}

void on_member_treeview_row_activated(GtkTreeView *treeview, GtkTreePath *path,
                                      GtkTreeViewColumn *column, gpointer user_data) {
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    
    if (model == NULL) return;
    
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        int id;
        gtk_tree_model_get(model, &iter, 0, &id, -1);
        
        selected_member_cours_id = id;
        
        GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
        if (selection) gtk_tree_selection_select_iter(selection, &iter);
    }
}

void on_member_treeview_selection_changed(GtkTreeSelection *selection, gpointer user_data) {
    GtkTreeIter iter;
    GtkTreeModel *model;
    
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        int id;
        gtk_tree_model_get(model, &iter, 0, &id, -1);
        
        if (id > 0 && id < 10000) {
            selected_member_cours_id = id;
        } else {
            selected_member_cours_id = -1;
        }
        
        GtkWidget *window = GTK_WIDGET(user_data);
        if (window && selected_member_cours_id != -1) {
            GtkWidget *inscrire_button = lookup_widget(window, "eyabuttoncours");
            if (inscrire_button) gtk_widget_set_sensitive(inscrire_button, TRUE);
        }
        
    } else {
        selected_member_cours_id = -1;
        
        GtkWidget *window = GTK_WIDGET(user_data);
        if (window) {
            GtkWidget *inscrire_button = lookup_widget(window, "eyabuttoncours");
            if (inscrire_button) gtk_widget_set_sensitive(inscrire_button, FALSE);
        }
    }
}

void on_eyabuttoncours_clicked(GtkButton *button, gpointer user_data) {
    if (selected_member_cours_id == -1) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Veuillez d'abord sélectionner un cours dans la liste!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    Cours *c = find_cours_by_id(selected_member_cours_id);
    if (!c) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Cours avec ID %d non trouvé!", selected_member_cours_id);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    if (strcmp(c->statut, "DISPONIBLE") != 0) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Ce cours n'est pas disponible pour l'inscription!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    int member_id = 1;
    char member_name[] = "Membre Test";
    
    if (is_member_registered(member_id, c->id)) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Vous êtes déjà inscrit à ce cours!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    GtkWidget *confirm_dialog = gtk_message_dialog_new(NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Voulez-vous vous inscrire au cours '%s' (ID: %d)?\nDate: %s\nCoach: %s",
        c->nom_cours, c->id, c->date_heure, c->coach);
    
    gint response = gtk_dialog_run(GTK_DIALOG(confirm_dialog));
    gtk_widget_destroy(confirm_dialog);
    
    if (response == GTK_RESPONSE_YES) {
        Inscription inscription;
        inscription.member_id = member_id;
        inscription.course_id = c->id;
        strcpy(inscription.member_name, member_name);
        strcpy(inscription.course_name, c->nom_cours);
        strcpy(inscription.date_heure, c->date_heure);
        
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        sprintf(inscription.inscription_date, "%04d-%02d-%02d %02d:%02d:%02d",
                tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                tm.tm_hour, tm.tm_min, tm.tm_sec);
        
        if (save_inscription_to_file(inscription)) {
            if (c->capacite_max > 0) {
                c->capacite_max--;
                if (c->capacite_max == 0) strcpy(c->statut, "COMPLET");
                save_cours_to_file();
            }
            
            GtkWidget *success_dialog = gtk_message_dialog_new(NULL,
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_INFO,
                GTK_BUTTONS_OK,
                "Inscription réussie au cours '%s'!\n"
                "Vous recevrez une confirmation par email.\n"
                "Date d'inscription: %s",
                c->nom_cours, inscription.inscription_date);
            gtk_dialog_run(GTK_DIALOG(success_dialog));
            gtk_widget_destroy(success_dialog);
            
        } else {
            GtkWidget *error_dialog = gtk_message_dialog_new(NULL,
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_ERROR,
                GTK_BUTTONS_OK,
                "Erreur lors de l'inscription. Veuillez réessayer.");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
        }
        
        GtkWidget *window = lookup_widget(GTK_WIDGET(button), "MEMBRE");
        if (window) on_member_clear_filters_clicked(button, user_data);
    }
}

void on_eyaspinjour_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(spinbutton));
    GtkWidget *rech_button = lookup_widget(window, "eyabuttonrech");
    if (rech_button) on_member_recherche_clicked(GTK_BUTTON(rech_button), NULL);
}

void on_eyaspinmois_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(spinbutton));
    GtkWidget *rech_button = lookup_widget(window, "eyabuttonrech");
    if (rech_button) on_member_recherche_clicked(GTK_BUTTON(rech_button), NULL);
}

void on_eyaspinanee_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(spinbutton));
    GtkWidget *rech_button = lookup_widget(window, "eyabuttonrech");
    if (rech_button) on_member_recherche_clicked(GTK_BUTTON(rech_button), NULL);
}

void on_eyaradiotypem_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(togglebutton));
        GtkWidget *rech_button = lookup_widget(window, "eyabuttonrech");
        if (rech_button) on_member_recherche_clicked(GTK_BUTTON(rech_button), NULL);
    }
}

void on_eyaradiotypef_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(togglebutton));
        GtkWidget *rech_button = lookup_widget(window, "eyabuttonrech");
        if (rech_button) on_member_recherche_clicked(GTK_BUTTON(rech_button), NULL);
    }
}

void on_eyaradiotypeh_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(togglebutton));
        GtkWidget *rech_button = lookup_widget(window, "eyabuttonrech");
        if (rech_button) on_member_recherche_clicked(GTK_BUTTON(rech_button), NULL);
    }
}

void on_entrainement2_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "ENTRAINEMENT"); 
}

void on_musculation1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "MUSCULATION"); 
}

void on_cardio_training1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "CARDIO TRAINING");
}

void on_cross_training1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "CROSS TRAINING");
}

void on_circuit_training1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "CIRCUIT TRAINING");
}

void on_bien_etre1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "BIEN ETRE");
}

void on_yoga1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "YOGA"); 
}

void on_pstretching1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "PSTRETCHING"); 
}

void on_meditation1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "MEDIATION");
}

void on_cours_collectifs2_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "COURS COLLECTES");
}

void on_zumba1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "ZUMBA"); 
}

void on_boxe1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "BOXE"); 
}

void on_cycling1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "CYCLING"); 
}

void on_bootcamp1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "BOOTCAMP"); 
}

void on_seance_en_groupe1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "SEEACE EN GROUPE");
}

void on_coaching___suivi2_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "COACHING & SUIVIE");
}

void on_seance_decouverte1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "SEEANCE DECOUVEI");
}

void on_planification_d_objectifs1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "PLANIFICATION D'O");
}

void on_coaching_nutritionnel1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "COACHING NUTRITI");
}

void on_feminin1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.type, "Féminin"); 
}

void on_masculin1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.type, "Masculin"); 
}

void on_mixte1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.type, "Mixte"); 
}

void on_musculation2_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "MUSCULATION"); 
}

void on_cardio_training2_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "CARDIO TRAINING"); 
}

void on_circuit_training2_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "CIRCUIT TRAINING"); 
}

void on_yoga2_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "YOGA"); 
}

void on_pstretching2_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "PSTRETCHING"); 
}

void on_mediation1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "MEDIATION"); 
}

void on_zumba2_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "ZUMBA"); 
}

void on_boxe2_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "BOXE"); 
}

void on_cycling2_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "CYCLING"); 
}

void on_bootcamp4_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "BOOTCAMP"); 
}

void on_sceace_en_groupe1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "SEEACE EN GROUPE"); 
}

void on_sceance_decouverte1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "SEEANCE DECOUVEI"); 
}

void on_planification_d_objet1_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "PLANIFICATION D'O"); 
}

void on_coaching_nutritionnel2_activate(GtkMenuItem *menuitem, gpointer user_data) { 
    strcpy(e.categorie, "COACHING NUTRITI"); 
}

void on_jour3_activate(GtkMenuItem *menuitem, gpointer user_data) { }

void on_jour2_activate(GtkMenuItem *menuitem, gpointer user_data) { }

void on_item1_activate(GtkMenuItem *menuitem, gpointer user_data) { }

void on_horaire1_activate(GtkMenuItem *menuitem, gpointer user_data) { }

void on_eyaradiostatutd_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) strcpy(e.statut, "DISPONIBLE");
}

void on_eyaradiostatuta_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) strcpy(e.statut, "ANNULÉ");
}

void on_dhiatreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path,
                                  GtkTreeViewColumn *column, gpointer user_data) { }

void on_dhiabuttonrech_clicked(GtkButton *button, gpointer user_data) { }

void on_dhiabuttonaffilations_clicked(GtkButton *button, gpointer user_data) { }

void on_dec7_clicked(GtkButton *button, gpointer user_data) { }

void on_dec8_clicked(GtkButton *button, gpointer user_data) { }

void on_chihebtreeview_row_activated2(GtkTreeView *treeview, GtkTreePath *path,
                                     GtkTreeViewColumn *column, gpointer user_data) { }

void on_chihebcheckniveauxi_toggled(GtkToggleButton *togglebutton, gpointer user_data) { }

void on_chihebcheckniveauxa_toggled(GtkToggleButton *togglebutton, gpointer user_data) { }

void on_chihebbuttonevenements_clicked(GtkButton *button, gpointer user_data) { }

void on_chihebcheckniveauxd_toggled(GtkToggleButton *togglebutton, gpointer user_data) { }

void on_chihebbuttonrech_clicked(GtkButton *button, gpointer user_data) { }

void on_chihebradiotarifg_toggled(GtkToggleButton *togglebutton, gpointer user_data) { }

void on_chihebradiotarifp_toggled(GtkToggleButton *togglebutton, gpointer user_data) { }

void on_dec9_clicked(GtkButton *button, gpointer user_data) { }

void on_ghbuttoninscription_clicked(GtkButton *button, gpointer user_data) { }

void on_dec10_clicked(GtkButton *button, gpointer user_data) { }

void on_talelspinnombre_value_changed(GtkSpinButton *spinbutton, gpointer user_data) { }

void on_talelspinjour1_value_changed(GtkSpinButton *spinbutton, gpointer user_data) { }

void on_talelspinmois1_value_changed(GtkSpinButton *spinbutton, gpointer user_data) { }

void on_talelspinannee1_value_changed(GtkSpinButton *spinbutton, gpointer user_data) { }

void on_talelbuttonequipement_clicked(GtkButton *button, gpointer user_data) { }

void on_talelbuttonrech1_clicked(GtkButton *button, gpointer user_data) { }

void on_dec11_clicked(GtkButton *button, gpointer user_data) { }

void on_ranatreeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path,
                                   GtkTreeViewColumn *column, gpointer user_data) { }

void on_ranabuttonrech1_clicked(GtkButton *button, gpointer user_data) { }

void on_ranabuttoncentres_clicked(GtkButton *button, gpointer user_data) { }

void on_dec12_clicked(GtkButton *button, gpointer user_data) { }

void on_dhiabuttonajout_clicked(GtkButton *button, gpointer user_data) { }

void on_dec1_clicked(GtkButton *button, gpointer user_data) { }

void on_button1_clicked(GtkButton *button, gpointer user_data) { }

void on_button2_clicked(GtkButton *button, gpointer user_data) { }

void on_ghbouttonsupprimer_clicked(GtkButton *button, gpointer user_data) { }

void on_dec2_clicked(GtkButton *button, gpointer user_data) { }

void on_8h___1_activate(GtkMenuItem *menuitem, gpointer user_data) { }

void on_10h___12h1_activate(GtkMenuItem *menuitem, gpointer user_data) { }

void on_14h___16h1_activate(GtkMenuItem *menuitem, gpointer user_data) { }

void on_16___18h1_activate(GtkMenuItem *menuitem, gpointer user_data) { }

void on_dec3_clicked(GtkButton *button, gpointer user_data) { }

void on_talelspindispo_value_changed(GtkSpinButton *spinbutton, gpointer user_data) { }

void on_talelspinjour_value_changed(GtkSpinButton *spinbutton, gpointer user_data) { }

void on_talelspinmois_value_changed(GtkSpinButton *spinbutton, gpointer user_data) { }

void on_talelspinannee_value_changed(GtkSpinButton *spinbutton, gpointer user_data) { }

void on_talelbuttonmod_clicked(GtkButton *button, gpointer user_data) { }

void on_talelbuttonsupp_clicked(GtkButton *button, gpointer user_data) { }

void on_dec4_clicked(GtkButton *button, gpointer user_data) { }

void on_talelmenucategorie_changed(GtkWidget *widget, gpointer user_data) { }

void on_talelradioetatd_toggled(GtkToggleButton *togglebutton, gpointer user_data) { }

void on_talelradioetatn_toggled(GtkToggleButton *togglebutton, gpointer user_data) { }

void on_talelbuttonajout_clicked(GtkButton *button, gpointer user_data) { }

void on_ranaspincapacite_changed(GtkWidget *widget, gpointer user_data) { }

void on_ranatreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path,
                                  GtkTreeViewColumn *column, gpointer user_data) { }

void on_ranabuttonrech_clicked(GtkButton *button, gpointer user_data) { }

void on_ranabouttonmod_clicked(GtkButton *button, gpointer user_data) { }

void on_ranabouttonsup_clicked(GtkButton *button, gpointer user_data) { }

void on_ranabuttonajout_clicked(GtkButton *button, gpointer user_data) { }

void on_dec5_clicked(GtkButton *button, gpointer user_data) { }

void on_ranaradioproprieteei_toggled(GtkToggleButton *togglebutton, gpointer user_data) { }

void on_ranaradioproprieteep_toggled(GtkToggleButton *togglebutton, gpointer user_data) { }

void on_calendar2_day_selected(GtkCalendar *calendar, gpointer user_data) { }

void on_chihebtreeview_row_activated(GtkTreeView *treeview, GtkTreePath *path,
                                    GtkTreeViewColumn *column, gpointer user_data) { }

void on_chihebbuttonrecherche_clicked(GtkButton *button, gpointer user_data) { }

void on_chihebcheckniveauavance_toggled(GtkToggleButton *togglebutton, gpointer user_data) { }

void on_chihebbuttonajout_clicked(GtkButton *button, gpointer user_data) { }

void on_chihebbuttonmodifier_clicked(GtkButton *button, gpointer user_data) { }

void on_chihebbuttonsupprimer_clicked(GtkButton *button, gpointer user_data) { }

void on_chihebcheckniveaudebutant_toggled(GtkToggleButton *togglebutton, gpointer user_data) { }

void on_chihebcheckniveauinter_toggled(GtkToggleButton *togglebutton, gpointer user_data) { }

void on_dec6_clicked(GtkButton *button, gpointer user_data) { }

void on_loginbuttonlogin_clicked(GtkButton *button, gpointer user_data) { }
