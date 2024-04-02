#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


FILE* ouvrirFichier(const char* nomFichier, const char* mode) {
   FILE* fichier = fopen(nomFichier, mode);
   if (fichier == NULL) {
      perror("Erreur lors de l'ouverture du fichier");
      return NULL;
   }
   return fichier;
}

int nombreDeLignes(FILE* fichier) {
   rewind(fichier);
   int lignes = 0;
   char ch;
   int prev = '\n';

   while ((ch = fgetc(fichier)) != EOF) {
      if (ch == '\n') lignes++;
      prev = ch;
   }

   if (prev != '\n') lignes++; 

   return lignes;
}
//===========================================================================================
int estDansLeTableau(char mot[], char tableau[][MAX_LONGUEUR_MOT], int taille) {
   for (int i = 0; i < taille; i++) {
      if (strcmp(mot, tableau[i]) == 0) {
         return 1; // Vrai, le mot est déjà dans le tableau
      }
   }
   return 0; // Faux, le mot n'est pas dans le tableau
}

void ajouterMotSiUnique(char mot[], char motsUniques[][MAX_LONGUEUR_MOT], int *nombreMotsUniques) {
   if (!estDansLeTableau(mot, motsUniques, *nombreMotsUniques)) {
      strcpy(motsUniques[*nombreMotsUniques], mot);
      (*nombreMotsUniques)++;
   }
}

void traiterEtAjouterMot(char mot[], int *indexMot, char motsUniques[][MAX_LONGUEUR_MOT], int *nombreMotsUniques) {
   if (*indexMot > 0) { // Vérifie si le mot est non vide
      mot[*indexMot] = '\0'; // Termine la chaîne
      ajouterMotSiUnique(mot, motsUniques, nombreMotsUniques);
      *indexMot = 0; // Réinitialise l'index pour le prochain mot
   }
}

int nombreDeMotsSansDoublons(FILE* fichier) {
   char motsUniques[MAX_MOTS][MAX_LONGUEUR_MOT];
   int nombreMotsUniques = 0;
   char mot[MAX_LONGUEUR_MOT];
   int indexMot = 0;
   char ch;
   rewind(fichier);

   while ((ch = fgetc(fichier)) != EOF) {
      if (isalpha(ch)) { 
         mot[indexMot++] = tolower(ch);
         if (indexMot >= MAX_LONGUEUR_MOT - 1) {
            traiterEtAjouterMot(mot, &indexMot, motsUniques, &nombreMotsUniques);
         }
      } else {
         traiterEtAjouterMot(mot, &indexMot, motsUniques, &nombreMotsUniques);
      }
   }

   traiterEtAjouterMot(mot, &indexMot, motsUniques, &nombreMotsUniques);
   return nombreMotsUniques;
}
//===========================================================================================

int nombreDeMotsAvecDoublons(FILE* fichier) {
   char mot[MAX_LONGUEUR_MOT];
   int totalMots = 0;
   char ch;
   int index = 0; 
   rewind(fichier);

   while ((ch = fgetc(fichier)) != EOF) {
      if (isalpha(ch)) {
         if (index < MAX_LONGUEUR_MOT - 1) {
            mot[index++] = ch;
         }
      } else if (index > 0) { 
         mot[index] = '\0';
         index = 0;
         totalMots++;
      }
   }

   if (index > 0) {
      totalMots++;
   }

   return totalMots;
}

//===========================================================================================
void initMot(char *mot, int *indexMot) {
   *indexMot = 0;
   mot[0] = '\0'; // Assure que le mot est vide
}

void traiterMot(const char *mot, int *compteurLettres) {
   int lettresUtilisees[NB_LETTRES] = {0};
   int indexLettre;

   for (int i = 0; mot[i] != '\0'; i++) {
      if (isalpha(mot[i])) {
         indexLettre = tolower(mot[i]) - 'a';
         lettresUtilisees[indexLettre] = 1;
      }
   }

   for (int i = 0; i < NB_LETTRES; i++) {
      if (lettresUtilisees[i]) compteurLettres[i]++;
   }
}

char trouverLettreLaPlusFrequente(const int *compteurLettres) {
   int maxCompte = 0;
   char lettreLaPlusFrequente = 'a';

   for (int i = 0; i < NB_LETTRES; i++) {
      if (compteurLettres[i] > maxCompte) {
         maxCompte = compteurLettres[i];
         lettreLaPlusFrequente = 'a' + i;
      }
   }

   return lettreLaPlusFrequente;
}

