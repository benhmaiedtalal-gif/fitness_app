#include <gtk/gtk.h>
#include <stdio.h>
#include "callbacks.h"
#include "cours.h"    
#include "interface.h"
#include "support.h"

Cours cours_list[100];
int cours_count = 0;

Cours e;
int selected_cours_id = -1;

Cours filtered_cours_list[100];
int filtered_count = 0;
int selected_member_cours_id = -1;

void check_signal_connections(GtkWidget *window) {
    GtkWidget *ajout_button = lookup_widget(window, "eyabuttonajout");
    if (ajout_button) {
        g_signal_connect(ajout_button, "clicked",
                        G_CALLBACK(on_eyabuttonajout_clicked), NULL);
    }
}

gboolean init_treeview_idle(gpointer data) {
    GtkWidget *treeview = GTK_WIDGET(data);
    populate_cours_treeview(treeview);
    return FALSE;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *ADMINISTRATION = create_ADMINISTRATION();
    GtkWidget *MEMBRE = create_MEMBRE();
    
    GtkWidget *cours_entry = lookup_widget(ADMINISTRATION, "eyainputcours");
    if (cours_entry && GTK_IS_ENTRY(cours_entry)) {
        gtk_entry_set_visibility(GTK_ENTRY(cours_entry), TRUE);
        gtk_entry_set_invisible_char(GTK_ENTRY(cours_entry), 0);
    }
    
    const char *other_entries[] = {
        "eyainputid", "eyainputcoach", 
        "eyainputdateheure", "eyainputlieu", "eyainputrech",
        NULL
    };
    
    for (int i = 0; other_entries[i]; i++) {
        GtkWidget *entry = lookup_widget(ADMINISTRATION, other_entries[i]);
        if (entry && GTK_IS_ENTRY(entry)) {
            gtk_entry_set_visibility(GTK_ENTRY(entry), TRUE);
            gtk_entry_set_invisible_char(GTK_ENTRY(entry), 0);
        }
    }
    
    gtk_widget_show_all(ADMINISTRATION);
    gtk_widget_show_all(MEMBRE);
    
    if (GTK_IS_WINDOW(ADMINISTRATION)) {
        gtk_window_move(GTK_WINDOW(ADMINISTRATION), 50, 50);
    }
    if (GTK_IS_WINDOW(MEMBRE)) {
        gtk_window_move(GTK_WINDOW(MEMBRE), 700, 50);
    }

    init_database();
    
    if (ADMINISTRATION) {
        check_signal_connections(ADMINISTRATION);  // IMPORTANT: This connects the Ajouter button
        init_type_menu(ADMINISTRATION);
        init_categorie_menu(ADMINISTRATION);
    }

    GtkWidget *notebook = lookup_widget(ADMINISTRATION, "notebook1");
    if (notebook) {
        gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 5);
    }
    
    GtkWidget *treeview = lookup_widget(ADMINISTRATION, "eyatreeview");
    if (treeview) {
        g_signal_connect(treeview, "row-activated",
                       G_CALLBACK(on_eyatreeview_row_activated), NULL);
        
        g_idle_add((GSourceFunc)init_treeview_idle, treeview);
    }
    
    update_button_states(ADMINISTRATION, FALSE);
    
    GtkWidget *rech_button = lookup_widget(ADMINISTRATION, "eyabuttonrech");
    if (rech_button) {
        g_signal_connect(rech_button, "clicked", 
                       G_CALLBACK(on_eyabuttonrech_clicked), NULL);
    }

    if (MEMBRE) {
        init_member_window(MEMBRE);
        
        GtkWidget *member_rech_button = lookup_widget(MEMBRE, "eyabuttonrech");
        if (member_rech_button) {
            g_signal_connect(member_rech_button, "clicked",
                           G_CALLBACK(on_member_recherche_clicked), NULL);
        }
        
        GtkWidget *member_treeview = lookup_widget(MEMBRE, "eyatreeview");
        if (member_treeview) {
            g_signal_connect(member_treeview, "row-activated",
                           G_CALLBACK(on_member_treeview_row_activated), NULL);
        }
        
        GtkWidget *inscrire_button = lookup_widget(MEMBRE, "eyabuttoncours");
        if (inscrire_button) {
            g_signal_connect(inscrire_button, "clicked",
                           G_CALLBACK(on_eyabuttoncours_clicked), NULL);
        }
    }

    gtk_main();
    
    return 0;
}
