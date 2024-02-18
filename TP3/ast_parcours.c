
#include <stdio.h>
#include <stdlib.h>
#include "type_ast.h"

void aff_operateur(TypeOperateur op){
	switch (op) {
		case N_PLUS:
			printf("+") ;
			break;
		case N_MOINS:
			printf("-") ;
			break;
		case N_MUL:
			printf("*") ;
			break;
		case N_DIV: // division
			printf("/") ;
			break;
	} 
}

void afficher(Ast expr) {
	switch (expr->nature) {
               case OPERATION:
                        printf("(");
                        afficher(expr->gauche);
                        aff_operateur(expr->operateur) ;
                        afficher(expr->droite);
                        printf(")");
			break ;
               case VALEUR:
                  	printf("%d", expr->valeur);
			break ;
	}
}

int evaluation(Ast expr)
{
    int valeur, deno;
    switch (expr->nature)
    {
    case OPERATION:
        switch (expr->operateur)
        {
        case N_MUL:
            valeur = evaluation(expr->gauche) * evaluation(expr->droite);
            break;

        case N_MOINS:
            valeur = evaluation(expr->gauche) - evaluation(expr->droite);
            break;

        case N_PLUS:
            valeur = evaluation(expr->gauche) + evaluation(expr->droite);
            break;

        case N_DIV: 
            deno = evaluation(expr->droite);
            if (deno!=0)
                valeur = evaluation(expr->gauche) / deno;
            else
            {
                printf("\n:( division sur 0 \n");
                exit(1);
            }
            break;

        default:
            exit(1);
        }
        break;

    case VALEUR:
        valeur = expr->valeur;
        break;
    default:
        exit(1);
    }

    return valeur;
}
