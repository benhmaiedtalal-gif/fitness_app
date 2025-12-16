#ifndef COURS_H
#define COURS_H

typedef struct {
    int id;
    char nom_cours[100];
    char coach[100];
    char date_heure[50];
    char lieu[100];
    char categorie[50];
    char type[50];
    char statut[20];
    int duree;
    int capacite_max;
} Cours;
typedef struct {
    int member_id;
    int course_id;
    char member_name[50];
    char course_name[50];
    char date_heure[50];
    char inscription_date[20]; // Date when registered
} Inscription;

/* Database operations */
int ajouter_cours(char *filename, Cours c);
int modifier_cours(char *filename, int id, Cours nouv);
int supprimer_cours(char *filename, int id);
Cours chercher_cours(char *filename, int id);

/* Memory operations */
Cours* trouver_cours_par_id(Cours *liste, int count, int id);
void supprimer_cours_de_liste(Cours *liste, int *count, int id);
int ajouter_cours_a_liste(Cours *liste, int *count, Cours c, int max);

#endif
