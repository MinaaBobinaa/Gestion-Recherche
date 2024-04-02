#ifndef STATS_H
#define STATS_H

#include <stdio.h>

#define MAX_MOTS 1000 // Nombre maximum de mots uniques que nous pouvons gérer
#define MAX_LONGUEUR_MOT 100 // Longueur maximale d'un mot
#define NB_LETTRES 26
#define MAX_LONGUEUR_LIGNE 120
#define MAX_CAT 500 // Nombre maximal de catégories uniques que vous pouvez gérer
#define MAX_CAT_LENGTH 50 // Longueur maximale d'une catégorie 
#define MAX_CATEGORY_NAME 50

typedef struct {
   char nom[MAX_CATEGORY_NAME];
   int compteur;
} Categorie;

typedef struct {
   char nomRecette[MAX_LONGUEUR_LIGNE];
   int longueur;
} RecetteLongue;

FILE* ouvrirFichier(const char* nomFichier, const char* mode);
int nombreDeLignes(FILE* fichier);
int estDansLeTableau(char mot[], char tableau[][MAX_LONGUEUR_MOT], int taille);
void ajouterMotSiUnique(char mot[], char motsUniques[][MAX_LONGUEUR_MOT], int *nombreMotsUniques);
void traiterEtAjouterMot(char mot[], int *indexMot, char motsUniques[][MAX_LONGUEUR_MOT], int *nombreMotsUniques);
int nombreDeMotsSansDoublons(FILE* fichier);
int nombreDeMotsAvecDoublons(FILE* fichier);
void initMot(char *mot, int *indexMot);
void traiterMot(const char *mot, int *compteurLettres);
char trouverLettreLaPlusFrequente(const int *compteurLettres);
char lettreLaPlusFrequenteSansDoublons(FILE* fichier);
int estCategoriePresente(char categories[MAX_CAT][MAX_CAT_LENGTH], int nbCat, char* cat);
int compterCategoriesUniques(FILE* fichier);
int compterRecettes(FILE* fichier);
void nettoyerToken(char* token);
void incrementerOuAjouterCategorie(Categorie categories[], int* nbCategories, const char* categorieNom);
int lireLigneEtExtraireCategories(FILE* fichier, Categorie categories[], int* nbCategories);
char* determinerCategorieLaPlusFrequente(Categorie categories[], int nbCategories);
char* trouverCategorieLaPlusFrequente(FILE* fichier);
RecetteLongue trouverRecetteLaPlusLongue(FILE* fichier);
void calculerEtEcrireStatistiques(const char* fichierRecettes, const char* fichierStatistiques);


#endif
