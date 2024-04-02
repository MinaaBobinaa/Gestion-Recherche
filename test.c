#include "test.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "stats.h" 

void test_ouvrirFichier(void) {
   FILE* f = ouvrirFichier("liste.txt", "r");
   CU_ASSERT_PTR_NOT_NULL(f);
   if (f != NULL) fclose(f);

   f = ouvrirFichier("fichier_inexistant.txt", "r");
   CU_ASSERT_PTR_NULL(f);
}

void test_nombreDeLignes(void) {
   FILE* f = ouvrirFichier("liste.txt", "r");
   if (f != NULL) {
     int lignes = nombreDeLignes(f);
     CU_ASSERT(lignes > 0);
     fclose(f);
   }
}

void test_estDansLeTableau(void) {
   char tableau[TAILLE_TABLEAU][MAX_LONGUEUR_MOT] = {"chat", "chien", "oiseau"};
   int taille = 3;
   
   CU_ASSERT_TRUE(estDansLeTableau("chat", tableau, taille));
   CU_ASSERT_FALSE(estDansLeTableau("poisson", tableau, taille));
}


void test_ajouterMotSiUnique(void) {
   char motsUniques[TAILLE_TABLEAU][MAX_LONGUEUR_MOT] = {"chat"};
   int nombreMotsUniques = 1;
   
   ajouterMotSiUnique("chien", motsUniques, &nombreMotsUniques);
   CU_ASSERT_TRUE(estDansLeTableau("chien", motsUniques, nombreMotsUniques));
   CU_ASSERT_EQUAL(nombreMotsUniques, 2);

   ajouterMotSiUnique("chat", motsUniques, &nombreMotsUniques);
   CU_ASSERT_EQUAL(nombreMotsUniques, 2); 
}

void test_traiterEtAjouterMot(void) {
   char motsUniques[TAILLE_TABLEAU][MAX_LONGUEUR_MOT] = {0};
   int nombreMotsUniques = 0;
   char mot[MAX_LONGUEUR_MOT] = "pomme";
   int indexMot = 5; // "pomme" a 5 caractères

   traiterEtAjouterMot(mot, &indexMot, motsUniques, &nombreMotsUniques);
   CU_ASSERT_TRUE(estDansLeTableau("pomme", motsUniques, nombreMotsUniques));
   CU_ASSERT_EQUAL(nombreMotsUniques, 1);
   CU_ASSERT_EQUAL(indexMot, 0); 
}

void test_nombreDeMotsSansDoublons(void) {
   FILE *fichier;
   int resultat;

   // Test avec le premier fichier
   fichier = fopen("liste.txt", "r");
   CU_ASSERT_PTR_NOT_NULL_FATAL(fichier);
   resultat = nombreDeMotsSansDoublons(fichier);
   CU_ASSERT_EQUAL(resultat, 22); // Remplacez 22 par le nombre attendu de mots uniques pour ce fichier
   fclose(fichier);

}

void test_nombreDeMotsAvecDoublons(void) {
   FILE *fichier;
   int resultat;

   fichier = fopen("liste.txt", "r");
   CU_ASSERT_PTR_NOT_NULL_FATAL(fichier);
   resultat = nombreDeMotsAvecDoublons(fichier);
   CU_ASSERT_EQUAL(resultat, 29); // Remplacez 29 par le nombre réel de mots dans le fichier
   fclose(fichier);
}

void test_initMot(void) {
   char mot[MAX_LONGUEUR_MOT] = "initial";
   int indexMot = 7; 

   initMot(mot, &indexMot);

   CU_ASSERT_STRING_EQUAL(mot, "");
   CU_ASSERT_EQUAL(indexMot, 0);
}

void test_traiterMot(void) {
   int compteurLettres[NB_LETTRES];
   memset(compteurLettres, 0, sizeof(compteurLettres)); 

   traiterMot("example", compteurLettres);

   CU_ASSERT_EQUAL(compteurLettres['e' - 'a'], 1);
   CU_ASSERT_EQUAL(compteurLettres['x' - 'a'], 1);
   CU_ASSERT_EQUAL(compteurLettres['a' - 'a'], 1);
   CU_ASSERT_EQUAL(compteurLettres['m' - 'a'], 1);
   CU_ASSERT_EQUAL(compteurLettres['p' - 'a'], 1);
   CU_ASSERT_EQUAL(compteurLettres['l' - 'a'], 1);
}

