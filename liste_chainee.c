#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "liste_chainee.h"

void trim(char* s) {                                       
   char* p = s;
   int l = strlen(p);
   while(isspace(p[l - 1])) p[--l] = 0;
   while(* p && isspace(* p)) ++p, --l;
   memmove(s, p, l + 1);
}

void ajouterRecetteACategorie(CategorieNode** teteCategorie, const char* nomCategorie, const char* nomRecette) { ///ouii
   CategorieNode* currentCategorie = *teteCategorie;
   CategorieNode* lastCategorie = NULL;
   while (currentCategorie != NULL && strcmp(currentCategorie->nomCategorie, nomCategorie) != 0) {
      lastCategorie = currentCategorie;
      currentCategorie = currentCategorie->suivant;
   }

   if (currentCategorie == NULL) { 
      currentCategorie = (CategorieNode*)malloc(sizeof(CategorieNode));
      strcpy(currentCategorie->nomCategorie, nomCategorie);
      currentCategorie->recettes = NULL; 
      currentCategorie->suivant = NULL;
      
      if (lastCategorie != NULL) {
         lastCategorie->suivant = currentCategorie;
      } else {
         *teteCategorie = currentCategorie;
      }
   }

   RecetteNode* nouvelleRecette = (RecetteNode*)malloc(sizeof(RecetteNode));
   strcpy(nouvelleRecette->nomRecette, nomRecette);
   nouvelleRecette->suivant = currentCategorie->recettes;
   currentCategorie->recettes = nouvelleRecette;
}


void enMinuscules(char *str) {                                               
   for ( ; *str; ++str) *str = tolower((unsigned char) *str);
}



void chargerEtOrganiserRecettes(const char* cheminFichier, CategorieNode** teteCategorie) { 
   FILE* fichier = fopen(cheminFichier, "r");
   char ligne[MAX_LIGNE];
   
   if (!fichier) {
      perror("Erreur lors de l'ouverture du fichier");
      return;
   }

   while (fgets(ligne, sizeof(ligne), fichier)) {
      char* nomRecette = strtok(ligne, "[");
      char* categorie;
      while ((categorie = strtok(NULL, "[]"))) {
         trim(categorie);
         if (strlen(categorie) > 0) { 
            enMinuscules(categorie); 
            ajouterRecetteACategorie(teteCategorie, categorie, nomRecette);
         }
      }
   }

   fclose(fichier);
}

void trierRecettesParInsertion(RecetteNode** tete) {                           
   if (*tete == NULL || (*tete)->suivant == NULL) return;

   RecetteNode *sorted = NULL;
   RecetteNode *current = *tete; 

   while (current != NULL) {
      RecetteNode *next = current->suivant; 
      if (sorted == NULL || strcmp(current->nomRecette, sorted->nomRecette) <= 0) {
         current->suivant = sorted;
         sorted = current;
      } else {
         RecetteNode *sortedCurrent = sorted;
         while (sortedCurrent->suivant != NULL && strcmp(current->nomRecette, sortedCurrent->suivant->nomRecette) > 0) {
            sortedCurrent = sortedCurrent->suivant;
         }
         current->suivant = sortedCurrent->suivant;
         sortedCurrent->suivant = current;
      }
      current = next; 
   }

   *tete = sorted; 
}



void afficherCategoriesEtRecettesDansFichier(CategorieNode* teteCategorie, const char* nomFichier) {   
   FILE* fichier = fopen(nomFichier, "w");
   if (!fichier) {
      perror("Erreur lors de l'ouverture du fichier");
      return;
   }

   CategorieNode* currentCategorie = teteCategorie;
   while (currentCategorie != NULL) {
      fprintf(fichier, "{%s}\n", currentCategorie->nomCategorie);
      trierRecettesParInsertion(&(currentCategorie->recettes)); 
      RecetteNode* currentRecette = currentCategorie->recettes;
      while (currentRecette != NULL) {
         fprintf(fichier, "%s\n", currentRecette->nomRecette);
         currentRecette = currentRecette->suivant;
      }
      fprintf(fichier, "\n");
      currentCategorie = currentCategorie->suivant;
   }

   fclose(fichier);
}


void libererCategoriesEtRecettes(CategorieNode** teteCategorie) {                  
   CategorieNode* currentCategorie = *teteCategorie;
   while (currentCategorie != NULL) {
      RecetteNode* currentRecette = currentCategorie->recettes;
      while (currentRecette != NULL) {
         RecetteNode* tempRecette = currentRecette;
         currentRecette = currentRecette->suivant;
         free(tempRecette);
      }
      CategorieNode* tempCategorie = currentCategorie;
      currentCategorie = currentCategorie->suivant;
      free(tempCategorie);
   }
   *teteCategorie = NULL;
}



