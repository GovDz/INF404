#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <stdbool.h>
#include "lecture_caracteres.h"
#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"

bool is_para(){ // here is my simple function, to check if every parenthesis is closed

    Lexeme Var_lexeme_courant = lexeme_courant();
    int counter=0;
    while (!fin_de_sequence())
    {
        if(Var_lexeme_courant.nature == PARO) counter++;
        if(Var_lexeme_courant.nature == PARF) counter--;
        avancer();
        Var_lexeme_courant = lexeme_courant();
    }
    return counter == 0;
}
void rec_ea(int *resultat){
    Lexeme Var_lexeme_courant = lexeme_courant(); 
    if (Var_lexeme_courant.nature == ENTIER )
    {
        *resultat = Var_lexeme_courant.valeur;
        avancer();
    }
    else if (Var_lexeme_courant.nature == PARO)
    {
        avancer();
        rec_ea(resultat);
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
                if (Var_lexeme_courant.nature == ENTIER){
                    *resultat = *resultat + Var_lexeme_courant.valeur;
                    avancer();}
                    else if (Var_lexeme_courant.nature == PARO)
                    {
                        int temp = 0;
                        rec_ea(&temp);
                        *resultat = *resultat - temp;
                    }
                else{
                    printf("Erreur de syntaxe entier \n");
                    exit(1);
                }
            break;
        case MOINS:
            avancer();
            Var_lexeme_courant = lexeme_courant();
                if (Var_lexeme_courant.nature == ENTIER){
                    *resultat = *resultat - Var_lexeme_courant.valeur;
                    avancer();}
                    else if (Var_lexeme_courant.nature == PARO)
                    {
                        int temp = 0;
                        rec_ea(&temp);
                        *resultat = *resultat - temp;
                    }
                else{
                    printf("Erreur de syntaxe entier \n");
                    exit(1);
                }
            break;
        case MUL:
            avancer();
            Var_lexeme_courant = lexeme_courant();
                if (Var_lexeme_courant.nature == ENTIER){

                    *resultat = *resultat * Var_lexeme_courant.valeur;
                    avancer();}
                    else if (Var_lexeme_courant.nature == PARO)
                    {
                        int temp = 0;
                        rec_ea(&temp);
                        *resultat = *resultat * temp;
                    }
                else{
                    printf("Erreur de syntaxe entier \n");
                    exit(1);
                }
            break;
        case DIV:
            avancer();
            Var_lexeme_courant = lexeme_courant();
                if (Var_lexeme_courant.nature == ENTIER){
                    if (Var_lexeme_courant.valeur == 0)
                    {
                        printf("Erreur de syntaxe division par 0 \n");
                        exit(1);}
                    *resultat = *resultat / Var_lexeme_courant.valeur;
                    avancer();}
                                        else if (Var_lexeme_courant.nature == PARO)
                    {
                        int temp = 0;
                        rec_ea(&temp);
                        if(temp == 0){
                            printf("Erreur de syntaxe division par 0 \n");
                            exit(1);
                        }
                        *resultat = *resultat / temp;
                    }
                else{
                    printf("Erreur de syntaxe entier \n");
                    exit(1);
                }
            break;
            case PARF:
            avancer();
            break;
        
        default:
            printf("Erreur :( \n");
            exit(1);
            break;
        }
    }
    
    printf("Yayy :D !! Syntaxe est correct \n");
}
void analyser (char *fichier,int *resultat){
    demarrer(fichier);
    if(!is_para){
        printf("Erreur de syntaxe, les parenthèses ne sont pas fermées \n");
        exit(1);
    }
    demarrer(fichier);
    rec_ea(resultat);
    if (!fin_de_sequence())
    {
        printf("Erreur de syntaxe \n");
        exit(1);
    }
}
