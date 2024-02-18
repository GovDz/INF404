#ifndef ANALYSE_SYNTAXIQUE_H
#define ANALYSE_SYNTAXIQUE_H


#include "type_ast.h"
#include "ast_construction.h"
#include "ast_parcours.h"

Ast rec_eag();
Ast seq_terme();
Ast suite_seq_terme(Ast A1, Ast *A2);
Ast terme();
Ast seq_facteur();
Ast suite_seq_facteur(Ast A1, Ast *A2);
Ast facteur();
TypeOperateur op1();
TypeOperateur op2();

#endif  // ANALYSE_SYNTAXIQUE_H

int analyser(char *nomFichier, Ast *A);
