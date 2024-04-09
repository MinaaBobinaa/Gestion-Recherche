#ifndef LISTE_CHAINEE_H
#define LISTE_CHAINEE_H

#include <stdio.h>

#define MAX_NOM_RECETTE 100
#define MAX_CAT_RECETTE 50
#define MAX_CAT_PAR_RECETTE 5
#define MAX_RECETTES 1000
#define MAX_LIGNE 120
#define MAX_CAT_NOM 100


typedef struct {
   char categorie[100];
   char nom[100];
} Recette;

typedef struct RecetteNode {
   char nomRecette[MAX_NOM_RECETTE];
   struct RecetteNode* suivant;
} RecetteNode;

typedef struct CategorieNode {
   char nomCategorie[MAX_CAT_RECETTE];
   RecetteNode* recettes;
   struct CategorieNode* suivant;
} CategorieNode;


void trim(char* s);
void ajouterRecetteACategorie(CategorieNode** teteCategorie, const char* nomCategorie, const char* nomRecette);
void enMinuscules(char *str);
void chargerEtOrganiserRecettes(const char* cheminFichier, CategorieNode** teteCategorie);
void trierRecettesParInsertion(RecetteNode** tete);
void afficherCategoriesEtRecettesDansFichier(CategorieNode* teteCategorie, const char* nomFichier);
void libererCategoriesEtRecettes(CategorieNode** teteCategorie);
void chargerRecettes(Recette recettes[], int *nbRecettes);
void afficherRecettesCategorie(const Recette recettes[], int nbRecettes, const char *categorie, const char *motCle);
int verifierCategorie(const Recette recettes[], int nbRecettes, const char *categorie);
int extraireMots(char *chaine, char mots[][MAX_CAT_NOM]);
void rechercherRecettes(const Recette recettes[], int nbRecettes);


#endif