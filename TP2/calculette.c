
/* Exemple d'utilisation de l'analyse lexicale : 
    Affichage d'une sequence de lexemes            */

#include <stdio.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"

int main (int argc, char *argv[]) {
    int resultat;
    if(argc!=2){
        printf("Usage : %s fichier \n", argv[0]);
        exit(1);
    }
   analyser(argv[1],&resultat);
   printf("Result is = %d \n",resultat);
   return 0 ;
}
