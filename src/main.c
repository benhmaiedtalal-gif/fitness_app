#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"
#include "callbacks.h"
#include "equipement.h"

// Déclarations des fonctions d'initialisation (déjà dans callbacks.c)
gboolean initialiser_treeview_delayed(gpointer user_data);
gboolean initialiser_treeview_coach_delayed(gpointer user_data);

// Fonction pour quitter l'application quand une fenêtre est fermée
void quitter_application(GtkWidget *widget, gpointer data) {
    g_print("Fermeture de l'application...\n");
    gtk_main_quit();
}

int main (int argc, char *argv[])
{
  GtkWidget *CONNECTION;
  GtkWidget *ADMINISTRATION;
  GtkWidget *COACH;
  GtkWidget *MEMBRE;
  
  gtk_set_locale ();
  gtk_init (&argc, &argv);

  add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");

  // Créer les 4 fenêtres
  CONNECTION = create_CONNECTION();
  ADMINISTRATION = create_ADMINISTRATION();
  COACH = create_COACH();
  MEMBRE = create_MEMBRE();
  
  // Connecter les événements de fermeture
  g_signal_connect(G_OBJECT(CONNECTION), "destroy",
                   G_CALLBACK(quitter_application), NULL);
  g_signal_connect(G_OBJECT(ADMINISTRATION), "destroy",
                   G_CALLBACK(quitter_application), NULL);
  g_signal_connect(G_OBJECT(COACH), "destroy",
                   G_CALLBACK(quitter_application), NULL);
  g_signal_connect(G_OBJECT(MEMBRE), "destroy",
                   G_CALLBACK(quitter_application), NULL);
  
  // Afficher les 4 fenêtres
  gtk_widget_show (CONNECTION);
  gtk_widget_show (ADMINISTRATION);
  gtk_widget_show (COACH);
  gtk_widget_show (MEMBRE);
  
  // Positionner les fenêtres pour qu'elles ne se superposent pas
  gtk_window_move(GTK_WINDOW(CONNECTION), 50, 50);
  gtk_window_move(GTK_WINDOW(ADMINISTRATION), 500, 50);
  gtk_window_move(GTK_WINDOW(COACH), 50, 400);
  gtk_window_move(GTK_WINDOW(MEMBRE), 500, 400);
  
  // Initialiser les TreeViews après un délai
  g_timeout_add(500, initialiser_treeview_delayed, ADMINISTRATION);
  g_timeout_add(500, initialiser_treeview_coach_delayed, COACH);
  
  g_print("Application démarrée - 4 fenêtres affichées\n");
  g_print("1. CONNECTION (en haut à gauche)\n");
  g_print("2. ADMINISTRATION (en haut à droite)\n");
  g_print("3. COACH (en bas à gauche)\n");
  g_print("4. MEMBRE (en bas à droite)\n");
  
  gtk_main ();
  return 0;
}
