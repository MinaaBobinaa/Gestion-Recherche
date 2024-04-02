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
    
    return 0;

    return 0;
}
