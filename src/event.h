#ifndef EVENEMENT_H_INCLUDED
#define EVENEMENT_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    int id;
    char nom[100];
    char categorie[50];
    char lieu[100];
    char tarif;
    char niveaux[100];
    char etat[20];
    char coach[100];
    int capacite;
    int periode;
    char date[20];
} Evenement;

int chercher_id(char *fichier, int id);
int ajouter(char *fichier, Evenement event);
int supprimer(char *fichier, int id);
Evenement chercher(char *fichier, int id);
int modifier(char *fichier, int id, Evenement event, int modif);
int inscrit(char *fichieri, int idu, int ide);
Evenement chercher_simple(char *fichier, char *recherche);
#endif
