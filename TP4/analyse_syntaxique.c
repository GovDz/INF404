#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "analyse_syntaxique.h"
#include "type_ast.h"
#include "ast_construction.h"
#include "ast_parcours.h"
#include "analyse_lexicale.h"

TypeOperateur Operateur(Nature_Lexeme nature); // si on met cette fonction dans analyse_lexicale.h, on a une erreur de compilation

void rec_eag(Ast *A1) {  // d'apres le cours + aide d'AI pour l'optimisation
    seq_terme(A1);
}
void seq_terme(Ast *A2) {
    Ast A1;
    terme(&A1);
    suite_seq_terme(A1, A2);
}
void suite_seq_terme(Ast A1, Ast *A2) {
    Ast A3, A4;
    TypeOperateur op;

    if (op1(&op)) {
        terme(&A3);
        A4 = creer_operation(op, A1, A3);
        suite_seq_terme(A4, A2);
    } else {
        *A2 = A1;
    }
}
void terme(Ast *A1) {
    seq_facteur(A1);
}
void seq_facteur(Ast *A2) {
    Ast A1;
    facteur(&A1);
    suite_seq_facteur(A1, A2);
}
void suite_seq_facteur(Ast A1, Ast *A2) {
    Ast A3, A4;
    TypeOperateur op;

    if (op2(&op)) {
        facteur(&A3);
        A4 = creer_operation(op, A1, A3);
        suite_seq_facteur(A4, A2);
    } else {
        *A2 = A1;
    }
}
void facteur(Ast *A1) {
    switch (lexeme_courant().nature) {
        case ENTIER:
            *A1 = creer_valeur(lexeme_courant().valeur);
            avancer();
            break;
        case PARO:
            avancer();
            rec_eag(A1);
            if (lexeme_courant().nature == PARF) {
                avancer();
            } else {
                handle_error("Missing PARF");
            }
            break;
        default:
            handle_error("Missing PARO");
    }
}

bool op1(TypeOperateur *Op) {
    switch (lexeme_courant().nature) {
        case PLUS:
        case MOINS:
            *Op = Operateur(lexeme_courant().nature);
            avancer();
            return true;
        default:
            return false;
    }
}

bool op2(TypeOperateur *Op) {
    switch (lexeme_courant().nature) {
        case MUL:
        case DIV:
            *Op = Operateur(lexeme_courant().nature);
            avancer();
            return true;
        default:
            return false;
    }
}

TypeOperateur Operateur(Nature_Lexeme nature) {
    switch (nature) {
        case PLUS:
            return N_PLUS;
        case MOINS:
            return N_MOINS;
        case DIV:
            return N_DIV;
        case MUL:
            return N_MUL;
        default:
            handle_error("Operateur");
    }
}
int analyser(char *nomFichier, Ast *A) {
    demarrer(nomFichier);
    rec_eag(A);

    if (lexeme_courant().nature == FIN_SEQUENCE) {
        printf("\n200 OK :))\n");
        afficherA(*A);
        return 1;
    } else {
        handle_error("Erreur syntaxique\n");
        return 0;
    }
}

void handle_error(const char *message) {
    printf("Erreur : %s\n", message);
    exit(1);
}
