#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste_chainee.h"
#include "stats.h" 



int main(int argc, char* argv[]) {
     if(argc < 4 || strcmp(argv[2], "-S") != 0) {
        printf("Usage: %s <fichier_recettes> -S <fichier_statistiques>\n", argv[0]);
        return 1;
    }
    
    calculerEtEcrireStatistiques(argv[1], argv[3]);

    const char* cheminFichier = "liste.txt";
    CategorieNode* teteCategorie = NULL;

    chargerEtOrganiserRecettes(cheminFichier, &teteCategorie);

    const char* nomFichierSortie = "resultat_recettes.txt";
    afficherCategoriesEtRecettesDansFichier(teteCategorie, nomFichierSortie);
    libererCategoriesEtRecettes(&teteCategorie);

     Recette recettes[100]; // Tableau pour stocker jusqu'à 100 recettes
    int nbRecettes = 0;
    
    chargerRecettes(recettes, &nbRecettes); // Chargement des recettes depuis un fichier
    rechercherRecettes(recettes, nbRecettes); // Boucle de recherche des recettes
    

  

    return 0;
}