void chargerRecettes(Recette recettes[], int *nbRecettes) {          
   FILE *fichier = fopen("resultat_recettes.txt", "r");
   char ligne[MAX_LIGNE];
   char categorie[MAX_CAT_NOM] = "";
   
   if (fichier == NULL) {
      printf("Impossible d'ouvrir le fichier\n");
      exit(1);
   }
   
   while (fgets(ligne, sizeof(ligne), fichier)) {
      if (ligne[0] == '{') {
         sscanf(ligne, "{%[^}]}", categorie); 
      } else {
         if (strlen(ligne) > 1) { 
            sscanf(ligne, " %[^\n]", recettes[*nbRecettes].nom); 
            strcpy(recettes[*nbRecettes].categorie, categorie);
            (*nbRecettes)++;
         }
      }
   }
   
   fclose(fichier);
}


void afficherRecettesCategorie(const Recette recettes[], int nbRecettes, const char *categorie, const char *motCle) {   
   char categorieModifiable[MAX_CAT_NOM];
   char motCleModifiable[MAX_CAT_NOM];
   strncpy(categorieModifiable, categorie, MAX_CAT_NOM);
   strncpy(motCleModifiable, motCle, MAX_CAT_NOM);
   enMinuscules(categorieModifiable);
   enMinuscules(motCleModifiable);

   int trouve = 0;
   for (int i = 0; i < nbRecettes; i++) {
      char catMin[MAX_CAT_NOM], nomMin[MAX_CAT_NOM];
      strncpy(catMin, recettes[i].categorie, MAX_CAT_NOM);
      strncpy(nomMin, recettes[i].nom, MAX_CAT_NOM);
      enMinuscules(catMin);
      enMinuscules(nomMin);

      if (strcmp(catMin, categorieModifiable) == 0 && (motCleModifiable[0] == '\0' || strstr(nomMin, motCleModifiable))) {
         printf("%s\n", recettes[i].nom);
         trouve = 1;
      }
   }
   
   if (!trouve) {
      printf("Aucun résultat trouvé.\n");
   }
}


int verifierCategorie(const Recette recettes[], int nbRecettes, const char *categorie) {   
   char categorieModifiable[MAX_CAT_NOM];
   strncpy(categorieModifiable, categorie, MAX_CAT_NOM);
   enMinuscules(categorieModifiable);

   for (int i = 0; i < nbRecettes; i++) {
      char catMin[MAX_CAT_NOM];
      strncpy(catMin, recettes[i].categorie, MAX_CAT_NOM);
      enMinuscules(catMin);
      if (strcmp(catMin, categorieModifiable) == 0) {
         return 1;
      }
   }
   return 0;
}

int extraireMots(char *chaine, char mots[][MAX_CAT_NOM]) {
   int nbMots = 0;
   char *token = strtok(chaine, " ");
   while (token != NULL && nbMots < 3) {
      strcpy(mots[nbMots++], token);
      token = strtok(NULL, " ");
   }
   return nbMots;
}


void rechercherRecettes(const Recette recettes[], int nbRecettes) {       
   char input[MAX_LIGNE], categorie[MAX_CAT_NOM], motCle[MAX_CAT_NOM];
   
   while (1) {
      printf("\nEntrez votre critère de recherche (ou 'q' pour quitter) : ");
      fgets(input, MAX_LIGNE, stdin);
      input[strcspn(input, "\n")] = 0; 

      if (strcmp(input, "q") == 0) {      
         break; 
      }

      categorie[0] = '\0';
      motCle[0] = '\0';

      char mots[3][MAX_CAT_NOM];
      int nbMots = extraireMots(input, mots);

      if (nbMots == 1) {
         strcpy(categorie, mots[0]);
         if (!verifierCategorie(recettes, nbRecettes, categorie)) {
            printf("Catégorie inexistante\n");
         } else {
            afficherRecettesCategorie(recettes, nbRecettes, categorie, "");
         }
      } else if (nbMots == 2) {
         strcpy(categorie, mots[0]);
         strcpy(motCle, mots[1]);
         if (!verifierCategorie(recettes, nbRecettes, categorie)) {
            printf("Catégorie inexistante\n");
         } else {
            afficherRecettesCategorie(recettes, nbRecettes, categorie, motCle);
         }
      } else {
         printf("Recherche invalide.\n");
      }
   }
}





