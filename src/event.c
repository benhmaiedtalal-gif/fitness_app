#include "event.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int chercher_id(char *fichier, int id) {
    char ligne[300];
    int trouve = 0;
    int idf;
    FILE *f = fopen(fichier, "r");
    
    if (f != NULL) {
        while (fgets(ligne, sizeof(ligne), f)) {
            if (sscanf(ligne, "%d", &idf) == 1) {
                if (id == idf) {
                    trouve = 1;
                    break;
                }
            }
        }
        fclose(f);
    }
    return trouve;
}

int ajouter(char *fichier, Evenement event) {
    if (chercher_id(fichier, event.id) == 1) {
        printf("ERREUR: ID %d existe déjà!\n", event.id);
        return 0;
    }
    FILE *f = fopen(fichier, "a");
    if (f != NULL) {
        fprintf(f, "%d;%s;%s;%s;%c;%s;%s;%s;%d;%d;%s\n",
                event.id,
                event.nom,
                event.categorie,
                event.lieu,
                event.tarif,
                event.niveaux,
                event.etat,
                event.coach,
                event.capacite,
                event.periode,
                event.date);
        fclose(f);
        return 1;
    }
    return 0;
}

int supprimer(char *fichier, int id) {
    FILE *f = fopen(fichier, "r");
    if (f == NULL) {
        return 0;
    }

    if (chercher_id(fichier, id) == 0) {
        fclose(f);
        return 0;
    }

    FILE *fichier_temp = fopen("temp.txt", "w");
    if (fichier_temp == NULL) {
        fclose(f);
        return 0;
    }

    char ligne[300];
    int supprime = 0;

    while (fgets(ligne, sizeof(ligne), f)) {
        int idf;
        if (sscanf(ligne, "%d", &idf) == 1) {
            if (idf == id) {
                supprime = 1;
            } else {
                fputs(ligne, fichier_temp);
            }
        } else {
            fputs(ligne, fichier_temp);
        }
    }

    fclose(f);
    fclose(fichier_temp);

    if (supprime) {
        remove(fichier);
        rename("temp.txt", fichier);
        return 1;
    } else {
        remove("temp.txt");
        return 0;
    }
}

Evenement chercher(char *fichier, int id) {
    char ligne[300];
    Evenement e;
    e.id = -1;
    
    FILE *f = fopen(fichier, "r");
    if (f != NULL) {
        while (fgets(ligne, sizeof(ligne), f)) {
            int champs_lus = sscanf(ligne, "%d;%99[^;];%49[^;];%99[^;];%c;%99[^;];%19[^;];%99[^;];%d;%d;%19[^\n]",
                                   &e.id, e.nom, e.categorie, e.lieu, &e.tarif, e.niveaux,
                                   e.etat, e.coach, &e.capacite, &e.periode, e.date);
            
            if (champs_lus == 11 && e.id == id) {
                fclose(f);
                return e;
            }
        }
        fclose(f);
    }
    
    // Return empty event if not found
    e.id = -1;
    e.nom[0] = '\0';
    e.categorie[0] = '\0';
    e.lieu[0] = '\0';
    e.tarif = "G";
    e.niveaux[0] = '\0';
    e.etat[0] = '\0';
    e.coach[0] = '\0';
    e.date[0] = '\0';
    e.capacite = 0;
    e.periode = 0;
    
    return e;
}
Evenement chercher_simple(char *fichier, char *recherche) {
    FILE *f = fopen(fichier, "r");
    Evenement e;
    e.id = -1;
    
    if (f == NULL) return e;
    
    char ligne[300];
    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d;%99[^;];%49[^;];%99[^;];%c;%99[^;];%19[^;];%99[^;];%d;%d;%49[^\n]",
               &e.id, e.nom, e.categorie, e.lieu, &e.tarif, e.niveaux,
               e.etat, e.coach, &e.capacite, &e.periode, e.date);
        
        /* Chercher dans tous les champs */
        if (strstr(ligne, recherche) != NULL) {
            fclose(f);
            return e;
        }
    }
    
    fclose(f);
    e.id = -1;
    e.nom[0] = '\0';
    e.categorie[0] = '\0';
    e.lieu[0] = '\0';
    e.tarif = "G";
    e.niveaux[0] = '\0';
    e.etat[0] = '\0';
    e.coach[0] = '\0';
    e.date[0] = '\0';
    e.capacite = 0;
    e.periode = 0;
    return e;
}
int modifier(char *fichier, int id, Evenement event, int modif) {
    FILE *f = fopen(fichier, "r");
    if (f == NULL) {
        return 0;
    }

    FILE *fichier_temp = fopen("temp.txt", "w");
    if (fichier_temp == NULL) {
        fclose(f);
        return 0;
    }

    char ligne[300];
    int modifie = 0;

    while (fgets(ligne, sizeof(ligne), f)) {
        int idf;
        if (sscanf(ligne, "%d", &idf) == 1) {
            if (idf == id) {

                fprintf(fichier_temp, "%d;%s;%s;%s;%c;%s;%s;%s;%d;%d;%s\n",
                        event.id, event.nom, event.categorie, event.lieu, 
                        event.tarif, event.niveaux, event.etat, event.coach,
                        event.capacite, event.periode, event.date);
                modifie = 1;
            } else {
                fputs(ligne, fichier_temp);
            }
        } else {
            fputs(ligne, fichier_temp);
        }
    }

    fclose(f);
    fclose(fichier_temp);

    if (modifie) {
        remove(fichier);
        rename("temp.txt", fichier);
        return 1;
    } else {
        remove("temp.txt");
        return 0;
    }
}

int inscrit(char *fichieri, int idu, int ide) {
    FILE *f = fopen(fichieri, "a+");
    if (f == NULL) {
        return 0;
    }
    
    
    char ligne[100];
    int deja_inscrit = 0;
    int idu_f, ide_f;
    
    while (fgets(ligne, sizeof(ligne), f)) {
        if (sscanf(ligne, "%d;%d", &idu_f, &ide_f) == 2) {
            if (idu_f == idu && ide_f == ide) {
                deja_inscrit = 1;
                break;
            }
        }
    }
    
    if (!deja_inscrit) {
        fprintf(f, "%d;%d\n", idu, ide);
    }
    
    fclose(f);
    return !deja_inscrit;
}
