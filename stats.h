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

/**
 * Ouvre un fichier en lecture ou en écriture, selon le mode spécifié
 * Affiche une erreur si le fichier ne peut pas être ouvert
 * 
 * @param nomFichier Le chemin d'accès au fichier à ouvrir
 * @param mode Le mode d'ouverture du fichier (ex : "r" pour lecture, "w" pour écriture)
 * @return Un pointeur vers le fichier ouvert, ou NULL en cas d'échec
 */
FILE* ouvrirFichier(const char* nomFichier, const char* mode);

/**
 * Compte le nombre de lignes dans un fichier ouvert
 * 
 * @param fichier Un pointeur vers le fichier ouvert à lire
 * @return Le nombre total de lignes dans le fichier
 */
int nombreDeLignes(FILE* fichier);

/**
 * Vérifie si un mot est présent dans un tableau de chaînes
 * 
 * @param mot La chaîne de caractères à rechercher
 * @param tableau Le tableau de chaînes de caractères dans lequel effectuer la recherche
 * @param taille La taille du tableau
 * @return 1 si le mot est trouvé dans le tableau, 0 sinon
 */
int estDansLeTableau(char mot[], char tableau[][MAX_LONGUEUR_MOT], int taille);

/**
 * Ajoute un mot à un tableau de mots uniques si le mot n'est pas déjà présent dans le tableau
 * 
 * @param mot La chaîne de caractères à ajouter
 * @param motsUniques Le tableau contenant les mots déjà uniques
 * @param nombreMotsUniques Un pointeur vers le nombre actuel de mots uniques dans le tableau
 */
void ajouterMotSiUnique(char mot[], char motsUniques[][MAX_LONGUEUR_MOT], int *nombreMotsUniques);

/**
 * Traite et ajoute un mot à un tableau de mots uniques si le mot n'est pas déjà présent
 * Cette fonction ajoute le mot actuellement construit si sa longueur est supérieure à 0
 * Après l'ajout, le mot est réinitialisé pour un nouveau traitement
 * 
 * @param mot Le buffer contenant le mot actuel à ajouter. Il doit être terminé par un caractère nul
 * @param indexMot Un pointeur vers l'index actuel dans le buffer du mot
 * @param motsUniques Le tableau de mots uniques où ajouter le mot
 * @param nombreMotsUniques Un pointeur vers le nombre total de mots uniques actuellement dans le tableau
 */
void traiterEtAjouterMot(char mot[], int *indexMot, char motsUniques[][MAX_LONGUEUR_MOT], int *nombreMotsUniques);

/**
 * Compte le nombre de mots uniques dans un fichier
 * Un mot est défini comme une séquence de caractères alphabétiques
 * La casse est ignorée (tout est converti en minuscules)
 * 
 * @param fichier Un pointeur vers le fichier à lire
 * @return Le nombre total de mots uniques dans le fichier
 */
int nombreDeMotsSansDoublons(FILE* fichier);

/**
 * Compte le nombre total de mots dans un fichier, y compris les doublons
 * Un mot est défini comme une séquence de caractères alphabétiques
 * 
 * @param fichier Un pointeur vers le fichier à lire
 * @return Le nombre total de mots (avec doublons) dans le fichier
 */
int nombreDeMotsAvecDoublons(FILE* fichier);

/**
 * Initialise un buffer de mot à vide
 * 
 * @param mot Le buffer du mot à initialiser
 * @param indexMot Un pointeur vers l'index actuel dans le buffer du mot
 */
void initMot(char *mot, int *indexMot);

/**
 * Traite un mot pour compter la fréquence d'apparition de chaque lettre
 * Met à jour un tableau de compteurs, un pour chaque lettre de l'alphabet
 * 
 * @param mot Le mot à traiter
 * @param compteurLettres Un tableau de 26 entiers représentant le compteur pour chaque lettre de l'alphabet
 */
void traiterMot(const char *mot, int *compteurLettres);

/**
 * Trouve la lettre la plus fréquemment utilisée parmi celles présentes dans le tableau de compteurs
 * 
 * @param compteurLettres Un tableau de 26 entiers où chaque élément représente le compteur
 * pour une lettre de l'alphabet
 * @return La lettre la plus fréquente
 */
char trouverLettreLaPlusFrequente(const int *compteurLettres);

