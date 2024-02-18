
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
	int valeur = 0, deno;	
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
			deno = evaluation(expr->droite);
			if (/* condition */ deno != 0) // division par 0
			{
				valeur = evaluation(expr->gauche) / deno;
			}else{
				printf("Division par 0 :( \n"); // ERREUR
			}
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

