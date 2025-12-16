#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cours.h"

/* File operations */
int ajouter_cours(char *filename, Cours c) {
    FILE *f = fopen(filename, "a");
    if (f == NULL) return 0;

    fprintf(f, "%d|%s|%s|%s|%s|%s|%s|%s|%d|%d\n",
            c.id, c.nom_cours, c.coach, c.date_heure,
            c.lieu, c.categorie, c.type, c.statut,
            c.duree, c.capacite_max);
    fclose(f);
    return 1;
}

int modifier_cours(char *filename, int id, Cours nouv) {
    Cours c;
    int trouve = 0;
    FILE *f = fopen(filename, "r");
    FILE *tmp = fopen("temp.txt", "w");
    if (f == NULL || tmp == NULL) return 0;

    char line[500];
    while (fgets(line, sizeof(line), f)) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        // Parse the line
        char *token;
        char *tokens[10];
        int token_count = 0;
        
        token = strtok(line, "|");
        while (token && token_count < 10) {
            tokens[token_count++] = token;
            token = strtok(NULL, "|");
        }
        
        if (token_count == 10) {
            c.id = atoi(tokens[0]);
            strcpy(c.nom_cours, tokens[1]);
            strcpy(c.coach, tokens[2]);
            strcpy(c.date_heure, tokens[3]);
            strcpy(c.lieu, tokens[4]);
            strcpy(c.categorie, tokens[5]);
            strcpy(c.type, tokens[6]);
            strcpy(c.statut, tokens[7]);
            c.duree = atoi(tokens[8]);
            c.capacite_max = atoi(tokens[9]);
            
            if (c.id == id) {
                // Write the new course
                fprintf(tmp, "%d|%s|%s|%s|%s|%s|%s|%s|%d|%d\n",
                        nouv.id, nouv.nom_cours, nouv.coach, nouv.date_heure,
                        nouv.lieu, nouv.categorie, nouv.type, nouv.statut,
                        nouv.duree, nouv.capacite_max);
                trouve = 1;
            } else {
                // Write the original course
                fprintf(tmp, "%d|%s|%s|%s|%s|%s|%s|%s|%d|%d\n",
                        c.id, c.nom_cours, c.coach, c.date_heure,
                        c.lieu, c.categorie, c.type, c.statut,
                        c.duree, c.capacite_max);
            }
        }
    }

    fclose(f);
    fclose(tmp);
    remove(filename);
    rename("temp.txt", filename);
    return trouve;
}

int supprimer_cours(char *filename, int id) {
    Cours c;
    int trouve = 0;
    FILE *f = fopen(filename, "r");
    FILE *tmp = fopen("temp.txt", "w");
    if (f == NULL || tmp == NULL) return 0;

    char line[500];
    while (fgets(line, sizeof(line), f)) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        // Parse the line
        char *token;
        char *tokens[10];
        int token_count = 0;
        
        token = strtok(line, "|");
        while (token && token_count < 10) {
            tokens[token_count++] = token;
            token = strtok(NULL, "|");
        }
        
        if (token_count == 10) {
            c.id = atoi(tokens[0]);
            strcpy(c.nom_cours, tokens[1]);
            strcpy(c.coach, tokens[2]);
            strcpy(c.date_heure, tokens[3]);
            strcpy(c.lieu, tokens[4]);
            strcpy(c.categorie, tokens[5]);
            strcpy(c.type, tokens[6]);
            strcpy(c.statut, tokens[7]);
            c.duree = atoi(tokens[8]);
            c.capacite_max = atoi(tokens[9]);
            
            if (c.id == id) {
                trouve = 1; // Skip this line (delete)
            } else {
                // Write the course to temp file
                fprintf(tmp, "%d|%s|%s|%s|%s|%s|%s|%s|%d|%d\n",
                        c.id, c.nom_cours, c.coach, c.date_heure,
                        c.lieu, c.categorie, c.type, c.statut,
                        c.duree, c.capacite_max);
            }
        }
    }

    fclose(f);
    fclose(tmp);
    remove(filename);
    rename("temp.txt", filename);
    return trouve;
}

Cours chercher_cours(char *filename, int id) {
    Cours c;
    c.id = -1; // Indicate not found
    
    FILE *f = fopen(filename, "r");
    if (f == NULL) return c;

    char line[500];
    while (fgets(line, sizeof(line), f)) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        // Parse the line
        char *token;
        char *tokens[10];
        int token_count = 0;
        
        token = strtok(line, "|");
        while (token && token_count < 10) {
            tokens[token_count++] = token;
            token = strtok(NULL, "|");
        }
        
        if (token_count == 10) {
            c.id = atoi(tokens[0]);
            strcpy(c.nom_cours, tokens[1]);
            strcpy(c.coach, tokens[2]);
            strcpy(c.date_heure, tokens[3]);
            strcpy(c.lieu, tokens[4]);
            strcpy(c.categorie, tokens[5]);
            strcpy(c.type, tokens[6]);
            strcpy(c.statut, tokens[7]);
            c.duree = atoi(tokens[8]);
            c.capacite_max = atoi(tokens[9]);
            
            if (c.id == id) {
                fclose(f);
                return c;
            }
        }
    }

    fclose(f);
    c.id = -1; // Not found
    return c;
}

/* Memory operations */
Cours* trouver_cours_par_id(Cours *liste, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (liste[i].id == id) return &liste[i];
    }
    return NULL;
}

void supprimer_cours_de_liste(Cours *liste, int *count, int id) {
    for (int i = 0; i < *count; i++) {
        if (liste[i].id == id) {
            // Shift all elements after i one position left
            for (int j = i; j < *count - 1; j++) {
                liste[j] = liste[j + 1];
            }
            (*count)--;
            i--; // Check the same index again
        }
    }
}

int ajouter_cours_a_liste(Cours *liste, int *count, Cours c, int max) {
    if (*count >= max) return 0;
    
    // Check if ID already exists
    for (int i = 0; i < *count; i++) {
        if (liste[i].id == c.id) return 0;
    }
    
    liste[*count] = c;
    (*count)++;
    return 1;
}