void test_trouverLettreLaPlusFrequente(void) {
   int compteurLettres[NB_LETTRES] = {0};
   compteurLettres['a' - 'a'] = 3;
   compteurLettres['b' - 'a'] = 5;
   compteurLettres['c' - 'a'] = 10;

   CU_ASSERT_EQUAL(trouverLettreLaPlusFrequente(compteurLettres), 'c');
}

void test_lettreLaPlusFrequenteSansDoublons(void) {
   FILE *fichier = fopen("liste.txt", "r");
   CU_ASSERT_PTR_NOT_NULL_FATAL(fichier);

   char resultat = lettreLaPlusFrequenteSansDoublons(fichier);
   CU_ASSERT_EQUAL(resultat, 'e'); 

   fclose(fichier);
}

void test_estCategoriePresente(void) {
   char categories[MAX_CAT][MAX_CAT_LENGTH] = {"chat", "chien", "oiseau"};
   int nbCat = 3;

   CU_ASSERT_TRUE(estCategoriePresente(categories, nbCat, "chat"));
   CU_ASSERT_FALSE(estCategoriePresente(categories, nbCat, "poisson"));
}

void test_compterCategoriesUniques(void) {
   FILE *fichier = fopen("liste.txt", "r");
   CU_ASSERT_PTR_NOT_NULL_FATAL(fichier);

   int resultat = compterCategoriesUniques(fichier);
   fclose(fichier);

   CU_ASSERT_EQUAL(resultat, 8);
}


void test_compterRecettes(void) {
   FILE *fichier;
   int resultat;

   fichier = fopen("liste.txt", "r");
   CU_ASSERT_PTR_NOT_NULL_FATAL(fichier);
   resultat = compterRecettes(fichier);
   fclose(fichier);
   CU_ASSERT_EQUAL(resultat, 6); 

}

void test_nettoyerToken(void) {
   char token[] = " test  token ";
   nettoyerToken(token);
   CU_ASSERT_STRING_EQUAL(token, "testtoken");
}

void test_incrementerOuAjouterCategorie(void) {
   Categorie categories[10];
   int nbCategories = 0;

   incrementerOuAjouterCategorie(categories, &nbCategories, "test");
   CU_ASSERT_EQUAL(nbCategories, 1);
   CU_ASSERT_STRING_EQUAL(categories[0].nom, "test");
   CU_ASSERT_EQUAL(categories[0].compteur, 1);

   incrementerOuAjouterCategorie(categories, &nbCategories, "test");
   CU_ASSERT_EQUAL(nbCategories, 1); // Le nombre de catégories ne devrait pas augmenter
   CU_ASSERT_EQUAL(categories[0].compteur, 2); // Le compteur de la catégorie "test" devrait augmenter
}

void test_lireLigneEtExtraireCategories(void) {
   FILE* fichier = fopen("liste.txt", "r");
   CU_ASSERT_PTR_NOT_NULL_FATAL(fichier);

   Categorie categories[10];
   int nbCategories = 0;
   
   while (lireLigneEtExtraireCategories(fichier, categories, &nbCategories));

   CU_ASSERT_EQUAL(nbCategories, 8);
   fclose(fichier);
}

void test_determinerCategorieLaPlusFrequente(void) {
   Categorie categories[2] = {{"dessert", 2}, {"salade", 1}};
   char* categorieLaPlusFrequente = determinerCategorieLaPlusFrequente(categories, 2);

   CU_ASSERT_STRING_EQUAL(categorieLaPlusFrequente, "dessert");
}

void test_trouverCategorieLaPlusFrequente(void) {
   FILE* fichier = fopen("liste.txt", "r");
   CU_ASSERT_PTR_NOT_NULL_FATAL(fichier);

   char* categorieLaPlusFrequente = trouverCategorieLaPlusFrequente(fichier);
   CU_ASSERT_STRING_EQUAL(categorieLaPlusFrequente, "poulet");

   free(categorieLaPlusFrequente);
   fclose(fichier);
}

