#include "test.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "stats.h" 
#include "liste_chainee.h"

void test_ouvrirFichier(void) {
   FILE* f = ouvrirFichier("tests/test.txt", "r");
   CU_ASSERT_PTR_NOT_NULL(f);
   if (f != NULL) fclose(f);

   f = ouvrirFichier("fichier_inexistant.txt", "r");
   CU_ASSERT_PTR_NULL(f);
}

void test_nombreDeLignes(void) {
   FILE* f = ouvrirFichier("tests/test.txt", "r");
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

   fichier = fopen("tests/test.txt", "r");
   CU_ASSERT_PTR_NOT_NULL_FATAL(fichier);
   resultat = nombreDeMotsSansDoublons(fichier);
   CU_ASSERT_EQUAL(resultat, 22); 
   fclose(fichier);

}

void test_nombreDeMotsAvecDoublons(void) {
   FILE *fichier;
   int resultat;

   fichier = fopen("tests/test.txt", "r");
   CU_ASSERT_PTR_NOT_NULL_FATAL(fichier);
   resultat = nombreDeMotsAvecDoublons(fichier);
   CU_ASSERT_EQUAL(resultat, 29);
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
   FILE *fichier = fopen("tests/test.txt", "r");
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
   FILE *fichier = fopen("tests/test.txt", "r");
   CU_ASSERT_PTR_NOT_NULL_FATAL(fichier);

   int resultat = compterCategoriesUniques(fichier);
   fclose(fichier);

   CU_ASSERT_EQUAL(resultat, 8);
}

void test_compterRecettes(void) {
   FILE *fichier;
   int resultat;

   fichier = fopen("tests/test.txt", "r");
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
   CU_ASSERT_EQUAL(nbCategories, 1); 
   CU_ASSERT_EQUAL(categories[0].compteur, 2);
}

void test_lireLigneEtExtraireCategories(void) {
   FILE* fichier = fopen("tests/test.txt", "r");
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
   FILE* fichier = fopen("tests/test.txt", "r");
   CU_ASSERT_PTR_NOT_NULL_FATAL(fichier);
   char* categorieLaPlusFrequente = trouverCategorieLaPlusFrequente(fichier);
   CU_ASSERT_STRING_EQUAL(categorieLaPlusFrequente, "poulet");
   free(categorieLaPlusFrequente);
   fclose(fichier);
}

void test_trouverRecetteLaPlusLongue(void) {
   FILE* fichier = fopen("tests/test.txt", "r");
   CU_ASSERT_PTR_NOT_NULL_FATAL(fichier);
   RecetteLongue recetteLaPlusLongue = trouverRecetteLaPlusLongue(fichier);
   fclose(fichier);
   CU_ASSERT_STRING_EQUAL(recetteLaPlusLongue.nomRecette, "Authentique gibelotte des iles de Sorel ");
}

void test_trim_basic(void) {
   char testStr1[] = "  Hello World  ";
   trim(testStr1);
   CU_ASSERT_STRING_EQUAL(testStr1, "Hello World");
}

void test_trim_no_spaces(void) {
   char testStr2[] = "NoSpaces";
   trim(testStr2);
   CU_ASSERT_STRING_EQUAL(testStr2, "NoSpaces");
}

void test_trim_all_spaces(void) {
   char testStr3[] = "   ";
   trim(testStr3);
   CU_ASSERT_STRING_EQUAL(testStr3, "");
}

void test_trim_empty_string(void) {
   char testStr4[] = "";
   trim(testStr4);
   CU_ASSERT_STRING_EQUAL(testStr4, "");
}

void test_add_recipe_to_new_category(void) {
   CategorieNode* teteCategorie = NULL;
   ajouterRecetteACategorie(&teteCategorie, "Desserts", "Tarte aux pommes");
   CU_ASSERT_PTR_NOT_NULL_FATAL(teteCategorie);
   libererCategoriesEtRecettes(&teteCategorie);
}

