#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste_chainee.h"
#include "stats.h" 


int main(int argc, char* argv[]) {
   if (argc < 2) {
      fprintf(stderr, "Usage: %s <fichier_recettes> [-S <fichier_statistiques>]\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   const char* cheminFichier = argv[1];
   CategorieNode* teteCategorie = NULL;

   chargerEtOrganiserRecettes(cheminFichier, &teteCategorie);

   if (argc == 4 && strcmp(argv[2], "-S") == 0) {
      calculerEtEcrireStatistiques(argv[1], argv[3]);
   } else if (argc > 2) {
      fprintf(stderr, "Usage: %s <fichier_recettes> [-S <fichier_statistiques>]\n", argv[0]);
      libererCategoriesEtRecettes(&teteCategorie);
      exit(EXIT_FAILURE);
   }

   const char* nomFichierSortie = "resultat_recettes.txt";
   afficherCategoriesEtRecettesDansFichier(teteCategorie, nomFichierSortie);
   libererCategoriesEtRecettes(&teteCategorie);

   Recette recettes[100];
   int nbRecettes = 0;

   chargerRecettes(recettes, &nbRecettes);
   rechercherRecettes(recettes, nbRecettes);

   return 0;
}