char lettreLaPlusFrequenteSansDoublons(FILE* fichier) {
   char mot[MAX_LONGUEUR_MOT];
   int compteurLettres[NB_LETTRES] = {0};
   int indexMot;
   char ch;

   rewind(fichier);
   initMot(mot, &indexMot);

   while ((ch = fgetc(fichier)) != EOF) {
      if (isalpha(ch) && indexMot < MAX_LONGUEUR_MOT - 1) {
         mot[indexMot++] = tolower(ch);
         mot[indexMot] = '\0'; // Maintient le mot terminé correctement
      } else if (indexMot > 0) { // Mot terminé
         traiterMot(mot, compteurLettres);
         initMot(mot, &indexMot);
      }
   }

   if (indexMot > 0) { // Dernier mot
      traiterMot(mot, compteurLettres);
   }

   return trouverLettreLaPlusFrequente(compteurLettres);
}
//===========================================================================================

int estCategoriePresente(char categories[MAX_CAT][MAX_CAT_LENGTH], int nbCat, char* cat) {
   for (int i = 0; i < nbCat; i++) {
      if (strcmp(categories[i], cat) == 0) return 1;
   }
   return 0;
}

int compterCategoriesUniques(FILE* fichier) {
   char ligne[MAX_LONGUEUR_LIGNE];
   char categories[MAX_CAT][MAX_CAT_LENGTH];
   int nbCat = 0;
   rewind(fichier);

   while (fgets(ligne, MAX_LONGUEUR_LIGNE, fichier)) {
      char* start = ligne;
      while ((start = strchr(start, '[')) != NULL) {
         char* end = strchr(start, ']');
         if (end == NULL) break;
         *end = '\0';

         char cat[MAX_CAT_LENGTH];
         strncpy(cat, start + 1, MAX_CAT_LENGTH - 1);
         cat[MAX_CAT_LENGTH - 1] = '\0';

         if (!estCategoriePresente(categories, nbCat, cat)) {
            strncpy(categories[nbCat], cat, MAX_CAT_LENGTH - 1);
            categories[nbCat][MAX_CAT_LENGTH - 1] = '\0';
            nbCat++;
            if (nbCat >= MAX_CAT) break;
         }
         start = end + 1;
      }
   }

   return nbCat;
}

//===========================================================================================
int compterRecettes(FILE* fichier) {
   int nbRecettes = 0;
   char ligne[1024]; // Assumption: une ligne ne dépasse pas 1024 caractères

   // Assurez-vous de commencer à lire depuis le début du fichier
   rewind(fichier);

   // Lire le fichier ligne par ligne
   while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
      nbRecettes++; // Incrémenter le compteur pour chaque ligne lue
   }

   return nbRecettes;
}

//===========================================================================================

void nettoyerToken(char* token) {
   // Cette fonction pourrait être étendue pour effectuer un nettoyage plus approfondi si nécessaire
   char* dest = token;
   for ( ; *token != '\0'; ++token) {
      if (*token != ' ') { // Copie seulement si le caractère n'est pas un espace
         *dest++ = *token;
      }
   }
   *dest = '\0';
}

void incrementerOuAjouterCategorie(Categorie categories[], int* nbCategories, const char* categorieNom) {
   for (int i = 0; i < *nbCategories; i++) {
      if (strcmp(categories[i].nom, categorieNom) == 0) {
         categories[i].compteur++;
         return;
      }
   }
   strncpy(categories[*nbCategories].nom, categorieNom, MAX_CATEGORY_NAME - 1);
   categories[*nbCategories].nom[MAX_CATEGORY_NAME - 1] = '\0';
   categories[(*nbCategories)++].compteur = 1;
}

int lireLigneEtExtraireCategories(FILE* fichier, Categorie categories[], int* nbCategories) {
   char ligne[256];
   if (fgets(ligne, sizeof(ligne), fichier) == NULL) {
      return 0; // Fin du fichier
   }

   char* token = strtok(ligne, "[]\n"); // Ignorer le nom de la recette
   while ((token = strtok(NULL, "[]\n")) != NULL) {
      nettoyerToken(token);
      if (token[0] != '\0') { // Si le token n'est pas vide après nettoyage
         incrementerOuAjouterCategorie(categories, nbCategories, token);
      }
   }
   return 1; // Ligne lue avec succès
}

