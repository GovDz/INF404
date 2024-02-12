#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <stdbool.h>
#include "lecture_caracteres.h"
#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"
#include "ast_construction.h"
#include "ast_parcours.h"
#include "type_ast.h"


Ast rec_eag(){
    return rec_seq_terme();
}
Ast rec_seq_terme(){
    Ast A1 = rec_terme();
    return rec_suite_seq_terme(A1);
}
Ast rec_terme(){
        return rec_facteur();
}
Ast rec_facteur()
{
    Lexeme LC = lexeme_courant();
    Ast A;
    switch (LC.nature)
    {
    case ENTIER:
        A = creer_valeur(LC.valeur);
        avancer();
        break;
    case PARO:
        avancer();
        A = rec_eag();
        if (LC.nature == PARF)
            avancer();
        else
            printf("Erreur de syntaxe : ')' attendu ");
        break;
    case MOINS:
        avancer();
        A = rec_facteur();
        A = creer_op_unaire(MOINS, A);
        break;
    default:
        printf("Erreur de syntaxe : '(', entier ou ')' attendu ");
        break;
    }
    return A;
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
void analyser (char *fichier,int *resultat){
    demarrer(fichier);
    if(!is_para()){
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
    else{
        printf("Yayy :D !! Syntaxe est correct \n");
    }
}
