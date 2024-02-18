#include "lecture_caracteres.h"
#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"
#include "type_ast.h"
#include "ast_construction.h"

void analyser (char *fichier, Ast *arbre);
void counter_para(int *number);
void rec_ea(int *resultat);
Ast rec_eag();
Ast rec_seq_terme();
Ast rec_terme();
Ast rec_suite_seq_terme();
Ast rec_seq_facteur();
Ast rec_suite_seq_facteur();
Ast rec_facteur();
TypeOperateur rec_op1();
TypeOperateur rec_op2();
