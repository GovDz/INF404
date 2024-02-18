#ifndef ANALYSE_SYNTAXIQUE_H
#define ANALYSE_SYNTAXIQUE_H


#include "type_ast.h"
#include "ast_construction.h"
#include "ast_parcours.h"

 
void rec_eag(Ast *A1);
void seq_terme(Ast *A2);
void suite_seq_facteur(Ast A1, Ast *A2);
void facteur(Ast *A1);
void suite_seq_terme(Ast A1, Ast *A2);
void terme(Ast *A1);
void seq_facteur(Ast *A2);
bool op1(TypeOperateur *Op);
bool op2(TypeOperateur *Op);
// TypeOperateur Operateur(Nature_Lexeme nature); 
#endif  // ANALYSE_SYNTAXIQUE_H

int analyser(char *nomFichier, Ast *A);
