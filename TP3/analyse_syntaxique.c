#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <stdbool.h>
#include "lecture_caracteres.h"
#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"



void rec_eag(){
    rec_seq_terme();
}
void rec_seq_terme(){
    rec_terme();
    rec_suite_seq_terme();
}
void rec_terme(){
    rec_facteur();
}
void rec_suite_seq_terme()
{
    Lexeme LC = lexeme_courant();
    switch (LC.nature)
    {
    case PLUS:
    case MOINS:
        avancer();
        rec_terme();
        rec_suite_seq_terme();
        break;
    default:
        break;
    }
}
void rec_seq_facteur()
{
    Lexeme LC = lexeme_courant();
    switch (LC.nature)
    {
    case PLUS:
    case MOINS:
        avancer();
        rec_terme();
        rec_suite_seq_terme();
        break;
    default:
        break;
    }
}
void rec_suite_seq_facteur()
{
    Lexeme LC = lexeme_courant();
    switch (LC.nature)
    {
    case PLUS:
    case MOINS:
        avancer();
        rec_terme();
        rec_suite_seq_terme();
        break;
    default:
        break;
    }
}

void rec_facteur()
{
    Lexeme LC = lexeme_courant();
    switch (LC.nature)
    {
    case ENTIER:
        avancer();
        break;
    case PARO:
        printf(" : %s",LC.valeur);
        avancer();
        rec_eag();
        if(LC.nature == PARF){
            avancer();
        }
        else{
            printf("Erreur :( PARO ");
            printf(" : %s",LC.valeur);
        }
        break;
    default:
        printf("Erreur de syntaxe : '(', entier ou ')' attendu ");
        break;
    }
}
void rec_op1()
{
    Lexeme LC = lexeme_courant();
    switch (LC.nature)
    {
    case PLUS:
    case MOINS:
        avancer();
        break;
    default:
        printf("Erreur de syntaxe : '+' ou '-' attendu ");
        break;
    }
}
void rec_op2()
{
    Lexeme LC = lexeme_courant();
    switch (LC.nature)
    {
    case PLUS:
    case MOINS:
        avancer();
        break;
    default:
        printf("Erreur de syntaxe : '+' ou '-' attendu ");
        break;
    }
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
    
}
void analyser (char *fichier){
    demarrer(fichier);
    rec_eag();
    if (!fin_de_sequence())
    {
        printf("Erreur de syntaxe \n");
        exit(1);
    }
    else{
        printf("Yayy :D !! Syntaxe est correct \n");
    }
}