void test_add_multiple_recipes_to_same_category(void) {
   CategorieNode* teteCategorie = NULL;
   ajouterRecetteACategorie(&teteCategorie, "Desserts", "Tarte aux pommes");
   ajouterRecetteACategorie(&teteCategorie, "Desserts", "Cheesecake");
   CU_ASSERT_PTR_NOT_NULL_FATAL(teteCategorie->recettes->suivant);
   libererCategoriesEtRecettes(&teteCategorie);
}

void test_add_recipe_to_different_categories(void) {
   CategorieNode* teteCategorie = NULL;
   ajouterRecetteACategorie(&teteCategorie, "Desserts", "Tarte aux pommes");
   ajouterRecetteACategorie(&teteCategorie, "Entrees", "Salade César");
   CU_ASSERT_PTR_NOT_NULL_FATAL(teteCategorie->suivant);
   libererCategoriesEtRecettes(&teteCategorie);
}

void test_enMinuscules(void) {
   char testStr[] = "TeSt StRiNg";
   enMinuscules(testStr);
   CU_ASSERT_STRING_EQUAL(testStr, "test string");
}

void test_chargerEtOrganiserRecettes(void) {
   CategorieNode* teteCategorie = NULL;
   chargerEtOrganiserRecettes("tests/test.txt", &teteCategorie);

   CU_ASSERT_PTR_NOT_NULL_FATAL(teteCategorie);
   
   CategorieNode* current = teteCategorie;
   int foundPoulet = 0, foundBbq = 0; 
   int countPoulet = 0, countBbq = 0;

   while (current != NULL) {
   if (strcmp(current->nomCategorie, "poulet") == 0) {
     foundPoulet = 1;
     RecetteNode* recette = current->recettes;
     while (recette != NULL) {
      countPoulet++;
      recette = recette->suivant;
     }
   } else if (strcmp(current->nomCategorie, "bbq") == 0) {
     foundBbq = 1;
     RecetteNode* recette = current->recettes;
     while (recette != NULL) {
      countBbq++;
      recette = recette->suivant;
     }
   } 
   current = current->suivant;
   }

   CU_ASSERT_TRUE(foundPoulet);
   CU_ASSERT_TRUE(foundBbq);
   CU_ASSERT_EQUAL(countPoulet, 2);
   CU_ASSERT_EQUAL(countBbq, 1); 
   
}

void test_trierRecettesParInsertion(void) {
   RecetteNode* tete = (RecetteNode*)malloc(sizeof(RecetteNode));
   strcpy(tete->nomRecette, "Gâteau au chocolat");
   tete->suivant = (RecetteNode*)malloc(sizeof(RecetteNode));
   strcpy(tete->suivant->nomRecette, "Tarte aux pommes");
   tete->suivant->suivant = (RecetteNode*)malloc(sizeof(RecetteNode));
   strcpy(tete->suivant->suivant->nomRecette, "Crème brûlée");
   tete->suivant->suivant->suivant = NULL;
   trierRecettesParInsertion(&tete);
   CU_ASSERT_STRING_EQUAL(tete->nomRecette, "Crème brûlée");
   CU_ASSERT_STRING_EQUAL(tete->suivant->nomRecette, "Gâteau au chocolat");
   CU_ASSERT_STRING_EQUAL(tete->suivant->suivant->nomRecette, "Tarte aux pommes");

   RecetteNode* current = tete;
   while (current != NULL) {
   RecetteNode* temp = current;
   current = current->suivant;
   free(temp);
   }
}

void test_afficherCategoriesEtRecettesDansFichier(void) {
   CategorieNode* teteCategorie = NULL;
   ajouterRecetteACategorie(&teteCategorie, "dessert", "Gâteau au chocolat");

   const char* nomFichierTest = "test_categories_et_recettes.txt";
   afficherCategoriesEtRecettesDansFichier(teteCategorie, nomFichierTest);
   FILE* fichierTest = fopen(nomFichierTest, "r");
   CU_ASSERT_PTR_NOT_NULL_FATAL(fichierTest);

   char buffer[256];
   CU_ASSERT_PTR_NOT_NULL_FATAL(fgets(buffer, sizeof(buffer), fichierTest)); 
   CU_ASSERT_TRUE(strcmp(buffer, "{dessert}\n") == 0);
   CU_ASSERT_PTR_NOT_NULL_FATAL(fgets(buffer, sizeof(buffer), fichierTest));
   CU_ASSERT_TRUE(strcmp(buffer, "Gâteau au chocolat\n") == 0);

   CU_ASSERT_PTR_NOT_NULL_FATAL(fgets(buffer, sizeof(buffer), fichierTest));

   fclose(fichierTest);
   remove(nomFichierTest); 
   libererCategoriesEtRecettes(&teteCategorie); 
}

