
/* Exemple d'utilisation de l'analyse lexicale : 
    Affichage d'une sequence de lexemes            */

#include <stdio.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"

int main (int argc, char *argv[]) {
    Ast *arbre = malloc(sizeof(Ast));
    if(argc!=2){
        printf("Usage : %s fichier \n", argv[0]);
        exit(1);
    }
   analyser(argv[1],arbre);
   return 0 ;
}
