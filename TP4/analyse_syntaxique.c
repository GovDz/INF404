#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <stdbool.h>
#include "lecture_caracteres.h"
#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"
#include "type_ast.h"
#include "ast_construction.h"



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
Ast rec_suite_seq_terme(Ast *Ag)
{
    Ast *Ad,*A1;
    TypeOperateur Op;
    Lexeme LC = lexeme_courant();
    switch (LC.nature)
    {
    case PLUS:
    case MOINS:
        Op = rec_op1();
        Ad = rec_terme();
        A1 = creer_operation(Op, Ag, Ad);
        return rec_suite_seq_terme(A1);
    case DIV:
    case MUL:
        Op = rec_op2();
        Ad = rec_terme();
        A1 = creer_operation(Op, Ag, Ad);
        return rec_suite_seq_terme(A1);
    default:
        return Ag;
    }
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
        if(LC.nature == PARF){
            avancer();
        }
        else{
            printf("Erreur :( PARO ");
        }
        break;
    case MOINS:
        avancer();
        A = rec_facteur();
        A = creer_op_unaire(MOINS, A);
        break;
    default:
        printf("Erreur de syntaxe : '(', entier ou ')'");
        break;
    }
    return A;
}
TypeOperateur rec_op1()
{
    Lexeme LC = lexeme_courant();
    TypeOperateur Op;
    switch (LC.nature)
    {
    case PLUS:
        Op = N_PLUS;
        avancer();
        break;
    case MOINS:
        Op = N_MOINS;
        avancer();
        break;
    default:
        printf("Erreur : '+' / '-'");
        break;
    }
    return Op;
}
TypeOperateur rec_op1()
{
    Lexeme LC = lexeme_courant();
    TypeOperateur Op;
    switch (LC.nature)
    {
    case PLUS:
        Op = N_PLUS;
        avancer();
        break;
    case MOINS:
        Op = N_MOINS;
        avancer();
        break;
    default:
        printf("Erreur : '+' / '-'");
        break;
    }
    return Op;
}
Ast creer_op_unaire(TypeOperateur Op, Ast A)
{
    Ast A1 = (Ast)malloc(sizeof(NoeudAst));
    A1->nature = OPERATION;
    A1->operateur = Op;
    A1->gauche = A;
    A1->droite = NULL;
    return A1;
}
/*
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
*/
void analyser (char *fichier, Ast *arbre){
    demarrer(fichier);
    *arbre = rec_eag();
    if (!fin_de_sequence())
    {
        printf("Erreur de syntaxe \n");
        exit(1);
    }
    else{
        printf("Yayy :D !! Syntaxe est correct \n");
    }
    printf(" OK :) \n");
    int resultat= evaluation(*arbre);
    printf("Le resultat est : %d \n",resultat);
}
