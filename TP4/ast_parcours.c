
#include <stdio.h>
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
	int valeur = 0;
	switch (expr->nature)
	{
	case OPERATION:
		switch (expr->operateur)
		{
		case N_PLUS:
			valeur = evaluation(expr->gauche) + evaluation(expr->droite);
			break;
		case N_MOINS:
			valeur = evaluation(expr->gauche) - evaluation(expr->droite);
			break;
		case N_MUL:
			valeur = evaluation(expr->gauche) * evaluation(expr->droite);
			break;
		case N_DIV:
			valeur = evaluation(expr->gauche) / evaluation(expr->droite);
			break;
		case N_PARO:
			valeur = evaluation(expr->gauche);
			break;
		case N_PARF:
			valeur = evaluation(expr->droite);
			break;
		}
		break;
	case VALEUR:
		valeur = expr->valeur;
		break;
	}
	return valeur;
}