void test_afficherRecettesCategorie(void) {
    Recette recettes[5] = {
        {"Gâteau au chocolat", "Dessert"},
        {"Salade César", "Salade"},
        {"Tarte aux pommes", "Dessert"},
        {"Poulet Basquaise", "Plat principal"},
        {"Quiche Lorraine", "Plat principal"}
    };
    int nbRecettes = 5;

    FILE *tempFile = freopen("test_output.txt", "w+", stdout);
    if (tempFile == NULL) {
        CU_FAIL("Failed to redirect stdout to a file.");
        return;
    }
    
    afficherRecettesCategorie(recettes, nbRecettes, "dessert", "pommes");
    fflush(stdout);
    freopen("/dev/tty", "a", stdout);
    tempFile = fopen("test_output.txt", "r");
    CU_ASSERT_PTR_NOT_NULL_FATAL(tempFile);

   
    fclose(tempFile);
    remove("test_output.txt");
}

void test_verifierCategorie(void) {
   Recette recettes[3] = {
      {"Gâteau au chocolat", "Dessert"},
      {"Salade César", "Salade"},
      {"Tarte aux pommes", "Dessert"}
   };
   int nbRecettes = 3;

   int resultInexistante = verifierCategorie(recettes, nbRecettes, "Petit déjeuner");
   CU_ASSERT_EQUAL(resultInexistante, 0);
}

void test_extraireMots(void) {
   char chaine[] = "gâteau au chocolat";
   char mots[3][MAX_CAT_NOM];
   int nbMots;

   nbMots = extraireMots(chaine, mots);

   CU_ASSERT_EQUAL(nbMots, 3);
   CU_ASSERT_STRING_EQUAL(mots[0], "gâteau");
   CU_ASSERT_STRING_EQUAL(mots[1], "au");
   CU_ASSERT_STRING_EQUAL(mots[2], "chocolat");
}


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



   CU_pSuite suite12 = CU_add_suite("Suite de test pour trim et ajout recette", NULL, NULL);
   CU_add_test(suite12, "test trim with basic input", test_trim_basic);
   CU_add_test(suite12, "test trim with no spaces", test_trim_no_spaces);
   CU_add_test(suite12, "test trim with all spaces", test_trim_all_spaces);
   CU_add_test(suite12, "test trim with empty string", test_trim_empty_string);
   CU_add_test(suite12, "test adding recipe to new category", test_add_recipe_to_new_category);
   CU_add_test(suite12, "test adding multiple recipes to same category", test_add_multiple_recipes_to_same_category);
   CU_add_test(suite12, "test adding recipe to different categories", test_add_recipe_to_different_categories);


   CU_pSuite suite13 = CU_add_suite("Suite13", NULL, NULL);
   CU_add_test(suite13, "test of enMinuscules()", test_enMinuscules);
   CU_add_test(suite13, "test of chargerEtOrganiserRecettes()", test_chargerEtOrganiserRecettes);
   CU_add_test(suite13, "test of trierRecettesParInsertion()", test_trierRecettesParInsertion);
   CU_add_test(suite13, "test of test_afficherCategoriesEtRecettesDansFichier()", test_afficherCategoriesEtRecettesDansFichier);
   CU_add_test(suite13, "test of test_afficherRecettesCategorie()", test_afficherRecettesCategorie);
   CU_add_test(suite13, "test of test_verifierCategorie()", test_verifierCategorie);
   CU_add_test(suite13, "test of test_extraireMots()", test_extraireMots);

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();

   CU_cleanup_registry();
   return CU_get_error();
}
