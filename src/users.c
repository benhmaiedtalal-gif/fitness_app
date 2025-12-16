#include "users.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int verifier_utilisateur(char *fichier, char *id, char *mdp, char *type) {
    FILE *f = fopen(fichier, "r");
    char ligne[200];
    
    if (f == NULL) return 0;
    
    while (fgets(ligne, sizeof(ligne), f)) {
        char id_fichier[50], mdp_fichier[50], type_fichier[50];
        
        if (sscanf(ligne, "%[^;];%[^;];%s", id_fichier, mdp_fichier, type_fichier) == 3) {
            if (strcmp(id, id_fichier) == 0 && strcmp(mdp, mdp_fichier) == 0) {
                strcpy(type, type_fichier);
                fclose(f);
                return 1;
            }
        }
    }
    
    fclose(f);
    return 0;
}