/**
 * Lit un fichier et détermine la lettre la plus fréquemment utilisée sans compter les doublons dans un même mot
 * 
 * @param fichier Un pointeur vers le fichier à lire
 * @return La lettre la plus fréquente dans le fichier, sans compter les doublons de lettre dans un même mot
 */
char lettreLaPlusFrequenteSansDoublons(FILE* fichier);

/**
 * Vérifie si une catégorie est présente dans un tableau de catégories
 * 
 * @param categories Le tableau contenant les catégories déjà lues
 * @param nbCat Le nombre de catégories déjà dans le tableau
 * @param cat La catégorie à vérifier
 * @return 1 si la catégorie est déjà présente dans le tableau, 0 sinon
 */
int estCategoriePresente(char categories[MAX_CAT][MAX_CAT_LENGTH], int nbCat, char* cat);

/**
 * Compte le nombre de catégories uniques dans un fichier
 * Les catégories sont identifiées comme étant entre crochets '[]' dans chaque ligne du fichier
 * 
 * @param fichier Un pointeur vers le fichier à lire
 * @return Le nombre de catégories uniques trouvées dans le fichier
 */
int compterCategoriesUniques(FILE* fichier);

/**
 * Compte le nombre total de recettes (lignes) dans un fichier
 * 
 * @param fichier Un pointeur vers le fichier à lire
 * @return Le nombre total de lignes (recettes) dans le fichier
 */
int compterRecettes(FILE* fichier);

/**
 * Nettoie un token en supprimant tous les espaces
 * 
 * @param token Le token à nettoyer
 */
void nettoyerToken(char* token);

/**
 * Incrémente le compteur d'une catégorie si elle existe déjà dans le tableau de catégories,
 * sinon ajoute une nouvelle catégorie au tableau
 * 
 * @param categories Le tableau de structures Categorie où stocker ou incrémenter les catégories
 * @param nbCategories Un pointeur vers le nombre de catégories actuellement dans le tableau
 * @param categorieNom Le nom de la catégorie à incrémenter ou à ajouter
 */
void incrementerOuAjouterCategorie(Categorie categories[], int* nbCategories, const char* categorieNom);

/**
 * Lit une ligne du fichier, extrait les catégories mentionnées, et les traite via incrementerOuAjouterCategorie
 * 
 * @param fichier Un pointeur vers le fichier à lire
 * @param categories Le tableau de structures Categorie où stocker ou incrémenter les catégories
 * @param nbCategories Un pointeur vers le nombre de catégories actuellement dans le tableau
 * @return 0 si la fin du fichier est atteinte, 1 sinon
 */
int lireLigneEtExtraireCategories(FILE* fichier, Categorie categories[], int* nbCategories);

/**
 * Détermine la catégorie la plus fréquente parmi un tableau de catégories
 * 
 * @param categories Le tableau de catégories à examiner
 * @param nbCategories Le nombre de catégories dans le tableau
 * @return Le nom de la catégorie la plus fréquente. Retourne NULL si aucune catégorie n'est présente
 */
char* determinerCategorieLaPlusFrequente(Categorie categories[], int nbCategories);

/**
 * Trouve et retourne le nom de la catégorie la plus fréquente dans un fichier
 * 
 * @param fichier Un pointeur vers le fichier contenant les données des catégories
 * @return Le nom de la catégorie la plus fréquente. La chaîne de caractères doit être libérée après utilisation
 */
char* trouverCategorieLaPlusFrequente(FILE* fichier);

/**
 * Trouve et retourne la recette ayant le nom le plus long dans un fichier
 * 
 * @param fichier Un pointeur vers le fichier à lire
 * @return Une structure RecetteLongue contenant le nom de la recette la plus longue et sa longueur
 */
RecetteLongue trouverRecetteLaPlusLongue(FILE* fichier);

/**
 * Calcule différentes statistiques à partir d'un fichier de recettes donné et écrit ces 
 * statistiques dans un autre fichier.
 * Les statistiques incluent le nombre de lignes, le nombre de mots (avec et sans doublons),
 * la lettre la plus fréquente,le nombre total de catégories, le nombre de recettes, 
 * la catégorie la plus fréquente, et la recette avec le nom le plus long.
 * 
 * @param fichierRecettes Le chemin vers le fichier contenant les recettes à analyser
 * @param fichierStatistiques Le chemin vers le fichier où écrire les statistiques calculées
 */
void calculerEtEcrireStatistiques(const char* fichierRecettes, const char* fichierStatistiques);


#endif