char* determinerCategorieLaPlusFrequente(Categorie categories[], int nbCategories) {
   if (nbCategories == 0) {
      return NULL;
   }

   int maxIndex = 0;
   for (int i = 1; i < nbCategories; i++) {
      if (categories[i].compteur > categories[maxIndex].compteur) {
         maxIndex = i;
      }
   }
   return categories[maxIndex].nom;

}

char* trouverCategorieLaPlusFrequente(FILE* fichier) {
   rewind(fichier);
   Categorie categories[100]; // Supposons un maximum de 100 catégories différentes
   int nbCategories = 0;

   while (lireLigneEtExtraireCategories(fichier, categories, &nbCategories)) {}

   char* categorieLaPlusFrequenteNom = determinerCategorieLaPlusFrequente(categories, nbCategories);
   // Copie le nom de la catégorie la plus fréquente pour le retourner
   if (categorieLaPlusFrequenteNom != NULL) {
      char* result = (char*)malloc(strlen(categorieLaPlusFrequenteNom) + 1);
      strcpy(result, categorieLaPlusFrequenteNom);
      return result;
   }
   return NULL;
}
//===========================================================================================

RecetteLongue trouverRecetteLaPlusLongue(FILE* fichier) {
   RecetteLongue recetteLaPlusLongue = {"", 0};
   char ligne[MAX_LONGUEUR_LIGNE];
   rewind(fichier); 

   while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
      char* posCrochete = strchr(ligne, '[');
      int longueurNom = (posCrochete != NULL) ? (int)(posCrochete - ligne) : strlen(ligne);

      if (ligne[longueurNom - 1] == '\n') {
         longueurNom--;
      }

      if (longueurNom > recetteLaPlusLongue.longueur) {
         strncpy(recetteLaPlusLongue.nomRecette, ligne, longueurNom);
         recetteLaPlusLongue.nomRecette[longueurNom] = '\0'; // Assurez-vous que la chaîne est terminée
         recetteLaPlusLongue.longueur = longueurNom;
      }
   }

   return recetteLaPlusLongue;
}

//===========================================================================================

void calculerEtEcrireStatistiques(const char* fichierRecettes, const char* fichierStatistiques) {
   FILE* fichierR = ouvrirFichier(fichierRecettes, "r");
   if (fichierR == NULL) {
      return; 
   }

   int lignes = nombreDeLignes(fichierR);
   int motsSansDoublons = nombreDeMotsSansDoublons(fichierR);
   int totalMots = nombreDeMotsAvecDoublons(fichierR);
   char lettre = lettreLaPlusFrequenteSansDoublons(fichierR);
   int totalCategories = compterCategoriesUniques(fichierR);
   int nbRecettes = compterRecettes(fichierR);
   char* categorieLaPlusFrequente = trouverCategorieLaPlusFrequente(fichierR);
   RecetteLongue recetteLaPlusLongue = trouverRecetteLaPlusLongue(fichierR);

   fclose(fichierR);

   FILE* fichierS = ouvrirFichier(fichierStatistiques, "w");
   if (fichierS == NULL) {
      return; // Erreur d'ouverture du fichier statistiques, la gestion d'erreur affiche déjà un message
   }

   fprintf(fichierS, "Le nombre de lignes dans le fichier d'entrée: %d\n", lignes);
   fprintf(fichierS, "Le nombre de mots sans doublons: %d\n", motsSansDoublons);
   fprintf(fichierS, "Le nombre de mots avec doublons: %d\n", totalMots);
   fprintf(fichierS, "La lettre la plus fréquente (sans considérer les doublons): %c\n", lettre);
   fprintf(fichierS, "Le nombre de catégories : %d\n", totalCategories);
   fprintf(fichierS, "Le nombre de recettes: %d\n", nbRecettes);
   fprintf(fichierS, "La catégorie qui a le plus grand nombre de recettes: %s\n", categorieLaPlusFrequente);
   fprintf(fichierS,"La recette la plus longue est : %s\n", recetteLaPlusLongue.nomRecette);

   fclose(fichierS);
}