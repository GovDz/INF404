#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 
#include "lecture_caracteres.h"
#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"

void analyser (char *fichier){
    demarrer(fichier);
    Lexeme Var_lexeme_courant = lexeme_courant(); 
    if (Var_lexeme_courant.nature == ENTIER)
    {
        avancer();
    }
    else
    {
        printf("Erreur de syntaxe entier \n");
        exit(1);
    }
    while (!fin_de_sequence())
    {
        Var_lexeme_courant = lexeme_courant();
        switch (Var_lexeme_courant.nature)
        {
        case PLUS:
            avancer();
            Var_lexeme_courant = lexeme_courant();
                if (Var_lexeme_courant.nature == ENTIER){avancer();}
                else{
                    printf("Erreur de syntaxe entier \n");
                    exit(1);
                }
            break;
        case MOINS:
            avancer();
            Var_lexeme_courant = lexeme_courant();
                if (Var_lexeme_courant.nature == ENTIER){avancer();}
                else{
                    printf("Erreur de syntaxe entier \n");
                    exit(1);
                }
            break;
        case MUL:
            avancer();
            Var_lexeme_courant = lexeme_courant();
                if (Var_lexeme_courant.nature == ENTIER){avancer();}
                else{
                    printf("Erreur de syntaxe entier \n");
                    exit(1);
                }
            break;
        
        default:
            printf("Erreur :( \n");
            exit(1);
            break;
        }
        printf("A\n");
    }
    
    printf("Yayy :D !! Syntaxe est correct ");
}