void test_trouverRecetteLaPlusLongue(void) {
   FILE* fichier = fopen("liste.txt", "r");
   CU_ASSERT_PTR_NOT_NULL_FATAL(fichier);

   RecetteLongue recetteLaPlusLongue = trouverRecetteLaPlusLongue(fichier);
   fclose(fichier);

   CU_ASSERT_STRING_EQUAL(recetteLaPlusLongue.nomRecette, "Authentique gibelotte des iles de Sorel ");
}

//===================================================================================================
int main() {
   
   CU_initialize_registry();

   CU_pSuite suite1 = CU_add_suite("Suite_de_tests_pour_ouvrirFichier_et_nombreDeLignes", NULL, NULL);
   CU_add_test(suite1, "test de ouvrirFichier", test_ouvrirFichier);
   CU_add_test(suite1, "test de nombreDeLignes", test_nombreDeLignes);

   CU_pSuite suite2 = CU_add_suite("Suite_de_tests", NULL, NULL);
   CU_add_test(suite2, "test de estDansLeTableau", test_estDansLeTableau);
   CU_add_test(suite2, "test de ajouterMotSiUnique", test_ajouterMotSiUnique);
   CU_add_test(suite2, "test de traiterEtAjouterMot", test_traiterEtAjouterMot);

   CU_pSuite suite3 = CU_add_suite("Suite_Test_nombreDeMotsSansDoublons", NULL, NULL);
   CU_add_test(suite3, "test de nombreDeMotsSansDoublons", test_nombreDeMotsSansDoublons);

   CU_pSuite suite4 = CU_add_suite("Suite_Test_nombreDeMotsAvecDoublons", NULL, NULL);
   CU_add_test(suite4, "test de nombreDeMotsAvecDoublons", test_nombreDeMotsAvecDoublons);

   CU_pSuite suite5 = CU_add_suite("Suite_Test_Pour_initMot_et_traiterMot", NULL, NULL);
   CU_add_test(suite5, "test de initMot", test_initMot);
   CU_add_test(suite5, "test de traiterMot", test_traiterMot);

   CU_pSuite suite6 = CU_add_suite("Suite_Test_Pour_LettreLaPlusFrequente", NULL, NULL);
   CU_add_test(suite6, "test de trouverLettreLaPlusFrequente", test_trouverLettreLaPlusFrequente);
   CU_add_test(suite6, "test de lettreLaPlusFrequenteSansDoublons", test_lettreLaPlusFrequenteSansDoublons);

   CU_pSuite suite7 = CU_add_suite("Suite_de_test_pour_categories", NULL, NULL);
   CU_add_test(suite7, "test estCategoriePresente", test_estCategoriePresente);
   CU_add_test(suite7, "test compterCategoriesUniques", test_compterCategoriesUniques);

   CU_pSuite suite8 = CU_add_suite("Suite_de_test_pour_compterRecettes", NULL, NULL);
   CU_add_test(suite8, "test de compterRecettes", test_compterRecettes);

   CU_pSuite suite9 = CU_add_suite("Suite_de_test_pour_categories", NULL, NULL);
   CU_add_test(suite9, "test de nettoyer Token", test_nettoyerToken);
   CU_add_test(suite9, "test de incrementer ou ajouter categorie", test_incrementerOuAjouterCategorie);
   CU_add_test(suite9, "test de lire ligne et extraire categories", test_lireLigneEtExtraireCategories);

   CU_pSuite suite10 = CU_add_suite("Suite_de_test_pour_categories_plus_frequente", NULL, NULL);
   CU_add_test(suite10, "test determiner categeorie plus frequente", test_determinerCategorieLaPlusFrequente);
   CU_add_test(suite10, "test trouver categeorie plus frequente", test_trouverCategorieLaPlusFrequente);

   CU_pSuite suite11 = CU_add_suite("Suite_de_test_pour_recette_plus_longue", NULL, NULL);
   CU_add_test(suite11, "test trouver recette plus frequente", test_trouverRecetteLaPlusLongue);


   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();

   CU_cleanup_registry();
   return CU_get_error();
}
