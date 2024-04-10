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

/**
 * Supprime les espaces au début et à la fin de la chaîne de caractères donnée
 * 
 * @param s Un pointeur vers le tableau de caractères (chaîne) à traiter
 */
void trim(char* s);

/**
 * Ajoute une recette à une catégorie spécifique dans une liste chaînée de nœuds de catégories
 * Si la catégorie n'existe pas, elle est créée et ajoutée à la liste
 * 
 * @param teteCategorie Un pointeur vers le pointeur du premier nœud de catégorie dans la liste chaînée
 * @param nomCategorie Le nom de la catégorie à laquelle la recette doit être ajoutée
 * @param nomRecette Le nom de la recette à ajouter à la catégorie
 */
void ajouterRecetteACategorie(CategorieNode** teteCategorie, const char* nomCategorie, const char* nomRecette);

/**
 * Convertit tous les caractères d'une chaîne en minuscules
 * 
 * @param str Un pointeur vers le tableau de caractères (chaîne) dont les caractères
 * doivent être convertis en minuscules. La modification est effectuée sur place
 */
void enMinuscules(char *str);

/**
 * Charge les recettes à partir d'un fichier et les organise par catégorie dans une liste chaînée
 * 
 * @param cheminFichier Le chemin vers le fichier contenant les recettes. Chaque ligne du fichier doit
 * contenir une recette suivie de sa catégorie entre crochets
 * @param teteCategorie Un pointeur vers le pointeur du premier nœud de catégorie dans la liste chaînée
 */
void chargerEtOrganiserRecettes(const char* cheminFichier, CategorieNode** teteCategorie);

/**
 * Trie les recettes d'une liste chaînée en utilisant le tri par insertion
 * 
 * @param tete Un pointeur vers le pointeur du premier nœud de recette dans la liste chaînée
 */
void trierRecettesParInsertion(RecetteNode** tete);

/**
 * Affiche les catégories et leurs recettes associées dans un fichier
 * Les recettes de chaque catégorie sont préalablement triées par ordre alphabétique
 * 
 * @param teteCategorie Le pointeur vers le premier nœud de catégorie dans la liste chaînée
 * @param nomFichier Le nom du fichier dans lequel les catégories et recettes seront écrites.
 * Si le fichier existe déjà, il sera écrasé
 */
void afficherCategoriesEtRecettesDansFichier(CategorieNode* teteCategorie, const char* nomFichier);

/**
 * Libère la mémoire allouée pour les catégories et les recettes
 * 
 * @param teteCategorie Un pointeur vers le pointeur du premier nœud de catégorie dans la liste chaînée.
 */
void libererCategoriesEtRecettes(CategorieNode** teteCategorie);

/**
 * Charge des recettes à partir d'un fichier et les stocke dans un tableau de structures de recettes
 * Le fichier doit avoir un format spécifique où chaque catégorie est entourée de crochets "{}"
 * et les recettes sont listées après leur catégorie respective
 * 
 * @param recettes Un tableau de structures de recettes où charger les données
 * @param nbRecettes Un pointeur vers un entier qui sera mis à jour avec le nombre de recettes chargées
 */
void chargerRecettes(Recette recettes[], int *nbRecettes);

/**
 * Affiche les recettes d'une catégorie spécifique qui contiennent un mot-clé donné
 * 
 * @param recettes Le tableau des recettes à parcourir
 * @param nbRecettes Le nombre total de recettes dans le tableau
 * @param categorie La catégorie des recettes à afficher
 * @param motCle Le mot-clé à rechercher dans les noms des recettes
 */
void afficherRecettesCategorie(const Recette recettes[], int nbRecettes, const char *categorie, const char *motCle);

/**
 * Vérifie si une catégorie spécifique est présente dans un tableau de recettes
 * 
 * @param recettes Le tableau des recettes à parcourir
 * @param nbRecettes Le nombre total de recettes dans le tableau
 * @param categorie La catégorie à rechercher. La recherche ne tient pas compte de la casse
 * @return 1 si la catégorie est trouvée, 0 sinon
 */
int verifierCategorie(const Recette recettes[], int nbRecettes, const char *categorie);

/**
 * Extrait jusqu'à 3 mots d'une chaîne donnée, les stockant dans un tableau de chaînes
 * 
 * @param chaine La chaîne de caractères à diviser en mots
 * @param mots Un tableau de chaînes où les mots extraits seront stockés
 * @return Le nombre de mots extraits et stockés dans le tableau mots
 */
int extraireMots(char *chaine, char mots[][MAX_CAT_NOM]);

/**
 * Lance une boucle interactive permettant à l'utilisateur de rechercher des recettes par catégorie et/ou mot-clé
 * L'utilisateur peut saisir une catégorie seule pour voir toutes les recettes de cette catégorie, ou une catégorie
 * suivie d'un mot-clé pour filtrer davantage les résultats. La recherche est insensible à la casse.
 * La saisie de 'q' termine la recherche et sort de la fonction
 * 
 * @param recettes Le tableau des recettes à parcourir
 * @param nbRecettes Le nombre total de recettes dans le tableau
 */
void rechercherRecettes(const Recette recettes[], int nbRecettes);


#endif